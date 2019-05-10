//=============================================================================
//
// エンター処理 [enter.cpp]
// Author : Ozaki
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "enter.h"
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
LPDIRECT3DTEXTURE9 g_pTextureEnter = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnter = NULL;	// 頂点バッファへのポインタ
ENTER g_Enter;
int	g_nCntEnter = 0;
float g_fEnterTimer = 0.0f;

//=============================================================================
// タイトル初期化処理
//=============================================================================
void InitEnter(void)
{
	LPDIRECT3DDEVICE9 pDevice;	// デバイスへのポインタ

	// デバイスの取得
	pDevice = GetDevice();

	// エンターの情報の初期化
	g_Enter.pos = D3DXVECTOR3(SCREEN_WIDTH / 2, 570.0f, 0.0f);
	g_Enter.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, ENTER_TEXTURENAME, &g_pTextureEnter);

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,	// 確保するバッファのサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,			// 頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffEnter,
		NULL);

	VERTEX_2D *pVtx;	// 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffEnter->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_Enter.pos.x - ENTER_SIZE1, g_Enter.pos.y - ENTER_SIZE0, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Enter.pos.x + ENTER_SIZE1, g_Enter.pos.y - ENTER_SIZE0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Enter.pos.x - ENTER_SIZE1, g_Enter.pos.y + ENTER_SIZE0, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Enter.pos.x + ENTER_SIZE1, g_Enter.pos.y + ENTER_SIZE0, 0.0f);

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
	g_pVtxBuffEnter->Unlock();
}

//=============================================================================
// タイトル終了処理
//=============================================================================
void UninitEnter(void)
{
	// テクスチャの破棄
	if (g_pTextureEnter != NULL)
	{
		g_pTextureEnter->Release();
		g_pTextureEnter = NULL;
	}

	// 頂点バッファの破棄
	if (g_pVtxBuffEnter != NULL)
	{
		g_pVtxBuffEnter->Release();
		g_pVtxBuffEnter = NULL;
	}
}

//=============================================================================
// タイトル更新処理
//=============================================================================
void UpdateEnter(void)
{
	g_nCntEnter++;
	if (g_nCntEnter >= 10)
	{
		if (g_fEnterTimer == 1)
		{
			g_fEnterTimer = 0.0f;
		}
		else if (g_fEnterTimer == 0)
		{
			g_fEnterTimer = 1.0f;
		}

		VERTEX_2D *pVtx;	// 頂点情報へのポインタ

		// 頂点バッファをロックし、頂点データへのポインタを取得
		g_pVtxBuffEnter->Lock(0, 0, (void**)&pVtx, 0);

		
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, g_fEnterTimer);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, g_fEnterTimer);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, g_fEnterTimer);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, g_fEnterTimer);

		g_nCntEnter = 0;
	}

	// 頂点バッファをアンロック
	g_pVtxBuffEnter->Unlock();
}

//=============================================================================
// タイトル描画処理
//=============================================================================
void DrawEnter(void)
{
	LPDIRECT3DDEVICE9	pDevice;	// デバイスへのポインタ

	// デバイスを取得する
	pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffEnter, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureEnter);

	// タイトルの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}