//=============================================================================
//
// ギミック処理 [gimmick.h]
// Author : Ozaki
//
//=============================================================================
#ifndef _GIMMICK_H_
#define _GIMMICK_H_

#include "main.h"
#include "scene.h"

//*****************************************************************************
// モデル
//*****************************************************************************
#define MODEL_GIMMICK			"data\\MODEL\\gimmick000.x"
#define MODEL_TYPE			(2)
//*****************************************************************************
// クラス宣言
//*****************************************************************************

class CGimmick : CScene
{
public:

	typedef enum
	{
		GIMMICK_NONE = 0,
		GIMMICK_HEIHT,
		GIMMICK_WIDTH,
		GIMMICK_MAX
	}GIMMICK_TYPE;

	CGimmick();
	~CGimmick();

	HRESULT Init(void);
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);
	void	BindTexture(LPDIRECT3DTEXTURE9 texture);
	float	GetLHeght(D3DXVECTOR3 pos);
	static CGimmick *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot,GIMMICK_TYPE type);

private:

	GIMMICK_TYPE				m_nType;			// タイプ
	D3DXVECTOR3					m_pos;				// 位置
	D3DXVECTOR3					m_rot;				// 向き
	D3DXVECTOR3					m_move;				// 動き
	static LPDIRECT3DTEXTURE9	m_pTexture;			// テクスチャのポインタ
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;			// 頂点バッファのポインタ
	LPD3DXMESH					m_pMeshModel;		// メッシュ情報へのポインタ
	DWORD						m_nNumMatModel;		// マテリアル情報の数
	LPD3DXBUFFER				m_pBuffMatModel;	// マテリアル情報へのポインタ
	D3DXMATRIX					m_mtxWorld;			//ワールドマトリックス
	D3DXMATERIAL				*m_pMat;
	D3DXVECTOR3					m_vtxMin;			// モデルの最小値
	D3DXVECTOR3					m_vtxMax;			// モデルの最大値
};

#endif