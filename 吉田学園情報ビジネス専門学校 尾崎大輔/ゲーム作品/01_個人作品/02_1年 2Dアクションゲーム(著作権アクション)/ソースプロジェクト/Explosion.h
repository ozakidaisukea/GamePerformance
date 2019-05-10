//=============================================================================
//
// �e���� [explosion.h]
// Author : ozaki
//
//=============================================================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include "main.h"

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;		//���݂̈ʒu
	D3DXVECTOR3 posold;		//�O��̈ʒu
	D3DXVECTOR3 move;		//�ړ���
	D3DXCOLOR col;			//�F					
	float        fwidth;	//��
	float       fheigth;	//�c
	int nCounterAnim;
	int nPatternAnim;
	bool bUse;				//�g�p���Ă��邩
	int nLife;				//����
}Explosion;	

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitExplosion(void);
void UninitExplosion(void);
void UpdateExplosion(void);
void DrawExplosion(void);
void SetExplosion(D3DXVECTOR3 pos, D3DXCOLOR col, int nLife);
Explosion *GetExplosion(void);
#endif
