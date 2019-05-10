//=============================================================================
//
// ”šˆ— [number.h]
// Author : Ozaki
//
//=============================================================================
#ifndef _NUMBER_H_
#define _NUMBER_H_

#include "scene2D.h"
#include "score.h"

//*****************************************************************************
// ƒNƒ‰ƒXéŒ¾
//*****************************************************************************
class CNumber
{
public:

	CNumber();
	~CNumber();

	static void Load(void);	// “Ç‚İ‚İ

	static void Unload(void);	// ŠJ•ú

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