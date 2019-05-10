//=============================================================================
//
// ゲーム処理 [game.h]
// Author : Ozaki
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"
#include "scene2D.h"

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
#define ENEMYLIFE_NO5	(20)

//*****************************************************************************
// クラス宣言
//*****************************************************************************
class CBullet;
class CRenderer;
class CInputKeyboard;
class CPlayer;
class CEnemy;
class CCamera;
class CLight;
class CFade;
class CMeshFiled;
class CWall;
class CObjectBG;
class CStarter;
class CHorse;
class CHorse2;
class CHorse3;
class CHorse4;
class CHorse5;
class CHorse6;
class CHorse7;
class CHorse8;
class CHorse9;
class CHorse10;
class CGate;
class CJockey;
class CJockey2;
class CJockey3;
class CJockey4;
class CJockey5;
class CJockey6;
class CJockey7;
class CJockey8;
class CJockey9;
class CJockey10;
class COwner;
class CUnion;
class CScene3D;
class CLogo;
class CInputjoypad;
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

	HRESULT Load(void);	// 読み込み

	void Unload(void);	// 開放

	static CGame *Create(void);

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// プレイヤー
	static CPlayer *GetPlayer(void);

	// 敵
	static CEnemy *GetEnemy(void);

	// 馬
	static CHorse *GetHorse(void);
	// 馬
	static CHorse2 *GetHorse2(void);
	// 馬
	static CHorse3 *GetHorse3(void);
	// 馬
	static CHorse4 *GetHorse4(void);
	// 馬
	static CHorse5 *GetHorse5(void);
	// 馬
	static CHorse6 *GetHorse6(void);
	// 馬
	static CHorse7 *GetHorse7(void);
	// 馬
	static CHorse8 *GetHorse8(void);
	// 馬
	static CHorse9 *GetHorse9(void);
	// 馬
	static CHorse10 *GetHorse10(void);


	// カメラ
	static CCamera *GetCamera(void);

	// ライト
	static CLight *GetLight(void);

	// メッシュフィールド
	static CMeshFiled *GetMeshFiled(void);

	// 壁
	static CWall *GetWall(void);

	// オブジェクト背景
	static CObjectBG *GetObjectbg(void);

	// スターター
	static CStarter *GetStarter(void);

	// ゲート
	static CGate *GetGate(void);

	// ジョッキー
	static CJockey *GetJockey(void);
	// ジョッキー
	static CJockey2 *GetJockey2(void);
	// ジョッキー
	static CJockey3 *GetJockey3(void);
	// ジョッキー
	static CJockey4 *GetJockey4(void);
	// ジョッキー
	static CJockey5 *GetJockey5(void);
	// ジョッキー
	static CJockey6 *GetJockey6(void);
	// ジョッキー
	static CJockey7 *GetJocke7(void);
	// ジョッキー
	static CJockey8 *GetJocke8(void);
	// ジョッキー
	static CJockey9 *GetJockey9(void);
	// ジョッキー
	static CJockey10 *GetJockey10(void);
	// オーナー
	static COwner *GetOwner(void);

	// 合体
	static CUnion *GetUnion(void);

	// シーン3D
	static CScene3D *GetScene3D(void);

	static CLogo *GetLogo(void);

	// ゲージ
	static CGauge *GetGauge(void);

	static int	GetTime(void);

private:

	// プレイヤー
	static CPlayer *m_pPlayer;

	// 敵
	static CEnemy *m_pEnemy;

	// カメラ
	static CCamera *m_pCamera;

	// ライト
	static CLight *m_pLight;

	// メッシュフィールド
	static CMeshFiled *m_pMeshField;

	// 壁
	static CWall *m_pWall;

	// オブジェクト背景
	static CObjectBG *m_pObjectbg;

	// スターター
	static CStarter *m_pStarter;

	// 馬
	static CHorse *m_pHorse;
	// 馬
	static CHorse2 *m_pHorse2;
	// 馬
	static CHorse3 *m_pHorse3;
	// 馬
	static CHorse4 *m_pHorse4;
	// 馬
	static CHorse5 *m_pHorse5;
	// 馬
	static CHorse6 *m_pHorse6;
	// 馬
	static CHorse7 *m_pHorse7;
	// 馬
	static CHorse8 *m_pHorse8;
	// 馬
	static CHorse9 *m_pHorse9;
	// 馬
	static CHorse10 *m_pHorse10;

	// ゲート
	static CGate *m_pGate;

	// ジョッキー
	static CJockey *m_pJockey;
	// ジョッキー
	static CJockey2 *m_pJockey2;
	// ジョッキー
	static CJockey3 *m_pJockey3;
	// ジョッキー
	static CJockey4 *m_pJockey4;
	// ジョッキー
	static CJockey5 *m_pJockey5;
	// ジョッキー
	static CJockey6 *m_pJockey6;
	// ジョッキー
	static CJockey7 *m_pJockey7;
	// ジョッキー
	static CJockey8 *m_pJockey8;
	// ジョッキー
	static CJockey9 *m_pJockey9;
	// ジョッキー
	static CJockey10 *m_pJockey10;

	// ロゴ
	static CLogo *m_pLogo;

	// オーナー
	static COwner *m_pOwner;

	// 合体
	static CUnion *m_pUnion;

	// シーン3D
	static CScene3D *m_pScene3D;

	// ゲージ
	static CGauge *m_pGauge;

	static LPDIRECT3DTEXTURE9			m_pTexture;
	static LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;
	int									m_nCounterGameState;
	int									m_Gametimmer;
	static STATE						m_State;
	int									m_nIndex;
	static int							m_nTimer;

};
#endif

