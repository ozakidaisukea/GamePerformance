//=============================================================================
//
// �G�̏��� [enemy.h]
// Author : Meguro Mikiya
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"
#include "polygon.h"
#include "player.h"
#include "model.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define ENEMY_NAME000		 "data\\MODEL\\��\\arisuta.x"		//�e�N�X�`���̃t�@�C����
#define ENEMY_NAME001		 "data\\MODEL\\��\\arisuta.x"				//�e�N�X�`���̃t�@�C����
#define ENEMY_NAME002		 "data\\MODEL\\��\\arisuta.x"		//�e�N�X�`���̃t�@�C����

#define MOVE_ENEMY			(0.2f)							//�G�̈ړ���
#define MOVE_SIN_COS_TOP	(0.75f)							//�|���S���ړ���
#define MOVE_SIN_COS_BOT	(0.25f)							//�|���S���ړ���
#define FIELD_MAX_SIZE		(FIELD_SIZE - 10)
#define MAX_ENEMY			(300)							//�G�̔z�u�̍ő吔
#define MAX_ENEMY_TYPE		(3)								//�G�̎�ނ̍ő吔
//*****************************************************************************
// �\���̒�`
//*****************************************************************************
//typedef struct
//{
//	D3DXVECTOR3 VtxMinEnemy, VtxMaxEnemy;	//���f���̍ŏ��l�A�ő�l
//} VTX;
typedef struct
{
	DWORD nNumMat = 0;						//�}�e���A�����̐�
	D3DXVECTOR3 pos;						//�ʒu
	D3DXVECTOR3 posold;						//�O��̈ʒu
	D3DXVECTOR3 move;						//�ړ���
	D3DXVECTOR3 rot;						//����
	float fDestAngle;						//�v���C���[�̊p�x
	float fDiffAngle;						//����
	D3DXMATRIX	mtxWorld;					//���[���h�}�g���b�N�X
	float fShadow;							//�e�̑傫��
	int nIdxShadow;							//�e�̃C���f�b�N�X
	int nType;								//���f���̎��
	bool bUse;								//�g�p���Ă��邩
	D3DXVECTOR3 VtxMinEnemy, VtxMaxEnemy;	//���f���̍ŏ��l�A�ő�l
} ENEMY;

//typedef enum
//{
//	COLLISION_PLAYER = 0,	//�v���C���[
//	COLLISION_BULLET,		//�e
//} COLLISIONENEMYTYPE;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
ENEMY *GetEnemy(void);
bool CollisionEnemy(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 VtxMax, D3DXVECTOR3 VtxMin);
void SetEnemy(D3DXVECTOR3 pos,int nType);
#endif