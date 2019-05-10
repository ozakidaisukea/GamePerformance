//=============================================================================
//
// 操作処理 [sousa.h]
// Author : Ozaki
//
//=============================================================================
#ifndef _SOUSA_H_
#define _SOUSA_H_

#include "scene2D.h"
#include "score.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define Title_WIDTH		(SCREEN_WIDTH)
#define Title_HEIGHT	(SCREEN_HEIGHT)

//*****************************************************************************
// クラス宣言
//*****************************************************************************
class CFade;
class CSound;

class CSousa
{
public:

	CSousa();
	~CSousa();

	HRESULT Load(void);	// 読み込み

	void Unload(void);	// 開放

	static CSousa *Create(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:

	static CSound						*m_pSound;
	D3DXVECTOR3							m_move;
	static LPDIRECT3DTEXTURE9			m_pTexture;
	static LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;
};
#endif

