//=============================================================================
//
// ゲームオーバー処理 [gameover.h]
// Author : Ozaki
//
//=============================================================================
#ifndef _GAMEOVER_H_
#define _GAMEOVER_H_

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

class CGameover
{
public:

	CGameover();
	~CGameover();

	HRESULT Load(void);	// 読み込み

	void Unload(void);	// 開放

	static CGameover *Create(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:

	static LPDIRECT3DTEXTURE9			m_pTexture;
	static LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;
};
#endif

