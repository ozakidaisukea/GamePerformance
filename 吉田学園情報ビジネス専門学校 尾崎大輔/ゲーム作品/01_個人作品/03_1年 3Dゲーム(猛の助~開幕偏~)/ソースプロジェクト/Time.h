//=============================================================================
//
// スコア処理 [Time.h]
// Author : Ozaki
//
//=============================================================================
#ifndef _TIME_H_
#define _TIME_H_

#include "main.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitTime(void);
void UninitTime(void);
void UpdateTime(void);
void DrawTime(void);
bool *GetTime(void);
void AddTime(int nValue);
void StopTimer(void);

#endif

