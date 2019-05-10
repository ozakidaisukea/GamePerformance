//=============================================================================
//
// inputx���� [inputx.h]
// Author : komatsu keisuke
//
//=============================================================================
#ifndef _INPUTX_H_
#define _INPUTX_H_

#include "main.h"

//=============================================================================
// �W���C�p�b�h�̍\����
//=============================================================================
typedef enum
{
	INPUT_JOYSTATE_NOTPUSH = 0,
	INPUT_JOYSTATE_PUSH,
	INPUT_JOYSTATE_NONE,
}InputJoyState;

typedef struct
{
	InputJoyState nJoypadState;		//�W���C�p�b�h�̏��
	bool bConnectionJoypad;			//�W���C�p�b�h�̐ڑ����
}JoyState;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void InitJoyPad(void);
void UninitJoyPad(void);
JoyState GetJoystate(void);
#endif