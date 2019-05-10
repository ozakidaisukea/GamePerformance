//=============================================================================
//
// エフェクトの処理 [effect.h]
// Author : Ozaki
//
//=============================================================================
#pragma once
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "scene2D.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MAX_EFFECT		(256)		// 弾の最大数
#define ADD_POSITION	(50)
#define MAX_TEXEFFECT	(2)
//*****************************************************************************
// クラス宣言
//*****************************************************************************
class CPlayer;
class CExplosion;
class CEnemy;

class CEffect : public CScene2D
{
public:

	CEffect();
	~CEffect();

	static HRESULT Load(void);	// 読み込み

	static void Unload(void);	// 開放

	static	CEffect *Create(D3DXVECTOR3 pos, D3DXCOLOR col, float widtgh, float height);

	HRESULT Init(D3DXVECTOR3 pos, D3DXCOLOR col, float widtgh, float height);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:

	// 爆発
	static CExplosion *m_pExplosion;

	// 共有テクスチャへのポインタ
	static LPDIRECT3DTEXTURE9	m_pTexture;									// 保存する場所
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuffBullet = NULL;				    // 頂点バッファへのポインタ
	D3DXVECTOR3					m_move;										// 移動量
	D3DXCOLOR					m_col;										// 色
	int							m_nLife;									// 表示時間(寿命)
	float						m_rot = 0.0f;
	float						m_position = 0.0f;
	float						m_Addposition = 1.0f;
	float						m_bUse;

protected:
	float					m_fLength = 0.0f;

};
#endif