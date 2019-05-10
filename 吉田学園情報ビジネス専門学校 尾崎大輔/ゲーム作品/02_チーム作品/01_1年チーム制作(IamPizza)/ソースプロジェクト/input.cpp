//=============================================================================
//
// ���͏��� [input.cpp]
// Author :	Shun Yokomichi
//
//=============================================================================
#include "dinput.h"

//*************************************************************************************************************************
// �}�N����`
//*************************************************************************************************************************
#define	NUM_KEY_MAX			(256)				// �L�[�̍ő吔
#define JOYKEY_MAX			(12)				// �W���C�L�[�̍ő吔

//*************************************************************************************************************************
// �O���[�o���ϐ�
//*************************************************************************************************************************
LPDIRECTINPUT8				g_pInput = NULL;					// DirerctInput�I�u�W�F�N�g�ւ̃|�C���^
LPDIRECTINPUTDEVICE8		g_pDevKeyboard = NULL;				// ���̓f�o�C�X�i�L�[�{�[�h�j�ւ̃|�C���^
BYTE						g_aKeyState[NUM_KEY_MAX];			// �L�[�{�[�h�̓��͏��i�v���X���j
BYTE						g_aKeyStateTrigger[NUM_KEY_MAX];	// �L�[�{�[�h�̓��͏��i�g���K�[���j
BYTE						g_aKeyStateRelease[NUM_KEY_MAX];	// �L�[�{�[�h�̓��͏��i�����[�X���j
LPDIRECTINPUT8				g_pInputJoycon = NULL;				// �_�C���N�g�C���v�b�g
LPDIRECTINPUTDEVICE8		g_lpDIJoycon = NULL;				// �_�C���N�g�C���v�b�g �f�o�C�X
DIDEVCAPS					g_diDevCaps;						// �W���C�X�e�B�b�N�̔\��
DIJOYSTATE2					g_JoyKeyState;						// �W���C�L�[�̓��͏��(�v���X���)
DIJOYSTATE2					g_JoyKeyStateTrigger;				// �W���C�L�[�̓��͏��(�g���K�[���)
DIJOYSTATE2					g_InputStick;						// �X�e�B�b�N�̓��͏��

//=========================================================================================================================
// �L�[�{�[�h�̏�����
//=========================================================================================================================
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	// DirectInput�I�u�W�F�N�g�̐���
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pInput, NULL)))
	{
		return E_FAIL;
	}

	// ���̓f�o�C�X(�L�[�{�[�h)�̐���
	if (FAILED(g_pInput->CreateDevice(GUID_SysKeyboard, &g_pDevKeyboard, NULL)))
	{
		return E_FAIL;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	// �������[�h��ݒ�
	if (FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��(���͐���J�n)
	g_pDevKeyboard->Acquire();

	return S_OK;
}

//=========================================================================================================================
// �L�[�{�[�h�̏I������
//=========================================================================================================================
void UninitKeyboard(void)
{
	// ���̓f�o�C�X(�L�[�{�[�h)�̊J��
	if (g_pDevKeyboard != NULL)
	{
		g_pDevKeyboard->Unacquire();	// �L�[�{�[�h�ւ̃A�N�Z�X�������
		g_pDevKeyboard->Release();
		g_pDevKeyboard = NULL;
	}

	// ���̓f�o�C�X(�W���C�X�e�B�b�N)�̊J��
	if (g_lpDIJoycon != NULL)
	{
		g_lpDIJoycon->Unacquire();	// �L�[�{�[�h�ւ̃A�N�Z�X�������
		g_lpDIJoycon->Release();
		g_lpDIJoycon = NULL;
	}

	// DirectInput�I�u�W�F�N�g�̊J��
	if (g_pInput != NULL)
	{
		g_pInput->Release();
		g_pInput = NULL;
	}

}

//=========================================================================================================================
// �L�[�{�[�h�̍X�V����
//=========================================================================================================================
void UpdateKeyboard(void)
{
	BYTE aKeyState[NUM_KEY_MAX];
	int nCntKey;

	// ���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			g_aKeyStateRelease[nCntKey] = (g_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & g_aKeyState[nCntKey];
			g_aKeyStateTrigger[nCntKey] = (g_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];
			g_aKeyState[nCntKey] = aKeyState[nCntKey];
		}
	}
	else
	{
		g_pDevKeyboard->Acquire();		// �L�[�{�[�h�ւ̃A�N�Z�X�����l��
	}
}

