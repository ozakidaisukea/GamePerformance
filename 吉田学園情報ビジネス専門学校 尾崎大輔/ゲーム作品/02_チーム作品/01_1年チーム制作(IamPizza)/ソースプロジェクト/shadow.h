//=============================================================================
//
// �|���S������ [shadow.h]
// Author :  Meguro Mikiya
//
//=============================================================================
#ifndef _SHADOW_H_
#define _SHADOW_H_

#include "main.h"
//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;					// �ʒu
	D3DXVECTOR3 rot;					// ����
	D3DXCOLOR col;						// �F
	D3DXMATRIX	mtrxWorld;				// ���[���h�}�g���b�N�X
	float fRadius;						// ���a(�傫��)
	bool bUse;							// �g�p���Ă��邩�ǂ���
	float fLength;
} SHADOW;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitShadow(void);
void UninitShadow(void);
void UpdateShadow(void);
void DrawShadow(void);
int SetShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius);
void SetPositionShadow(int nIdxShadow, D3DXVECTOR3 pos, float fRadius);
void DeleteShadow(int nIdxShadow);

#endif
