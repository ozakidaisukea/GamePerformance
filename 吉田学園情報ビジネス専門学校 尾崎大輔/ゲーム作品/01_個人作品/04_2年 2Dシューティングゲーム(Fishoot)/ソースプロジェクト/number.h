//=============================================================================
//
// 数字処理 [number.h]
// Author : Ozaki
//
//=============================================================================
#ifndef _NUMBER_H_
#define _NUMBER_H_

#include "scene2D.h"
#include "score.h"

//*****************************************************************************
// クラス宣言
//*****************************************************************************
class CNumber
{
public:

	CNumber();
	~CNumber();

	static void Load(void);	// 読み込み

	static void Unload(void);	// 開放

	void Init(D3DXVECTOR3 pos, float widtgh, float height);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CNumber *Create(D3DXVECTOR3 pos, float widtgh, float height);
	void SetNumber(int nNumber);

private:

	static LPDIRECT3DTEXTURE9	m_pTexture;
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;
};
#endif