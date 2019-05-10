//=============================================================================
//
// アイテムの処理 [item.h]
// Author : Ozaki
//
//=============================================================================
#pragma once
#ifndef _ITEM_H_
#define _ITEM_H_

#include "scene2D.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MAX_ITEM		(256)		// アイテムの最大数
#define MAX_MIKY		(50)		// アイテムの大きさ
#define TEX_U			(8)			// テクスチャ横の分割数
#define TEX_V			(1)			// テクスチャ縦の分割数

//*****************************************************************************
// クラス宣言
//*****************************************************************************
class CPlayer;
class CGauge;
class CScore;

class CItem : public CScene2D
{
public:

	typedef enum
	{
		ITEM_NORMAL0 = 0,
		ITEM_HIGH0,
		ITEM_NORMAL1,
		ITEM_HIGH1,
		ITEM_MAX
	}ITEM_TYPE;

	CItem();
	~CItem();

	static HRESULT Load(void);	// 読み込み

	static void Unload(void);	// 開放

	static CItem *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float widtgh, float height,ITEM_TYPE type);

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, float widtgh, float height, ITEM_TYPE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	// スコア
	static CScore				*m_apScore;

	// 共有テクスチャへのポインタ
	static LPDIRECT3DTEXTURE9	m_pTexture[MAX_ITEM];	// 保存する場所
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;
	//CGauge						*f_gauge;				// ゲージの値
	ITEM_TYPE					m_type;
	D3DXVECTOR3					m_move;					//移動量
	float						m_rot = 0.0f;
	float						m_pos = 0.0f;
	float						m_Addposition = 1.0f;

protected:
};
#endif