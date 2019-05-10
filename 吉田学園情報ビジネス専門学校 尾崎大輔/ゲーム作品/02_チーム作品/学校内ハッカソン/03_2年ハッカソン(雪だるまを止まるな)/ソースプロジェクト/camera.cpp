//=============================================================================
//
// �J�������� [camera.cpp]
// Author : Jukiya Hayakawa
// Editor : Yuto Kodama
//
//=============================================================================
#include "camera.h"
#include "input.h"
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "debugproc.h"
#include "scene.h"
#include "player.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define CAMERA_MOVE (1.0f);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//=============================================================================
// �J�����R���X�g���N�^
//=============================================================================
CCamera::CCamera()
{
	m_pTargetObj = NULL;
}

//=============================================================================
// �J�����f�X�g���N�^
//=============================================================================
CCamera::~CCamera()
{

}

//=============================================================================
// �J�����̐���
//=============================================================================
CCamera *CCamera::Create()
{
	CCamera *pCamera = NULL;

	if (pCamera == NULL)
	{
		pCamera = new CCamera;
		pCamera->Init();
	}
	return pCamera;
}

//=============================================================================
// �J�����̏���������
//=============================================================================
HRESULT CCamera::Init(void)
{
	m_posV = D3DXVECTOR3(0.0f, 100.0f, 150.0f);						//	���_
	m_posR = D3DXVECTOR3(0.0f, 40.0f, 0.0f);						//	�����_
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);							//	������x�N�g��
	m_posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						//	�ړI�̎��_
	m_posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						//	�ړI�̒����_
	m_rot.y = atan2f(m_posR.x - m_posV.x, m_posR.z - m_posV.z);		//	����
																	//	m_rot.y = 0.0f;

	m_rotDest = m_rot;													//�ړI�̌���
	m_rotDiff = 0.0f;
	m_fLength = sqrtf((m_posV.x - m_posR.x) * (m_posV.x - m_posR.x) + (m_posV.z - m_posR.z) * (m_posV.z - m_posR.z));	//����
	return S_OK;
}

//=============================================================================
// �J�����̏I������
//=============================================================================
void CCamera::Uninit(void)
{

}

//=============================================================================
// �J�����̍X�V����
//=============================================================================
void CCamera::Update(void)
{
	CManager::MODE mode = CManager::GetMode();
	//�L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetKeyboard();

	switch (mode)
	{
	case CManager::MODE_TITLE:
		m_posV.z -= 1.0f;
		m_posR.z -= 1.0f;
		break;
	case CManager::MODE_GAME:
		//�Ǐ]
		TargetTracking();

		if (pInputKeyboard->GetPress(DIK_Z) == true)
		{// �L�[�{�[�h��[Z]�L�[�������ꂽ
			m_rot.y += 0.025f;
			if (m_rot.y >= D3DX_PI)
			{
				m_rot.y = -D3DX_PI;
			}
			//m_posV.x = m_posR.x - sinf(m_rot.y) * m_fLength;
			//m_posV.z = m_posR.z - cosf(m_rot.y) *m_fLength;
		}
		if (pInputKeyboard->GetPress(DIK_C) == true)
		{// �L�[�{�[�h��[C]�L�[�������ꂽ
			m_rot.y -= 0.025f;
			if (m_rot.y <= -D3DX_PI)
			{
				m_rot.y = D3DX_PI;
			}
			//m_posV.x = m_posR.x - sinf(m_rot.y) * m_fLength;
			//m_posV.z = m_posR.z - cosf(m_rot.y) * m_fLength;
		}
		break;
	}

	//#ifdef _DEBUG
	//	//�����_�̕\��
	//	CDebugProc::Print(1, "���_�̈ړ�    : x[%.1f],y[%.1f],z[%.1f]\n", m_posV.x, m_posV.y, m_posV.z);
	//	//���_�̕\��
	//	CDebugProc::Print(1, "�����_�̈ړ�  : x[%.1f],y[%.1f],z[%.1f]\n", m_posR.x, m_posR.y, m_posR.z);
	//#endif // _DEBUG
}

//=============================================================================
// �J�����̐ݒ菈��
//=============================================================================
void CCamera::SetCamera(void)
{
	//�����_�����O�̎擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);

	// �v���W�F�N�V�����}�g���b�N�X���쐬
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45.0f),						//��p
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,	//��ʔ䗦
		10.0f,										//��O
		1000.0f);									//���s��	�ύX����1000

													// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);

	// �r���[�}�g���b�N�X���쐬
	D3DXMatrixLookAtLH(&m_mtxView,
		&m_posV,
		&m_posR,
		&m_vecU);

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}

//=============================================================================
// �J�����̃^�[�Q�b�g�ݒ�
//=============================================================================
void CCamera::SetTarget(CScene* pTarget)
{
	m_pTargetObj = pTarget;
}

//=============================================================================
// �J�����̌����擾
//=============================================================================
D3DXVECTOR3 CCamera::GetRot(void)
{
	return m_rot;
}

//=============================================================================
// �J�����̒Ǐ]����
//=============================================================================
void CCamera::TargetTracking(void)
{
	D3DXVECTOR3 TargetPos;
	if (m_pTargetObj != NULL)
	{
		switch (m_pTargetObj->GetObjType())
		{
		case CScene::OBJTYPE_PLAYER:
			CPlayer* pPlayer = NULL;
			pPlayer = (CPlayer*)m_pTargetObj;
			if (pPlayer != NULL)
			{
				TargetPos = pPlayer->GetPosition();
			}

			break;
		}

		//�ړ��ɒǏ]
		m_posRDest = TargetPos + D3DXVECTOR3(0.0f, 30.0f, 0.0f);	//���Â炩�����炱���ɒl�𑫂�
		m_posR.x += (m_posRDest.x - m_posR.x) * 0.6f;
		m_posR.y += (m_posRDest.y - m_posR.y) * 0.6f;
		m_posR.z += (m_posRDest.z - m_posR.z) * 0.6f;

		m_posVDest.x = m_posRDest.x + sinf(m_rot.y) * m_fLength;
		m_posVDest.y = m_posV.y;
		m_posVDest.z = m_posRDest.z + cosf(m_rot.y) * m_fLength;

		m_posV += (m_posVDest - m_posV) * 0.1f;

		CDebugProc::Print(1, "m_posV = (%f,%f,%f)", m_posV.x, m_posV.y, m_posV.z);
	}
}