//=============================================================================
//
// ���͏��� [joypad.h]
// Author : Ozaki
//
//=============================================================================
#ifndef _JOYPAD_H_
#define _JOYPAD_H_

#include "main.h"
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_DATA (256)
#define PAD_DATA (32)
#define DI_JOY_I_INPUT (1000)

//*****************************************************************************
// �N���X�錾
//*****************************************************************************

//*****************************************************************************
// �h���N���X�錾
//*****************************************************************************
class CInputjoypad : public CInput
{
public:

	CInputjoypad();
	~CInputjoypad();

	typedef enum
	{
		DIJS_BOTTON_X = 0,
		DIJS_BOTTON_A,
		DIJS_BOTTON_B,
		DIJS_BOTTON_Y,
		DIJS_BOTTON_LB,
		DIJS_BOTTON_RB,
		DIJS_BOTTON_LT,
		DIJS_BOTTON_RT,
		DIJS_BOTTON_BACK,
		DIJS_BOTTON_START,
		DIJS_BOTTON_11,
		DIJS_BOTTON_12,
		DIJS_BOTTON_13,
		DIJS_BOTTON_14,
		DIJS_BOTTON_15,
		DIJS_BOTTON_16,
		DIJS_BOTTON_17,
		DIJS_BOTTON_18,
		DIJS_BOTTON_19,
		DIJS_BOTTON_20,
		DIJS_STICK_LEFT_UP,			// ����
		DIJS_STICK_LEFT_DOWN,		// ����
		DIJS_STICK_LEFT_LEFT,		// ����
		DIJS_STICK_LEFT_RIGTH,		// ���E
		DIJS_STICK_RIGTH_UP,		// �E��
		DIJS_STICK_RIGTH_DOWN,		//
		DIJS_STICK_RIGTH_LEFT,
		DIJS_STICK_RIGTH_RIGTH,
		DIJS_STICK_POV_UP,
		DIJS_STICK_POV_DOWN,
		DIJS_STICK_POV_LEFT,
		DIJS_STICK_POV_RIGTH,
		DIJS_BOTTON_MAX,

	}DIJS_BOTTON;


	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	bool GetPress(int nKey);
	bool GetTrigger(int nKey);

	float GetLefAxiz(void);
	float GetRightAxiz(void);
	float GetRadiom(void);

private:

	BYTE m_aKeyState[MAX_DATA];
	BYTE m_aKeyStateTrigger[MAX_DATA];

	float m_LefAxizX;
	float m_LefAxizY;
	float m_RightAxizX;
	float m_RightAxizY;
	float m_Radiom;

};
#endif