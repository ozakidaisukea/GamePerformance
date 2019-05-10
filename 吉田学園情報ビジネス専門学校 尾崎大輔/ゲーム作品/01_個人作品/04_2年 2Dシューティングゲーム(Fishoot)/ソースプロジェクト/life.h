//=============================================================================
//
// ライフ処理 [life.h]
// Author : Ozaki
//
//=============================================================================
#ifndef _LIFE_H_
#define _LIFE_H_

#include "main.h"
#include "scene2D.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_LIFE (5)

//*****************************************************************************
// クラス宣言
//*****************************************************************************
class CLIfeScene2D;

class CLife : public CScene
{
public:
	CLife();
	~CLife();

	static HRESULT Load(void);	// 読み込み

	static void Unload(void);	// 開放

	HRESULT Init(D3DXVECTOR3 pos, float widtgh, float height);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void CutLife(int nLife);

	int GetLife(int nLife);

	static	CLife *Create(D3DXVECTOR3 pos, float widtgh, float height);

	CLIfeScene2D					*m_apScene2D[MAX_LIFE];

	int								 m_nLife;

private:

	// 共有テクスチャへのポインタ
	static LPDIRECT3DTEXTURE9		m_pTexture;	// 保存する場所
	LPDIRECT3DVERTEXBUFFER9			m_pVtxBuff;

};
#endif