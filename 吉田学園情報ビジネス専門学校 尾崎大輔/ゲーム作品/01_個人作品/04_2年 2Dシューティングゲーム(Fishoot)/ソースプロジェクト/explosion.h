//=============================================================================
//
// 爆発の処理 [explosion.h]
// Author : Ozaki
//
//=============================================================================
#pragma once
#ifndef _EXPLPSION_H_
#define _EXPLOSION_H_

#include "scene2D.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MAX_EXPLOSION	(256)		// 爆発の最大数
#define MAX_MIKY		(50)		// 爆発の大きさ
#define TEX_U			(8)			// テクスチャ横の分割数
#define TEX_V			(1)			// テクスチャ縦の分割数

//*****************************************************************************
// クラス宣言
//*****************************************************************************
class CBullet;

class CExplosion : public CScene2D //CPlayer
{
public:

	CExplosion();
	~CExplosion();

	static HRESULT Load(void);	// 読み込み

	static void Unload(void);	// 開放

	static CExplosion *Create(D3DXVECTOR3 pos, float widtgh, float height);

	HRESULT Init(D3DXVECTOR3 pos, float widtgh, float height);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:

	// 共有テクスチャへのポインタ
	static LPDIRECT3DTEXTURE9	m_pTexture;					// 保存する場所
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;

	D3DXVECTOR3					m_move;						//移動量
	float						m_rot = 0.0f;
	float						m_position = 0.0f;
	float						m_Addposition = 1.0f;

protected:

	int							m_nCounterAnim;				//アニメーションカウンター
	int							m_nPatternAnim;				//アニメーションパターン

	//int m_nCounterState;		//状態管理カウンター
	//int m_nLife;				//体力
	//bool m_bDisp;				//使用してるかどうか
};
#endif