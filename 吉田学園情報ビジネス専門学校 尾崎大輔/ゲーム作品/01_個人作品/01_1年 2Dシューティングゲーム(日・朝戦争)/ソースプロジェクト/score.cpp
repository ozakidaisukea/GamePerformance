//=============================================================================
//
// スコア処理 [score.cpp]
// Author : Ozaki
//
//=============================================================================
#include "score.h"
#include "Game.h"
#include "enemy.h"
#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_SCORE		"data/TEXTURE/number000.png"	// 読み込むテクスチャファイル名
#define MAX_MIKY			(20)
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexScore(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureScore = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL;		// 頂点バッファへのポインタ
int						g_nScore;					// スコア
D3DXVECTOR3				g_posScore;
int						g_aScore;
//=============================================================================
// 初期化処理
//=============================================================================
void InitScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// スコアの初期化
	g_nScore = 0;
	g_posScore = D3DXVECTOR3(900, 50, 0.0f);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
								TEXTURE_SCORE,		// ファイルの名前
								&g_pTextureScore);	// テクスチャへのポインタ

	// 頂点情報の作成
	MakeVertexScore(pDevice);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitScore(void)
{
	// テクスチャの開放
	if (g_pTextureScore != NULL)
	{
		g_pTextureScore->Release();
		g_pTextureScore = NULL;
	}

	// 頂点バッファの開放
	if (g_pVtxBuffScore != NULL)
	{
		g_pVtxBuffScore->Release();
		g_pVtxBuffScore = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateScore(void)
{

}
//=============================================================================
// 描画処理
//=============================================================================
void DrawScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
    pDevice->SetStreamSource(0, g_pVtxBuffScore, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VRETEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureScore);

	// ポリゴンの描画
	for (int nCntScore = 0; nCntScore < 8; nCntScore++)
	{
		//ポリゴンの破棄
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			4 * nCntScore,
			2);
	}
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexScore(LPDIRECT3DDEVICE9 pDevice)
{

	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 *8,
		D3DUSAGE_WRITEONLY,
		FVF_VRETEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffScore,
		NULL);

		VERTEX_2D*pVtx;


	//頂点バッファをロックし、頂点データのポインタの取得
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報を設定
	for (int nCnt = 0; nCnt < 8; nCnt++)
	{
		//g_aExplosion[nCntExplosion].pos.y -= 10.0f;
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_posScore.x - MAX_MIKY, g_posScore.y - MAX_MIKY, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posScore.x + MAX_MIKY, g_posScore.y - MAX_MIKY, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posScore.x - MAX_MIKY, g_posScore.y + MAX_MIKY, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posScore.x + MAX_MIKY, g_posScore.y + MAX_MIKY, 0.0f);


		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(0, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(0, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(0, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(0, 255, 255, 255);

		//テクスチャの設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;

		g_posScore.x += 50;
	}
	//g_posScore.x = 1200;

	//頂点バッファをアンロック
	g_pVtxBuffScore->Unlock();

}

//=============================================================================
// スコアの加算
//=============================================================================
void AddScore(int nValue)
{
	VERTEX_2D*pVtx;

	int nScoreda[8];
	int nCntScoreda;

	g_nScore += nValue * 2;

	//頂点バッファをロックし、頂点データのポインタの取得
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	nScoreda[0] = g_nScore / 10000000;
	nScoreda[1] = g_nScore % 10000000 / 1000000;
	nScoreda[2] = g_nScore % 1000000 / 100000;
	nScoreda[3] = g_nScore % 100000 / 10000;
	nScoreda[4] = g_nScore % 10000 / 1000;
	nScoreda[5] = g_nScore % 1000 / 100;
	nScoreda[6] = g_nScore % 100 / 10;
	nScoreda[7] = g_nScore % 10;

	for (nCntScoreda = 0; nCntScoreda < 8; nCntScoreda++)
	{
		pVtx[0].tex = D3DXVECTOR2(0.0f + nScoreda[nCntScoreda] * 0.1f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + nScoreda[nCntScoreda] * 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + nScoreda[nCntScoreda] * 0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + nScoreda[nCntScoreda] * 0.1f, 1.0f);

		pVtx += 4;
	}
	//頂点バッファをアンロック
	g_pVtxBuffScore->Unlock();
}

//=============================================================================
// 敵の取得
//=============================================================================
int GetScore(void)
{
	return g_nScore;
}