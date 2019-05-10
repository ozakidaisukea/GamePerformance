//=============================================================================
//
// モデル処理 [Player2.h]
// Author : Ozaki
//
//=============================================================================
#ifndef _PLAYER2_H_
#define _PLAYER2_H_

#include "main.h"
#include "model.h"

//*****************************************************************************
// モデルの構造体
//*****************************************************************************
typedef enum
{
	PLAYER2_NORMAL = 0,
}PLAYER2;

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
}Model2;

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
	bool		bUse;				// 使用してるかどうか
	bool		bJunp;				// ジャンプしてるかどうか
	PLAYER2		state;
	Model2		aModel[2];
	MODEL		*pModel;

	D3DXVECTOR3 VtxMinModel, VtxMaxModel;	//モデルの最小値、最大値


}Player2;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitPlayer2(void);
void UninitPlayer2(void);
void UpdatePlayer2(void);
void DrawPlayer2(void);
void HitPlayer(int nCntPlayer,int nDamage);
bool CollisionPlayer(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 radius, MODEL **pPlayer2);
Player2 *GetPlayer2(void);
#endif
