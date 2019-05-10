//=============================================================================
//
// �̗̓Q�[�W�̏��� [lifegauge.h]
// Author  Jukiya Hayakawa
//
//=============================================================================
#ifndef _LIFEGAUGE_H_
#define _LIFEGAUGE_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_LIFEGAUGE			(2)								// �Q�[�W�̑���
#define LIFEGAUGE_WIDTH			(460)							// �Q�[�W�̕�
#define LIFEGAUGE_HEIGHT		(25)							// �Q�[�W�̍���

//*****************************************************************************
// �Q�[�W�̍\���̂̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3  pos;                       // �ʒu
	D3DXCOLOR	 col;						// �F
	float		 fWidth;					// ��
	float		 fHeight;					// ����
	int			 nType;						//�v���C���[�̎��
}LifeGauge;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitLifeGauge(void);
void UninitLifeGauge(void);
void UpdateLifeGauge(void);
void DrawLifeGauge(void);
void SetLifeGauge(float fWidth,int nType);
#endif