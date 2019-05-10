//=============================================================================
//
// ���͏��� [input.h]
// Author : Niwa Hodaka
//
//=============================================================================
#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"

//*****************************************************************************
// �\���̂̒�`
//*****************************************************************************
typedef enum
{
	DIJS_BUTTON_0 = 0,  // X�{�^��
	DIJS_BUTTON_1,      // A�{�^��
	DIJS_BUTTON_2,      // B�{�^��
	DIJS_BUTTON_3,      // Y�{�^��
	DIJS_BUTTON_4,      // LB�{�^��
	DIJS_BUTTON_5,      // RB�{�^��
	DIJS_BUTTON_6,      // LT�{�^��
	DIJS_BUTTON_7,      // RT�{�^��
	DIJS_BUTTON_8,      // BACK�{�^��
	DIJS_BUTTON_9,      // START�{�^��
	DIJS_BUTTON_10,     // ���A�i���O�X�e�B�b�N���������
	DIJS_BUTTON_11,     // ���A�i���O�X�e�B�b�N����������
	DIJS_BUTTON_12,     // ���A�i���O�X�e�B�b�N�E��������
	DIJS_BUTTON_13,     // ���A�i���O�X�e�B�b�N����������
	DIJS_BUTTON_14,     // �E�A�i���O�X�e�B�b�N���������
	DIJS_BUTTON_15,     // �E�A�i���O�X�e�B�b�N����������
	DIJS_BUTTON_16,     // �E�A�i���O�X�e�B�b�N�E��������
	DIJS_BUTTON_17,     // �E�A�i���O�X�e�B�b�N����������
	DIJS_BUTTON_18,     // �\���L�[���������
	DIJS_BUTTON_19,     // �\���L�[����������
	DIJS_BUTTON_20,     // �\���L�[�E��������
	DIJS_BUTTON_21,     // �\���L�[����������
	// �ȉ����蓖�ĂȂ�
	DIJS_BUTTON_22,
	DIJS_BUTTON_23,
	DIJS_BUTTON_24,
	DIJS_BUTTON_25,
	DIJS_BUTTON_26,
	DIJS_BUTTON_27,
	DIJS_BUTTON_28,
	DIJS_BUTTON_29,
	DIJS_BUTTON_30,
	DIJS_BUTTON_31,
	DIJS_BUTTON_MAX
}PADBUTTON;

typedef enum
{
	XIJS_BUTTON_0,     // �\���L�[�����
	XIJS_BUTTON_1,     // �\���L�[������
	XIJS_BUTTON_2,     // �\���L�[������
	XIJS_BUTTON_3,     // �\���L�[�E����
	XIJS_BUTTON_4,     // START�{�^��
	XIJS_BUTTON_5,     // BACK�{�^��
	XIJS_BUTTON_6,     // ���X�e�B�b�N�������ݓ���
	XIJS_BUTTON_7,     // �E�X�e�B�b�N�������ݓ���
	XIJS_BUTTON_8,     // LB�{�^��
	XIJS_BUTTON_9,     // RB�{�^��
	XIJS_BUTTON_10,    // A�{�^��
	XIJS_BUTTON_11,    // B�{�^��
	XIJS_BUTTON_12,    // X�{�^��
	XIJS_BUTTON_13,    // Y�{�^��
	XIJS_BUTTON_14,    // LT�{�^��
	XIJS_BUTTON_15,    // RT�{�^��
	XIJS_BUTTON_16,
	XIJS_BUTTON_17,
	XIJS_BUTTON_18,
	XIJS_BUTTON_19,
	XIJS_BUTTON_20,
	XIJS_BUTTON_21,
	XIJS_BUTTON_22,
	XIJS_BUTTON_23,
	XIJS_BUTTON_24,    // ���X�e�B�b�N�����
	XIJS_BUTTON_25,    // ���X�e�B�b�N������
	XIJS_BUTTON_26,    // ���X�e�B�b�N������
	XIJS_BUTTON_27,    // ���X�e�B�b�N�E����
	XIJS_BUTTON_28,    // �E�X�e�B�b�N�����
	XIJS_BUTTON_29,    // �E�X�e�B�b�N������
	XIJS_BUTTON_30,    // �E�X�e�B�b�N������
	XIJS_BUTTON_31,    // �E�X�e�B�b�N�E����
	XIJS_BUTTON_MAX,
}XIJS_BUTTON;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitInput(HINSTANCE hInstance, HWND hWnd);
void UninitInput(void);
void UpdateInput(void);
bool GetKeyboardPress(int nKey);
bool GetKeyboardTrigger(int nKey);
bool GetKeyboardRelease(int nKey);
bool GetJoyPadPress(int nButton);
bool GetJoyPadTrigger(int nButton);
bool GetJoyPadRelease(int nButton);

bool GetXInputPress(int nCntPad, XIJS_BUTTON nButton);
bool GetXInputTrigger(int nCntPad, XIJS_BUTTON nButton);
bool GetXInputRelease(int nCntPad, XIJS_BUTTON nButton);
bool GetXInputRepeat(int nCntPad, XIJS_BUTTON nButton);
void SetXInputLeftMotorSpeed(int nCntPad, WORD wLeftMotorSpeed);
void SetXInputRightMotorSpeed(int nCntPad, WORD wRightMotorSpeed);

BYTE GetXInputLeftTrigger(int nCntPad);
BYTE GetXInputRightTrigger(int nCntPad);
float GetXInputLeftAxiz(int nCntPad);
float GetXInputRightAxiz(int nCntPad);
SHORT GetXInputThumbLX(int nCntPad);
SHORT GetXInputThumbLY(int nCntPad);
SHORT GetXInputThumbRX(int nCntPad);
SHORT GetXInputThumbRY(int nCntPad);

#endif