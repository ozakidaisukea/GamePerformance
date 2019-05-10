//=============================================================================
//
// ゲージ処理 [gauge.cpp]
// Author : Ozaki
//
//=============================================================================
#include "gauge.h"
#include "renderer.h"
#include "fade.h"
#include "scene2D.h"
#include "item.h"
#include "player.h"

//=============================================================================
// 静的メンバ変数
//=============================================================================
LPDIRECT3DTEXTURE9 CGauge::m_pTexture[MAX_GAUGE] = {};
float CGauge::m_fGauge = NULL;
//=============================================================================
// コンストラクタ
//=============================================================================
CGauge::CGauge() :CScene2D(8)
{
	m_fGauge = 100.0f;
}

//=============================================================================
// デストラクタ
//=============================================================================
CGauge::~CGauge()
{
}

//=============================================================================
// ロード
//=============================================================================
HRESULT CGauge::Load(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = NULL;

	pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの生成0	[背景]
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\game\\gaugebg.png",
		&m_pTexture[0]);

	// テクスチャの生成1	[ゲージ]
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\game\\gauge.png",
		&m_pTexture[1]);

	// テクスチャの生成1	[フレーム]
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\game\\gaugeframe.png",
		&m_pTexture[2]);

	return S_OK;
}

//=============================================================================
// アンロード
//=============================================================================
void CGauge::Unload(void)
{
	for (int nCnt = 0; nCnt < MAX_GAUGE; nCnt++)
	{
		// テクスチャの破棄
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();

			m_pTexture[nCnt] = NULL;
		}
	}
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CGauge::Init(D3DXVECTOR3 pos, float widtgh, float height)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = NULL;

	for (int nCnt = 0; nCnt < MAX_GAUGE; nCnt++)
	{
		m_Scene2D[nCnt] = new CScene2D(8);
		m_Scene2D[nCnt]->CScene2D::Init(pos, widtgh, height);
		m_Scene2D[nCnt]->BindTexture(m_pTexture[nCnt]);
	}

	m_widtgh = widtgh;
	m_height = height;

	m_fGauge = 20.0f;

	// 頂点情報の作成
	VERTEX_2D*pVtx;			//頂点情報へのポインタ

	// 頂点バッファをロックし、頂点データへのポインタを取得
	for (int nCnt = 0; nCnt < MAX_GAUGE; nCnt++)
	{
		m_pVtxBuff = m_Scene2D[nCnt]->GetVtxBG();
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// 背景
		if (nCnt == 0)
		{
			pVtx[0].pos = D3DXVECTOR3(20.0f, 100.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(GAUGE_VALUE, 100.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(20.0f, 130.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(GAUGE_VALUE, 130.0f, 0.0f);
		}

		// ゲージ
		if (nCnt == 1)
		{
			pVtx[0].pos = D3DXVECTOR3(20.0f, 100.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(m_fGauge, 100.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(20.0f, 130.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(m_fGauge, 130.0f, 0.0f);
		}

		// フレーム
		if (nCnt == 2)
		{
			pVtx[0].pos = D3DXVECTOR3(20.0f, 100.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(GAUGE_VALUE, 100.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(20.0f, 130.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(GAUGE_VALUE, 130.0f, 0.0f);
		}

		//頂点バッファのアンロック
		m_pVtxBuff->Unlock();
	}


	SetObjtType(CScene::OBJTYPE_GAUGE);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CGauge::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_GAUGE; nCnt++)
	{
		// テクスチャの破棄
		if (m_Scene2D[nCnt] != NULL)
		{
			m_Scene2D[nCnt]->Uninit();

			m_Scene2D[nCnt] = NULL;
		}
	}
	CScene::Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CGauge::Update(void)
{
	// 頂点情報の作成
	VERTEX_2D*pVtx;			//頂点情報へのポインタ

	// ゲージをGAUGE_VALUEを超えない
	if (m_fGauge >= GAUGE_VALUE)
	{
		m_fGauge = GAUGE_VALUE;
	}

	// 頂点バッファをロックし、頂点データへのポインタを取得
	for (int nCnt = 0; nCnt < MAX_GAUGE; nCnt++)
	{
		m_pVtxBuff = m_Scene2D[nCnt]->GetVtxBG();
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// 背景
		if (nCnt == 0)
		{
			pVtx[0].pos = D3DXVECTOR3(20.0f, 100.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(GAUGE_VALUE, 100.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(20.0f, 130.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(GAUGE_VALUE, 130.0f, 0.0f);
		}

		// ゲージ
		if (nCnt == 1)
		{
			pVtx[0].pos = D3DXVECTOR3(20.0f, 100.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(m_fGauge, 100.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(20.0f, 130.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(m_fGauge, 130.0f, 0.0f);
		}

		// フレーム
		if (nCnt == 2)
		{
			pVtx[0].pos = D3DXVECTOR3(20.0f, 100.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(GAUGE_VALUE, 100.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(20.0f, 130.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(GAUGE_VALUE, 130.0f, 0.0f);
		}

		//頂点バッファのアンロック
		m_pVtxBuff->Unlock();
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CGauge::Draw(void)
{

}

//=============================================================================
// ゲージの生成
//=============================================================================
CGauge*CGauge::Create(D3DXVECTOR3 pos, float widtgh, float height)
{
	CGauge *pGauge;

	pGauge = new CGauge;

	if (pGauge != NULL)
	{
		pGauge->Init(pos,widtgh,height);
	}

	return pGauge;
}

//=============================================================================
// アイテム取得時にゲージをUP
//=============================================================================
void CGauge::AddGauge(float f_gauge)
{
	// 250を超えない
	if (m_fGauge <= GAUGE_VALUE)
	{
		m_fGauge += f_gauge;

	}
	else if (m_fGauge > GAUGE_VALUE)
	{
		m_fGauge = GAUGE_VALUE;
	}

	// 250を0
	if (m_fGauge < 20)
	{
		m_fGauge = 20;
	}
}