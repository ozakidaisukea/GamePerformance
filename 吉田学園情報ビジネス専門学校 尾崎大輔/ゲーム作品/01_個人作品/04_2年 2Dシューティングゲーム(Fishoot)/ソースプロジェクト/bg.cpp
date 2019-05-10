//=============================================================================
//
// 背景の処理　[bg.cpp]
// Author : Ozaki
//
//=============================================================================
#include "bg.h"
#include "renderer.h"
#include "main.h"
#include "manager.h"
#include "scene2D.h"
#include "input.h"
#include "scene.h"

//=============================================================================
// 静的メンバ変数
//=============================================================================
LPDIRECT3DTEXTURE9 CBg::m_apTexture[MAX_BG] = {};
CBg::MODE CBg::m_mode;

//=============================================================================
// コンストラクタ
//=============================================================================
CBg::CBg():CScene(0)
{
	m_fTex = 0.0f;
}

//=============================================================================
// デストラクタ
//=============================================================================
CBg::~CBg()
{

}

//=============================================================================
// 読み込み
//=============================================================================
HRESULT CBg::Load(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = NULL;

	pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの生成[1枚目]
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\bg\\umi000.png",
		&m_apTexture[0]);

	// テクスチャの生成[2枚目]
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\bg\\mizu001.png",
		&m_apTexture[1]);

	// テクスチャの生成[3枚目]
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\bg\\nami000.png",
		&m_apTexture[2]);

	return S_OK;
}

//=============================================================================
// 開放
//=============================================================================
void CBg::Unload(void)
{
	for (int nCnt = 0; nCnt < MAX_BG; nCnt++)
	{
		// テクスチャの破棄
		if (m_apTexture[nCnt] != NULL)
		{
			m_apTexture[nCnt]->Release();

			m_apTexture[nCnt] = NULL;
		}
	}
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CBg::Init(D3DXVECTOR3 pos, float widtgh, float height)
{
	//for (int nCnt = 0; nCnt < MAX_BG; nCnt++)
	//{
	//	m_apScene2D[nCnt] = new CScene2D;

	//	// 共有テクスチャを割り当てる
	//	m_apScene2D[nCnt]->BindTexture(m_apTexture[0]);

	//	m_apScene2D[nCnt]->Init(pos);
	//}
	LPDIRECT3DVERTEXBUFFER9 VtxBuff;

	for (int nCntBG = 0; nCntBG < MAX_BG; nCntBG++)
	{
		VtxBuff = m_apScene2D[nCntBG]->GetVtxBG();
		//ローカル変数
		VERTEX_2D*pVtx;

		//頂点バッファをロックし、頂点データのポインタの取得
		VtxBuff->Lock(0, 0, (void**)&pVtx, 0);

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


		pVtx += 4;					//頂点データのポインタを4つ分進める

		//頂点バッファをアンロック
		VtxBuff->Unlock();
	}
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CBg::Uninit(void)
{
	for (int nCntBG = 0; nCntBG < MAX_BG; nCntBG++)
	{
		m_apScene2D[nCntBG]->Uninit();

		m_apScene2D[nCntBG] = NULL;
	}
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CBg::Update(void)
{

	m_fTex -= 0.005f;

	LPDIRECT3DVERTEXBUFFER9 VtxBuff;

	for (int nCntBG = 0; nCntBG < MAX_BG; nCntBG++)
	{
		VtxBuff = m_apScene2D[nCntBG]->GetVtxBG();
		//ローカル変数
		VERTEX_2D*pVtx;

		//頂点バッファをロックし、頂点データのポインタの取得
		VtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//テクスチャの設定
		pVtx[0].tex = D3DXVECTOR2(0.0f + (m_fTex * (nCntBG + 0.5f) * 0.5f), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f + (m_fTex * (nCntBG + 0.5f) * 0.5f), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (m_fTex * (nCntBG + 0.5f) * 0.5f), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f + (m_fTex * (nCntBG + 0.5f) * 0.5f), 1.0f);


		pVtx += 4;					//頂点データのポインタを4つ分進める

		//頂点バッファをアンロック
		VtxBuff->Unlock();
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CBg::Draw(void)
{

}

//=============================================================================
// 背景の生成
//=============================================================================
CBg *CBg::Create(D3DXVECTOR3 pos, float widtgh, float height)
{
	CBg *pBg;

	pBg = new CBg;

	for (int nCntBG = 0; nCntBG < MAX_BG; nCntBG++)
	{
		pBg->m_apScene2D[nCntBG] = new CScene2D(0);

		// 共有テクスチャを割り当てる
		pBg->m_apScene2D[nCntBG]->BindTexture(m_apTexture[nCntBG]);

		pBg->m_apScene2D[nCntBG]->Init(pos, widtgh,height);
	}
	pBg->Init(pos, widtgh,height);

	return pBg;
}

//=============================================================================
// モードの設定
//=============================================================================
void CBg::SetMode(MODE mode)
{

}
