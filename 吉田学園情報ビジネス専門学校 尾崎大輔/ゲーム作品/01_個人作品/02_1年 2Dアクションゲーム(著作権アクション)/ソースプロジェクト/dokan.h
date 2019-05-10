//=============================================================================
//
// 弾処理 [dokan.h]
// Author : ozaki
//
//=============================================================================
#ifndef _DOKAN_H_
#define _DOKAN_H_

#include "main.h"
//*****************************************************************************
// ブロックの種類
//*****************************************************************************
typedef enum
{
	DokanType_Dokan,			// 土管

}Dokan_TYPE;

typedef struct
{
	D3DXVECTOR3 pos;			// 位置
	D3DXVECTOR3 move;			// 移動
	float    fwidth;			// 幅
	float	fheight;			// 高さ
	bool       bUse;			// 使用してるかどうか
	Dokan_TYPE type;			// ブロックのタイプ
	int    nCntItem;			// 
	int       nType;
}Dokan;

typedef struct
{
	D3DXVECTOR3 pos;			// 位置
	float    fwidth;			// 幅
	float	fheight;			// 高さ
	Dokan_TYPE type;			// ブロックのタイプ
}DokanInfo;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitDokan(void);
void UninitDokan(void);
void UpdateDokan(void);
void DrawDokan(void);
void SetDokan(D3DXVECTOR3 pos, float fwidth, float fheigth, Dokan_TYPE type);
bool CollisionDokan(D3DXVECTOR3 *pPos, D3DXVECTOR3*pPosOld, D3DXVECTOR3 *pMove, float fwigth, float fheigth);

#endif