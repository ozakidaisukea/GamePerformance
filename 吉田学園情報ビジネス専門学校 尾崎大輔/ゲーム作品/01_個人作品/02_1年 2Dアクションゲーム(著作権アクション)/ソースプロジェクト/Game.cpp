//=============================================================================
//
// 背景の処理 [Game.cpp]
// Author : Ozaki
//
//=============================================================================
#include "main.h"								// メイン
#include "bg.h"									// 背景
#include "bg2.h"								// 背景２
#include "block.h"								// ブロック
#include "input.h"								// 入手
#include "Player.h"								// プレイヤー
#include "Game.h"								// ゲーム
#include "item.h"								// アイテム
#include "fade.h"								// フェード
#include "score.h"								// スコア
#include "Scoreframe.h"							// スコア枠
#include "sound.h"								// 音
#include "Gameover.h"							// ゲームオーヴァー
#include "Pause.h"								// ポーズ
#include "Time.h"								// 時間
#include "Timeframe.h"							// 時間枠
#include "ranking.h"							// ランキング
#include "rankingBG.h"							// ランキング背景
#include "PauseBG.h"							// ポーズ背景
#include "pausemenu.h"							// ポーズメニュー
#include "Explosion.h"							// 爆発
#include "dokan.h"								// 土管

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

BlockInfo g_aBlockInfo[] =						//各ブロックの位置と種類
{

	{ D3DXVECTOR3(160, 200, 0.0f), 40, 40,BlockType_Normal },			// 通常ブロック(左)1
	{ D3DXVECTOR3(160, 240, 0.0f), 40, 40,BlockType_Normal },			// 通常ブロック(左)2
	{ D3DXVECTOR3(160, 280, 0.0f), 40, 40,BlockType_Normal },			// 通常ブロック(左)4
	{ D3DXVECTOR3(160, 320, 0.0f), 40, 40,BlockType_Normal },			// 通常ブロック(左)5
	{ D3DXVECTOR3(160, 360, 0.0f), 40, 40,BlockType_Normal },			// 通常ブロック(左)7
	{ D3DXVECTOR3(160, 400, 0.0f), 40, 40,BlockType_Normal },			// 通常ブロック(左)8
	{ D3DXVECTOR3(160, 440, 0.0f), 40, 40,BlockType_Normal },			// 通常ブロック(左)9
	{ D3DXVECTOR3(160, 480, 0.0f), 40, 40,BlockType_Normal },			// 通常ブロック(左)10
	{ D3DXVECTOR3(160, 520, 0.0f), 40, 40,BlockType_Normal },			// 通常ブロック(左)11
	{ D3DXVECTOR3(160, 560, 0.0f), 40, 40,BlockType_Normal },			// 通常ブロック(左)12
	{ D3DXVECTOR3(160, 600, 0.0f), 40, 40,BlockType_Normal },			// 通常ブロック(左)13
	{ D3DXVECTOR3(160, 640, 0.0f), 40, 40,BlockType_Normal },			// 通常ブロック(左)14

	{ D3DXVECTOR3(900, 630, 0.0f), 300, 50,BlockType_Beltconveyor },	// ベルトコンベヤ
	{ D3DXVECTOR3(550, 350, 0.0f), 83, 50,BlockType_Ice },				// 氷床

	{ D3DXVECTOR3(400, 200, 0.0f), 40, 40,BlockType_Normal },			// 通常ブロック(右)1
	{ D3DXVECTOR3(400, 240, 0.0f), 40, 40,BlockType_Normal },			// 通常ブロック(右)2
	{ D3DXVECTOR3(400, 280, 0.0f), 40, 40,BlockType_Normal },			// 通常ブロック(右)3
	{ D3DXVECTOR3(400, 320, 0.0f), 40, 40,BlockType_Normal },			// 通常ブロック(右)4
	{ D3DXVECTOR3(400, 360, 0.0f), 40, 40,BlockType_Normal },			// 通常ブロック(右)5
	{ D3DXVECTOR3(400, 400, 0.0f), 40, 40,BlockType_Normal },			// 通常ブロック(右)6
	{ D3DXVECTOR3(400, 440, 0.0f), 40, 40,BlockType_Normal },			// 通常ブロック(右)7
	{ D3DXVECTOR3(400, 480, 0.0f), 40, 40,BlockType_Normal },			// 通常ブロック(右)8
	{ D3DXVECTOR3(400, 520, 0.0f), 40, 40,BlockType_Normal },			// 通常ブロック(右)9
	{ D3DXVECTOR3(400, 560, 0.0f), 40, 40,BlockType_Normal },			// 通常ブロック(右)10
	{ D3DXVECTOR3(400, 600, 0.0f), 40, 40,BlockType_Normal },			// 通常ブロック(右)11
	{ D3DXVECTOR3(400, 640, 0.0f), 40, 40,BlockType_Normal },			// 通常ブロック(右)12

	{ D3DXVECTOR3(220, 620, 0.0f), 60, 70, BlockType_Junp },			// ジャンプ台
	{ D3DXVECTOR3(310, 400, 0.0f), 90, 40, BlockType_Isi },				// 石ブロック
	{ D3DXVECTOR3(900, 460, 0.0f), 160, 40, BlockType_Move },			// 移動床
	{ D3DXVECTOR3(700, 400, 0.0f), 60, 60, BlockType_Question1 },		// ？1ブロック
	{ D3DXVECTOR3(80, 500, 0.0f), 60, 60, BlockType_Question2 },		// ？2ブロック
	{ D3DXVECTOR3(-100,680, 0.0f), 1500, 40, BlockType_Normal},			// 床ブロック
};

