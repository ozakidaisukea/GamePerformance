//=============================================================================
//
// チュートリアル処理 [tutorial.cpp]
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
// 静的メンバ変数
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
// コンストラクタ
//=============================================================================
CTutorial::CTutorial()
{
	m_ItemTimer = 0;

}

//=============================================================================
// デストラクタ
//=============================================================================
CTutorial::~CTutorial()
{

}

//=============================================================================
// ロード
//=============================================================================
HRESULT CTutorial::Load(void)
{
	return S_OK;
}

//=============================================================================
// アンロード
//=============================================================================
void CTutorial::Unload(void)
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
HRESULT CTutorial::Init(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = NULL;

	pDevice = CManager::GetRenderer()->GetDevice();

	m_nCounterTutorialState = 0;

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

	// ロゴの読み込み
	CLogo::Load();

	// ゲージの読み込み
	CGauge::Load();

	// エンターの読み込み
	CEntor::Load();

	//=====================================生成=======================================================

	// 背景の生成
	CBg::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0), 50.0f, SCREEN_WIDTH);

	// プレイヤーの生成 [シャケ]
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(300, 600, 0), 100.0f, 100.0f);

	// 敵の生成			[漁船]		[3体目]
	m_pEnemy = CEnemy::Create(D3DXVECTOR3(1300, 230, 0), 250.0f, 150.0f, D3DXVECTOR3(0.05f, 0.0f, 0.0f), 10, CEnemy::ENEMY_GYOSEN);

	// スコアの生成
	m_pScore = CScore::Create(D3DXVECTOR3(960, 30, 0), 30.0f, 20.0f);

	// ライフの生成
	m_pLife = CLife::Create(D3DXVECTOR3(50, 50, 0), 50.0f, 50.0f);

	// ロゴの生成
	/*m_pLogo = */CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 50, 0), 200.0f, 100.0f, CLogo::LOGO_TUTORIAL);

	//CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 560, 0), 900.0f, 200.0f, CLogo::LOGO_TUTORIALHAKASE);

	// ゲージの生成
	CGauge::Create(D3DXVECTOR3(50, 80, 0), 100.0f, 100.0f);

	// エンターの生成
	CEntor::Create(D3DXVECTOR3(1070, 680, 0), 280.0f, 100.0f);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CTutorial::Uninit(void)
{
	CScene::ReleaseAll();
}

//=============================================================================
// 更新処理
//=============================================================================
void CTutorial::Update(void)
{
	// キーボードを取得
	CInputKeyboard *InputKeyboard;
	InputKeyboard = CManager::GetInputKeyboard();

	// キーボードを取得
	CInputjoypad *InputJoypad;
	InputJoypad = CManager::GetInputJoypad();

	// フェードを取得
	CFade *pFade;
	pFade = CManager::GetFade();

	m_ItemTimer++;

	if (m_ItemTimer == 240)
	{
		// アイテムの生成	[0ノーマル]
		CItem::Create(D3DXVECTOR3(1450, 500, 0), D3DXVECTOR3(0.05f, 0.0f, 0.0f), 20.0f, 20.0f, CItem::ITEM_NORMAL0);

		// アイテムの生成	[0レア]
		CItem::Create(D3DXVECTOR3(1450, 550, 0), D3DXVECTOR3(-0.05f, 0.0f, 0.0f), 20.0f, 20.0f, CItem::ITEM_HIGH0);

		// アイテムの生成	[1ノーマル]
		CItem::Create(D3DXVECTOR3(1450, 600, 0), D3DXVECTOR3(0.05f, 0.0f, 0.0f), 20.0f, 20.0f, CItem::ITEM_NORMAL1);

		// アイテムの生成	[1レア]
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
// 描画処理
//=============================================================================
void CTutorial::Draw(void)
{

}

//=============================================================================
// チュートリアルの生成
//=============================================================================
CTutorial*CTutorial::Create(void)
{
	CTutorial *pTutorial;

	pTutorial = new CTutorial;

	pTutorial->Init();

	return pTutorial;
}

//=============================================================================
// プレイヤーの取得
//=============================================================================
CPlayer *CTutorial::GetPlayer(void)
{
	return m_pPlayer;
}

//=============================================================================
// 敵の取得
//=============================================================================
CEnemy *CTutorial::GetEnemy(void)
{
	return m_pEnemy;
}

//=============================================================================
// スコアの取得
//=============================================================================
CScore *CTutorial::GetScore(void)
{
	return m_pScore;
}

//=============================================================================
// ライフの取得
//=============================================================================
CLife *CTutorial::GetLife(void)
{
	return m_pLife;
}

//=============================================================================
// アイテムの取得
//=============================================================================
CItem *CTutorial::GetItem(void)
{
	return m_pItem;
}

//=============================================================================
// ロゴの取得
//=============================================================================
CLogo *CTutorial::GetLogo(void)
{
	return m_pLogo;
}