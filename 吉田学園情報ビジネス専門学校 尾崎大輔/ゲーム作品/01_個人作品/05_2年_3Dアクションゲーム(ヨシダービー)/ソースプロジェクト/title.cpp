//=============================================================================
//
// タイトル処理 [title.cpp]
// Author : Ozaki
//
//=============================================================================
#include "title.h"
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
#include "pressentor.h"
#include "joypad.h"

//=============================================================================
// 静的メンバ変数
//=============================================================================
LPDIRECT3DTEXTURE9	CTitle::m_pTexture = NULL;
LPDIRECT3DVERTEXBUFFER9 CTitle::m_pVtxBuff = NULL;
CSound*CTitle::m_pSound = NULL;
CCamera*CTitle::m_pCamera = NULL;
CLight*CTitle::m_pLight = NULL;
CMeshFiled*CTitle::m_pMeshFiled = NULL;
CLogo*CTitle::m_pLogo = NULL;
CPressEntor*CTitle::m_pPressEntor = NULL;

CPlayer*CTitle::m_pPlayer = NULL;
CHorse2*CTitle::m_pHorse2 = NULL;
CHorse3*CTitle::m_pHorse3 = NULL;
CHorse4*CTitle::m_pHorse4 = NULL;
CHorse5*CTitle::m_pHorse5 = NULL;
CHorse6*CTitle::m_pHorse6 = NULL;
CHorse7*CTitle::m_pHorse7 = NULL;
CHorse8*CTitle::m_pHorse8 = NULL;
CHorse9*CTitle::m_pHorse9 = NULL;
CHorse10*CTitle::m_pHorse10 = NULL;
CJockey*CTitle::m_pJockey = NULL;
CJockey2*CTitle::m_pJockey2 = NULL;
CJockey3*CTitle::m_pJockey3 = NULL;
CJockey4*CTitle::m_pJockey4 = NULL;
CJockey5*CTitle::m_pJockey5 = NULL;
CJockey6*CTitle::m_pJockey6 = NULL;
CJockey7*CTitle::m_pJockey7 = NULL;
CJockey8*CTitle::m_pJockey8 = NULL;
CJockey9*CTitle::m_pJockey9 = NULL;
CJockey10*CTitle::m_pJockey10 = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CTitle::CTitle()
{
	// ランキングに切り替えるタイマー
	m_Titletimer = 0;
	m_pLogo = NULL;
}

//=============================================================================
// デストラクタ
//=============================================================================
CTitle::~CTitle()
{

}

