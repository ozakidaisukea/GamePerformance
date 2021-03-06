//=============================================================================
//
// 背景の処理 [rankingbg.cpp]
// Author : Ozaki
//
//=============================================================================
#include "main.h"
#include "rankingBG.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define RANKINGBG_WIDTH		(SCREEN_WIDTH)
#define RANKINGBG_HEIGHT	(SCREEN_HEIGHT)


//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureRankingBG = NULL;				//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRankingBG = NULL;		//テクスチャのポインタ

//=============================================================================
// 初期化処理(ポリゴン)
//=============================================================================
void InitRankingBG(void)
{
	LPDIRECT3DDEVICE9 pDevise;						//デバイスのポインタ
													//デバイスの取得
	pDevise = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevise,
		"data\\TEXTURE\\ran.jpg",
		&g_pTextureRankingBG);

	//頂点バッファの生成
	pDevise->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VRETEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRankingBG,
		NULL);

	//ローカル変数
	VERTEX_2D*pVtx;								//頂点情報へのポインタ

												//頂点バッファをロックし、頂点データのポインタの取得
	g_pVtxBuffRankingBG->Lock(0, 0, (void**)&pVtx, 0);

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
	g_pVtxBuffRankingBG->Unlock();
}

//=============================================================================
// 終了処理(ポリゴン)
//=============================================================================
void UninitRankingBG(void)
{
	//テクスチャの破棄
	if (g_pTextureRankingBG != NULL)
	{
		g_pTextureRankingBG->Release();
		g_pTextureRankingBG = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffRankingBG != NULL)
	{
		g_pVtxBuffRankingBG->Release();
		g_pVtxBuffRankingBG = NULL;
	}
}

//=============================================================================
// 更新処理(ポリゴン)
//=============================================================================
void UpdateRankingBG(void)
{

}

//=============================================================================
// 描画処理(ポリゴン)
//=============================================================================
void DrawRankingBG(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デヴァイスを取得
	pDevice = GetDevice();


	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffRankingBG, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VRETEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureRankingBG);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);
}