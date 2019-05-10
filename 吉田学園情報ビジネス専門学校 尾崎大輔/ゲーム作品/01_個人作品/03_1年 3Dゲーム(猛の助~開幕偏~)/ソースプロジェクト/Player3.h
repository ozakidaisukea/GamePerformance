//=============================================================================
//
// モデル処理 [Player2.h]
// Author : Ozaki
//
//=============================================================================
#ifndef _SAKU_H_
#define _SAKU_H_

#include "main.h"
#include "model.h"

//*****************************************************************************
// モデルの構造体
//*****************************************************************************
typedef enum
{
	PLAYER3_NORMAL = 0,
}PLAYER3;

//*****************************************************************************
// 構造体
//*****************************************************************************
typedef struct
{
	LPD3DXMESH		pMesh;
	LPD3DXBUFFER	pBuffMat;
	DWORD			nNumMat;
	D3DXMATRIX		mtxWorld;
	D3DXVECTOR3		rot;
	D3DXVECTOR3 pos;				// 現在の位置
	int				nIdxModelParent;			// 親モデルのインデックス
}Model3;

typedef struct
{
	D3DXVECTOR3 pos;				// 現在の位置
	D3DXVECTOR3 posold;
	D3DXVECTOR3 move;				// 移動量
	D3DXVECTOR3 posVDest;			// 視点
	D3DXVECTOR3 posRDest;			// 注意点
	D3DXVECTOR3 posUDest;			// 上方向ベクト
	D3DXVECTOR3 rot;				// 向き
	D3DXMATRIX	mtxWorld;
	float       fwidth;				// 横
	float       fheigth;			// 縦
	int			nCounterState;		// 状態管理カウンター
	int			nLife;				// 寿命
	float		flength;			// 距離 
	bool		bDisp;				// 使用してるかどうか
	bool		bJunp;				// ジャンプしてるかどうか
	PLAYER3		state;
	Model3		aModel[2];
	MODEL		*pModel;

}Player3;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitPlayer3(void);
void UninitPlayer3(void);
void UpdatePlayer3(void);
void DrawPlayer3(void);
Player3 *GetPlayer3(void);

#endif
