//=============================================================================
//
// 弾処理 [Dokan.cpp]
// Author : ozaki
//
//=============================================================================
#include "dokan.h"
#include "main.h"
#include "Player.h"
#include "Input.h"
#include "sound.h"
#include "item.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MAX_Dokan		(100)		// ブロックの最大数
#define MAX_MIKY		(50)		// ブロックの大きさ
#define X_Y				(13)		// 当たり数
#define Dokan_TYPEs		(1)			// ブロックの種類
//*****************************************************************************
// グローバル変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureDokan = {};		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffDokan = NULL;					// 頂点バッファへのポインタ
Dokan g_aDokan;										// ブロックの情報

//=============================================================================
// 初期化処理
//=============================================================================
void InitDokan(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D*pVtx;										//頂点情報へのポインタ

	//デヴァイスを取得
	pDevice = GetDevice();

	// 弾の情報の初期化
		g_aDokan.pos = D3DXVECTOR3(680.0f, 600.0f, 0.0f);
		g_aDokan.fwidth = 10.0f;
		g_aDokan.fheight = 10.0f;
		g_aDokan.move = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		g_aDokan.bUse = false;
		g_aDokan.nCntItem = 0;

	// ブロックの読み込み

	// 土管 [2]
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\dokan.png",
		&g_pTextureDokan);

	// 頂点情報の作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_Dokan,
		D3DUSAGE_WRITEONLY,
		FVF_VRETEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffDokan,
		NULL);

	////頂点バッファをロックし、頂点データのポインタの取得
	g_pVtxBuffDokan->Lock(0, 0, (void**)&pVtx, 0);


	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_aDokan.pos.x, g_aDokan.pos.y, g_aDokan.pos.z);
	pVtx[1].pos = D3DXVECTOR3(g_aDokan.pos.x + g_aDokan.fwidth, g_aDokan.pos.y, g_aDokan.pos.z);
	pVtx[2].pos = D3DXVECTOR3(g_aDokan.pos.x, g_aDokan.pos.y + g_aDokan.fheight, g_aDokan.pos.z);
	pVtx[3].pos = D3DXVECTOR3(g_aDokan.pos.x + g_aDokan.fwidth, g_aDokan.pos.y + g_aDokan.fheight, g_aDokan.pos.z);

	//テクスチャの設定
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


	pVtx += 4;				//頂点データのポインタを4つ分進める
	
	//頂点バッファをアンロック
	g_pVtxBuffDokan->Unlock();
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitDokan(void)
{
	// テクスチャの開放
	if (g_pTextureDokan != NULL)
	{
			g_pTextureDokan->Release();
			g_pTextureDokan = NULL;
	}
	// 頂点バッファの開放
	if (g_pVtxBuffDokan != NULL)
	{
		g_pVtxBuffDokan->Release();
		g_pVtxBuffDokan = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateDokan(void)
{

	D3DXVECTOR3 move;
	VERTEX_2D*pVtx;										//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データのポインタの取得
	g_pVtxBuffDokan->Lock(0, 0, (void**)&pVtx, 0);
	//頂点バッファをアンロック
	g_pVtxBuffDokan->Unlock();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawDokan(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffDokan, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VRETEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureDokan);

	// ポリゴンの描画

	//ポリゴンの破棄
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);
	}
//=============================================================================
// ブロックの設定処理
//=============================================================================
void SetDokan(D3DXVECTOR3 pos, float fwidth, float fheigth,Dokan_TYPE type)
{
	
	VERTEX_2D*pVtx;													//頂点情報へのポインタ

	g_pVtxBuffDokan->Lock(0, 0, (void**)&pVtx, 0);

		if (g_aDokan.bUse == false)						//ブロックが使用されている
		{
			g_aDokan.pos = pos;
			g_aDokan.fwidth = fwidth;
			g_aDokan.fheight = fheigth;
			switch (g_aDokan.type)
			{
				// 土管
			case DokanType_Dokan:
				g_aDokan.nType = 1;
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				break;
			}
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aDokan.pos.x, g_aDokan.pos.y, g_aDokan.pos.z);
			pVtx[1].pos = D3DXVECTOR3(g_aDokan.pos.x + g_aDokan.fwidth, g_aDokan.pos.y, g_aDokan.pos.z);
			pVtx[2].pos = D3DXVECTOR3(g_aDokan.pos.x, g_aDokan.pos.y + g_aDokan.fheight, g_aDokan.pos.z);
			pVtx[3].pos = D3DXVECTOR3(g_aDokan.pos.x + g_aDokan.fwidth, g_aDokan.pos.y + g_aDokan.fheight, g_aDokan.pos.z);

			g_aDokan.bUse = true;
			//break;
		}
		pVtx += 4;

	g_pVtxBuffDokan->Unlock();
}

