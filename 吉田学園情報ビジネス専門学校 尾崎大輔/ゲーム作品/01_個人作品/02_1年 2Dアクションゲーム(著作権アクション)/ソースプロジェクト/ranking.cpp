//=============================================================================
//
// ランキング処理 [ranking.cpp]
// Author : Ozaki
//
//=============================================================================
#include "score.h"
#include "Game.h"
#include "main.h"
#include "fade.h"
#include "input.h"
#include "sound.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_Ranking		"data/TEXTURE/Number000.png"	// 読み込むテクスチャファイル名
#define MAX_MIKY			(20)
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexRanking(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureRanking = NULL;			// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRanking = NULL;			// 頂点バッファへのポインタ
int						g_nRanking;							// スコア
D3DXVECTOR3				g_posRanking;
int						nScore;
int						rankingtimer;
//=============================================================================
// 初期化処理
//=============================================================================
void InitRanking(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// スコアの初期化
	rankingtimer = 0;

	//プレイヤーの取得
	g_nRanking = 0;
	g_posRanking = D3DXVECTOR3(600, 350, 0.0f);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
		TEXTURE_Ranking,									// ファイルの名前
		&g_pTextureRanking);								// テクスチャへのポインタ

															// 頂点情報の作成
	MakeVertexRanking(pDevice);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitRanking(void)
{
	// テクスチャの開放
	if (g_pTextureRanking != NULL)
	{
		g_pTextureRanking->Release();
		g_pTextureRanking = NULL;
	}

	// 頂点バッファの開放
	if (g_pVtxBuffRanking != NULL)
	{
		g_pVtxBuffRanking->Release();
		g_pVtxBuffRanking = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateRanking(void)
{
	FADE Fade;
	Fade = GetFade();
	rankingtimer++;


	if (Fade == FADE_NONE)
	{
		if (GetKeyboardTrigger(DIK_RETURN) == true && Fade == FADE_NONE)
		{
			SetFade(MODE_TITLE);
			PlaySound(SOUND_LABEL_SE_DECIDE);

		}
		if (rankingtimer == 700)
		{
			SetFade(MODE_TITLE);
			rankingtimer = 0;
			
		}

	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawRanking(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffRanking, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VRETEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureRanking);

	// ポリゴンの描画
	for (int nCntRanking = 0; nCntRanking < 8; nCntRanking++)
	{
		//ポリゴンの破棄
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			4 * nCntRanking,
			2);
	}
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexRanking(LPDIRECT3DDEVICE9 pDevice)
{

	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 8,
		D3DUSAGE_WRITEONLY,
		FVF_VRETEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRanking,
		NULL);

	VERTEX_2D*pVtx;
	int nRankingda[8];

	//頂点バッファをロックし、頂点データのポインタの取得
	g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);
	nRankingda[0] = g_nRanking / 10000000;
	nRankingda[1] = g_nRanking % 10000000 / 1000000;
	nRankingda[2] = g_nRanking % 1000000 / 100000;
	nRankingda[3] = g_nRanking % 100000 / 10000;
	nRankingda[4] = g_nRanking % 10000 / 1000;
	nRankingda[5] = g_nRanking % 1000 / 100;
	nRankingda[6] = g_nRanking % 100 / 10;
	nRankingda[7] = g_nRanking % 10;

	// 頂点情報を設定
	for (int nCnt = 0; nCnt < 8; nCnt++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_posRanking.x - MAX_MIKY, g_posRanking.y - MAX_MIKY, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posRanking.x + MAX_MIKY, g_posRanking.y - MAX_MIKY, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posRanking.x - MAX_MIKY, g_posRanking.y + MAX_MIKY, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posRanking.x + MAX_MIKY, g_posRanking.y + MAX_MIKY, 0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(0, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(0, 255, 0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);

		pVtx[0].tex = D3DXVECTOR2(0.0f + nRankingda[nCnt] * 0.1f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + nRankingda[nCnt] * 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + nRankingda[nCnt] * 0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + nRankingda[nCnt] * 0.1f, 1.0f);

		pVtx += 4;

		g_posRanking.x += 50;
	}

	//頂点バッファをアンロック
	g_pVtxBuffRanking->Unlock();
}

//=============================================================================
// ランキングの加算
//=============================================================================
void AddRanking(int nValue)
{
	VERTEX_2D*pVtx;

	int nRankingda[8];
	int nCntRankingda;

	g_nRanking = nValue;

	//頂点バッファをロックし、頂点データのポインタの取得
	g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);

	nRankingda[0] = g_nRanking / 10000000;
	nRankingda[1] = g_nRanking % 10000000 / 1000000;
	nRankingda[2] = g_nRanking % 1000000 / 100000;
	nRankingda[3] = g_nRanking % 100000 / 10000;
	nRankingda[4] = g_nRanking % 10000 / 1000;
	nRankingda[5] = g_nRanking % 1000 / 100;
	nRankingda[6] = g_nRanking % 100 / 10;
	nRankingda[7] = g_nRanking % 10;

	for (nCntRankingda = 0; nCntRankingda < 8; nCntRankingda++)
	{
		pVtx[0].tex = D3DXVECTOR2(0.0f + nRankingda[nCntRankingda] * 0.1f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + nRankingda[nCntRankingda] * 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + nRankingda[nCntRankingda] * 0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + nRankingda[nCntRankingda] * 0.1f, 1.0f);

		pVtx += 4;
	}
	//頂点バッファをアンロック
	g_pVtxBuffRanking->Unlock();
}