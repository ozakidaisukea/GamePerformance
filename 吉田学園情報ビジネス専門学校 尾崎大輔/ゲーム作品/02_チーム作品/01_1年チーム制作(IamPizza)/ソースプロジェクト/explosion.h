//=============================================================================
//
// �����̏��� [Explosion.h]
// Author :  Meguro Mikiya
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
	D3DXVECTOR3 pos;					// �ʒu
	D3DXCOLOR col;						// �F
	D3DXMATRIX	mtrxWorldExplosion;		// ���[���h�}�g���b�N�X
	float fRadius;						// ���a(�傫��)
	float fHeght;						// ����
	float fWidth;						// ��
	float fTest;						// ��
	int nCounterAnim;					// �A�j���[�V�����J�E���^�[
	int nPatternAnim;					// �A�j���[�V�����p�^�[��No��������
	float fAlpha;						// �����x
	bool bUse;							// �g�p���Ă��邩�ǂ���
} EXPLOSION;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitExplosion(void);
void UninitExplosion(void);
void UpdateExplosion(void);
void DrawExplosion(void);
void SetExplosion(D3DXVECTOR3 pos, D3DXCOLOR col, float fHeght, float fWidth);

#endif
