//=============================================================================
//
// スコア処理 [scoreframe.cpp]
// Author : Ozaki
//
//=============================================================================
#include "Timeframe.h"
#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_SCORE		"data/TEXTURE/frame_timer.png"	// 読み込むテクスチャファイル名
#define MAX_MIKY			(80)

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureTimeFrame = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTimeFrame = NULL;		// 頂点バッファへのポインタ
int						g_nTimeFrame;						// スコア
D3DXVECTOR3				g_posTimeFrame;
int						g_aTimeFrame;
//=============================================================================
// 初期化処理
//=============================================================================
void InitTimeFrame(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// スコアの初期化
	g_nTimeFrame = 0;
	g_posTimeFrame = D3DXVECTOR3(650, 60, 0.0f);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		TEXTURE_SCORE,		// ファイルの名前
		&g_pTextureTimeFrame);	// テクスチャへのポインタ
								//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VRETEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTimeFrame,
		NULL);

	//ローカル変数
	VERTEX_2D*pVtx;								//頂点情報へのポインタ


	//頂点バッファをロックし、頂点データのポインタの取得
	g_pVtxBuffTimeFrame->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_posTimeFrame.x - MAX_MIKY, g_posTimeFrame.y - MAX_MIKY / 2, g_posTimeFrame.z);
	pVtx[1].pos = D3DXVECTOR3(g_posTimeFrame.x + MAX_MIKY, g_posTimeFrame.y - MAX_MIKY / 2, g_posTimeFrame.z);
	pVtx[2].pos = D3DXVECTOR3(g_posTimeFrame.x - MAX_MIKY, g_posTimeFrame.y + MAX_MIKY / 2, g_posTimeFrame.z);
	pVtx[3].pos = D3DXVECTOR3(g_posTimeFrame.x + MAX_MIKY, g_posTimeFrame.y + MAX_MIKY / 2, g_posTimeFrame.z);

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
	pVtx[0].col = D3DCOLOR_RGBA(255,0 , 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(0, 255, 0, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 0, 255);
	pVtx[3].col = D3DCOLOR_RGBA(0, 255, 255, 255);

	//頂点バッファをアンロック
	g_pVtxBuffTimeFrame->Unlock();
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitTimeFrame(void)
{
	// テクスチャの開放
	if (g_pTextureTimeFrame != NULL)
	{
		g_pTextureTimeFrame->Release();
		g_pTextureTimeFrame = NULL;
	}

	// 頂点バッファの開放
	if (g_pVtxBuffTimeFrame != NULL)
	{
		g_pVtxBuffTimeFrame->Release();
		g_pVtxBuffTimeFrame = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateTimeFrame(void)
{

}
//=============================================================================
// 描画処理
//=============================================================================
void DrawTimeFrame(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTimeFrame, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VRETEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureTimeFrame);

	//ポリゴンの破棄
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);
}