//=============================================================================
//
// 敵処理 [boss.cpp]
// Author : Ozaki
//
//=============================================================================
#include "enemy.h"
#include "Explosion.h"
#include <time.h>
#include "bullet.h"
#include "Player.h"
#include "Game.h"
#include "score.h"
#include "sound.h"
#include "boss.h"
#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MAX_TYPE_BOSS		(1)						// 敵の種類
#define MAX_MIKY			(200)
//*****************************************************************************
// グローバル変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_apTextureBoss[MAX_TYPE_BOSS] = {};	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBoss = NULL;					// 頂点バッファへのポインタ
Boss g_aBoss[MAX_BOSS];										// 敵の情報
int g_nNumBoss;													// 敵の総数

//=============================================================================
// 初期化処理
//=============================================================================
void InitBoss(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// 敵の情報の初期化
	for (int nCntBoss = 0; nCntBoss < MAX_BOSS; nCntBoss++)
	{
		g_aBoss[nCntBoss].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBoss[nCntBoss].nType = 0;
		g_aBoss[nCntBoss].bUse = false;
		g_aBoss[nCntBoss].nCounterState = 0;
		g_aBoss[nCntBoss].nLife = 26;
		g_aBoss[nCntBoss].nCounterAnim = 0;				//アニメーションカウンター
		g_aBoss[nCntBoss].nPatternAnim = 0;				//アニメーションパターン
		g_aBoss[nCntBoss].state = BOSSSTATE_NORMAL;
	}

	// テクスチャの読み込み(1体分)
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\iru.png",
		&g_apTextureBoss[0]);

	// 頂点情報の作成
	VERTEX_2D *pVtx;
	int nCntBoss;

	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BOSS,
		D3DUSAGE_WRITEONLY,
		FVF_VRETEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBoss,
		NULL);

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBoss->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBoss = 0; nCntBoss < MAX_BOSS; nCntBoss++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x - MAX_MIKY, g_aBoss[nCntBoss].pos.y - MAX_MIKY, g_aBoss[nCntBoss].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + MAX_MIKY, g_aBoss[nCntBoss].pos.y - MAX_MIKY, g_aBoss[nCntBoss].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x - MAX_MIKY, g_aBoss[nCntBoss].pos.y + MAX_MIKY, g_aBoss[nCntBoss].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + MAX_MIKY, g_aBoss[nCntBoss].pos.y + MAX_MIKY, g_aBoss[nCntBoss].pos.z);

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
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);





		pVtx += 4;					//頂点データのポインタを4つ分進める
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffBoss->Unlock();
	g_nNumBoss = 0;					//敵の総数をクリア
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitBoss(void)
{
	int nCntTex;

	// テクスチャの開放
	for (nCntTex = 0; nCntTex < MAX_TYPE_BOSS; nCntTex++)
	{
		if (g_apTextureBoss[nCntTex] != NULL)
		{
			g_apTextureBoss[nCntTex]->Release();
			g_apTextureBoss[nCntTex] = NULL;
		}
	}

	// 頂点バッファの開放
	if (g_pVtxBuffBoss != NULL)
	{
		g_pVtxBuffBoss->Release();
		g_pVtxBuffBoss = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateBoss(void)
{
	int nCntBoss;

	for (nCntBoss = 0; nCntBoss < MAX_BOSS; nCntBoss++)
	{
		if (g_aBoss[nCntBoss].bUse == true)		//敵が使用されている
		{

			g_aBoss[nCntBoss].nCounterAnim++;
			if ((g_aBoss[nCntBoss].nCounterAnim % 5) == 0)
			{
				g_aBoss[nCntBoss].nPatternAnim = (g_aBoss[nCntBoss].nPatternAnim + 1 % 8);
				//g_aExplosion[nCntExplosion].pos.y -= 10.0f;

				// 頂点情報の作成
				VERTEX_2D *pVtx;

				g_pVtxBuffBoss->Lock(0, 0, (void**)&pVtx, 0);
				pVtx += nCntBoss * 4;

				//頂点座標の設定
				pVtx[0].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x - MAX_MIKY, g_aBoss[nCntBoss].pos.y - MAX_MIKY, g_aBoss[nCntBoss].pos.z);
				pVtx[1].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + MAX_MIKY, g_aBoss[nCntBoss].pos.y - MAX_MIKY, g_aBoss[nCntBoss].pos.z);
				pVtx[2].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x - MAX_MIKY, g_aBoss[nCntBoss].pos.y + MAX_MIKY, g_aBoss[nCntBoss].pos.z);
				pVtx[3].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + MAX_MIKY, g_aBoss[nCntBoss].pos.y + MAX_MIKY, g_aBoss[nCntBoss].pos.z);

				//テクスチャの設定
				pVtx[0].tex.x = (0.0f + (0.5f * (g_aBoss[nCntBoss].nPatternAnim % 8)));
				pVtx[0].tex.y = (0.0f + 1.0f);

				pVtx[1].tex.x = (0.5f + (0.5f * (g_aBoss[nCntBoss].nPatternAnim % 8)));
				pVtx[1].tex.y = (0.0f + 1.0f);

				pVtx[2].tex.x = (0.0f + (0.5f * (g_aBoss[nCntBoss].nPatternAnim % 8)));
				pVtx[2].tex.y = (1.0f + 1.0f);

				pVtx[3].tex.x = (0.5f + (0.5f * (g_aBoss[nCntBoss].nPatternAnim % 8)));
				pVtx[3].tex.y = (1.0f + 1.0f);

				if (g_aBoss[nCntBoss].nPatternAnim >= 8)
				{
					g_aBoss[nCntBoss].nPatternAnim = false;
				}
				g_pVtxBuffBoss->Unlock();
			}

			switch (g_aBoss[nCntBoss].state)
			{
			case BOSSSTATE_NORMAL:
				if (rand() % 5 == 0)
				{
					float Kakudo;
					float Idoux;
					float Idouy;
					Player *pPlayer;

					//プレイヤーの取得
					pPlayer = GetPlayer();
					//プレイヤーとの距離
					Idoux = g_aBoss[nCntBoss].pos.x - pPlayer->pos.x;
					Idouy = g_aBoss[nCntBoss].pos.y - pPlayer->pos.y;

					Kakudo = atan2f(Idoux, Idouy);

					D3DXVECTOR3 movepos(0.0f, 0.0f, 0.0f);

					movepos.x = sinf(Kakudo) * 10.0f;
					movepos.y = cosf(Kakudo) * 10.0f;


					D3DXVECTOR3 Setpos(g_aBoss[nCntBoss].pos.x, g_aBoss[nCntBoss].pos.y + 60, 0.0f);
					SetBullet(Setpos, movepos, BULLETTYPE_ENEMY);
				}
				break;

			case BOSSSTATE_DAMAGE:
				g_aBoss[nCntBoss].nCounterState--;
				if (g_aBoss[nCntBoss].nCounterState <= 0)
				{
					g_aBoss[nCntBoss].state = BOSSSTATE_NORMAL;

					// 頂点情報の作成
					VERTEX_2D *pVtx;

					g_pVtxBuffBoss->Lock(0, 0, (void**)&pVtx, 0);
					pVtx += nCntBoss * 4;

					//頂点カラーの設定
					pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

					g_pVtxBuffBoss->Unlock();
				}
				break;
			}
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawBoss(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pVtxBuffBoss, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VRETEX_2D);

	// ポリゴンの描画
	for (int nCntBoss = 0; nCntBoss < MAX_ENEMY; nCntBoss++)
	{
		if (g_aBoss[nCntBoss].bUse == true)
		{
			//テクスチャの破棄
			pDevice->SetTexture(0, g_apTextureBoss[g_aBoss[nCntBoss].nType]);

			//ポリゴンの破棄
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				0 + (4 * nCntBoss),
				2);
		}
	}
}

