//=============================================================================
//
//	ゲージの処理 [gauge.h]
// Author : Ozaki
//
//=============================================================================
#ifndef _GAUGE_H_
#define _GAUGE_H_


#include "scene2D.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_GAUGE				(3)					// ゲージの最大数
#define REDUCE_GAUGE			(0.08f)				// ゲージの減る量(毎フレーム)
#define GAUGE_VALUE				(250.0f)			// ゲージの最大値
//*****************************************************************************
// クラス宣言
//*****************************************************************************
class CRenderer;
class CItem;
class CPlayer;
class CScene2D;

class CGauge : public CScene2D
{
public:
	CGauge();
	~CGauge();

	static HRESULT Load(void);	// 読み込み

	static void Unload(void);	// 開放

	static CGauge *Create(D3DXVECTOR3 pos, float widtgh, float height);

	HRESULT Init(D3DXVECTOR3 pos, float widtgh, float height);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static void AddGauge(float f_itemgauge);

	static float					m_fGauge;							// ゲージの値

private:

	static LPDIRECT3DTEXTURE9		m_pTexture[MAX_GAUGE];				// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9			m_pVtxBuff= NULL;					// 頂点バッファへのポインタ
	CScene2D						*m_Scene2D[MAX_GAUGE];
	float							m_fGaugeColR = 1.0f;				// ゲージの色(赤)
	float							m_fGaugeColG = 0.0f;				// ゲージの色(緑)
	float							m_fGaugeColB = 0.0f;				// ゲージの色(青)
	D3DXVECTOR3						m_move;

};
#endif