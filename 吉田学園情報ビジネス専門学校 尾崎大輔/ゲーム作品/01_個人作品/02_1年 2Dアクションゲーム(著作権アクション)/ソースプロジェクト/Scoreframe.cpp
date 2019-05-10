//=============================================================================
//
// スコア処理 [scoreframe.cpp]
// Author : Ozaki
//
//=============================================================================
#include "scoreframe.h"
#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_SCORE		"data/TEXTURE/frame_score.png"	// 読み込むテクスチャファイル名
#define MAX_MIKY			(70)

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureScoreFrame = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScoreFrame = NULL;		// 頂点バッファへのポインタ
int						g_nScoreFrame;						// スコア
D3DXVECTOR3				g_posScoreFrame;
int						g_aScoreFrame;
//=============================================================================
// 初期化処理
//=============================================================================
void InitScoreFrame(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// スコアの初期化
	g_nScoreFrame = 0;
	g_posScoreFrame = D3DXVECTOR3(1070, 75, 0.0f);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		TEXTURE_SCORE,		// ファイルの名前
		&g_pTextureScoreFrame);	// テクスチャへのポインタ
								//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VRETEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffScoreFrame,
		NULL);

	//ローカル変数
	VERTEX_2D*pVtx;								//頂点情報へのポインタ

	
	//頂点バッファをロックし、頂点データのポインタの取得
	g_pVtxBuffScoreFrame->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_posScoreFrame.x - MAX_MIKY * 3, g_posScoreFrame.y - MAX_MIKY , g_posScoreFrame.z);
	pVtx[1].pos = D3DXVECTOR3(g_posScoreFrame.x + MAX_MIKY * 3, g_posScoreFrame.y - MAX_MIKY , g_posScoreFrame.z);
	pVtx[2].pos = D3DXVECTOR3(g_posScoreFrame.x - MAX_MIKY * 3, g_posScoreFrame.y + MAX_MIKY / 2, g_posScoreFrame.z);
	pVtx[3].pos = D3DXVECTOR3(g_posScoreFrame.x + MAX_MIKY * 3, g_posScoreFrame.y + MAX_MIKY / 2, g_posScoreFrame.z);

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2( 0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2( 1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2( 0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2( 1.0f, 1.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 0, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 0, 255);
	pVtx[2].col = D3DCOLOR_RGBA(0, 255, 0, 255);
	pVtx[3].col = D3DCOLOR_RGBA(0, 255, 255, 255);

	//頂点バッファをアンロック
	g_pVtxBuffScoreFrame->Unlock();
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitScoreFrame(void)
{
	// テクスチャの開放
	if (g_pTextureScoreFrame != NULL)
	{
		g_pTextureScoreFrame->Release();
		g_pTextureScoreFrame = NULL;
	}

	// 頂点バッファの開放
	if (g_pVtxBuffScoreFrame != NULL)
	{
		g_pVtxBuffScoreFrame->Release();
		g_pVtxBuffScoreFrame = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateScoreFrame(void)
{

}
//=============================================================================
// 描画処理
//=============================================================================
void DrawScoreFrame(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffScoreFrame, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VRETEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureScoreFrame);

	// ポリゴンの描画

		//ポリゴンの破棄
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			0,
			2);	
}