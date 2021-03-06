//=============================================================================
//
// プレイヤー 処理 [palyer.h]
// Author : Ozaki
//
//=============================================================================
#ifndef _STARTER_H_
#define _STARTER_H_

#include "main.h"
#include "scene.h"
#include "sceneX.h"

#include<stdio.h>
#include<string.h>

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MODEL_UMA			"data\\MODEL\\uma.x"	//テクスチャのファイル名
#define MODEL_USI			"data\\MODEL\\arista.x"	//テクスチャのファイル名
#define MODEL_BODY			"data\\MODEL\\body.x"
#define MODEL_HEAD			"data\\MODEL\\01_head.x"
#define MODEL_RARM			"data\\MODEL\\arm_r.x"
#define MODEL_LARM			"data\\MODEL\\arm_l.x"

#define FIELD_MAX_SIZE			(FIELD_SIZE - 10)
//#define MAX_MODEL				(300)							//モデル配置の最大数
#define MAX_MODEL_TYPE			(5)								//モデル種類の最大数
#define MOVE_PLAYER				(0.005f)
#define MOVE_PLAYER1			(0.01f)
#define NUM_STAERTER_MODEL		(13)
#define MAX_ROT					(1.0f)
#define MAX_PARTS				(30)
#define MAX_MOTION				(30)

//*****************************************************************************
// クラス宣言
//*****************************************************************************
class CModel;
class CScene3D;
class CMeshOrbit;

class CStarter : public CScene
{
public:

	//================
	// キー要素
	//================
	typedef struct
	{
		float fPosX;
		float fPosY;
		float fPosZ;

		float fRotX;
		float fRotY;
		float fRotZ;
	}KEY;

	//================
	// キー情報
	//================
	typedef struct
	{
		int nFrame;
		KEY aKey[MAX_PARTS];
	}KEY_INFO;

	//================
	// モーション情報
	//================
	typedef struct
	{
		bool		bLoop;
		int			nNumKey;
		KEY_INFO	aKeyInfo[NUM_STAERTER_MODEL];
	}MOTION_INFO;

	typedef enum
	{
		STARTER_NONE = 0,		//初期状態
		STARTER_NORMAL,			//通常
		STARTER_MAX,			//最大数
	}STARTER;

	static HRESULT Load(void);	// 読み込み
	static void Unload(void);	// 開放

	CStarter(int nPriority = 4, OBJTYPE objtype = OBJTYPE_PLAYER);
	~CStarter();

	HRESULT Init(void);									// 初期化処理
	void	Uninit(void);								// 終了処理
	void	Update(void);								// 更新処理
	void	Draw(void);									// 描画処理
	static CStarter *Create(D3DXVECTOR3 pos);			// 生成処理
	D3DXVECTOR3 GetPlayerpos(D3DXVECTOR3 pos);			// 位置取得
	D3DXVECTOR3 Getpos(void);							// 位置取得
	D3DXVECTOR3 Getrot(void);							// 位置取得
	D3DXVECTOR3 Getmove(void);							// 位置取得


	static void	FileLoad(void);							// ファイル読み込み
	void UpdateMotion(void);							// モーションの更新関数

	static char	*ReadLine(FILE *pFile, char *pDest);	// 1行分(256文字分)の読み込み
	static char *GetLineTop(char *pSrc);				// 文字列の先頭を取得
	static int	PopString(char *pSrc, char *pDest);		// 文字列を抜き出す

	int							GetCntA(void);
	int							GetCntB(void);

	float						m_fDestAngle;			//プレイヤーの角度
	float						m_fDiffAngle;			//差分

private:

	//================================================================================
	// メンバ変数
	//================================================================================

	// D3DXVECTOR類
	static D3DXVECTOR3			m_pos;							// 位置
	static D3DXVECTOR3			m_rot;							// 向き
	D3DXVECTOR3					m_move;							// 動き
	D3DXVECTOR3					m_aPos[4];						// 総数
	D3DXVECTOR3					m_VecA;							// ベクトルA
	D3DXVECTOR3					m_VecB;							// ベクトルB
	D3DXVECTOR3					m_VecC;							// ベクトルC
	D3DXVECTOR3					m_vecAxis;						// 回転軸

																// バッファ類
	LPD3DXBUFFER				m_pBuffMatModel2;				// マテリアル情報へのポインタ

																// マトリックス類
	D3DXMATRIX					m_mtxWorld;						// ワールドマトリックス
	D3DXMATRIX					*m_Mtx;
	D3DXMATRIX					m_mtxRot;						// 回転マトリックス(保存用)

																// フロート類
	float						m_fValueRot;					// 回転角(量)

																// ブール類
	bool						m_blr;
	bool						m_bBrake;						// ブレーキ状態

																// char型類
	static char					m_aFileNameModel[MAX_PARTS][256];

	// int型類
	int							m_nCntA;
	int							m_nCntB;
	int							m_testCnt;

	// その他
	D3DXQUATERNION				m_quat;							// クォータニオン
	static CMeshOrbit			*m_mesh;
	static STARTER				m_State;

	//================================================================================
	// モーション関数
	//================================================================================

	D3DXVECTOR3					m_OffSetPos[MAX_PARTS];
	CScene						*m_pSceneTarget;				// 対象のオブジェクト(当たり判定)
	int							m_nKey;
	int							m_nCountMotion;					// モーションカウンター
	int							m_nMotionType;					// モーションのタイプ(int型)
	int							m_nCountFlame;					// フレーム数

	bool						m_bMotionEnd;

	// 静的メンバ変数
	static CModel				*m_apModel[MAX_PARTS];			// モデルへのポインタ
	static KEY					m_aKeyOffset[MAX_PARTS];		// パーツの最大数
	static KEY_INFO				*m_pKeyInfo[MAX_MOTION];		// キーの総数
	static MOTION_INFO			m_aMotionInfo[MAX_PARTS];		// モーション情報へのポインタ
	static LPD3DXMESH			m_pMeshModel[MAX_PARTS];		// メッシュ情報へのポインタ
	static DWORD				m_nNumMatModel[MAX_PARTS];		// マテリアル情報の数
	static LPD3DXBUFFER			m_pBuffMatModel[MAX_PARTS];		// マテリアル情報へのポインタ
	static LPDIRECT3DTEXTURE9	m_pTexture;						// テクスチャ
	static int					m_nNumParts;					// パーツ数
	static int					m_nNumModel;					// モデル数
	static int					m_aIndexParent[MAX_PARTS];		// パーツの最大数
};
#endif