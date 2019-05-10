//=============================================================================
//
// �t�F�[�h�̏��� [bg.cpp]
// Author : Jukiya Hayakawa
//
//=============================================================================
#include "fade.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "scene2D.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
CFade::FADE CFade::m_fade = CFade::FADE_NONE;
CManager::MODE CFade::m_modeNext = {};
D3DXCOLOR CFade::m_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
//=============================================================================
// �}�N����`
//=============================================================================

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================

//=============================================================================
// �t�F�[�h�̃R���X�g���N�^
//=============================================================================
CFade::CFade()
{
	//m_fade = FADE_NONE;
	//m_modeNext = CManager::MODE_TITLE;
	m_pVtxBuff = NULL;							// ���_�o�b�t�@�ւ̃|�C���^
	m_pTexture = NULL;
}
//=============================================================================
// �t�F�[�h�̃f�X�g���N�^
//=============================================================================
CFade::~CFade()
{

}

//=============================================================================
//�t�F�[�h�̐���
//=============================================================================
CFade *CFade::Create(void)
{
	CFade *pFade = NULL;

	if (pFade == NULL)
	{
		pFade = new CFade;		//���I�m��
		pFade->Init();			//����������
	}
	return pFade;				//�l��Ԃ�
}

//=============================================================================
// �t�F�[�h�̏���������
//=============================================================================
HRESULT CFade::Init(void)
{
	m_fade = FADE_NONE;											//�t�F�[�h�C����Ԃɂ���
	m_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);			//�����

																//�����_�����O�̎擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	//�|�C���^�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_2D*pVtx;	//���_���ւ̃|�C���^

					//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)& pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = m_colorFade;
	pVtx[1].col = m_colorFade;
	pVtx[2].col = m_colorFade;
	pVtx[3].col = m_colorFade;

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
	return S_OK;
}

//=============================================================================
// �t�F�[�h�̏I������
//=============================================================================
void CFade::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//=============================================================================
// �t�F�[�h�̍X�V����
//=============================================================================
void CFade::Update(void)
{
	if (m_fade != FADE_NONE)
	{
		if (m_fade == FADE_IN)
		{
			m_colorFade.a -= 0.015f;	//��ʂ𓧖��ɂ��Ă���

			if (m_colorFade.a <= 0.0f)
			{
				m_colorFade.a = 0.0f;
				m_fade = FADE_NONE;		//�������Ă��Ȃ���Ԃɂ���
			}
		}
		else if (m_fade == FADE_OUT)
		{
			m_colorFade.a += 0.015f;		//��ʂ�s�����ɂ���
			if (m_colorFade.a >= 1.0f)
			{//�s�����ɂȂ����ꍇ
				m_colorFade.a = 1.0f;
				m_fade = FADE_IN;		//�t�F�[�h�C����Ԃɂ���

				//���[�h�̐ݒ�
				CManager::SetMode(m_modeNext);
			}
		}
	}

	VERTEX_2D*pVtx;	//���_���ւ̃|�C���^
					//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)& pVtx, 0);

	//���_�J���[�̐ݒ�
	pVtx[0].col = m_colorFade;
	pVtx[1].col = m_colorFade;
	pVtx[2].col = m_colorFade;
	pVtx[3].col = m_colorFade;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}
//=============================================================================
// �t�F�[�h�̕`�揈��
//=============================================================================
void CFade::Draw(void)
{
	//�����_�����O�̎擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

}

//=============================================================================
// �t�F�[�h�̐ݒ�
//=============================================================================
void CFade::SetFade(CManager::MODE modeNext, FADE fade)
{
	if (m_fade == FADE_NONE)
	{
		m_fade = FADE_OUT;
		m_modeNext = modeNext;
		m_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		if (fade == FADE_IN)
		{
			m_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.8f);
		}
	}
}
//=============================================================================
// �t�F�[�h�̎擾����
//=============================================================================
CFade::FADE CFade::GetFade(void)
{
	return m_fade;
}