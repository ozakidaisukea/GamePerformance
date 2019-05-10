//=============================================================================
//
// ゲームオーバー処理 [gameover.cpp]
// Author : Ozaki
//
//=============================================================================
#include "gameover.h"
#include "manager.h"
#include "renderer.h"
#include "fade.h"
#include "bg.h"
#include "logo.h"
#include "score.h"
#include "joypad.h"
#include "logosyake.h"

//=============================================================================
// 静的メンバ変数
//=============================================================================
LPDIRECT3DTEXTURE9	CGameover::m_pTexture = NULL;
LPDIRECT3DVERTEXBUFFER9 CGameover::m_pVtxBuff = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CGameover::CGameover()
{

}

//=============================================================================
// デストラクタ
//=============================================================================
CGameover::~CGameover()
{

}

//=============================================================================
// ロード
//=============================================================================
HRESULT CGameover::Load(void)
{
	CRenderer *pRenderer;

	pRenderer = new CRenderer;

	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = NULL;

	pDevice = CManager::GetRenderer()->GetDevice();

	return S_OK;
}

//=============================================================================
// アンロード
//=============================================================================
void CGameover::Unload(void)
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
HRESULT CGameover::Init(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = NULL;

	pDevice = CManager::GetRenderer()->GetDevice();

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VRETEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// 背景の読み込み
	CBg::Load();

	// ロゴの読み込み
	CLogo::Load();

	// 鮭ロゴの読み込み
	CLogosyake::Load();

	// 背景の生成
	CBg::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0),10.0f, SCREEN_WIDTH);

	// ロゴの生成
	CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 500, 0), 650.0f, 200.0f, CLogo::LOGO_GAMEOVER);

	// 鮭ロゴの生成
	CLogosyake::Create(D3DXVECTOR3(390, 340, 0), 200.0f,300.0f, D3DXVECTOR3(0.5f, 0.0f, 0.0f), CLogosyake::SYAKE_GAMEOVER);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CGameover::Uninit(void)
{
	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();

		m_pTexture = NULL;
	}
	CScene::ReleaseAll();
}

//=============================================================================
// 更新処理
//=============================================================================
void CGameover::Update(void)
{
	// キーボードを取得
	CInputKeyboard *InputKeyboard;
	InputKeyboard = CManager::GetInputKeyboard();

	// フェードを取得
	CFade *pFade;
	pFade = CManager::GetFade();

	// キーボードを取得
	CInputjoypad *InputJoypad;
	InputJoypad = CManager::GetInputJoypad();

	if (pFade->GetFade() == CFade::FADE_NONE)
	{
		if (InputKeyboard->GetTrigger(DIK_RETURN) == true || InputJoypad->GetPress(CInputjoypad::DIJS_BOTTON_START) == true
			|| InputJoypad->GetTrigger(CInputjoypad::DIJS_BOTTON_B) == true)
		{
			pFade->SetFade(CManager::MODE_RANKING);
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CGameover::Draw(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = NULL;

	pDevice = CManager::GetRenderer()->GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VRETEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);
}

//=============================================================================
// リザルトの生成
//=============================================================================
CGameover*CGameover::Create(void)
{
	CGameover *pResult;

	pResult = new CGameover;

	pResult->Init();

	return pResult;
}