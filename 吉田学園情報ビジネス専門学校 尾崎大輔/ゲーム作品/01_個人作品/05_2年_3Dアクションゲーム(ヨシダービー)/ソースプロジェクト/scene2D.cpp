//=============================================================================
//
// �V�[������2D [scene2D.cpp]
// Author : Ozaki
//
//=============================================================================
#include "main.h"
#include "scene2D.h"
#include "scene.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "debugproc.h"

//=============================================================================
// �ÓI�����o-�ϐ��錾
//=============================================================================

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CScene2D::CScene2D(int nPriority, OBJTYPE objtype) :CScene(3, CScene::OBJTYPE_2D)
{
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f);
	m_pos = D3DXVECTOR3(0, 0, 0);
	m_width = 0.0f;
	m_height = 0.0f;
	m_pTexture = NULL;
	m_pVtxBuff = NULL;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CScene2D::~CScene2D()
{

}

//=============================================================================
// �V�[��2D�̐���
//=============================================================================
CScene2D *CScene2D::Create(D3DXVECTOR3 pos, float width, float height)
{
	CScene2D *pScene2D;

	pScene2D = new CScene2D(4);

	pScene2D->Init();

	pScene2D->m_pos = pos;
	pScene2D->m_width = width;
	pScene2D->m_height = height;

	return pScene2D;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CScene2D::Init(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = NULL;

	pDevice = CManager::GetRenderer()->GetDevice();

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VRETEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//���[�J���ϐ�
	VERTEX_2D*pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^�̎擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	// ���_����ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x + sinf(-D3DX_PI * 0.75f) * m_width, m_pos.y + cosf(-D3DX_PI * 0.75f) * m_height, m_pos.z);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + sinf(D3DX_PI * 0.75f) * m_width, m_pos.y + cosf(D3DX_PI * 0.75f) * m_height, m_pos.z);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x + sinf(-D3DX_PI * 0.25f) * m_width, m_pos.y + cosf(-D3DX_PI * 0.25f) * m_height, m_pos.z);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + sinf(D3DX_PI * 0.25f) * m_width, m_pos.y + cosf(D3DX_PI * 0.25f) * m_height, m_pos.z);

	//�e�N�X�`���̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(255, 255, 255, 255);
	pVtx[1].col = D3DXCOLOR(255, 255, 255, 255);
	pVtx[2].col = D3DXCOLOR(255, 255, 255, 255);
	pVtx[3].col = D3DXCOLOR(255, 255, 255, 255);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

	SetObjtType(CScene::OBJTYPE_2D);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CScene2D::Uninit(void)
{
	// �e�N�X�`���̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CScene2D::Update(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void CScene2D::Draw(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = NULL;

	pDevice = CManager::GetRenderer()->GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VRETEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);
}

//=============================================================================
// �o�[�e�b�N�w�i���擾
//=============================================================================
LPDIRECT3DVERTEXBUFFER9 CScene2D::GetVtxBG(void)
{
	return m_pVtxBuff;
}

//=============================================================================
// �ʒu���擾
//=============================================================================
D3DXVECTOR3 CScene2D::GetPos(void)
{
	return m_pos;
}

//=============================================================================
// �|�W�V�����̐ݒ�
//=============================================================================
void CScene2D::SetPosition(D3DXVECTOR3 pos, float frot, float position, float addposition)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = NULL;

	pDevice = CManager::GetRenderer()->GetDevice();

	//���[�J���ϐ�
	VERTEX_2D*pVtx;

	m_pos = pos;
	m_flength = addposition;

	if (m_pVtxBuff != NULL)
	{
		//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^�̎擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// ���_����ݒ�
		pVtx[0].pos = D3DXVECTOR3(m_pos.x + sinf(-D3DX_PI * 0.75f - frot) * (m_width + position), m_pos.y + cosf(-D3DX_PI * 0.75f - frot) * (m_height + position), m_pos.z);
		pVtx[1].pos = D3DXVECTOR3(m_pos.x + sinf(D3DX_PI * 0.75f - frot) * (m_width + position), m_pos.y + cosf(D3DX_PI * 0.75f - frot) * (m_height + position), m_pos.z);
		pVtx[2].pos = D3DXVECTOR3(m_pos.x + sinf(-D3DX_PI * 0.25f - frot) * (m_width + position), m_pos.y + cosf(-D3DX_PI * 0.25f - frot) * (m_height + position), m_pos.z);
		pVtx[3].pos = D3DXVECTOR3(m_pos.x + sinf(D3DX_PI * 0.25f - frot) * (m_width + position), m_pos.y + cosf(D3DX_PI * 0.25f - frot) * (m_height + position), m_pos.z);

		//���_�o�b�t�@���A�����b�N
		m_pVtxBuff->Unlock();
	}

}

//=============================================================================
// �����擾
//=============================================================================
void CScene2D::SetWidth(float width)
{
	m_width = width;
}

//=============================================================================
// �c���擾
//=============================================================================
void CScene2D::Setheight(float heidht)
{
	m_height = heidht;
}

//=============================================================================
// �J���[���擾
//=============================================================================
void CScene2D::SetColor(D3DXCOLOR col)
{
	m_col = col;

	//���[�J���ϐ�
	VERTEX_2D*pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^�̎擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(m_col.r, m_col.g, m_col.b, m_col.a);
	pVtx[1].col = D3DXCOLOR(m_col.r, m_col.g, m_col.b, m_col.a);
	pVtx[2].col = D3DXCOLOR(m_col.r, m_col.g, m_col.b, m_col.a);
	pVtx[3].col = D3DXCOLOR(m_col.r, m_col.g, m_col.b, m_col.a);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

//=============================================================================
// ���L�e�N�X�`�������蓖�Ă�
//=============================================================================
void CScene2D::BindTexture(LPDIRECT3DTEXTURE9 texture)
{
	m_pTexture = texture;
}

//=============================================================================
// �e�N�X�`�����擾
//=============================================================================
LPDIRECT3DTEXTURE9 CScene2D::GetTexture(void)
{
	return m_pTexture;
}

//=============================================================================
// �e�N�X�`���̐ݒ�
//=============================================================================
void CScene2D::SetTexture(float TexU, float TexV, int nPatternAnim, int MaxPattern)
{
	float fTexU = 1 / TexU;
	float fTexV = 1 / TexV;

	//���[�J���ϐ�
	VERTEX_2D*pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^�̎擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`���̐ݒ�
	pVtx[0].tex.x = (0.0f + (fTexU * (nPatternAnim % MaxPattern)));
	pVtx[0].tex.y = (0.0f + fTexV);

	pVtx[1].tex.x = (fTexU + (fTexU * (nPatternAnim % MaxPattern)));
	pVtx[1].tex.y = (fTexU + fTexV);

	pVtx[2].tex.x = (0.0f + (fTexU * (nPatternAnim % MaxPattern)));
	pVtx[2].tex.y = (fTexV + fTexV);

	pVtx[3].tex.x = (fTexU + (fTexU * (nPatternAnim % MaxPattern)));
	pVtx[3].tex.y = (fTexV + fTexV);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}