//=============================================================================
// 敵の設定
//=============================================================================
void SetBoss(D3DXVECTOR3 pos, int nType)
{
	int nCntBoss;


	// 頂点情報の作成
	VERTEX_2D *pVtx;

	g_pVtxBuffBoss->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBoss = 0; nCntBoss < MAX_BOSS; nCntBoss++)
	{
		if (g_aBoss[nCntBoss].bUse == false)		//弾が使用されている
		{
			g_aBoss[nCntBoss].pos = pos;
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x - MAX_MIKY, g_aBoss[nCntBoss].pos.y - MAX_MIKY, g_aBoss[nCntBoss].pos.z);
			pVtx[1].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + MAX_MIKY, g_aBoss[nCntBoss].pos.y - MAX_MIKY, g_aBoss[nCntBoss].pos.z);
			pVtx[2].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x - MAX_MIKY, g_aBoss[nCntBoss].pos.y + MAX_MIKY, g_aBoss[nCntBoss].pos.z);
			pVtx[3].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + MAX_MIKY, g_aBoss[nCntBoss].pos.y + MAX_MIKY, g_aBoss[nCntBoss].pos.z);

			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			g_aBoss[nCntBoss].nCounterState = 0;
			g_aBoss[nCntBoss].nLife = 26;
			g_aBoss[nCntBoss].state = BOSSSTATE_NORMAL;

			g_aBoss[nCntBoss].nType = nType;
			g_aBoss[nCntBoss].bUse = true;
			g_nNumBoss++;		//敵の総数を加算する

			break;
		}
		pVtx += 4;
	}
	g_pVtxBuffBoss->Unlock();
}

//=============================================================================
// 敵の取得
//=============================================================================
Boss*GetBoss(void)
{
	return &g_aBoss[0];
}
//=============================================================================
//敵のダメージ処理
//=============================================================================
void HitBoss(int nCntBoss, int nDamage)
{
	g_aBoss[nCntBoss].nLife -= nDamage;
	if (g_aBoss[nCntBoss].nLife <= 0)
	{
		SetExplosion(g_aBoss[nCntBoss].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.1f));
		PlaySound(SOUND_LABEL_SE_EXPLOSION);
		g_aBoss[nCntBoss].bUse = false;
		AddScore(10000);
		g_nNumBoss--;				//敵の総数を減らす
		if (g_nNumBoss <= 0)
		{
			SetGameState(GAMESTATE_END);
		}
	}
	else
	{
		g_aBoss[nCntBoss].state = BOSSSTATE_DAMAGE;
		g_aBoss[nCntBoss].nCounterState = 5;

		// 頂点情報の作成
		VERTEX_2D *pVtx;

		g_pVtxBuffBoss->Lock(0, 0, (void**)&pVtx, 0);
		pVtx += nCntBoss * 4;

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

		g_pVtxBuffBoss->Unlock();
	}
}