//=============================================================================
//
// 敵処理 [enemy.cpp]
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
#define	MAX_TYPE_ENEMY		(10)						// 敵の種類
#define MAX_MIKY			(100)
//*****************************************************************************
// グローバル変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_apTextureEnemy[MAX_TYPE_ENEMY] = {};	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;					// 頂点バッファへのポインタ
Enemy g_aEnemy[MAX_ENEMY];										// 敵の情報
int g_nNumEnemy;												// 敵の総数

//=============================================================================
// 初期化処理
//=============================================================================
void InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// 敵の情報の初期化
	for(int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].nType = 0;
		g_aEnemy[nCntEnemy].bUse = false;
		g_aEnemy[nCntEnemy].nCounterState = 0;
		g_aEnemy[nCntEnemy].nLife = 3;
		g_aEnemy[nCntEnemy].nCounterAnim = 0;				//アニメーションカウンター
		g_aEnemy[nCntEnemy].nPatternAnim = 0;				//アニメーションパターン
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;
	}

	// テクスチャの読み込み(10体分)
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\k.png",
		&g_apTextureEnemy[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\kim.png",
		&g_apTextureEnemy[1]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\ana.png", 
		&g_apTextureEnemy[2]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\kimu.png",
		&g_apTextureEnemy[3]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\kii.png",
		&g_apTextureEnemy[4]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\1a.png",
		&g_apTextureEnemy[5]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\1b.png",
		&g_apTextureEnemy[6]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\1c.png",
		&g_apTextureEnemy[7]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\1d.png",
		&g_apTextureEnemy[8]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\1e.png",
		&g_apTextureEnemy[9]);

	// 頂点情報の作成
	VERTEX_2D *pVtx;
	int nCntEnemy;

	// 頂点バッファを生成
    pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ENEMY,
									D3DUSAGE_WRITEONLY,
									FVF_VRETEX_2D,
									D3DPOOL_MANAGED,
									&g_pVtxBuffEnemy,
									NULL);

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for(nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - MAX_MIKY, g_aEnemy[nCntEnemy].pos.y - MAX_MIKY, g_aEnemy[nCntEnemy].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + MAX_MIKY, g_aEnemy[nCntEnemy].pos.y - MAX_MIKY, g_aEnemy[nCntEnemy].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - MAX_MIKY, g_aEnemy[nCntEnemy].pos.y + MAX_MIKY, g_aEnemy[nCntEnemy].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + MAX_MIKY, g_aEnemy[nCntEnemy].pos.y + MAX_MIKY, g_aEnemy[nCntEnemy].pos.z);
		
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
	g_pVtxBuffEnemy->Unlock();
	g_nNumEnemy = 0;				//敵の総数をクリア
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEnemy(void)
{
	int nCntTex;

	// テクスチャの開放
	for(nCntTex = 0; nCntTex < MAX_TYPE_ENEMY; nCntTex++)
	{
		if (g_apTextureEnemy[nCntTex] != NULL)
		{
			g_apTextureEnemy[nCntTex]->Release();
			g_apTextureEnemy[nCntTex] = NULL;
		}
	}

	// 頂点バッファの開放
	if (g_pVtxBuffEnemy != NULL)
	{
		g_pVtxBuffEnemy->Release();
		g_pVtxBuffEnemy = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEnemy(void)
{
	int nCntEnemy;

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)		//敵が使用されている
		{

			g_aEnemy[nCntEnemy].nCounterAnim++;
			if ((g_aEnemy[nCntEnemy].nCounterAnim % 5) == 0)
			{
				g_aEnemy[nCntEnemy].nPatternAnim = (g_aEnemy[nCntEnemy].nPatternAnim + 1 % 8);
				//g_aExplosion[nCntExplosion].pos.y -= 10.0f;

				// 頂点情報の作成
				VERTEX_2D *pVtx;

				g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);
				pVtx += nCntEnemy * 4;

				//頂点座標の設定
				pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - MAX_MIKY, g_aEnemy[nCntEnemy].pos.y - MAX_MIKY, g_aEnemy[nCntEnemy].pos.z);
				pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + MAX_MIKY, g_aEnemy[nCntEnemy].pos.y - MAX_MIKY, g_aEnemy[nCntEnemy].pos.z);
				pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - MAX_MIKY, g_aEnemy[nCntEnemy].pos.y + MAX_MIKY, g_aEnemy[nCntEnemy].pos.z);
				pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + MAX_MIKY, g_aEnemy[nCntEnemy].pos.y + MAX_MIKY, g_aEnemy[nCntEnemy].pos.z);

				//テクスチャの設定
				pVtx[0].tex.x = (0.0f + (0.5f * (g_aEnemy[nCntEnemy].nPatternAnim % 8)));
				pVtx[0].tex.y = (0.0f + 1.0f);

				pVtx[1].tex.x = (0.5f + (0.5f * (g_aEnemy[nCntEnemy].nPatternAnim % 8)));
				pVtx[1].tex.y = (0.0f + 1.0f);

				pVtx[2].tex.x = (0.0f + (0.5f * (g_aEnemy[nCntEnemy].nPatternAnim % 8)));
				pVtx[2].tex.y = (1.0f + 1.0f);

				pVtx[3].tex.x = (0.5f + (0.5f * (g_aEnemy[nCntEnemy].nPatternAnim % 8)));
				pVtx[3].tex.y = (1.0f + 1.0f);

				if (g_aEnemy[nCntEnemy].nPatternAnim >= 8)
				{
					g_aEnemy[nCntEnemy].nPatternAnim = false;
				}
				g_pVtxBuffEnemy->Unlock();
			}

			switch (g_aEnemy[nCntEnemy].state)
			{
			case ENEMYSTATE_NORMAL:
				if (rand() % 60 == 0)
				{
					float Kakudo;
					float Idoux;
					float Idouy;
					Player *pPlayer;

					//プレイヤーの取得
					pPlayer = GetPlayer();
					//プレイヤーとの距離
					Idoux = g_aEnemy[nCntEnemy].pos.x - pPlayer->pos.x;
					Idouy = g_aEnemy[nCntEnemy].pos.y - pPlayer->pos.y;

					Kakudo = atan2f(Idoux, Idouy);

					D3DXVECTOR3 movepos(0.0f, 0.0f, 0.0f);

					movepos.x = sinf(Kakudo) * 10.0f;
					movepos.y = cosf(Kakudo) * 10.0f;


					D3DXVECTOR3 Setpos(g_aEnemy[nCntEnemy].pos.x, g_aEnemy[nCntEnemy].pos.y + 60, 0.0f);
					SetBullet(Setpos, movepos, BULLETTYPE_ENEMY);
				}
				break;

			case ENEMYSTATE_DAMAGE:
				g_aEnemy[nCntEnemy].nCounterState--;
				if (g_aEnemy[nCntEnemy].nCounterState <= 0)
				{
					g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;

					// 頂点情報の作成
					VERTEX_2D *pVtx;

					g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);
					pVtx += nCntEnemy * 4;

					//頂点カラーの設定
					pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

					g_pVtxBuffEnemy->Unlock();
				}
				break;
			}
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
    pDevice->SetStreamSource(0, g_pVtxBuffEnemy, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VRETEX_2D);

	// ポリゴンの描画
	for(int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			//テクスチャの破棄
			pDevice->SetTexture(0, g_apTextureEnemy[g_aEnemy[nCntEnemy].nType]);

			//ポリゴンの破棄
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				0 + (4 * nCntEnemy),
				2);
		}
	}
}

