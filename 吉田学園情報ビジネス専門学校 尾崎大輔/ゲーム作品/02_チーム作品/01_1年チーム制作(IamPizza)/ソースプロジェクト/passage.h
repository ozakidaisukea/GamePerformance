//=============================================================================
//
// �ʍs�l���� [passage.h]
// Author : SHUN YOKOMICHI
//
//=============================================================================
#ifndef _PASSAGE_H_
#define _PASSAGE_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define PASSAGE_NAME000		 "data\\MODEL\\Passage\\Passage001.x"	//MODEL�̃t�@�C����
							//"data\\MODEL\\Bill\\pokkuruzou.x"
#define MAX_PASSAGE			(128)							//���f���z�u�̍ő吔
#define MAX_PASSAGE_TYPE	(1)								//���f����ނ̍ő吔

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 VtxMinEnemy, VtxMaxEnemy;	// ���f���̍ŏ��l�A�ő�l
} VTXPASSAGE;
typedef struct
{
	DWORD nNumMat = 0;						// �}�e���A�����̐�
	D3DXVECTOR3 pos;						// �ʒu
	D3DXVECTOR3 move;						// �ړ�
	D3DXVECTOR3 rot;						// ����(����)
	D3DXVECTOR3 rotDest;					// ����(�ړI)
	D3DXMATRIX	mtxWorld;					// ���[���h�}�g���b�N�X
	float fShadow;							// �e�̑傫��
	float fSpeed;							// �ړ����x
	float fDestAngle;						//�ʍs�l�̊p�x
	int nActiontime;						// �s������
	int nIdxShadow;							// �e�̃C���f�b�N�X
	int nType;								// ���f���̎��
	int nCntTime;							// �ړ����郂�f���̎���
	int nPattan;							// �s��( 0 : ���ړ� / 1 : �c�s��)
	bool bUse;								// �g�p���Ă��邩
	bool bChange;							// �s���̕ω�
	D3DXVECTOR3 VtxMinEnemy, VtxMaxEnemy;	// ���f���̍ŏ��l�A�ő�l
	float fLength;
} PASSAGE;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitPassage(void);
void UninitPassage(void);
void UpdatePassage(void);
void DrawPassage(void);
PASSAGE *GetPassage(void);
bool CollisionPassage(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 VtxMax, D3DXVECTOR3 VtxMin);
void SetPassage(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType, int nPattan, int nActiontime, float fSpeed, bool bChange);
#endif