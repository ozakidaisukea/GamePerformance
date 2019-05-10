//=============================================================================
//
// 弾処理 [explosion.h]
// Author : ozaki
//
//=============================================================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include "main.h"

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;		//現在の位置
	D3DXVECTOR3 posold;		//前回の位置
	D3DXVECTOR3 move;		//移動量
	D3DXCOLOR col;			//色					
	float        fwidth;	//横
	float       fheigth;	//縦
	int nCounterAnim;
	int nPatternAnim;
	bool bUse;				//使用しているか
	int nLife;				//寿命
}Explosion;	

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitExplosion(void);
void UninitExplosion(void);
void UpdateExplosion(void);
void DrawExplosion(void);
void SetExplosion(D3DXVECTOR3 pos, D3DXCOLOR col, int nLife);
Explosion *GetExplosion(void);
#endif
