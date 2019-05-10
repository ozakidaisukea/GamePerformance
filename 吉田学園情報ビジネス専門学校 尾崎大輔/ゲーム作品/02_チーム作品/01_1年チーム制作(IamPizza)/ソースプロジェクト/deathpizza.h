//=============================================================================
//
// �s�U���S���̏��� [deathpizza.h]
// Author :  Meguro Mikiya
//
//=============================================================================
#ifndef _DEATHPIZZA_H_
#define _DEATHPIZZA_H_

#include "main.h"
//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;					// �ʒu
	D3DXVECTOR3 move;					// �ʒu
	D3DXCOLOR col;						// �F
	D3DXMATRIX	mtrxWorldDeathPizza;	// ���[���h�}�g���b�N�X
	float fRadius;						// ���a(�傫��)
	float fHeght;						// ����
	float fWidth;						// ��
	int nLife;							// �\������(����)
	bool bUse;							// �g�p���Ă��邩�ǂ���
} DEATHPIZZA;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitDeathPizza(void);
void UninitDeathPizza(void);
void UpdateDeathPizza(void);
void DrawDeathPizza(void);
void SetDeathPizza(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fRadius, int nLife);

#endif
