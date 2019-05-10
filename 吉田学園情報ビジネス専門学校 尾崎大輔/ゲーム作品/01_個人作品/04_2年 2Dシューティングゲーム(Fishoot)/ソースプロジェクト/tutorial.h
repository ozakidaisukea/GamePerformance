//=============================================================================
//
// チュートリアル処理 [tutorial.h]
// Author : Ozaki
//
//=============================================================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

#include "scene2D.h"
#include "score.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TUTORIAL_WIDTH		(SCREEN_WIDTH)
#define TUTORIAL_HEIGHT	(SCREEN_HEIGHT)

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

class CTutorial
{
public:

	typedef enum
	{
		TUTORIALSTATE_NONE = 0,			//何もしていない状態
		TUTORIALSTATE_NORMAL,			//通常状態
		TUTORIALSTATE_END,				//終了状態
		TUTORIALSTATE_BOSS,
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

	// 敵
	static CEnemy *GetEnemy(void);

	// スコア
	static CScore *GetScore(void);

	// ライフ
	static CLife *GetLife(void);

	// アイテム
	static CItem *GetItem(void);

	// ロゴ
	static CLogo *GetLogo(void);

private:

	static LPDIRECT3DTEXTURE9			m_pTexture;
	static LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;
	int									m_nCounterTutorialState;

	// プレイヤー
	static CPlayer *m_pPlayer;

	// 敵
	static CEnemy *m_pEnemy;

	// スコア
	static CScore *m_pScore;

	// ライフ
	static CLife *m_pLife;

	// アイテム
	static CItem *m_pItem;

	// ロゴ
	static CLogo *m_pLogo;

	int	m_ItemTimer;


};
#endif

