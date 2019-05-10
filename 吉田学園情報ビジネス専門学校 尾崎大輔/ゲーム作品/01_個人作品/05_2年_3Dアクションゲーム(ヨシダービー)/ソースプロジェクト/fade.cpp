//=============================================================================
//
// フェード処理 [fade.cpp]
// Author : Ozaki
//
//=============================================================================
#include "fade.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// 静的メンバ変数
//=============================================================================
LPDIRECT3DTEXTURE9	CFade::m_pTexture = NULL;
//LPDIRECT3DVERTEXBUFFER9 CFade::m_pVtxBuff = NULL;
CManager::MODE CFade::m_modeNext = CManager::MODE_TITLE;

CFade::FADE CFade::m_fade = CFade::FADE_IN;
D3DXCOLOR CFade::m_colorFade = D3DXCOLOR(0, 0, 0, 0);

//=============================================================================
// コンストラクタ
//=============================================================================
CFade::CFade()
{
	m_pVtxBuff = NULL;
}

//=============================================================================
// デストラクタ
//=============================================================================
CFade::~CFade()
{

}

//=============================================================================
// ロード
//=============================================================================
HRESULT CFade::Load(void)
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
void CFade::Unload(void)
{
	// テクスチャの破棄
	/*if (m_pTexture != NULL)
	{
		m_pTexture->Release();

		m_pTexture = NULL;
	}*/
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CFade::Init(CManager::MODE modeNext)
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

	//ローカル変数
	VERTEX_2D*pVtx;

	//頂点バッファをロックし、頂点データのポインタの取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//テクスチャの設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();

	m_colorFade = D3DXCOLOR(0, 0, 0, 0);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CFade::Uninit(void)
{
	// テクスチャの破棄
	/*if (m_pTexture != NULL)
	{
		m_pTexture->Release();

		m_pTexture = NULL;
	}*/
	CScene::ReleaseAll();
}

//=============================================================================
// 更新処理
//=============================================================================
void CFade::Update(void)
{
	VERTEX_2D*pVtx;									//頂点情報へのポインタ

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点カラーの設定
	pVtx[0].col = m_colorFade;
	pVtx[1].col = m_colorFade;
	pVtx[2].col = m_colorFade;
	pVtx[3].col = m_colorFade;

	m_pVtxBuff->Unlock();

	if (m_fade != FADE_NONE)
	{
		if (m_fade == FADE_IN)
		{
			m_colorFade.a -= 0.03f;
			if (m_colorFade.a <= 0.0f)
			{
				m_colorFade.a = 0.0f;
				m_fade = FADE_NONE;
			}
		}
		else if (m_fade == FADE_OUT)
		{
			m_colorFade.a += 0.02f;
			if (m_colorFade.a >= 1.0f)
			{
				m_colorFade.a = 1.0f;
				m_fade = FADE_IN;

				CManager::SetMode(m_modeNext);
			}
		}
	}



}

//=============================================================================
// 描画処理
//=============================================================================
void CFade::Draw(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = NULL;

	pDevice = CManager::GetRenderer()->GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VRETEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, NULL);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);
}

//=============================================================================
// フェードの生成
//=============================================================================
CFade*CFade::Create(void)
{
	CFade *pFade;

	pFade = new CFade;

	if (pFade != NULL)
	{
		pFade->Init(m_modeNext);
	}

	return pFade;
}

//=============================================================================
// フェードの設定
//=============================================================================
void CFade::SetFade(CManager::MODE modeNext)
{
	if (m_fade != FADE_OUT)
	{
		m_fade = FADE_OUT;
		m_modeNext = modeNext;								//次の画面
		m_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	//フェードの色
	}
}

//=============================================================================
// モードの取得
//=============================================================================
CFade::FADE CFade::GetFade(void)
{
	return m_fade;
}