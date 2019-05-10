//=============================================================================
//
// ���f������ [Player.h]
// Author : Ozaki
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
#include "model.h"

//*****************************************************************************
// ���f���̍\����
//*****************************************************************************
typedef enum
{
	PLAYER_NORMAL = 0,
}PLAYER;

//*****************************************************************************
// �\����
//*****************************************************************************
typedef struct
{
	LPD3DXMESH		pMesh;
	LPD3DXBUFFER	pBuffMat;
	DWORD			nNumMat;
	D3DXMATRIX		mtxWorld;
	D3DXVECTOR3		rot;
	D3DXVECTOR3 pos;				// ���݂̈ʒu
	int				nIdxModelParent;			// �e���f���̃C���f�b�N�X
}Model1;

typedef struct
{
	D3DXVECTOR3 pos;				// ���݂̈ʒu
	D3DXVECTOR3 posold;
	D3DXVECTOR3 move;				// �ړ���
	D3DXVECTOR3 posVDest;			// ���_
	D3DXVECTOR3 posRDest;			// ���ӓ_
	D3DXVECTOR3 posUDest;			// ������x�N�g
	D3DXVECTOR3 rot;				// ����
	D3DXMATRIX	mtxWorld;
	float       fwidth;				// ��
	float       fheigth;			// �c
	int			nCounterState;		// ��ԊǗ��J�E���^�[
	int			nLife;				// ����
	float		flength;			// ���� 
	bool		bUse;				// �g�p���Ă邩�ǂ���
	bool		bJunp;				// �W�����v���Ă邩�ǂ���
	PLAYER		state;
	Model1		aModel[2];
	D3DXVECTOR3 rotmove;
	MODEL		*pModel;
	D3DXVECTOR3 VtxMinModel, VtxMaxModel;	//���f���̍ŏ��l�A�ő�l

}Player;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
Player *GetPlayer(void);
bool CollisionPlayer(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 radius, MODEL **pPlayer);
#endif
