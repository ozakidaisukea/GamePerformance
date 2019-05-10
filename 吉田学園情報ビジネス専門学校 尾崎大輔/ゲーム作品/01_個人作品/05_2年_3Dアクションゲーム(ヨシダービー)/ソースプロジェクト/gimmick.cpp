//=============================================================================
//
// �M�~�b�N���� [gimmick.cpp]
// Author : Ozaki
//
//=============================================================================
#include "gimmick.h"
#include "manager.h"
#include "input.h"
#include "renderer.h"
#include "debugproc.h"

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9 CGimmick::m_pTexture = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CGimmick::CGimmick() : CScene(2, OBJTYPE_GIMMICK)
{
	// �|���S���̓�����ݒ�
	m_move = D3DXVECTOR3(0, 0, 0);
	// �|���S���̈ʒu��ݒ�
	m_pos = D3DXVECTOR3(0, 0, 0);
	// �|���S���̌�����ݒ�
	m_rot = D3DXVECTOR3(0, 0, 0);

	m_nType = GIMMICK_NONE;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CGimmick::~CGimmick()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CGimmick::Init(void)
{
	// �I�u�W�F�N�g�^�C�v�̐ݒ�
	SetObjtType(CScene::OBJTYPE_GIMMICK);

	//	�f�o�C�X�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9	pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\bg\\gimmick000.jpg",
		&m_pTexture);

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(MODEL_GIMMICK,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMatModel,
		NULL,
		&m_nNumMatModel,
		&m_pMeshModel);

	// �ŏ��l/�ő�l�̐ݒ� ���Scene�Ŏ擾
	m_vtxMin = D3DXVECTOR3(100, 0, 100);
	m_vtxMax = D3DXVECTOR3(-100, 0, -100);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CGimmick::Uninit(void)
{
	// �M�~�b�N��j��
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CGimmick::Update(void)
{
	// �f�o�b�N�\�����擾
	CDebugProc *m_Dubug = CRenderer::GetDebug();

	// �L�[�{�[�h���擾
	CInputKeyboard *InputKeyboard;
	InputKeyboard = CManager::GetInputKeyboard();

	if (CGimmick::GIMMICK_HEIHT == m_nType)
	{
		if (m_pos.y <= 50)
		{
			m_move.y += 0.01f;

			m_pos += m_move;

		}
		else if (m_pos.y >= 50)
		{
			m_move.y -= 0.01f;

			m_pos += m_move;
		}
	}

	if (CGimmick::GIMMICK_WIDTH == m_nType)
	{
		if (m_pos.x <= 25)
		{
			m_move.x += 0.01f;

			m_pos += m_move;

		}
		else if (m_pos.x >= 25)
		{
			m_move.x -= 0.01f;

			m_pos += m_move;
		}
	}

#ifdef _DEBUG
	// �͈͐ݒ�̃f�o�b�N
	//m_Dubug->Print("ssfsfsf", "\n[ �M�~�b�N�̈ʒu ] ", "X", m_pos.x, "Y", m_pos.y, "Z", m_pos.z);
#endif
}

//=============================================================================
// �`�揈��
//=============================================================================
void CGimmick::Draw(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = NULL;

	pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;						//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;							//�}�e���A���f�[�^�ւ̃|�C���^

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);
	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);
	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);
	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	// �}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMatModel->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_nNumMatModel; nCntMat++)
	{	// �}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
		// �e�N�X�`��
		pDevice->SetTexture(0, m_pTexture);

		// ���f��(�p�[�c)�̕`��
		m_pMeshModel->DrawSubset(nCntMat);
	}

	// �}�e���A�����f�t�H���g�ɖ߂�
	pDevice->SetMaterial(&matDef);
}

//=============================================================================
// �M�~�b�N�̐���
//=============================================================================
CGimmick * CGimmick::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot,GIMMICK_TYPE type)
{
	CGimmick *pGimmick = NULL;

	// NULL�Ƀ`�F�b�N
	if (pGimmick == NULL)
	{
		pGimmick = new CGimmick();

		// ������
		pGimmick->Init();
		// �ʒu
		pGimmick->m_pos = pos;
		// ����
		pGimmick->m_rot = rot;
		// �^�C�v
		pGimmick->m_nType = type;
	}

	// ���L�e�N�X�`�������蓖�Ă�
	pGimmick->BindTexture(m_pTexture);

	return pGimmick;
}

//=============================================================================
// ���L�e�N�X�`��
//=============================================================================
void CGimmick::BindTexture(LPDIRECT3DTEXTURE9 texture)
{
	m_pTexture = texture;
}
