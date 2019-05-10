//=============================================================================
//
// �J�������� [camera.cpp]
// Author : Ozaki
//
//=============================================================================
#include "camera.h"
#include "manager.h"
#include "renderer.h"
#include "scene3D.h"
#include "scene2D.h"
#include "input.h"
#include "player.h"
#include "owner.h"
#include "game.h"

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
//CScene2D CCamera::m_Scene2D = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CCamera::CCamera()
{
	m_rot = D3DXVECTOR3(0, 0, 0);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CCamera::~CCamera()
{

}

//=============================================================================
// ���͏���
//=============================================================================
HRESULT CCamera::Init(void)
{
	m_camera.posV = D3DXVECTOR3(0.0f, 100.0f, -320.0f);
	m_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_camera.posVDest = D3DXVECTOR3(0.0f, 220.0f, -320.0f);
	m_camera.posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_camera.posU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_camera.rot.y = atan2f(m_camera.posR.x - m_camera.posV.x, m_camera.posR.z - m_camera.posV.z);
	m_camera.rotDest = m_camera.rot;
	m_camera.rotDiff = 0.0f;
	m_camera.nCounterAngle = 0;
	m_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_camera.flength = sqrtf((m_camera.posRDest.x - m_camera.posVDest.x)*(m_camera.posRDest.x - m_camera.posVDest.x)
	+ (m_camera.posRDest.z - m_camera.posVDest.z)*(m_camera.posRDest.z - m_camera.posVDest.z));

	fLength = sqrtf(
		//X�̋��������߂�@X�̋�����2��
		(m_camera.posR.x - m_camera.posV.x) * (m_camera.posR.x - m_camera.posV.x)
		//Z�̋��������߂�@Z�̋�����2��
		+ (m_camera.posR.z - m_camera.posV.z) * (m_camera.posR.z - m_camera.posV.z));
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CCamera::Uninit(void)
{

}

//=============================================================================
// �X�V����
//=============================================================================
void CCamera::Update(void)
{
	// �L�[�{�[�h���擾
	CInputKeyboard *InputKeyboard;
	InputKeyboard = CManager::GetInputKeyboard();
#if 1

#ifdef _DEBUG

	// �S�[���O�J����
	if (InputKeyboard->GetTrigger(DIK_1) == true)
	{
		//m_camera.posV = D3DXVECTOR3(300.0f, 120.0f, 3000.0f);
		//m_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 3000.0f);
	}


#endif // DEBUG


#endif // 0
	switch (m_mode)
	{
	// �Q�[�����̃J����
	case MODE_GAME:

		COwner *pOwner;
		pOwner = CGame::GetOwner();

		if (pOwner != NULL)
		{
			for (int nCnrCamera = 0; nCnrCamera < MAX_CAMERA; nCnrCamera++)
			{
				m_camera.posRDest.x = pOwner->Getpos().x - sinf(pOwner->Getrot().y) * 10;
				m_camera.posRDest.z = pOwner->Getpos().z - cosf(pOwner->Getrot().y) * 30;

				//
				m_camera.posVDest.x = pOwner->Getpos().x - sinf(m_camera.rot.y) * fLength / 1.5f;
				m_camera.posVDest.z = pOwner->Getpos().z - cosf(m_camera.rot.y) * fLength / 1.5f;

				//����
				m_camera.posR.x += (m_camera.posRDest.x - m_camera.posR.x) * 0.2f + pOwner->Getmove().x;
				m_camera.posR.z += (m_camera.posRDest.z - m_camera.posR.z) * 0.2f + pOwner->Getmove().z;

				m_camera.posV.x += ((m_camera.posVDest.x - m_camera.posV.x) * 0.2f);
				m_camera.posV.z += ((m_camera.posVDest.z - m_camera.posV.z) * 0.2f);

				//�J�������v���C���[�̌��ɂ���
				m_camera.rotDest.y = (pOwner->Getrot().y + D3DX_PI);
				//�J�����ƃv���C���[�̋��������߂�
				m_camera.rotDiff = m_camera.rotDest.y - m_camera.rot.y;

				//�p�x�̐ݒ�
				if (m_camera.rotDiff > D3DX_PI)
				{
					m_camera.rotDiff -= D3DX_PI* CAMERA_MOVE;
				}
				if (m_camera.rotDiff < -D3DX_PI)
				{
					m_camera.rotDiff += D3DX_PI* CAMERA_MOVE;
				}
				//
				m_camera.rot.y += m_camera.rotDiff * 0.5f;

				if (m_camera.rot.y > D3DX_PI)
				{
					m_camera.rot.y -= D3DX_PI* CAMERA_MOVE;
				}
				if (m_camera.rot.y < -D3DX_PI)
				{
					m_camera.rot.y += D3DX_PI* CAMERA_MOVE;
				}
			}
		}
		break;
	}


#ifdef _DEBUG


	//�C�ӂ̃L�[A
	if (InputKeyboard->GetPress(DIK_LEFT) == true)
	{
		if (InputKeyboard->GetPress(DIK_UP) == true)
		{//�����ړ�
		 //�J�����̈ړ�	�J�����̈ړ�����p�x(�J�����̌��� + �p�x) * �ړ���
			m_camera.posV.x -= sinf(m_camera.rot.y + D3DX_PI * 0.75f) * 1.0f;
			m_camera.posV.z -= cosf(m_camera.rot.y + D3DX_PI * 0.75f) * 1.0f;
			//�J�����̒����_�̈ړ� �J�����̈ʒu + �J�����̊p�x * �J�����̋���
			m_camera.posR.x = m_camera.posV.x + sinf(m_camera.rot.y) * fLength;
			m_camera.posR.z = m_camera.posV.z + cosf(m_camera.rot.y) * fLength;
		}
		else if (InputKeyboard->GetPress(DIK_DOWN) == true)
		{//����O�ړ�
		 //�J�����̈ړ�	�J�����̈ړ�����p�x(�J�����̌��� + �p�x) * �ړ���
			m_camera.posV.x -= sinf(m_camera.rot.y + D3DX_PI * 0.25f) * 1.0f;
			m_camera.posV.z -= cosf(m_camera.rot.y + D3DX_PI * 0.25f) * 1.0f;
			//�J�����̒����_�̈ړ� �J�����̈ʒu + �J�����̊p�x * �J�����̋���
			m_camera.posR.x = m_camera.posV.x + sinf(m_camera.rot.y) * fLength;
			m_camera.posR.z = m_camera.posV.z + cosf(m_camera.rot.y) * fLength;
		}
		else
		{
			//�J�����̈ړ�	�J�����̈ړ�����p�x(�J�����̌��� + �p�x) * �ړ���
			m_camera.posV.x -= sinf(m_camera.rot.y + D3DX_PI * 0.5f) * 1.0f;
			m_camera.posV.z -= cosf(m_camera.rot.y + D3DX_PI * 0.5f) * 1.0f;
			//�J�����̒����_�̈ړ� �J�����̈ʒu + �J�����̊p�x * �J�����̋���
			m_camera.posR.x = m_camera.posV.x + sinf(m_camera.rot.y) * fLength;
			m_camera.posR.z = m_camera.posV.z + cosf(m_camera.rot.y) * fLength;
		}
	}
	//�C�ӂ̃L�[D
	else if (InputKeyboard->GetPress(DIK_RIGHT) == true)
	{
		if (InputKeyboard->GetPress(DIK_UP) == true)
		{//�E���ړ�
		 //�J�����̈ړ�	�J�����̈ړ�����p�x(�J�����̌��� + �p�x) * �ړ���
			m_camera.posV.x -= sinf(m_camera.rot.y - D3DX_PI * 0.75f) * 1.0f;
			m_camera.posV.z -= cosf(m_camera.rot.y - D3DX_PI * 0.75f) * 1.0f;
			//�J�����̒����_�̈ړ� �J�����̈ʒu + �J�����̊p�x * �J�����̋���
			m_camera.posR.x = m_camera.posV.x + sinf(m_camera.rot.y) * fLength;
			m_camera.posR.z = m_camera.posV.z + cosf(m_camera.rot.y) * fLength;
		}
		else if (InputKeyboard->GetPress(DIK_DOWN) == true)
		{//�E��O�ړ�
		 //�J�����̈ړ�	�J�����̈ړ�����p�x(�J�����̌��� + �p�x) * �ړ���
			m_camera.posV.x -= sinf(m_camera.rot.y - D3DX_PI * 0.25f) * 1.0f;
			m_camera.posV.z -= cosf(m_camera.rot.y - D3DX_PI * 0.25f) * 1.0f;
			//�J�����̒����_�̈ړ� �J�����̈ʒu + �J�����̊p�x * �J�����̋���
			m_camera.posR.x = m_camera.posV.x + sinf(m_camera.rot.y) * fLength;
			m_camera.posR.z = m_camera.posV.z + cosf(m_camera.rot.y) * fLength;
		}
		else
		{
			//�J�����̈ړ�	�J�����̈ړ�����p�x(�J�����̌��� + �p�x) * �ړ���
			m_camera.posV.x += sinf(m_camera.rot.y + D3DX_PI * 0.5f) * 1.0f;
			m_camera.posV.z += cosf(m_camera.rot.y + D3DX_PI * 0.5f) * 1.0f;
			//�J�����̒����_�̈ړ� �J�����̈ʒu + �J�����̊p�x * �J�����̋���
			m_camera.posR.x = m_camera.posV.x + sinf(m_camera.rot.y) * fLength;
			m_camera.posR.z = m_camera.posV.z + cosf(m_camera.rot.y) * fLength;
		}
	}
	if (InputKeyboard->GetPress(DIK_UP) == true)
	{//���ړ�
	 //�J�����̈ړ�	�J�����̈ړ�����p�x(�J�����̌��� + �p�x) * �ړ���
		m_camera.posV.x += sinf(m_camera.rot.y) * 1.0f;
		m_camera.posV.z += cosf(m_camera.rot.y) * 1.0f;
		//�J�����̒����_�̈ړ� �J�����̈ʒu + �J�����̊p�x * �J�����̋���
		m_camera.posR.x = m_camera.posV.x + sinf(m_camera.rot.y) * fLength;
		m_camera.posR.z = m_camera.posV.z + cosf(m_camera.rot.y) * fLength;
	}
	if (InputKeyboard->GetPress(DIK_DOWN) == true)
	{//��O�ړ�
	 //�J�����̈ړ�	�J�����̈ړ�����p�x(�J�����̌��� + �p�x) * �ړ���
		m_camera.posV.x -= sinf(m_camera.rot.y) * 1.0f;
		m_camera.posV.z -= cosf(m_camera.rot.y) * 1.0f;
		//�J�����̒����_�̈ړ� �J�����̈ʒu + �J�����̊p�x * �J�����̋���
		m_camera.posR.x = m_camera.posV.x + sinf(m_camera.rot.y) * fLength;
		m_camera.posR.z = m_camera.posV.z + cosf(m_camera.rot.y) * fLength;
	}


	//�C�ӂ̃L�[T
	if (InputKeyboard->GetPress(DIK_T) == true)
	{
		m_camera.rot.x += 2.0f;

		m_camera.posR.y = m_camera.rot.x;
	}
	//�C�ӂ̃L�[G
	if (InputKeyboard->GetPress(DIK_G) == true)
	{
		m_camera.rot.x -= 2.0f;

		m_camera.posR.y = m_camera.rot.x;
	}

	if (InputKeyboard->GetPress(DIK_Z) == true)
	{//���_��]
		m_camera.rot.y += 0.025f;

		m_camera.posV.x = m_camera.posR.x + sinf(m_camera.rot.y + D3DX_PI)* m_camera.flength;
		m_camera.posV.z = m_camera.posR.z + cosf(m_camera.rot.y + D3DX_PI)* m_camera.flength;

	}
	if (InputKeyboard->GetPress(DIK_C) == true)
	{// ���_��]
		m_camera.rot.y -= 0.025f;

		m_camera.posV.x = m_camera.posR.x + sinf(m_camera.rot.y + D3DX_PI)* m_camera.flength;
		m_camera.posV.z = m_camera.posR.z + cosf(m_camera.rot.y + D3DX_PI)* m_camera.flength;
	}

	//�C�ӂ̃L�[Y
	if (InputKeyboard->GetPress(DIK_Y) == true)
	{
		m_camera.posV.y += 2.0f;
	}
	//�C�ӂ̃L�[N
	if (InputKeyboard->GetPress(DIK_H) == true)
	{
		m_camera.posV.y -= 2.0f;
	}

#endif // DEBUG
}

//=============================================================================
// �J�����̐ݒ菈��
//=============================================================================
void CCamera::SetCamera(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = NULL;

	pDevice = CManager::GetRenderer()->GetDevice();

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_camera.mtxProjection);

	// �v���W�F�N�V�����}�g���b�N�X���쐬
	D3DXMatrixPerspectiveFovLH(&m_camera.mtxProjection,
		D3DXToRadian(45.0f),		// ����p
		(float)SCREEN_WIDTH /
		(float)SCREEN_HEIGHT,
		1.0f,						// ��O
		4000.0f);					// ���s


	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_camera.mtxProjection);

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_camera.mtxView);

	// �r���[�}�g���b�N�X���쐬
	D3DXMatrixLookAtLH(&m_camera.mtxView,
		&m_camera.posV,
		&m_camera.posR,
		&m_camera.posU);

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_camera.mtxView);
}
//=============================================================================
// �J�����̎擾
//=============================================================================
CCamera::Camera CCamera::GetCamera(void)
{
	return m_camera;
}

//=============================================================================
// ���[�h�̐ݒ�
//=============================================================================
void CCamera::SetMode(MODE mode)
{
	m_mode = mode;
}

//=============================================================================
// �������擾
//=============================================================================
D3DXVECTOR3 CCamera::GetRot(void)
{
	return m_camera.rot;
}