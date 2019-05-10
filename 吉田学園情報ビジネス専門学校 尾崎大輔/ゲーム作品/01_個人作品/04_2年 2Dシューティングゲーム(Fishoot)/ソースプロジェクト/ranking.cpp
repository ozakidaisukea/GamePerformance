//=============================================================================
//
// ランキング処理 [ranking.cpp]
// Author : Ozaki
//
//=============================================================================
#include "ranking.h"
#include "manager.h"
#include "renderer.h"
#include "fade.h"
#include "bg.h"
#include "logo.h"
#include "score.h"
#include "number.h"
#include "joypad.h"

//=============================================================================
// 静的メンバ変数
//=============================================================================
LPDIRECT3DTEXTURE9	CRanking::m_pTexture = NULL;
LPDIRECT3DVERTEXBUFFER9 CRanking::m_pVtxBuff = NULL;

CScore*CRanking::m_apScore[MAX_RANKING] = {};

//=============================================================================
// コンストラクタ
//=============================================================================
CRanking::CRanking()
{
	m_rankingtimer = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CRanking::~CRanking()
{

}

//=============================================================================
// ロード
//=============================================================================
HRESULT CRanking::Load(void)
{
	CRenderer *pRenderer;

	pRenderer = new CRenderer;

	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = NULL;

	pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\game\\mizu.png",
		&m_pTexture);

	return S_OK;
}

//=============================================================================
// アンロード
//=============================================================================
void CRanking::Unload(void)
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
HRESULT CRanking::Init(void)
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

	// スコアの読み込み
	CNumber::Load();

	// 背景の生成
	CBg::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0), 10.0f, SCREEN_WIDTH);

	// ロゴの生成
	CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 50, 0), 500.0f, 80.0f, CLogo::LOGO_RANKING);

	// 1位
	CLogo::Create(D3DXVECTOR3(400, 170, 0), 70.0f, 70.0f, CLogo::LOGO_1);

	// 2位
	CLogo::Create(D3DXVECTOR3(400, 290, 0), 70.0f, 70.0f, CLogo::LOGO_2);

	// 3位
	CLogo::Create(D3DXVECTOR3(400, 390, 0), 70.0f, 70.0f, CLogo::LOGO_3);

	// 4位
	CLogo::Create(D3DXVECTOR3(400, 490, 0), 60.0f, 60.0f, CLogo::LOGO_4);

	// 5位
	CLogo::Create(D3DXVECTOR3(400, 590, 0), 60.0f, 60.0f, CLogo::LOGO_5);

	float pos = 150;
	int	  aScore[MAX_RANKING] = {};

	// スコア
	for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
	{
		aScore[nCnt] = CManager::GetRankingScore(nCnt);

		m_apScore[nCnt] = CScore::Create(D3DXVECTOR3(700.0f, pos + 30, 0.0f), 30.0f, 50.0f);

		// スコア加算
		m_apScore[nCnt]->AddScore(aScore[nCnt]);

		pos += 100;
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CRanking::Uninit(void)
{
	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();

		m_pTexture = NULL;
	}

	for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
	{
		if (m_apScore[nCnt] != NULL)
		{
			m_apScore[nCnt]->ReleaseAll();

			m_apScore[nCnt] = NULL;
		}
	}

	CScene::ReleaseAll();
}

//=============================================================================
// 更新処理
//=============================================================================
void CRanking::Update(void)
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

	m_rankingtimer++;

	if (pFade->GetFade() == CFade::FADE_NONE)
	{
		if (InputKeyboard->GetTrigger(DIK_RETURN) == true ||
			InputJoypad->GetPress(CInputjoypad::DIJS_BOTTON_START) == true || InputJoypad->GetTrigger(CInputjoypad::DIJS_BOTTON_B) == true)
		{
			pFade->SetFade(CManager::MODE_TITLE);
		}

		if (m_rankingtimer == 500)
		{
			pFade->SetFade(CManager::MODE_TITLE);
			m_rankingtimer = 0;
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CRanking::Draw(void)
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
// ランキングの生成
//=============================================================================
CRanking*CRanking::Create(void)
{
	CRanking *pRanking;

	pRanking = new CRanking;

	pRanking->Init();

	return pRanking;
}