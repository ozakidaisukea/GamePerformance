//=============================================================================
//
// ポリゴン処理 [Explosion.h]
// Author : Ozaki
//
//=============================================================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define		MAX_EXPLOSION	(1)

//*****************************************************************************
// 構造体
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;				// 位置
	D3DXVECTOR3 rot;				// 向き
	D3DXVECTOR3 movve;				// 動き
	D3DXMATRIX  mtxWorld;			// ワールドマトリックス
	int			nCounterAnim;		//アニメーションカウンター
	int			nPatternAnim;		//アニメーションパターン
	int			nLife;				// 体力
	bool		bUse;				// 使用してるかしてないか

}Explosion;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitExplosion(void);
void UninitExplosion(void);
void UpdateExplosion(void);
void DrawExplosion(void);
void SetExplosion(D3DXVECTOR3 posExplosion, D3DXVECTOR3 rotExplosion,D3DXCOLOR col);
Explosion *GetExplosion(void);
#endif
