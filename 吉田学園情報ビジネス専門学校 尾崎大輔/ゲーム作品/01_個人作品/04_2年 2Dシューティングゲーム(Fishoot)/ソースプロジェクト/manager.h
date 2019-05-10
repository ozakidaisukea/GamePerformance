//=============================================================================
//
// マネージャーの処理 [manager.h]
// Author : Ozaki
//
//=============================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "main.h"
#include "input.h"

#define MAX_RANKING	(5)

//*****************************************************************************
// クラス宣言
//*****************************************************************************
class CTitle;
class CGame;
class CResult;
class CGameover;
class CRanking;
class CTutorial;
class CSound;
class CFade;
class CScore;
class CInputjoypad;
class CSousa;

class CManager
{
public:

	typedef enum
	{
		MODE_TITLE = 0,
		MODE_SOUSA,
		MODE_TUTORIAL,
		MODE_GAME,
		MODE_RESULT,
		MODE_GAMEOVER,
		MODE_RANKING,
		MODE_MAX
	}MODE;

	CManager();
	~CManager();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// モードを取得
	static MODE GetMode(void);

	// モードの設定
	static void SetMode(MODE mode);

	// レンダラー
	static CRenderer *GetRenderer(void);

	// キーボード
	static CInputKeyboard *GetInputKeyboard(void);

	// パッド
	static CInputjoypad *GetInputJoypad(void);

	// サウンド
	static CSound *GetSound(void);

	// フェード
	static CFade *GetFade(void);

	// スコア
	static CScore *GetScore(void);

	// ゲーム
	static CGame *GetGame(void);

	// チュートリアル
	static CTutorial *GetTutorial(void);

	// 操作方法
	static CSousa *GetSousa(void);

	// ランキングを並び替え
	static void RankingScore(int m_pScore);

	static int GetRankingScore(int nIdx);

private:

	// モード
	static MODE m_mode;

	// レンダラー
	static CRenderer *m_pRenderer;

	// キーボード
	static CInputKeyboard *m_pInputKeyboard;

	// ジョイパッド
	static CInputjoypad *m_pInputJoypad;

	// サウンド
	static CSound *m_pSound;

	// タイトル
	static CTitle *m_pTitle;

	// チュートリアル
	static CTutorial *m_pTutorial;

	// ゲーム
	static CGame *m_pGame;

	// リザルト
	static CResult *m_pResult;

	// ゲームオーバー
	static CGameover *m_pGameover;

	// ランキング
	static CRanking *m_pRanking;

	// フェード
	static CFade *m_pFade;

	// スコア
	static CScore *m_pScore;

	// 操作方法
	static CSousa *m_pSousa;

	// ランキングの
	static int m_Rankingscore[MAX_RANKING];
};
#endif