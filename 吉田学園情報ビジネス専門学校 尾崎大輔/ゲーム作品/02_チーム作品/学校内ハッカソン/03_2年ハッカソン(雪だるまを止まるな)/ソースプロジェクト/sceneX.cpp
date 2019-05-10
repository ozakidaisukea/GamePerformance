//=============================================================================
//
// �I�u�W�F�N�gX���� [sceneX.cpp]
// Author : Jukiya Hayakawa
//
//=============================================================================
#include "sceneX.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "debugproc.h"
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CSceneX::CSceneX(int nPrioriry,OBJTYPE objtype) : CScene(nPrioriry,objtype)
{
	// �ʒu�E�����̏����ݒ�
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu�̏����ݒ�
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�����̏����ݒ�
	m_pTexture = NULL;
	m_bHit = false;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CSceneX::~CSceneX()
{

}
//=============================================================================
// �I�u�W�F�N�gX�̐���
//=============================================================================
CSceneX *CSceneX::Create(void)
{
	CSceneX *pSceneX = NULL;

	if (pSceneX == NULL)
	{
		pSceneX = new CSceneX;
		pSceneX->Init();
	}
	return pSceneX;
}
//=============================================================================
// ����������
//=============================================================================
HRESULT CSceneX::Init(void)
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
void CSceneX::Uninit(void)
{
	if (m_pTexture != NULL)
	{//�e�N�X�`����NULL�łȂ��ꍇ(��)
		for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
		{//�}�e���A���̐����J��Ԃ�
			if (m_pTexture[nCntMat] != NULL)
			{//�|�C���^�̒���NULL�`�F�b�N(�Ƌ�)
				m_pTexture[nCntMat]->Release();
				m_pTexture[nCntMat] = NULL;
			}
		}
		//�������J��(���)
		delete[] m_pTexture;
		//NULL�ɂ���(�X�n)
		m_pTexture = NULL;
	}
	//�I�u�W�F�N�g�̔j��
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CSceneX::Update(void)
{
#ifdef _DEBUG
	CDebugProc::Print(1, "���f���̈ʒu  : x[%.1f],y[%.1f],z[%.1f]\n", m_pos.x, m_pos.y, m_pos.z);
#endif
}

//=============================================================================
// �`�揈��
//=============================================================================
void CSceneX::Draw(void)
{
	//�����_�����O�̎擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans,mtxScale;					//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;									//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;										//�}�e���A���f�[�^�ւ̃|�C���^

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		m_rot.y, m_rot.x, m_rot.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �傫���̔��f
	D3DXMatrixScaling(&mtxScale,m_size.x, m_size.y, m_size.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScale);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

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

		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			//�e�N�X�`������
			pDevice->SetTexture(0, m_pTexture[nCntMat]);
		}
		else
		{
			pDevice->SetTexture(0, NULL);
		}
		pMat->MatD3D.Diffuse.a = 0.5f;

		// ���f��(�p�[�c)�̕`��
		m_pMesh->DrawSubset(nCntMat);
	}

	// �}�e���A�����f�t�H���g�ɖ߂�
	pDevice->SetMaterial(&matDef);
}

//=============================================================================
// �ʒu�̐ݒu����
//=============================================================================
void CSceneX::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
// �ʒu�̐ݒu����
//=============================================================================
void CSceneX::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//=============================================================================
// ���_���W�ő�l�̐ݒu����
//=============================================================================
void CSceneX::SetVtxMax(D3DXVECTOR3 vtxMax)
{
	//m_vtxMax = vtxMax;
	m_vtxMax = D3DXVECTOR3(vtxMax.x * m_size.x, vtxMax.y * m_size.y, vtxMax.z * m_size.z);
}

//=============================================================================
// ���_���W�ŏ��l�̐ݒu����
//=============================================================================
void CSceneX::SetVtxMin(D3DXVECTOR3 vtxMin)
{
	//m_vtxMin = vtxMin;
	m_vtxMin = D3DXVECTOR3(vtxMin.x * m_size.x, vtxMin.y * m_size.y, vtxMin.z * m_size.z);
}


//=============================================================================
// �傫���̐ݒu����
//=============================================================================
void CSceneX::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}

//=============================================================================
// �����蔻��̐ݒu����
//=============================================================================
void CSceneX::SetHit(bool bHit)
{
	m_bHit = bHit;
}

//=============================================================================
// �ʒu�̎擾����
//=============================================================================
D3DXVECTOR3 CSceneX::GetPos(void)
{
	return m_pos;
}

//=============================================================================
// ���_���W�ő�l�̎擾����
//=============================================================================
D3DXVECTOR3 CSceneX::GetVtxMax(void)
{
	return m_vtxMax;
}

//=============================================================================
// ���_���W�ŏ��l�̎擾����
//=============================================================================
D3DXVECTOR3 CSceneX::GetVtxMin(void)
{
	return m_vtxMin;
}

//=============================================================================
// �����蔻��̎擾����
//=============================================================================
bool CSceneX::GetHit(void)
{
	return m_bHit;
}
//=============================================================================
// X�t�@�C���̎擾����
//=============================================================================
void CSceneX::BindX(LPD3DXMESH mesh, LPD3DXBUFFER buffmat, DWORD nummat)
{
	//�����_�����O�̎擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();

	D3DXMATERIAL *pMat;								//�}�e���A���f�[�^�ւ̃|�C���^

	m_pMesh = mesh;
	m_pBuffMat = buffmat;
	m_nNumMat = nummat;

	// �}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	//�e�N�X�`���̐����𓮓I�m��
	m_pTexture = new LPDIRECT3DTEXTURE9[m_nNumMat];

	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		//�e�N�X�`����������O��NULL�ɂ���
		m_pTexture[nCntMat] = NULL;

		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			//�e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCntMat].pTextureFilename,
				&m_pTexture[nCntMat]);
		}
	}
}