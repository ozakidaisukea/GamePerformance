//=============================================================================
//
// モデル処理 [model.h]
// Author :Ozaki Ozaki
//
//=============================================================================
#ifndef _MODEL_H_
#define _MODEL_H_

#include "main.h"
#include "scene.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************

#define FIELD_MAX_SIZE		(FIELD_SIZE - 10)
#define MAX_MODEL			(300)							//モデル配置の最大数
#define MAX_MODEL_TYPE		(5)								//モデル種類の最大数

//*****************************************************************************
// クラス宣言
//*****************************************************************************
class CModel
{
public:

	CModel();
	~CModel();

	static HRESULT Load(void);	// 読み込み
	static void Unload(void);	// 開放

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType);
	static CModel *Create(D3DXVECTOR3 pos,D3DXVECTOR3 rot);
	void BindTexture(LPDIRECT3DTEXTURE9 texture);
	void BindModel(LPD3DXBUFFER	BuffMatModel, DWORD	NumMatModel, LPD3DXMESH	MeshModel);

	D3DXVECTOR3 GetPosition(void);
	D3DXVECTOR3 GetMove(void);
	//D3DXMATRIX GetMatrix(void);

	void SetMove(D3DXVECTOR3 move);
	void SetPosition(D3DXVECTOR3 pos);
	void SetRot(D3DXVECTOR3 rot);
	void SetParent(CModel *pModel);
	//MODEL *GetModel(void);
	D3DXMATRIX GetMtxWorld(void);

private:

	CModel									*m_pModel;						// モデルへのポインタ
	CModel									*m_pParent;						// 親モデルへのポインタ;

	static LPDIRECT3DTEXTURE9				m_pTexture;						// テクスチャ
	LPDIRECT3DVERTEXBUFFER9					m_pVtxBuff;						// 頂点バッファのポインタ
	LPD3DXMESH								m_pMeshModel;					// メッシュ情報へのポインタ
	DWORD									m_nNumMatModel;					// マテリアル情報の数
	LPD3DXBUFFER							m_pBuffMatModel;				// マテリアル情報へのポインタ
	D3DXMATERIAL							*m_pMat;
	//DWORD									m_nNumMat;						// マテリアル情報の数
	D3DXVECTOR3								m_pos;							// 位置
	D3DXVECTOR3								m_rot;							// 向き
	D3DXMATRIX								m_mtxWorld;						// ワールドマトリックス
	D3DXVECTOR3								m_VtxMinModel, m_VtxMaxModel;	// モデルの最小値、最大値
	D3DXVECTOR3								m_move;
};
#endif