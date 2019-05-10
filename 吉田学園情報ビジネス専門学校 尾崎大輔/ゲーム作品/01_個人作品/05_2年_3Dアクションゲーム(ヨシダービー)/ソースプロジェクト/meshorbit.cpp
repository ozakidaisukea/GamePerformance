//=============================================================================
//
// ���b�V���t�B�[���h���� [meshField.cpp]
// Author : OZAKI
//
//=============================================================================
#include "meshorbit.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "debugproc.h"
#include "player.h"

//=============================================================================
//	�ÓI�����o�ϐ��̏�����
//=============================================================================
LPDIRECT3DTEXTURE9 CMeshOrbit::m_pTexture = NULL;

//=============================================================================
//	�R���X�g���N�^
//=============================================================================
CMeshOrbit::CMeshOrbit(int nPriarity = 1, OBJTYPE objtype = OBJTYPE_MESHORBIT) : CScene(1, OBJTYPE_MESHORBIT)
{
}

//=============================================================================
//	�f�X�g���N�^
//=============================================================================
CMeshOrbit::~CMeshOrbit()
{

}

//=============================================================================
//	����������
//=============================================================================
HRESULT CMeshOrbit::Init(void)
{
	//�I�u�W�F�N�g�̎�ނ̐ݒ�
	SetObjtType(CScene::OBJTYPE_MESHORBIT);

	//	�f�o�C�X�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9	pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\bg\\gradation008.jpg", &m_pTexture);

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 400
		, D3DUSAGE_WRITEONLY
		, FVF_VRETEX_3D
		, D3DPOOL_MANAGED
		, &m_pVtxBuff
		, NULL);

	// ���_���̐ݒ�
	VERTEX_3D *pVtx;						// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���̕�����
	m_nWidth = 100;
	for (int nCnt = 0; nCnt < m_nWidth; nCnt++)
	{
		pVtx[nCnt].pos = D3DXVECTOR3(0.0, 0.0, 0.0);
		pVtx[nCnt].nor = D3DXVECTOR3(0, 1, 0);
		pVtx[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[nCnt].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx++;
	}

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
//	�I������
//=============================================================================
void CMeshOrbit::Uninit(void)
{
	//�e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}

	//���_�o�b�t�@�̊J��
	if (m_pVtxBuff != NULL)
	{//	���_�o�b�t�@���g���Ă�����
		m_pVtxBuff->Release();
		// ��ɂ���
		m_pVtxBuff = NULL;
	}
	//�������g�̔j��
	CMeshOrbit::Release();
}

//=============================================================================
//	�X�V����
//=============================================================================
void CMeshOrbit::Update(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = NULL;

	// �}�l�[�W���[���擾
	pDevice = CManager::GetRenderer()->GetDevice();

	// �L�[�{�[�h���擾
	CInputKeyboard *InputKeyboard;
	InputKeyboard = CManager::GetInputKeyboard();

	// �f�o�b�N�\�����擾
	CDebugProc *m_Dubug = CRenderer::GetDebug();

	// ���_���̐ݒ�
	VERTEX_3D *pVtx;						// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �Â��Ƃ�����ŐV�ɃX���C�h
	for (int nCnt = m_nWidth; nCnt > 0; nCnt--)
	{
		pVtx[nCnt * 2] = pVtx[nCnt * 2 - 2];			// 8����6�ɑ��
		pVtx[nCnt * 2 + 1] = pVtx[nCnt * 2 - 2 + 1];	// 9����7�ɑ��
	}

	// �I�t�Z�b�g�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pMtxParent->_41, m_pMtxParent->_42, m_pMtxParent->_43);
	pVtx[1].pos = D3DXVECTOR3(m_pMtxParent->_41, m_pMtxParent->_42 + 50.0f, m_pMtxParent->_43);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

#ifdef _DEBUG
	//m_Dubug->Print("ssfsfsf", "\n[ pVtx�̈ʒu ] ", "X", pVtx->pos.x, "Y", pVtx->pos.y, "Z", pVtx->pos.z);
#endif
}

//=============================================================================
//	�X�V����
//=============================================================================
void CMeshOrbit::Draw(void)
{
	//	�f�o�C�X�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;				// �v�Z�p�}�g���b�N�X

	D3DXVECTOR3 aPosVertex[MAX_NUM];

	// �J�����O
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	// ���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxworld);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxworld);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VRETEX_3D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		200);

	//// �e�̃}�g���b�N�X�Ɗ|�����킹��	(�V�������_���W)
	//m_pos.x = m_mtxworld._41;
	//m_pos.y = m_mtxworld._42;
	//m_pos.z = m_mtxworld._43;

	// �J�����O��߂�
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

//=============================================================================
//�|���S���̐�������
//=============================================================================
CMeshOrbit *CMeshOrbit::Create(D3DXMATRIX mtxWorld)
{
	CMeshOrbit *pMeshOrbit;

	pMeshOrbit = new CMeshOrbit;

	pMeshOrbit->Init();

	pMeshOrbit->m_pMtxParent = &mtxWorld;

	pMeshOrbit->BindTexture(m_pTexture);

	return pMeshOrbit;
}

//=============================================================================
//�|���S���̐e�q�ݒ�
//=============================================================================
void CMeshOrbit::SetMtxParent(D3DXMATRIX * pMtx)
{
	m_pMtxParent = pMtx;
}

//=============================================================================
//���L�e�N�X�`����ݒ�
//=============================================================================
void CMeshOrbit::BindTexture(LPDIRECT3DTEXTURE9 texture)
{
	m_pTexture = texture;
}
