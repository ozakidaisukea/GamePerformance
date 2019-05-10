//=============================================================================
//
// ���f������ [model.h]
// Author : Meguro Mikiya
//
//=============================================================================
#ifndef _MODEL_H_
#define _MODEL_H_

#include "main.h"
#include "polygon.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MODEL_NAME000		 "data\\MODEL\\Bill\\supermarket.x"		//�e�N�X�`���̃t�@�C����
#define MODEL_NAME001		 "data\\MODEL\\Bill\\house000.x"			//�e�N�X�`���̃t�@�C����
#define MODEL_NAME002		 "data\\MODEL\\Bill\\pizzaya.x"			//�e�N�X�`���̃t�@�C����
#define MODEL_NAME003		 "data\\MODEL\\Bill\\cafe.x"				//�e�N�X�`���̃t�@�C����
#define MODEL_NAME004		 "data\\MODEL\\Bill\\cafe.x"				//�e�N�X�`���̃t�@�C����


//#define MOVE_MODEL			(2.0f)						//���f���ړ���
//#define MOVE_SIN_COS_TOP	(0.75f)							//�|���S���ړ���
//#define MOVE_SIN_COS_BOT	(0.25f)							//�|���S���ړ���
#define FIELD_MAX_SIZE		(FIELD_SIZE - 10)
#define MAX_MODEL			(300)							//���f���z�u�̍ő吔
#define MAX_MODEL_TYPE		(5)								//���f����ނ̍ő吔

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 VtxMinModel, VtxMaxModel;	//���f���̍ŏ��l�A�ő�l
	D3DXVECTOR3 VtxMinEnemy, VtxMaxEnemy;	//���f���̍ŏ��l�A�ő�l
	D3DXVECTOR3 VtxMinTexModel, VtxMaxTexModel;	//���f���̍ŏ��l�A�ő�l
} VTX;
typedef struct
{
	DWORD nNumMat = 0;						//�}�e���A�����̐�
	D3DXVECTOR3 pos;						//�ʒu
	D3DXVECTOR3 rot;						//����
	D3DXMATRIX	mtxWorld;					//���[���h�}�g���b�N�X
	float fShadow;							//�e�̑傫��
	int nIdxShadow;							//�e�̃C���f�b�N�X
	int nType;								//���f���̎��
	bool bUse;								//�g�p���Ă��邩
	D3DXVECTOR3 VtxMinModel, VtxMaxModel;	//���f���̍ŏ��l�A�ő�l
} MODEL;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitModel(void);
void UninitModel(void);
void UpdateModel(void);
void DrawModel(void);
MODEL *GetModel(void);
bool CollisionModel(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 VtxMax, D3DXVECTOR3 VtxMin/*, MODEL **pModel*/);
void SetModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType);
#endif