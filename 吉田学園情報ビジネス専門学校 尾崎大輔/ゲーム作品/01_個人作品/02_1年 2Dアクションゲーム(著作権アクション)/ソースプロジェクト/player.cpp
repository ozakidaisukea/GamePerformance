//=============================================================================
//
// DirectX雛型処理 [player.cpp]
// Author : Ozaki
//
//=============================================================================
#include "main.h"
#include "player.h"
#include "Input.h"
#include "block.h"
#include "player.h"
#include "item.h"
#include "sound.h"
#include "dokan.h"
#include "Game.h"

//*****************************************************************************
//マクロ定義
//*****************************************************************************
#define MAX_MIKY		(40)
#define PLAYER_JNP		(600)
#define MAX_WIDTH		(30)
#define MAX_HEIGHT		(40)

//*****************************************************************************
// グローバル変数
//*****************************************************************************
VERTEX_2D g_aVertex[4];											//頂点情報を格納する
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;						//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;				//テクスチャのポインタ
Player g_Player;
int nCountAnim;
int nPatternAnim;
D3DXVECTOR3 pos;
//=============================================================================
// 初期化処理(ポリゴン)
//=============================================================================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevise;									//デバイスのポインタ

	//デバイスの取得
	pDevise = GetDevice();

	g_Player.pos = D3DXVECTOR3(950.0f, 100.0f, 0.0f);
	g_Player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.bDisp = true;
	g_Player.bJunp = false;
	g_Player.fwidth = MAX_WIDTH;
	g_Player.fheigth = MAX_HEIGHT;
	g_Player.state = PLAYER_NORMAL;
	g_Player.nCounterState = 0;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevise,
		"data\\TEXTURE\\mario2.png",
		&g_pTexturePlayer);

	//頂点バッファの生成
	pDevise->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VRETEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPlayer,
		NULL);

	//ローカル変数
	VERTEX_2D*pVtx;														//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データのポインタの取得
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_Player.pos.x - g_Player.fwidth, g_Player.pos.y - g_Player.fheigth, g_Player.pos.z);
	pVtx[1].pos = D3DXVECTOR3(g_Player.pos.x + g_Player.fwidth, g_Player.pos.y - g_Player.fheigth, g_Player.pos.z);
	pVtx[2].pos = D3DXVECTOR3(g_Player.pos.x - g_Player.fwidth, g_Player.pos.y , g_Player.pos.z);
	pVtx[3].pos = D3DXVECTOR3(g_Player.pos.x + g_Player.fwidth, g_Player.pos.y , g_Player.pos.z);

	//テクスチャの設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
	pVtx[3].tex = D3DXVECTOR2(0.25f, 0.5f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//頂点バッファをアンロック
	g_pVtxBuffPlayer->Unlock();
}

//=============================================================================
// 終了処理(ポリゴン)
//=============================================================================
void UninitPlayer(void)
{
	//テクスチャの破棄
	if (g_pTexturePlayer != NULL)
	{
		g_pTexturePlayer->Release();
		g_pTexturePlayer = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffPlayer != NULL)
	{
		g_pVtxBuffPlayer->Release();
		g_pVtxBuffPlayer = NULL;
	}
}

