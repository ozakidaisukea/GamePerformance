//=============================================================================
//
// タイトル処理 [title.cpp]
// Author : Ozaki
//
//=============================================================================
#include "result.h"
#include "manager.h"
#include "renderer.h"
#include "sound.h"
#include "pressentor.h"
#include "fade.h"
#include "input.h"
#include "camera.h"
#include "light.h"
#include "debugproc.h"
#include "meshfield.h"
#include "union.h"
#include "scene2D.h"
#include "logo.h"
#include "player.h"			// プレイヤー
#include "jockey.h"			// ジョッキー
#include "horse2.h"			// 馬２
#include "horse3.h"
#include "horse4.h"
#include "horse5.h"
#include "horse6.h"
#include "horse7.h"
#include "horse8.h"
#include "horse9.h"
#include "horse10.h"
#include "jockey2.h"
#include "jockey3.h"
#include "jockey4.h"
#include "jockey5.h"
#include "jockey6.h"
#include "jockey7.h"
#include "jockey8.h"
#include "jockey9.h"
#include "jockey10.h"
#include "union.h"
#include "joypad.h"

//=============================================================================
// 静的メンバ変数
//=============================================================================
LPDIRECT3DTEXTURE9	CResult::m_pTexture = NULL;
LPDIRECT3DVERTEXBUFFER9 CResult::m_pVtxBuff = NULL;
CSound*CResult::m_pSound = NULL;
CCamera*CResult::m_pCamera = NULL;
CLight*CResult::m_pLight = NULL;
CMeshFiled*CResult::m_pMeshFiled = NULL;
CLogo*CResult::m_pLogo = NULL;