//=============================================================================
// ブロックの当たり判定処理
//=============================================================================
bool CollisionDokan(D3DXVECTOR3 *pPos, D3DXVECTOR3*pPosOld, D3DXVECTOR3 *pMove, float fwigth, float fheigth)								//移動
{
	int nCntDokan;

	bool bLand = false;					//着地したかどうか
	
	Player *pPlayer;
	pPlayer = GetPlayer();

	for (nCntDokan = 0; nCntDokan < MAX_Dokan; nCntDokan++)
	{

		if (g_aDokan.bUse == true)
		{
			if (pPos->x + fwigth - X_Y >= g_aDokan.pos.x
				&& pPos->x - fwigth + X_Y <= g_aDokan.pos.x + g_aDokan.fwidth)
			{
				if (pPosOld->y <= g_aDokan.pos.y && pPos->y >= g_aDokan.pos.y)
				{//上の当たり判定

				 // 各ブロックを仕様
					if (g_aDokan.type == DokanType_Dokan)
					{// 土管
						pPosOld->x >= g_aDokan.pos.x - g_aDokan.fwidth &&
							pPos->x + fwigth <= g_aDokan.pos.x - g_aDokan.fwidth;
						{//右の当たり判定

							pPosOld->x - X_Y <= g_aDokan.pos.x &&
								pPos->x - fwigth - X_Y >= g_aDokan.pos.x;
							{//左の当たり判定
								pPos->y = g_aDokan.pos.y;
								bLand = true;
								pMove->y = 0.0f;
							}
						}
					}
				}
				else if (pPosOld->y - fheigth >= g_aDokan.pos.y + 7/* + g_aDokan.fheight*/
					&& pPos->y - fheigth <= g_aDokan.pos.y + 7/*+ g_aDokan.fheight*/)
				{//下の当たり判定

					Player *pPlayer;
					pPlayer = GetPlayer();

					pPlayer->bJunp = true;


					//pPos->y = g_aDokan.pos.y + g_aDokan.fheight + fheigth;

					pMove->y = 0.0f;

					//pPos->y = g_aDokan.pos.y + g_aDokan.fheight + fheigth;
				}
				if (//頭から足
					pPosOld->y - fheigth >= g_aDokan.pos.y
					&& pPosOld->y <= g_aDokan.pos.y + g_aDokan.fheight
					//頭だけ
					|| pPosOld->y - fheigth > g_aDokan.pos.y
					&& pPosOld->y - fheigth < g_aDokan.pos.y + g_aDokan.fheight
					// 足だけ
					|| pPosOld->y > g_aDokan.pos.y
					&& pPosOld->y < g_aDokan.pos.y + g_aDokan.fheight)
				{
					if (pPosOld->x + X_Y >= g_aDokan.pos.x + g_aDokan.fwidth &&
						pPos->x - fwigth + X_Y <= g_aDokan.pos.x + g_aDokan.fwidth)
					{//右の当たり判定
						pPos->x = g_aDokan.pos.x + g_aDokan.fwidth + fwigth - X_Y;

						pMove->x = 0.0f;
					}
					else if (pPosOld->x - X_Y <= g_aDokan.pos.x &&
						pPos->x + fwigth - X_Y >= g_aDokan.pos.x)
					{//左の当たり判定
						pPos->x = g_aDokan.pos.x - fwigth + X_Y;

						pMove->x = 0.0f;
					}
				}

				if (pPlayer->state == PLAYER_BIGSTATE)
				{


					if (//頭から足
						pPosOld->y - fheigth >= g_aDokan.pos.y
						&& pPosOld->y <= g_aDokan.pos.y + g_aDokan.fheight
						//頭だけ
						|| pPosOld->y - fheigth > g_aDokan.pos.y
						&& pPosOld->y - fheigth < g_aDokan.pos.y + g_aDokan.fheight
						// 足だけ
						|| pPosOld->y > g_aDokan.pos.y
						&& pPosOld->y < g_aDokan.pos.y + g_aDokan.fheight)
					{
						if (pPosOld->x + 7 >= g_aDokan.pos.x + g_aDokan.fwidth &&
							pPos->x - fwigth + 7 <= g_aDokan.pos.x + g_aDokan.fwidth)
						{//右の当たり判定
							pPos->x = g_aDokan.pos.x + g_aDokan.fwidth + fwigth - 7;

							pMove->x = 0.0f;
						}
						else if (pPosOld->x - 7 <= g_aDokan.pos.x &&
							pPos->x + fwigth - 7 >= g_aDokan.pos.x)
						{//左の当たり判定
							pPos->x = g_aDokan.pos.x - fwigth + 7;

							pMove->x = 0.0f;
						}

					}
				}
			}
		}
	}
	return bLand;
}