//=============================================================================
// 敵の設定
//=============================================================================
void SetEnemy(D3DXVECTOR3 pos, int nType)
{
	int nCntEnemy;


	// 頂点情報の作成
	VERTEX_2D *pVtx;

	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == false)		//弾が使用されている
		{
			g_aEnemy[nCntEnemy].pos = pos;
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - MAX_MIKY, g_aEnemy[nCntEnemy].pos.y - MAX_MIKY, g_aEnemy[nCntEnemy].pos.z);
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + MAX_MIKY, g_aEnemy[nCntEnemy].pos.y - MAX_MIKY, g_aEnemy[nCntEnemy].pos.z);
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - MAX_MIKY, g_aEnemy[nCntEnemy].pos.y + MAX_MIKY, g_aEnemy[nCntEnemy].pos.z);
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + MAX_MIKY, g_aEnemy[nCntEnemy].pos.y + MAX_MIKY, g_aEnemy[nCntEnemy].pos.z);

			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			g_aEnemy[nCntEnemy].nCounterState = 0;
			g_aEnemy[nCntEnemy].nLife = 3;
			g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;

			g_aEnemy[nCntEnemy].nType = nType;
			g_aEnemy[nCntEnemy].bUse = true;
			g_nNumEnemy++;		//敵の総数を加算する

			break;
		}
		pVtx += 4;
	}
	g_pVtxBuffEnemy->Unlock();
}

//=============================================================================
// 敵の取得
//=============================================================================
Enemy*GetEnemy(void)
{
	return &g_aEnemy[0];
}

//=============================================================================
//敵のダメージ処理
//=============================================================================
void HitEnemy(int nCntEnemy, int nDamage)
{
	g_aEnemy[nCntEnemy].nLife -= nDamage;
	if (g_aEnemy[nCntEnemy].nLife <= 0)
	{
		SetExplosion(g_aEnemy[nCntEnemy].pos , D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.1f));
		PlaySound(SOUND_LABEL_SE_HUMAN3);
		g_aEnemy[nCntEnemy].bUse = false;
		AddScore(1000);
		g_nNumEnemy--;				//敵の総数を減らす
		if (g_nNumEnemy <= 0)
		{
   			SetGameState(GAMESTATE_BOSS);
		}
	}
	else
	{
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_DAMAGE;
		g_aEnemy[nCntEnemy].nCounterState = 5;

		// 頂点情報の作成
		VERTEX_2D *pVtx;

		g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);
		pVtx += nCntEnemy * 4;

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		
		g_pVtxBuffEnemy->Unlock();
	}
}