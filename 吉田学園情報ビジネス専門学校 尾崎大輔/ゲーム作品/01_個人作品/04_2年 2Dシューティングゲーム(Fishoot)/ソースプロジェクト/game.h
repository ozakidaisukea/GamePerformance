//=============================================================================
//
// ゲーム処理 [game.h]
// Author : Ozaki
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "scene2D.h"
#include "score.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define GAME_WIDTH		(SCREEN_WIDTH)
#define GAME_HEIGHT		(SCREEN_HEIGHT)
#define MAX_ENEMY		(5)
#define MAX_GAUGE		(3)
#define ENEMYLIFE_NO1	(3)
#define ENEMYLIFE_NO2	(5)
#define ENEMYLIFE_NO3	(10)
#define ENEMYLIFE_NO4	(15)
#define ENEMYLIFE_NO5	(40)

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
class CGauge;

class CGame
{
public:

	typedef enum
	{
		STATE_NONE = 0,			//何もしていない状態
		STATE_NORMAL,			//通常状態
		STATE_RESULT,			//終了状態
		STATE_GAMEOVER,
		STATE_MAX,
	}STATE;

	CGame();
	~CGame();

	void Load(void);	// 読み込み

	void Unload(void);	// 開放

	static CGame *Create(void);

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// プレイヤー
	static CPlayer *GetPlayer(void);

	// 敵
	static CEnemy *GetEnemy(int nIdx);

	static void SetEnemy(int nIdx, CEnemy* pEnemy);

	// スコア
	static CScore *GetScore(void);

	// ライフ
	static CLife *GetLife(void);

	// アイテム
	static CItem *GetItem(void);

	// ゲージ
	static CGauge *GetGauge(void);

	int GetNumEnemy(void);
	int GetNumEnemyAll(void);

	void SetNumEnemy(int nNumEnemy);
	void SetNumEnemyAll(int nNumEnemyAll);
	static void SetState(STATE state);

	void SetEnemy(void);

private:

	void	SetEnemy00(void);
	void	SetEnemy01(void);
	void	SetEnemy02(void);
	void	SetEnemy03(void);
	void	SetEnemy04(void);


	static LPDIRECT3DTEXTURE9			m_pTexture;
	static LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;
	int									m_nCounterGameState;
	//static int							m_Creattimer;


	// プレイヤー
	static CPlayer *m_pPlayer;

	// 敵
	static CEnemy *m_pEnemy[MAX_ENEMY];

	// スコア
	static CScore *m_pScore;

	// ライフ
	static CLife *m_pLife;

	// アイテム
	static CItem *m_pItem;

	// ゲージ
	static CGauge *m_pGauge[MAX_GAUGE];

	static STATE m_State;
	int	m_nNumEnemy;
	int m_nNumEnemyAll;
	int	m_nIndex;
	int	m_ItemTimer;

};
#endif

