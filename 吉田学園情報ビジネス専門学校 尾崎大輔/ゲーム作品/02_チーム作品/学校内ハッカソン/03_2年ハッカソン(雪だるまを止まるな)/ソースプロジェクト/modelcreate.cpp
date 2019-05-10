//=============================================================================
//
// ���f�������̏��� [modelcreate.cpp]
// Author : Jukiya Hayakawa
//
//=============================================================================
#include "modelcreate.h"
#include "manager.h"
#include "renderer.h"
#include "loadfilefunction.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CModelCreate::CModelCreate()
{
	m_nNumModel = 0;    //���f���̑���������
	m_pMesh = NULL;     //���b�V��������
	m_pBuffMat = NULL;  //�}�e���A��������
	m_pNumMat = NULL;   //�}�e���A������������
	m_pVtxMax = NULL;   //���_���W�ő�l������
	m_pVtxMin = NULL;   //���_���W�ŏ��l������
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CModelCreate::~CModelCreate()
{

}

//=============================================================================
// ���f���̐���
//=============================================================================
CModelCreate *CModelCreate::Create(int nNumModel)
{
	CModelCreate *pModelCreate = NULL;  //���f�������|�C���^
	if (pModelCreate == NULL)
	{//NULL�̏ꍇ
		pModelCreate = new CModelCreate;	//���I�m��
		if (pModelCreate != NULL)
		{//NULL�łȂ��ꍇ
			pModelCreate->SetNumModel(nNumModel);  //���f�������ݒu����
			pModelCreate->Init();					//����������
		}
	}
	return pModelCreate;
}

//=============================================================================
// ���f���̏���������
//=============================================================================
HRESULT CModelCreate::Init(void)
{
	//���b�V���𑍐������I�m��
	m_pMesh = new LPD3DXMESH[m_nNumModel];

	//�}�e���A���𑍐������I�m��
	m_pBuffMat = new LPD3DXBUFFER[m_nNumModel];

	//�}�e���A�������𑍐������I�m��
	m_pNumMat = new DWORD[m_nNumModel];

	//���_���W�ő�l�𑍐������I�m��
	m_pVtxMax = new D3DXVECTOR3[m_nNumModel];

	//���_���W�ŏ��l�𑍐������I�m��
	m_pVtxMin = new D3DXVECTOR3[m_nNumModel];

	return S_OK;
}

//=============================================================================
// ���f���̏I������
//=============================================================================
void CModelCreate::Uninit(void)
{
	// ���b�V���J��
	if (m_pMesh != NULL)
	{
		for (int nCntMesh = 0; nCntMesh < m_nNumModel; nCntMesh++)
		{
			m_pMesh[nCntMesh]->Release();
		}
		delete[] m_pMesh;
		m_pMesh = NULL;
	}

	// �}�e���A���J��
	if (m_pBuffMat != NULL)
	{
		for (int nCntBuffMat = 0; nCntBuffMat < m_nNumModel; nCntBuffMat++)
		{
			m_pBuffMat[nCntBuffMat]->Release();
		}
		delete[] m_pBuffMat;
		m_pBuffMat = NULL;
	}

	// �}�e���A�������J��
	if (m_pNumMat != NULL)
	{
		delete[] m_pNumMat;
		m_pNumMat = NULL;
	}

	// ���_���W�̍ő�l�J��
	if (m_pVtxMax != NULL)
	{
		delete[] m_pVtxMax;
		m_pVtxMax = NULL;
	}

	// ���_�̍ŏ��l���̊J��
	if (m_pVtxMin != NULL)
	{
		delete[] m_pVtxMin;
		m_pVtxMin = NULL;
	}
}

//=============================================================================
// ���f���̑����ݒu����
//=============================================================================
void CModelCreate::SetNumModel(int nNumModel)
{
	m_nNumModel = nNumModel;
}

//=============================================================================
// ���b�V���̐ݒu����
//=============================================================================
void CModelCreate::SetMesh(LPD3DXMESH pMesh, int nIdx)
{
	//�Ώۂ̃��b�V���ԍ��ɏ����
	m_pMesh[nIdx] = pMesh;

	if (m_pMesh[nIdx] != NULL)
	{// NULL�o�Ȃ��ꍇ
	 // ���_���W�ŏ��l�ƒ��_���W�ő�l��������
		m_pVtxMin[nIdx] = D3DXVECTOR3(10000.0f, 10000.0f, 10000.0f);
		m_pVtxMax[nIdx] = D3DXVECTOR3(-10000.0f, -10000.0f, -10000.0f);

		int nNumVtx;     // ���_��
		DWORD sizeFVF;   // ���_�t�H�[�}�b�g�̃T�C�Y
		BYTE *pVtxBuff;  // ���_�o�b�t�@�ւ̃|�C���^

		// ���_�����擾
		nNumVtx = m_pMesh[nIdx]->GetNumVertices();

		// ���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFVF = D3DXGetFVFVertexSize(m_pMesh[nIdx]->GetFVF());

		// ���_�o�b�t�@�����b�N
		m_pMesh[nIdx]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{// ���ׂĂ̒��_���r���ă��f���̍ŏ��l,�ő�l�𔲂��o��
			D3DXVECTOR3 Vtx = *(D3DXVECTOR3*)pVtxBuff;   // ���_���W�̑��

			if (Vtx.x < m_pVtxMin[nIdx].x)
			{
				m_pVtxMin[nIdx].x = Vtx.x;
			}
			if (Vtx.y < m_pVtxMin[nIdx].y)
			{
				m_pVtxMin[nIdx].y = Vtx.y;  // �ŏ��l�X�V
			}
			if (Vtx.z < m_pVtxMin[nIdx].z)
			{
				m_pVtxMin[nIdx].z = Vtx.z;  // �ŏ��l�X�V
			}
			if (Vtx.x > m_pVtxMax[nIdx].x)
			{
				m_pVtxMax[nIdx].x = Vtx.x;  // �ő�l�X�V
			}
			if (Vtx.y > m_pVtxMax[nIdx].y)
			{
				m_pVtxMax[nIdx].y = Vtx.y;  // �ő�l�X�V
			}
			if (Vtx.z > m_pVtxMax[nIdx].z)
			{
				m_pVtxMax[nIdx].z = Vtx.z;  // �ő�l�X�V
			}

			pVtxBuff += sizeFVF;  // �|�C���^��i�߂�
		}
		// ���_�o�b�t�@���A�����b�N
		m_pMesh[nIdx]->UnlockVertexBuffer();
	}
}

//=============================================================================
// ���f���̃}�e���A������ݒ肷��
//=============================================================================
void CModelCreate::SetBuffMat(LPD3DXBUFFER pBuffMat, int nIdx)
{
	m_pBuffMat[nIdx] = pBuffMat;
}

//=============================================================================
// ���f���̃}�e���A���̐�����ݒ肷��
//=============================================================================
void CModelCreate::SetNumMat(DWORD nNumMat, int nIdx)
{
	m_pNumMat[nIdx] = nNumMat;
}

//=============================================================================
// ���f���̒��_�̍ő�l����ݒ肷��
//=============================================================================
void CModelCreate::SetVtxMax(D3DXVECTOR3 VtxMax, int nIdx)
{
	m_pVtxMax[nIdx] = VtxMax;
}

//=============================================================================
// ���f���̒��_�̍ŏ��l����ݒ肷��
//=============================================================================
void CModelCreate::SetVtxMin(D3DXVECTOR3 VtxMin, int nIdx)
{
	m_pVtxMin[nIdx] = VtxMin;
}

//=============================================================================
// ���f���̃��b�V�������擾����
//=============================================================================
LPD3DXMESH CModelCreate::GetMesh(int nIdx)
{
	LPD3DXMESH pMesh = NULL;  // ���b�V�����

	if (m_pMesh != NULL)
	{// ���������m�ۂ���Ă�
		pMesh = m_pMesh[nIdx];   // �ۑ����ꂽ���b�V��������
	}

	return pMesh;  // ���b�V������Ԃ�
}

//=============================================================================
// ���f���̃}�e���A�������擾����
//=============================================================================
LPD3DXBUFFER CModelCreate::GetBuffMat(int nIdx)
{
	LPD3DXBUFFER pBuffMat = NULL;  // �}�e���A�����

	if (m_pBuffMat != NULL)
	{// ���������m�ۂ���Ă�
		pBuffMat = m_pBuffMat[nIdx];   // �ۑ����ꂽ�}�e���A��������
	}

	return pBuffMat;  // �}�e���A������Ԃ�
}

//=============================================================================
// ���f���̃}�e���A���̐������擾����
//=============================================================================
DWORD CModelCreate::GetNumMat(int nIdx)
{
	DWORD nNumMat = 0;  // �}�e���A���̐����

	if (m_pNumMat != NULL)
	{// ���������m�ۂ���Ă�
		nNumMat = m_pNumMat[nIdx];   // �ۑ����ꂽ�}�e���A���̐�������
	}

	return nNumMat;  // �}�e���A���̐�����Ԃ�
}

//=============================================================================
// ���f���̒��_�̍ő�l�����擾����
//=============================================================================
D3DXVECTOR3 CModelCreate::GetVtxMax(int nIdx)
{
	D3DXVECTOR3 VtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);  // ���_�̍ő�l���

	if (m_pVtxMax != NULL)
	{// ���������m�ۂ���Ă�
		VtxMax = m_pVtxMax[nIdx];   // �ۑ����ꂽ���_�̍ő�l������
	}

	return VtxMax;  // ���_�̍ő�l����Ԃ�
}

//=============================================================================
// ���f���̒��_�̍ŏ��l�����擾����
//=============================================================================
D3DXVECTOR3 CModelCreate::GetVtxMin(int nIdx)
{
	D3DXVECTOR3 VtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);  // ���_�̍ŏ��l���

	if (m_pVtxMin != NULL)
	{// ���������m�ۂ���Ă�
		VtxMin = m_pVtxMin[nIdx];   // �ۑ����ꂽ���_�̍ŏ��l������
	}

	return VtxMin;  // ���_�̍ŏ��l����Ԃ�
}