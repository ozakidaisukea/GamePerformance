//=============================================================================
//
// �|���S������ [meshField.h]
// Author :  Meguro Mikiya
//
//=============================================================================
#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_

#include "main.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MESHFIELD_TEXTURENAME		 "data\\TEXTURE\\field000.jpg"	//�e�N�X�`���̃t�@�C����
#define TEX_POS_X_INIT			(1.0f)								//�e�N�X�`�����WU�̏����ʒu
#define TEX_POS_Y_INIT			(1.0f)								//�e�N�X�`�����WV�̏����ʒu
#define TEX_LEFT				(0.0f)								//�e�N�X�`�����WU��
#define TEX_RIGHT				(1.0f)								//�e�N�X�`�����WU�E
#define TEX_TOP					(0.0f)								//�e�N�X�`�����WV��
#define TEX_BOT					(1.0f)								//�e�N�X�`�����WV��
#define X_POSSIZE				(50)								//X�̑傫��
#define Z_POSSIZE				(50)								//Z�̑傫��
#define X_FIELD_SIZE			(9)									//X�̕�
#define Z_FIELD_SIZE			(9)									//Z�̕�
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitMeshField(void);
void UninitMeshField(void);
void UpdateMeshField(void);
void DrawMeshField(void);

#endif
