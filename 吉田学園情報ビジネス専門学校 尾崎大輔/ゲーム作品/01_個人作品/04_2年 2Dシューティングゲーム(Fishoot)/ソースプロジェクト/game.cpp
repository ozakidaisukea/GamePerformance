//=============================================================================
//
// �Q�[������ [game.cpp]
// Author : Ozaki
//
//=============================================================================
#include "game.h"
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
#include "gauge.h"
#include "pause.h"

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
CPlayer*CGame::m_pPlayer = NULL;
CEnemy*CGame::m_pEnemy[MAX_ENEMY] = {};
CScore*CGame::m_pScore = NULL;
CLife*CGame::m_pLife = NULL;
CItem*CGame::m_pItem = NULL;
CGauge*CGame::m_pGauge[MAX_GAUGE] = {};

CGame::STATE CGame::m_State = CGame::STATE_NONE;

LPDIRECT3DTEXTURE9	CGame::m_pTexture = NULL;
LPDIRECT3DVERTEXBUFFER9 CGame::m_pVtxBuff = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CGame::CGame()
{
	m_nNumEnemy = 0;
	m_nIndex = 0;
	m_nNumEnemyAll = MAX_ENEMY;
	m_nCounterGameState = 0;
	m_ItemTimer = 0;
	m_State = STATE_NORMAL;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CGame::~CGame()
{

}

//=============================================================================
// ���[�h
//=============================================================================
void CGame::Load(void)
{

}

//=============================================================================
// �A�����[�h
//=============================================================================
void CGame::Unload(void)
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
void CGame::Init(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = NULL;

	pDevice = CManager::GetRenderer()->GetDevice();

	//===================================
	// �ǂݍ��ݗ�
	//===================================

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

	// �Q�[�W�̓ǂݍ���
	CGauge::Load();

	//===================================
	// ������
	//===================================

	// �w�i�̐���
	CBg::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0), 50.0f, SCREEN_WIDTH);

	// �v���C���[�̐��� [�V���P]
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(300, 600, 0), 100.0f, 100.0f);

	// �G�̐���
	SetEnemy();

	// �X�R�A�̐���
	m_pScore = CScore::Create(D3DXVECTOR3(960, 30, 0), 30.0f, 20.0f);

	// ���C�t�̐���
	m_pLife = CLife::Create(D3DXVECTOR3(50, 50, 0), 50.0f, 50.0f);

	// �Q�[�W�̐���
	CGauge::Create(D3DXVECTOR3(50, 80, 0), 100.0f, 100.0f);
}

//=============================================================================
// �I������
//=============================================================================
void CGame::Uninit(void)
{
	CScene::ReleaseAll();
}

