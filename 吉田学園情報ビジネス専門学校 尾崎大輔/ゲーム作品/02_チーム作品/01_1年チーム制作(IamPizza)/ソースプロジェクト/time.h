//=============================================================================
//
// �X�R�A���� [time.h]
// Author : Mikiya Meguro
//
//=============================================================================
#ifndef _TIME_H_
#define _TIME_H_

#include "main.h"


typedef struct
{
	int				nTime;				// �^�C��
	D3DXVECTOR3		TimePos;			//�^�C�}�[�̈ʒu
	int				nTimeCounter;		//�^�C���J�E���^�[
	bool			bTimerStop;			//�^�C�}�[�X�g�b�v

}TIME;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitTime(void);
void UninitTime(void);
void UpdateTime(void);
void DrawTime(void);
TIME *GetTime(void);

#endif
