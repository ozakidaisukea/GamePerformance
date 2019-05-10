//=============================================================================
//
// 背景の処理 [bg2.cpp]
// Author : Ozaki
//
//=============================================================================
#include "main.h"
#include "bg2.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define BG_WIDTH	(SCREEN_WIDTH)
#define BG_HEIGHT	(SCREEN_HEIGHT)
#define PATTERN_X (0.00005f * g_PatrnAnime2)

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTexturebg2 = NULL;				//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffbg2 = NULL;		//テクスチャのポインタ
int g_PatrnAnime2;
int g_KounterAnime2 = 0;
//=============================================================================
// 初期化処理(ポリゴン)
//=============================================================================
void Initbg2(void)
{
	LPDIRECT3DDEVICE9 pDevise;						//デバイスのポインタ
													//デバイスの取得
	pDevise = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevise,
		"data\\TEXTURE\\mountain000.png",
		&g_pTexturebg2);

	//頂点バッファの生成
	pDevise->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VRETEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffbg2,
		NULL);

	//ローカル変数
	VERTEX_2D*pVtx;								//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データのポインタの取得
	g_pVtxBuffbg2->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0, 500, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 500, 0.0f);
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
	g_pVtxBuffbg2->Unlock();
}

//=============================================================================
// 終了処理(ポリゴン)
//=============================================================================
void Uninitbg2(void)
{
	//テクスチャの破棄
	if (g_pTexturebg2 != NULL)
	{
		g_pTexturebg2->Release();
		g_pTexturebg2 = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffbg2 != NULL)
	{
		g_pVtxBuffbg2->Release();
		g_pVtxBuffbg2 = NULL;
	}
}

//=============================================================================
// 更新処理(ポリゴン)
//=============================================================================
void Updatebg2(void)
{
	g_PatrnAnime2++;

	//ローカル変数
	VERTEX_2D*pVtx;								//頂点情報へのポインタ
												//頂点バッファをロックし、頂点データのポインタの取得
	g_pVtxBuffbg2->Lock(0, 0, (void**)&pVtx, 0);

	g_KounterAnime2++;
	pVtx[0].tex.x = PATTERN_X + 0.0f;
	pVtx[1].tex.x = PATTERN_X + 0.2f;
	pVtx[2].tex.x = PATTERN_X + 0.0f;
	pVtx[3].tex.x = PATTERN_X + 0.2f;

	pVtx += 4;

	//頂点バッファをアンロック
	g_pVtxBuffbg2->Unlock();
}

//=============================================================================
// 描画処理(ポリゴン)
//=============================================================================
void Drawbg2(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デヴァイスを取得
	pDevice = GetDevice();


	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffbg2, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VRETEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTexturebg2);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);
}