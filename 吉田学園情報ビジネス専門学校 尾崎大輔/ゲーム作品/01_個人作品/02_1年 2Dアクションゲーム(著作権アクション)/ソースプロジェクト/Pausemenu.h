#pragma once
//=============================================================================
//
// 入力処理 [paseaselct.h]
// Author :  Ozaki
//
//=============================================================================
#ifndef _PAUSESELECT_H_
#define _PAUSESELECT_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MAX_Pausecont	(10)	// 敵の最大数

//*****************************************************************************
// 構造体定義
//*****************************************************************************

//列挙型
typedef enum
{
	SELECTMODE_NONE = 0,
	SELECTMODE_CONTINE,
	SELECTMODE_RETRY,
	SELECTMODE_QUIT,
	SELECTMODE_MAX,
}SELECTMODE;

typedef enum
{
	SELECTTYPE_NONE = 0,
	SELECTTYPE_SELECT,
	SELECTTYPE_MAX
}SELECT;

typedef struct
{
	SELECT		select;		//セレクト
	D3DXVECTOR3 pos;		//位置
	D3DXCOLOR   col;		//カラー

}PAUSESELECT;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitPauseSelect(void);
void UninitPauseSelect(void);
void UpdatePauseSelect(void);
void DrawPauseSelect(void);
void SetPauseSelect(D3DXVECTOR3 pos, D3DXCOLOR col);
SELECTMODE *GetPauseMode(void);

#endif


