//=============================================================================
//
// チュートリアル処理 [tutorial.h]
// Author : Ozaki
//
//=============================================================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

#include "scene2D.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TUTORIAL_WIDTH		(SCREEN_WIDTH)
#define TUTORIAL_HEIGHT		(SCREEN_HEIGHT)

//*****************************************************************************
// クラス宣言
//*****************************************************************************
class CBullet;
class CRenderer;
class CInputKeyboard;
class CPlayer;
class CExplosion;
class CScore;
class CLife;
class CEffect;
class CEnemy;
class CLIfe;
class CFade;
class CItem;
class CLogo;
class CInputjoypad;

class CTutorial
{
public:

	typedef enum
	{
		TUTORIALSTATE_NONE = 0,			//何もしていない状態
		TUTORIALSTATE_NORMAL,			//通常状態
		TUTORIALSTATE_END,				//終了状態
		TUTORIALSTATE_GAMEOVER,
		TUTORIALSTATE_MAX,
	}TUTORIALSTATE;

	CTutorial();
	~CTutorial();

	HRESULT Load(void);	// 読み込み

	void Unload(void);	// 開放

	static CTutorial *Create(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// プレイヤー
	static CPlayer *GetPlayer(void);

	// ロゴ
	static CLogo *GetLogo(void);

private:

	// プレイヤー
	static CPlayer *m_pPlayer;

	// ロゴ
	static CLogo *m_pLogo;

	static LPDIRECT3DTEXTURE9			m_pTexture;
	static LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;
	int									m_nCounterTutorialState;
	int									m_Tutorial;

};
#endif

