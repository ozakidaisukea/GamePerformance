//=============================================================================
//
// ゲーム処理 [game.cpp]
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
// 静的メンバ変数
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
// コンストラクタ
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
// デストラクタ
//=============================================================================
CGame::~CGame()
{

}

//=============================================================================
// ロード
//=============================================================================
void CGame::Load(void)
{

}

//=============================================================================
// アンロード
//=============================================================================
void CGame::Unload(void)
{
	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();

		m_pTexture = NULL;
	}
}

//=============================================================================
// 初期化処理
//=============================================================================
void CGame::Init(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = NULL;

	pDevice = CManager::GetRenderer()->GetDevice();

	//===================================
	// 読み込み類
	//===================================

	// 背景の読み込み
	CBg::Load();

	// プレイヤーの読み込み
	CPlayer::Load();

	// 敵の読み込み
	CEnemy::Load();

	// エフェクトの読み込み
	CEffect::Load();

	// 弾の読み込み
	CBullet::Load();

	// 爆発の読み込み
	CExplosion::Load();

	// アイテムの読み込み
	CItem::Load();

	// ナンバーの読み込み
	CNumber::Load();

	// ライフの読み込み
	CLife::Load();

	// ゲージの読み込み
	CGauge::Load();

	//===================================
	// 生成類
	//===================================

	// 背景の生成
	CBg::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0), 50.0f, SCREEN_WIDTH);

	// プレイヤーの生成 [シャケ]
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(300, 600, 0), 100.0f, 100.0f);

	// 敵の生成
	SetEnemy();

	// スコアの生成
	m_pScore = CScore::Create(D3DXVECTOR3(960, 30, 0), 30.0f, 20.0f);

	// ライフの生成
	m_pLife = CLife::Create(D3DXVECTOR3(50, 50, 0), 50.0f, 50.0f);

	// ゲージの生成
	CGauge::Create(D3DXVECTOR3(50, 80, 0), 100.0f, 100.0f);
}

//=============================================================================
// 終了処理
//=============================================================================
void CGame::Uninit(void)
{
	CScene::ReleaseAll();
}

//=============================================================================
// 更新処理
//=============================================================================
void CGame::Update(void)
{
	// キーボードを取得
	CInputKeyboard *InputKeyboard;
	InputKeyboard = CManager::GetInputKeyboard();

	// フェードを取得
	CFade *pFade;
	pFade = CManager::GetFade();

	m_ItemTimer++;

	if (m_ItemTimer == 540)
	{
		// アイテムの生成 [0ノーマル]
		CItem::Create(D3DXVECTOR3(1450, 500, 0), D3DXVECTOR3(0.05f, 0.0f, 0.0f), 20.0f, 20.0f, CItem::ITEM_NORMAL0);

		// アイテムの生成 [1ノーマル]
		CItem::Create(D3DXVECTOR3(1450, 600, 0), D3DXVECTOR3(0.05f, 0.0f, 0.0f), 20.0f, 20.0f, CItem::ITEM_NORMAL1);

		// アイテムの生成 [1レア]
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
				// スコアの値を取得
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
				// スコアの値を取得
				CManager::RankingScore(m_pScore->GetScore());
				pFade->SetFade(CManager::MODE_GAMEOVER);
			}
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CGame::Draw(void)
{

}

//=============================================================================
// ゲームの生成
//=============================================================================
CGame*CGame::Create(void)
{
	CGame *pGame;

	pGame = new CGame;

	pGame->Init();

	return pGame;
}

//=============================================================================
// プレイヤーの取得
//=============================================================================
CPlayer *CGame::GetPlayer(void)
{
	return m_pPlayer;
}

//=============================================================================
// 敵の取得
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
// 敵の設定
//=============================================================================
void CGame::SetEnemy(int nIdx, CEnemy* pEnemy)
{
	m_pEnemy[nIdx] = pEnemy;
}

//=============================================================================
// スコアの取得
//=============================================================================
CScore *CGame::GetScore(void)
{
	return m_pScore;
}

//=============================================================================
// ライフの取得
//=============================================================================
CLife *CGame::GetLife(void)
{
	return m_pLife;
}

//=============================================================================
// アイテムの取得
//=============================================================================
CItem *CGame::GetItem(void)
{
	return m_pItem;
}

//=============================================================================
// ゲージの取得
//=============================================================================
CGauge *CGame::GetGauge(void)
{
	return m_pGauge[0];
}

//=============================================================================
// 敵の数を取得
//=============================================================================
int CGame::GetNumEnemy(void)
{
	return m_nNumEnemy;
}

//=============================================================================
// 全ての敵の数を取得
//=============================================================================
int CGame::GetNumEnemyAll(void)
{
	return m_nNumEnemyAll;
}

//=============================================================================
// 状態の設定
//=============================================================================
void CGame::SetState(STATE state)
{
	m_State = state;
}

//=============================================================================
// 敵の数の設定
//=============================================================================
void CGame::SetNumEnemy(int nNumEnemy)
{
	m_nNumEnemy = nNumEnemy;
}

//=============================================================================
// 全て敵の数の設定
//=============================================================================
void CGame::SetNumEnemyAll(int nNumEnemyAll)
{
	m_nNumEnemyAll = nNumEnemyAll;
}

//=============================================================================
// 敵の設定
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
// 敵1体目
//=============================================================================
void CGame::SetEnemy00(void)
{
	// 敵の生成 [鳥]	[1体目]
	m_pEnemy[0] = CEnemy::Create(D3DXVECTOR3(1300, 150, 0), 100.0f, 100.0f, D3DXVECTOR3(0.05f, 0.0f, 0.0f), ENEMYLIFE_NO1, CEnemy::ENEMY_TORI);
}

//=============================================================================
// 敵2体目
//=============================================================================
void CGame::SetEnemy01(void)
{
	// 敵の生成 [バイク]	[2体目]
	m_pEnemy[0] = CEnemy::Create(D3DXVECTOR3(1400, 280, 0), 100.0f, 100.0f, D3DXVECTOR3(0.05f, 0.0f, 0.0f), ENEMYLIFE_NO2, CEnemy::ENEMY_BIKE);
}

//=============================================================================
// 敵3体目
//=============================================================================
void CGame::SetEnemy02(void)
{
	// 敵の生成 [ボード]		[3体目]
	m_pEnemy[0] = CEnemy::Create(D3DXVECTOR3(1400, 260, 0), 110.0f, 100.0f, D3DXVECTOR3(0.05f, 0.0f, 0.0f), ENEMYLIFE_NO3, CEnemy::ENEMY_BOARD);
}

//=============================================================================
// 敵4体目
//=============================================================================
void CGame::SetEnemy03(void)
{
	// 敵の生成	[漁船]	[4体目]
	m_pEnemy[0] = CEnemy::Create(D3DXVECTOR3(1400, 230, 0), 250.0f, 150.0f, D3DXVECTOR3(0.05f, 0.0f, 0.0f), ENEMYLIFE_NO4, CEnemy::ENEMY_GYOSEN);
}

//=============================================================================
// 敵5体目
//=============================================================================
void CGame::SetEnemy04(void)
{
	// 敵の生成 [宇宙船]	[5体目]
	m_pEnemy[0] = CEnemy::Create(D3DXVECTOR3(1400, 150, 0), 200.0f, 100.0f, D3DXVECTOR3(0.05f,0.0f, 0.0f), ENEMYLIFE_NO5, CEnemy::ENEMY_UTYUSEN);
}