//=============================================================================
// �X�V����
//=============================================================================
void CGame::Update(void)
{
	// �L�[�{�[�h���擾
	CInputKeyboard *InputKeyboard;
	InputKeyboard = CManager::GetInputKeyboard();

	// �t�F�[�h���擾
	CFade *pFade;
	pFade = CManager::GetFade();

	m_ItemTimer++;

	if (m_ItemTimer == 540)
	{
		// �A�C�e���̐��� [0�m�[�}��]
		CItem::Create(D3DXVECTOR3(1450, 500, 0), D3DXVECTOR3(0.05f, 0.0f, 0.0f), 20.0f, 20.0f, CItem::ITEM_NORMAL0);

		// �A�C�e���̐��� [1�m�[�}��]
		CItem::Create(D3DXVECTOR3(1450, 600, 0), D3DXVECTOR3(0.05f, 0.0f, 0.0f), 20.0f, 20.0f, CItem::ITEM_NORMAL1);

		// �A�C�e���̐��� [1���A]
		CItem::Create(D3DXVECTOR3(1450, 650, 0), D3DXVECTOR3(-0.05f, 0.0f, 0.0f), 30.0f, 20.0f, CItem::ITEM_HIGH1);

		m_ItemTimer = 0;
	}

	if (m_State == STATE_RESULT)
	{
		m_nCounterGameState++;

		if (m_nCounterGameState >= 60)
		{
			if (pFade->GetFade() == CFade::FADE_NONE)
			{
				// �X�R�A�̒l���擾
				CManager::RankingScore(m_pScore->GetScore());
				pFade->SetFade(CManager::MODE_RESULT);
			}
		}
	}
	else if (m_State == STATE_GAMEOVER)
	{

		m_nCounterGameState++;

		if (m_nCounterGameState >= 60)
		{
			if (pFade->GetFade() == CFade::FADE_NONE)
			{
				// �X�R�A�̒l���擾
				CManager::RankingScore(m_pScore->GetScore());
				pFade->SetFade(CManager::MODE_GAMEOVER);
			}
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CGame::Draw(void)
{

}

//=============================================================================
// �Q�[���̐���
//=============================================================================
CGame*CGame::Create(void)
{
	CGame *pGame;

	pGame = new CGame;

	pGame->Init();

	return pGame;
}

//=============================================================================
// �v���C���[�̎擾
//=============================================================================
CPlayer *CGame::GetPlayer(void)
{
	return m_pPlayer;
}

//=============================================================================
// �G�̎擾
//=============================================================================
CEnemy *CGame::GetEnemy(int nIdx)
{
	CEnemy *pEnemy = m_pEnemy[0];

	if (pEnemy == NULL)
	{
		return NULL;
	}

	return pEnemy;
}


//=============================================================================
// �G�̐ݒ�
//=============================================================================
void CGame::SetEnemy(int nIdx, CEnemy* pEnemy)
{
	m_pEnemy[nIdx] = pEnemy;
}

//=============================================================================
// �X�R�A�̎擾
//=============================================================================
CScore *CGame::GetScore(void)
{
	return m_pScore;
}

//=============================================================================
// ���C�t�̎擾
//=============================================================================
CLife *CGame::GetLife(void)
{
	return m_pLife;
}

//=============================================================================
// �A�C�e���̎擾
//=============================================================================
CItem *CGame::GetItem(void)
{
	return m_pItem;
}

//=============================================================================
// �Q�[�W�̎擾
//=============================================================================
CGauge *CGame::GetGauge(void)
{
	return m_pGauge[0];
}

//=============================================================================
// �G�̐����擾
//=============================================================================
int CGame::GetNumEnemy(void)
{
	return m_nNumEnemy;
}

//=============================================================================
// �S�Ă̓G�̐����擾
//=============================================================================
int CGame::GetNumEnemyAll(void)
{
	return m_nNumEnemyAll;
}

//=============================================================================
// ��Ԃ̐ݒ�
//=============================================================================
void CGame::SetState(STATE state)
{
	m_State = state;
}

//=============================================================================
// �G�̐��̐ݒ�
//=============================================================================
void CGame::SetNumEnemy(int nNumEnemy)
{
	m_nNumEnemy = nNumEnemy;
}

//=============================================================================
// �S�ēG�̐��̐ݒ�
//=============================================================================
void CGame::SetNumEnemyAll(int nNumEnemyAll)
{
	m_nNumEnemyAll = nNumEnemyAll;
}

//=============================================================================
// �G�̐ݒ�
//=============================================================================
void CGame::SetEnemy(void)
{
	switch (m_nIndex)
	{
	case 0:
		SetEnemy00();
		break;
	case 1:
		SetEnemy01();
		break;
	case 2:
		SetEnemy02();
		break;
	case 3:
		SetEnemy03();
		break;
	case 4:
		SetEnemy04();
		break;
	}
	m_nIndex++;
}

//=============================================================================
// �G1�̖�
//=============================================================================
void CGame::SetEnemy00(void)
{
	// �G�̐��� [��]	[1�̖�]
	m_pEnemy[0] = CEnemy::Create(D3DXVECTOR3(1300, 150, 0), 100.0f, 100.0f, D3DXVECTOR3(0.05f, 0.0f, 0.0f), ENEMYLIFE_NO1, CEnemy::ENEMY_TORI);
}

//=============================================================================
// �G2�̖�
//=============================================================================
void CGame::SetEnemy01(void)
{
	// �G�̐��� [�o�C�N]	[2�̖�]
	m_pEnemy[0] = CEnemy::Create(D3DXVECTOR3(1400, 280, 0), 100.0f, 100.0f, D3DXVECTOR3(0.05f, 0.0f, 0.0f), ENEMYLIFE_NO2, CEnemy::ENEMY_BIKE);
}

//=============================================================================
// �G3�̖�
//=============================================================================
void CGame::SetEnemy02(void)
{
	// �G�̐��� [�{�[�h]		[3�̖�]
	m_pEnemy[0] = CEnemy::Create(D3DXVECTOR3(1400, 260, 0), 110.0f, 100.0f, D3DXVECTOR3(0.05f, 0.0f, 0.0f), ENEMYLIFE_NO3, CEnemy::ENEMY_BOARD);
}

//=============================================================================
// �G4�̖�
//=============================================================================
void CGame::SetEnemy03(void)
{
	// �G�̐���	[���D]	[4�̖�]
	m_pEnemy[0] = CEnemy::Create(D3DXVECTOR3(1400, 230, 0), 250.0f, 150.0f, D3DXVECTOR3(0.05f, 0.0f, 0.0f), ENEMYLIFE_NO4, CEnemy::ENEMY_GYOSEN);
}

//=============================================================================
// �G5�̖�
//=============================================================================
void CGame::SetEnemy04(void)
{
	// �G�̐��� [�F���D]	[5�̖�]
	m_pEnemy[0] = CEnemy::Create(D3DXVECTOR3(1400, 150, 0), 200.0f, 100.0f, D3DXVECTOR3(0.05f,0.0f, 0.0f), ENEMYLIFE_NO5, CEnemy::ENEMY_UTYUSEN);
}
