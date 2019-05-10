//=============================================================================
//
// 敵処理 [boss.h]
// Author : Ozaki
//
//=============================================================================
#ifndef _BOSS_H_
#define _BOSS_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MAX_BOSS	(256)	// 敵の最大数

//*****************************************************************************
// 構造体定義
//*****************************************************************************

//列挙型
typedef enum
{
	BOSSSTATE_NORMAL = 0,
	BOSSSTATE_DAMAGE,
	BOSSSTATE_MAX,
}BOSSSTATE;

typedef struct
{
	D3DXVECTOR3 pos;		//位置
	int nType;				//種類
	BOSSSTATE state;		//敵の状態
	int nCounterState;		//状態管理カウンター
	int nLife;				//体力
	bool bUse;				//使用してるかどうか
	int nCounterAnim;		//アニメーションカウンター
	int nPatternAnim;		//アニメーションパターン
}Boss;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitBoss(void);
void UninitBoss(void);
void UpdateBoss(void);
void DrawBoss(void);
void SetBoss(D3DXVECTOR3 pos, int nType);
void HitBoss(int nCntBoss, int nDamage);
Boss *GetBoss(void);

#endif

