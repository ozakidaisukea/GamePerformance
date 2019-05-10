//=============================================================================
//
// 背景の処理 [bg.cpp]
// Author : Ozaki
//
//=============================================================================
#include "main.h"
#include "rankingrogo.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define BG_WIDTH	(SCREEN_WIDTH)
#define BG_HEIGHT	(20)

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureRankingRogo = NULL;				//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRankingRogo = NULL;		//テクスチャのポインタ
int g_PatrnAnimeRankingRogo;
int g_KounterAnimeRankingRogo = 0;
//=============================================================================
// 初期化処理(ポリゴン)
//=============================================================================
void InitRankingRogo(void)
{
	LPDIRECT3DDEVICE9 pDevise;						//デバイスのポインタ
													//デバイスの取得
	pDevise = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevise,
		"data\\TEXTURE\\HighScores.png",
		&g_pTextureRankingRogo);

	//頂点バッファの生成
	pDevise->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VRETEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRankingRogo,
		NULL);

	//ローカル変数
	VERTEX_2D*pVtx;								//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データのポインタの取得
	g_pVtxBuffRankingRogo->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(400, 150, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(900, 150, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(400, 200, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(900, 200, 0.0f);

	// テクスチャ座標の設定
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
	g_pVtxBuffRankingRogo->Unlock();
}

//=============================================================================
// 終了処理(ポリゴン)
//=============================================================================
void UninitRankingRogo(void)
{
	//テクスチャの破棄
	if (g_pTextureRankingRogo != NULL)
	{
		g_pTextureRankingRogo->Release();
		g_pTextureRankingRogo = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffRankingRogo != NULL)
	{
		g_pVtxBuffRankingRogo->Release();
		g_pVtxBuffRankingRogo = NULL;
	}
}

//=============================================================================
// 更新処理(ポリゴン)
//=============================================================================
void UpdateRankingRogo(void)
{

	//ローカル変数
	VERTEX_2D*pVtx;								//頂点情報へのポインタ
	
	//頂点バッファをロックし、頂点データのポインタの取得
	g_pVtxBuffRankingRogo->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += 4;

	//頂点バッファをアンロック
	g_pVtxBuffRankingRogo->Unlock();

}

//=============================================================================
// 描画処理(ポリゴン)
//=============================================================================
void DrawRankingRogo(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デヴァイスを取得
	pDevice = GetDevice();


	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffRankingRogo, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VRETEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureRankingRogo);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);
}