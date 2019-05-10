//=============================================================================
//
// �r���{�[�h���� [billboard.cpp]
// Author : Ozaki
//
//=============================================================================
#include "main.h"
#include "billboard.h"
#include "scene.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "debugproc.h"
#include "player.h"

//=============================================================================
// �ÓI�����o-�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CBillboard::m_pTexture = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBillboard::CBillboard(int nCntPriority, OBJTYPE objtype) :CScene(4, CScene::OBJTYPE_BILLBOARD)
{
	// �|���S���̈ʒu��ݒ�
	m_pos = D3DXVECTOR3(0, 0, 0.0f);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CBillboard::~CBillboard()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CBillboard::Init(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = NULL;

	pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\game\\name.png",
		&m_pTexture);

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VRETEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//���[�J���ϐ� ���_���̃|�C���^
	VERTEX_3D*pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^�̎擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-10.0, 20.0, -0);
	pVtx[1].pos = D3DXVECTOR3(50.0, 20.0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-10.0, -0, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(50.0, -0, 0.0f);

	// �@�����
	pVtx[0].nor = D3DXVECTOR3(0, 0, -1);
	pVtx[1].nor = D3DXVECTOR3(0, 0, -1);
	pVtx[2].nor = D3DXVECTOR3(0, 0, -1);
	pVtx[3].nor = D3DXVECTOR3(0, 0, -1);

	// ���_�J���[
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

	SetObjtType(CScene::OBJTYPE_3D);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CBillboard::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}

	// �e�N�X�`���̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	CScene::Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CBillboard::Update(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = NULL;

	// �}�l�[�W���[���擾
	pDevice = CManager::GetRenderer()->GetDevice();

	// �L�[�{�[�h���擾
	CInputKeyboard *InputKeyboard;
	InputKeyboard = CManager::GetInputKeyboard();

	m_pos = CPlayer::Getpos();
	m_pos.y += 50.0f;

	CDebugProc *m_Dubug = CRenderer::GetDebug();

#ifdef _DEBUG
	m_Dubug->Print("ssfsfsf", "[ �r���{�[�h �ʒu ] ", "X", m_pos.x, "Y", m_pos.y, "Z", m_pos.z);
#endif
}

//=============================================================================
// �`�揈��
//=============================================================================
void CBillboard::Draw(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = NULL;

	pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans, mtxView;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);
	m_mtxWorld._11 = mtxView._11;
	m_mtxWorld._12 = mtxView._21;
	m_mtxWorld._13 = mtxView._31;
	m_mtxWorld._21 = mtxView._12;
	m_mtxWorld._22 = mtxView._22;
	m_mtxWorld._23 = mtxView._32;
	m_mtxWorld._31 = mtxView._13;
	m_mtxWorld._32 = mtxView._23;
	m_mtxWorld._33 = mtxView._33;

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VRETEX_3D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	// �A���t�@�e�X�g
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	// �����_�[�X�e�[�g�����ɖ߂�

	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//=============================================================================
// �V�[��3D�̐���
//=============================================================================
CBillboard *CBillboard::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CBillboard *pScene3D;

	pScene3D = new CBillboard(4);

	pScene3D->Init();

	pScene3D->m_pos = pos;
	pScene3D->m_rot = rot;

	// ���L�e�N�X�`�������蓖�Ă�
	pScene3D->BindTexture(m_pTexture);

	return pScene3D;
}

//=============================================================================
// ���L�e�N�X�`�������蓖�Ă�
//=============================================================================
void CBillboard::BindTexture(LPDIRECT3DTEXTURE9 texture)
{
	m_pTexture = texture;
}

//=============================================================================
// �|�W�V�������擾
//=============================================================================
D3DXVECTOR3 CBillboard::GetPosition(void)
{
	return m_pos;
}

//=============================================================================
// �|�W�V�����̐ݒ�
//=============================================================================
void CBillboard::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
// �|�W�V�������擾
//=============================================================================
D3DXVECTOR3 CBillboard::GetMove(void)
{
	return m_movve;
}

//=============================================================================
// �|�W�V�����̐ݒ�
//=============================================================================
void CBillboard::SetMove(D3DXVECTOR3 move)
{
	m_movve = move;
}