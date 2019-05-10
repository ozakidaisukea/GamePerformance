//=============================================================================
//
// ���͏��� [input.cpp]
// Author : Niwa Hodaka
//
//=============================================================================
#include "input.h"

typedef struct
{
	XINPUT_STATE m_State;     // �Q�[���p�b�h�̏��
	bool m_bConnected;        // �ڑ����ꂽ���ǂ���
}CONTROLER_STATE;

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	NUM_KEY_MAX	     (256)	 // �L�[�̍ő吔
#define DI_JOY_I_INPUT   (1000)  // �X�e�B�b�N�̕������͎�t���s���͈�
#define MAX_DEVICE       (4)
#define REPEAT_FRAME     (20)    // ���s�[�g�����N�����n�߂�t���[�����̍��v
#define REPEAT_TRIGGER   (7)     // ���s�[�g�����N������t���[���̊Ԋu


#define MIN_GAMEPAD_LEFT_THUMB_X  (300)     // ���X�e�B�b�N�̉������̓��͂��󂯕t���鎲�̍ŏ��l
#define MIN_GAMEPAD_LEFT_THUMB_Y  (25000)   // ���X�e�B�b�N�̏c�����̓��͂��󂯕t���鎲�̍ŏ��l

#define MIN_GAMEPAD_RIGHT_THUMB_X (300)     // �E�X�e�B�b�N�̉������̓��͂��󂯕t���鎲�̍ŏ��l
#define MIN_GAMEPAD_RIGHT_THUMB_Y (25000)   // �E�X�e�B�b�N�̏c�����̓��͂��󂯕t���鎲�̍ŏ��l

#define MIN_GAMEPAD_LEFT_TRIGGER  (130)     // LT�{�^���̓��͂��󂯕t����l�̍ŏ��l
#define MIN_GAMEPAD_RIGHT_TRIGGER (130)     // RT�{�^���̓��͂��󂯕t����l�̍ŏ��l

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECTINPUT8 g_pInput = NULL;              // DirectInput�I�u�W�F�N�g�ւ̃|�C���^
LPDIRECTINPUTDEVICE8 g_pDevKeyboard = NULL;  // ���̓f�o�C�X(�L�[�{�[�h)�ւ̃|�C���^
LPDIRECTINPUTDEVICE8 g_pDevJoypad = NULL;    // ���̓f�o�C�X(�W���C�p�b�h)�ւ̃|�C���^
CONTROLER_STATE g_XInput[MAX_DEVICE];        // XInput�̏��
XINPUT_VIBRATION g_aVibrarion[MAX_DEVICE];   // �U���@�\�ݒ�p

BYTE g_aKeyState[NUM_KEY_MAX];               // �L�[�{�[�h�̓��͏��(�v���X���)
BYTE g_aKeyStateTrigger[NUM_KEY_MAX];        // �L�[�{�[�h�̓��͏��(�g���K�[���)
BYTE g_aKeyStateRelease[NUM_KEY_MAX];        // �L�[�{�[�h�̓��͏��(�����[�X���)
BYTE g_aJoyState[DIJS_BUTTON_MAX];           // �W���C�p�b�h�̓��͏��(�v���X���)
BYTE g_aJoyStateTrigger[DIJS_BUTTON_MAX];    // �W���C�p�b�h�̓��͏��(�g���K�[���)
BYTE g_aJoyStateRelease[DIJS_BUTTON_MAX];    // �W���C�p�b�h�̓��͏��(�����[�X���)

