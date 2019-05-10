//=============================================================================
//
// サウンド処理 [sound.h]
// Author : Ozaki
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
	SOUND_LABEL_BGM000 = 0,		// BGM0
	SOUND_LABEL_BGM001,			// BGM1
	SOUND_LABEL_BGM002,			// BGM2
	SOUND_LABEL_BGM003,			// BGM3
	SOUND_LABEL_BGM004,			// BGM4
	SOUND_LABEL_BGM005,			// BGM5  [マリオ]
	SOUND_LABEL_BGM006,			// BGM6  [マリオ編集]
	SOUND_LABEL_BGM007,			// BGM7  [マリオランキング]
	SOUND_LABEL_BGM008,			// BGM8  [マリオチュートリアル]
	SOUND_LABEL_BGM009,			// BGM9  [マリオタイトル]
	SOUND_LABEL_BGM0010,		// BGM10  [SIM_GUNSHOT]
	SOUND_LABEL_BGM0011,		// BGM11  [SIM_KILLINGME]
	SOUND_LABEL_BGM0012,		// BGM12  [SIM_BLHA]
	SOUND_LABEL_BGM0013,		// BGM13  [爪爪爪]
	SOUND_LABEL_BGM0014,		// BGM14  [やる気のないダースベイダー]

	SOUND_LABEL_SE_MARIO_CLEAR,	// リザルト  [マリオクリア]
	SOUND_LABEL_SE_MARIO_DETH,	// 死亡音 [マリオ]
	SOUND_LABEL_SE_HUMAN1,		// 人間音1 [ハッ]
	SOUND_LABEL_SE_HUMAN2,		// 人間音2 [なんでやねん]
	SOUND_LABEL_SE_HUMAN3,		// 人間音3 [笑い]
	SOUND_LABEL_SE_SHOT,		// 弾発射音
	SOUND_LABRL_SE_COIN,		// コイン
	SOUND_LABRL_SE_ambulance,	// 救急
	SOUND_LABRL_SE_junp,		// ジャンプ
	SOUND_LABRL_SE_serect,		// 選択
	SOUND_LABRL_SE_nomu,		// 飲む
	SOUND_LABRL_SE_coughing,	// なんか
	SOUND_LABRL_SE_running,		// 走り
	SOUND_LABRL_SE_heart,		// 心拍音
	SOUND_LABEL_SE_HIT000,		// ヒット音0
	SOUND_LABEL_SE_HIT001,		// ヒット音1
	SOUND_LABEL_SE_EXPLOSION,	// 爆発音
	SOUND_LABEL_SE_DECIDE,		// 決定音
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

