//=============================================================================
//
// ���͏��� [input.h]
// Author :	Shun Yokomichi
//
//=============================================================================
#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);
void UninitKeyboard(void);
void UpdateKeyboard(void);
bool GetKeyboardPress(int nKey);
bool GetKeyboardTrigger(int nKey);
bool GetKeyboardRelease(int nKey);
HRESULT InitJoycon(HINSTANCE hInstance, HWND hWnd);											// �W���C�R������������
void UpdateJoycon(void);																	// �W���C�R���X�V����
BOOL CALLBACK EnumJoystickCallback(const DIDEVICEINSTANCE *pdidInstance, VOID *pContext);	// �R�[���o�b�N(�f�o�C�X�쐬)�ɕK�v�Ȑ錾
BOOL CALLBACK EnumAxesCallback(const DIDEVICEOBJECTINSTANCE *pdidoi, VOID *pContext);		// �������߂�
bool GetJoyControllerPress(int nKey);														// �}�E�X�v���X
bool GetJoyControllerTrigger(int nKey);														// �}�E�X�g���K�[
DIJOYSTATE2 GetStick(void);

#endif