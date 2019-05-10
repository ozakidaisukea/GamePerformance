//=============================================================================
//
// �S�[������ [goal.h]
// Author : Meguro Mikiya
//
//=============================================================================
#ifndef _GOAL_H_
#define _GOAL_H_

#include "main.h"
#include "polygon.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define GOAL_NAME000		 "data\\MODEL\\goal.x"	//�e�N�X�`���̃t�@�C����
#define FIELD_MAX_SIZE		(FIELD_SIZE - 10)
#define MAX_GOAL			(1)
//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef enum
{
	GOALSTATE_NORMAL = 0,		// �ʏ���
	GOALSTATE_CHECKPOINT,
	GOALSTATE_GOAL,
	GOALSTATE_MAX,			// ��Ԃ̑���
}GOALSTATE;

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
	D3DXVECTOR3 VtxMinGoal, VtxMaxGoal;		//���f���̍ŏ��l�A�ő�l
	int nCntGoal;
	int nGoalPattern;
	int nCounterState;
	GOALSTATE state;
	float fLength;
} GOAL;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitGoal(void);
void UninitGoal(void);
void UpdateGoal(void);
void DrawGoal(void);
GOAL *GetGoal(void);
bool CollisionGoal(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 VtxMax, D3DXVECTOR3 VtxMin/*, MODEL **pGoal*/);
void SetGoal(D3DXVECTOR3 pos,int nType);
#endif