//=============================================================================
// ロード
//=============================================================================
void CTitle::Load(void)
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
void CTitle::Unload(void)
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
void CTitle::Init(void)
{
	m_pCamera = new CCamera;
	m_pLight = new CLight;

	// カメラを取得
	m_pCamera->SetMode(CCamera::MODE_TITLE);

	//============================================================================================================================
	// 読み込み類
	//============================================================================================================================

	// カメラの初期化
	m_pCamera->Init();

	// ライトの初期化
	m_pLight->Init();

	CUnion::Load();

	// ロゴの初期化
	CLogo::Load();

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
	CPressEntor::Load();

	//============================================================================================================================
	// 生成類
	//============================================================================================================================

	//============================================================================================================================
	// 右移動
	//============================================================================================================================
	// プレイヤーの生成
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(100, 0, 0), D3DXVECTOR3(0, D3DX_PI / 2, 0), CPlayer::JOCKEYTYPE_TITLE);
	// ジョッキーの生成
	m_pJockey = CJockey::Create(D3DXVECTOR3(100, 20, 0), D3DXVECTOR3(0, D3DX_PI / 2, 0), CJockey::JOCKEYTYPE_TITLE);

	// 馬2の生成
	m_pHorse2 = CHorse2::Create(D3DXVECTOR3(100, 0, 50), D3DXVECTOR3(0, D3DX_PI / 2, 0), CHorse2::JOCKEYTYPE_TITLE);
	// ジョッキー２の生成
	m_pJockey2 = CJockey2::Create(D3DXVECTOR3(100, 20, 50), D3DXVECTOR3(0, D3DX_PI / 2, 0), CJockey2::JOCKEYTYPE_TITLE);

	//===============================================================================================================
	// 左移動
	//===============================================================================================================
	// 馬3の生成
	m_pHorse3 = CHorse3::Create(D3DXVECTOR3(-100, 0, 25), D3DXVECTOR3(0,11, 0), CHorse3::JOCKEYTYPE_TITLE);
	// ジョッキー3の生成
	m_pJockey3 = CJockey3::Create(D3DXVECTOR3(-100, 20, 25), D3DXVECTOR3(0, 11, 0), CJockey3::JOCKEYTYPE_TITLE);

	// 馬4の生成
	m_pHorse4 = CHorse4::Create(D3DXVECTOR3(-100, 0, 75), D3DXVECTOR3(0, 11, 0), CHorse4::JOCKEYTYPE_TITLE);
	// ジョッキー4の生成
	m_pJockey4 = CJockey4::Create(D3DXVECTOR3(-100, 20, 75), D3DXVECTOR3(0, 11, 0), CJockey4::JOCKEYTYPE_TITLE);

	//===============================================================================================================
	// 前方移動
	//===============================================================================================================
	// 馬5の生成
	m_pHorse5 = CHorse5::Create(D3DXVECTOR3(-20, 0, -200), D3DXVECTOR3(0, D3DX_PI, 0), CHorse5::JOCKEYTYPE_TITLE);
	// ジョッキー5の生成
	m_pJockey5 = CJockey5::Create(D3DXVECTOR3(-20, 20, -200), D3DXVECTOR3(0, D3DX_PI, 0), CJockey5::JOCKEYTYPE_TITLE);

	// 馬6の生成
	m_pHorse6 = CHorse6::Create(D3DXVECTOR3(20, 0, -200), D3DXVECTOR3(0, D3DX_PI, 0), CHorse6::JOCKEYTYPE_TITLE);
	// ジョッキー6の生成
	m_pJockey6 = CJockey6::Create(D3DXVECTOR3(20, 20, -200), D3DXVECTOR3(0, D3DX_PI, 0), CJockey6::JOCKEYTYPE_TITLE);

	//===============================================================================================================
	// 後方移動
	//===============================================================================================================
	// 馬7の生成
	m_pHorse7 = CHorse7::Create(D3DXVECTOR3(0, 0, 200), D3DXVECTOR3(0, 0, 0), CHorse7::JOCKEYTYPE_TITLE);
	// ジョッキー7の生成
	m_pJockey7 = CJockey7::Create(D3DXVECTOR3(0, 20, 200), D3DXVECTOR3(0, 0, 0), CJockey7::JOCKEYTYPE_TITLE);

	// 馬8の生成
	m_pHorse8 = CHorse8::Create(D3DXVECTOR3(45, 0, 200), D3DXVECTOR3(0, 0, 0), CHorse8::JOCKEYTYPE_TITLE);
	// ジョッキー8の生成
	m_pJockey8 = CJockey8::Create(D3DXVECTOR3(45, 20, 200), D3DXVECTOR3(0, 0, 0), CJockey8::JOCKEYTYPE_TITLE);

	//===============================================================================================================
	// 上から
	//===============================================================================================================
	// 馬9の生成
	m_pHorse9 = CHorse9::Create(D3DXVECTOR3(-20, 300, 0), D3DXVECTOR3(0, 0, 0), CHorse9::JOCKEYTYPE_TITLE);
	// ジョッキー9の生成
	m_pJockey9 = CJockey9::Create(D3DXVECTOR3(-20, 320, 0), D3DXVECTOR3(0, 0, 0), CJockey9::JOCKEYTYPE_TITLE);

	// 馬10の生成
	m_pHorse10 = CHorse10::Create(D3DXVECTOR3(20, 300, 0), D3DXVECTOR3(0, 0, 0), CHorse10::JOCKEYTYPE_TITLE);
	// ジョッキー10の生成
	m_pJockey10 = CJockey10::Create(D3DXVECTOR3(20, 320, 0), D3DXVECTOR3(0, 0, 0), CJockey10::JOCKEYTYPE_TITLE);

	// メッシュフィールドの生成
	//m_pMeshFiled = CMeshFiled::Create(D3DXVECTOR3(0.0f, 0.0f, 1700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), X_SIZE, Z_SIZE, mPolygonX, mPolygonZ);

	// ロゴの生成
	CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, -500, 0.0f), 600.0f, 200.0f, CLogo::LOGO_TITLE);

	// プレスエンターの生成
	//m_pPressEntor = CPressEntor::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 200, 0), 200.0f, 70.0f);
	// プレスエンターの生成
	CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 200, 0), 200.0f, 70.0f, CLogo::LOGO_PRESSENTOR);
}

