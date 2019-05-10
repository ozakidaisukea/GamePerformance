//=============================================================================
//
// �ǂ̏��� [wall.h]
// Author :  Meguro Mikiya
//
//=============================================================================
#ifndef _WALL_H_
#define _WALL_H_

#include "main.h"
//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;					// �ʒu
	D3DXVECTOR3 rot;					// ����
	//D3DXCOLOR col;					// �F
	D3DXMATRIX	mtrxWorld;				// ���[���h�}�g���b�N�X
	float fRadius;						// ���a(�傫��)
	float fHeght;						// ����
	float fWidth;						// ��
	bool bUse;							// �g�p���Ă��邩�ǂ���
} WALL;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitWall(void);
void UninitWall(void);
void UpdateWall(void);
void DrawWall(void);
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fHeght, float fWidth);

#endif
