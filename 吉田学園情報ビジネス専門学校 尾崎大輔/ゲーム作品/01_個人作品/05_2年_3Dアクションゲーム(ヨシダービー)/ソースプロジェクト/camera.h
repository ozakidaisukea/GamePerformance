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
// マクロ定義
//*****************************************************************************
#define MOVE			(30.0f)
#define MAX_X			(250)
#define	CAMERA_MOVE		(2.0f)
#define	MAX_CAMERA		(2)
//*****************************************************************************
// クラス宣言
//*****************************************************************************
class COwner;
class CCamera
{
public:

	//*****************************************************************************
	// カメラの構造体
	//*****************************************************************************
	typedef enum
	{
		CAMERA_NORMAL = 0,
		CAMERA_PLAYER,
	}CAMERA;

	typedef enum
	{
		MODE_TITLE = 0,		// タイトル
		MODE_TUTORIAL,		// チュートリアル
		MODE_GAME,			// ゲーム
		MODE_RESULT,		// リザルト
		MODE_MAX
	}MODE;

	typedef struct
	{
		D3DXVECTOR3 posV;				// 視点
		D3DXVECTOR3 posR;				// 注視点
		D3DXVECTOR3 posU;				// 上方向ベクトル

		D3DXVECTOR3 posVDest;			// 視点
		D3DXVECTOR3 posRDest;			// 注視点
		D3DXVECTOR3 posUDest;			// 上方向ベクトル
		D3DXVECTOR3 rot;				// 向き
		D3DXVECTOR3 rotDest;			// 目的の向き
		float		rotDiff;			// 差分
		D3DXMATRIX  mtxProjection;		// プロジェクターマトリックス
		D3DXMATRIX	mtxView;			// ビューマトリックス
		float		flength;			// 距離
		float		angle;				// 周り
		int			nCounterState;		// 状態管理カウンター
		int			DirectionMove0;		// 右
		bool		bDisp;				// 使用してるかどうか
		CAMERA		state;				// カメラのステート
		int nCounterAngle;				// カメラアングルが変わるカウンター

	}Camera;

	CCamera();
	~CCamera();

	HRESULT Init(void);
	void	Uninit(void);
	void	Update(void);
	void	SetCamera(void);
	Camera  GetCamera(void);
	MODE	GetMode(void);
	void	SetMode(MODE mode);
	D3DXVECTOR3 GetRot(void);

private:

	Camera	m_camera;						// カメラの情報
	MODE	m_mode;
	D3DXVECTOR3	m_rot;
	float fLength;
	int nCounterAngle;			//カメラアングルが変わるカウンター
};
#endif
