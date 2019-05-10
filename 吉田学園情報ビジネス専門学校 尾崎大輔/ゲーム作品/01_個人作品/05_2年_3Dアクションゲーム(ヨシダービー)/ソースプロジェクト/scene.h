//=============================================================================
//
// シーン処理 [scene.h]
// Author : Ozaki
//
//=============================================================================
#ifndef _SCENE_H_
#define _SCENE_H_

#include "main.h"

//===================================================================
// マクロ定義
//===================================================================
#define MAX_POLYGON		(9)		// ポリゴン数
#define MAX_PRIORITY1	(9)		// 描画の優先順位

//*****************************************************************************
// クラス宣言
//*****************************************************************************
class CScene
{
public:

	typedef enum
	{
		OBJTYPE_NONE = 0,		// 何もない
		OBJTYPE_2D,				// 2D
		OBJTYPE_3D,				// 3D
		OBJTYPE_X,				// X
		OBJTYPE_LOGO,			// ロゴ
		OBJTYPE_MODEL,			// モデル
		OBJTYPE_GIMMICK,		// ギミック
		OBJTYPE_MESHFIELD,		// メッシュフィールド
		OBJTYPE_GAUGE,			// ゲージ
		OBJTYPE_WALL,
		OBJTYPE_MESHORBIT,		// メッシュオービット
		OBJTYPE_BILLBOARD,		// ビルボード
		OBJTYPE_PLAYER,			// プレイヤー
		OBJTYPE_ENEMY,			// 敵
		OBJTYPE_BULLET,			// 弾
		OBJTYPE_PRESSENTOR,		// プレスエンター
		OBJTYPE_BGMODEL,		// オブジェクトモデル
		OBJTYPE_PAUSE,
		OBJTYPE_MAX				// 最大数
	}OBJTYPE;

	CScene(int nPriority = 3,OBJTYPE objtype = OBJTYPE_NONE);
	virtual ~CScene();

	// 純粋仮想関数
	virtual HRESULT	Init(void) = 0;
	virtual void	Uninit(void) = 0;
	virtual void	Update(void) = 0;
	virtual void	Draw(void) = 0;

	static void ReleaseAll(void);
	static void UpdateAll(void);
	static void DrawAll(void);
		   void	UninitAll(void);
		   void SetObjtType(OBJTYPE objttpe);

		   OBJTYPE GetObjtType(void);
		   void SetObjType(OBJTYPE ObjType);			//タイプを設定
		   CScene::OBJTYPE GetObjType(void);			//タイプを取得

		   // X
		   D3DXVECTOR3 GetPosition(void);
		   void SetPosition(D3DXVECTOR3 pos);
		   D3DXVECTOR3 GetMove(void);
		   void SetMove(D3DXVECTOR3 move);
		   void SetRot(D3DXVECTOR3 rot);
protected:

	void Release(void);

private:

	static	CScene * m_pTop[MAX_PRIORITY1];					// 先頭のオブジェクトへのポインタ
	static	CScene * m_pCur[MAX_PRIORITY1];					// 現在(最後尾)のオブジェクトへのポインタ
	CScene		   * m_pPrev;								// 前のオブジェクトへのポインタ
	CScene		   * m_pNext;								// 次のオブジェクトへのポインタ


	static int		m_nNumALL;								// ポリゴンの総数
	int				m_nID;									// 自分自身の番号
	int				m_nPriority;							// 優先順位の番号
	static int		m_nNumPriority[MAX_PRIORITY1];
	OBJTYPE			m_objtype;								// オブジェクトタイプ
	bool			m_bDeath;								// 死亡フラグ
	bool			m_pDeath;								// 死亡フラグ

	// X
	D3DXVECTOR3		m_move;									// 動き
	D3DXVECTOR3		m_pos;									// 位置

	D3DXVECTOR3		m_rot;									// 向き
};
#endif