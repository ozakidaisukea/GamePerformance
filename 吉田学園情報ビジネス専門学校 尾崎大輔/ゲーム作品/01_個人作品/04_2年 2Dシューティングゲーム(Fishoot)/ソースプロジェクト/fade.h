//=============================================================================
//
// フェード処理 [fade.h]
// Author : Ozaki
//
//=============================================================================
#ifndef _FADE_H_
#define _FADE_H_

#include "scene2D.h"
#include "score.h"
#include "manager.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define Title_WIDTH		(SCREEN_WIDTH)
#define Title_HEIGHT	(SCREEN_HEIGHT)

//*****************************************************************************
// クラス宣言
//*****************************************************************************
class CFade
{
public:

	//*************************************
	// フェードの状態
	//*************************************
	typedef enum
	{
		FADE_NONE = 0,		// 何もしていない状態
		FADE_IN,			// フェードイン状態
		FADE_OUT,			// フェードアウト状態
		FADE_MAX
	} FADE;

	CFade();
	~CFade();

	HRESULT Load(void);	// 読み込み

	void Unload(void);	// 開放

	static CFade *Create(void);

	HRESULT Init(CManager::MODE modeNext);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetFade(CManager::MODE modeNext);
	static FADE GetFade(void);

private:

	static FADE							m_fade;					// フェード状態
	static CManager::MODE				m_modeNext;				// 次のモード
	static D3DXCOLOR					m_colorFade;			// フェード色
	static LPDIRECT3DTEXTURE9			m_pTexture;
	static LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;
};
#endif

