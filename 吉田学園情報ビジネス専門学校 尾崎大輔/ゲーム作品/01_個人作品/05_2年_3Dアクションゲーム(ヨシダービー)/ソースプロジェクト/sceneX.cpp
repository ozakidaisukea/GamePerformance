//=============================================================================
//
// ���f������ [model.cpp]
// Author : Meguro Mikiya
//
//=============================================================================
#include "sceneX.h"
#include "input.h"
#include "camera.h"
#include "sound.h"
#include "manager.h"
#include "renderer.h"
#include "debugproc.h"

#define MOVE_PLAYER			(2.8f)

LPDIRECT3DTEXTURE9 CSceneX::m_pTexture = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CSceneX::CSceneX(int nPriority, OBJTYPE objtype):CScene(1,CScene::OBJTYPE_X)
{
	m_move = D3DXVECTOR3(0, 0, 0);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CSceneX::~CSceneX()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CSceneX::Init(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = NULL;

	pDevice = CManager::GetRenderer()->GetDevice();

	// �|���S���̈ʒu��ݒ�
	m_pos = D3DXVECTOR3(0, 0, 0.0f);

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(MODEL_EARTH,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMatModel,
		NULL,
		&m_nNumMatModel,
		&m_pMeshModel);

	m_VtxMinModel = D3DXVECTOR3(10000, 0, 10000);
	m_VtxMaxModel = D3DXVECTOR3(-10000, 0, -10000);


	m_VtxMaxModel = D3DXVECTOR3(-10000, 0, -10000);
	m_VtxMinModel = D3DXVECTOR3(10000, 0, 10000);

#if 0
	for (int nCntTypeModel = 0; nCntTypeModel < MAX_MODEL_TYPE; nCntTypeModel++)
	{
		//���_�����擾
		nNumVtex = m_pMeshModel[nCntTypeModel]->GetNumVertices();
		//���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFvF = D3DXGetFVFVertexSize(m_pMeshModel[nCntTypeModel]->GetFVF());
		for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
		{
			//���_�@���b�N
			m_pMeshModel[nCntTypeModel]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff[nCntModel]);
			for (int nCntVtx = 0; nCntVtx < nNumVtex; nCntVtx++)
			{	//���_���W�̑��
				D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff[nCntModel];
				if (m_aModel.VtxMinModel.x > vtx.x)
				{
					m_aModel.VtxMinModel.x = vtx.x;
				}
				if (m_aModel.VtxMinModel.y > vtx.y)
				{
					m_aModel.VtxMinModel.y = vtx.y;
				}
				if (m_aModel.VtxMinModel.z > vtx.z)
				{
					m_aModel.VtxMinModel.z = vtx.z;
				}

				if (m_aModel.VtxMaxModel.x < vtx.x)
				{
					m_aModel.VtxMaxModel.x = vtx.x;
				}
				if (m_aModel.VtxMaxModel.y < vtx.y)
				{
					m_aModel.VtxMaxModel.y = vtx.y;
				}
				if (m_aModel.VtxMaxModel.z < vtx.z)
				{
					m_aModel.VtxMaxModel.z = vtx.z;
				}
				pVtxBuff[nCntModel] += sizeFvF;
			}
			//			//���_�o�b�t�@���A�����b�N
			m_pMeshModel[nCntTypeModel]->UnlockVertexBuffer();
		}
	}

#endif

	SetObjtType(CScene::OBJTYPE_X);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CSceneX::Uninit(void)
{

	CScene:: Release();

}

//=============================================================================
// �X�V����
//=============================================================================
void CSceneX::Update(void)
{
	// �L�[�{�[�h���擾
	CInputKeyboard *InputKeyboard;
	InputKeyboard = CManager::GetInputKeyboard();
	// ���[�J���ϐ�
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 rotMotion;

	////���_�o�b�t�@���A�����b�N
	//m_pVtxBuff->Unlock();
	CDebugProc *m_Dubug = CRenderer::GetDebug();

#ifdef _DEBUG
//	m_Dubug->Print("ssfsfsf", "[ Model �ʒu ] ", "X", m_pos.x, "Y", m_pos.y, "Z", m_pos.z);
#endif
}
//=============================================================================
// �`�揈��
//=============================================================================
void CSceneX::Draw(void)
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
// ���f���̐���
//=============================================================================
CSceneX * CSceneX::Create(D3DXVECTOR3 pos)
{
	CSceneX *pSceneX;

	pSceneX = new CSceneX(1);

	pSceneX->Init();

	pSceneX->m_pos = pos;

	// ���L�e�N�X�`�������蓖�Ă�
	pSceneX->BindTexture(m_pTexture);

	return pSceneX;
}

//=============================================================================
// ���L�e�N�X�`�������蓖�Ă�
//=============================================================================
void CSceneX::BindTexture(LPDIRECT3DTEXTURE9 texture)
{
	m_pTexture = texture;
}

//=============================================================================
// �|�W�V�������擾
//=============================================================================
D3DXVECTOR3 CSceneX::GetPosition(void)
{
	return m_pos;
}

//=============================================================================
// �������擾
//=============================================================================
D3DXVECTOR3 CSceneX::GetMove(void)
{
	return m_move;
}

//=============================================================================
// �|�W�V�����̐ݒ�
//=============================================================================
void CSceneX::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
// ���[�u�̐ݒ�
//=============================================================================
void CSceneX::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}

//=============================================================================
// ���[�u�̐ݒ�
//=============================================================================
void CSceneX::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}