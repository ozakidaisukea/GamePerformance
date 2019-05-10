//=============================================================================
//
// ���f������ [model.cpp]
// Author : Jukiya Hayakawa
//
//=============================================================================
#include "model.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "debugproc.h"
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CModel::CModel()
{
	// �ʒu�E�����̏����ݒ�
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu�̏����ݒ�
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�����̏����ݒ�
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CModel::~CModel()
{

}
//=============================================================================
// �I�u�W�F�N�gX�̐���
//=============================================================================
CModel *CModel::Create(D3DXVECTOR3 pos)
{
	CModel *pModel = NULL;

	if (pModel == NULL)
	{
		pModel = new CModel;		//���I�m��
		if (pModel != NULL)
		{
			pModel->Init();			//����������
			pModel->m_pos = pos;	//�ʒu�̑��8
		}
	}
	return pModel;
}
//=============================================================================
// ����������
//=============================================================================
HRESULT CModel::Init(void)
{
	//�����_�����O�̎擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CModel::Uninit(void)
{
	////�o�b�t�@�̊J��
	//if (m_pBuffMat != NULL)
	//{
	//	m_pBuffMat->Release();
	//	m_pBuffMat = NULL;
	//}
	//// ���b�V���̊J��
	//if (m_pMesh != NULL)
	//{
	//	m_pMesh->Release();
	//	m_pMesh = NULL;
	//}
}

//=============================================================================
// �X�V����
//=============================================================================
void CModel::Update(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void CModel::Draw(void)
{
	//�����_�����O�̎擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;					//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;							//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;								//�}�e���A���f�[�^�ւ̃|�C���^
	D3DXMATRIX mtxParent;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		m_rot.y, m_rot.x, m_rot.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	if (m_pParent != NULL)
	{//�e������ꍇ
		mtxParent = m_pParent->GetMtxWorld();
	}
	else
	{//�e�����Ȃ��ꍇ
		pDevice->GetTransform(D3DTS_WORLD, &mtxParent);
	}
	//�e���f���̃}�g���b�N�X���|�����킹��
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	// �}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		// �}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//�e�N�X�`������
		pDevice->SetTexture(0, NULL);

		// ���f��(�p�[�c)�̕`��
		m_pMesh->DrawSubset(nCntMat);
	}

	// �}�e���A�����f�t�H���g�ɖ߂�
	pDevice->SetMaterial(&matDef);
}

//=============================================================================
// �ʒu�̐ݒu����
//=============================================================================
void CModel::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
// �ʒu�̐ݒu����
//=============================================================================
void CModel::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//=============================================================================
// �ʒu�̎擾����
//=============================================================================
D3DXVECTOR3 CModel::GetPos(void)
{
	return m_pos;
}

//=============================================================================
// �����̎擾����
//=============================================================================
D3DXVECTOR3 CModel::GetRot(void)
{
	return m_rot;
}

//=============================================================================
// X�t�@�C���̎擾����
//=============================================================================
void CModel::BindX(LPD3DXMESH mesh, LPD3DXBUFFER buffmat, DWORD nummat)
{
	m_pMesh = mesh;
	m_pBuffMat = buffmat;
	m_nNumMat = nummat;
}

//=============================================================================
// �e�̐ݒ�
//=============================================================================
void CModel::SetParent(CModel *pModel)
{
	m_pParent = pModel;
}

//=============================================================================
// ���[���h�}�g���b�N�X�̎擾
//=============================================================================
D3DXMATRIX CModel::GetMtxWorld(void)
{
	return m_mtxWorld;
}

//=============================================================================
// �e�N�X�`���̐ݒu
//=============================================================================
void CModel::BindTexture(LPDIRECT3DTEXTURE9 tex)
{
	m_pTexture = tex;
}
