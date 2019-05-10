//=============================================================================
//
// エンター処理 [enter2.cpp]
// Author : Ozaki
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "Enter2.h"
#include "fade.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define ENTER_TEXTURENAME		"data\\TEXTURE\\press_enter.png"	// テクスチャ名
#define	ENTER_SIZE0				(30)								// ポーズセレクトの大きさ
#define	ENTER_SIZE1				(120)								// ポーズセレクトの大きさ

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureEnter2 = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnter2 = NULL;	// 頂点バッファへのポインタ
ENTER2 g_Enter2;
int	g_nCntEnter2 = 0;
float g_fEnterTimer2 = 0.0f;

//=============================================================================
// タイトル初期化処理
//=============================================================================
void InitEnter2(void)
{
	LPDIRECT3DDEVICE9 pDevice;	// デバイスへのポインタ

								// デバイスの取得
	pDevice = GetDevice();

	// エンターの情報の初期化
	g_Enter2.pos = D3DXVECTOR3(200, SCREEN_HEIGHT / 2, 0.0f);
	g_Enter2.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, ENTER_TEXTURENAME, &g_pTextureEnter2);

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,	// 確保するバッファのサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,			// 頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffEnter2,
		NULL);

	VERTEX_2D *pVtx;	// 頂点情報へのポインタ

						// 頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffEnter2->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_Enter2.pos.x - ENTER_SIZE1, g_Enter2.pos.y - ENTER_SIZE0, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Enter2.pos.x + ENTER_SIZE1, g_Enter2.pos.y - ENTER_SIZE0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Enter2.pos.x - ENTER_SIZE1, g_Enter2.pos.y + ENTER_SIZE0, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Enter2.pos.x + ENTER_SIZE1, g_Enter2.pos.y + ENTER_SIZE0, 0.0f);

	// rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラー
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点バッファをアンロック
	g_pVtxBuffEnter2->Unlock();
}

//=============================================================================
// タイトル終了処理
//=============================================================================
void UninitEnter2(void)
{
	// テクスチャの破棄
	if (g_pTextureEnter2 != NULL)
	{
		g_pTextureEnter2->Release();
		g_pTextureEnter2 = NULL;
	}

	// 頂点バッファの破棄
	if (g_pVtxBuffEnter2 != NULL)
	{
		g_pVtxBuffEnter2->Release();
		g_pVtxBuffEnter2 = NULL;
	}
}

//=============================================================================
// タイトル更新処理
//=============================================================================
void UpdateEnter2(void)
{
	g_nCntEnter2++;
	if (g_nCntEnter2 >= 10)
	{
		if (g_fEnterTimer2 == 1)
		{
			g_fEnterTimer2 = 0.0f;
		}
		else if (g_fEnterTimer2 == 0)
		{
			g_fEnterTimer2 = 1.0f;
		}

		VERTEX_2D *pVtx;	// 頂点情報へのポインタ

							// 頂点バッファをロックし、頂点データへのポインタを取得
		g_pVtxBuffEnter2->Lock(0, 0, (void**)&pVtx, 0);


		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, g_fEnterTimer2);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, g_fEnterTimer2);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, g_fEnterTimer2);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, g_fEnterTimer2);

		g_nCntEnter2 = 0;
	}

	// 頂点バッファをアンロック
	g_pVtxBuffEnter2->Unlock();
}

//=============================================================================
// タイトル描画処理
//=============================================================================
void DrawEnter2(void)
{
	LPDIRECT3DDEVICE9	pDevice;	// デバイスへのポインタ

									// デバイスを取得する
	pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffEnter2, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureEnter2);

	// タイトルの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}