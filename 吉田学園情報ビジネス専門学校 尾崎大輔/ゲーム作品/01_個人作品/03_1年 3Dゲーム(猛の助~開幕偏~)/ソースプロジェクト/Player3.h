//=============================================================================
//
// ���f������ [Player2.h]
// Author : Ozaki
//
//=============================================================================
#ifndef _SAKU_H_
#define _SAKU_H_

#include "main.h"
#include "model.h"

//*****************************************************************************
// ���f���̍\����
//*****************************************************************************
typedef enum
{
	PLAYER3_NORMAL = 0,
}PLAYER3;

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
}Model3;

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
	bool		bDisp;				// �g�p���Ă邩�ǂ���
	bool		bJunp;				// �W�����v���Ă邩�ǂ���
	PLAYER3		state;
	Model3		aModel[2];
	MODEL		*pModel;

}Player3;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitPlayer3(void);
void UninitPlayer3(void);
void UpdatePlayer3(void);
void DrawPlayer3(void);
Player3 *GetPlayer3(void);

#endif
