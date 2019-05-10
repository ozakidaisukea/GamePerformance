//=============================================================================
//
// DirectX雛型処理 [player.cpp]
// Author : Ozaki
//
//=============================================================================
#include "main.h"
#include "player.h"
#include "input.h"
#include "bullet.h"
#include "enemy.h"
#include "Player.h"
#include "Explosion.h"
#include "Game.h"
#include "sound.h"

//*****************************************************************************
//マクロ定義
//*****************************************************************************
#define MAX_MIKY		(50)

//*****************************************************************************
// グローバル変数
//*****************************************************************************
VERTEX_2D g_aVertex[4];													//頂点情報を格納する
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;								//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;						//テクスチャのポインタ
int g_nCountAnim;														//アニメーションカウンター
int g_nPatternAnim;														//アニメーションパターン
Player g_Player;

//=============================================================================
// 初期化処理(ポリゴン)
//=============================================================================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevise;											//デバイスのポインタ

	//デバイスの取得
	pDevise = GetDevice();

	g_Player.pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 1.1, 0.0f);
	g_Player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.bDisp = true;

	g_Player.nCounterState = 0;
	g_Player.nLife = 100;
	g_Player.state = PLAYERSTATE_NORMAL;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevise,
						      "data\\TEXTURE\\23.png",
							  &g_pTexturePlayer);

	////テクスチャアニメーション
	//g_nCountAnim = 0;													//カウンターを初期化する
	//g_nPatternAnim = 0;												//パターンを初期化する

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
	pVtx[0].pos = D3DXVECTOR3(g_Player.pos.x - MAX_MIKY, g_Player.pos.y - MAX_MIKY, g_Player.pos.z);
	pVtx[1].pos = D3DXVECTOR3(g_Player.pos.x + MAX_MIKY, g_Player.pos.y - MAX_MIKY, g_Player.pos.z);
	pVtx[2].pos = D3DXVECTOR3(g_Player.pos.x - MAX_MIKY, g_Player.pos.y + MAX_MIKY, g_Player.pos.z);
	pVtx[3].pos = D3DXVECTOR3(g_Player.pos.x + MAX_MIKY, g_Player.pos.y + MAX_MIKY, g_Player.pos.z);

	//テクスチャの設定
	pVtx[0].tex = D3DXVECTOR2(0.0f,0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f,0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f,1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f,1.0f);

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
	if (g_pVtxBuffPlayer  != NULL)
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
	//if (g_Player.pos.x = 0)
	//{
	//	g_Player.move.x = 0;
	//}

	switch (g_Player.state)
	{
	case PLAYERSTATE_NORMAL:
		break;

	case PLAYERSTATE_DAMAGE:
		g_Player.nCounterState--;
		if (g_Player.nCounterState <= 0)
		{
			g_Player.state = PLAYERSTATE_NORMAL;

			VERTEX_2D *pVtx;
			g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//頂点バッファをアンロック
			g_pVtxBuffPlayer->Unlock();
		}
		break;

	case PLAYERSTATE_DEATH:
		g_Player.nCounterState--;
		if (g_Player.nCounterState <= 0)
		{
			g_Player.state = PLAYERSTATE_NORMAL;
			SetGameState(GAMESTATE_GAMEOVER);
		}
		return;
		break;
	}

	if (g_Player.bDisp == true)
	{
		VERTEX_2D*pVtx;														//頂点情報へのポインタ																//頂点バッファをロックし、テクスチャ座標を更新
		g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);
		if (GetKeyboardPress(DIK_A) == true)
		{
			if (GetKeyboardPress(DIK_W) == true)
			{//左上移動
				g_Player.move.x += -sinf(D3DX_PI / 4 * 1) *1.0f;
				g_Player.move.y += -cosf(D3DX_PI / 4 * 1) *1.0f;
			}
			else if (GetKeyboardPress(DIK_S) == true)
			{//左下移動
				g_Player.move.x += -sinf(D3DX_PI / 4 * 3) *1.0f;
				g_Player.move.y += -cosf(D3DX_PI / 4 * 3) *1.0f;
			}
			else
			{// 左移動
				g_Player.move.x += -sinf(D3DX_PI / 2) *1.0f;
				g_Player.move.y += -cosf(D3DX_PI / 2) *1.0f;
			}

		}
		else if (GetKeyboardPress(DIK_D) == true)
		{
			if (GetKeyboardPress(DIK_W) == true)
			{//右上移動
				g_Player.move.x += sinf(D3DX_PI / 4 * 3) *1.0f;
				g_Player.move.y += cosf(D3DX_PI / 4 * 3) *1.0f;
			}
			else if (GetKeyboardPress(DIK_S) == true)
			{//右下移動
				g_Player.move.x += sinf(D3DX_PI / 4 * 1) *1.0f;
				g_Player.move.y += cosf(D3DX_PI / 4 * 1) *1.0f;
			}
			else
			{// 右移動
				g_Player.move.x += sinf(D3DX_PI / 2) *1.0f;
				g_Player.move.y += cosf(D3DX_PI / 2) *1.0f;
			}

		}
		//任意のキー(Sキー)が押されたかどうか
		else if (GetKeyboardPress(DIK_S) == true)
		{
			g_Player.move.x += -sinf(D3DX_PI) *1.0f;
			g_Player.move.y += -cosf(D3DX_PI) *1.0f;
		}
		//任意のキー(Wキー)が押されたかどうか
		else if (GetKeyboardPress(DIK_W) == true)
		{
			g_Player.move.x += sinf(D3DX_PI) *1.0f;
			g_Player.move.y += cosf(D3DX_PI) *1.0f;
		}
		//任意のキー(SPACEキー)が押されたかどうか
		if (GetKeyboardTrigger(DIK_SPACE) == true)
		{
			PlaySound(SOUND_LABEL_SE_ABE);
			SetBullet(g_Player.pos, D3DXVECTOR3(0.0f, 10.0f, 0.0f), BULLETTYPE_PLAYER);
		}

		g_Player.pos.x += g_Player.move.x;
		g_Player.pos.y += g_Player.move.y;

		g_Player.move.x += (0.0f - g_Player.move.x) *0.1f;
		g_Player.move.y += (0.0f - g_Player.move.y) *0.1f;

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_Player.pos.x - MAX_MIKY, g_Player.pos.y - MAX_MIKY, g_Player.pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_Player.pos.x + MAX_MIKY, g_Player.pos.y - MAX_MIKY, g_Player.pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_Player.pos.x - MAX_MIKY, g_Player.pos.y + MAX_MIKY, g_Player.pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_Player.pos.x + MAX_MIKY, g_Player.pos.y + MAX_MIKY, g_Player.pos.z);

		//頂点バッファをアンロック
		g_pVtxBuffPlayer->Unlock();

		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			PlaySound(SOUND_LABEL_SE_DECIDE);
			SetMode(MODE_RESULT);
		}
	}

}

//=============================================================================
// 描画処理(ポリゴン)
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デヴァイスを取得
	pDevice = GetDevice();

	if (g_Player.bDisp == true)
	{
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

}
//=============================================================================
//プレイヤーのポインターの取得
//=============================================================================
Player *GetPlayer(void)
{
		return &g_Player;
}

//=============================================================================
//敵の弾
//=============================================================================
void HitPlayer(int nDamage)
{
	g_Player.nLife -= nDamage;
	if (g_Player.nLife <= 0)
	{
		if (g_Player.bDisp == true)
		{
			SetExplosion(g_Player.pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.1f));
			g_Player.bDisp = false;
			g_Player.state = PLAYERSTATE_DEATH;
			PlaySound(SOUND_LABEL_SE_HUMAN2);
			g_Player.nCounterState = 10;
		}
	}
	else
	{
		g_Player.state = PLAYERSTATE_DAMAGE;
		g_Player.nCounterState = 5;

		// 頂点情報の作成
		VERTEX_2D *pVtx;

		g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

		g_pVtxBuffPlayer->Unlock();
	}
}