CPlayer*CResult::m_pPlayer = NULL;
CHorse2*CResult::m_pHorse2 = NULL;
CHorse3*CResult::m_pHorse3 = NULL;
CHorse4*CResult::m_pHorse4 = NULL;
CHorse5*CResult::m_pHorse5 = NULL;
CHorse6*CResult::m_pHorse6 = NULL;
CHorse7*CResult::m_pHorse7 = NULL;
CHorse8*CResult::m_pHorse8 = NULL;
CHorse9*CResult::m_pHorse9 = NULL;
CHorse10*CResult::m_pHorse10 = NULL;
CJockey*CResult::m_pJockey = NULL;
CJockey2*CResult::m_pJockey2 = NULL;
CJockey3*CResult::m_pJockey3 = NULL;
CJockey4*CResult::m_pJockey4 = NULL;
CJockey5*CResult::m_pJockey5 = NULL;
CJockey6*CResult::m_pJockey6 = NULL;
CJockey7*CResult::m_pJockey7 = NULL;
CJockey8*CResult::m_pJockey8 = NULL;
CJockey9*CResult::m_pJockey9 = NULL;
CJockey10*CResult::m_pJockey10 = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CResult::CResult()
{
	// ランキングに切り替えるタイマー
	m_Titletimer = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CResult::~CResult()
{

}

//=============================================================================
// ロード
//=============================================================================
void CResult::Load(void)
{
	CRenderer *pRenderer;

	pRenderer = new CRenderer;

	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = NULL;

	pDevice = CManager::GetRenderer()->GetDevice();
}

//=============================================================================
// アンロード
//=============================================================================
void CResult::Unload(void)
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
void CResult::Init(void)
{
	m_pCamera = new CCamera;
	m_pLight = new CLight;

	//============================================================================================================================
	// 読み込み類
	//============================================================================================================================

	// カメラの初期化
	m_pCamera->Init();

	// カメラを取得
	m_pCamera->SetMode(CCamera::MODE_RESULT);

	// ライトの初期化
	m_pLight->Init();

	CUnion::Load();

	// ロゴの初期化
	m_pLogo->Load();

	// 馬の読み込み
	CHorse2::Load();
	// 馬の読み込み
	CHorse3::Load();
	// 馬の読み込み
	CHorse4::Load();
	// 馬の読み込み
	CHorse5::Load();
	// 馬の読み込み
	CHorse6::Load();
	// 馬の読み込み
	CHorse7::Load();
	// 馬の読み込み
	CHorse8::Load();
	// 馬の読み込み
	CHorse9::Load();
	// 馬の読み込み
	CHorse10::Load();
	// プレイヤーを読み込む
	CPlayer::Load();

	// ジョッキーの読み込み
	CJockey::Load();
	// ジョッキーの読み込み
	CJockey2::Load();
	// ジョッキーの読み込み
	CJockey3::Load();
	// ジョッキーの読み込み
	CJockey4::Load();
	// ジョッキーの読み込み
	CJockey5::Load();
	// ジョッキーの読み込み
	CJockey6::Load();
	// ジョッキーの読み込み
	CJockey7::Load();
	// ジョッキーの読み込み
	CJockey8::Load();
	// ジョッキーの読み込み
	CJockey9::Load();
	// ジョッキーの読み込み
	CJockey10::Load();

	// プレスエンターの読み込み
	//CPressEntor::Load();

	//============================================================================================================================
	// 右
	//============================================================================================================================
	// 馬9の生成
	m_pHorse9 = CHorse9::Create(D3DXVECTOR3(100, 0, -150), D3DXVECTOR3(0, D3DX_PI / 2, 0), CHorse9::JOCKEYTYPE_RESULT);

	// 馬2の生成
	m_pHorse2 = CHorse2::Create(D3DXVECTOR3(100, 0, -100), D3DXVECTOR3(0, D3DX_PI / 2, 0), CHorse2::JOCKEYTYPE_RESULT);

	// 馬3の生成
	m_pHorse3 = CHorse3::Create(D3DXVECTOR3(100, 0, -50), D3DXVECTOR3(0, D3DX_PI / 2, 0), CHorse3::JOCKEYTYPE_RESULT);

	// 馬4の生成
	m_pHorse4 = CHorse4::Create(D3DXVECTOR3(100, 0, 0), D3DXVECTOR3(0, D3DX_PI / 2, 0), CHorse4::JOCKEYTYPE_RESULT);

	//===============================================================================================================
	// 左
	//===============================================================================================================
	 //馬7の生成
	m_pHorse7 = CHorse7::Create(D3DXVECTOR3(-100, 0, -150), D3DXVECTOR3(0, 11, 0), CHorse7::JOCKEYTYPE_RESULT);

	// 馬8の生成
	m_pHorse8 = CHorse8::Create(D3DXVECTOR3(-100, 0, -100), D3DXVECTOR3(0, 11, 0), CHorse8::JOCKEYTYPE_RESULT);

	// 馬5の生成
	m_pHorse5 = CHorse5::Create(D3DXVECTOR3(-100, 0, -50), D3DXVECTOR3(0, 11, 0), CHorse5::JOCKEYTYPE_RESULT);

	// 馬6の生成
	m_pHorse6 = CHorse6::Create(D3DXVECTOR3(-100, 0, 0), D3DXVECTOR3(0, 11, 0), CHorse6::JOCKEYTYPE_RESULT);

	CUnion::Create(D3DXVECTOR3(0, 0, -100), D3DXVECTOR3(0, 0, 0));

	// メッシュフィールドの生成
	//m_pMeshFiled = CMeshFiled::Create(D3DXVECTOR3(0.0f, 0.0f, 1700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), X_SIZE, Z_SIZE, mPolygonX, mPolygonZ);

	// プレスエンターの生成
	//CPressEntor::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 200, 0), 200.0f, 70.0f);

	// ロゴの生成
	CLogo::Create(D3DXVECTOR3(-700, SCREEN_HEIGHT - 500, 0.0f), 600.0f, 200.0f, CLogo::LOGO_RESULT);
}

//=============================================================================
// 終了処理
//=============================================================================
void CResult::Uninit(void)
{
	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();

		m_pTexture = NULL;
	}

	// カメラを破棄
	if (m_pCamera != NULL)
	{
		m_pCamera->Uninit();			// カメラを消す

		delete m_pCamera;
		m_pCamera = NULL;
	}

	// ライトを破棄
	if (m_pLight != NULL)
	{
		m_pLight->Uninit();				// ライトを消す

		delete m_pLight;
		m_pLight = NULL;
	}

	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	CScene::ReleaseAll();
}

