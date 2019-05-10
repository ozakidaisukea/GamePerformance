//=============================================================================
//
// ���C�t�V�[������2D [lifescene2D.cpp]
// Author : Ozaki
//
//=============================================================================
#include "main.h"
#include "lifescene2D.h"
#include "scene.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "bg.h"

//=============================================================================
//
//============================================================================

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CLIfeScene2D::CLIfeScene2D()
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CLIfeScene2D::~CLIfeScene2D()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CLIfeScene2D::Init(D3DXVECTOR3 pos, float widtgh, float height)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = NULL;

	pDevice = CManager::GetRenderer()->GetDevice();

	// �|���S���̈ʒu��ݒ�
	m_pos = pos;
	m_fwidtgh = widtgh;
	m_fheight = height;

	m_Perjudgment = widtgh,height - 40.0f;

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

	// ���_����ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x + sinf(-D3DX_PI * 0.75f) * m_fwidtgh, m_pos.y + cosf(-D3DX_PI * 0.75f) * m_fheight, m_pos.z);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + sinf(D3DX_PI * 0.75f) * m_fwidtgh, m_pos.y + cosf(D3DX_PI * 0.75f) * m_fheight, m_pos.z);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x + sinf(-D3DX_PI * 0.25f) * m_fwidtgh, m_pos.y + cosf(-D3DX_PI * 0.25f) * m_fheight, m_pos.z);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + sinf(D3DX_PI * 0.25f) * m_fwidtgh, m_pos.y + cosf(D3DX_PI * 0.25f) * m_fheight, m_pos.z);

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
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CLIfeScene2D::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void CLIfeScene2D::Update(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void CLIfeScene2D::Draw(void)
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
// �V�[��2D�̐���
//=============================================================================
CLIfeScene2D *CLIfeScene2D::Create(D3DXVECTOR3 pos, float widtgh, float height)
{
	CLIfeScene2D *pScene2D = NULL;

	pScene2D = new CLIfeScene2D;

	pScene2D->Init(pos,widtgh,height);

	pScene2D->m_pos = pos;
	pScene2D->m_fwidtgh = widtgh;
	pScene2D->m_fheight = height;

	return pScene2D;
}

//=============================================================================
// �Z�b�g
//=============================================================================
void CLIfeScene2D::SetPosition(D3DXVECTOR3 pos, float rot, float position, float addposition)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = NULL;

	pDevice = CManager::GetRenderer()->GetDevice();

	//���[�J���ϐ�
	VERTEX_2D*pVtx;

	m_pos = pos;
	m_fwidtgh, m_fheight = addposition;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^�̎擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_����ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x + sinf(-D3DX_PI * 0.75f - rot) * (m_fwidtgh + position), m_pos.y + cosf(-D3DX_PI * 0.75f - rot) * (m_fheight + position), m_pos.z);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + sinf(D3DX_PI * 0.75f - rot) * (m_fwidtgh + position), m_pos.y + cosf(D3DX_PI * 0.75f - rot) * (m_fheight + position), m_pos.z);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x + sinf(-D3DX_PI * 0.25f - rot) * (m_fwidtgh + position), m_pos.y + cosf(-D3DX_PI * 0.25f - rot) * (m_fheight + position), m_pos.z);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + sinf(D3DX_PI * 0.25f - rot) * (m_fwidtgh + position), m_pos.y + cosf(D3DX_PI * 0.25f - rot) * (m_fheight + position), m_pos.z);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

	//if (bUse == false)
	//{
	//	bUse = true;
	//	Release();
	//}
}

//=============================================================================
// �|�W�V�������擾
//=============================================================================
D3DXVECTOR3 CLIfeScene2D::GetPosition(void)
{
	return m_pos;
}

//=============================================================================
// �����擾
//=============================================================================
float CLIfeScene2D::GetLength(void)
{
	return m_Perjudgment;
}


//=============================================================================
// ���L�e�N�X�`�������蓖�Ă�
//=============================================================================
void CLIfeScene2D::BindTexture(LPDIRECT3DTEXTURE9 texture)
{
	m_pTexture = texture;
}

void CLIfeScene2D::SetTexture(float TexU, float TexV, int nPatternAnim, int MaxPattern)
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

//=============================================================================
// �o�[�e�b�N�w�i���擾
//=============================================================================
LPDIRECT3DVERTEXBUFFER9 CLIfeScene2D::GetVtxBG(void)
{
	return m_pVtxBuff;
}