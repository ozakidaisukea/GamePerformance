//=============================================================================
//
// 背景の処理 [ResultRogo.cpp]
// Author : Ozaki
//
//=============================================================================
#include "main.h"
#include "resultrogo.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define BG_WIDTH	(SCREEN_WIDTH)
#define BG_HEIGHT	(70)

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureResultRogo = NULL;				//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResultRogo = NULL;		//テクスチャのポインタ

//=============================================================================
// 初期化処理(ポリゴン)
//=============================================================================
void InitResultRogo(void)
{
	LPDIRECT3DDEVICE9 pDevise;						//デバイスのポインタ
													//デバイスの取得
	pDevise = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevise,
		"data\\TEXTURE\\result_logo000.png",
		&g_pTextureResultRogo);

	//頂点バッファの生成
	pDevise->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VRETEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResultRogo,
		NULL);

	//ローカル変数
	VERTEX_2D*pVtx;								//頂点情報へのポインタ

												//頂点バッファをロックし、頂点データのポインタの取得
	g_pVtxBuffResultRogo->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

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
	g_pVtxBuffResultRogo->Unlock();
}

//=============================================================================
// 終了処理(ポリゴン)
//=============================================================================
void UninitResultRogo(void)
{
	//テクスチャの破棄
	if (g_pTextureResultRogo != NULL)
	{
		g_pTextureResultRogo->Release();
		g_pTextureResultRogo = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffResultRogo != NULL)
	{
		g_pVtxBuffResultRogo->Release();
		g_pVtxBuffResultRogo = NULL;
	}
}

//=============================================================================
// 更新処理(ポリゴン)
//=============================================================================
void UpdateResultRogo(void)
{

	//ローカル変数
	VERTEX_2D*pVtx;								//頂点情報へのポインタ

												//頂点バッファをロックし、頂点データのポインタの取得
	g_pVtxBuffResultRogo->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += 4;

	//頂点バッファをアンロック
	g_pVtxBuffResultRogo->Unlock();

}

//=============================================================================
// 描画処理(ポリゴン)
//=============================================================================
void DrawResultRogo(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デヴァイスを取得
	pDevice = GetDevice();


	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffResultRogo, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VRETEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureResultRogo);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);
}