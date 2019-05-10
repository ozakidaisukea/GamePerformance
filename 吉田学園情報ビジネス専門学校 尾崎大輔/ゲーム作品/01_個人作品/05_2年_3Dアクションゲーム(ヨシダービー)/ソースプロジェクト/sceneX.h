//=============================================================================
//
// モデル処理 [model.h]
// Author :Ozaki Ozaki
//
//=============================================================================
#ifndef _SCENEX_H_
#define _SCENEX_H_

#include "main.h"
#include "scene.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MODEL_EARTH			"data\\MODEL\\earth000.x"		// モデルのファイル名
#define FIELD_MAX_SIZE		(FIELD_SIZE - 10)
#define MAX_MODEL			(300)							// モデル配置の最大数
#define MAX_MODEL_TYPE		(5)								// モデル種類の最大数

//*****************************************************************************
// クラス宣言
//*****************************************************************************
class CSceneX : public CScene
{
public:
	CSceneX(int nPriority, OBJTYPE objtype = CScene::OBJTYPE_X);
	~CSceneX();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	bool CollisionModel(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 radius, D3DXVECTOR3 VtxMax, D3DXVECTOR3 VtxMin);
	void SetModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType);
	static CSceneX *Create(D3DXVECTOR3 pos);
	void BindTexture(LPDIRECT3DTEXTURE9 texture);

	D3DXVECTOR3 GetPosition(void);

	D3DXVECTOR3 GetMove(void);

	void SetMove(D3DXVECTOR3 move);

	void SetPosition(D3DXVECTOR3 pos);

	void SetRot(D3DXVECTOR3 rot);

private:

	static LPDIRECT3DTEXTURE9				m_pTexture;						// テクスチャ
	LPDIRECT3DVERTEXBUFFER9					m_pVtxBuff;						// 頂点バッファのポインタ
	LPD3DXMESH								m_pMeshModel;					//メッシュ情報へのポインタ
	DWORD									m_nNumMatModel;					//マテリアル情報の数
	LPD3DXBUFFER							m_pBuffMatModel;				//マテリアル情報へのポインタ
	D3DXMATERIAL							*m_pMat;
	DWORD									m_nNumMat = 0;					//マテリアル情報の数
	D3DXVECTOR3								m_pos;							//位置
	D3DXVECTOR3								m_rot;							//向き
	D3DXMATRIX								m_mtxWorld;						//ワールドマトリックス
	D3DXVECTOR3								m_VtxMinModel, m_VtxMaxModel;	//モデルの最小値、最大値
	D3DXVECTOR3								m_move;

	int						takumi1;
};
#endif