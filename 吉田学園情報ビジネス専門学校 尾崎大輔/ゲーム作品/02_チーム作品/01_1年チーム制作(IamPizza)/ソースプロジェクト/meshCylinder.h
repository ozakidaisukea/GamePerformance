//=============================================================================
//
// �|���S������ [meshCylinder.h]
// Author :  Meguro Mikiya
//
//=============================================================================
#ifndef _MESHCYLINDERSIZE_H_
#define _MESHCYLINDERSIZE_H_

#include "main.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MESHCYLINDER_TEXTURENAME		 "data\\TEXTURE\\mesh000.jpg"	//�e�N�X�`���̃t�@�C����
#define TEX_POS_X_INIT			(1.0f)								//�e�N�X�`�����WU�̏����ʒu
#define TEX_POS_Y_INIT			(1.0f)								//�e�N�X�`�����WV�̏����ʒu
#define TEX_LEFT				(0.0f)								//�e�N�X�`�����WU��
#define TEX_RIGHT				(1.0f)								//�e�N�X�`�����WU�E
#define TEX_TOP					(0.0f)								//�e�N�X�`�����WV��
#define TEX_BOT					(1.0f)								//�e�N�X�`�����WV��
//#define FIELD_SIZE				(225.0f)							//�n�ʂ̑傫��
#define X_CYLINDERPOSSIZE		(20)								//X�̑傫��
#define Y_CYLINDERPOSSIZE		(20)								//Z�̑傫��
#define X_CYLINDERSIZE			(16)									//X�̕�
#define Y_CYLINDERSIZE			(2)									//Z�̕�
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitMeshCylinder(void);
void UninitMeshCylinder(void);
void UpdateMeshCylinder(void);
void DrawMeshCylinder(void);

#endif
