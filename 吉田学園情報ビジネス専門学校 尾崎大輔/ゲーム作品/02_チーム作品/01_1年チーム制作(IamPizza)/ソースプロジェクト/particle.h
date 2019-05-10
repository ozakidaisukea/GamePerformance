//=============================================================================
//
// �p�[�e�B�N���̏��� [particle.h]
// Author :  Meguro Mikiya
//
//=============================================================================
#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "main.h"
//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef enum
{
	PARTICLE_TYPE_PIZZA = 0,			// 
	PARTICLE_TYPE_PIZZA_DEATH,			// �s�U�@��
	PARTICLE_TYPE_GOAL,					// �S�[��
	PARTICLE_TYPE_MAX,
}PARTICLE_TYPE;

typedef struct
{
	D3DXVECTOR3 pos;					// �ʒu
	D3DXVECTOR3 move;					// �ړ���
	D3DXVECTOR3 rot;					// ����
	D3DXCOLOR col;						// �F
	D3DXMATRIX	mtrxWorldParticle;		// ���[���h�}�g���b�N�X
	float fRadius;						// ���a(�傫��)
	float fHeght;						// ����
	float fWidth;						// ��
	int nLife;							// �\������(����)
	bool bUse;							// �g�p���Ă��邩�ǂ���
	PARTICLE_TYPE ParticleType;			// �p�[�e�B�N���̎��
	int nTexType;						// �p�[�e�B�N���̃e�N�X�`���̎��
}PARTICLE;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitParticle(void);
void UninitParticle(void);
void UpdateParticle(void);
void DrawParticle(void);
void SetParticle(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, D3DXCOLOR col, float fRadius, int nLife , PARTICLE_TYPE type);

#endif