DWORD            m_wButtons[MAX_DEVICE];                                // �{�^���̏��
BYTE             m_bLeftTrigger[MAX_DEVICE];                            // LT�{�^���̏��
BYTE             m_bRightTrigger[MAX_DEVICE];                           // RT�{�^���̏��
SHORT            m_sThumbLX[MAX_DEVICE];                                // ���X�e�B�b�N��X��
SHORT            m_sThumbLY[MAX_DEVICE];                                // ���X�e�B�b�N��Y��
SHORT            m_sThumbRX[MAX_DEVICE];                                // �E�X�e�B�b�N��X��
SHORT            m_sThumbRY[MAX_DEVICE];                                // �E�X�e�B�b�N��Y��
BYTE             m_aGamePadState[MAX_DEVICE][XIJS_BUTTON_MAX];          // �Q�[���p�b�h�̓��͏��(�v���X���)
BYTE             m_aGamePadStateTrigger[MAX_DEVICE][XIJS_BUTTON_MAX];   // �Q�[���p�b�h�̓��͏��(�g���K�[���)
BYTE             m_aGamePadStateRelease[MAX_DEVICE][XIJS_BUTTON_MAX];   // �Q�[���p�b�h�̓��͏��(�����[�X���)
BYTE             m_aGamePadStateRepeat[MAX_DEVICE][XIJS_BUTTON_MAX];    // �Q�[���p�b�h�̓��͏��(���s�[�g���)
DWORD            m_aGamePadCounter[MAX_DEVICE][XIJS_BUTTON_MAX];        // �Q�[���p�b�h�̓��͂���Ă�Ԃ𐔂���J�E���^�[
int  Pad;                                    // �ڑ�����Ă���W���C�p�b�h�̐�

