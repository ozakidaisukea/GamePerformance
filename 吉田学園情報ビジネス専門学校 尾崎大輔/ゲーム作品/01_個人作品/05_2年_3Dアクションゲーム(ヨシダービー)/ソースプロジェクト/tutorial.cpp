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
#include "sound.h"
#include "title.h"
#include "fade.h"
#include "logo.h"
#include "debugproc.h"
#include "joypad.h"

//=============================================================================
// 静的メンバ変数
//=============================================================================
CPlayer*CTutorial::m_pPlayer = NULL;
CLogo*CTutorial::m_pLogo = NULL;

LPDIRECT3DTEXTURE9	CTutorial::m_pTexture = NULL;
LPDIRECT3DVERTEXBUFFER9 CTutorial::m_pVtxBuff = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CTutorial::CTutorial()
{

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


	//================================
	// 読み込み類
	//================================
	CLogo::Load();

	//================================
	// 生成類
	//================================
	CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 350, 0), 900, 500, CLogo::LOGO_TUTORIAL);
	CLogo::Create(D3DXVECTOR3(1950, 350, 0), 900, 500, CLogo::LOGO_RESECARD);

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
	// サウンドを取得
	CSound *pSound;
	pSound = CManager::GetSound();

	// キーボードを取得
	CInputKeyboard *InputKeyboard;
	InputKeyboard = CManager::GetInputKeyboard();

	// パッドを取得
	CInputjoypad *InputJoypad;
	InputJoypad = CManager::GetInputJoypad();

	// フェードを取得
	CFade *pFade;
	pFade = CManager::GetFade();

	// デバックを取得
	CDebugProc *m_Dubug = CRenderer::GetDebug();
#ifdef _DEBUG
	m_Dubug->Print("s", "Tutorial");
#endif // _DEBUG


	if (pFade->GetFade() == CFade::FADE_NONE)
	{
		if (InputKeyboard->GetTrigger(DIK_RETURN) == true || InputJoypad->GetPress(CInputjoypad::DIJS_BOTTON_B) == true)
		{
			pFade->SetFade(CManager::MODE_GAME);
			pSound->PlaySound(pSound->SOUND_LABEL_SE_DECISON2);
		}
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
// ロゴの取得
//=============================================================================
CLogo *CTutorial::GetLogo(void)
{
	return m_pLogo;
}