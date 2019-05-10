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
	SOUND_LABEL_BGM005,			// BGM5  [�}���I]
	SOUND_LABEL_BGM006,			// BGM6  [�}���I�ҏW]
	SOUND_LABEL_BGM007,			// BGM7  [�}���I�����L���O]
	SOUND_LABEL_BGM008,			// BGM8  [�}���I�`���[�g���A��]
	SOUND_LABEL_BGM009,			// BGM9  [�}���I�^�C�g��]
	SOUND_LABEL_BGM0010,		// BGM10  [SIM_GUNSHOT]
	SOUND_LABEL_BGM0011,		// BGM11  [SIM_KILLINGME]
	SOUND_LABEL_BGM0012,		// BGM12  [SIM_BLHA]
	SOUND_LABEL_BGM0013,		// BGM13  [�ܒܒ�]
	SOUND_LABEL_BGM0014,		// BGM14  [���C�̂Ȃ��_�[�X�x�C�_�[]

	SOUND_LABEL_SE_MARIO_CLEAR,	// ���U���g  [�}���I�N���A]
	SOUND_LABEL_SE_MARIO_DETH,	// ���S�� [�}���I]
	SOUND_LABEL_SE_HUMAN1,		// �l�ԉ�1 [�n�b]
	SOUND_LABEL_SE_HUMAN2,		// �l�ԉ�2 [�Ȃ�ł�˂�]
	SOUND_LABEL_SE_HUMAN3,		// �l�ԉ�3 [�΂�]
	SOUND_LABEL_SE_SHOT,		// �e���ˉ�
	SOUND_LABRL_SE_COIN,		// �R�C��
	SOUND_LABRL_SE_ambulance,	// �~�}
	SOUND_LABRL_SE_junp,		// �W�����v
	SOUND_LABRL_SE_serect,		// �I��
	SOUND_LABRL_SE_nomu,		// ����
	SOUND_LABRL_SE_coughing,	// �Ȃ�
	SOUND_LABRL_SE_running,		// ����
	SOUND_LABRL_SE_heart,		// �S����
	SOUND_LABEL_SE_HIT000,		// �q�b�g��0
	SOUND_LABEL_SE_HIT001,		// �q�b�g��1
	SOUND_LABEL_SE_EXPLOSION,	// ������
	SOUND_LABEL_SE_DECIDE,		// ���艹
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