//=============================================================================
// ����������
//=============================================================================
HRESULT InitInput(HINSTANCE hInstance, HWND hWnd)
{
	// DirectInput�I�u�W�F�N�g�̐���
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pInput, NULL)))
	{
		return E_FAIL;
	}
	//======================================
	// �L�[�{�[�h����������
	//======================================
	// ���̓f�o�C�X(�L�[�{�[�h)�̐���
	if (FAILED(g_pInput->CreateDevice(GUID_SysKeyboard, &g_pDevKeyboard, NULL)))
	{
		return E_FAIL;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	if(FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	// �������[�h��ݒ�
	if(FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}
	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��(���͐���J�n)
	g_pDevKeyboard->Acquire();

	//======================================
	// �W���C�p�b�h����������
	//======================================
	// ���̓f�o�C�X(�W���C�p�b�h)�̐���
	if (FAILED(g_pInput->CreateDevice(GUID_Joystick, &g_pDevJoypad, NULL)))
	{
		return E_FAIL;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(g_pDevJoypad->SetDataFormat(&c_dfDIJoystick)))
	{
		return E_FAIL;
	}

	// �������[�h��ݒ�
	if (FAILED(g_pDevJoypad->SetCooperativeLevel(hWnd, (DISCL_BACKGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}
	if (FAILED(g_pDevJoypad->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	if (g_pDevJoypad != NULL)
	{// �����ł���
		DIPROPRANGE diprg;

		// ���̒l�͈̔͂�ݒ�
		diprg.diph.dwSize = sizeof(diprg);
		diprg.diph.dwHeaderSize = sizeof(diprg.diph);
		diprg.diph.dwHow = DIPH_BYOFFSET;
		diprg.lMin = -DI_JOY_I_INPUT;
		diprg.lMax = DI_JOY_I_INPUT;

		// ���̐ݒ�
		// ���A�i���O�X�e�B�b�N
		diprg.diph.dwObj = DIJOFS_X;
		g_pDevJoypad->SetProperty(DIPROP_RANGE, &diprg.diph);
		diprg.diph.dwObj = DIJOFS_Y;
		g_pDevJoypad->SetProperty(DIPROP_RANGE, &diprg.diph);
		diprg.diph.dwObj = DIJOFS_Z;
		g_pDevJoypad->SetProperty(DIPROP_RANGE, &diprg.diph);

		// �E�A�i���O�X�e�B�b�N
		diprg.diph.dwObj = DIJOFS_RX;
		g_pDevJoypad->SetProperty(DIPROP_RANGE, &diprg.diph);
		diprg.diph.dwObj = DIJOFS_RY;
		g_pDevJoypad->SetProperty(DIPROP_RANGE, &diprg.diph);
		diprg.diph.dwObj = DIJOFS_RZ;
		g_pDevJoypad->SetProperty(DIPROP_RANGE, &diprg.diph);

		// ?
		//diprg.diph.dwObj = DIJOFS_SLIDER(0);
		//g_pDevJoypad->SetProperty(DIPROP_RANGE, &diprg.diph);

		// �\���L�[(���0�x�Ƃ����v���Ɋp�x * 100)
		diprg.diph.dwObj = DIJOFS_POV(0);
		g_pDevJoypad->SetProperty(DIPROP_RANGE, &diprg.diph);

		// �W���C�p�b�h�ւ̃A�N�Z�X�����l��(���͐���J�n)
		g_pDevJoypad->Acquire();
	}

	//======================================
	// XInput����������
	//======================================
	// �Q�[���p�b�h�̃N���A
	ZeroMemory(&g_XInput, sizeof(CONTROLER_STATE) * MAX_DEVICE);

	// �U���@�\�̃N���A
	ZeroMemory(&g_aVibrarion, sizeof(XINPUT_VIBRATION) * MAX_DEVICE);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitInput(void)
{
	// ���̓f�o�C�X(�L�[�{�[�h)�̊J��
	if (g_pDevKeyboard != NULL)
	{
		g_pDevKeyboard->Unacquire(); // �L�[�{�[�h�ւ̃A�N�Z�X�������
		g_pDevKeyboard->Release();
		g_pDevKeyboard = NULL;
	}

	// ���̓f�o�C�X(�W���C�p�b�h)�̊J��
	if (g_pDevJoypad != NULL)
	{
		g_pDevJoypad->Unacquire();   // �W���C�p�b�h�ւ̃A�N�Z�X�������
		g_pDevJoypad->Release();
		g_pDevJoypad = NULL;
	}

	// DirectInput�I�u�W�F�N�g�̊J��
	if (g_pInput != NULL)
	{
		g_pInput->Release();
		g_pInput = NULL;
	}

	// �Q�[���p�b�h�̊J��
	XInputEnable(false);
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateInput(void)
{
	//======================================
	// �L�[�{�[�h�X�V����
	//======================================
	BYTE aKeyState[NUM_KEY_MAX]; // �L�[�{�[�h�̓��͏��
	int nCntKey;

	// ���̓f�o�C�X(�L�[�{�[�h)����f�[�^���擾
	if (SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			g_aKeyStateTrigger[nCntKey] = (g_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];   // �L�[�{�[�h�̓��͏��(�g���K�[���)�ۑ�
			g_aKeyStateRelease[nCntKey] = (g_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & g_aKeyState[nCntKey]; // �L�[�{�[�h�̓��͏��(�����[�X���)�ۑ�
			g_aKeyState[nCntKey] = aKeyState[nCntKey];  // �L�[�{�[�h�̓��͏��(�v���X���)�ۑ�
		}
	}
	else
	{
		g_pDevKeyboard->Acquire(); // �L�[�{�[�h�ւ̃A�N�Z�X�����l��
	}

	//======================================
	// �W���C�p�b�h�X�V����
	//======================================
	if (g_pDevJoypad != NULL)
	{// �����ł���
		DIJOYSTATE dijs;   // �W���C�p�b�h�̓��͏��
		BYTE aJoyState[DIJS_BUTTON_MAX]; // �L�[�{�[�h�̓��͏��

		// ���̓f�o�C�X(�W���C�p�b�h)����f�[�^���擾
		g_pDevJoypad->Poll();
		if (SUCCEEDED(g_pDevJoypad->GetDeviceState(sizeof(DIJOYSTATE), &dijs)))
		{
			//-----------------------------
			// ���A�i���O�X�e�B�b�N
			//-----------------------------
			if (dijs.lY <= -100)
			{// ���A�i���O�X�e�B�b�N����ɓ|���ꂽ
				dijs.rgbButtons[DIJS_BUTTON_10] = 0x80;
			}
			if (dijs.lY >= 100)
			{// ���A�i���O�X�e�B�b�N�����ɓ|���ꂽ
				dijs.rgbButtons[DIJS_BUTTON_11] = 0x80;
			}
			if (dijs.lX <= -100)
			{// ���A�i���O�X�e�B�b�N�����ɓ|���ꂽ
				dijs.rgbButtons[DIJS_BUTTON_13] = 0x80;
			}
			if (dijs.lX >= 100)
			{// ���A�i���O�X�e�B�b�N���E�ɓ|���ꂽ
				dijs.rgbButtons[DIJS_BUTTON_12] = 0x80;
			}

			//-----------------------------
			// �E�A�i���O�X�e�B�b�N
			//-----------------------------
			if (dijs.lRz <= -100)
			{// �E�A�i���O�X�e�B�b�N����ɓ|���ꂽ
				dijs.rgbButtons[DIJS_BUTTON_14] = 0x80;
			}
			if (dijs.lRz >= 100)
			{// �E�A�i���O�X�e�B�b�N�����ɓ|���ꂽ
				dijs.rgbButtons[DIJS_BUTTON_15] = 0x80;
			}
			if (dijs.lZ <= -100)
			{// �E�A�i���O�X�e�B�b�N�����ɓ|���ꂽ
				dijs.rgbButtons[DIJS_BUTTON_17] = 0x80;
			}
			if (dijs.lZ >= 100)
			{// �E�A�i���O�X�e�B�b�N���E�ɓ|���ꂽ
				dijs.rgbButtons[DIJS_BUTTON_16] = 0x80;
			}

			//-----------------------------
			// �\���L�[
			//-----------------------------
			if (dijs.rgdwPOV[0] / 100 == 0)
			{// �\���L�[�̏オ�����ꂽ
				dijs.rgbButtons[DIJS_BUTTON_18] = 0x80;
			}
			if (dijs.rgdwPOV[0] / 100 == 45)
			{// �\���L�[�̉E�オ�����ꂽ
				dijs.rgbButtons[DIJS_BUTTON_18] = 0x80;
				dijs.rgbButtons[DIJS_BUTTON_20] = 0x80;
			}
			if (dijs.rgdwPOV[0] / 100 == 90)
			{// �\���L�[�̉��������ꂽ
				dijs.rgbButtons[DIJS_BUTTON_20] = 0x80;
			}
			if (dijs.rgdwPOV[0] / 100 == 135)
			{// �\���L�[�̉E���������ꂽ
				dijs.rgbButtons[DIJS_BUTTON_19] = 0x80;
				dijs.rgbButtons[DIJS_BUTTON_20] = 0x80;
			}
			if (dijs.rgdwPOV[0] / 100 == 180)
			{// �\���L�[�̉E�������ꂽ
				dijs.rgbButtons[DIJS_BUTTON_19] = 0x80;
			}
			if (dijs.rgdwPOV[0] / 100 == 225)
			{// �\���L�[�̍����������ꂽ
				dijs.rgbButtons[DIJS_BUTTON_19] = 0x80;
				dijs.rgbButtons[DIJS_BUTTON_21] = 0x80;
			}
			if (dijs.rgdwPOV[0] / 100 == 270)
			{// �\���L�[�̍��������ꂽ
				dijs.rgbButtons[DIJS_BUTTON_21] = 0x80;
			}
			if (dijs.rgdwPOV[0] / 100 == 315)
			{// �\���L�[�̍��オ�����ꂽ
				dijs.rgbButtons[DIJS_BUTTON_18] = 0x80;
				dijs.rgbButtons[DIJS_BUTTON_21] = 0x80;
			}

			for (int nCntJoyButton = 0; nCntJoyButton < DIJS_BUTTON_MAX; nCntJoyButton++)
			{// �W���C�p�b�h�̃{�^���̐������J��Ԃ�
				g_aJoyStateTrigger[nCntJoyButton] = (g_aJoyState[nCntJoyButton] ^ dijs.rgbButtons[nCntJoyButton]) & dijs.rgbButtons[nCntJoyButton];  // �W���C�p�b�h�̓��͏��(�g���K�[���)�ۑ�
				g_aJoyStateRelease[nCntJoyButton] = (g_aJoyState[nCntJoyButton] ^ dijs.rgbButtons[nCntJoyButton]) & g_aJoyState[nCntJoyButton];      // �W���C�p�b�h�̓��͏��(�����[�X���)�ۑ�
				g_aJoyState[nCntJoyButton] = dijs.rgbButtons[nCntJoyButton];   // �W���C�p�b�h�̓��͏��(�v���X���)�ۑ�
				aJoyState[nCntJoyButton] = false;
			}
		}
		else
		{
			g_pDevJoypad->Acquire(); // �W���C�p�b�h�ւ̃A�N�Z�X�����l��
		}
	}



	DWORD dwResult;                                         // �Q�[���p�b�h���擾�ł������ǂ���
	BYTE aGamePadState[MAX_DEVICE][XIJS_BUTTON_MAX] = {};   // �Q�[���p�b�h�̃{�^�����͏��
	for (DWORD nCntPad = 0; nCntPad < MAX_DEVICE; nCntPad++)
	{// �ڑ��ł���Q�[���p�b�h(�ő�4�܂�)�̐������J��Ԃ�
	 // �Q�[���p�b�h�̏�Ԃ��擾
		dwResult = XInputGetState(nCntPad, &g_XInput[nCntPad].m_State);
		if (dwResult == ERROR_SUCCESS)
		{// ��Ԏ擾�ɐ�������
		 // ��Ԃ��i�[����
			g_XInput[nCntPad].m_bConnected = true;                                       // �ڑ����ꂽ��Ԃɂ���
			m_wButtons[nCntPad] = g_XInput[nCntPad].m_State.Gamepad.wButtons;            // �{�^���̃r�b�g�����擾
			m_bLeftTrigger[nCntPad] = g_XInput[nCntPad].m_State.Gamepad.bLeftTrigger;    // LT�{�^���̏�Ԃ��擾
			m_bRightTrigger[nCntPad] = g_XInput[nCntPad].m_State.Gamepad.bRightTrigger;  // RT�{�^���̏�Ԃ��擾
			m_sThumbLX[nCntPad] = g_XInput[nCntPad].m_State.Gamepad.sThumbLX;            // ���X�e�B�b�N��X�����擾
			m_sThumbLY[nCntPad] = g_XInput[nCntPad].m_State.Gamepad.sThumbLY;            // ���X�e�B�b�N��Y�����擾
			m_sThumbRX[nCntPad] = g_XInput[nCntPad].m_State.Gamepad.sThumbRX;            // �E�X�e�B�b�N��X�����擾
			m_sThumbRY[nCntPad] = g_XInput[nCntPad].m_State.Gamepad.sThumbRY;            // �E�X�e�B�b�N��Y�����擾

			// ���͂̏�Ԃ��擾����
			// �{�^��
			DWORD wButtons = m_wButtons[nCntPad];   // �{�^���̃r�b�g���
			if (wButtons >= XINPUT_GAMEPAD_Y)
			{// Y�{�^����������Ă���
				aGamePadState[nCntPad][XIJS_BUTTON_13] = 0x80;  // ���͂��N��
				wButtons -= XINPUT_GAMEPAD_Y;
			}
			if (wButtons >= XINPUT_GAMEPAD_X)
			{// X�{�^����������Ă���
				aGamePadState[nCntPad][XIJS_BUTTON_12] = 0x80;  // ���͂��N��
				wButtons -= XINPUT_GAMEPAD_X;
			}
			if (wButtons >= XINPUT_GAMEPAD_B)
			{// B�{�^����������Ă���
				aGamePadState[nCntPad][XIJS_BUTTON_11] = 0x80;  // ���͂��N��
				wButtons -= XINPUT_GAMEPAD_B;
			}
			if (wButtons >= XINPUT_GAMEPAD_A)
			{// A�{�^����������Ă���
				aGamePadState[nCntPad][XIJS_BUTTON_10] = 0x80;  // ���͂��N��
				wButtons -= XINPUT_GAMEPAD_A;
			}
			if (wButtons >= XINPUT_GAMEPAD_RIGHT_SHOULDER)
			{// RB�{�^����������Ă���
				aGamePadState[nCntPad][XIJS_BUTTON_9] = 0x80;  // ���͂��N��
				wButtons -= XINPUT_GAMEPAD_RIGHT_SHOULDER;
			}
			if (wButtons >= XINPUT_GAMEPAD_LEFT_SHOULDER)
			{// LB�{�^����������Ă���
				aGamePadState[nCntPad][XIJS_BUTTON_8] = 0x80;  // ���͂��N��
				wButtons -= XINPUT_GAMEPAD_LEFT_SHOULDER;
			}
			if (wButtons >= XINPUT_GAMEPAD_RIGHT_THUMB)
			{// �E�X�e�B�b�N���������܂�Ă���
				aGamePadState[nCntPad][XIJS_BUTTON_7] = 0x80;  // ���͂��N��
				wButtons -= XINPUT_GAMEPAD_RIGHT_THUMB;
			}
			if (wButtons >= XINPUT_GAMEPAD_LEFT_THUMB)
			{// �E�X�e�B�b�N���������܂�Ă���
				aGamePadState[nCntPad][XIJS_BUTTON_6] = 0x80;  // ���͂��N��
				wButtons -= XINPUT_GAMEPAD_LEFT_THUMB;
			}
			if (wButtons >= XINPUT_GAMEPAD_BACK)
			{// BACK�{�^����������Ă���
				aGamePadState[nCntPad][XIJS_BUTTON_5] = 0x80;  // ���͂��N��
				wButtons -= XINPUT_GAMEPAD_BACK;
			}
			if (wButtons >= XINPUT_GAMEPAD_START)
			{// BACK�{�^����������Ă���
				aGamePadState[nCntPad][XIJS_BUTTON_4] = 0x80;  // ���͂��N��
				wButtons -= XINPUT_GAMEPAD_START;
			}
			if (wButtons >= XINPUT_GAMEPAD_DPAD_RIGHT)
			{// �\���L�[�̉E��������Ă���
				aGamePadState[nCntPad][XIJS_BUTTON_3] = 0x80;  // ���͂��N��
				wButtons -= XINPUT_GAMEPAD_DPAD_RIGHT;
			}
			if (wButtons >= XINPUT_GAMEPAD_DPAD_LEFT)
			{// �\���L�[�̍���������Ă���
				aGamePadState[nCntPad][XIJS_BUTTON_2] = 0x80;  // ���͂��N��
				wButtons -= XINPUT_GAMEPAD_DPAD_LEFT;
			}
			if (wButtons >= XINPUT_GAMEPAD_DPAD_DOWN)
			{// �\���L�[�̉���������Ă���
				aGamePadState[nCntPad][XIJS_BUTTON_1] = 0x80;  // ���͂��N��
				wButtons -= XINPUT_GAMEPAD_DPAD_DOWN;
			}
			if (wButtons >= XINPUT_GAMEPAD_DPAD_UP)
			{// �\���L�[�̏オ������Ă���
				aGamePadState[nCntPad][XIJS_BUTTON_0] = 0x80;  // ���͂��N��
			}

			// LT�g���K�[
			if (m_bLeftTrigger[nCntPad] >= MIN_GAMEPAD_LEFT_TRIGGER)
			{// LT�g���K�[��������Ă���
				aGamePadState[nCntPad][XIJS_BUTTON_14] = 0x80;  // ���͂��N������
			}
			// RT�g���K�[
			if (m_bRightTrigger[nCntPad] >= MIN_GAMEPAD_RIGHT_TRIGGER)
			{// LR�g���K�[��������Ă���
				aGamePadState[nCntPad][XIJS_BUTTON_15] = 0x80;  // ���͂��N������
			}

			// ���X�e�B�b�N
			if (m_sThumbLX[nCntPad] >= MIN_GAMEPAD_LEFT_THUMB_X)
			{// ���X�e�B�b�N���E�ɓ|���ꂽ
				aGamePadState[nCntPad][XIJS_BUTTON_27] = 0x80;   // ���͂��N������
			}
			if (m_sThumbLX[nCntPad] <= -MIN_GAMEPAD_LEFT_THUMB_X)
			{// ���X�e�B�b�N�����ɓ|���ꂽ
				aGamePadState[nCntPad][XIJS_BUTTON_26] = 0x80;   // ���͂��N������
			}
			if (m_sThumbLY[nCntPad] >= MIN_GAMEPAD_LEFT_THUMB_Y)
			{// ���X�e�B�b�N����ɓ|���ꂽ
				aGamePadState[nCntPad][XIJS_BUTTON_24] = 0x80;   // ���͂��N������
			}
			if (m_sThumbLY[nCntPad] <= -MIN_GAMEPAD_LEFT_THUMB_Y)
			{// ���X�e�B�b�N�����ɓ|���ꂽ
				aGamePadState[nCntPad][XIJS_BUTTON_25] = 0x80;   // ���͂��N������
			}

			// �E�X�e�B�b�N
			if (m_sThumbRX[nCntPad] >= MIN_GAMEPAD_LEFT_THUMB_X)
			{// �E�X�e�B�b�N���E�ɓ|���ꂽ
				aGamePadState[nCntPad][XIJS_BUTTON_31] = 0x80;   // ���͂��N������
			}
			if (m_sThumbRX[nCntPad] <= -MIN_GAMEPAD_LEFT_THUMB_X)
			{// �E�X�e�B�b�N�����ɓ|���ꂽ
				aGamePadState[nCntPad][XIJS_BUTTON_30] = 0x80;   // ���͂��N������
			}
			if (m_sThumbRY[nCntPad] >= MIN_GAMEPAD_LEFT_THUMB_Y)
			{// �E�X�e�B�b�N����ɓ|���ꂽ
				aGamePadState[nCntPad][XIJS_BUTTON_28] = 0x80;   // ���͂��N������
			}
			if (m_sThumbRY[nCntPad] <= -MIN_GAMEPAD_LEFT_THUMB_Y)
			{// �E�X�e�B�b�N�����ɓ|���ꂽ
				aGamePadState[nCntPad][XIJS_BUTTON_29] = 0x80;   // ���͂��N������
			}

			// �{�^���̏�Ԃ��i�[����
			for (int nCntButton = 0; nCntButton < XIJS_BUTTON_MAX; nCntButton++)
			{// �{�^���̐������J��Ԃ�
				m_aGamePadStateTrigger[nCntPad][nCntButton] = (m_aGamePadState[nCntPad][nCntButton] ^ aGamePadState[nCntPad][nCntButton]) & aGamePadState[nCntPad][nCntButton];   // �{�^���̓��͏��(�g���K�[���)�ۑ�
				m_aGamePadStateRelease[nCntPad][nCntButton] = (m_aGamePadState[nCntPad][nCntButton] ^ aGamePadState[nCntPad][nCntButton]) & m_aGamePadState[nCntPad][nCntButton]; // �{�^���̓��͏��(�����[�X���)�ۑ�
				if (aGamePadState[nCntPad][nCntButton] == 0x80)
				{// �{�^�������͂���Ă���
					m_aGamePadCounter[nCntPad][nCntButton]++;    // �J�E���^�[��i�߂�
					if (m_aGamePadCounter[nCntPad][nCntButton] >= REPEAT_FRAME)
					{// 20�t���[�����{�^����������Ă���
						if (m_aGamePadCounter[nCntPad][nCntButton] % REPEAT_TRIGGER == 0)
						{// 3�t���[������
							m_aGamePadStateRepeat[nCntPad][nCntButton] = 0x80;   // �{�^���̓��͏��(���s�[�g���)���N��
						}
						else
						{// ����ȊO�̃t���[��
							m_aGamePadStateRepeat[nCntPad][nCntButton] = 0;      // �{�^���̓��͏��(���s�[�g���)���ꎞ��~
						}
					}
				}
				else
				{// �Q�[���p�b�h�̃{�^�������͂���Ă��Ȃ�
					m_aGamePadCounter[nCntPad][nCntButton] = 0;        // �J�E���^�[��߂�
					m_aGamePadStateRepeat[nCntPad][nCntButton] = 0;    // �{�^���̓��͏��(���s�[�g���)���~
				}
				m_aGamePadState[nCntPad][nCntButton] = aGamePadState[nCntPad][nCntButton];  // �{�^���̓��͏��(�v���X���)�ۑ�
			}
		}
		else
		{// ��Ԏ擾�Ɏ��s����
			g_XInput[nCntPad].m_bConnected = false;  // �ڑ�����Ă��Ȃ���Ԃɂ���
		}
	}
}

//=============================================================================
// �L�[�{�[�h�̓��͏��(�v���X���)���擾
//=============================================================================
bool GetKeyboardPress(int nKey)
{
	return (g_aKeyState[nKey] & 0x80) ? true : false;
}
//=============================================================================
// �L�[�{�[�h�̓��͏��(�g���K�[���)���擾
//=============================================================================
bool GetKeyboardTrigger(int nKey)
{
	return (g_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}
//=============================================================================
// �L�[�{�[�h�̓��͏��(�����[�X���)���擾
//=============================================================================
bool GetKeyboardRelease(int nKey)
{
	return (g_aKeyStateRelease[nKey] & 0x80) ? true : false;
}
//=============================================================================
// �W���C�p�b�h�̓��͏��(�v���X���)���擾
//=============================================================================
bool GetJoyPadPress(int nButton)
{
	return (g_aJoyState[nButton] & 0x80) ? true : false;
}
//=============================================================================
// �W���C�p�b�h�̓��͏��(�g���K�[���)���擾
//=============================================================================
bool GetJoyPadTrigger(int nButton)
{
	return (g_aJoyStateTrigger[nButton] & 0x80) ? true : false;
}
//=============================================================================
// �W���C�p�b�h�̓��͏��(�����[�X���)���擾
//=============================================================================
bool GetJoyPadRelease(int nButton)
{
	return (g_aJoyStateRelease[nButton] & 0x80) ? true : false;
}



//=============================================================================
//    �����̐U���̃��[�^�[��ݒ肷��
//=============================================================================
void SetXInputLeftMotorSpeed(int nCntPad, WORD wLeftMotorSpeed)
{
	g_aVibrarion[nCntPad].wLeftMotorSpeed = wLeftMotorSpeed;
	XInputSetState(nCntPad, &g_aVibrarion[nCntPad]);
}

//=============================================================================
//    �E���̐U���̃��[�^�[��ݒ肷��
//=============================================================================
void SetXInputRightMotorSpeed(int nCntPad, WORD wRightMotorSpeed)
{
	g_aVibrarion[nCntPad].wRightMotorSpeed = wRightMotorSpeed;
	XInputSetState(nCntPad, &g_aVibrarion[nCntPad]);
}

//=============================================================================
//    �Q�[���p�b�h�̓��͏��(�v���X���)���擾
//=============================================================================
bool GetXInputPress(int nCntPad, XIJS_BUTTON Button)
{
	return (m_aGamePadState[nCntPad][Button] & 0x80) ? true : false;
}

//=============================================================================
//    �Q�[���p�b�h�̓��͏��(�g���K�[���)���擾
//=============================================================================
bool GetXInputTrigger(int nCntPad, XIJS_BUTTON Button)
{
	return (m_aGamePadStateTrigger[nCntPad][Button] & 0x80) ? true : false;
}

//=============================================================================
//    �Q�[���p�b�h�̓��͏��(�����[�X���)���擾
//=============================================================================
bool GetXInputRelease(int nCntPad, XIJS_BUTTON Button)
{
	return (m_aGamePadStateRelease[nCntPad][Button] & 0x80) ? true : false;
}

//=============================================================================
//    �Q�[���p�b�h�̓��͏��(���s�[�g���)���擾
//=============================================================================
bool GetXInputRepeat(int nCntPad, XIJS_BUTTON Button)
{
	return (m_aGamePadStateRepeat[nCntPad][Button] & 0x80) ? true : false;
}

//=============================================================================
//    LT�{�^���̏�Ԃ��擾
//=============================================================================
BYTE GetXInputLeftTrigger(int nCntPad)
{
	return m_bLeftTrigger[nCntPad];
}

//=============================================================================
//    RT�{�^���̏�Ԃ��擾
//=============================================================================
BYTE GetXInputRightTrigger(int nCntPad)
{
	return m_bRightTrigger[nCntPad];
}

//=============================================================================
//    ���X�e�B�b�N�̌������擾
//=============================================================================
float GetXInputLeftAxiz(int nCntPad)
{
	float axiz = atan2f((float)m_sThumbLX[nCntPad], (float)-m_sThumbLY[nCntPad]);
	return axiz;
}

//=============================================================================
//    �E�X�e�B�b�N�̌������擾
//=============================================================================
float GetXInputRightAxiz(int nCntPad)
{
	float axiz = atan2f((float)m_sThumbRX[nCntPad], (float)-m_sThumbRY[nCntPad]);
	return axiz;
}

//=============================================================================
//    ���X�e�B�b�N��X�����擾
//=============================================================================
SHORT GetXInputThumbLX(int nCntPad)
{
	return m_sThumbLX[nCntPad];
}

//=============================================================================
//    ���X�e�B�b�N��Y�����擾
//=============================================================================
SHORT GetXInputThumbLY(int nCntPad)
{
	return m_sThumbLY[nCntPad];
}

//=============================================================================
//    �E�X�e�B�b�N��X�����擾
//=============================================================================
SHORT GetXInputThumbRX(int nCntPad)
{
	return m_sThumbRX[nCntPad];
}

//=============================================================================
//    �E�X�e�B�b�N��Y�����擾
//=============================================================================
SHORT GetXInputThumbRY(int nCntPad)
{
	return m_sThumbRY[nCntPad];
}