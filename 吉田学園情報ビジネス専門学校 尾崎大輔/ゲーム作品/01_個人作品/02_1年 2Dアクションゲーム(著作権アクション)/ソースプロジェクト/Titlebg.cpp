//=============================================================================
//
// 背景の処理 [Titlebg.cpp]
// Author : Ozaki
//
//=============================================================================
#include "main.h"
#include "Titlebg.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define BG_WIDTH	(SCREEN_WIDTH)
#define BG_HEIGHT	(SCREEN_HEIGHT)
#define PATTERN_X (0.00005f * g_PatrnAnimeTitle)

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureTitlebg = NULL;				//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitlebg = NULL;		//テクスチャのポインタ
int g_PatrnAnimeTitle;
int g_KounterAnimeTitle = 0;
//=============================================================================
// 初期化処理(ポリゴン)
//=============================================================================
void InitTitlebg(void)
{
	LPDIRECT3DDEVICE9 pDevise;						//デバイスのポインタ
													//デバイスの取得
	pDevise = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevise,
		"data\\TEXTURE\\title_bg000.jpg",
		&g_pTextureTitlebg);

	//頂点バッファの生成
	pDevise->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VRETEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitlebg,
		NULL);

	//ローカル変数
	VERTEX_2D*pVtx;								//頂点情報へのポインタ

												//頂点バッファをロックし、頂点データのポインタの取得
	g_pVtxBuffTitlebg->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(PATTERN_X + 0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(PATTERN_X + 0.25f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(PATTERN_X + 0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(PATTERN_X + 0.25f, 1.0f);

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
	g_pVtxBuffTitlebg->Unlock();
}

//=============================================================================
// 終了処理(ポリゴン)
//=============================================================================
void UninitTitlebg(void)
{
	//テクスチャの破棄
	if (g_pTextureTitlebg != NULL)
	{
		g_pTextureTitlebg->Release();
		g_pTextureTitlebg = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffTitlebg != NULL)
	{
		g_pVtxBuffTitlebg->Release();
		g_pVtxBuffTitlebg = NULL;
	}
}

//=============================================================================
// 更新処理(ポリゴン)
//=============================================================================
void UpdateTitlebg(void)
{
	g_PatrnAnimeTitle++;

	//ローカル変数
	VERTEX_2D*pVtx;								//頂点情報へのポインタ
												//頂点バッファをロックし、頂点データのポインタの取得
	g_pVtxBuffTitlebg->Lock(0, 0, (void**)&pVtx, 0);

	g_KounterAnimeTitle++;
	pVtx[0].tex.x = PATTERN_X + 0.0f;
	pVtx[1].tex.x = PATTERN_X + 0.25f;
	pVtx[2].tex.x = PATTERN_X + 0.0f;
	pVtx[3].tex.x = PATTERN_X + 0.25f;

	pVtx += 4;

	//頂点バッファをアンロック
	g_pVtxBuffTitlebg->Unlock();

}

//=============================================================================
// 描画処理(ポリゴン)
//=============================================================================
void DrawTitlebg(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デヴァイスを取得
	pDevice = GetDevice();


	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTitlebg, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VRETEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureTitlebg);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);
}