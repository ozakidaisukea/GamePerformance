//=============================================================================
//
// 背景の処理 [Pausebg.cpp]
// Author : Ozaki
//
//=============================================================================
#include "main.h"
#include "PauseBG.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define PauseBG_WIDTH	(SCREEN_WIDTH)
#define PauseBG_HEIGHT	(SCREEN_HEIGHT)

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTexturePauseBG = NULL;				//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPauseBG = NULL;			//テクスチャのポインタ
int g_PatrnAnimea = 0;
int g_KounterAnimea = 0;

//=============================================================================
// 初期化処理(ポリゴン)
//=============================================================================
void InitPauseBG(void)
{
	LPDIRECT3DDEVICE9 pDevise;						//デバイスのポインタ
													//デバイスの取得
	pDevise = GetDevice();

	////テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevise,
		"data\\TEXTURE\\pause100.png",
		&g_pTexturePauseBG);

	//頂点バッファの生成
	pDevise->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPauseBG,
		NULL);

	//ローカル変数
	VERTEX_2D*pVtx;								//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データのポインタの取得
	g_pVtxBuffPauseBG->Lock(0, 0, (void**)&pVtx, 0);

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
	pVtx[0].col = D3DXCOLOR(1.0f, 0, 0, 0.5);
	pVtx[1].col = D3DXCOLOR(1.0f, 0, 0, 0.5);
	pVtx[2].col = D3DXCOLOR(1.0f, 0, 0, 0.5);
	pVtx[3].col = D3DXCOLOR(1.0f, 0, 0, 0.5);

	//頂点バッファをアンロック
	g_pVtxBuffPauseBG->Unlock();


}

//=============================================================================
// 終了処理(ポリゴン)
//=============================================================================
void UninitPauseBG(void)
{
	//テクスチャの破棄
	if (g_pTexturePauseBG != NULL)
	{
		g_pTexturePauseBG->Release();
		g_pTexturePauseBG = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffPauseBG != NULL)
	{
		g_pVtxBuffPauseBG->Release();
		g_pVtxBuffPauseBG = NULL;
	}
}

//=============================================================================
// 更新処理(ポリゴン)
//=============================================================================
void UpdatePauseBG(void)
{
	////ローカル変数
	//VERTEX_2D*pVtx;								//頂点情報へのポインタ
	//											//頂点バッファをロックし、頂点データのポインタの取得
	//g_pVtxBuffPauseBG->Lock(0, 0, (void**)&pVtx, 0);

	//g_KounterAnimea++;
	//pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f - (g_KounterAnimea * 0.005f));
	//pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f - (g_KounterAnimea * 0.005f));
	//pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f - (g_KounterAnimea * 0.005f));
	//pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f - (g_KounterAnimea * 0.005f));

	//pVtx += 4;

	////頂点バッファをアンロック
	//g_pVtxBuffPauseBG->Unlock();


}

//=============================================================================
// 描画処理(ポリゴン)
//=============================================================================
void DrawPauseBG(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デヴァイスを取得
	pDevice = GetDevice();


	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPauseBG, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTexturePauseBG);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);
}