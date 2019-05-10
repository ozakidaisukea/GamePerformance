//=============================================================================
//
// �V�[������3D [scene3D.cpp]
// Author : Ozaki
//
//=============================================================================
#include "main.h"
#include "scene3D.h"
#include "scene.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "debugproc.h"
#include "scene2D.h"
#include "player.h"

#define FIELD_SIZE				(100.0f)						//�n�ʂ̑傫��
//=============================================================================
// �ÓI�����o-�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CScene3D::m_pTexture = NULL;
CPlayer*CScene3D::m_Playerpos = NULL;
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CScene3D::CScene3D(int nCntPriority, OBJTYPE objtype):CScene(2, CScene::OBJTYPE_3D)
{
	// a
	m_aPos[0] = D3DXVECTOR3(-100.0, 0.0, 100.0);
	m_aPos[1] = D3DXVECTOR3(100.0, 0.0, 100.0);
	m_aPos[2] = D3DXVECTOR3(100.0, 0.0, -100.0);

	// b
	m_aPos[3] = D3DXVECTOR3(100.0, 0.0, -100.0);
	m_aPos[4] = D3DXVECTOR3(-100.0, 0.0, -100.0);
	m_aPos[5] = D3DXVECTOR3(-100.0, 0.0, 100.0);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CScene3D::~CScene3D()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CScene3D::Init(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = NULL;

	pDevice = CManager::GetRenderer()->GetDevice();

	// �|���S���̈ʒu��ݒ�
	m_pos = D3DXVECTOR3(-100, 0, 0.0f);

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\bg\\sky001.jpg",
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
	pVtx[0].pos = D3DXVECTOR3(-200.0f, 0.0f, -200.0f);
	pVtx[1].pos = D3DXVECTOR3(-200.0f, 0.0f, 200.0f);
	pVtx[2].pos = D3DXVECTOR3(200.0f, 0.0f, -200.0f);
	pVtx[3].pos = D3DXVECTOR3(200.0f, 0.0f, 200.0f);

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
void CScene3D::Uninit(void)
{

	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}

	// ���_�o�b�t�@�̔j��
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
void CScene3D::Update(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = NULL;

	// �}�l�[�W���[���擾
	pDevice = CManager::GetRenderer()->GetDevice();

	// �L�[�{�[�h���擾
	CInputKeyboard *InputKeyboard;
	InputKeyboard = CManager::GetInputKeyboard();

	CDebugProc *m_Dubug = CRenderer::GetDebug();


	//���[�J���ϐ�
	VERTEX_3D*pVtx;

	////���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^�̎擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	D3DXVECTOR3						m_Vec0;
	D3DXVECTOR3						m_Vec1;
	D3DXVECTOR3						m_Vec2;
	D3DXVECTOR3						m_Vec3;

	D3DXVECTOR3						m_VecA;

	D3DXVECTOR3						m_nor0;
	D3DXVECTOR3						m_nor1;
	D3DXVECTOR3						m_nor;

	m_Vec0 = pVtx[1].pos - pVtx[0].pos;
	m_Vec1 = pVtx[2].pos - pVtx[0].pos;
	D3DXVec3Cross(&m_nor0, &m_Vec0, &m_Vec1);
	D3DXVec3Normalize(&m_nor0, &m_nor0);


	m_Vec2 = pVtx[2].pos - pVtx[3].pos;
	m_Vec3 = pVtx[1].pos - pVtx[3].pos;
	D3DXVec3Cross(&m_nor1, &m_Vec2, &m_Vec3);
	D3DXVec3Normalize(&m_nor1, &m_nor1);

	// �@�����
	pVtx[0].nor = m_nor0;
	pVtx[1].nor = (m_nor0 + m_nor1) / 2;
	pVtx[2].nor = (m_nor0 + m_nor1) / 2;
	pVtx[3].nor = m_nor1;

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

#ifdef _DEBUG
	//m_Dubug->Print("ssfsfsf", "[ 3D �ʒu ] ", "X", m_pos.x, "Y", m_pos.y, "Z", m_pos.z);

	//m_Dubug->Print("ssfsfsf", "\n[ �@���O ] ","X", pVtx[0].nor.x, "Y", pVtx[0].nor.y, "Z", pVtx[0].nor.z);
	//m_Dubug->Print("ssfsfsf", "[ �@���P ] ", "X", pVtx[1].nor.x, "Y", pVtx[1].nor.y, "Z", pVtx[1].nor.z);
	//m_Dubug->Print("ssfsfsf", "[ �@���Q ] ", "X", pVtx[2].nor.x, "Y", pVtx[2].nor.y, "Z", pVtx[2].nor.z);
	//m_Dubug->Print("ssfsfsf", "[ �@���R ] ", "X", pVtx[3].nor.x, "Y", pVtx[3].nor.y, "Z", pVtx[3].nor.z);
	//m_Dubug->Print("s","\n");
#endif
}

//=============================================================================
// �`�揈��
//=============================================================================
void CScene3D::Draw(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = NULL;

	pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorldPolygon);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rotpolygon.y, m_rotpolygon.x, m_rotpolygon.z);
	D3DXMatrixMultiply(&m_mtxWorldPolygon, &m_mtxWorldPolygon, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_rotpolygon.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorldPolygon, &m_mtxWorldPolygon, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorldPolygon);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VRETEX_3D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);
}

//=============================================================================
// �V�[��3D�̐���
//=============================================================================
CScene3D *CScene3D::Create(D3DXVECTOR3 pos,D3DXVECTOR3 rot)
{
	CScene3D *pScene3D;

	pScene3D = new CScene3D(2);

	pScene3D->Init();

	pScene3D->m_pos = pos;
	pScene3D->m_rotpolygon = rot;

	// ���L�e�N�X�`�������蓖�Ă�
	pScene3D->BindTexture(m_pTexture);

	//m_pTexture = NULL;

	return pScene3D;
}

//=============================================================================
// ���L�e�N�X�`�������蓖�Ă�
//=============================================================================
void CScene3D::BindTexture(LPDIRECT3DTEXTURE9 texture)
{
	m_pTexture = texture;
}

//=============================================================================
// �v���C���[�̍������擾
//=============================================================================
float CScene3D::GetLHeght(D3DXVECTOR3 pos)
{
	//���[�J���ϐ�
	VERTEX_3D*pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^�̎擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	CPlayer *pPlayer;
	pPlayer = CManager::GetPlayer();

	int nCntA;
	int nCntB;

	nCntA = pPlayer->GetCntA();
	nCntB = pPlayer->GetCntB();

	if (nCntA == 1)
	{
		// pVtx[0]�̍���
		pos.y = ((-pVtx[3].nor.x * (pos.x - pVtx[3].pos.x)) - pVtx[3].nor.z * (pos.z - pVtx[3].pos.z) / pVtx[3].nor.y) + pVtx[3].pos.y;
	}
	if (nCntB == 1)
	{
		// pVtx[3]�̍���
		pos.y = ((-pVtx[0].nor.x * (pos.x - pVtx[0].pos.x)) - pVtx[0].nor.z * (pos.z - pVtx[0].pos.z) / pVtx[0].nor.y) + pVtx[0].pos.y;
	}

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

	return pos.y;
}