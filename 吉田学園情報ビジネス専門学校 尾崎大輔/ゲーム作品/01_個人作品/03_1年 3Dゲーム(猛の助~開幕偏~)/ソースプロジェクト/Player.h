//=============================================================================
//
// モデル処理 [Player.h]
// Author : Ozaki
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
#include "model.h"

//*****************************************************************************
// モデルの構造体
//*****************************************************************************
typedef enum
{
	PLAYER_NORMAL = 0,
}PLAYER;

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
}Model1;

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
	PLAYER		state;
	Model1		aModel[2];
	D3DXVECTOR3 rotmove;
	MODEL		*pModel;
	D3DXVECTOR3 VtxMinModel, VtxMaxModel;	//モデルの最小値、最大値

}Player;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
Player *GetPlayer(void);
bool CollisionPlayer(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 radius, MODEL **pPlayer);
#endif
