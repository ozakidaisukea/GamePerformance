//=============================================================================
//
// �z�[������ [home.h]
// Author : Meguro Mikiya
//
//=============================================================================
#ifndef _HOME_H_
#define _HOME_H_

#include "main.h"
#include "polygon.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define HOME_NAME000		 "data\\MODEL\\goal.x"	//�e�N�X�`���̃t�@�C����
#define FIELD_MAX_SIZE		(FIELD_SIZE - 10)
#define MAX_HOME			(1)
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
	int nType;								//���f���̎��
	bool bUse;								//�g�p���Ă��邩
	D3DXVECTOR3 VtxMinHome, VtxMaxHome;	//���f���̍ŏ��l�A�ő�l
} HOME;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitHome(void);
void UninitHome(void);
void UpdateHome(void);
void DrawHome(void);
HOME *GetHome(void);
bool CollisionHome(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 VtxMax, D3DXVECTOR3 VtxMin/*, MODEL **pHome*/);
void SetHome(D3DXVECTOR3 pos,int nType);
#endif