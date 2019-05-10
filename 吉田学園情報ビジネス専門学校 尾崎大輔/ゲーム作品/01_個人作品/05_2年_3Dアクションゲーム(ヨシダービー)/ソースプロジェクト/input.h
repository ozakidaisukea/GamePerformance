//=============================================================================
//
// 入力処理 [input.h]
// Author : Ozaki
//
//=============================================================================
#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_DATA (256)

//*****************************************************************************
// クラス宣言
//*****************************************************************************
class CInput
{
public:
	CInput();
	virtual~CInput();

	virtual HRESULT Input(HINSTANCE hInstance, HWND hWnd);
	virtual void Uninit(void);

	// 純粋仮想関数
	virtual void Update(void) = 0;

protected:
	static LPDIRECTINPUT8 m_pInput;
	LPDIRECTINPUTDEVICE8 m_pDevice;
};

//*****************************************************************************
// 派生クラス宣言
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