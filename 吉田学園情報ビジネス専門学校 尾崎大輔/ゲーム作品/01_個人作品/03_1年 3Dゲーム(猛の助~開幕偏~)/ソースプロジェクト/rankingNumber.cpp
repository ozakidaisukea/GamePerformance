//=============================================================================
//
// 背景の処理 [RankingNum.cpp]
// Author : Ozaki
//
//=============================================================================
#include "main.h"
#include "rankingNumber.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define RankingNum_WIDTH	(SCREEN_WIDTH)
#define RankingNum_HEIGHT	(SCREEN_HEIGHT)
#define RANKING_NUM			(5)

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureRankingNum = NULL;		//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRankingNum = NULL;				//テクスチャのポインタ

//=============================================================================
// 初期化処理(ポリゴン)
//=============================================================================
void InitRankingNum(void)
{
	LPDIRECT3DDEVICE9 pDevise;						//デバイスのポインタ
													
	//デバイスの取得
	pDevise = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevise,
		"data\\TEXTURE\\ranking_rank.png",
		&g_pTextureRankingNum);

	//頂点バッファの生成
	pDevise->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 *RANKING_NUM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRankingNum,
		NULL);

	//ローカル変数
	VERTEX_2D*pVtx;								//頂点情報へのポインタ

	int Ypos = 0;
	float TexUP = 0;
	float TexDOWN = 0.2;

	//頂点バッファをロックし、頂点データのポインタの取得
	g_pVtxBuffRankingNum->Lock(0, 0, (void**)&pVtx, 0);

	for (int RankingNum = 0; RankingNum < RANKING_NUM; RankingNum++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(400, 100 + Ypos, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(500, 100 + Ypos, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(400, 200 + Ypos, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(500, 200 + Ypos, 0.0f);

		//テクスチャの設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, TexUP);
		pVtx[1].tex = D3DXVECTOR2(1.0f, TexUP);
		pVtx[2].tex = D3DXVECTOR2(0.0f, TexDOWN);
		pVtx[3].tex = D3DXVECTOR2(1.0f, TexDOWN);

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

		// １位
		if (RankingNum == 0)
		{
			pVtx[0].col = D3DCOLOR_RGBA(0, 0, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 155, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 0, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(0, 255, 155, 255);

		// ２位
		}
		if (RankingNum == 1)
		{
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 0, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 55, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 55, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 0, 255);
		}
		// ３位
		if (RankingNum == 2)
		{
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 200, 255);
			pVtx[1].col = D3DCOLOR_RGBA(100, 150, 150, 255);
			pVtx[2].col = D3DCOLOR_RGBA(100, 150, 150, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 200, 255);
		}
		// ４位
		if (RankingNum == 3)
		{
			pVtx[0].col = D3DCOLOR_RGBA(255, 200, 100, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 100, 0, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 100, 0, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 200, 100, 255);
		}
		// ５位
		if (RankingNum == 4)
		{
			
			pVtx[0].col = D3DCOLOR_RGBA(0, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(150, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(150, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(0, 255, 255, 255);
		}

		pVtx += 4;					//頂点データのポインタを4つ分進める
		Ypos += 100;
		TexUP += 0.2;
		TexDOWN += 0.2;
	}

	//頂点バッファをアンロック
	g_pVtxBuffRankingNum->Unlock();
}

//=============================================================================
// 終了処理(ポリゴン)
//=============================================================================
void UninitRankingNum(void)
{
		//テクスチャの破棄
		if (g_pTextureRankingNum != NULL)
		{
			g_pTextureRankingNum->Release();
			g_pTextureRankingNum = NULL;
		}
		//頂点バッファの破棄
		if (g_pVtxBuffRankingNum != NULL)
		{
			g_pVtxBuffRankingNum->Release();
			g_pVtxBuffRankingNum = NULL;
		}
	
}

//=============================================================================
// 更新処理(ポリゴン)
//=============================================================================
void UpdateRankingNum(void)
{

}

//=============================================================================
// 描画処理(ポリゴン)
//=============================================================================
void DrawRankingNum(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デヴァイスを取得
	pDevice = GetDevice();


	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffRankingNum, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureRankingNum);
	for (int RankingNum = 0; RankingNum < RANKING_NUM; RankingNum++)
	{

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			0 + (4 * RankingNum),
			2);
	}
}