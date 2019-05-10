//=============================================================================
//
// 弾処理 [block.h]
// Author : ozaki
//
//=============================================================================
#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "main.h"
//*****************************************************************************
// ブロックの種類
//*****************************************************************************
typedef enum
{
	BlockType_Normal,			// ノーマル
	BlockType_Dokan,			// 土管
	BlockType_Beltconveyor,		// ベルトコンベアー
	BlockType_Ice,				// 氷床
	BlockType_Question1,		// ？ブロック1
	BlockType_Question2,		// ？ブロック2
	BlockType_Move,				// 移動床
	BlockType_Junp,				// ジャンプ台
	BlockType_Isi,				// 石ブロック

}BLOCK_TYPE;

typedef struct
{
	D3DXVECTOR3 pos;			// 位置
	D3DXVECTOR3 move;			// 移動
	float    fwidth;			// 幅
	float	fheight;			// 高さ
	bool       bUse;			// 使用してるかどうか
	BLOCK_TYPE type;			// ブロックのタイプ
	int    nCntItem;			// 
	int       nType;
}Block;

typedef struct
{
	D3DXVECTOR3 pos;			// 位置
	float    fwidth;			// 幅
	float	fheight;			// 高さ
	BLOCK_TYPE type;			// ブロックのタイプ
}BlockInfo;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitBlock(void);
void UninitBlock(void);
void UpdateBlock(void);
void DrawBlock(void);
Block *GetBlock(void);
void SetBlock(D3DXVECTOR3 pos,float fwidth,float fheigth, BLOCK_TYPE type);
bool CollisionBlock(D3DXVECTOR3 *pPos, D3DXVECTOR3*pPosOld,D3DXVECTOR3 *pMove, float fwigth,float fheigth);

#endif