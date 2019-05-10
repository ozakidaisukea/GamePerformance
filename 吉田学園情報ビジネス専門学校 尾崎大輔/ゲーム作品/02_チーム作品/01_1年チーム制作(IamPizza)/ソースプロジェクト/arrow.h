//=============================================================================
//
// ��󏈗� [arrow.h]
// Author : Meguro Mikiya
//
//=============================================================================
#ifndef _ARROW_H_
#define _ARROW_H_

#include "main.h"
#include "polygon.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define ARROW_NAME000		 "data\\MODEL\\arrow.x"		//�e�N�X�`���̃t�@�C����
#define MOVE_ARROW			(2.0f)							//���ړ���
#define MOVE_SIN_COS_TOP	(0.75f)							//�|���S���ړ���
#define MOVE_SIN_COS_BOT	(0.25f)							//�|���S���ړ���
#define FIELD_MAX_SIZE		(FIELD_SIZE - 10)
#define MAX_ARROW			(1)
//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	DWORD nNumMat = 0;						//�}�e���A�����̐�
	D3DXVECTOR3 pos;						//�ʒu
	D3DXVECTOR3 rot;						//����
	D3DXMATRIX	mtxWorld;					//���[���h�}�g���b�N�X
	float fShadow;							//�e�̑傫��
	int nIdxShadow;							//�e�̃C���f�b�N�X
	D3DXVECTOR3 DestAngle;					//
	D3DXVECTOR3 DiffAngle;
	D3DXVECTOR3 rotDest;
	int nType;								//���̎��
	bool bUse;								//�g�p���Ă��邩
	D3DXVECTOR3 VtxMinArrow, VtxMaxArrow;	//���̍ŏ��l�A�ő�l
} ARROW;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitArrow(void);
void UninitArrow(void);
void UpdateArrow(void);
void DrawArrow(void);
ARROW *GetArrow(void);

#endif