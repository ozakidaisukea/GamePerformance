//=============================================================================
//
// ���͏��� [input.h]
// Author : Ozaki
//
//=============================================================================
#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_DATA (256)

//*****************************************************************************
// �N���X�錾
//*****************************************************************************
class CInput
{
public:
	CInput();
	virtual~CInput();

	virtual HRESULT Input(HINSTANCE hInstance, HWND hWnd);
	virtual void Uninit(void);

	// �������z�֐�
	virtual void Update(void) = 0;

protected:
	static LPDIRECTINPUT8 m_pInput;
	LPDIRECTINPUTDEVICE8 m_pDevice;
};

//*****************************************************************************
// �h���N���X�錾
//*****************************************************************************
class CInputKeyboard : public CInput
{
public:
	CInputKeyboard();
	~CInputKeyboard();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	bool GetPress(int nKey);
	bool GetTrigger(int nKey);


private:
	BYTE m_aKeyState[MAX_DATA];
	BYTE m_aKeyStateTrigger[MAX_DATA];
};
#endif