//=============================================================================
// 終了処理
//=============================================================================
void CTitle::Uninit(void)
{
	// テクスチャの解放
	CLogo::Unload();
	CUnion::Unload();
	CHorse2::Unload();
	CHorse3::Unload();
	CHorse4::Unload();
	CHorse5::Unload();
	CHorse6::Unload();
	CHorse7::Unload();
	CHorse8::Unload();
	CHorse9::Unload();
	CHorse10::Unload();
	CPlayer::Unload();
	CJockey::Unload();
	CJockey2::Unload();
	CJockey3::Unload();
	CJockey4::Unload();
	CJockey5::Unload();
	CJockey6::Unload();
	CJockey7::Unload();
	CJockey8::Unload();
	CJockey9::Unload();
	CJockey10::Unload();

	// プレスエンターの読み込み
	CPressEntor::Load();

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
void CTitle::Update(void)
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
			pFade->SetFade(CManager::MODE_TUTORIAL);
			pSound->PlaySound(pSound->SOUND_LABEL_SE_DECISON1);
		}
	}

	if (m_Titletimer == 2400)
	{
		pFade->SetFade(CManager::MODE_TITLE);
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
void CTitle::Draw(void)
{
	 //NULLチェック
	if (m_pCamera != NULL)
	{
		m_pCamera->SetCamera();			// カメラの設定
	}
}

//=============================================================================
// タイトルの生成
//=============================================================================
CTitle*CTitle::Create(void)
{
	CTitle *pTitle;

	pTitle = new CTitle;

	pTitle->Init();

	return pTitle;
}

//=============================================================================
// カメラの取得
//=============================================================================
CCamera * CTitle::GetCamera(void)
{
	return m_pCamera;
}

//=============================================================================
// ライトの取得
//=============================================================================
CLight * CTitle::GetLight(void)
{
	return m_pLight;
}

//=============================================================================
// メッシュフィールドの取得
//=============================================================================
CMeshFiled * CTitle::GetMeshFiled(void)
{
	return m_pMeshFiled;
}

//=============================================================================
// ロゴの取得
//=============================================================================
CLogo * CTitle::GetLogo(void)
{
	return m_pLogo;
}

//=============================================================================
// 馬の取得
//=============================================================================
CPlayer * CTitle::GetPlayer(void)
{
	return m_pPlayer;
}
//=============================================================================
// 馬2の取得
//=============================================================================
CHorse2 * CTitle::GetHorse2(void)
{
	return m_pHorse2;
}
//=============================================================================
// 馬3の取得
//=============================================================================
CHorse3 * CTitle::GetHorse3(void)
{
	return m_pHorse3;
}
//=============================================================================
// 馬4の取得
//=============================================================================
CHorse4 * CTitle::GetHorse4(void)
{
	return m_pHorse4;
}
//=============================================================================
// 馬5の取得
//=============================================================================
CHorse5 * CTitle::GetHorse5(void)
{
	return m_pHorse5;
}
//=============================================================================
// 馬6の取得
//=============================================================================
CHorse6 * CTitle::GetHorse6(void)
{
	return m_pHorse6;
}
//=============================================================================
// 馬7の取得
//=============================================================================
CHorse7 * CTitle::GetHorse7(void)
{
	return m_pHorse7;
}
//=============================================================================
// 馬8の取得
//=============================================================================
CHorse8 * CTitle::GetHorse8(void)
{
	return m_pHorse8;
}
//=============================================================================
// 馬9の取得
//=============================================================================
CHorse9 * CTitle::GetHorse9(void)
{
	return m_pHorse9;
}
//=============================================================================
// 馬10の取得
//=============================================================================
CHorse10 * CTitle::GetHorse10(void)
{
	return m_pHorse10;
}

//=============================================================================
// ジョッキー1の取得
//=============================================================================
CJockey * CTitle::GetJockey(void)
{
	return m_pJockey;
}
//=============================================================================
// ジョッキー2の取得
//=============================================================================
CJockey2 * CTitle::GetJockey2(void)
{
	return m_pJockey2;
}
//=============================================================================
// ジョッキー3の取得
//=============================================================================
CJockey3 * CTitle::GetJockey3(void)
{
	return m_pJockey3;
}
//=============================================================================
// ジョッキー4の取得
//=============================================================================
CJockey4 * CTitle::GetJockey4(void)
{
	return m_pJockey4;
}
//=============================================================================
// ジョッキー5の取得
//=============================================================================
CJockey5 * CTitle::GetJockey5(void)
{
	return m_pJockey5;
}
//=============================================================================
// ジョッキー6の取得
//=============================================================================
CJockey6 * CTitle::GetJockey6(void)
{
	return m_pJockey6;
}
//=============================================================================
// ジョッキー7の取得
//=============================================================================
CJockey7 * CTitle::GetJocke7(void)
{
	return m_pJockey7;
}

//=============================================================================
// ジョッキー8の取得
//=============================================================================
CJockey8 * CTitle::GetJocke8(void)
{
	return m_pJockey8;
}
//=============================================================================
// ジョッキー9の取得
//=============================================================================
CJockey9 * CTitle::GetJockey9(void)
{
	return m_pJockey9;
}
//=============================================================================
// ジョッキー10の取得
//=============================================================================
CJockey10 * CTitle::GetJockey10(void)
{
	return m_pJockey10;
}
//=============================================================================
// ジョッキー10の取得
//=============================================================================
CPressEntor * CTitle::GetEntor(void)
{
	return m_pPressEntor;
}