//=============================================================================
//
// ポリゴン処理 [billboard.h]
// Author : Ozaki
//
//=============================================================================
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define		MAX_BILLBOARD	(20)

//*****************************************************************************
// 構造体
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;							// 位置
	D3DXVECTOR3 rot;							// 向き
	D3DXVECTOR3 movve;							// 動き
	D3DXMATRIX mtxWorld;						// ワールドマトリックス
	bool		bUse;							// 使用してるかしてないか

}Billboard;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitBillboard(void);
void UninitBillboard(void);
void UpdateBillboard(void);
void DrawBillboard(void);
void SetBillboard(D3DXVECTOR3 posBillboard, D3DXVECTOR3 rotBillboard);
#endif
