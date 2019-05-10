//=============================================================================
//
// �t�F�[�h���� [fade.cpp]
// Author : Ozaki
//
//=============================================================================
#include "fade.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9	CFade::m_pTexture = NULL;
//LPDIRECT3DVERTEXBUFFER9 CFade::m_pVtxBuff = NULL;
CManager::MODE CFade::m_modeNext = CManager::MODE_TITLE;

CFade::FADE CFade::m_fade = CFade::FADE_IN;
D3DXCOLOR CFade::m_colorFade = D3DXCOLOR(0, 0, 0, 0);

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CFade::CFade()
{
	m_pVtxBuff = NULL;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CFade::~CFade()
{

}

//=============================================================================
// ���[�h
//=============================================================================
HRESULT CFade::Load(void)
{
	CRenderer *pRenderer;

	pRenderer = new CRenderer;

	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = NULL;

	pDevice = CManager::GetRenderer()->GetDevice();

	return S_OK;
}

//=============================================================================
// �A�����[�h
//=============================================================================
void CFade::Unload(void)
{
	// �e�N�X�`���̔j��
	/*if (m_pTexture != NULL)
	{
		m_pTexture->Release();

		m_pTexture = NULL;
	}*/
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CFade::Init(CManager::MODE modeNext)
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

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

	m_colorFade = D3DXCOLOR(0, 0, 0, 0);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CFade::Uninit(void)
{
	// �e�N�X�`���̔j��
	/*if (m_pTexture != NULL)
	{
		m_pTexture->Release();

		m_pTexture = NULL;
	}*/
	CScene::ReleaseAll();
}

//=============================================================================
// �X�V����
//=============================================================================
void CFade::Update(void)
{
	VERTEX_2D*pVtx;									//���_���ւ̃|�C���^

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_�J���[�̐ݒ�
	pVtx[0].col = m_colorFade;
	pVtx[1].col = m_colorFade;
	pVtx[2].col = m_colorFade;
	pVtx[3].col = m_colorFade;

	m_pVtxBuff->Unlock();

	if (m_fade != FADE_NONE)
	{
		if (m_fade == FADE_IN)
		{
			m_colorFade.a -= 0.03f;
			if (m_colorFade.a <= 0.0f)
			{
				m_colorFade.a = 0.0f;
				m_fade = FADE_NONE;
			}
		}
		else if (m_fade == FADE_OUT)
		{
			m_colorFade.a += 0.02f;
			if (m_colorFade.a >= 1.0f)
			{
				m_colorFade.a = 1.0f;
				m_fade = FADE_IN;

				CManager::SetMode(m_modeNext);
			}
		}
	}



}

//=============================================================================
// �`�揈��
//=============================================================================
void CFade::Draw(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = NULL;

	pDevice = CManager::GetRenderer()->GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VRETEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);
}

//=============================================================================
// �t�F�[�h�̐���
//=============================================================================
CFade*CFade::Create(void)
{
	CFade *pFade;

	pFade = new CFade;

	if (pFade != NULL)
	{
		pFade->Init(m_modeNext);
	}

	return pFade;
}

//=============================================================================
// �t�F�[�h�̐ݒ�
//=============================================================================
void CFade::SetFade(CManager::MODE modeNext)
{
	if (m_fade != FADE_OUT)
	{
		m_fade = FADE_OUT;
		m_modeNext = modeNext;								//���̉��
		m_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	//�t�F�[�h�̐F
	}
}

//=============================================================================
// ���[�h�̎擾
//=============================================================================
CFade::FADE CFade::GetFade(void)
{
	return m_fade;
}