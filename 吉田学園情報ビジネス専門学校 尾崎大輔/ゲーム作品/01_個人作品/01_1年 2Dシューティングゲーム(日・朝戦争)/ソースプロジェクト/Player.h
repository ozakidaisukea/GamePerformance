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

//列挙型
typedef enum
{
	PLAYERSTATE_APPEAR = 0,
	PLAYERSTATE_NORMAL ,
	PLAYERSTATE_DAMAGE,
	PLAYERSTATE_DEATH,
	PLAYERSTATE_MAX,
}PLAYERSTATE;

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	PLAYERSTATE state;		//敵の状態
	
	int nCounterState;		//状態管理カウンター
	int nLife;				//体力
	bool bDisp;				//使用してるかどうか
}Player;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
Player *GetPlayer(void);
void HitPlayer(int nDamage);

#endif // _PLAYER_H_
