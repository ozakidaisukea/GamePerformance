//=============================================================================
//
// サウンド処理 [sound.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*************************************
// サウンドファイル
//*************************************
typedef enum
{
	SOUND_LABEL_TITLE = 0,		// BGM0
	SOUND_LABEL_TUTORIAL,		// BGM1
	SOUND_LABEL_GAME,			// BGM2
	SOUND_LABEL_CLEAR,			// BGM3
	SOUND_LABEL_GAMEOVER,		// BGM4
	SOUND_LABEL_RUNKING,		// BGM5
	SOUND_LABEL_SE_SHOT,		// 弾発射音
	//SOUND_LABEL_SE_HIT000,		// ヒット音0
	//SOUND_LABEL_SE_HIT001,		// ヒット音1
	SOUND_LABEL_SE_EXPLOSION,	// 爆発音
	SOUND_LABEL_SE_USHI,		// 決定音1
	SOUND_LABEL_SE_ENTER,		// 決定音2
	SOUND_LABEL_SE_SAKEBI,		// 博士叫び声
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