ItemInfo g_aItemInfo[] =						//各アイテムの位置
{
	{D3DXVECTOR3(500, 450, 0.0f), 30,50,ITEMSTATE_COIN },
	{D3DXVECTOR3(850, 550, 0.0f), 30,50,ITEMSTATE_COIN },
	{D3DXVECTOR3(200, 160, 0.0f), 30,50,ITEMSTATE_COIN },
	{D3DXVECTOR3(100, 250, 0.0f), 30,50,ITEMSTATE_COIN },
	{D3DXVECTOR3(10,  500, 0.0f), 30,50,ITEMSTATE_COIN },
	{D3DXVECTOR3(250, 160, 0.0f), 30,50,ITEMSTATE_COIN },
	{D3DXVECTOR3(400, 160, 0.0f), 30,50,ITEMSTATE_COIN },
	{D3DXVECTOR3(360, 600, 0.0f), 30,50,ITEMSTATE_COIN },
};

//=============================================================================
// 初期化処理(ポリゴン)
//=============================================================================
void InitGame(void)
{
	g_gameState = GAMESTATE_NORMAL;				//通常状態に設定

	g_nCounterGameState = 0;

	//背景の初期化処理
	Initbg();
	//背景の初期化処理
	Initbg2();
	//ブロックの初期化処理
	InitBlock();
	InitDokan();
	//プレイヤーの初期化処理
	InitPlayer();
	//アイテムの初期化処理
	InitItem();
	//爆発の初期化処理
	InitExplosion();
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

	int nCntBlock = 0;
	int nCntItem = 0;
	//ブロックの初期位置(横位置,縦位置,高さ),横幅,立幅,ブロック名);
	for ( nCntBlock = 0; nCntBlock < sizeof g_aBlockInfo / sizeof(BlockInfo); nCntBlock++)
	{
		SetBlock(g_aBlockInfo[nCntBlock].pos, g_aBlockInfo[nCntBlock].fwidth, g_aBlockInfo[nCntBlock].fheight, g_aBlockInfo[nCntBlock].type);
	}

	//コインの初期位置(横位置,縦位置,透明度),なんか)
	for (nCntItem = 0; nCntItem < sizeof g_aItemInfo / sizeof(ItemInfo); nCntItem++)
	{
		SetItem(g_aItemInfo[nCntItem].pos, g_aItemInfo[nCntItem].fwidth, g_aItemInfo[nCntItem].fheigth, g_aItemInfo[nCntItem].type);
	}

	SetDokan(D3DXVECTOR3(680, 600, 0.0f), 100, 100, DokanType_Dokan);
}

//=============================================================================
// 終了処理(ポリゴン)
//=============================================================================
void UninitGame(void)
{
	//背景の終了処理
	Uninitbg();
	Uninitbg2();
	//ブロックの終了処理
	UninitBlock();
	UninitDokan();
	//プレイヤーの終了処理
	UninitPlayer();
	//アイテムの終了処理
	UninitItem();
	//爆発の終了処理
	UninitExplosion();
	//スコアの終了処理
	UninitScore();
	UninitScoreFrame();
	//時間の終了処理
	UninitTime();
	UninitTimeFrame();
	//ポーズの終了処理
	UninitPause();
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
		Updatebg();
		Updatebg2();
		//アイテムの更新処理
		UpdateItem();
		//爆発の更新処理
		UpdateExplosion();
		//ブロックの更新処理
		UpdateBlock();
		UpdateDokan();
		//プレイヤーの更新処理
		UpdatePlayer();
		//スコアの更新処理
		UpdateScore();
		UpdateScoreFrame();
		//時間の更新処理
		UpdateTime();
		UpdateTimeFrame();


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
	Drawbg();
	Drawbg2();
	//ブロックの描画処理
	DrawBlock();
	//アイテム描画処理
	DrawItem();
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
	DrawDokan();

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