//=============================================================================
//
// 弾処理 [block.cpp]
// Author : ozaki
//
//=============================================================================
#include "block.h"
#include "main.h"
#include "Player.h"
#include "Input.h"
#include "sound.h"
#include "item.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MAX_BLOCK		(50)		// ブロックの最大数
#define MAX_MIKY		(50)		// ブロックの大きさ
#define X_Y				(9)			// 当たり数
#define BLOCK_TYPEs		(9)			// ブロックの種類

//*****************************************************************************
// グローバル変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureBlock[BLOCK_TYPEs] = {};		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBlock = NULL;			// 頂点バッファへのポインタ
Block g_aBlock[MAX_BLOCK];								// ブロックの情報

//=============================================================================
// 初期化処理
//=============================================================================
void InitBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D*pVtx;										//頂点情報へのポインタ
	int nCntBlock = 0;

	//デヴァイスを取得
	pDevice = GetDevice();

	// 弾の情報の初期化
	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		g_aBlock[nCntBlock].pos = D3DXVECTOR3(700.0f, 450.0f, 0.0f);
		g_aBlock[nCntBlock].fwidth = 10.0f;
		g_aBlock[nCntBlock].fheight = 10.0f;
		g_aBlock[nCntBlock].move = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		g_aBlock[nCntBlock].bUse = false;
		g_aBlock[nCntBlock].nCntItem = 0;
	}
	// ブロックの読み込み

	// ノーマル [1]
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\bulock.png",
		&g_pTextureBlock[0]);

	// 土管 [2]
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\dokan.png",
		&g_pTextureBlock[1]);

	// ベルトコンベアー [3]
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\block005.jpg",
		&g_pTextureBlock[2]);

	// 氷床 [4]
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\iceblock.png",
		&g_pTextureBlock[3]);

	// ？ブロック1 [5]
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\block200.jpg",
		&g_pTextureBlock[4]);

	// ？ブロック2 [6]
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\block200.jpg",
		&g_pTextureBlock[5]);

	// 移動床 [7]
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\move.png",
		&g_pTextureBlock[6]);

	// ジャンプ台 [8]
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Jun.png",
		&g_pTextureBlock[7]);

	// 石ブロック [9]
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\isi.png",
		&g_pTextureBlock[8]);

	// 頂点情報の作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BLOCK,
		D3DUSAGE_WRITEONLY,
		FVF_VRETEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBlock,
		NULL);

	////頂点バッファをロックし、頂点データのポインタの取得
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y, g_aBlock[nCntBlock].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fwidth ,g_aBlock[nCntBlock].pos.y, g_aBlock[nCntBlock].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fheight, g_aBlock[nCntBlock].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fwidth, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fheight, g_aBlock[nCntBlock].pos.z);

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
	}
	//頂点バッファをアンロック
	g_pVtxBuffBlock->Unlock();
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitBlock(void)
{
	for (int nCnt = 0; nCnt < BLOCK_TYPEs; nCnt++)
	{
		// テクスチャの開放
		if (g_pTextureBlock[nCnt] != NULL)
		{
			g_pTextureBlock[nCnt]->Release();
			g_pTextureBlock[nCnt] = NULL;
		}
	}
	// 頂点バッファの開放
	if (g_pVtxBuffBlock != NULL)
	{
		g_pVtxBuffBlock->Release();
		g_pVtxBuffBlock = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateBlock(void)
{
	int nCntBlock;
	D3DXVECTOR3 move;
	VERTEX_2D*pVtx;										//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データのポインタの取得
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		switch (g_aBlock[nCntBlock].nType)
		{
		case 0:		// 通常ブロック
			break;
		case 1:		// 土管ブロック
			break;
		case 2:		// 氷床
			break;
		case 3:		// ベルトコンベヤ
			break;
		case 4:		// ？ブロック
			break;
		case 5:		//？ブロック
			break;
		case 6:		// 移動床
			g_aBlock[nCntBlock].pos.x += g_aBlock[nCntBlock].move.x;
			if (g_aBlock[nCntBlock].pos.x >= 1000)
			{
				g_aBlock[nCntBlock].move *= -1;

			}
			else if (g_aBlock[nCntBlock].pos.x <= 900)
			{
				g_aBlock[nCntBlock].move *= -1;
			}
			break;
		case 7:		// ジャンプ台
			break;
		case 8:		// 石ブロック
			break;
		}
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y, g_aBlock[nCntBlock].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fwidth, g_aBlock[nCntBlock].pos.y, g_aBlock[nCntBlock].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fheight, g_aBlock[nCntBlock].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fwidth, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fheight, g_aBlock[nCntBlock].pos.z);
		pVtx += 4;				//頂点データのポインタを4つ分進める
	}

	//頂点バッファをアンロック
	g_pVtxBuffBlock->Unlock();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBlock;

	//デヴァイスを取得
	pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pVtxBuffBlock, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VRETEX_2D);

	// ポリゴンの描画
	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{// テクスチャの設定
			pDevice->SetTexture(0, g_pTextureBlock[g_aBlock[nCntBlock].type]);

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				0 + (4 * nCntBlock),
				2);
		}
	}
}
//=============================================================================
// ブロックの設定処理
//=============================================================================
void SetBlock(D3DXVECTOR3 pos,float fwidth,float fheigth, BLOCK_TYPE type)
{
	int nCntBlock;
	VERTEX_2D*pVtx;													//頂点情報へのポインタ

	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == false)						//ブロックが使用されている
		{
			g_aBlock[nCntBlock].pos = pos;
			g_aBlock[nCntBlock].fwidth = fwidth;
			g_aBlock[nCntBlock].fheight = fheigth;
			g_aBlock[nCntBlock].type = type;
			switch (g_aBlock[nCntBlock].type)
			{
			// ノーマル
			case BlockType_Normal:
				g_aBlock[nCntBlock].nType = 0;
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				break;

			// 土管
			case BlockType_Dokan:
				g_aBlock[nCntBlock].nType = 1;
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				break;

				// ベルトコンベアー
			case BlockType_Beltconveyor:
				g_aBlock[nCntBlock].nType = 2;
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				break;

			// 氷床
			case BlockType_Ice:
				g_aBlock[nCntBlock].nType = 3;
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				break;

			// ？ブロック1
			case BlockType_Question1:
				g_aBlock[nCntBlock].nType = 4;
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				break;

				// ？ブロック2
			case BlockType_Question2:
				g_aBlock[nCntBlock].nType = 5;
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				break;

			// 移動床
			case BlockType_Move:
				g_aBlock[nCntBlock].nType = 6;
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				break;

			// ジャンプ台
			case BlockType_Junp:
				g_aBlock[nCntBlock].nType = 7;
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				break;

			// 石ブロック
			case BlockType_Isi:
				g_aBlock[nCntBlock].nType = 8;
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				break;
			}
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y, g_aBlock[nCntBlock].pos.z);
			pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fwidth, g_aBlock[nCntBlock].pos.y, g_aBlock[nCntBlock].pos.z);
			pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fheight, g_aBlock[nCntBlock].pos.z);
			pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fwidth, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fheight, g_aBlock[nCntBlock].pos.z);

			g_aBlock[nCntBlock].bUse = true;
			break;
		}
		pVtx += 4;
	}
		g_pVtxBuffBlock->Unlock();
}

