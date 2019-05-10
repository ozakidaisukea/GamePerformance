//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : Ozaki Daisuke
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*************************************
// �T�E���h�t�@�C��
//*************************************
typedef enum //���x���Ɛ��ƕ��т𑵂���
{
	SOUND_LABEL_BGM_TITLE = 0,	// BGM�^�C�g��
	SOUND_LABEL_BGM_TUTORIAL,	// BGM�`���[�g���A��
	SOUND_LABEL_BGM_GAME,		// BGM�Q�[��
	SOUND_LABEL_BGM_CLEAR,		// BGM�N���A
	SOUND_LABEL_BGM_GAMEOVER,	// BGM�Q�[���I�[�o�[
	SOUND_LABEL_BGM_RANKING,	// BGM�����L���O
	SOUND_LABEL_BGM_PIZZA,		// �s�U���
	SOUND_LABEL_BGM_SINZOU,		// �S����
	SOUND_LABEL_BGM_SINDENZU,	// �S�d�}��
	SOUND_LABEL_SE_GOAL,		// �S�[��
	SOUND_LABEL_SE_DECIDE,		// ���艹
	SOUND_LABEL_SE_PAUSE,		// �|�[�Y��
	SOUND_LABEL_SE_SELECT,		// �Z���N�g��
	SOUND_LABEL_SE_CANCEL,		// �L�����Z�����P
	SOUND_LABEL_SE_SAKEBI1,		// ���ѐ��P
	SOUND_LABEL_SE_SAKEBI2,		// ���ѐ��Q
	SOUND_LABEL_SE_SAKEBI3,		// ���ѐ��R
	SOUND_LABEL_SE_ENZIN,		// �G���W����
	SOUND_LABEL_SE_BIKU,		// �o�C�N��
	SOUND_LABEL_SE_TABERU,		// �H�ׂ鉹
	SOUND_LABEL_SE_NIMIKOMI,	// ���ݍ��݉�
	SOUND_LABEL_SE_DORO,		// �D��
	SOUND_LABEL_SE_KABE,		// �ǐڐG��
	SOUND_LABEL_SE_WIND,		// ����
	SOUND_LABEL_SE_YUKIARASHI,	// �ᗒ��
	SOUND_LABEL_SE_CHIME1,		// �`���C���P
	SOUND_LABEL_SE_CHIME2,		// �`���C���Q
	SOUND_LABEL_SE_CHIME3,		// �`���C���R
	SOUND_LABEL_SE_CHIME4,		// �`���C���S
	SOUND_LABEL_SE_KLAXON1,		// �N���N�V�����P
	SOUND_LABEL_SE_KLAXON2,		// �N���N�V�����Q
	SOUND_LABEL_SE_GEPPU,		// ������
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
