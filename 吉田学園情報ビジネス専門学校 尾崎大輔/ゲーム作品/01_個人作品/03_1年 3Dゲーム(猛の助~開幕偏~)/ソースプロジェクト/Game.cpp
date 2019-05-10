//=============================================================================
//
// 背景の処理 [Game.cpp]
// Author : Ozaki
//
//=============================================================================
#include "main.h"								// メイン
#include "input.h"								// 入手
#include "Player.h"								// プレイヤー
#include "Game.h"								// ゲーム
#include "fade.h"								// フェード
#include "Player.h"								// プレイヤー
#include "camera.h"								// カメラ
#include "model.h"								// モデル
#include "light.h"								// ライト
#include "bullet.h"								// 弾
#include "wall.h"								// 壁
#include "Explosion.h"							// 爆破
#include "camera.h"								// カメラ
#include "polygon.h"							// ポリゴン
#include "light.h"								// ライト
#include "model.h"								// モデル
#include "shadow.h"								// 影
#include "wall.h"								// 壁
#include "bullet.h"								// 弾
#include "billboard.h"							// ビルボード
#include "effect.h"								// エフェクト
#include "Explosion.h"							// 爆発
#include "Player.h"								// プレイヤー
#include "score.h"								// スコア
#include "Scoreframe.h"							// スコア枠
#include "sound.h"								// 音
#include "Pause.h"								// ポーズ
#include "PauseBG.h"							// ポーズ背景
#include "pausemenu.h"							// ポーズメニュー
#include "model.h"
#include "Time.h"								// タイム
#include "Timeframe.h"							// タイム枠
#include "ranking.h"							// ランキング
#include "particle.h"							// パーティクル
#include "Player2.h"
#include "Player3.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define Game_WIDTH	(SCREEN_WIDTH)
#define Game_HEIGHT	(SCREEN_HEIGHT)

