//=============================================================================
//
// DirectX雛型処理 [player.h]
// Author : Ozaki
//
//=============================================================================
#pragma once
#ifndef _PLAYER_H_
#define _PLAYER_H_

//*****************************************************************************
//プレイヤーの構造体
//*****************************************************************************
typedef enum
{
	PLAYER_NORMAL = 0,
	PLAYER_DETHSTATE,	// プレイヤーが死ぬ
	PLAYER_BIGSTATE,		// 
}PLAYER;

typedef struct
{
	D3DXVECTOR3 pos;		//現在の位置
	D3DXVECTOR3 posold;		//前回の位置
	D3DXVECTOR3 move;		//移動量
	float        fwidth;	//横
	float       fheigth;	//縦
	int nCounterAnim;		
	int nPatternAnim;
	int nCounterState;		//状態管理カウンター
	int DirectionMove0;		//右
	int nLife;				//体力
	bool bDisp;				//使用してるかどうか
	bool bJunp;				//ジャンプしてるかどうか
	//Block *spBlock;			//対象のブロックへのポインタ
	PLAYER state;
}Player;



//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
Player *GetPlayer(void);

#endif // _PLAYER_H_
