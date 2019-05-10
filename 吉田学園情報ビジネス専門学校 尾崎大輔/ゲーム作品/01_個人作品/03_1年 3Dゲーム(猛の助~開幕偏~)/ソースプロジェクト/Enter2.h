//=============================================================================
//
// エンター処理 [enter2.h]
// Author : Ozaki
//
//=============================================================================
#ifndef _ENTER2_H_
#define _ENTER2_H_

#include "main.h"

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;	// 位置
	D3DXCOLOR col;	// カラー
} ENTER2;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitEnter2(void);
void UninitEnter2(void);
void UpdateEnter2(void);
void DrawEnter2(void);

#endif
