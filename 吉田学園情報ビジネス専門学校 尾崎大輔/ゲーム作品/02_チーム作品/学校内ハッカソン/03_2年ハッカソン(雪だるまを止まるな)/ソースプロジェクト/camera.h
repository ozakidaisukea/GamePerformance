//=============================================================================
//
// �J�������� [camera.h]
// Author : Jukiya Hayakawa
// Editor : Yuto Kodama
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"
//*****************************************************************************
// �J�����̍\����
//*****************************************************************************
class CCamera
{
public:	//�N������A�N�Z�X�\
		//�����o�֐�
	CCamera();
	~CCamera();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void SetCamera(void);
	void SetTarget(CScene* pTarget);

	D3DXVECTOR3 GetRot(void);
	void TargetTracking(void);

	//�ÓI�����o�֐�
	static CCamera *Create(void);

private://�����������A�N�Z�X�\
	D3DXVECTOR3 m_posV;				//���_
	D3DXVECTOR3 m_posR;				//�����_
	D3DXVECTOR3 m_vecU;				//������x�N�g��
	D3DXMATRIX	m_mtxProjection;	//�v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX	m_mtxView;			//�r���[�}�g���b�N�X
	D3DXVECTOR3 m_rot;				//����
	D3DXVECTOR3 m_rotDest;			//�ړI�̌���
	float		m_rotDiff;
	float		m_fLength;			//����
	D3DXVECTOR3 m_posVDest;			//�ړI�̎��_
	D3DXVECTOR3 m_posRDest;			//�ړI�̒����_
	D3DXVECTOR3 m_DiffAngle;		//����

									/*Tracking*/
	CScene* m_pTargetObj;			//�Ǐ]����^�[�Q�b�g
};
#endif
