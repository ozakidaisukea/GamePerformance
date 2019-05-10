//=============================================================================
//
// �ԏ��� [car.h]
// Author : SHUN YOKOMICHI
//
//=============================================================================
#ifndef _CAR_H_
#define _CAR_H_

#include "main.h"
#include "polygon.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define CAR_NAME000		"data\\MODEL\\��\\anbirance.x"		//MODEL�̃t�@�C����
#define CAR_NAME001		"data\\MODEL\\��\\car000.x"			//MODEL�̃t�@�C����
#define CAR_NAME002		"data\\MODEL\\��\\car001.x"			//MODEL�̃t�@�C����
#define CAR_NAME003		"data\\MODEL\\��\\car002.x"			//MODEL�̃t�@�C����  // �c��MODEL

#define CAR_NAME004		"data\\MODEL\\��\\car003.x"			//MODEL�̃t�@�C����
#define CAR_NAME005		"data\\MODEL\\��\\car004.x"			//MODEL�̃t�@�C����
#define CAR_NAME006		"data\\MODEL\\��\\car005.x"			//MODEL�̃t�@�C����
#define CAR_NAME007		"data\\MODEL\\��\\car006.x"			//MODEL�̃t�@�C����  // ����MODEL

#define MAX_CAR			(246)								//���f���z�u�̍ő吔
#define MAX_CAR_TYPE	(8)									//���f����ނ̍ő吔


//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 VtxMinEnemy, VtxMaxEnemy;	// ���f���̍ŏ��l�A�ő�l
} VTXCAR;
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
} CAR;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitCar(void);
void UninitCar(void);
void UpdateCar(void);
void DrawCar(void);
CAR *GetCar(void);
bool CollisionCar(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 VtxMax, D3DXVECTOR3 VtxMin);
void SetCar(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType, int nPattan, int nActiontime, float fSpeed, bool bChange);
#endif