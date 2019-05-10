//=============================================================================
//
// ���[�h�Z���N�g�̏��� [modeselect.h]
// Author : Niwa Hodaka
//
//=============================================================================
#ifndef _MODESELECT_H_
#define _MODESELECT_H_

#include "main.h"

//*************************************
// ���ڂ̏��
//*************************************
typedef enum
{
	MODESTATE_NONE = 0,   // �I������Ă��Ȃ����
	MODESTATE_SELECT,     // �I������Ă�����
	MODESTATE_MAX
}MODESTATE;

typedef enum
{
	MODESTART_GAME,     // �Q�[���J��
	MODESTART_TUTORIAL, // �`���[�g���A���J��
	MODESTART_RANKING,  // �����L���O�J��
	MODESTART_TITLE,    // �^�C�g���J��
	MODESTART_MAX
}MODESTART;

//*************************************
// ���ڂ̍\����
//*************************************
typedef struct
{
	D3DXCOLOR col;    // �F
	MODESTATE state;  // �I������Ă��邩�ǂ���
}MODESELECT;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitModeSelect(void);
void UninitModeSelect(void);
void UpdateModeSelect(void);
void DrawModeSelect(void);

#endif