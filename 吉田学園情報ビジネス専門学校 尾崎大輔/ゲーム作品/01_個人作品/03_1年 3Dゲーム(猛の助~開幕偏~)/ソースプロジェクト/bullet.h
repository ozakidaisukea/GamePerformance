//=============================================================================
//
// ポリゴン処理 [bullet.h]
// Author : Ozaki
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"
#include "model.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define		MAX_BULLET	(256)

//*****************************************************************************
// 構造体
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;							// 位置
	D3DXVECTOR3 posold;							// 位置

	D3DXVECTOR3 move;							// 動き
	D3DXMATRIX mtxWorld;						// ワールドマトリックス
	int			nLife;							// 寿命
	int			nIdxShadow;						// 影
	bool		bUse;							// 使用してるかしてないか
	MODEL		*pModel;

}BULLET;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 posbullet, D3DXVECTOR3 rotbullet,D3DXVECTOR3 movebullet);
#endif
