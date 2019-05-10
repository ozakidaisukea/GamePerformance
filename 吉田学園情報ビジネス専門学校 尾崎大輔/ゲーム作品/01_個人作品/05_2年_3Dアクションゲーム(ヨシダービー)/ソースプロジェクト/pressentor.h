//=============================================================================
//
// プレスエンターの処理 [Pressentor.h]
// Author : Ozaki
//
//=============================================================================
#ifndef _PRESSENTOR_H_
#define _PRESSENTOR_H_

#include "scene2D.h"
#include "logo.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_ENTOR (8)

//*****************************************************************************
// クラス宣言
//*****************************************************************************
class CPressEntor : public CLogo
{
public:
	CPressEntor();
	~CPressEntor();

	static HRESULT Load(void);	// 読み込み

	static void Unload(void);	// 開放

	HRESULT Init(D3DXVECTOR3 pos, float widtgh, float height);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static	CPressEntor *Create(D3DXVECTOR3 pos, float widtgh, float height);

private:

	D3DXVECTOR3						m_move;							// 移動量
	float							m_rot = 0.0f;
	float							m_position = 0.0f;
	D3DXVECTOR3						m_pos;
	float							m_flength;
	// プレスエンター
	int								m_nCntEnter = 0;
	float							m_fEnterTimer = 0.0f;

	// 共有テクスチャへのポインタ
	static LPDIRECT3DTEXTURE9		m_pTexture;					// 保存する場所
	LPDIRECT3DVERTEXBUFFER9			m_pVtxBuff = NULL;			// 頂点バッファへのポインタ

	CScene2D						*m_apScene2D;

protected:

	float							m_Perjudgment;
};
#endif