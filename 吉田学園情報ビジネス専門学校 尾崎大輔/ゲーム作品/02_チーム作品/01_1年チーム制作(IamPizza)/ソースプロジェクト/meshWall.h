//=============================================================================
//
// �|���S������ [meshWall.h]
// Author :  Meguro Mikiya
//
//=============================================================================
#ifndef _MESHWALL_H_
#define _MESHWALL_H_

#include "main.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MESHWALL_TEXTURENAME		 "data\\TEXTURE\\wall003.jpg"	//�e�N�X�`���̃t�@�C����
#define TEX_POS_X_INIT			(1.0f)								//�e�N�X�`�����WU�̏����ʒu
#define TEX_POS_Y_INIT			(1.0f)								//�e�N�X�`�����WV�̏����ʒu
#define TEX_LEFT				(0.0f)								//�e�N�X�`�����WU��
#define TEX_RIGHT				(1.0f)								//�e�N�X�`�����WU�E
#define TEX_TOP					(0.0f)								//�e�N�X�`�����WV��
#define TEX_BOT					(1.0f)								//�e�N�X�`�����WV��
#define X_POSSIZE				(50)								//X�̑傫��
#define Y_POSSIZE				(50)								//Z�̑傫��
#define X_WALLSIZE				(120)									//X�̕�
#define Y_WALLSIZE			 	(2)									//Z�̕�
#define MAX_MESHWALL			(4)									//���b�V���I�[���̍ő吔
//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;					//�ʒu
	D3DXVECTOR3 rot;					//����
	D3DXMATRIX	mtrxWorld;				//���[���h�}�g���b�N�X
	
	float fHeght;						// ����
	float fWidth;						// ��
	int nVtxIndex = 0;
	int nIdxIndex = 0;
	float fPos_X = 0;
	float fPos_Y = 0;
	float fXpos = 0;
	float fYpos = 0;
	bool bUse;							// �g�p���Ă��邩�ǂ���
} MESHWALL;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitMeshWall(int nIdxShadow , D3DXVECTOR3 pos , D3DXVECTOR3 rot);
void UninitMeshWall(void);
void UpdateMeshWall(void);
void DrawMeshWall(void);

#endif
