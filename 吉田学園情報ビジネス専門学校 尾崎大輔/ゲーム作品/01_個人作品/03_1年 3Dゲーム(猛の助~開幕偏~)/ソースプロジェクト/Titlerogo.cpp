//=============================================================================
//
// 背景の処理 [TitleRogo.cpp]
// Author : Ozaki
//
//=============================================================================
#include "main.h"
#include "Titlerogo.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define BG_WIDTH	(SCREEN_WIDTH)
#define BG_HEIGHT	(SCREEN_HEIGHT)

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureTitleRogo = NULL;				//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitleRogo = NULL;		//テクスチャのポインタ

//=============================================================================
// 初期化処理(ポリゴン)
//=============================================================================
void InitTitleRogo(void)
{
	LPDIRECT3DDEVICE9 pDevise;						//デバイスのポインタ
													//デバイスの取得
	pDevise = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevise,
		"data\\TEXTURE\\title1１.png",
		&g_pTextureTitleRogo);

	//頂点バッファの生成
	pDevise->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitleRogo,
		NULL);

	//ローカル変数
	VERTEX_2D*pVtx;								//頂点情報へのポインタ

												//頂点バッファをロックし、頂点データのポインタの取得
	g_pVtxBuffTitleRogo->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(300, 0, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(950, 0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(300, 600, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(950, 600, 0.0f);

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
	g_pVtxBuffTitleRogo->Unlock();
}

//=============================================================================
// 終了処理(ポリゴン)
//=============================================================================
void UninitTitleRogo(void)
{
	//テクスチャの破棄
	if (g_pTextureTitleRogo != NULL)
	{
		g_pTextureTitleRogo->Release();
		g_pTextureTitleRogo = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffTitleRogo != NULL)
	{
		g_pVtxBuffTitleRogo->Release();
		g_pVtxBuffTitleRogo = NULL;
	}
}

//=============================================================================
// 更新処理(ポリゴン)
//=============================================================================
void UpdateTitleRogo(void)
{

	////ローカル変数
	//VERTEX_2D*pVtx;								//頂点情報へのポインタ

	////頂点バッファをロックし、頂点データのポインタの取得
	//g_pVtxBuffTitleRogo->Lock(0, 0, (void**)&pVtx, 0);

	//pVtx += 4;

	////頂点バッファをアンロック
	//g_pVtxBuffTitleRogo->Unlock();

}

//=============================================================================
// 描画処理(ポリゴン)
//=============================================================================
void DrawTitleRogo(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デヴァイスを取得
	pDevice = GetDevice();


	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTitleRogo, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureTitleRogo);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);
}