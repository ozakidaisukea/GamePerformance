//=============================================================================
//
// 背景の処理 [Game.cpp]
// Author : Ozaki
//
//=============================================================================
#pragma once
#ifndef _Game_H_
#define _Game_H_

//*****************************************************************************
//プロトタイプ宣言
//*****************************************************************************
typedef enum
{
	GAMESTATE_NONE = 0,			//何もしていない状態
	GAMESTATE_NORMAL,			//通常状態
	GAMESTATE_END,				//終了状態
	GAMESTATE_BOSS,
	GAMESTATE_GAMEOVER,
	GAMESTATE_MAX,
}GAMESTATE;
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);
void SetGameState(GAMESTATE state);
GAMESTATE GetGameState(void);

#endif // _Game_H_