//*****************************************************************************
// グローバル変数
//*****************************************************************************
GAMESTATE g_gameState = GAMESTATE_NONE;			//ゲームの状態
int g_nCounterGameState;						//ゲームしてる状態
bool g_bPouse;									//ポーズ中かどうか
SELECTMODE *g_Select;							//
int gametimer;
//=============================================================================
// 初期化処理(ポリゴン)
//=============================================================================
void InitGame(void)
{
	g_gameState = GAMESTATE_NORMAL;				//通常状態に設定

	g_nCounterGameState = 0;

	// 影の初期化処理
	InitShadow();

	//プレイヤーの初期化処理
	InitPlayer();

	//爆発の初期化処理
	//InitExplosion();

	// カメラの初期化処理
	InitCamera();

	// ライトの初期化処理
	InitLight();

	// ポリゴンの初期化処理
	InitPolygon();

	// モデルの初期化処理
	InitModel();

	// 壁の初期化
	InitWall();

	// ビルボード初期化処理
	InitBillboard();

	// 弾の初期化処理
	InitBullet();

	// エフェクトの初期化処理
	InitEffect();

	// 爆発の初期化処理
	InitExplosion();

	// フィールドの初期化処理
	//InitMeshField();

	// メッシュ壁の初期化処理
	//InitMeshWall();

	// メッシュ円柱の初期化処理
	//InitMeshCylinder();

	// プレイヤーの初期化処理
	InitPlayer();

	//スコアの初期化処理
	InitScore();
	InitScoreFrame();

	//ポーズの初期化処理
	InitPause();

	//時間の初期化処理
	InitTime();
	InitTimeFrame();

	//ポーズの初期化処理
	InitPause();
	InitPauseSelect();

	InitParticle();
	// プレイヤー2の初期化処理
	InitPlayer2();

	// プレイヤー3の初期化処理
	InitPlayer3();

	SetWall(D3DXVECTOR3(0.0f, 0.0f, -1000.0f), D3DXVECTOR3(0.0f, D3DX_PI*1.0f, 0.0f));	 // 手前
	SetWall(D3DXVECTOR3(0.0f, 0.0f, 1000.0f), D3DXVECTOR3(0.0f, -D3DX_PI*0.0f, 0.0f));	 // 奥
	SetWall(D3DXVECTOR3(-1000.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI*-0.5f, 0.0f));	 // 左
	SetWall(D3DXVECTOR3(1000.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f));	 // 右

	SetModel(D3DXVECTOR3(800.0f, 0.0f, -1000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetModel(D3DXVECTOR3(400.0f, 0.0f, -1000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1);
	SetModel(D3DXVECTOR3(10.0f, 0.0f, -1000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 2);
	SetModel(D3DXVECTOR3(-400.0f, 0.0f, -1000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3);
	SetModel(D3DXVECTOR3(-800.0f, 0.0f, -1000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 4);


}

//=============================================================================
// 終了処理(ポリゴン)
//=============================================================================
void UninitGame(void)
{
	// カメラの終了処理
	UninitCamera();

	// ライトの終了処理
	UninitLight();

	//プレイヤーの終了処理
	UninitPlayer();

	//プレイヤー2の終了処理
	UninitPlayer2();

	//プレイヤー3の終了処理
	UninitPlayer3();

	//爆発の終了処理
	UninitExplosion();

	// ポリゴンの終了処理
	UninitPolygon();

	// モデルの終了処理
	UninitModel();

	// 影の終了処理
	UninitShadow();

	// 壁の終了処理
	UninitWall();

	// ビルボードの終了処理
	//UninitBillboard();

	// 弾の終了処理
	UninitBullet();

	// エフェクトの終了処理
	//UninitEffect();

	// フィールドの終了処理
	//UninitMeshField();

	// メッシュ壁の終了処理
	//UninitMeshWall();

	// メッシュ円柱の終了処理
	//UninitMeshCylinder();

	////スコアの終了処理
	UninitScore();
	UninitScoreFrame();

	//時間の終了処理
	UninitTime();
	UninitTimeFrame();

	//ポーズの終了処理
	UninitPause();
	UninitPauseSelect();

	UninitParticle();
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
		// カメラの更新処理
		UpdateCamera();

		// ライトの更新処理
		UpdateLight();

		//爆発の更新処理
		UpdateExplosion();
		//プレイヤーの更新処理
		UpdatePlayer();
		//スコアの更新処理
		UpdateScore();
		UpdateScoreFrame();

		//時間の更新処理
		UpdateTime();
		UpdateTimeFrame();

		// ポリゴンの更新処理
		UpdatePolygon();

		// モデルの更新処理
		UpdateModel();

		// 影の更新処理
		UpdateShadow();

		// 壁の更新処理
		UpdateWall();

		// ビルボードの更新処理
	//	UpdateBillboard();

		// 弾の更新処理
		UpdateBullet();

		// エフェクトの更新処理
		UpdateEffect();

		// 爆発の更新処理
		UpdateExplosion();

		// フィールドの更新処理
		//UpdateMeshField();

		// メッシュ壁の更新処理
		//UpdateMeshWall();

		// メッシュ円柱の更新処理
		//UpdateMeshCylinder();

		// プレイヤーの更新処理
		UpdatePlayer();

		// プレイヤー2の更新処理
		UpdatePlayer2();

		// プレイヤー3の更新処理
		UpdatePlayer3();

		UpdateParticle();


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
			if (g_nCounterGameState >= 100)
			{
				g_gameState = GAMESTATE_NONE;
				AddRanking(GetScore());
				//画面(モード)の設定
				SetFade(MODE_GAMEOVER);
			}
			break;
		}
	}
	else
	{
		UpdatePause();
		UpdatePauseSelect();
		g_Select = GetPauseMode();

		if (*g_Select == SELECTMODE_CONTINE)
		{
			g_bPouse = g_bPouse ? false : true;
			*g_Select = SELECTMODE_NONE;
			//PlaySound(SOUND_LABEL_SE_DECIDE);
		}
		if (*g_Select == SELECTMODE_RETRY)
		{
			g_bPouse = g_bPouse ? false : true;
			*g_Select = SELECTMODE_NONE;
			//PlaySound(SOUND_LABEL_SE_DECIDE);
		}
		if (*g_Select == SELECTMODE_QUIT)
		{
			g_bPouse = g_bPouse ? false : true;
			*g_Select = SELECTMODE_NONE;
			//PlaySound(SOUND_LABEL_SE_DECIDE);
			SetFade(MODE_TITLE);
		}
	}

	FADE Fade;
	Fade = GetFade();
	gametimer++;
	if (Fade == FADE_NONE)
	{
		if (GetKeyboardTrigger(DIK_Z) == true)
		{
			if (gametimer >= 3)
			{
				SetFade(MODE_RESULT);
			}


			//SetFade(MODE_TUTORIAL);
			//PlaySound(SOUND_LABEL_SE_DECIDE);
		}
	}

}

//=============================================================================
// 描画処理(ポリゴン)
//=============================================================================
void DrawGame(void)
{
	SetCamera();

	//爆発の描画処理
	DrawExplosion();

	//スコアの描画処理
	DrawScore();
	DrawScoreFrame();

	//時間の描画処理
	DrawTime();
	DrawTimeFrame();

	//プレイヤーの描画処理
	DrawPlayer();

	//プレイヤー2の描画処理
	DrawPlayer2();

	//プレイヤー3の描画処理
	DrawPlayer3();

	DrawPolygon();

	DrawWall();

	//DrawBillboard();

	DrawBullet();

	DrawExplosion();

	DrawModel();

	DrawShadow();

	DrawParticle();

	if (g_bPouse == true)
	{//ポーズの描画処理
		DrawPause();
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