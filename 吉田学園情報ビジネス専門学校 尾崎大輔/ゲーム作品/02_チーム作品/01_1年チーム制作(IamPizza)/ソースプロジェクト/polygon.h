//=============================================================================
//
// �|���S������ [polygon.h]
// Author :  Meguro Mikiya
//
//=============================================================================
#ifndef _POLYGON_H_
#define _POLYGON_H_

#include "main.h"

//*****************************************************************************
// �|���S���̍\����
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;							//�ʒu
	D3DXVECTOR3 rot;							//����
	D3DXMATRIX	mtrxWorld;						//���[���h�}�g���b�N�X
	bool bUse;
}POLYGON;
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define POLYGON_TEXTURENAME		 "data\\TEXTURE\\MapField001.jpg"		//�e�N�X�`���̃t�@�C����
#define TEX_POS_X_INIT			(1.0f)							//�e�N�X�`�����WU�̏����ʒu
#define TEX_POS_Y_INIT			(1.0f)							//�e�N�X�`�����WV�̏����ʒu
#define TEX_LEFT				(0.0f)							//�e�N�X�`�����WU��
#define TEX_RIGHT				(1.0f)							//�e�N�X�`�����WU�E
#define TEX_TOP					(0.0f)							//�e�N�X�`�����WV��
#define TEX_BOT					(1.0f)							//�e�N�X�`�����WV��
#define FIELD_SIZE				(3000.0f)						//�n�ʂ̑傫��
#define MAX_POLYGON				(9)
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitPolygon(void);
void UninitPolygon(void);
void UpdatePolygon(void);
void DrawPolygon(void);
void SetPolygon(D3DXVECTOR3 pos);

#endif
