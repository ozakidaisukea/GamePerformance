//=============================================================================
//
// 敵処理 [enemy.h]
// Author : Ozaki
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MAX_ENEMY	(256)	// 敵の最大数

//*****************************************************************************
// 構造体定義
//*****************************************************************************

//列挙型
typedef enum
{
	ENEMYSTATE_NORMAL = 0,
	ENEMYSTATE_DAMAGE,
	ENEMYSTATE_MAX,
}ENEMYSTATE;

typedef struct
{
	D3DXVECTOR3 pos;		//位置
	int nType;				//種類
	ENEMYSTATE state;		//敵の状態
	int nCounterState;		//状態管理カウンター
	int nLife;				//体力
	bool bUse;				//使用してるかどうか
	int nCounterAnim;		//アニメーションカウンター
	int nPatternAnim;		//アニメーションパターン
}Enemy;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void SetEnemy(D3DXVECTOR3 pos, int nType);
void HitEnemy(int nCntEnemy, int nDamage);
Enemy *GetEnemy(void);

#endif
