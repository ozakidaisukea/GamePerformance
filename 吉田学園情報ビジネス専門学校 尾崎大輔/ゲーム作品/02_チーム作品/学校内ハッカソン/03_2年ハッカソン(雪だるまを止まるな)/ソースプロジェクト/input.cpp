//=============================================================================
//
// ���͏������� [input.cpp]
// Author : Jukiya Hayakawa
//
//=============================================================================
#include "input.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECTINPUT8 CInput::m_pInput = NULL;

//*****************************************************************************
// ���͏���
//*****************************************************************************
//=============================================================================
// ���͏����̃R���X�g���N�^
//=============================================================================
CInput::CInput()
{
	m_pDevice = NULL;
}

//=============================================================================
// ���͏����̃f�X�g���N�^
//=============================================================================
CInput::~CInput()
{

}

//=============================================================================
// ���͏����̏���������
//=============================================================================
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (m_pInput == NULL)
	{
		// DirectInput�I�u�W�F�N�g�̐���
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL)))
		{
			return E_FAIL;
		}
	}

	return S_OK;
}

//=============================================================================
// ���͏����̏I������
//=============================================================================
void CInput::Uninit(void)
{
	// ���̓f�o�C�X(�L�[�{�[�h)�̊J��
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire();	// �L�[�{�[�h�ւ̃A�N�Z�X�������
		m_pDevice->Release();
		m_pDevice = NULL;
	}

	// DirectInput�I�u�W�F�N�g�̊J��
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}
}

//*****************************************************************************
// �L�[�{�[�h�̓��͏���
//*****************************************************************************
//=============================================================================
// �L�[�{�[�h�̃R���X�g���N�^
//=============================================================================
CInputKeyboard::CInputKeyboard()
{
	//����͐�΂ɋ֎~�I�I�I
	//m_aKeyState[NUM_KEY_MAX] = {};
	//m_aKeyStateTrigger[NUM_KEY_MAX] = {};

	for (int nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
	{
		m_aKeyState[nCntKey] = 0;
		m_aKeyStateTrigger[nCntKey] = 0;
	}
}

//=============================================================================
// �L�[�{�[�h�̃f�X�g���N�^
//=============================================================================
CInputKeyboard::~CInputKeyboard()
{

}

//=============================================================================
// �L�[�{�[�h�̏���������
//=============================================================================
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);

	// ���̓f�o�C�X(�L�[�{�[�h)�̐���
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	// �������[�h��ݒ�
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��(���͐���J�n)
	m_pDevice->Acquire();

	return S_OK;
}

//=============================================================================
// �L�[�{�[�h�̏I������
//=============================================================================
void CInputKeyboard::Uninit(void)
{
	//���͏����̏I������
	CInput::Uninit();
}

//=============================================================================
// �L�[�{�[�h�̍X�V����
//=============================================================================
void CInputKeyboard::Update(void)
{
	BYTE aKeyState[NUM_KEY_MAX];	// �L�[�{�[�h�̓��͏��
	int nCntKey;

	// ���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];
			m_aKeyState[nCntKey] = aKeyState[nCntKey];	// �L�[�{�[�h���͏��ۑ�
		}
	}
	else
	{
		m_pDevice->Acquire();	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��
	}
}

//=============================================================================
// �L�[�{�[�h�̓��͏��(�v���X���)���擾
//=============================================================================
bool CInputKeyboard::GetPress(int nKey)
{
	return(m_aKeyState[nKey] & 0x80) ? true : false;
}

