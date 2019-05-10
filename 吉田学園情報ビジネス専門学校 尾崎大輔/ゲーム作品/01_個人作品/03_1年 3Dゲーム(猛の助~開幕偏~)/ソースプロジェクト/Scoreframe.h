//=============================================================================
//
// �X�R�A���� [scoreframe.h]
// Author : Ozaki
//
//=============================================================================
#ifndef _SCOREFRAME_H_
#define _SCOREFRAME_H_

#include "main.h"


typedef struct
{
	D3DXVECTOR3 pos;		//���݂̈ʒu
	D3DXVECTOR3 posold;		//�O��̈ʒu
	D3DXVECTOR3 move;		//�ړ���
	D3DXVECTOR3 col;		//�F
	float fwidth;			//����
	float fheigth;			//�c��
	int nCounterAnim;		//�A�j���[�V�����J�E���^�[
	int nPatternAnim;		//�A�j���[�V�������p�^�[����
	bool bUse;				//�g�p���Ă邩�ǂ���
}ScoreFrame;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitScoreFrame(void);
void UninitScoreFrame(void);
void UpdateScoreFrame(void);
void DrawScoreFrame(void);

#endif
