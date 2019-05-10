//=============================================================================
//
// スコア処理 [scoreframe.h]
// Author : Ozaki
//
//=============================================================================
#ifndef _SCOREFRAME_H_
#define _SCOREFRAME_H_

#include "main.h"


typedef struct
{
	D3DXVECTOR3 pos;		//現在の位置
	D3DXVECTOR3 posold;		//前回の位置
	D3DXVECTOR3 move;		//移動量
	D3DXVECTOR3 col;		//色
	float fwidth;			//横幅
	float fheigth;			//縦幅
	int nCounterAnim;		//アニメーションカウンター
	int nPatternAnim;		//アニメーションをパターン化
	bool bUse;				//使用してるかどうか
}ScoreFrame;
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitScoreFrame(void);
void UninitScoreFrame(void);
void UpdateScoreFrame(void);
void DrawScoreFrame(void);

#endif
