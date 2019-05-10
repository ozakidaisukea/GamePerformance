//=============================================================================
//
// �ǂ̏��� [billboard.h]
// Author :  Meguro Mikiya
//
//=============================================================================
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

#include "main.h"
//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;					// �ʒu
	//D3DXCOLOR col;					// �F
	D3DXMATRIX	mtrxWorldBillboard;		// ���[���h�}�g���b�N�X
	float fRadius;						// ���a(�傫��)
	float fHeght;						// ����
	float fWidth;						// ��
	int nIdxShadow;						// �e�̃C���f�b�N�X
	bool bUse;							// �g�p���Ă��邩�ǂ���
} BILLBOARD;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitBillboard(void);
void UninitBillboard(void);
void UpdateBillboard(void);
void DrawBillboard(void);
void SetBillboard(D3DXVECTOR3 pos, float fHeght, float fWidth);

#endif
