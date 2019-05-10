//=============================================================================
//
// マネージャーの処理 [manager.h]
// Author : Ozaki
//
//=============================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "main.h"

//*****************************************************************************
// クラス宣言
//*****************************************************************************
class CRenderer;
class CInputKeyboard;
class CCamera;
class CLight;
class CPlayer;
class CScene3D;
class CMeshFiled;
class CGimmick;
class CMeshOrbit;
class CSound;
class CFade;
class CTitle;
class CTutorial;
class CGame;
class CResult;
class CRanking;
class CInputjoypad;

class CManager
{
public:

	typedef enum
	{
		MODE_TITLE = 0,
		MODE_TUTORIAL,
		MODE_GAME,
		MODE_RESULT,
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

	// サウンド
	static CSound *GetSound(void);

	// モードの設定
	static void SetMode(MODE mode);

	// レンダラー
	static CRenderer *GetRenderer(void);

	// キーボード
	static CInputKeyboard *GetInputKeyboard(void);

	// タイトル
	static CTitle *GetTitle(void);

	// チュートリアル
	static CTutorial *GetTutorial(void);

	// ゲーム
	static CGame *GetGame(void);

	// リザルト
	static CResult *GetResult(void);

	// ランキング
	static CRanking *GetRamking(void);

	// ライト
	static CLight *GetLight(void);

	// シーン3D
	static CScene3D *GetScene3D(void);

	// プレイヤー
	static CPlayer *GetPlayer(void);

	// フェード
	static CFade *GetFade(void);

	// メッシュフィールド
	static CMeshFiled *GetMeshField(void);

	// メッシュオービット
	static CMeshOrbit *GetMeshOrbit(void);

	// パッド
	static CInputjoypad *GetInputJoypad(void);

	// モード
	static MODE m_mode;

private:

	// サウンド
	static CSound *m_pSound;

	// レンダラー
	static CRenderer *m_pRenderer;

	// カメラ
	static CCamera *m_pCamera;

	// ジョイパッド
	static CInputjoypad *m_pInputJoypad;

	// ライト
	static CLight *m_pLight;

	// シーン3D
	static CScene3D *m_pScene3D;

	// キーボード
	static CInputKeyboard *m_pInputKeyboard;

	// タイトル
	static CTitle *m_pTitle;

	// チュートリアル
	static CTutorial *m_pTutorial;

	// ゲーム
	static CGame *m_pGame;

	// リザルト
	static CResult *m_pResult;

	// ランキング
	static CRanking *m_pRanking;

	// プレイヤー
	static CPlayer *m_pPlayer;

	// フェード
	static CFade *m_pFade;

	// メッシュフィールド
	static CMeshFiled *m_pMeshField;

	// メッシュオービット
	static CMeshOrbit *m_pMeshOrbit;

	static int m_playertaime;
};
#endif