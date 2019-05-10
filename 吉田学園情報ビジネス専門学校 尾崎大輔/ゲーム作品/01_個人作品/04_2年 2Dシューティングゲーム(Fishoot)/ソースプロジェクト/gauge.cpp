//=============================================================================
//
// �Q�[�W���� [gauge.cpp]
// Author : Ozaki
//
//=============================================================================
#include "gauge.h"
#include "renderer.h"
#include "fade.h"
#include "scene2D.h"
#include "item.h"
#include "player.h"

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9 CGauge::m_pTexture[MAX_GAUGE] = {};
float CGauge::m_fGauge = NULL;
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CGauge::CGauge() :CScene2D(8)
{
	m_fGauge = 100.0f;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CGauge::~CGauge()
{
}

//=============================================================================
// ���[�h
//=============================================================================
HRESULT CGauge::Load(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = NULL;

	pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̐���0	[�w�i]
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\game\\gaugebg.png",
		&m_pTexture[0]);

	// �e�N�X�`���̐���1	[�Q�[�W]
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\game\\gauge.png",
		&m_pTexture[1]);

	// �e�N�X�`���̐���1	[�t���[��]
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\game\\gaugeframe.png",
		&m_pTexture[2]);

	return S_OK;
}

//=============================================================================
// �A�����[�h
//=============================================================================
void CGauge::Unload(void)
{
	for (int nCnt = 0; nCnt < MAX_GAUGE; nCnt++)
	{
		// �e�N�X�`���̔j��
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();

			m_pTexture[nCnt] = NULL;
		}
	}
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CGauge::Init(D3DXVECTOR3 pos, float widtgh, float height)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = NULL;

	for (int nCnt = 0; nCnt < MAX_GAUGE; nCnt++)
	{
		m_Scene2D[nCnt] = new CScene2D(8);
		m_Scene2D[nCnt]->CScene2D::Init(pos, widtgh, height);
		m_Scene2D[nCnt]->BindTexture(m_pTexture[nCnt]);
	}

	m_widtgh = widtgh;
	m_height = height;

	m_fGauge = 20.0f;

	// ���_���̍쐬
	VERTEX_2D*pVtx;			//���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	for (int nCnt = 0; nCnt < MAX_GAUGE; nCnt++)
	{
		m_pVtxBuff = m_Scene2D[nCnt]->GetVtxBG();
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// �w�i
		if (nCnt == 0)
		{
			pVtx[0].pos = D3DXVECTOR3(20.0f, 100.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(GAUGE_VALUE, 100.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(20.0f, 130.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(GAUGE_VALUE, 130.0f, 0.0f);
		}

		// �Q�[�W
		if (nCnt == 1)
		{
			pVtx[0].pos = D3DXVECTOR3(20.0f, 100.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(m_fGauge, 100.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(20.0f, 130.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(m_fGauge, 130.0f, 0.0f);
		}

		// �t���[��
		if (nCnt == 2)
		{
			pVtx[0].pos = D3DXVECTOR3(20.0f, 100.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(GAUGE_VALUE, 100.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(20.0f, 130.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(GAUGE_VALUE, 130.0f, 0.0f);
		}

		//���_�o�b�t�@�̃A�����b�N
		m_pVtxBuff->Unlock();
	}


	SetObjtType(CScene::OBJTYPE_GAUGE);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CGauge::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_GAUGE; nCnt++)
	{
		// �e�N�X�`���̔j��
		if (m_Scene2D[nCnt] != NULL)
		{
			m_Scene2D[nCnt]->Uninit();

			m_Scene2D[nCnt] = NULL;
		}
	}
	CScene::Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CGauge::Update(void)
{
	// ���_���̍쐬
	VERTEX_2D*pVtx;			//���_���ւ̃|�C���^

	// �Q�[�W��GAUGE_VALUE�𒴂��Ȃ�
	if (m_fGauge >= GAUGE_VALUE)
	{
		m_fGauge = GAUGE_VALUE;
	}

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	for (int nCnt = 0; nCnt < MAX_GAUGE; nCnt++)
	{
		m_pVtxBuff = m_Scene2D[nCnt]->GetVtxBG();
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// �w�i
		if (nCnt == 0)
		{
			pVtx[0].pos = D3DXVECTOR3(20.0f, 100.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(GAUGE_VALUE, 100.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(20.0f, 130.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(GAUGE_VALUE, 130.0f, 0.0f);
		}

		// �Q�[�W
		if (nCnt == 1)
		{
			pVtx[0].pos = D3DXVECTOR3(20.0f, 100.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(m_fGauge, 100.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(20.0f, 130.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(m_fGauge, 130.0f, 0.0f);
		}

		// �t���[��
		if (nCnt == 2)
		{
			pVtx[0].pos = D3DXVECTOR3(20.0f, 100.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(GAUGE_VALUE, 100.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(20.0f, 130.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(GAUGE_VALUE, 130.0f, 0.0f);
		}

		//���_�o�b�t�@�̃A�����b�N
		m_pVtxBuff->Unlock();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CGauge::Draw(void)
{

}

//=============================================================================
// �Q�[�W�̐���
//=============================================================================
CGauge*CGauge::Create(D3DXVECTOR3 pos, float widtgh, float height)
{
	CGauge *pGauge;

	pGauge = new CGauge;

	if (pGauge != NULL)
	{
		pGauge->Init(pos,widtgh,height);
	}

	return pGauge;
}

//=============================================================================
// �A�C�e���擾���ɃQ�[�W��UP
//=============================================================================
void CGauge::AddGauge(float f_gauge)
{
	// 250�𒴂��Ȃ�
	if (m_fGauge <= GAUGE_VALUE)
	{
		m_fGauge += f_gauge;

	}
	else if (m_fGauge > GAUGE_VALUE)
	{
		m_fGauge = GAUGE_VALUE;
	}

	// 250��0
	if (m_fGauge < 20)
	{
		m_fGauge = 20;
	}
}