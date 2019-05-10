//=============================================================================
//
// 弾処理 [item.h]
// Author : ozaki
//
//=============================================================================
#ifndef _ITEM_H_
#define _ITEM_H_

#include "main.h"

//*****************************************************************************
//アイテムの構造体
//*****************************************************************************
typedef enum
{
	ITEMSTATE_COIN = 0,		// コイン
	ITEMSTATE_MUSHROOMS,	// キノコ
	ITEMSTATE_BIGMUSHROOMS,	// ビッグキノコ
	ITEMSTATE_MAX,
}ITEMTYPE;

typedef struct
{
	D3DXVECTOR3 pos;		//現在の位置
	D3DXVECTOR3 posold;		//前回の位置
	D3DXVECTOR3 move;		//移動量
	D3DXVECTOR3 col;		//色
	float fwidth;			//横幅
	float fheigth;			//縦幅
	int       nType;
	int nCounterAnim;		//アニメーションカウンター
	int nPatternAnim;		//アニメーションをパターン化
	ITEMTYPE type;			//種類
	bool bUse;				//使用してるかどうか
}Item;

typedef struct
{
	D3DXVECTOR3 pos;		// 現在の位置
	float fwidth;			// 横幅
	float fheigth;			// 縦幅
	ITEMTYPE type;			// 種類

}ItemInfo;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitItem(void);
void UninitItem(void);
void UpdateItem(void);
void DrawItem(void);
void SetItem(D3DXVECTOR3 pos, float fwidth, float fheigth, ITEMTYPE type);
Item *GetItem(void);
void CollisionItem(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pMove, float fwidth,float fheigth);
#endif
