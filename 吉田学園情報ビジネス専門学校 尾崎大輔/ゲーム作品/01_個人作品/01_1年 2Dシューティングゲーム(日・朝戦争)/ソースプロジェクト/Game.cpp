//=============================================================================
//
// 背景の処理 [Game.cpp]
// Author : Ozaki
//
//=============================================================================
#include "main.h"
#include "BG.h"
#include "bullet.h"
#include "input.h"
#include "Explosion.h"
#include "enemy.h"
#include "Player.h"
#include "Game.h"
#include "score.h"
#include "effect.h"
#include "fade.h"
#include "sound.h"
#include "Gameover.h"
#include "Pause.h"
#include "Time.h"
#include "ranking.h"
#include "boss.h"
#include "rankingBG.h"
#include "PauseBG.h"
#include "pausemenu.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define Game_WIDTH	(SCREEN_WIDTH)
#define Game_HEIGHT	(SCREEN_HEIGHT)

//*****************************************************************************
// グローバル変数
//*****************************************************************************
GAMESTATE g_gameState = GAMESTATE_NONE;			//ゲームの状態
int g_nCounterGameState ;
bool g_bPouse;									//ポーズ中かどうか
int g_CounterBoss;                              // ボスの総数
SELECTMODE *g_Select;
//=============================================================================
// 初期化処理(ポリゴン)
//=============================================================================
void InitGame(void)
{
	g_gameState = GAMESTATE_NORMAL;				//通常状態に設定
	
	g_nCounterGameState = 0;
	g_CounterBoss = 0;

	//背景の初期化処理
	InitBG();
	//プレイヤーの初期化処理
	InitPlayer();
	//弾の初期化処理
	InitBullet();
	//爆発の初期化処理
	InitExplosion();
	//敵の初期化処理
	InitEnemy();
	//ボスの初期化処理
	InitBoss();
	//スコアの初期化処理
	InitScore();
	//エフェクトの初期化処理
	InitEffect();
	//ポーズの初期化処理
	InitPause();
	//時間の初期化処理
	InitTime();
	//ポーズ背景の初期化処理
	//InitPauseBG();
	//ポーズ背景の初期化処理
	//InitPausecont();
	InitPauseSelect();

	//敵の位置
	SetEnemy(D3DXVECTOR3(100, 100, 0), 0);
	SetEnemy(D3DXVECTOR3(300, 100, 0), 1);
	SetEnemy(D3DXVECTOR3(500, 100, 0), 2);
	SetEnemy(D3DXVECTOR3(800, 150, 0), 3);
	SetEnemy(D3DXVECTOR3(1000,150, 0), 4);
	SetEnemy(D3DXVECTOR3(200, 270, 0), 5);
	SetEnemy(D3DXVECTOR3(400, 270, 0), 6);
	SetEnemy(D3DXVECTOR3(600, 270, 0), 7);
	SetEnemy(D3DXVECTOR3(900, 270, 0), 8);
	SetEnemy(D3DXVECTOR3(1100,270, 0), 9);

}

//=============================================================================
// 終了処理(ポリゴン)
//=============================================================================
void UninitGame(void)
{
	//背景の終了処理
	UninitBG();
	//プレイヤーの終了処理
	UninitPlayer();
	//バレットの終了処理
	UninitBullet();
	//爆発の終了処理
	UninitExplosion();
	//敵の終了処理
	UninitEnemy();
	//ボスの終了処理
	UninitBoss();
	//スコアの終了処理
	UninitScore();
	//エフェクトの終了処理
	UninitEffect();
	//ポーズの終了処理
	UninitPause();
	//時間の終了処理
	UninitTime();
	//ポーズ背景の終了処理
	//UninitPauseBG();
	//ポーズ背景の終了処理
//	UninitPausecont();
	UninitPauseSelect();
}

//=============================================================================
// 更新処理(ポリゴン)
//=============================================================================
void UpdateGame(void)
{

	if (GetKeyboardTrigger(DIK_P) == true)
	{//ポーズ ON/OFF
		g_bPouse = g_bPouse ? false : true;
	}
	if (g_bPouse == false)
	{
		//背景の更新処理
		UpdateBG();
		//弾の更新処理
		UpdateBullet();
		//エフェクトの更新処理
		UpdateEffect();
		//爆発の更新処理
		UpdateExplosion();
		//敵の更新処理
		UpdateEnemy();
		//ボスの更新処理
		UpdateBoss();
		//プレイヤーの更新処理
		UpdatePlayer();
		//スコアの更新処理
		UpdateScore();
		//時間の更新処理
		UpdateTime();



		switch (g_gameState)
		{
		case GAMESTATE_NORMAL:
			break;
			//ゲーム終了
		case GAMESTATE_END:
			g_nCounterGameState++;
			if (g_nCounterGameState >= 60)
			{
				g_gameState = GAMESTATE_NONE;
				//画面(モード)の設定
				AddRanking(GetScore());
				SetFade(MODE_RESULT);
			}
			break;
			//ゲームオーバー
		case GAMESTATE_GAMEOVER:
			g_nCounterGameState++;
			if (g_nCounterGameState >= 60)
			{
				g_gameState = GAMESTATE_NONE;
				AddRanking(GetScore());
				//画面(モード)の設定
				SetFade(MODE_GAMEOVER);
			}
			break;

			//ボス
		case GAMESTATE_BOSS:
			if (g_CounterBoss <= 0)
			{
				SetBoss(D3DXVECTOR3(230, 180, 0.0f), 0);
				g_CounterBoss++;
			}

			break;
		
		}
	}
	else
	{
		UpdatePause();
		//UpdatePauseBG();
		//UpdatePausecont();
		UpdatePauseSelect();
		g_Select = GetPauseMode();

		if(*g_Select == SELECTMODE_CONTINE)
		{
			g_bPouse = g_bPouse ? false : true;
			*g_Select = SELECTMODE_NONE;
			PlaySound(SOUND_LABEL_SE_DECIDE);
		}
		if (*g_Select == SELECTMODE_RETRY)
		{
			g_bPouse = g_bPouse ? false : true;
			*g_Select = SELECTMODE_NONE;
			PlaySound(SOUND_LABEL_SE_DECIDE);
		}
		if (*g_Select == SELECTMODE_QUIT)
		{
			g_bPouse = g_bPouse ? false : true;
			*g_Select = SELECTMODE_NONE;
			PlaySound(SOUND_LABEL_SE_DECIDE);
			SetFade(MODE_TITLE);
		}
	}

}

//=============================================================================
// 描画処理(ポリゴン)
//=============================================================================
void DrawGame(void)
{
		//背景の描画処理
		DrawBG();
		//エフェクトの描画処理
		DrawEffect();
		//プレイヤーの描画処理
		DrawPlayer();
		//バレットの描画処理
		DrawBullet();
		//爆発の描画処理
		DrawExplosion();
		//敵の描画処理
		DrawEnemy();
		//ボス描画処理
		DrawBoss();
		//スコアの描画処理
		DrawScore();
		//時間の描画処理
		DrawTime();

		if (g_bPouse == true)
	{//ポーズの描画処理
		DrawPause();
		//DrawPauseBG();
		//DrawPausecont();
		DrawPauseSelect();
	}

}

//=============================================================================
//
//=============================================================================
void SetGameState(GAMESTATE state)
{
	g_gameState = state;
	g_nCounterGameState = 0;
}

//=============================================================================
//
//=============================================================================
GAMESTATE GetGameState(void)
{
	return g_gameState;
}