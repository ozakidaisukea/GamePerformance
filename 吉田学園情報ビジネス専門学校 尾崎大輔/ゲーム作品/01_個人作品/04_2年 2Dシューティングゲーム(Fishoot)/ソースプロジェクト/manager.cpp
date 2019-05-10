//=============================================================================
//
// マネージャーの処理 [manager.cpp]
// Author : Ozaki
//
//=============================================================================
#include "manager.h"
#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "scene2D.h"
#include "input.h"
#include "sound.h"
#include "title.h"
#include "tutorial.h"
#include "game.h"
#include "result.h"
#include "gameover.h"
#include "ranking.h"
#include "fade.h"
#include "score.h"
#include "joypad.h"
#include "sousa.h"

//=============================================================================
// 静的メンバ-変数宣言
//=============================================================================
CRenderer*CManager::m_pRenderer = NULL;					// レンダラー
CInputKeyboard*CManager::m_pInputKeyboard = NULL;		// キーボード
CInputjoypad*CManager::m_pInputJoypad = NULL;			// パッド
CSound*CManager::m_pSound = NULL;						// サウンド
CTitle*CManager::m_pTitle = NULL;						// タイトル
CTutorial*CManager::m_pTutorial = NULL;					// チュートリアル
CGame*CManager::m_pGame = NULL;							// ゲーム
CResult*CManager::m_pResult = NULL;						// リザルト
CGameover*CManager::m_pGameover = NULL;					// ゲームオーバー
CRanking*CManager::m_pRanking = NULL;					// ランキング
CFade*CManager::m_pFade = NULL;							// フェード
CScore*CManager::m_pScore = NULL;						// スコア
CSousa*CManager::m_pSousa = NULL;						// 操作方法

int CManager::m_Rankingscore[MAX_RANKING] = {};			// ランキングのスコア

CManager::MODE CManager::m_mode;						// モード

//=============================================================================
// コンストラクタ
//=============================================================================
CManager::CManager()
{

}

//=============================================================================
// デストラクタ
//=============================================================================
CManager::~CManager()
{

}

