//=============================================================================
//
// �J�������� [camera.h]
// Author : Ozaki 
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

//*****************************************************************************
// �J�����̍\����
//*****************************************************************************
typedef enum
{
	CAMERA_NORMAL = 0,
}CAMERA;

typedef struct
{
	D3DXVECTOR3 posV;				// ���_
	D3DXVECTOR3 posR;				// �����_
	D3DXVECTOR3 posU;				// ������x�N�g��

	D3DXVECTOR3 posVDest;				// ���_
	D3DXVECTOR3 posRDest;				// �����_
	D3DXVECTOR3 posUDest;				// ������x�N�g��
	D3DXVECTOR3 rot;				// ����
	D3DXVECTOR3 rotDest;			// �ړI�̌���
	float		rotDiff;			// ����
	D3DXMATRIX  mtxProjection;		// �v���W�F�N�^�[�}�g���b�N�X
	D3DXMATRIX	mtxView;			// �r���[�}�g���b�N�X
	float		flength;			// ���� 
	float		angle;				// ����
	int			nCounterState;		//��ԊǗ��J�E���^�[
	int			DirectionMove0;		//�E
	bool		bDisp;				//�g�p���Ă邩�ǂ���
	CAMERA		state;
	int nCounterAngle;			//�J�����A���O�����ς��J�E���^�[

}Camera;


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);
void SetCamera(void);
Camera*GetCamera(void);

#endif
