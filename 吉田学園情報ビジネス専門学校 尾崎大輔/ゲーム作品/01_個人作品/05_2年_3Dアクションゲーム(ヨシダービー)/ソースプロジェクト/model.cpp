//=============================================================================
//
// ���f������ [model.cpp]
// Author : Ozaki
//
//=============================================================================
#include "model.h"
#include "input.h"
#include "camera.h"
#include "sound.h"
#include "manager.h"
#include "renderer.h"
#include "debugproc.h"
#include "player.h"

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9 CModel::m_pTexture = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CModel::CModel()
{
	m_pBuffMatModel = NULL;
	m_pMeshModel = NULL;
	// �|���S���̓�����ݒ�
	m_move = D3DXVECTOR3(0, 0, 0);
	// �|���S���̈ʒu��ݒ�
	m_pos = D3DXVECTOR3(0, 0, 0);
	// �|���S���̌�����ݒ�
	m_rot = D3DXVECTOR3(0, 0, 0);

	m_pParent = NULL;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CModel::~CModel()
{
}

//=============================================================================
// �ǂݍ���
//=============================================================================
HRESULT CModel::Load(void)
{
	// �����_���[���擾
	CRenderer *pRenderer;
	pRenderer = new CRenderer;

	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();

	return S_OK;
}

//=============================================================================
// �J��
//=============================================================================
void CModel::Unload(void)
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CModel::Init(void)
{
	// �|���S���̓�����ݒ�
	m_move = D3DXVECTOR3(0, 0, 0);
	// �|���S���̈ʒu��ݒ�
	m_pos = D3DXVECTOR3(0, 0, 0);
	// �|���S���̌�����ݒ�
	m_rot = D3DXVECTOR3(0, 0, 0);

	m_pParent = NULL;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CModel::Uninit(void)
{
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
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMATRIX mtxRot, mtxTrans, mtxParent;		//�v�Z�p�}�g���b�N�X
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

	// �e�̃}�g���b�N�X�Ɗ|�����킹��
	if (m_pParent != NULL)
	{// �e���f���̃}�g���b�N�X���擾
		mtxParent = m_pParent->GetMtxWorld();
	}
	// �e���f�������Ȃ���
	else
	{// ����(�ŐV)�̃}�g���b�N�X���擾
		pDevice->GetTransform(D3DTS_WORLD, &mtxParent);
	}

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	// �}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMatModel->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_nNumMatModel; nCntMat++)
	{
		//pMat[nCntMat].MatD3D.Diffuse.r = 1.0f;
		//pMat[nCntMat].MatD3D.Diffuse.g = 1.0f;
		//pMat[nCntMat].MatD3D.Diffuse.b = 1.0f;

		// �}�e���A���̐ݒ�
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
// ���f���̐���
//=============================================================================
CModel * CModel::Create(D3DXVECTOR3 pos,D3DXVECTOR3 rot)
{
	CModel *pModel = NULL;

	if (pModel == NULL)
	{
		pModel = new CModel;

		// ������
		pModel->Init();

		// �ʒu
		pModel->m_pos = pos;
		// ����
		pModel->m_rot = rot;
	}

	pModel->BindTexture(m_pTexture);

	// ���f����Ԃ�
	return pModel;
}

//=============================================================================
// ���L�e�N�X�`�������蓖�Ă�
//=============================================================================
void CModel::BindTexture(LPDIRECT3DTEXTURE9 texture)
{
	m_pTexture = texture;
}

//=============================================================================
// ���L���f�������蓖�Ă�
//=============================================================================
void CModel::BindModel(LPD3DXBUFFER BuffMatModel, DWORD NumMatModel, LPD3DXMESH MeshModel)
{
	m_pBuffMatModel = BuffMatModel;
	m_nNumMatModel = NumMatModel;
	m_pMeshModel = MeshModel;
}

////=============================================================================
//// ���[���h�}�g���b�N�X�̎擾
////=============================================================================
//D3DXMATRIX CModel::GetMatrix(void)
//{
//	return m_mtxWorld;
//}

//=============================================================================
// �|�W�V�������擾
//=============================================================================
D3DXVECTOR3 CModel::GetPosition(void)
{
	return m_pos;
}

//=============================================================================
// �������擾
//=============================================================================
D3DXVECTOR3 CModel::GetMove(void)
{
	return m_move;
}

//=============================================================================
//�v���C���[�̃��[���h�}�g���b�N�X�̐ݒ�
//=============================================================================
D3DXMATRIX CModel::GetMtxWorld(void)
{
	return m_mtxWorld;
}

//=============================================================================
// �|�W�V�����̐ݒ�
//=============================================================================
void CModel::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
// �����̐ݒ�
//=============================================================================
void CModel::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//=============================================================================
// ���[�u�̐ݒ�
//=============================================================================
void CModel::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}

//=============================================================================
// �e���f����ݒ�
//=============================================================================
void CModel::SetParent(CModel *pModel)
{
	m_pParent = pModel;
}