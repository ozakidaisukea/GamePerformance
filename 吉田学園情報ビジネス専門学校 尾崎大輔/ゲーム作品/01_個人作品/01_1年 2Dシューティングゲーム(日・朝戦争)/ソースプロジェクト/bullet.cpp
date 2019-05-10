//=============================================================================
//
// 弾処理 [bullet.cpp]
// Author : ozaki
//
//=============================================================================
#include "bullet.h"
#include "Explosion.h"
#include "enemy.h"
#include "Player.h"
#include "effect.h"
#include "sound.h"
#include "boss.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MAX_BULLET		(256)		// 弾の最大数
#define MAX_MIKY		(50)		// 弾の大きさ

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;				//位置
	D3DXVECTOR3 move;				//移動量
	BULLETTYPE type;				//弾の種類
	int bullettex;					//テクスチャの種類
	int nLife;						//寿命
	bool bUse;						//使用しているか
}Bullet;

//*****************************************************************************
// グローバル変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureBullet[2] = { NULL };	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;		// 頂点バッファへのポインタ
Bullet g_aBullet[MAX_BULLET];							// 弾の情報

//=============================================================================
// 初期化処理
//=============================================================================
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D*pVtx;														//頂点情報へのポインタ
	int nCntBullet;

	//デヴァイスを取得
	pDevice = GetDevice();

	// 弾の情報の初期化
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].nLife = 30;
		g_aBullet[nCntBullet].bUse = false;
	}
	// テクスチャの読み込み[1敵]
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\12.png",
		&g_pTextureBullet[0]);

	// テクスチャの読み込み[2プレイヤー]
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\abe1.png",
		&g_pTextureBullet[1]);

	// 頂点情報の作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VRETEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL);

	////頂点バッファをロックし、頂点データのポインタの取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - MAX_MIKY, g_aBullet[nCntBullet].pos.y - MAX_MIKY, g_aBullet[nCntBullet].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + MAX_MIKY, g_aBullet[nCntBullet].pos.y - MAX_MIKY, g_aBullet[nCntBullet].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - MAX_MIKY, g_aBullet[nCntBullet].pos.y + MAX_MIKY, g_aBullet[nCntBullet].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + MAX_MIKY, g_aBullet[nCntBullet].pos.y + MAX_MIKY, g_aBullet[nCntBullet].pos.z);

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


		pVtx += 4;					//頂点データのポインタを4つ分進める
	}
	//頂点バッファをアンロック
	g_pVtxBuffBullet->Unlock();
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitBullet(void)
{
	for (int nCnt = 0;nCnt < 2;nCnt++)
	{
		// テクスチャの開放
		if (g_pTextureBullet[nCnt] != NULL)
		{
			g_pTextureBullet[nCnt]->Release();
			g_pTextureBullet[nCnt] = NULL;
		}
	}
	// 頂点バッファの開放
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateBullet(void)
{
	int nCntBullet;

	VERTEX_2D*pVtx;	//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データのポインタの取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{
			g_aBullet[nCntBullet].pos.y -= g_aBullet[nCntBullet].move.y;
			g_aBullet[nCntBullet].pos.x -= g_aBullet[nCntBullet].move.x;

			g_aBullet[nCntBullet].nLife--;

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - MAX_MIKY, g_aBullet[nCntBullet].pos.y - MAX_MIKY, g_aBullet[nCntBullet].pos.z);
			pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + MAX_MIKY, g_aBullet[nCntBullet].pos.y - MAX_MIKY, g_aBullet[nCntBullet].pos.z);
			pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - MAX_MIKY, g_aBullet[nCntBullet].pos.y + MAX_MIKY, g_aBullet[nCntBullet].pos.z);
			pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + MAX_MIKY, g_aBullet[nCntBullet].pos.y + MAX_MIKY, g_aBullet[nCntBullet].pos.z);

			//テクスチャの設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			//一定時間経過
			g_aBullet[nCntBullet].nLife;
			if (g_aBullet[nCntBullet].nLife <= 0)
			{
				SetExplosion(g_aBullet[nCntBullet].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				g_aBullet[nCntBullet].bUse = false;
			}
			if (g_aBullet[nCntBullet].pos.y < 0)
			{
				g_aBullet[nCntBullet].bUse = false;
			}

			if (g_aBullet[nCntBullet].type == BULLETTYPE_ENEMY)
			{
				Player *pPlayer;

				//プレイヤーの取得
				pPlayer = GetPlayer();

				if (pPlayer->bDisp == true)
				{
					if (pPlayer->pos.x - 50 < g_aBullet[nCntBullet].pos.x && pPlayer->pos.x + 50 > g_aBullet[nCntBullet].pos.x
						&& pPlayer->pos.y - 50 < g_aBullet[nCntBullet].pos.y && pPlayer->pos.y + 50 > g_aBullet[nCntBullet].pos.y)
					{
						HitPlayer(1);
						g_aBullet[nCntBullet].bUse = false;		//使用してない状態になる
						PlaySound(SOUND_LABEL_SE_HUMAN1);
					}
				}
			}
			else if (g_aBullet[nCntBullet].type == BULLETTYPE_PLAYER)
			{
				int nCntEnemy;
				Enemy *pEnemy;
				Boss  *pBoss;

				//敵の取得
				pEnemy = GetEnemy();

				pBoss = GetBoss();

				for (nCntEnemy = 0; nCntEnemy < MAX_BULLET; nCntEnemy++, pEnemy++)
				{
					if (pEnemy->bUse == true)					//敵が使用されている
					{
						if (pEnemy->pos.x - 50 < g_aBullet[nCntBullet].pos.x && pEnemy->pos.x + 50 > g_aBullet[nCntBullet].pos.x
							&& pEnemy->pos.y - 50 < g_aBullet[nCntBullet].pos.y && pEnemy->pos.y + 50 > g_aBullet[nCntBullet].pos.y)
						{
							HitEnemy(nCntEnemy, 1);
							g_aBullet[nCntBullet].bUse = false;		//使用してない状態になる

						}
					}
				}
				if (pBoss->bUse == true)				//敵が使用されている
				{
					if (pBoss->pos.x - 200 < g_aBullet[nCntBullet].pos.x && pBoss->pos.x + 200 > g_aBullet[nCntBullet].pos.x
						&& pBoss->pos.y - 200 < g_aBullet[nCntBullet].pos.y && pBoss->pos.y + 200 > g_aBullet[nCntBullet].pos.y)
					{
						HitBoss(0, 1);
						g_aBullet[nCntBullet].bUse = false;		//使用してない状態になる
					}
				}

				SetEffect(g_aBullet[nCntBullet].pos, D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), 50.0f, 50);
			}
		}
		pVtx += 4;
	}

	//頂点バッファをアンロック
	g_pVtxBuffBullet->Unlock();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBullet;

	//デヴァイスを取得
	pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VRETEX_2D);


		// ポリゴンの描画
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{
			if (g_aBullet[nCntBullet].type == BULLETTYPE_PLAYER)
			{
				// テクスチャの設定
				pDevice->SetTexture(0, g_pTextureBullet[1]);

				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
					0 + (4 * nCntBullet),
					2);
			}
			else if (g_aBullet[nCntBullet].type == BULLETTYPE_ENEMY)
			{
				// テクスチャの設定
				pDevice->SetTexture(0, g_pTextureBullet[0]);

				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
					0 + (4 * nCntBullet),
					2);
			}
		}
	}
}

//=============================================================================
// 弾の設定処理
//=============================================================================
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move,BULLETTYPE type)
{
	int nCntBullet;
	VERTEX_2D*pVtx;														//頂点情報へのポインタ

	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == false)		//弾が使用されている
		{
			g_aBullet[nCntBullet].pos = pos;
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - MAX_MIKY, g_aBullet[nCntBullet].pos.y - MAX_MIKY, g_aBullet[nCntBullet].pos.z);
			pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + MAX_MIKY, g_aBullet[nCntBullet].pos.y - MAX_MIKY, g_aBullet[nCntBullet].pos.z);
			pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - MAX_MIKY, g_aBullet[nCntBullet].pos.y + MAX_MIKY, g_aBullet[nCntBullet].pos.z);
			pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + MAX_MIKY, g_aBullet[nCntBullet].pos.y + MAX_MIKY, g_aBullet[nCntBullet].pos.z);
			g_aBullet[nCntBullet].move = move;
			g_aBullet[nCntBullet].nLife = 380;
			g_aBullet[nCntBullet].bUse = true;
			g_aBullet[nCntBullet].type = type;

			break;
		}
		pVtx += 4;
	}
	g_pVtxBuffBullet->Unlock();
}