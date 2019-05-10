//=============================================================================
//
// �J�������� [camera.h]
// Author :  Meguro Mikiya
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

//*****************************************************************************
// �J�����̍\����
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 posV;			//���_
	D3DXVECTOR3 posR;			//�����_
	D3DXVECTOR3 posU;			//������x�N�g��
	D3DXVECTOR3 posVDest;
	D3DXVECTOR3 posRDest;
	D3DXVECTOR3 rotCamera;		//����
	D3DXVECTOR3 rotDest;
	D3DXVECTOR3 DiffAngle;
	D3DXMATRIX mtxProjection;	//�v���W�F�N�V�����}�g���b�N�X(�e���r)
	D3DXMATRIX mtxView;			//�r���[�}�g���b�N�X(�J�����}��)
	int nCounterAngle;			//�J�����A���O�����ς��J�E���^�[
	D3DVIEWPORT9 Viewport;		//�r���[�|�[�g
}Camera;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);
void SetCamera(int nIdxCamera);
Camera *GetCamera(void);
#endif
