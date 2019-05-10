//=============================================================================
//
// 背景の処理 [bg.cpp]
// Author : Ozaki
//
//=============================================================================
#include "main.h"
#include "BG.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define BG_WIDTH	(SCREEN_WIDTH)
#define BG_HEIGHT	(SCREEN_HEIGHT)


//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureBG = NULL;				//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBG = NULL;		//テクスチャのポインタ
int g_PatrnAnime = 0;
int g_KounterAnime = 0;
//=============================================================================
// 初期化処理(ポリゴン)
//=============================================================================
void InitBG(void)
{
	LPDIRECT3DDEVICE9 pDevise;						//デバイスのポインタ
	//デバイスの取得
	pDevise = GetDevice();



	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevise,
						      "data\\TEXTURE\\mizu.png",
							  &g_pTextureBG);

	//頂点バッファの生成
	pDevise->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VRETEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBG,
		NULL);

	//ローカル変数
	VERTEX_2D*pVtx;								//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データのポインタの取得
	g_pVtxBuffBG->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//テクスチャの設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f,0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f,1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f,1.0f);

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
	g_pVtxBuffBG->Unlock();
}

//=============================================================================
// 終了処理(ポリゴン)
//=============================================================================
void UninitBG(void)
{
	//テクスチャの破棄
	if (g_pTextureBG != NULL)
	{
		g_pTextureBG->Release();
		g_pTextureBG = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffBG != NULL)
	{
		g_pVtxBuffBG->Release();
		g_pVtxBuffBG = NULL;
	}
}

//=============================================================================
// 更新処理(ポリゴン)
//=============================================================================
void UpdateBG(void)
{
	//ローカル変数
	VERTEX_2D*pVtx;								//頂点情報へのポインタ
												//頂点バッファをロックし、頂点データのポインタの取得
	g_pVtxBuffBG->Lock(0, 0, (void**)&pVtx, 0);

	g_KounterAnime++;
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f - (g_KounterAnime * 0.005f));
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f - (g_KounterAnime * 0.005f));
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f - (g_KounterAnime * 0.005f));
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f - (g_KounterAnime * 0.005f));

	pVtx += 4;

	//頂点バッファをアンロック
	g_pVtxBuffBG->Unlock();

}

//=============================================================================
// 描画処理(ポリゴン)
//=============================================================================
void DrawBG(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デヴァイスを取得
	pDevice = GetDevice();



	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBG, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VRETEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureBG);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
							0,
							2);
}