//=============================================================================
// �L�[�{�[�h�̓��͏��(�g���K�[���)���擾
//=============================================================================
bool CInputKeyboard::GetTrigger(int nKey)
{
	return(m_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//*****************************************************************************
// �W���C�p�b�h�̓��͏���
//*****************************************************************************
//=============================================================================
// �W���C�p�b�h�̃R���X�g���N�^
//=============================================================================
CInputJoypad::CInputJoypad()
{
	//����͐�΂ɋ֎~�I�I�I
	//m_aKeyState[NUM_KEY_MAX] = {};
	//m_aKeyStateTrigger[NUM_KEY_MAX] = {};

	for (int nCntKey = 0; nCntKey < 32; nCntKey++)
	{
		m_aButtonState[nCntKey] = 0;
		m_aButtonStateTrigger[nCntKey] = 0;
	}
}

//=============================================================================
// �W���C�p�b�h�̃f�X�g���N�^
//=============================================================================
CInputJoypad::~CInputJoypad()
{

}

//=============================================================================
// �W���C�p�b�h�̏���������
//=============================================================================
HRESULT CInputJoypad::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);

	// ���̓f�o�C�X(�L�[�{�[�h)�̐���
	if (FAILED(m_pInput->CreateDevice(GUID_Joystick, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIJoystick)))
	{
		return E_FAIL;
	}

	// �������[�h��ݒ�
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	if (m_pDevice != NULL)
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
		m_pDevice->SetProperty(DIPROP_RANGE, &diprg.diph);
		diprg.diph.dwObj = DIJOFS_Y;
		m_pDevice->SetProperty(DIPROP_RANGE, &diprg.diph);
		diprg.diph.dwObj = DIJOFS_Z;
		m_pDevice->SetProperty(DIPROP_RANGE, &diprg.diph);

		// �E�A�i���O�X�e�B�b�N
		diprg.diph.dwObj = DIJOFS_RX;
		m_pDevice->SetProperty(DIPROP_RANGE, &diprg.diph);
		diprg.diph.dwObj = DIJOFS_RY;
		m_pDevice->SetProperty(DIPROP_RANGE, &diprg.diph);
		diprg.diph.dwObj = DIJOFS_RZ;
		m_pDevice->SetProperty(DIPROP_RANGE, &diprg.diph);

		// ?
		//diprg.diph.dwObj = DIJOFS_SLIDER(0);
		//g_pDevJoypad->SetProperty(DIPROP_RANGE, &diprg.diph);

		// �\���L�[(���0�x�Ƃ����v���Ɋp�x * 100)
		diprg.diph.dwObj = DIJOFS_POV(0);
		m_pDevice->SetProperty(DIPROP_RANGE, &diprg.diph);

		// �W���C�X�e�B�b�N�ւ̃A�N�Z�X�����l��(���͐���J�n)
		m_pDevice->Acquire();
	}
	return S_OK;
}

//=============================================================================
// �W���C�p�b�h�̏I������
//=============================================================================
void CInputJoypad::Uninit(void)
{
	//���͏����̏I������
	CInput::Uninit();
}

