//=============================================================================
//
// �����L���O���� [ranking.cpp]
// Author : Ozaki
//
//=============================================================================
#include "ranking.h"
#include "manager.h"
#include "renderer.h"
#include "fade.h"
#include "bg.h"
#include "logo.h"
#include "score.h"
#include "number.h"
#include "joypad.h"

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9	CRanking::m_pTexture = NULL;
LPDIRECT3DVERTEXBUFFER9 CRanking::m_pVtxBuff = NULL;

CScore*CRanking::m_apScore[MAX_RANKING] = {};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CRanking::CRanking()
{
	m_rankingtimer = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CRanking::~CRanking()
{

}

//=============================================================================
// ���[�h
//=============================================================================
HRESULT CRanking::Load(void)
{
	CRenderer *pRenderer;

	pRenderer = new CRenderer;

	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = NULL;

	pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\game\\mizu.png",
		&m_pTexture);

	return S_OK;
}

//=============================================================================
// �A�����[�h
//=============================================================================
void CRanking::Unload(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();

		m_pTexture = NULL;
	}
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CRanking::Init(void)
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

	// �w�i�̓ǂݍ���
	CBg::Load();

	// ���S�̓ǂݍ���
	CLogo::Load();

	// �X�R�A�̓ǂݍ���
	CNumber::Load();

	// �w�i�̐���
	CBg::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0), 10.0f, SCREEN_WIDTH);

	// ���S�̐���
	CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 50, 0), 500.0f, 80.0f, CLogo::LOGO_RANKING);

	// 1��
	CLogo::Create(D3DXVECTOR3(400, 170, 0), 70.0f, 70.0f, CLogo::LOGO_1);

	// 2��
	CLogo::Create(D3DXVECTOR3(400, 290, 0), 70.0f, 70.0f, CLogo::LOGO_2);

	// 3��
	CLogo::Create(D3DXVECTOR3(400, 390, 0), 70.0f, 70.0f, CLogo::LOGO_3);

	// 4��
	CLogo::Create(D3DXVECTOR3(400, 490, 0), 60.0f, 60.0f, CLogo::LOGO_4);

	// 5��
	CLogo::Create(D3DXVECTOR3(400, 590, 0), 60.0f, 60.0f, CLogo::LOGO_5);

	float pos = 150;
	int	  aScore[MAX_RANKING] = {};

	// �X�R�A
	for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
	{
		aScore[nCnt] = CManager::GetRankingScore(nCnt);

		m_apScore[nCnt] = CScore::Create(D3DXVECTOR3(700.0f, pos + 30, 0.0f), 30.0f, 50.0f);

		// �X�R�A���Z
		m_apScore[nCnt]->AddScore(aScore[nCnt]);

		pos += 100;
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CRanking::Uninit(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();

		m_pTexture = NULL;
	}

	for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
	{
		if (m_apScore[nCnt] != NULL)
		{
			m_apScore[nCnt]->ReleaseAll();

			m_apScore[nCnt] = NULL;
		}
	}

	CScene::ReleaseAll();
}

//=============================================================================
// �X�V����
//=============================================================================
void CRanking::Update(void)
{
	// �L�[�{�[�h���擾
	CInputKeyboard *InputKeyboard;
	InputKeyboard = CManager::GetInputKeyboard();

	// �L�[�{�[�h���擾
	CInputjoypad *InputJoypad;
	InputJoypad = CManager::GetInputJoypad();

	// �t�F�[�h���擾
	CFade *pFade;
	pFade = CManager::GetFade();

	m_rankingtimer++;

	if (pFade->GetFade() == CFade::FADE_NONE)
	{
		if (InputKeyboard->GetTrigger(DIK_RETURN) == true ||
			InputJoypad->GetPress(CInputjoypad::DIJS_BOTTON_START) == true || InputJoypad->GetTrigger(CInputjoypad::DIJS_BOTTON_B) == true)
		{
			pFade->SetFade(CManager::MODE_TITLE);
		}

		if (m_rankingtimer == 500)
		{
			pFade->SetFade(CManager::MODE_TITLE);
			m_rankingtimer = 0;
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CRanking::Draw(void)
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
// �����L���O�̐���
//=============================================================================
CRanking*CRanking::Create(void)
{
	CRanking *pRanking;

	pRanking = new CRanking;

	pRanking->Init();

	return pRanking;
}