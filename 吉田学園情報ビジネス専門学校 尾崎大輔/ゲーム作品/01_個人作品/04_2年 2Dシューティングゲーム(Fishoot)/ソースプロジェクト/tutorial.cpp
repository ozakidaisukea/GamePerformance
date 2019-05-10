//=============================================================================
//
// �`���[�g���A������ [tutorial.cpp]
// Author : Ozaki
//
//=============================================================================
#include "tutorial.h"
#include "manager.h"
#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "scene2D.h"
#include "input.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "explosion.h"
#include "bg.h"
#include "enemy.h"
#include "score.h"
#include "number.h"
#include "life.h"
#include "effect.h"
#include "sound.h"
#include "title.h"
#include "fade.h"
#include "item.h"
#include "logo.h"
#include "gauge.h"
#include "enter.h"
#include "joypad.h"

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
CPlayer*CTutorial::m_pPlayer = NULL;
CEnemy*CTutorial::m_pEnemy = NULL;
CScore*CTutorial::m_pScore = NULL;
CLife*CTutorial::m_pLife = NULL;
CItem*CTutorial::m_pItem = NULL;
CLogo*CTutorial::m_pLogo = NULL;

LPDIRECT3DTEXTURE9	CTutorial::m_pTexture = NULL;
LPDIRECT3DVERTEXBUFFER9 CTutorial::m_pVtxBuff = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTutorial::CTutorial()
{
	m_ItemTimer = 0;

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTutorial::~CTutorial()
{

}

//=============================================================================
// ���[�h
//=============================================================================
HRESULT CTutorial::Load(void)
{
	return S_OK;
}

//=============================================================================
// �A�����[�h
//=============================================================================
void CTutorial::Unload(void)
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
HRESULT CTutorial::Init(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = NULL;

	pDevice = CManager::GetRenderer()->GetDevice();

	m_nCounterTutorialState = 0;

	// �w�i�̓ǂݍ���
	CBg::Load();

	// �v���C���[�̓ǂݍ���
	CPlayer::Load();

	// �G�̓ǂݍ���
	CEnemy::Load();

	// �G�t�F�N�g�̓ǂݍ���
	CEffect::Load();

	// �e�̓ǂݍ���
	CBullet::Load();

	// �����̓ǂݍ���
	CExplosion::Load();

	// �A�C�e���̓ǂݍ���
	CItem::Load();

	// �i���o�[�̓ǂݍ���
	CNumber::Load();

	// ���C�t�̓ǂݍ���
	CLife::Load();

	// ���S�̓ǂݍ���
	CLogo::Load();

	// �Q�[�W�̓ǂݍ���
	CGauge::Load();

	// �G���^�[�̓ǂݍ���
	CEntor::Load();

	//=====================================����=======================================================

	// �w�i�̐���
	CBg::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0), 50.0f, SCREEN_WIDTH);

	// �v���C���[�̐��� [�V���P]
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(300, 600, 0), 100.0f, 100.0f);

	// �G�̐���			[���D]		[3�̖�]
	m_pEnemy = CEnemy::Create(D3DXVECTOR3(1300, 230, 0), 250.0f, 150.0f, D3DXVECTOR3(0.05f, 0.0f, 0.0f), 10, CEnemy::ENEMY_GYOSEN);

	// �X�R�A�̐���
	m_pScore = CScore::Create(D3DXVECTOR3(960, 30, 0), 30.0f, 20.0f);

	// ���C�t�̐���
	m_pLife = CLife::Create(D3DXVECTOR3(50, 50, 0), 50.0f, 50.0f);

	// ���S�̐���
	/*m_pLogo = */CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 50, 0), 200.0f, 100.0f, CLogo::LOGO_TUTORIAL);

	//CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 560, 0), 900.0f, 200.0f, CLogo::LOGO_TUTORIALHAKASE);

	// �Q�[�W�̐���
	CGauge::Create(D3DXVECTOR3(50, 80, 0), 100.0f, 100.0f);

	// �G���^�[�̐���
	CEntor::Create(D3DXVECTOR3(1070, 680, 0), 280.0f, 100.0f);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CTutorial::Uninit(void)
{
	CScene::ReleaseAll();
}

//=============================================================================
// �X�V����
//=============================================================================
void CTutorial::Update(void)
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

	m_ItemTimer++;

	if (m_ItemTimer == 240)
	{
		// �A�C�e���̐���	[0�m�[�}��]
		CItem::Create(D3DXVECTOR3(1450, 500, 0), D3DXVECTOR3(0.05f, 0.0f, 0.0f), 20.0f, 20.0f, CItem::ITEM_NORMAL0);

		// �A�C�e���̐���	[0���A]
		CItem::Create(D3DXVECTOR3(1450, 550, 0), D3DXVECTOR3(-0.05f, 0.0f, 0.0f), 20.0f, 20.0f, CItem::ITEM_HIGH0);

		// �A�C�e���̐���	[1�m�[�}��]
		CItem::Create(D3DXVECTOR3(1450, 600, 0), D3DXVECTOR3(0.05f, 0.0f, 0.0f), 20.0f, 20.0f, CItem::ITEM_NORMAL1);

		// �A�C�e���̐���	[1���A]
		CItem::Create(D3DXVECTOR3(1450, 650, 0), D3DXVECTOR3(-0.05f, 0.0f, 0.0f), 30.0f, 20.0f, CItem::ITEM_HIGH1);

		m_ItemTimer = 0;

	}

	if (CEnemy::m_nCounterEnemyState == 1)
	{
		m_nCounterTutorialState++;

		if (m_nCounterTutorialState >= 60)
		{
			if (pFade->GetFade() == CFade::FADE_NONE)
			{
				pFade->SetFade(CManager::MODE_GAME);
			}
		}
	}

	if (InputKeyboard->GetTrigger(DIK_RETURN) == true || InputJoypad->GetTrigger(CInputjoypad::DIJS_BOTTON_START) == true)
	{
		pFade->SetFade(CManager::MODE_GAME);

	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CTutorial::Draw(void)
{

}

//=============================================================================
// �`���[�g���A���̐���
//=============================================================================
CTutorial*CTutorial::Create(void)
{
	CTutorial *pTutorial;

	pTutorial = new CTutorial;

	pTutorial->Init();

	return pTutorial;
}

//=============================================================================
// �v���C���[�̎擾
//=============================================================================
CPlayer *CTutorial::GetPlayer(void)
{
	return m_pPlayer;
}

//=============================================================================
// �G�̎擾
//=============================================================================
CEnemy *CTutorial::GetEnemy(void)
{
	return m_pEnemy;
}

//=============================================================================
// �X�R�A�̎擾
//=============================================================================
CScore *CTutorial::GetScore(void)
{
	return m_pScore;
}

//=============================================================================
// ���C�t�̎擾
//=============================================================================
CLife *CTutorial::GetLife(void)
{
	return m_pLife;
}

//=============================================================================
// �A�C�e���̎擾
//=============================================================================
CItem *CTutorial::GetItem(void)
{
	return m_pItem;
}

//=============================================================================
// ���S�̎擾
//=============================================================================
CLogo *CTutorial::GetLogo(void)
{
	return m_pLogo;
}