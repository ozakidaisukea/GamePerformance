//=============================================================================
//
// メッシュフィールドの処理 [meshField.h]
// Author :
//
//=============================================================================
#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_

#include "main.h"
#include "scene.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_NOR		(10000)
#define XSize		(10)
#define ZSize		(10)

#define mPolygonX	(50)				// 横の頂点数
#define mPolygonZ	(50)				// 縦の頂点数
#define X_SIZE		(1200)				// Xのサイズ
#define Z_SIZE		(3600)				// Zのサイズ
//=============================================================================
//	メッシュフィールドクラス（シーンの派生クラス）
//=============================================================================
class CMeshFiled : public CScene
{
public:
	CMeshFiled(int nPriarity, CScene::OBJTYPE objtype);		//	コンストラクタ
	~CMeshFiled();											//	デストラクタ

	void Load(void);								// 読み込み
	void Unload(void);								// 開放

	HRESULT Init(void);										//	初期化処理
	void Uninit(void);										//	終了処理
	void Update(void);										//	更新処理
	void Draw(void);										//	描画処理
	void BindTexture(LPDIRECT3DTEXTURE9		pTexture);		//	共通テクスチャを割り当てる
	static CMeshFiled *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fDepth, int nCutX, int nCutZ);		//	ポリゴンの生成
	//float CMeshFiled::GetHeight(D3DXVECTOR3 pos);			//	地面の高さの取得
	void SetHigth(D3DXVECTOR3 pos, float fValue, float fRange);
	void Save(void);


private:
	LPDIRECT3DTEXTURE9		m_pTexture;						//　テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;						//　頂点バッファへのポインタ
	LPDIRECT3DINDEXBUFFER9	m_pIdxBuff;						//  インデックスバッファへのポインタ
	D3DXVECTOR3				m_pos;							//　位置
	D3DXVECTOR3				m_rot;							//　向き
	D3DXMATRIX				m_mtxworld;						//	ワールドマトリックス
	float					m_fWidth;						//	幅
	float					m_fDepth;						//	奥行
	int						m_nNumVtx;						//  頂点数
	int						m_nNumIdx;						//  インデックス数
	int						m_nNumPolygon;					//  ポリゴン数
	int						m_nCutX;						//  横のメッシュの分割数
	int						m_nCutZ;						//  縦のメッシュの分割数
	float					m_posY;
	float					m_aHeight;
protected:
};
#endif