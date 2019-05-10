//=============================================================================
//
// カメラ処理 [camera.h]
// Author : Ozaki 
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

//*****************************************************************************
// カメラの構造体
//*****************************************************************************
typedef enum
{
	CAMERA_NORMAL = 0,
}CAMERA;

typedef struct
{
	D3DXVECTOR3 posV;				// 視点
	D3DXVECTOR3 posR;				// 注視点
	D3DXVECTOR3 posU;				// 上方向ベクトル

	D3DXVECTOR3 posVDest;				// 視点
	D3DXVECTOR3 posRDest;				// 注視点
	D3DXVECTOR3 posUDest;				// 上方向ベクトル
	D3DXVECTOR3 rot;				// 向き
	D3DXVECTOR3 rotDest;			// 目的の向き
	float		rotDiff;			// 差分
	D3DXMATRIX  mtxProjection;		// プロジェクターマトリックス
	D3DXMATRIX	mtxView;			// ビューマトリックス
	float		flength;			// 距離 
	float		angle;				// 周り
	int			nCounterState;		//状態管理カウンター
	int			DirectionMove0;		//右
	bool		bDisp;				//使用してるかどうか
	CAMERA		state;
	int nCounterAngle;			//カメラアングルが変わるカウンター

}Camera;


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);
void SetCamera(void);
Camera*GetCamera(void);

#endif