//=============================================================================
// �W���C�p�b�h�̍X�V����
//=============================================================================
void CInputJoypad::Update(void)
{
	DIJOYSTATE aJoypadState;	// �W���C�p�b�h�̓��͏��
	int nCntJoypad;

	if (m_pDevice != NULL)
	{
		m_pDevice->Poll();
		// ���̓f�o�C�X����f�[�^���擾
		if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(DIJOYSTATE), &aJoypadState)))
		{
			m_LeftAxizX = (float)aJoypadState.lX;
			m_LeftAxizY = (float)aJoypadState.lY;
			m_RightAxizX = (float)aJoypadState.lZ;
			m_RightAxizY = (float)aJoypadState.lRz;

			if (m_LeftAxizY <= -100)
			{//���X�e�B�b�N����ɉ����ꂽ
				aJoypadState.rgbButtons[DIJS_BUTTON_LSTICK_UP] = 0x80;
			}
			if (m_LeftAxizY >= 100)
			{//���X�e�B�b�N�����ɉ����ꂽ
				aJoypadState.rgbButtons[DIJS_BUTTON_LSTICK_DOWN] = 0x80;
			}
			if (m_LeftAxizX >= 100)
			{//���X�e�B�b�N���E�ɉ����ꂽ
				aJoypadState.rgbButtons[DIJS_BUTTON_LSTICK_RIGHT] = 0x80;
			}
			if (m_LeftAxizX <= -100)
			{//���X�e�B�b�N�����ɉ����ꂽ
				aJoypadState.rgbButtons[DIJS_BUTTON_LSTICK_LEFT] = 0x80;
			}

			if (m_RightAxizY <= -100)
			{//�E�X�e�B�b�N����ɉ����ꂽ
				aJoypadState.rgbButtons[DIJS_BUTTON_RSTICK_UP] = 0x80;
			}
			if (m_RightAxizY >= 100)
			{//�E�X�e�B�b�N�����ɉ����ꂽ
				aJoypadState.rgbButtons[DIJS_BUTTON_RSTICK_DOWN] = 0x80;
			}
			if (m_RightAxizX <= -100)
			{//�E�X�e�B�b�N���E�ɉ����ꂽ
				aJoypadState.rgbButtons[DIJS_BUTTON_RSTICK_RIGHT] = 0x80;
			}
			if (m_RightAxizX >= 100)
			{//�E�X�e�B�b�N�����ɉ����ꂽ
				aJoypadState.rgbButtons[DIJS_BUTTON_RSTICK_LEFT] = 0x80;
			}
			if (aJoypadState.rgdwPOV[0] == 0)
			{//�\���L�[����ɉ����ꂽ
				aJoypadState.rgbButtons[DIJS_BUTTON_UP] = 0x80;
				m_Radian = D3DXToRadian(aJoypadState.rgdwPOV[0]);
			}
			if (aJoypadState.rgdwPOV[0] == 4500)
			{//�\���L�[���E��ɉ����ꂽ
				aJoypadState.rgbButtons[DIJS_BUTTON_RIGHT] = 0x80;
				m_Radian = D3DXToRadian(aJoypadState.rgdwPOV[0]);
			}
			if (aJoypadState.rgdwPOV[0] == 9000)
			{//�\���L�[���E�ɉ����ꂽ
				aJoypadState.rgbButtons[DIJS_BUTTON_RIGHT] = 0x80;
				m_Radian = D3DXToRadian(aJoypadState.rgdwPOV[0]);
			}
			if (aJoypadState.rgdwPOV[0] == 13500)
			{//�\���L�[���E���ɉ����ꂽ
				aJoypadState.rgbButtons[DIJS_BUTTON_RIGHT] = 0x80;
				m_Radian = D3DXToRadian(aJoypadState.rgdwPOV[0]);
			}
			if (aJoypadState.rgdwPOV[0] == 18000)
			{//�\���L�[�����ɉ����ꂽ
				aJoypadState.rgbButtons[DIJS_BUTTON_DOWN] = 0x80;
				m_Radian = D3DXToRadian(aJoypadState.rgdwPOV[0]);
			}
			if (aJoypadState.rgdwPOV[0] == 22500)
			{//�\���L�[���E���ɉ����ꂽ
				aJoypadState.rgbButtons[DIJS_BUTTON_DOWN] = 0x80;
				m_Radian = D3DXToRadian(aJoypadState.rgdwPOV[0]);
			}
			if (aJoypadState.rgdwPOV[0] == 27000)
			{//�\���L�[�����ɉ����ꂽ
				aJoypadState.rgbButtons[DIJS_BUTTON_LEFT] = 0x80;
				m_Radian = D3DXToRadian(aJoypadState.rgdwPOV[0]);
			}
			if (aJoypadState.rgdwPOV[0] == 31500)
			{//�\���L�[������ɉ����ꂽ
				aJoypadState.rgbButtons[DIJS_BUTTON_LEFT] = 0x80;
				m_Radian = D3DXToRadian(aJoypadState.rgdwPOV[0]);
			}

			for (nCntJoypad = 0; nCntJoypad < 32; nCntJoypad++)
			{
				m_aButtonStateTrigger[nCntJoypad] = (m_aButtonState[nCntJoypad] ^ aJoypadState.rgbButtons[nCntJoypad]) &aJoypadState.rgbButtons[nCntJoypad];
				m_aButtonState[nCntJoypad] = aJoypadState.rgbButtons[nCntJoypad];	// �L�[�{�[�h���͏��ۑ�
			}

		}
		else
		{
			m_pDevice->Acquire();	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��
		}
	}
}

//=============================================================================
// �W���C�p�b�h�̓��͏��(�v���X���)���擾
//=============================================================================
bool CInputJoypad::GetPress(DIJS_BUTTON button)
{
	return(m_aButtonState[button] & 0x80) ? true : false;
}

//=============================================================================
// �W���C�p�b�h�̓��͏��(�g���K�[���)���擾
//=============================================================================
bool CInputJoypad::GetTrigger(DIJS_BUTTON button)
{
	return(m_aButtonStateTrigger[button] & 0x80) ? true : false;
}

//=============================================================================
// ���X�e�B�b�N�̎擾
//=============================================================================
float CInputJoypad::GetLeftAxiz(void)
{
	float Axiz = atan2f(m_LeftAxizX, m_LeftAxizY);
	return Axiz;
}

//=============================================================================
// �E�X�e�B�b�N�̎擾
//=============================================================================
float CInputJoypad::GetRightAxiz(void)
{
	float RightAxiz = atan2f(m_RightAxizX, m_RightAxizY);
	return RightAxiz;
}

//=============================================================================
// �p�x�̎擾
//=============================================================================
float CInputJoypad::GetRadian(void)
{
	return m_Radian / 100;
}