//=============================================================================
// 入力処理
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{

	m_pRenderer = new CRenderer;
	m_pInputKeyboard = new CInputKeyboard;
	m_pInputJoypad = new CInputjoypad;
	m_pSound = new CSound;

	// 初期化処理
	if (FAILED(m_pRenderer->Init(hWnd, bWindow)))
	{
		return -1;
	}

	if (FAILED(m_pInputKeyboard->Init(hInstance,hWnd)))
	{
		return -1;
	}

	if (m_pInputJoypad != NULL)
	{
		m_pInputJoypad->Init(hInstance, hWnd);
	}

	m_pSound->InitSound(hWnd);

	// フェード生成
	m_pFade = CFade::Create();

	// モードの設定
	m_mode = MODE_TITLE;


	for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
	{
		m_Rankingscore[nCnt] = 0;
	}

	SetMode(m_mode);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CManager::Uninit(void)
{
	// 全ての終了を破棄
	CScene::ReleaseAll();

	// レンダラーを破棄
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Uninit();

		delete m_pRenderer;
		m_pRenderer = NULL;
	}

	// キーボードを破棄
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Uninit();

		delete m_pInputKeyboard;
		m_pInputKeyboard = NULL;
	}

	// パッドを破棄
	if (m_pInputJoypad != NULL)
	{
		m_pInputJoypad->Uninit();

		delete m_pInputJoypad;
		m_pInputJoypad = NULL;
	}

	// フェード
	if (m_pFade != NULL)
	{
		m_pFade->Uninit();

		delete m_pFade;
		m_pFade = NULL;
	}

	// サウンド
	if (m_pSound != NULL)
	{
		m_pSound->UninitSound();

		delete m_pSound;
		m_pSound = NULL;
	}

	// タイトル
	if (m_pTitle != NULL)
	{
		m_pTitle->Uninit();

		delete m_pTitle;
		m_pTitle = NULL;
	}

	// 操作方法
	if (m_pSousa != NULL)
	{
		m_pSousa->Uninit();

		delete m_pSousa;
		m_pSousa = NULL;
	}

	// チュートリアル
	if (m_pTutorial != NULL)
	{
		m_pTutorial->Uninit();

		delete m_pTutorial;
		m_pTutorial = NULL;
	}

	// ゲーム
	if (m_pGame != NULL)
	{
		m_pGame->Uninit();

		delete m_pGame;
		m_pGame = NULL;
	}

	// リザルト
	if (m_pResult != NULL)
	{
		m_pResult->Uninit();

		delete m_pResult;
		m_pResult = NULL;
	}

	// ゲームオーバー
	if (m_pGameover != NULL)
	{
		m_pGameover->Uninit();

		delete m_pGameover;
		m_pGameover = NULL;
	}

	// ランキング
	if (m_pRanking != NULL)
	{
		m_pRanking->Uninit();

		delete m_pRanking;
		m_pRanking = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void CManager::Update(void)
{
	// キーボードの更新
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Update();
	}

	// パッドの更新
	if (m_pInputJoypad != NULL)
	{
		m_pInputJoypad->Update();
	}

	// レンダラーの更新
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Update();
	}

	// フェードの更新
	if (m_pFade != NULL)
	{
		m_pFade->Update();
	}

	//更新の開始
	switch (m_mode)
	{
		// タイトル
	case MODE_TITLE:
		if (m_pTitle != NULL)
		{
 			m_pTitle->Update();
		}
		break;

		// 操作方法
	case MODE_SOUSA:
		if (m_pSousa != NULL)
		{
			m_pSousa->Update();
		}
		break;

		// チュートリアル
	case MODE_TUTORIAL:
		if (m_pTutorial != NULL)
		{
			m_pTutorial->Update();
		}
		break;

		// ゲーム
	case MODE_GAME:
		if (m_pGame != NULL)
		{
			m_pGame->Update();
		}
		break;

		// リザルト
	case MODE_RESULT:
		if (m_pResult != NULL)
		{
			m_pResult->Update();
		}
		break;

		// ゲームオーバー
	case MODE_GAMEOVER:
		if (m_pGameover != NULL)
		{
			m_pGameover->Update();
		}
		break;

		// ランキング
	case MODE_RANKING:
		if (m_pRanking != NULL)
		{
			m_pRanking->Update();
		}
		break;
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CManager::Draw(void)
{
	// キーボードを取得
	CSound *pSound;
	pSound = CManager::GetSound();

	// レンダラーの描画
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Draw();
	}

	//描画の開始
	switch (m_mode)
	{
		// タイトル
	case MODE_TITLE:
		if (m_pTitle != NULL)
		{
			m_pTitle->Draw();
		}
		break;

		// 操作方法
	case MODE_SOUSA:
		if (m_pSousa != NULL)
		{
			m_pSousa->Draw();
		}
		break;

		// チュートリアル
	case MODE_TUTORIAL:
		if (m_pTutorial != NULL)
		{
			m_pTutorial->Draw();
		}
		break;

		// ゲーム
	case MODE_GAME:
		if (m_pGame != NULL)
		{
			m_pGame->Draw();
		}
		break;

		// リザルト
	case MODE_RESULT:
		if (m_pResult != NULL)
		{
			m_pResult->Draw();
		}
		break;

		// ゲームオーバー
	case MODE_GAMEOVER:
		if (m_pGameover != NULL)
		{
			m_pGameover->Draw();
		}
		break;

		// ランキング
	case MODE_RANKING:
		if (m_pRanking != NULL)
		{
			m_pRanking->Draw();
		}
		break;
	}
}

