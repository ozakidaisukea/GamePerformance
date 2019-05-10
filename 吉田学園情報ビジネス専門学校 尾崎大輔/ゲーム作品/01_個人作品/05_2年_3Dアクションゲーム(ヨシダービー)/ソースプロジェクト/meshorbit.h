//=============================================================================
//
// メッシュオービットの処理 [meshorbit.h]
// Author : Ozaki
//
//=============================================================================
#ifndef _MESHORBIT_H_
#define _MESHORBIT_H_

#include "main.h"
#include "scene.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_NOR		(10000)			//
#define MAX_NUM		(10)			// 頂点の最大数
#define NUM_OFFSET	(2)				// オフセット数
//=============================================================================
//	メッシュオービットクラス（シーンの派生クラス）
//=============================================================================
class CMeshOrbit : public CScene
{
public:
	CMeshOrbit(int nPriarity, CScene::OBJTYPE objtype);		//	コンストラクタ
	~CMeshOrbit();											//	デストラクタ
	HRESULT Init(void);										//	初期化処理
	void Uninit(void);										//	終了処理
	void Update(void);										//	更新処理
	void Draw(void);										//	描画処理
	static CMeshOrbit * Create(D3DXMATRIX mtxWorld);
	void SetMtxParent(D3DXMATRIX *pMtx);
	void BindTexture(LPDIRECT3DTEXTURE9 texture);

private:

	static LPDIRECT3DTEXTURE9	m_pTexture;						//　テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;						//　頂点バッファへのポインタ

	D3DXVECTOR3					m_pos;							//　位置
	D3DXVECTOR3					m_rot;							//　向き
	D3DXVECTOR3					m_aPosVertex[MAX_NUM];			//	算出した頂点座標
	D3DXVECTOR3					m_affset[NUM_OFFSET];			//	両端のオフセット
	D3DXMATRIX					m_mtxworld;						//	ワールドマトリックス
	D3DXMATRIX					*m_pMtxParent;					//	親のマトリックスへのポインタ
	int							m_nWidth;

protected:
};
#endif