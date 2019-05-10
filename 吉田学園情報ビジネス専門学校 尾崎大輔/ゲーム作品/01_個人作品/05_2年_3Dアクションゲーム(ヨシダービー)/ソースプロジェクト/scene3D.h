//=============================================================================
//
// シーン3D 処理 [scene3D.h]
// Author : Ozaki
//
//=============================================================================
#ifndef _SCENE3D_H_
#define _SCENE3D_H_

#include "main.h"
#include "scene.h"

//*****************************************************************************
// クラス宣言
//*****************************************************************************
class CPlayer;

class CScene3D : public CScene
{
public:

	CScene3D(int nCntPriority, OBJTYPE objtype = CScene::OBJTYPE_3D);
	~CScene3D();

	HRESULT Init(void);
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);
	void	BindTexture(LPDIRECT3DTEXTURE9 texture);
	float	GetLHeght(D3DXVECTOR3 pos);
	static CScene3D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

private:

	float									m_rot = 0.0f;
	float									m_position = 0.0f;
	float									m_Addposition = 1.0f;

	static LPDIRECT3DTEXTURE9				m_pTexture;					// テクスチャ
	LPDIRECT3DVERTEXBUFFER9					m_pVtxBuff;					// 頂点バッファのポインタ
	D3DXVECTOR3								m_pos;						// 位置
	D3DXVECTOR3								m_rotpolygon;				// 向き
	D3DXMATRIX								m_mtxWorldPolygon;			// ワールドマトリックス
	D3DXVECTOR3								m_aPos[6];
	static CPlayer							*m_Playerpos;
};
#endif