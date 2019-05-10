//=============================================================================
//
// マネージャーの処理 [manager.cpp]
// Author : Ozaki
//
//=============================================================================
#include "manager.h"
#include "main.h"
#include "renderer.h"
#include "input.h"
#include "scene.h"
#include "scene2D.h"
#include "scene3D.h"
#include "sceneX.h"
#include "sound.h"
#include "meshfield.h"
#include "camera.h"
#include "light.h"
#include "debugproc.h"
#include "billboard.h"
#include "player.h"
#include "meshorbit.h"
#include "fade.h"
#include "title.h"
#include "game.h"
#include "tutorial.h"
#include "result.h"
#include "joypad.h"

//=============================================================================
// 静的メンバ-変数宣言
//=============================================================================
CRenderer*CManager::m_pRenderer = NULL;
CInputKeyboard*CManager::m_pInputKeyboard = NULL;
CLight*CManager::m_pLight = NULL;
CScene3D*CManager::m_pScene3D = NULL;
CPlayer*CManager::m_pPlayer = NULL;
CMeshFiled*CManager::m_pMeshField = NULL;
CMeshOrbit*CManager::m_pMeshOrbit = NULL;
CSound*CManager::m_pSound = NULL;
CFade*CManager::m_pFade = NULL;
CTitle*CManager::m_pTitle = NULL;
CTutorial*CManager::m_pTutorial = NULL;
CGame*CManager::m_pGame = NULL;
CResult*CManager::m_pResult = NULL;
CRanking*CManager::m_pRanking = NULL;
CInputjoypad*CManager::m_pInputJoypad = NULL;
int	CManager::m_playertaime = NULL;
CCamera*CManager::m_pCamera = NULL;									  // カメラ

CManager::MODE CManager::m_mode = CManager::MODE_TITLE;		   		  // モード

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

	// 初期化処理
	if (FAILED(m_pInputKeyboard->Init(hInstance, hWnd)))
	{
		return -1;
	}
	if (m_pInputJoypad != NULL)
	{
		m_pInputJoypad->Init(hInstance, hWnd);
	}

	// デバックを取得
	CDebugProc *m_Dubug = CRenderer::GetDebug();

#ifdef DEBUG
	m_Dubug->Print("sss", " 1でScene2D削除\n", " 2でScene3D削除\n", " 3でSceneXを削除\n");

#endif // DEBUG

	m_pSound->InitSound(hWnd);

	// フェード生成
	m_pFade = CFade::Create();

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

	// サウンド
	if (m_pSound != NULL)
	{
		m_pSound->UninitSound();		// 音

		delete m_pSound;
		m_pSound = NULL;
	}

	// キーボードを破棄
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Uninit();		// キーボードを消す

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

	// フェードの破棄
	if (m_pFade != NULL)
	{
		m_pFade->Uninit();

		delete m_pFade;
		m_pFade = NULL;
	}

	// タイトル
	if (m_pTitle != NULL)
	{
		m_pTitle->Uninit();

		delete m_pTitle;
		m_pTitle = NULL;
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

	// NULLチェック
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Uninit();			// レンダラーを消す

		delete m_pRenderer;
		m_pRenderer = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void CManager::Update(void)
{
#ifdef _DEBUG
	// 文字列を消す
	CDebugProc::ResetStr();

	// デバックを取得
	CDebugProc *m_Dubug = CRenderer::GetDebug();

	m_playertaime++;

#endif

	// NULLチェック
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Update();		// キーボードを更新
	}

	// パッドの更新
	if (m_pInputJoypad != NULL)
	{
		m_pInputJoypad->Update();		// パッドを更新
	}

	// NULLチェック
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Update();			// レンダラーを更新
	}

	// NULLチェック
	if (m_pFade != NULL)
	{
		m_pFade->Update();				// フェードを更新
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
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CManager::Draw(void)
{
	// NULLチェック
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Draw();			// レンダラーの描画
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
			m_pGame = NULL;
		}
		break;

		// リザルト
	case MODE_RESULT:
		if (m_pResult != NULL)
		{
			m_pResult->Uninit();

			pSound->StopSound(pSound->SOUND_LABEL_BGM_RESULT);
			delete m_pResult;
			m_pResult = NULL;
		}
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
			//CGame::Create();
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
// サウンドの取得
//=============================================================================
CSound * CManager::GetSound(void)
{
	return m_pSound;
}

//=============================================================================
// デバイスの取得
//=============================================================================
 CRenderer *CManager::GetRenderer(void)
{
	return m_pRenderer;					// レンダラーを返す
}
 //=============================================================================
 // キーボードの取得
 //=============================================================================
 CInputKeyboard *CManager::GetInputKeyboard(void)
 {
	 return m_pInputKeyboard;			// キーボードを返す
 }

 //=============================================================================
 // タイトルの取得
 //=============================================================================
 CTitle * CManager::GetTitle(void)
 {
	 return m_pTitle;
 }

 //=============================================================================
 // チュートリアルの取得
 //=============================================================================
 CTutorial * CManager::GetTutorial(void)
 {
	 return m_pTutorial;
 }

 //=============================================================================
 // ゲームの取得
 //=============================================================================
 CGame * CManager::GetGame(void)
 {
	 return m_pGame;
 }

 //=============================================================================
 // リザルトの取得
 //=============================================================================
 CResult * CManager::GetResult(void)
 {
	 return m_pResult;
 }
 //=============================================================================
 // SCcene3Dの取得
 //=============================================================================
 CScene3D * CManager::GetScene3D(void)
 {
	 return m_pScene3D;					// シーン3Dを返す
 }

 //=============================================================================
 // プレイヤーの取得
 //=============================================================================
 CPlayer * CManager::GetPlayer(void)
 {
	 return m_pPlayer;					// プレイヤーを返す
 }

 //=============================================================================
 // フェードの取得
 //=============================================================================
 CFade * CManager::GetFade(void)
 {
	 return m_pFade;
 }

 //=============================================================================
 // メッシュフィールドの取得
 //=============================================================================
 CMeshFiled * CManager::GetMeshField(void)
 {
	 return m_pMeshField;				// メッシュフィールドを返す
 }

 //=============================================================================
 // メッシュオービットの取得
 //=============================================================================
 CMeshOrbit * CManager::GetMeshOrbit(void)
 {
	 return m_pMeshOrbit;
 }

 //=============================================================================
 // ジョイパッドの取得
 //=============================================================================
 CInputjoypad * CManager::GetInputJoypad(void)
 {
	 return m_pInputJoypad;
 }

 //=============================================================================
 // ライトの取得
 //=============================================================================
 CLight * CManager::GetLight(void)
 {
	 return m_pLight;
 }

