//=============================================================================
//
// �|���S������ [Explosion.h]
// Author : Ozaki
//
//=============================================================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define		MAX_EXPLOSION	(1)

//*****************************************************************************
// �\����
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;				// �ʒu
	D3DXVECTOR3 rot;				// ����
	D3DXVECTOR3 movve;				// ����
	D3DXMATRIX  mtxWorld;			// ���[���h�}�g���b�N�X
	int			nCounterAnim;		//�A�j���[�V�����J�E���^�[
	int			nPatternAnim;		//�A�j���[�V�����p�^�[��
	int			nLife;				// �̗�
	bool		bUse;				// �g�p���Ă邩���ĂȂ���

}Explosion;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitExplosion(void);
void UninitExplosion(void);
void UpdateExplosion(void);
void DrawExplosion(void);
void SetExplosion(D3DXVECTOR3 posExplosion, D3DXVECTOR3 rotExplosion,D3DXCOLOR col);
Explosion *GetExplosion(void);
#endif
