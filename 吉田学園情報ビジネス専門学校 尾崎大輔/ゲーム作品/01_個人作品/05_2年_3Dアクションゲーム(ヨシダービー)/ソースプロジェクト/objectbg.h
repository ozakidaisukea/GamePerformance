//=============================================================================
//
// オブジェクトBG処理 [objectBG.h]
// Author : Ozaki
//
//=============================================================================
#ifndef _OBJECTBG_H_
#define _OBJECTBG_H_

#include "main.h"
#include "scene.h"

#include<stdio.h>
#include<string.h>

//*********************************************************************
// マクロ定義
//*********************************************************************
#define MAX_MATTEX				(20)
#define MAX_PARTS				(30)
#define NUM_OBJ_MODEL			(11)
#define MAX_OBJMOTION			(10)
//*********************************************************************
// 構造体
//*********************************************************************

//*********************************************************************
//プレイヤークラスの定義
//*********************************************************************
class CModel;

class CObjectBG : public CScene //派生クラス
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
		KEY_INFO	aKeyInfo[NUM_OBJ_MODEL];
	}MOTION_INFO;

	typedef enum
	{
		MODELTYPE_BILL000 = 0,	// ビル 0 小
		MODELTYPE_BILL001,		// ビル 1 小
		MODELTYPE_BILL002,		// ビル 2 小
		MODELTYPE_BILL003,		// ビル 3 小
		MODELTYPE_GOAL,			// ゴール
		MODELTYPE_GAGE,			// ゲージ
		MODELTYPE_MAX,			// 最大数
	}MODELTYPE;

	CObjectBG();
	~CObjectBG();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Setpos(D3DXVECTOR3 pos);
	static CObjectBG *Create(D3DXVECTOR3 pos,D3DXVECTOR3 rot, MODELTYPE type);
	static HRESULT Load(void);
	static void UnLoad(void);
	D3DXVECTOR3 GetPos(void);

	//void	FileLoad(void);							// ファイル読み込み
	void UpdateMotion(void);							// モーションの更新関数

	static char	*ReadLine(FILE *pFile, char *pDest);	// 1行分(256文字分)の読み込み
	static char *GetLineTop(char *pSrc);				// 文字列の先頭を取得
	static int	PopString(char *pSrc, char *pDest);		// 文字列を抜き出す

	//bool CollisionObject(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove);
	CModel								*m_pModel;

private:

	//メンバ変数
	D3DXVECTOR3							m_pos;						//位置
	D3DXVECTOR3							m_posold;					//前回の位置
	D3DXVECTOR3							m_move;						//移動量
	D3DXVECTOR3							m_rot;						//向き
	D3DXMATRIX							m_mtxWorld;					//ワールドマトリックス
	MODELTYPE							m_Type;						//タイプ


	float								m_fDestAngle;				//角度
	float								m_fDiffAngle;				//差分

	static LPD3DXMESH					m_pMesh[MODELTYPE_MAX];		//メッシュ情報へのポインタ
	static LPD3DXBUFFER					m_pBuffMat[MODELTYPE_MAX];	//マテリアル情報へのポインタ
	static LPDIRECT3DTEXTURE9			m_pObjTexture[MODELTYPE_MAX];	//テクスチャへのポインタ
	static DWORD						m_nNumMat[MODELTYPE_MAX];	//マテリアル情報の数

	int									m_nCollision;				// 当たり判定のONOFF

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

	// char型類
	static char					m_aFileNameModel[MAX_PARTS][256];

	// 静的メンバ変数
	static CModel				*m_apModel[MAX_PARTS];			// モデルへのポインタ
	static KEY					m_aKeyOffset[MAX_PARTS];		// パーツの最大数
	static KEY_INFO				*m_pKeyInfo[MAX_OBJMOTION];		// キーの総数
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