//=============================================================================
// 更新処理
//=============================================================================
void CResult::Update(void)
{
	// キーボードを取得
	CInputKeyboard *InputKeyboard;
	InputKeyboard = CManager::GetInputKeyboard();

	// パッドを取得
	CInputjoypad *InputJoypad;
	InputJoypad = CManager::GetInputJoypad();

	// サウンドを取得
	CSound *pSound;
	pSound = CManager::GetSound();

	m_pSound = pSound;

	// デバックを取得
	CDebugProc *m_Dubug = CRenderer::GetDebug();

#ifdef _DEBUG
	m_Dubug->Print("s", "Title");

#endif // DEBUG


	m_Titletimer++;

	// フェードを取得
	CFade *pFade;
	pFade = CManager::GetFade();

	if (pFade->GetFade() == CFade::FADE_NONE)
	{
		if (InputKeyboard->GetTrigger(DIK_RETURN) == true || InputJoypad->GetPress(CInputjoypad::DIJS_BOTTON_B) == true)
		{
			pFade->SetFade(CManager::MODE_TITLE);
		}
	}

	// NULLチェック
	if (m_pCamera != NULL)
	{
		m_pCamera->Update();			// カメラを更新
	}

	// NULLチェック
	if (m_pLight != NULL)
	{
		m_pLight->Update();				// ライトを更新
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CResult::Draw(void)
{
	// NULLチェック
	if (m_pCamera != NULL)
	{
		m_pCamera->SetCamera();			// カメラの設定
	}
}

//=============================================================================
// タイトルの生成
//=============================================================================
CResult*CResult::Create(void)
{
	CResult *pTitle;

	pTitle = new CResult;

	pTitle->Init();

	return pTitle;
}

//=============================================================================
// カメラの取得
//=============================================================================
CCamera * CResult::GetCamera(void)
{
	return m_pCamera;
}

//=============================================================================
// ライトの取得
//=============================================================================
CLight * CResult::GetLight(void)
{
	return m_pLight;
}

//=============================================================================
// メッシュフィールドの取得
//=============================================================================
CMeshFiled * CResult::GetMeshFiled(void)
{
	return m_pMeshFiled;
}

//=============================================================================
// ロゴの取得
//=============================================================================
CLogo * CResult::GetLogo(void)
{
	return m_pLogo;
}

//=============================================================================
// 馬の取得
//=============================================================================
CPlayer * CResult::GetPlayer(void)
{
	return m_pPlayer;
}
//=============================================================================
// 馬2の取得
//=============================================================================
CHorse2 * CResult::GetHorse2(void)
{
	return m_pHorse2;
}
//=============================================================================
// 馬3の取得
//=============================================================================
CHorse3 * CResult::GetHorse3(void)
{
	return m_pHorse3;
}
//=============================================================================
// 馬4の取得
//=============================================================================
CHorse4 * CResult::GetHorse4(void)
{
	return m_pHorse4;
}
//=============================================================================
// 馬5の取得
//=============================================================================
CHorse5 * CResult::GetHorse5(void)
{
	return m_pHorse5;
}
//=============================================================================
// 馬6の取得
//=============================================================================
CHorse6 * CResult::GetHorse6(void)
{
	return m_pHorse6;
}
//=============================================================================
// 馬7の取得
//=============================================================================
CHorse7 * CResult::GetHorse7(void)
{
	return m_pHorse7;
}
//=============================================================================
// 馬8の取得
//=============================================================================
CHorse8 * CResult::GetHorse8(void)
{
	return m_pHorse8;
}
//=============================================================================
// 馬9の取得
//=============================================================================
CHorse9 * CResult::GetHorse9(void)
{
	return m_pHorse9;
}
//=============================================================================
// 馬10の取得
//=============================================================================
CHorse10 * CResult::GetHorse10(void)
{
	return m_pHorse10;
}

//=============================================================================
// ジョッキー1の取得
//=============================================================================
CJockey * CResult::GetJockey(void)
{
	return m_pJockey;
}
//=============================================================================
// ジョッキー2の取得
//=============================================================================
CJockey2 * CResult::GetJockey2(void)
{
	return m_pJockey2;
}
//=============================================================================
// ジョッキー3の取得
//=============================================================================
CJockey3 * CResult::GetJockey3(void)
{
	return m_pJockey3;
}
//=============================================================================
// ジョッキー4の取得
//=============================================================================
CJockey4 * CResult::GetJockey4(void)
{
	return m_pJockey4;
}
//=============================================================================
// ジョッキー5の取得
//=============================================================================
CJockey5 * CResult::GetJockey5(void)
{
	return m_pJockey5;
}
//=============================================================================
// ジョッキー6の取得
//=============================================================================
CJockey6 * CResult::GetJockey6(void)
{
	return m_pJockey6;
}
//=============================================================================
// ジョッキー7の取得
//=============================================================================
CJockey7 * CResult::GetJocke7(void)
{
	return m_pJockey7;
}

//=============================================================================
// ジョッキー8の取得
//=============================================================================
CJockey8 * CResult::GetJocke8(void)
{
	return m_pJockey8;
}
//=============================================================================
// ジョッキー9の取得
//=============================================================================
CJockey9 * CResult::GetJockey9(void)
{
	return m_pJockey9;
}
//=============================================================================
// ジョッキー10の取得
//=============================================================================
CJockey10 * CResult::GetJockey10(void)
{
	return m_pJockey10;
}