//=============================================================================
//
// ���͏��� [joypad.cpp]
// Author : Ozaki
//
//=============================================================================
#include "joypad.h"
#include "manager.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CInputjoypad::CInputjoypad()
{
	for (int nCnt = 0; nCnt < MAX_DATA; nCnt++)
	{
		// �L�[���̃N���A
		m_aKeyState[nCnt] = 0;
	}

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CInputjoypad::~CInputjoypad()
{

}

//=============================================================================
// �L�[�{�[�h�̏�����
//=============================================================================
HRESULT CInputjoypad::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Input(hInstance, hWnd);

	// ���̓f�o�C�X(�L�[�{�[�h)�̐���
	if (FAILED(m_pInput->CreateDevice(GUID_Joystick, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}
	// �f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED((m_pDevice->SetDataFormat(&c_dfDIJoystick))))
	{
		return E_FAIL;
	}

	// �������[�h��ݒ�
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	// ���̐ݒ�
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
// �L�[�{�[�h�̏I������
//=============================================================================
void CInputjoypad::Uninit(void)
{
	CInput::Uninit();
}

//=============================================================================
// �L�[�{�[�h�̍X�V����
//=============================================================================
void CInputjoypad::Update(void)
{
	DIJOYSTATE dijs;

	int nCntKey;

	if (m_pDevice != NULL)
	{
		m_pDevice->Poll();

		// ���̓f�o�C�X����f�[�^���擾
		if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(DIJOYSTATE), &dijs)))
		{
			m_LefAxizX = (float)dijs.lX;
			m_LefAxizY = (float)dijs.lY;
			m_RightAxizX = (float)dijs.lZ;
			m_RightAxizY = (float)dijs.lRz;

			if (m_LefAxizY <= -100)
			{
				dijs.rgbButtons[DIJS_STICK_LEFT_UP] = 0x80;
			}

			if (m_LefAxizY >= 100)
			{
				dijs.rgbButtons[DIJS_STICK_LEFT_DOWN] = 0x80;
			}
			if (m_LefAxizX <= -100)
			{
				dijs.rgbButtons[DIJS_STICK_LEFT_LEFT] = 0x80;
			}

			if (m_LefAxizX >= 100)
			{
				dijs.rgbButtons[DIJS_STICK_LEFT_RIGTH] = 0x80;
			}

			//=====================================================================
			//
			//=====================================================================

			// ��
			if ((dijs.rgdwPOV[0] / 100) == 0)
			{
				dijs.rgbButtons[DIJS_STICK_POV_UP] = 0x80;
				m_Radiom = D3DXToRadian(dijs.rgdwPOV[0]);
			}

			// �E��
			if ((dijs.rgdwPOV[0] / 100) == 45)
			{
				dijs.rgbButtons[DIJS_STICK_POV_UP] = 0x80;
				dijs.rgbButtons[DIJS_STICK_POV_RIGTH] = 0x80;
				m_Radiom = D3DXToRadian(dijs.rgdwPOV[0]);
			}

			// �E
			if ((dijs.rgdwPOV[0] / 100) == 90)
			{
				dijs.rgbButtons[DIJS_STICK_POV_RIGTH] = 0x80;
				m_Radiom = D3DXToRadian(dijs.rgdwPOV[0]);
			}

			// �E��
			if ((dijs.rgdwPOV[0] / 100) == 135)
			{
				dijs.rgbButtons[DIJS_STICK_POV_RIGTH] = 0x80;
				dijs.rgbButtons[DIJS_STICK_POV_DOWN] = 0x80;
				m_Radiom = D3DXToRadian(dijs.rgdwPOV[0]);

			}

			// ��
			if ((dijs.rgdwPOV[0] / 100) == 180)
			{
				dijs.rgbButtons[DIJS_STICK_POV_DOWN] = 0x80;

				m_Radiom = D3DXToRadian(dijs.rgdwPOV[0]);
			}

			// ����
			if ((dijs.rgdwPOV[0] / 100) == 225)
			{
				dijs.rgbButtons[DIJS_STICK_POV_DOWN] = 0x80;
				dijs.rgbButtons[DIJS_STICK_POV_LEFT] = 0x80;

				m_Radiom = D3DXToRadian(dijs.rgdwPOV[0]);
			}

			// ��
			if ((dijs.rgdwPOV[0] / 100) == 270)
			{
				dijs.rgbButtons[DIJS_STICK_POV_LEFT] = 0x80;

				m_Radiom = D3DXToRadian(dijs.rgdwPOV[0]);
			}

			// ����

			if ((dijs.rgdwPOV[0] / 100) == 315)
			{
				dijs.rgbButtons[DIJS_STICK_POV_LEFT] = 0x80;
				dijs.rgbButtons[DIJS_STICK_POV_UP] = 0x80;

				m_Radiom = D3DXToRadian(dijs.rgdwPOV[0]);
			}

			for (nCntKey = 0; nCntKey < PAD_DATA; nCntKey++)
			{
				m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ dijs.rgbButtons[nCntKey]) & dijs.rgbButtons[nCntKey];
				m_aKeyState[nCntKey] = dijs.rgbButtons[nCntKey];
			}
		}
		else
		{
			m_pDevice->Acquire();
		}
	}
}

//=============================================================================
// �L�[�{�[�h�̓��͏��(�v���X���)���擾
//=============================================================================
bool CInputjoypad::GetPress(int nKey)
{
	return(m_aKeyState[nKey] & 0x80) ? true : false;
}

//=============================================================================
// �L�[�{�[�h�̓��͏��(�g���K�[���)���擾
//=============================================================================
bool CInputjoypad::GetTrigger(int nKey)
{
	return(m_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//=============================================================================
// �p�b�h�̓��͏��(�g���K�[���)���擾
//=============================================================================
float CInputjoypad::GetLefAxiz(void)
{
	float Axiz = atan2f(m_LefAxizX, m_LefAxizY);

	return Axiz;
}

//=============================================================================
// �p�b�h�̓��͏��(�g���K�[���)���擾
//=============================================================================
float CInputjoypad::GetRightAxiz(void)
{
	float Axiz = atan2f(m_RightAxizX, m_RightAxizY);

	return Axiz;
}

//=============================================================================
// �p�b�h�̓��͏��(�g���K�[���)���擾
//=============================================================================
float CInputjoypad::GetRadiom(void)
{
	float Radion = m_Radiom / 100;

	return Radion;
}
