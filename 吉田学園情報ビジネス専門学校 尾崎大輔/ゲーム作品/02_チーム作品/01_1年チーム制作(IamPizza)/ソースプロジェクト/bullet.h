//=============================================================================
//
// �ǂ̏��� [bullet.h]
// Author :  Meguro Mikiya
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"
//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef enum
{
	BULLETTYPE_PLAYER = 0,	//�v���C���[���
	BULLETTYPE_ENEMY,		//�G�l�~�[���
	BULLETTYPE_BOSS,		//�{�X���
	BULLETTYPE_MAX			//��Ԃ̑���
}BULLETTYPE;

typedef struct
{
	D3DXVECTOR3 pos;					// �ʒu
	D3DXVECTOR3 move;					// �ړ���
	D3DXVECTOR3 posold;					//�O��̈ʒu
	D3DXCOLOR col;						// �F
	D3DXMATRIX	mtrxWorldBullet;		// ���[���h�}�g���b�N�X
	float fRadius;						// ���a(�傫��)
	int nIdxShadow;						// �e�̃C���f�b�N�X
	float fHeght;						// ����
	float fWidth;						// ��
	BULLETTYPE type;					// �e�̎��
	int nLife;							// ����
	bool bUse;							// �g�p���Ă��邩�ǂ���
	bool bShadowUse;					// �g�p���Ă��邩�ǂ���
	D3DXVECTOR3 VtxMin, VtxMax;			//�v���C���[�̍ŏ��l�A�ő�l

} BULLET;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fHeght, float fWidth);

#endif