//=============================================================================
// ブロックの当たり判定処理
//=============================================================================
bool CollisionBlock(D3DXVECTOR3 *pPos, D3DXVECTOR3*pPosOld, D3DXVECTOR3 *pMove,float fwigth, float fheigth)								//移動
{
	int nCntBlock;

	bool bLand = false;					//着地したかどうか

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{

		if (g_aBlock[nCntBlock].bUse == true)
		{
			if (pPos->x + fwigth - X_Y >= g_aBlock[nCntBlock].pos.x
				&& pPos->x - fwigth + X_Y <= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fwidth)
			{
				if (pPosOld->y <= g_aBlock[nCntBlock].pos.y && pPos->y >= g_aBlock[nCntBlock].pos.y)
				{//上の当たり判定

					// 各ブロックを仕様
					if (g_aBlock[nCntBlock].type == BlockType_Normal)
					{// ノーマルブロック
						pPos->y = g_aBlock[nCntBlock].pos.y;
						bLand = true;

						pMove->y = 0.0f;
					}
					if (g_aBlock[nCntBlock].type == BlockType_Beltconveyor)
					{// ベルトコンベアー
						pPos->y = g_aBlock[nCntBlock].pos.y;
						bLand = true;
						pPos->x += 3.0f;
						pMove->y = 0.0f;
					}
					if (g_aBlock[nCntBlock].type == BlockType_Dokan)
					{// 土管
						pPosOld->x >= g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fwidth &&
							pPos->x + fwigth <= g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fwidth;
						{//右の当たり判定
							pPosOld->x - X_Y <= g_aBlock[nCntBlock].pos.x &&
								pPos->x - fwigth - X_Y >= g_aBlock[nCntBlock].pos.x;
							{//左の当たり判定
								pPos->y = g_aBlock[nCntBlock].pos.y;
								bLand = true;
								pMove->y = 0.0f;

							}
						}
					}
					if (g_aBlock[nCntBlock].type == BlockType_Question1)
					{// ？ブロック1
						//PlaySound(SOUND_LABRL_SE_COIN);
						pPos->y = g_aBlock[nCntBlock].pos.y;
						bLand = true;

						pMove->y = 0.0f;
					}
					if (g_aBlock[nCntBlock].type == BlockType_Question2)
					{// ？ブロック2
					 //PlaySound(SOUND_LABRL_SE_COIN);
						pPos->y = g_aBlock[nCntBlock].pos.y;
						bLand = true;

						pMove->y = 0.0f;
					}
					if (g_aBlock[nCntBlock].type == BlockType_Ice)
					{// 氷床
						pPos->y = g_aBlock[nCntBlock].pos.y;
						bLand = true;

						pMove->y = 0.01f;
					}
					if (g_aBlock[nCntBlock].type == BlockType_Move)
					{// 移動床
						pPos->x = pPos->x + g_aBlock[nCntBlock].move.x;
						pPos->y = g_aBlock[nCntBlock].pos.y;
						bLand = true;

						pMove->y = 0.0f;
					}

					if (g_aBlock[nCntBlock].type == BlockType_Junp)
					{// ジャンプ台
						pPos->y = g_aBlock[nCntBlock].pos.y;
						bLand = true;
						pMove->y = -40.0f;
					}

					if (g_aBlock[nCntBlock].type == BlockType_Isi)
					{// 石ブロック
						pPos->y = g_aBlock[nCntBlock].pos.y;
						bLand = true;

						pMove->y = 0.0f;
					}
				}
				else if (pPosOld->y - fheigth >= g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fheight
					&& pPos->y - fheigth <= g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fheight)
				{//下の当たり判定
					pPos->y = g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fheight + fheigth;

					pMove->y = 0.0f;
					if (g_aBlock[nCntBlock].type == BlockType_Question1)
					{// ？ブロック1
						if (g_aBlock[nCntBlock].nCntItem < 1)
						{
							PlaySound(SOUND_LABRL_SE_COIN);
							SetItem(g_aBlock[nCntBlock].pos + D3DXVECTOR3(g_aBlock[nCntBlock].fwidth - 33, -40, 0.0f), 50, 50, ITEMSTATE_MUSHROOMS);
							g_aBlock[nCntBlock].nCntItem++;
						}

						pPos->y = g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fheight + fheigth;

						pMove->y = 0.0f;
					}
					if (g_aBlock[nCntBlock].type == BlockType_Question2)
					{// ？ブロック2
						if (g_aBlock[nCntBlock].nCntItem < 1)
						{
							PlaySound(SOUND_LABRL_SE_COIN);
							SetItem(g_aBlock[nCntBlock].pos + D3DXVECTOR3(g_aBlock[nCntBlock].fwidth -35, -60, 0.0f), 100, 100, ITEMSTATE_BIGMUSHROOMS);
							g_aBlock[nCntBlock].nCntItem++;
						}

						pPos->y = g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fheight + fheigth;

						pMove->y = 0.0f;
					}
				}

				if (//頭から足
					pPosOld->y - fheigth >= g_aBlock[nCntBlock].pos.y
					&& pPosOld->y <= g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fheight
					//頭だけ
					|| pPosOld->y - fheigth > g_aBlock[nCntBlock].pos.y
					&& pPosOld->y - fheigth < g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fheight
					// 足だけ
					|| pPosOld->y > g_aBlock[nCntBlock].pos.y
					&& pPosOld->y < g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fheight)
				{
					if (pPosOld->x + 7 >= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fwidth &&
						pPos->x - fwigth + 7 <= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fwidth)
					{//右の当たり判定
						pPos->x = g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fwidth + fwigth - 7;

						pMove->x = 0.0f;
					}
					else if (pPosOld->x - 7 <= g_aBlock[nCntBlock].pos.x &&
						pPos->x + fwigth - 7 >= g_aBlock[nCntBlock].pos.x)
					{//左の当たり判定
						pPos->x = g_aBlock[nCntBlock].pos.x - fwigth + 7;

						pMove->x = 0.0f;
					}
				}
			}
		}
	}
	return bLand;
}

//=============================================================================
//アイテムの取得
//=============================================================================
Block *GetBlock(void)
{
	return &g_aBlock[0];
}