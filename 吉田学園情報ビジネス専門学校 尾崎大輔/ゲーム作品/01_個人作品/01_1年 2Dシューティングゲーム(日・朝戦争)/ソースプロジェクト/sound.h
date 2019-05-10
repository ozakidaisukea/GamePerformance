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
	SOUND_LABEL_BGM000 = 0,		// BGM0
	SOUND_LABEL_BGM001,			// BGM1
	SOUND_LABEL_BGM002,			// BGM2
	SOUND_LABEL_BGM003,			// BGM3
	SOUND_LABEL_BGM004,			// BGM4
	SOUND_LABEL_SE_HUMAN1,		// �l�ԉ�1 [�n�b]
	SOUND_LABEL_SE_HUMAN2,		// �l�ԉ�2 [�Ȃ�ł�˂�]
	SOUND_LABEL_SE_HUMAN3,		// �l�ԉ�3 [�΂�]
	SOUND_LABEL_SE_SHOT,		// �e���ˉ�
	SOUND_LABEL_SE_HIT000,		// �q�b�g��0
	SOUND_LABEL_SE_HIT001,		// �q�b�g��1
	SOUND_LABEL_SE_EXPLOSION,	// ������
	SOUND_LABEL_SE_DECIDE,		// ���艹
	SOUND_LABEL_SE_ABE,			// ���{�W�O
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