//=========================================================================================================================
// �L�[�{�[�h�̓��͏��(�v���X���)���擾
//=========================================================================================================================
bool GetKeyboardPress(int nKey)
{
	return (g_aKeyState[nKey] & 0x80) ? true : false;
}

//=========================================================================================================================
// �L�[�{�[�h�̓��͏��(�g���K�[���)���擾
//=========================================================================================================================
bool GetKeyboardTrigger(int nKey)
{
	return (g_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//=========================================================================================================================
// �L�[�{�[�h�̓��͏��(�����[�X���)���擾
//=========================================================================================================================
bool GetKeyboardRelease(int nKey)
{
	return (g_aKeyStateRelease[nKey] & 0x80) ? true : false;
}

/*=========================================================
�W���C�R���g���[���[���擾(�f�o�C�X�̍쐬)
=========================================================*/
BOOL CALLBACK EnumJoystickCallback(const DIDEVICEINSTANCE *pdidInstance, VOID *pContext)
{
	HRESULT hr;

	hr = g_pInputJoycon->CreateDevice(pdidInstance->guidInstance, &g_lpDIJoycon, NULL);

	if (FAILED(hr))
	{
		return DIENUM_CONTINUE;
	}

	return DIENUM_STOP;
}


/*=========================================================
�W���C�X�e�B�b�N���擾(�f�o�C�X�̍쐬)
===========================================================*/
BOOL CALLBACK EnumAxesCallback(const DIDEVICEOBJECTINSTANCE *pdidoi, VOID *pContext)
{
	DIPROPRANGE diprg;

	diprg.diph.dwSize = sizeof(DIPROPRANGE);
	diprg.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	diprg.diph.dwHow = DIPH_BYID;
	diprg.diph.dwObj = pdidoi->dwType;
	diprg.lMin = 0 - 1000;										// ��܂��͍��{�^���������ꂽ�Ƃ��̒l
	diprg.lMax = 0 + 1000;										// ���܂��͉E�{�^���������ꂽ�Ƃ��̒l

	if (FAILED(g_lpDIJoycon->SetProperty(DIPROP_RANGE, &diprg.diph)))
	{
		return DIENUM_STOP;
	}
	return DIENUM_CONTINUE;
}


//=========================================================
// �_�C���N�g�C���v�b�g�̏���������
//===========================================================
HRESULT InitJoycon(HINSTANCE hInstance, HWND hWnd)
{
	HRESULT hr;

	// DirectInput�̍쐬
	hr = DirectInput8Create(hInstance, DIRECTINPUT_VERSION,
		IID_IDirectInput8, (void**)&g_pInputJoycon, NULL);
	if (FAILED(hr))
	{
		MessageBox(NULL, "DirectInput8�I�u�W�F�N�g�̍쐬�Ɏ��s", "Direct Input Error", MB_OK);
		return hr;
	}
	// �f�o�C�X��񋓂��č쐬
	hr = g_pInputJoycon->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumJoystickCallback,
		NULL, DIEDFL_ATTACHEDONLY);
	if (g_lpDIJoycon == NULL)
	{// �R���g���[���[���������Ă��Ȃ���
		if (FAILED(hr) || g_lpDIJoycon == NULL)
		{
			return hr;
		}
	}
	// �f�[�^�`����ݒ�
	if (g_lpDIJoycon != NULL)
	{// �R���g���[���[���������Ă��鎞
		hr = g_lpDIJoycon->SetDataFormat(&c_dfDIJoystick2);
	}
	if (g_lpDIJoycon == NULL)
	{// �R���g���[���[���������Ă��Ȃ���
		if (FAILED(hr))
		{
			MessageBox(NULL, "c_dfDIJoystick2�`���̐ݒ�Ɏ��s", "Direct Input Error", MB_OK);
			return hr;
		}
	}
	// �������[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
	if (g_lpDIJoycon != NULL)
	{// �R���g���[���[���������Ă��鎞
		hr = g_lpDIJoycon->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	}
	if (g_lpDIJoycon == NULL)
	{// �R���g���[���[���������Ă��Ȃ���
		if (FAILED(hr))
		{
			MessageBox(NULL, "�t�H�A�O���E���h����r�����[�h�̐ݒ�Ɏ��s", "Direct Input Error", MB_OK);
			return hr;
		}
	}
	// �R�[���o�b�N�֐����g���Ċe���̃��[�h��ݒ�
	if (g_lpDIJoycon != NULL)
	{// �R���g���[���[���������Ă��鎞
		hr = g_lpDIJoycon->EnumObjects(EnumAxesCallback, NULL, DIDFT_AXIS);
	}
	if (g_lpDIJoycon == NULL)
	{// �R���g���[���[���������Ă��Ȃ���
		if (FAILED(hr))
		{
			MessageBox(NULL, "�����[�h�̐ݒ�Ɏ��s", "Direct Input Error", MB_OK);
			return hr;
		}
	}
	// �R���g���[���[�ւ̃A�N�Z�X�����l��(���͐���J�n)
	g_lpDIJoycon->Acquire();
	return S_OK;
}


/*=============================================================================
�W���C�R���g���[���[�̍X�V����
=============================================================================*/
void UpdateJoycon(void)
{
	DIJOYSTATE2  aJoyKeyState;			//�R���g���[���[�̓��͑҂�
	int nCntKey;
	if (g_lpDIJoycon != NULL)
	{// �R���g���[���[���������Ă��鎞
	 // ���͂��ꂽ���̂������p��
		g_lpDIJoycon->Poll();

		// ���̓f�o�C�X����f�[�^���擾
		if (SUCCEEDED(g_lpDIJoycon->GetDeviceState(sizeof(DIJOYSTATE2), &aJoyKeyState)))
		{
			for (nCntKey = 0; nCntKey < JOYKEY_MAX; nCntKey++)
			{
				// �L�[�{�[�h(�g���K�[)�̓��͏��ۑ�
				g_JoyKeyStateTrigger.rgbButtons[nCntKey] =
					(g_JoyKeyState.rgbButtons[nCntKey] ^ aJoyKeyState.rgbButtons[nCntKey]) & aJoyKeyState.rgbButtons[nCntKey];
				// �L�[�{�[�h(�v���X)�̓��͏��ۑ�
				g_JoyKeyState.rgbButtons[nCntKey] = aJoyKeyState.rgbButtons[nCntKey];
			}
		}
		else
		{
			g_lpDIJoycon->Acquire(); //�L�[�{�[�h�̃A�N�Z�X�����l��
		}
	}
}


/*=============================================================================
�W���C�R���g���[���[�̓��͏��(�v���X���)���擾
=============================================================================*/
bool GetJoyControllerPress(int nKey)
{
	return(g_JoyKeyState.rgbButtons[nKey] & 0x80) ? true : false;
}


/*=============================================================================
�W���C�R���g���[���[�̓��͏��(�g���K�[���)���擾
=============================================================================*/
bool GetJoyControllerTrigger(int nKey)
{
	return(g_JoyKeyStateTrigger.rgbButtons[nKey] & 0x80) ? true : false;
}


/*=============================================================================
�A�i���O�X�e�B�b�N�̎擾
=============================================================================*/
DIJOYSTATE2 GetStick(void)
{
	if (g_lpDIJoycon != NULL)
	{// �R���g���[���[���������Ă��鎞
		g_lpDIJoycon->GetDeviceState(sizeof(DIJOYSTATE2), &g_InputStick);
	}
	return g_InputStick;
}

