//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : AKIRA TANAKA
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
	SOUND_LABEL_TITLE = 0,		// BGM0
	SOUND_LABEL_TUTORIAL,		// BGM1
	SOUND_LABEL_GAME,			// BGM2
	SOUND_LABEL_CLEAR,			// BGM3
	SOUND_LABEL_GAMEOVER,		// BGM4
	SOUND_LABEL_RUNKING,		// BGM5
	SOUND_LABEL_SE_SHOT,		// �e���ˉ�
	//SOUND_LABEL_SE_HIT000,		// �q�b�g��0
	//SOUND_LABEL_SE_HIT001,		// �q�b�g��1
	SOUND_LABEL_SE_EXPLOSION,	// ������
	SOUND_LABEL_SE_USHI,		// ���艹1
	SOUND_LABEL_SE_ENTER,		// ���艹2
	SOUND_LABEL_SE_SAKEBI,		// ���m���ѐ�
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
