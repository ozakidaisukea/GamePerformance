//=============================================================================
//
// ジョッキー 処理 [jockey.h]
// Author : Ozaki
//
//=============================================================================
#ifndef _JOCKEY_H_
#define _JOCKEY_H_

#include "main.h"
#include "scene.h"
#include "sceneX.h"

#include<stdio.h>
#include<string.h>

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define FIELD_MAX_SIZE			(FIELD_SIZE - 10)
#define MAX_MODEL_TYPE			(5)								//モデル種類の最大数
#define MOVE_PLAYER				(0.005f)
#define MOVE_PLAYER1			(0.01f)
#define NUM_PLAYER_MODEL		(11)
#define MAX_ROT					(1.0f)
#define MAX_PARTS				(30)
#define MAX_MOTION				(30)

//*****************************************************************************
// クラス宣言
//*****************************************************************************
class CModel;
class CScene3D;
class CMeshOrbit;

class CJockey : public CScene
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
		KEY_INFO	aKeyInfo[NUM_PLAYER_MODEL];
	}MOTION_INFO;

	typedef enum
	{
		JOCKEYSTATE_NONE = 0,		//初期状態
		JOCKEYSTATE_NORMAL,			//通常
		JOCKEYSTATE_MAX,			//最大数
	}JOCKEYSTATE;

	typedef enum
	{
		JOCKEYTYPE_NONE = 0,		//初期状態
		JOCKEYTYPE_TITLE,			//通常
		JOCKEYTYPE_GAME,			//通常
		JOCKEYTYPE_RESULT,
		JOCKEYTYOE_MAX,				//最大数
	}JOCKEYTYPE;

	static HRESULT Load(void);	// 読み込み
	static void Unload(void);	// 開放

	CJockey(int nPriority = 1, OBJTYPE objtype = OBJTYPE_PLAYER);
	~CJockey();

	HRESULT Init(void);									// 初期化処理
	void	Uninit(void);								// 終了処理
	void	Update(void);								// 更新処理
	void	Draw(void);									// 描画処理
	static CJockey *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, JOCKEYTYPE type);			// 生成処理
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
	static JOCKEYSTATE			m_State;
	static JOCKEYTYPE			m_nType;

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