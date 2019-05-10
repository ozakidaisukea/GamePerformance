//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : Ozaki
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*************************************
// �T�E���h�t�@�C��
//*************************************
typedef enum
{
	SOUND_LABEL_BGMTITLE = 0,		// BGMTITLE
	SOUND_LABEL_BGMTUTORIAL,			// BGMTUTORIAL
	SOUND_LABEL_BGMGAME,			// BGMGAME
	SOUND_LABEL_BGMRESULT,			// BGMRESULT
	SOUND_LABEL_SE_DAMAGE,			// �_���[�W��
	SOUND_LABEL_SE_WEAKPUNCH,		// ��p���`
	SOUND_LABEL_SE_STORONGPUNCH,	// ���p���`
	SOUND_LABEL_SE_DOWN,			// �|��鉹
	SOUND_LABEL_SE_LANDING,			// ���n
	SOUND_LABEL_SE_JUMP,			// ���n
	SOUND_LABEL_SE_MISS,			// �U������
	//SOUND_LABEL_SE_1P_ATTACK,		// 1P�U��
	//SOUND_LABEL_SE_1P_DAMAGE,		// 1P�_���[�W
	//SOUND_LABEL_SE_1P_DEATH,		// 1P���S
	//SOUND_LABEL_SE_1P_ULTIMATE,		// 1P�K�E�Z
	//SOUND_LABEL_SE_2P_ATTACK,		// 2P�U��
	//SOUND_LABEL_SE_2P_DAMAGE,		// 2P�_���[�W
	//SOUND_LABEL_SE_2P_DEATH,		// 2P���S
	//SOUND_LABEL_SE_2P_ULTIMATE,		// 2P�K�E�Z
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
