//=============================================================================
//
// �^�C�}�[���� [timer.h]
// Author : Jukiya Hayakawa
//
//=============================================================================
#ifndef _TIMER_H_
#define _TIMER_H_

#include "main.h"

//**********************************
// �^�C�}�[�̏��
//**********************************
typedef enum
{
	TIMERSTATE_COUNT = 0,
	TIMERSTATE_NONE_COUNT,
	TIMERSTATE_MAX
}TIMERSTATE;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitTimer(void);
void UninitTimer(void);
void UpdateTimer(void);
void DrawTimer(void);
void StopTimerState(void);
#endif