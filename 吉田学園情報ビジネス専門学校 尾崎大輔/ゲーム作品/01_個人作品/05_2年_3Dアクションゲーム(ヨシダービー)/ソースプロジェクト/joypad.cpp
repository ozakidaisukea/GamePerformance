//=============================================================================
//
// 入力処理 [joypad.cpp]
// Author : Ozaki
//
//=============================================================================
#include "joypad.h"
#include "manager.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CInputjoypad::CInputjoypad()
{
	for (int nCnt = 0; nCnt < MAX_DATA; nCnt++)
	{
		// キー情報のクリア
		m_aKeyState[nCnt] = 0;
	}

}

//=============================================================================
// デストラクタ
//=============================================================================
CInputjoypad::~CInputjoypad()
{

}

//=============================================================================
// キーボードの初期化
//=============================================================================
HRESULT CInputjoypad::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Input(hInstance, hWnd);

	// 入力デバイス(キーボード)の生成
	if (FAILED(m_pInput->CreateDevice(GUID_Joystick, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}
	// データフォーマットを設定
	if (FAILED((m_pDevice->SetDataFormat(&c_dfDIJoystick))))
	{
		return E_FAIL;
	}

	// 協調モードを設定
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	// 軸の設定
	if (m_pDevice != NULL)
	{// 生成できた
		DIPROPRANGE diprg;

		// 軸の値の範囲を設定
		diprg.diph.dwSize = sizeof(diprg);
		diprg.diph.dwHeaderSize = sizeof(diprg.diph);
		diprg.diph.dwHow = DIPH_BYOFFSET;
		diprg.lMin = -DI_JOY_I_INPUT;
		diprg.lMax = DI_JOY_I_INPUT;

		// 軸の設定
		// 左アナログスティック
		diprg.diph.dwObj = DIJOFS_X;
		m_pDevice->SetProperty(DIPROP_RANGE, &diprg.diph);
		diprg.diph.dwObj = DIJOFS_Y;
		m_pDevice->SetProperty(DIPROP_RANGE, &diprg.diph);
		diprg.diph.dwObj = DIJOFS_Z;
		m_pDevice->SetProperty(DIPROP_RANGE, &diprg.diph);

		// 右アナログスティック
		diprg.diph.dwObj = DIJOFS_RX;
		m_pDevice->SetProperty(DIPROP_RANGE, &diprg.diph);
		diprg.diph.dwObj = DIJOFS_RY;
		m_pDevice->SetProperty(DIPROP_RANGE, &diprg.diph);
		diprg.diph.dwObj = DIJOFS_RZ;
		m_pDevice->SetProperty(DIPROP_RANGE, &diprg.diph);

		// ?
		//diprg.diph.dwObj = DIJOFS_SLIDER(0);
		//g_pDevJoypad->SetProperty(DIPROP_RANGE, &diprg.diph);

		// 十字キー(上を0度とし時計回りに角度 * 100)
		diprg.diph.dwObj = DIJOFS_POV(0);
		m_pDevice->SetProperty(DIPROP_RANGE, &diprg.diph);

		// ジョイスティックへのアクセス権を獲得(入力制御開始)
		m_pDevice->Acquire();

	}
	return S_OK;
}

//=============================================================================
// キーボードの終了処理
//=============================================================================
void CInputjoypad::Uninit(void)
{
	CInput::Uninit();
}

//=============================================================================
// キーボードの更新処理
//=============================================================================
void CInputjoypad::Update(void)
{
	DIJOYSTATE dijs;

	int nCntKey;

	if (m_pDevice != NULL)
	{
		m_pDevice->Poll();

		// 入力デバイスからデータを取得
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

			// 上
			if ((dijs.rgdwPOV[0] / 100) == 0)
			{
				dijs.rgbButtons[DIJS_STICK_POV_UP] = 0x80;
				m_Radiom = D3DXToRadian(dijs.rgdwPOV[0]);
			}

			// 右上
			if ((dijs.rgdwPOV[0] / 100) == 45)
			{
				dijs.rgbButtons[DIJS_STICK_POV_UP] = 0x80;
				dijs.rgbButtons[DIJS_STICK_POV_RIGTH] = 0x80;
				m_Radiom = D3DXToRadian(dijs.rgdwPOV[0]);
			}

			// 右
			if ((dijs.rgdwPOV[0] / 100) == 90)
			{
				dijs.rgbButtons[DIJS_STICK_POV_RIGTH] = 0x80;
				m_Radiom = D3DXToRadian(dijs.rgdwPOV[0]);
			}

			// 右下
			if ((dijs.rgdwPOV[0] / 100) == 135)
			{
				dijs.rgbButtons[DIJS_STICK_POV_RIGTH] = 0x80;
				dijs.rgbButtons[DIJS_STICK_POV_DOWN] = 0x80;
				m_Radiom = D3DXToRadian(dijs.rgdwPOV[0]);

			}

			// 下
			if ((dijs.rgdwPOV[0] / 100) == 180)
			{
				dijs.rgbButtons[DIJS_STICK_POV_DOWN] = 0x80;

				m_Radiom = D3DXToRadian(dijs.rgdwPOV[0]);
			}

			// 左下
			if ((dijs.rgdwPOV[0] / 100) == 225)
			{
				dijs.rgbButtons[DIJS_STICK_POV_DOWN] = 0x80;
				dijs.rgbButtons[DIJS_STICK_POV_LEFT] = 0x80;

				m_Radiom = D3DXToRadian(dijs.rgdwPOV[0]);
			}

			// 左
			if ((dijs.rgdwPOV[0] / 100) == 270)
			{
				dijs.rgbButtons[DIJS_STICK_POV_LEFT] = 0x80;

				m_Radiom = D3DXToRadian(dijs.rgdwPOV[0]);
			}

			// 左上

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
// キーボードの入力情報(プレス情報)を取得
//=============================================================================
bool CInputjoypad::GetPress(int nKey)
{
	return(m_aKeyState[nKey] & 0x80) ? true : false;
}

//=============================================================================
// キーボードの入力情報(トリガー情報)を取得
//=============================================================================
bool CInputjoypad::GetTrigger(int nKey)
{
	return(m_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//=============================================================================
// パッドの入力情報(トリガー情報)を取得
//=============================================================================
float CInputjoypad::GetLefAxiz(void)
{
	float Axiz = atan2f(m_LefAxizX, m_LefAxizY);

	return Axiz;
}

//=============================================================================
// パッドの入力情報(トリガー情報)を取得
//=============================================================================
float CInputjoypad::GetRightAxiz(void)
{
	float Axiz = atan2f(m_RightAxizX, m_RightAxizY);

	return Axiz;
}

//=============================================================================
// パッドの入力情報(トリガー情報)を取得
//=============================================================================
float CInputjoypad::GetRadiom(void)
{
	float Radion = m_Radiom / 100;

	return Radion;
}
