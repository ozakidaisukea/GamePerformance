//=============================================================================
//
// スコア処理 [Time.cpp]
// Author : Ozaki
//
//=============================================================================
#include "Time.h"
#include "main.h"
#include "Game.h"
#include "Gameover.h"
#include "sound.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_TIME		"data/TEXTURE/number000.png"	// 読み込むテクスチャファイル名
#define MAX_MIKY			(20)							// 時間の大きさ

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexTime(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureTime = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTime = NULL;		// 頂点バッファへのポインタ
int						g_nTime;					// スコア
int                     g_nTimeCnt;
D3DXVECTOR3				g_posTime;
bool  bTimer;
//=============================================================================
// 初期化処理
//=============================================================================
void InitTime(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// スコアの初期化
	g_nTime = 20;
	g_posTime = D3DXVECTOR3(600, 70, 0.0f);
	bTimer = true;

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		TEXTURE_TIME,								// ファイルの名前
		&g_pTextureTime);							// テクスチャへのポインタ

													// 頂点情報の作成
	MakeVertexTime(pDevice);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitTime(void)
{
	// テクスチャの開放
	if (g_pTextureTime != NULL)
	{
		g_pTextureTime->Release();
		g_pTextureTime = NULL;
	}

	// 頂点バッファの開放
	if (g_pVtxBuffTime != NULL)
	{
		g_pVtxBuffTime->Release();
		g_pVtxBuffTime = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateTime(void)
{
	VERTEX_2D*pVtx;

	int nTimeda[3];
	int nCntTimeda;

	//頂点バッファをロックし、頂点データのポインタの取得
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	if (bTimer == true)
	{
		g_nTimeCnt++;
		if (g_nTimeCnt >= 60)
		{
			g_nTimeCnt = 0;
			g_nTime -= 1;
			if (g_nTime >= 0)
			{
				nTimeda[0] = g_nTime % 1000 / 100;
				nTimeda[1] = g_nTime % 100 / 10;
				nTimeda[2] = g_nTime % 10;

				for (nCntTimeda = 0; nCntTimeda < 3; nCntTimeda++)
				{
					pVtx[0].tex = D3DXVECTOR2(0.0f + nTimeda[nCntTimeda] * 0.1f, 0.0f);
					pVtx[1].tex = D3DXVECTOR2(0.1f + nTimeda[nCntTimeda] * 0.1f, 0.0f);
					pVtx[2].tex = D3DXVECTOR2(0.0f + nTimeda[nCntTimeda] * 0.1f, 1.0f);
					pVtx[3].tex = D3DXVECTOR2(0.1f + nTimeda[nCntTimeda] * 0.1f, 1.0f);

					pVtx += 4;
				}
			}
		}
		else if (g_nTime <= 0)
		{
			GAMESTATE state;
			state = GetGameState();
			if (state == GAMESTATE_NORMAL)
			{
				StopSound(SOUND_LABEL_BGM006);
				PlaySound(SOUND_LABEL_SE_MARIO_DETH);
				SetGameState(GAMESTATE_GAMEOVER);
			}
		}
	}
	//頂点バッファをアンロック
	g_pVtxBuffTime->Unlock();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawTime(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTime, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VRETEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureTime);

	// ポリゴンの描画
	for (int nCntTime = 0; nCntTime < 3; nCntTime++)
	{
		//ポリゴンの破棄
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			4 * nCntTime,
			2);
	}
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexTime(LPDIRECT3DDEVICE9 pDevice)
{
	int nTimeda[3];
	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 3,
		D3DUSAGE_WRITEONLY,
		FVF_VRETEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTime,
		NULL);

	VERTEX_2D*pVtx;


	//頂点バッファをロックし、頂点データのポインタの取得
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	nTimeda[0] = g_nTime % 1000 / 100;
	nTimeda[1] = g_nTime % 100 / 10;
	nTimeda[2] = g_nTime % 10;

	// 頂点情報を設定
	for (int nCnt = 0; nCnt < 3; nCnt++)
	{

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_posTime.x - MAX_MIKY, g_posTime.y - MAX_MIKY, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posTime.x + MAX_MIKY, g_posTime.y - MAX_MIKY, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posTime.x - MAX_MIKY, g_posTime.y + MAX_MIKY, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posTime.x + MAX_MIKY, g_posTime.y + MAX_MIKY, 0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 0,  0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);

		//テクスチャの設定
		pVtx[0].tex = D3DXVECTOR2(0.0f + nTimeda[nCnt] * 0.1f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + nTimeda[nCnt] * 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + nTimeda[nCnt] * 0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + nTimeda[nCnt] * 0.1f, 1.0f);

		pVtx += 4;

		g_posTime.x += 50;
	}
	//頂点バッファをアンロック
	g_pVtxBuffTime->Unlock();

}

//=============================================================================
// 時間の加算
//=============================================================================
void AddTime(int nValue)
{
	VERTEX_2D*pVtx;

	int nTimeda[8];
	int nCntTimeda;

	g_nTime += nValue;

	//頂点バッファをロックし、頂点データのポインタの取得
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	nTimeda[0] = g_nTime / 10000000;
	nTimeda[1] = g_nTime % 10000000 / 1000000;
	nTimeda[2] = g_nTime % 1000000 / 100000;
	nTimeda[3] = g_nTime % 100000 / 10000;
	nTimeda[4] = g_nTime % 10000 / 1000;
	nTimeda[5] = g_nTime % 1000 / 100;
	nTimeda[6] = g_nTime % 100 / 10;
	nTimeda[7] = g_nTime % 10;

	for (nCntTimeda = 0; nCntTimeda < 8; nCntTimeda++)
	{
		pVtx[0].tex = D3DXVECTOR2(0.0f + nTimeda[nCntTimeda] * 0.1f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + nTimeda[nCntTimeda] * 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + nTimeda[nCntTimeda] * 0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + nTimeda[nCntTimeda] * 0.1f, 1.0f);

		pVtx += 4;
	}
	//頂点バッファをアンロック
	g_pVtxBuffTime->Unlock();
}

//=============================================================================
// 時間の取得
//=============================================================================
bool *GetTime(void)
{
	return &bTimer;
}

void StopTimer(void)
{
	bTimer = false;
}