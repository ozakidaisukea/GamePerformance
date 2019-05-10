//=============================================================================
//
// �����L���O���� [ranking.h]
// Author : Mikiya Meguro
//
//=============================================================================
#ifndef _RANKING_H_
#define _RANKING_H_

#include "main.h"

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	//int nCounterAnim;	//�A�j���[�V�����J�E���^�[
	//int nPatternAnim;	//�A�j���[�V�����p�^�[��No��������	
	D3DXCOLOR col;		//�J���[
}Ranking;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitRanking(void);
void UninitRanking(void);
void UpdateRanking(void);
void DrawRanking(void);
void SetRanking(int aRanking);
#endif