//=============================================================================
// 更新処理(ポリゴン)
//=============================================================================
void UpdatePlayer(void)
{
	g_Player.posold = g_Player.pos;

	VERTEX_2D*pVtx;							//頂点情報へのポインタ

	//頂点バッファをロックし、テクスチャ座標を更新
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//左移動
	if (GetKeyboardPress(DIK_A) == true)
	{
		//PlaySound(SOUND_LABRL_SE_running);
		g_Player.DirectionMove0 = 1;
		g_Player.move.x += sinf(-D3DX_PI / 2) *1.0f;
		g_Player.move.y += -cosf(D3DX_PI / 2) *1.0f;
	}
	//右移動
	else if (GetKeyboardPress(DIK_D) == true)
	{
		//PlaySound(SOUND_LABRL_SE_running);
		g_Player.DirectionMove0 = 0;
		g_Player.move.x += sinf(D3DX_PI / 2) *1.0f;
		g_Player.move.y += cosf(D3DX_PI / 2) *1.0f;

	}

	//任意のキー(SPACEキー)が押されたかどうか
	if (GetKeyboardTrigger(DIK_SPACE) == true)
	{
		if (g_Player.bJunp == false)
		{
			PlaySound(SOUND_LABRL_SE_junp);
			g_Player.move.y = -20;

			g_Player.bJunp = true;
		}
	}

	if (g_Player.bJunp == false)
	{// ジャンプしていない時
		if (g_Player.move.x > 2 || g_Player.move.x < -2)
		{// 移動しているとき
			g_Player.nCounterAnim++;

			if ((g_Player.nCounterAnim % 5) == 0)
			{
				if(g_Player.nPatternAnim == 2)
				{
					g_Player.nPatternAnim = 1;
				}
				else if(g_Player.nPatternAnim == 1)
				{
					g_Player.nPatternAnim = 2;
				}
				else
				{
					g_Player.nPatternAnim = 1;
				}

				//テクスチャの設定
				pVtx[0].tex = D3DXVECTOR2(g_Player.nPatternAnim * 0.25f, 0.0f + (g_Player.DirectionMove0 * 0.5f));
				pVtx[1].tex = D3DXVECTOR2(g_Player.nPatternAnim * 0.25f + 0.25f, 0.0f + (g_Player.DirectionMove0 * 0.5f));
				pVtx[2].tex = D3DXVECTOR2(g_Player.nPatternAnim * 0.25f, 0.5f + (g_Player.DirectionMove0 * 0.5f));
				pVtx[3].tex = D3DXVECTOR2(g_Player.nPatternAnim * 0.25f + 0.25f, 0.5f + (g_Player.DirectionMove0 * 0.5f));

				//パターンアニメーション
				nPatternAnim++;
			}
		}
		else
		{// 移動していないとき
			if (g_Player.nPatternAnim != 0)
			{
				g_Player.nCounterAnim++;

				if ((g_Player.nCounterAnim % 2) == 0)
				{
					g_Player.nPatternAnim = 0;

					//テクスチャの設定
					pVtx[0].tex = D3DXVECTOR2(g_Player.nPatternAnim * 0.25f, 0.0f + (g_Player.DirectionMove0 * 0.5f));
					pVtx[1].tex = D3DXVECTOR2(g_Player.nPatternAnim * 0.25f + 0.25f, 0.0f + (g_Player.DirectionMove0 * 0.5f));
					pVtx[2].tex = D3DXVECTOR2(g_Player.nPatternAnim * 0.25f, 0.5f + (g_Player.DirectionMove0 * 0.5f));
					pVtx[3].tex = D3DXVECTOR2(g_Player.nPatternAnim * 0.25f + 0.25f, 0.5f + (g_Player.DirectionMove0 * 0.5f));
				}
			}

		}

	}
	else
	{// ジャンプしているとき
		if (g_Player.nPatternAnim != 3)
		{
			g_Player.nCounterAnim++;

			if ((g_Player.nCounterAnim % 10) == 0)
			{
				g_Player.nPatternAnim = 3;

				//テクスチャの設定
				pVtx[0].tex = D3DXVECTOR2(g_Player.nPatternAnim * 0.25f, 0.0f + (g_Player.DirectionMove0 * 0.5f));
				pVtx[1].tex = D3DXVECTOR2(g_Player.nPatternAnim * 0.25f + 0.25f, 0.0f + (g_Player.DirectionMove0 * 0.5f));
				pVtx[2].tex = D3DXVECTOR2(g_Player.nPatternAnim * 0.25f, 0.5f + (g_Player.DirectionMove0 * 0.5f));
				pVtx[3].tex = D3DXVECTOR2(g_Player.nPatternAnim * 0.25f + 0.25f, 0.5f + (g_Player.DirectionMove0 * 0.5f));
			}
		}
	}
	g_Player.move.x += (0.0f - g_Player.move.x) *0.1f;
	g_Player.move.y += 1.0f;

	g_Player.pos.x += g_Player.move.x;
	g_Player.pos.y += g_Player.move.y;

	if (g_Player.pos.x < 0)
	{
		g_Player.pos.x = SCREEN_WIDTH;
		g_Player.posold.x = g_Player.pos.x;
	}

	if (g_Player.pos.x > SCREEN_WIDTH)
	{
		g_Player.pos.x = 0;
		g_Player.posold.x = g_Player.pos.x;
	}
	if (g_Player.pos.y >= SCREEN_HEIGHT)
	{
		GAMESTATE GameState;
		GameState = GetGameState();
		if (GameState != GAMESTATE_GAMEOVER)
		{
			//SetGameState(GAMESTATE_END);
			SetGameState(GAMESTATE_GAMEOVER);
			PlaySound(SOUND_LABEL_SE_MARIO_DETH);
			StopSound(SOUND_LABEL_SE_MARIO_DETH);
		}

	}

	if (CollisionBlock(&g_Player.pos, &g_Player.posold, &g_Player.move, g_Player.fwidth, g_Player.fheigth) == true || CollisionDokan(&g_Player.pos, &g_Player.posold, &g_Player.move, g_Player.fwidth, g_Player.fheigth) == true)
	{
		g_Player.bJunp = false;
	}
	else
	{
		g_Player.bJunp = true;
	}

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_Player.pos.x - g_Player.fwidth, g_Player.pos.y - g_Player.fheigth, g_Player.pos.z);
	pVtx[1].pos = D3DXVECTOR3(g_Player.pos.x + g_Player.fwidth, g_Player.pos.y - g_Player.fheigth, g_Player.pos.z);
	pVtx[2].pos = D3DXVECTOR3(g_Player.pos.x - g_Player.fwidth, g_Player.pos.y, g_Player.pos.z);
	pVtx[3].pos = D3DXVECTOR3(g_Player.pos.x + g_Player.fwidth, g_Player.pos.y, g_Player.pos.z);

	//テクスチャの設定
	pVtx[0].tex = D3DXVECTOR2(g_Player.nPatternAnim * 0.25f, 0.0f + (g_Player.DirectionMove0 * 0.5f));
	pVtx[1].tex = D3DXVECTOR2(g_Player.nPatternAnim * 0.25f + 0.25f, 0.0f + (g_Player.DirectionMove0 * 0.5f));
	pVtx[2].tex = D3DXVECTOR2(g_Player.nPatternAnim * 0.25f, 0.5f + (g_Player.DirectionMove0 * 0.5f));
	pVtx[3].tex = D3DXVECTOR2(g_Player.nPatternAnim * 0.25f + 0.25f, 0.5f + (g_Player.DirectionMove0 * 0.5f));

	CollisionItem(&g_Player.pos, &g_Player.move, g_Player.fwidth, g_Player.fheigth);

	//頂点バッファをアンロック
	g_pVtxBuffPlayer->Unlock();
}

//=============================================================================
// 描画処理(ポリゴン)
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デヴァイスを取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPlayer, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VRETEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTexturePlayer);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);
}
//=============================================================================
// プレイヤーを取得
//=============================================================================
Player *GetPlayer(void)
{
	return &g_Player;
}