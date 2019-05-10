//=============================================================================
//
// �|���S������ [bullet.h]
// Author : Ozaki
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"
#include "model.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define		MAX_BULLET	(256)

//*****************************************************************************
// �\����
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;							// �ʒu
	D3DXVECTOR3 posold;							// �ʒu

	D3DXVECTOR3 move;							// ����
	D3DXMATRIX mtxWorld;						// ���[���h�}�g���b�N�X
	int			nLife;							// ����
	int			nIdxShadow;						// �e
	bool		bUse;							// �g�p���Ă邩���ĂȂ���
	MODEL		*pModel;

}BULLET;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 posbullet, D3DXVECTOR3 rotbullet,D3DXVECTOR3 movebullet);
#endif
