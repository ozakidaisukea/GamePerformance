//=============================================================================
//
// �G�t�F�N�g�̏��� [effect.h]
// Author :  Meguro Mikiya
//
//=============================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "main.h"
//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;					// �ʒu
	D3DXVECTOR3 move;					// �ʒu
	D3DXCOLOR col;						// �F
	D3DXMATRIX	mtrxWorldEffect;		// ���[���h�}�g���b�N�X
	float fRadius;						// ���a(�傫��)
	float fHeght;						// ����
	float fWidth;						// ��
	float fTest;						// ��
	int nLife;							// �\������(����)
	bool bUse;							// �g�p���Ă��邩�ǂ���
} EFFECT;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);
void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col, float fRadius, int nLife);

#endif