//=============================================================================
// モードの設定処理
//=============================================================================
void CManager::SetMode(MODE mode)
{
	// サウンドを取得
	CSound *pSound;
	pSound = CManager::GetSound();

	// 終了
	switch (m_mode)
	{
		// タイトル
	case MODE_TITLE:
		if (m_pTitle != NULL)
		{
			m_pTitle->Uninit();

			pSound->StopSound(pSound->SOUND_LABEL_BGM_TITLE);
			delete m_pTitle;
			m_pTitle = NULL;
		}
		break;

		// チュートリアル
	case MODE_SOUSA:
		if (m_pSousa != NULL)
		{
			m_pSousa->Uninit();

			pSound->StopSound(pSound->SOUND_LABEL_BGM_TUTORIAL);
			delete m_pSousa;
			m_pSousa = NULL;
		}
		break;

		// チュートリアル
	case MODE_TUTORIAL:
		if (m_pTutorial != NULL)
		{
			m_pTutorial->Uninit();

			pSound->StopSound(pSound->SOUND_LABEL_BGM_TUTORIAL);
			delete m_pTutorial;
			m_pTutorial = NULL;
		}
		break;

		// ゲーム
	case MODE_GAME:
		if (m_pGame != NULL)
		{
			m_pGame->Uninit();

			pSound->StopSound(pSound->SOUND_LABEL_BGM_GAME);
			delete m_pGame;
		}
		m_pGame = NULL;
		break;

		// リザルト
	case MODE_RESULT:
		if (m_pResult != NULL)
		{
			m_pResult->Uninit();

			pSound->StopSound(pSound->SOUND_LABEL_BGM_RESULT);
			delete m_pResult;
		}
		m_pResult = NULL;
		break;

		// ゲームオーバー
	case MODE_GAMEOVER:
		if (m_pGameover != NULL)
		{
			m_pGameover->Uninit();

			pSound->StopSound(pSound->SOUND_LABEL_BGM_GAMEOVER);
			delete m_pGameover;
		}
		m_pGameover = NULL;
		break;

		// ランキング
	case MODE_RANKING:
		if (m_pRanking != NULL)
		{
			m_pRanking->Uninit();

			pSound->StopSound(pSound->SOUND_LABEL_BGM_RANKING);
			delete m_pRanking;
		}
		m_pRanking = NULL;
		break;
	}

	// 初期化
	switch (mode)
	{
		// タイトル
	case MODE_TITLE:
		if (m_pTitle == NULL)
		{
			m_pTitle = CTitle::Create();

			pSound->PlaySound(pSound->SOUND_LABEL_BGM_TITLE);
		}
		break;

		// 操作方法
	case MODE_SOUSA:
		if (m_pSousa == NULL)
		{
			m_pSousa = CSousa::Create();

			pSound->PlaySound(pSound->SOUND_LABEL_BGM_TUTORIAL);
		}
		break;

		// チュートリアル
	case MODE_TUTORIAL:
		if (m_pTutorial == NULL)
		{
			m_pTutorial = CTutorial::Create();

			pSound->PlaySound(pSound->SOUND_LABEL_BGM_TUTORIAL);
		}
		break;

		// ゲーム
	case MODE_GAME:
		if (m_pGame == NULL)
		{
			m_pGame = CGame::Create();

			pSound->PlaySound(pSound->SOUND_LABEL_BGM_GAME);
		}
		break;

		// リザルト
	case MODE_RESULT:
		if (m_pResult == NULL)
		{
			m_pResult = CResult::Create();

			pSound->PlaySound(pSound->SOUND_LABEL_BGM_RESULT);
		}
		break;

		// ゲームオーバー
	case MODE_GAMEOVER:
		if (m_pGameover == NULL)
		{
			m_pGameover = CGameover::Create();

			pSound->PlaySound(pSound->SOUND_LABEL_BGM_GAMEOVER);
		}
		break;

		// ランキング
	case MODE_RANKING:
		if (m_pRanking == NULL)
		{
			m_pRanking = CRanking::Create();

			pSound->PlaySound(pSound->SOUND_LABEL_BGM_RANKING);
		}
		break;
	}
	m_mode = mode;
}

//=============================================================================
// モードの取得
//=============================================================================
CManager::MODE CManager::GetMode(void)
{
	return m_mode;
}

//=============================================================================
// デバイスの取得
//=============================================================================
 CRenderer *CManager::GetRenderer(void)
{
	return m_pRenderer;
}

 //=============================================================================
 // キーボード取得
 //=============================================================================
 CInputKeyboard *CManager::GetInputKeyboard(void)
 {
	 return m_pInputKeyboard;
 }

 //=============================================================================
 // パッド取得
 //=============================================================================
 CInputjoypad *CManager::GetInputJoypad(void)
 {
	 return m_pInputJoypad;
 }

 //=============================================================================
 // サウンド取得
 //=============================================================================
 CSound *CManager::GetSound(void)
 {
	 return m_pSound;
 }

 //=============================================================================
 // フェードの取得
 //=============================================================================
 CFade *CManager::GetFade(void)
 {
	 return m_pFade;
 }

 //=============================================================================
 // スコアの取得
 //=============================================================================
 CScore *CManager::GetScore(void)
 {
	 return m_pScore;
 }

 //=============================================================================
 // チュートリアルの取得
 //=============================================================================
 CTutorial * CManager::GetTutorial(void)
 {
	 return m_pTutorial;
 }

 //=============================================================================
 // 操作方法の取得
 //=============================================================================
 CSousa * CManager::GetSousa(void)
 {
	 return m_pSousa;
 }

 //=============================================================================
 // ゲームの取得
 //=============================================================================
 CGame * CManager::GetGame(void)
 {
	 return m_pGame;
 }


 //=============================================================================
 // ランキングの並び替え
 //=============================================================================
 void CManager::RankingScore(int nScore)
 {
	 int nData = 0;

	 for (int nCnt = 4; nCnt >= 0; nCnt--)
	 {
		 if ((m_Rankingscore[nCnt] <= nScore))
		 {
			 m_Rankingscore[nCnt] = nScore;
			 break;
		 }
	 }

	 for (int nCount = 0; nCount < MAX_RANKING - 1; nCount++)
	 {
		 for (int nCount2 = nCount + 1; nCount2 < MAX_RANKING; nCount2++)
		 {
			 if (m_Rankingscore[nCount] < m_Rankingscore[nCount2])
			 {
  				 nData = m_Rankingscore[nCount];
				 m_Rankingscore[nCount] = m_Rankingscore[nCount2];
				 m_Rankingscore[nCount2] = nData;
			 }

		 }

	 }
 }

 //=============================================================================
 // スコアを渡す
 //=============================================================================
 int CManager::GetRankingScore(int nIdx)
 {
	 return m_Rankingscore[nIdx];
 }

