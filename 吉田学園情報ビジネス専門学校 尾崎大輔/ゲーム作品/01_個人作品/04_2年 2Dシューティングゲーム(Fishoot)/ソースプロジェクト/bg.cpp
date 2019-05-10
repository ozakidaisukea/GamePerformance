//=============================================================================
//
// �w�i�̏����@[bg.cpp]
// Author : Ozaki
//
//=============================================================================
#include "bg.h"
#include "renderer.h"
#include "main.h"
#include "manager.h"
#include "scene2D.h"
#include "input.h"
#include "scene.h"

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9 CBg::m_apTexture[MAX_BG] = {};
CBg::MODE CBg::m_mode;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBg::CBg():CScene(0)
{
	m_fTex = 0.0f;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CBg::~CBg()
{

}

//=============================================================================
// �ǂݍ���
//=============================================================================
HRESULT CBg::Load(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = NULL;

	pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̐���[1����]
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\bg\\umi000.png",
		&m_apTexture[0]);

	// �e�N�X�`���̐���[2����]
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\bg\\mizu001.png",
		&m_apTexture[1]);

	// �e�N�X�`���̐���[3����]
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\bg\\nami000.png",
		&m_apTexture[2]);

	return S_OK;
}

//=============================================================================
// �J��
//=============================================================================
void CBg::Unload(void)
{
	for (int nCnt = 0; nCnt < MAX_BG; nCnt++)
	{
		// �e�N�X�`���̔j��
		if (m_apTexture[nCnt] != NULL)
		{
			m_apTexture[nCnt]->Release();

			m_apTexture[nCnt] = NULL;
		}
	}
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CBg::Init(D3DXVECTOR3 pos, float widtgh, float height)
{
	//for (int nCnt = 0; nCnt < MAX_BG; nCnt++)
	//{
	//	m_apScene2D[nCnt] = new CScene2D;

	//	// ���L�e�N�X�`�������蓖�Ă�
	//	m_apScene2D[nCnt]->BindTexture(m_apTexture[0]);

	//	m_apScene2D[nCnt]->Init(pos);
	//}
	LPDIRECT3DVERTEXBUFFER9 VtxBuff;

	for (int nCntBG = 0; nCntBG < MAX_BG; nCntBG++)
	{
		VtxBuff = m_apScene2D[nCntBG]->GetVtxBG();
		//���[�J���ϐ�
		VERTEX_2D*pVtx;

		//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^�̎擾
		VtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

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


		pVtx += 4;					//���_�f�[�^�̃|�C���^��4���i�߂�

		//���_�o�b�t�@���A�����b�N
		VtxBuff->Unlock();
	}
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CBg::Uninit(void)
{
	for (int nCntBG = 0; nCntBG < MAX_BG; nCntBG++)
	{
		m_apScene2D[nCntBG]->Uninit();

		m_apScene2D[nCntBG] = NULL;
	}
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CBg::Update(void)
{

	m_fTex -= 0.005f;

	LPDIRECT3DVERTEXBUFFER9 VtxBuff;

	for (int nCntBG = 0; nCntBG < MAX_BG; nCntBG++)
	{
		VtxBuff = m_apScene2D[nCntBG]->GetVtxBG();
		//���[�J���ϐ�
		VERTEX_2D*pVtx;

		//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^�̎擾
		VtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//�e�N�X�`���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f + (m_fTex * (nCntBG + 0.5f) * 0.5f), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f + (m_fTex * (nCntBG + 0.5f) * 0.5f), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (m_fTex * (nCntBG + 0.5f) * 0.5f), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f + (m_fTex * (nCntBG + 0.5f) * 0.5f), 1.0f);


		pVtx += 4;					//���_�f�[�^�̃|�C���^��4���i�߂�

		//���_�o�b�t�@���A�����b�N
		VtxBuff->Unlock();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CBg::Draw(void)
{

}

//=============================================================================
// �w�i�̐���
//=============================================================================
CBg *CBg::Create(D3DXVECTOR3 pos, float widtgh, float height)
{
	CBg *pBg;

	pBg = new CBg;

	for (int nCntBG = 0; nCntBG < MAX_BG; nCntBG++)
	{
		pBg->m_apScene2D[nCntBG] = new CScene2D(0);

		// ���L�e�N�X�`�������蓖�Ă�
		pBg->m_apScene2D[nCntBG]->BindTexture(m_apTexture[nCntBG]);

		pBg->m_apScene2D[nCntBG]->Init(pos, widtgh,height);
	}
	pBg->Init(pos, widtgh,height);

	return pBg;
}

//=============================================================================
// ���[�h�̐ݒ�
//=============================================================================
void CBg::SetMode(MODE mode)
{

}
