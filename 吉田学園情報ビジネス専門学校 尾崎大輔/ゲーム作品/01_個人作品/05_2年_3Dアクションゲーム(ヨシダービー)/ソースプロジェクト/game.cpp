//=============================================================================
//
// ゲーム処理 [game.cpp]
// Author : Ozaki
//
//=============================================================================
#include "game.h"			// ゲーム
#include "manager.h"		// マネージャー
#include "main.h"			// メイン
#include "renderer.h"		// レンダラー
#include "scene.h"			// シーン
#include "scene2D.h"		// シーン2D
#include "scene3D.h"		// シーン3D
#include "input.h"			// 入力
#include "enemyr.h"			// 敵
#include "bullet.h"			// 弾
#include "sound.h"			// サウンド
#include "title.h"			// タイトル
#include "fade.h"			// フェード
#include "camera.h"			// カメラ
#include "light.h"			// ライト
#include "meshfield.h"		// メッシュフィールド
#include "wall.h"			// メッシュウォール
#include "debugproc.h"		// デバック表示
#include "objectbg.h"		// オブジェクト背景
#include "starterh.h"		// スターター
#include "horse.h"			// 他の馬
#include "gate.h"			// ゲート
#include "owner.h"			// 馬主(player)
#include "union.h"			// 馬とジョッキー
#include "logo.h"
#include "gauge.h"

#include "player.h"			// プレイヤー
#include "jockey.h"			// ジョッキー
#include "horse2.h"			// 馬２
#include "horse3.h"
#include "horse4.h"
#include "horse5.h"
#include "horse6.h"
#include "horse7.h"
#include "horse8.h"
#include "horse9.h"
#include "horse10.h"
#include "jockey2.h"
#include "jockey3.h"
#include "jockey4.h"
#include "jockey5.h"
#include "jockey6.h"
#include "jockey7.h"
#include "jockey8.h"
#include "jockey9.h"
#include "jockey10.h"

//=============================================================================
// 静的メンバ変数
//=============================================================================
CEnemy*CGame::m_pEnemy = NULL;
CCamera*CGame::m_pCamera = NULL;
CLight*CGame::m_pLight = NULL;
CMeshFiled*CGame::m_pMeshField = NULL;
CWall*CGame::m_pWall = NULL;
CObjectBG*CGame::m_pObjectbg = NULL;
CStarter*CGame::m_pStarter = NULL;
CHorse*CGame::m_pHorse = NULL;
CGate*CGame::m_pGate = NULL;

CPlayer*CGame::m_pPlayer = NULL;
CHorse2*CGame::m_pHorse2 = NULL;
CHorse3*CGame::m_pHorse3 = NULL;
CHorse4*CGame::m_pHorse4 = NULL;
CHorse5*CGame::m_pHorse5 = NULL;
CHorse6*CGame::m_pHorse6 = NULL;
CHorse7*CGame::m_pHorse7 = NULL;
CHorse8*CGame::m_pHorse8 = NULL;
CHorse9*CGame::m_pHorse9 = NULL;
CHorse10*CGame::m_pHorse10 = NULL;
CJockey*CGame::m_pJockey = NULL;
CJockey2*CGame::m_pJockey2 = NULL;
CJockey3*CGame::m_pJockey3 = NULL;
CJockey4*CGame::m_pJockey4 = NULL;
CJockey5*CGame::m_pJockey5 = NULL;
CJockey6*CGame::m_pJockey6 = NULL;
CJockey7*CGame::m_pJockey7 = NULL;
CJockey8*CGame::m_pJockey8 = NULL;
CJockey9*CGame::m_pJockey9 = NULL;
CJockey10*CGame::m_pJockey10 = NULL;
COwner*CGame::m_pOwner = NULL;
CUnion*CGame::m_pUnion = NULL;
CScene3D*CGame::m_pScene3D = NULL;
CGauge*CGame::m_pGauge = NULL;

CGame::STATE CGame::m_State = CGame::STATE_NONE;

LPDIRECT3DTEXTURE9	CGame::m_pTexture = NULL;
LPDIRECT3DVERTEXBUFFER9 CGame::m_pVtxBuff = NULL;
int CGame::m_nTimer = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CGame::CGame()
{
	m_nIndex = 0;
	m_nCounterGameState = 0;
	m_State = STATE_NONE;
	m_Gametimmer = 0;
	m_nTimer = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CGame::~CGame()
{

}

//=============================================================================
// ロード
//=============================================================================
HRESULT CGame::Load(void)
{
	return S_OK;
}

//=============================================================================
// アンロード
//=============================================================================
void CGame::Unload(void)
{
	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();

		m_pTexture = NULL;
	}
}

//=============================================================================
// ゲームの生成
//=============================================================================
CGame *CGame::Create(void)
{
	CGame *pGame;

	pGame = new CGame;

	pGame->Init();

	return pGame;
}

//=============================================================================
// 初期化処理
//=============================================================================
void CGame::Init(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = NULL;

	pDevice = CManager::GetRenderer()->GetDevice();

	m_pCamera = new CCamera;
	m_pLight = new CLight;

	//===================================
	// 読み込み類
	//===================================

	// カメラの初期化
	m_pCamera->Init();

	// カメラを取得
	m_pCamera->SetMode(CCamera::MODE_GAME);

	// ライトの初期化
	m_pLight->Init();

	// オブジェクト背景の読み込み
	CObjectBG::Load();

	// スターターの読み込み
	CStarter::Load();

	// ゲートの読み込み
	CGate::Load();

	// 馬の読み込み
	CHorse::Load();
	// 馬の読み込み
	CHorse2::Load();
	// 馬の読み込み
	CHorse3::Load();
	// 馬の読み込み
	CHorse4::Load();
	// 馬の読み込み
	CHorse5::Load();
	// 馬の読み込み
	CHorse6::Load();
	// 馬の読み込み
	CHorse7::Load();
	// 馬の読み込み
	CHorse8::Load();
	// 馬の読み込み
	CHorse9::Load();
	// 馬の読み込み
	CHorse10::Load();
	// プレイヤーを読み込む
	CPlayer::Load();

	// ジョッキーの読み込み
	CJockey::Load();
	// ジョッキーの読み込み
	CJockey2::Load();
	// ジョッキーの読み込み
	CJockey3::Load();
	// ジョッキーの読み込み
	CJockey4::Load();
	// ジョッキーの読み込み
	CJockey5::Load();
	// ジョッキーの読み込み
	CJockey6::Load();
	// ジョッキーの読み込み
	CJockey7::Load();
	// ジョッキーの読み込み
	CJockey8::Load();
	// ジョッキーの読み込み
	CJockey9::Load();
	// ジョッキーの読み込み
	CJockey10::Load();

	// オーナーの読み込み
	COwner::Load();

	// ゲージの読み込み
	CGauge::Load();

	//===================================
	// 生成類
	//===================================

	// プレイヤーの生成
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, D3DX_PI, 0), CPlayer::JOCKEYTYPE_GAME);
	// ジョッキーの生成
	m_pJockey = CJockey::Create(D3DXVECTOR3(0, 20, 0), D3DXVECTOR3(0, D3DX_PI, 0), CJockey::JOCKEYTYPE_GAME);
	// 馬2の生成
	m_pHorse2 = CHorse2::Create(D3DXVECTOR3(50, 0, 0), D3DXVECTOR3(0, D3DX_PI, 0), CHorse2::JOCKEYTYPE_GAME);
	// ジョッキー２の生成
	m_pJockey2 = CJockey2::Create(D3DXVECTOR3(50, 20, 0),D3DXVECTOR3(0,D3DX_PI,0),CJockey2::JOCKEYTYPE_GAME);
	// 馬3の生成
	m_pHorse3 = CHorse3::Create(D3DXVECTOR3(-50, 0, 0), D3DXVECTOR3(0, D3DX_PI, 0), CHorse3::JOCKEYTYPE_GAME);
	// ジョッキー3の生成
	m_pJockey3 = CJockey3::Create(D3DXVECTOR3(-50, 20, 0), D3DXVECTOR3(0, D3DX_PI, 0), CJockey3::JOCKEYTYPE_GAME);
	// 馬4の生成
	m_pHorse4 = CHorse4::Create(D3DXVECTOR3(-100, 0, 0), D3DXVECTOR3(0, D3DX_PI, 0), CHorse4::JOCKEYTYPE_GAME);
	// ジョッキー4の生成
	m_pJockey4 = CJockey4::Create(D3DXVECTOR3(-100, 20, 0), D3DXVECTOR3(0, D3DX_PI, 0), CJockey4::JOCKEYTYPE_GAME);
	// 馬5の生成
	m_pHorse5 = CHorse5::Create(D3DXVECTOR3(-150, 0, 0), D3DXVECTOR3(0, D3DX_PI, 0), CHorse5::JOCKEYTYPE_GAME);
	// ジョッキー5の生成
	m_pJockey5 = CJockey5::Create(D3DXVECTOR3(-150, 20, 0), D3DXVECTOR3(0, D3DX_PI, 0), CJockey5::JOCKEYTYPE_GAME);
	// 馬6の生成
	m_pHorse6 = CHorse6::Create(D3DXVECTOR3(-200, 0, 0), D3DXVECTOR3(0, D3DX_PI, 0), CHorse6::JOCKEYTYPE_GAME);
	// ジョッキー6の生成
	m_pJockey6 = CJockey6::Create(D3DXVECTOR3(-200, 20, 0), D3DXVECTOR3(0, D3DX_PI, 0), CJockey6::JOCKEYTYPE_GAME);
	// 馬7の生成
	m_pHorse7 = CHorse7::Create(D3DXVECTOR3(-250, 0, 0), D3DXVECTOR3(0, D3DX_PI, 0), CHorse7::JOCKEYTYPE_GAME);
	// ジョッキー7の生成
	m_pJockey7 = CJockey7::Create(D3DXVECTOR3(-250, 20, 0), D3DXVECTOR3(0, D3DX_PI, 0), CJockey7::JOCKEYTYPE_GAME);
	// 馬8の生成
	m_pHorse8 = CHorse8::Create(D3DXVECTOR3(-300, 0, 0), D3DXVECTOR3(0, D3DX_PI, 0), CHorse8::JOCKEYTYPE_GAME);
	// ジョッキー8の生成
	m_pJockey8 = CJockey8::Create(D3DXVECTOR3(-300, 20, 0), D3DXVECTOR3(0, D3DX_PI, 0), CJockey8::JOCKEYTYPE_GAME);
	// 馬9の生成
	m_pHorse9 = CHorse9::Create(D3DXVECTOR3(-350, 0, 0), D3DXVECTOR3(0, D3DX_PI, 0), CHorse9::JOCKEYTYPE_GAME);
	// ジョッキー9の生成
	m_pJockey9 = CJockey9::Create(D3DXVECTOR3(-350, 20, 0), D3DXVECTOR3(0, D3DX_PI, 0), CJockey9::JOCKEYTYPE_GAME);
	// 馬10の生成
	m_pHorse10 = CHorse10::Create(D3DXVECTOR3(-400, 0, 0), D3DXVECTOR3(0, D3DX_PI, 0), CHorse10::JOCKEYTYPE_GAME);
	// ジョッキー10の生成
	m_pJockey10 = CJockey10::Create(D3DXVECTOR3(-400, 20, 0), D3DXVECTOR3(0, D3DX_PI, 0), CJockey10::JOCKEYTYPE_GAME);

	// ビルボードの生成
	CBillboard::Create(D3DXVECTOR3(0, 200, 50), D3DXVECTOR3(0, 0, 0));

	// メッシュフィールドの生成
	m_pMeshField = CMeshFiled::Create(D3DXVECTOR3(-300.0f, 0.0f, 1700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), X_SIZE, Z_SIZE, mPolygonX, mPolygonZ);

	// 壁の生成
	/*右*/m_pWall = CWall::Create(D3DXVECTOR3(300.0f, 100.0f, 1700.0f), D3DXVECTOR3(0.0f, 0.0f, 1.5f), X_SIZE, Y_SIZE, mPolygonX, mPolygonY);
	/*左*/m_pWall = CWall::Create(D3DXVECTOR3(-900.0f, 100.0f, 1700.0f), D3DXVECTOR3(0.0f, 0.0f, -1.5f), X_SIZE, Y_SIZE, mPolygonX, mPolygonY);
	/*奥*/m_pWall = CWall::Create(D3DXVECTOR3(-300.0f, 100.0f, 3600.0f), D3DXVECTOR3(-1.5f, 0.0f, 0.0f), 2000, 1200, mPolygonX, mPolygonY);
	/*前*/m_pWall = CWall::Create(D3DXVECTOR3(-300.0f, 100.0f, 0.0f), D3DXVECTOR3(1.5f, 0.0f, 0.0f), 2000, 1200, mPolygonX, mPolygonY);
	/*蓋*/m_pWall = CWall::Create(D3DXVECTOR3(-300.0f, 600.0f, 1700.0f), D3DXVECTOR3(0.0f, 0.0f, D3DX_PI), X_SIZE, Z_SIZE, mPolygonX, mPolygonZ);


	// オブジェクト背景の生成
	// 競馬場
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-800.0f, 0.0f, 500.0f), D3DXVECTOR3(0.0f, 30.0f, 0.0f), CObjectBG::MODELTYPE_BILL000);

	// ゴールの生成
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 3000.0f),D3DXVECTOR3(0.0f,11.0f,0.0f), CObjectBG::MODELTYPE_GOAL);

	// ゲージの生成
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, -30.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 30.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 60.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 90.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 125.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 155.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 185.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 215.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 245.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 275.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 305.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 335.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 365.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 395.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 425.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 455.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 485.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 515.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 545.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 575.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 605.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 635.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 665.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 695.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 725.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 755.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 785.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 815.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 845.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 875.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 905.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 935.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 965.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 995.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 1025.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 1055.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 1085.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 1105.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 1135.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 1165.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 1195.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 1225.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 1255.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 1285.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 1315.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 1345.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 1375.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 1405.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 1435.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 1465.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 1495.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 1525.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 1555.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 1585.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 1615.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 1645.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 1675.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 1705.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 1735.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 1765.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 1795.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 1825.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 1855.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 1885.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 1915.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 1945.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 1975.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 2005.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 2035.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 2065.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 2095.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 2125.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 2155.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 2185.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 2215.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 2245.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 2275.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 2305.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 2335.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 2365.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 2395.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 2425.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 2455.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 2485.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 2515.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 2545.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 2575.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 2605.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 2635.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 2665.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 2695.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 2725.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 2755.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 2785.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 2815.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 2845.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 2875.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 2905.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 2935.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 2965.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 2995.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 3025.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 3055.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 3085.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 3115.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 3145.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 3175.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 3205.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 3235.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 3265.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 3295.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 3295.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 3295.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 3325.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 3355.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 3385.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 3415.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 3445.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 3475.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);

	//===================反対====================================================================================================================
	// ゲージの生成
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, -30.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 30.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 60.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 90.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 125.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 155.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 185.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 215.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 245.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 275.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 305.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 335.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 365.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 395.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 425.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 455.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 485.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 515.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 545.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 575.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 605.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 635.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 665.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 695.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 725.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 755.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 785.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 815.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 845.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 875.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 905.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 935.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 965.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 995.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 1025.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 1055.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 1085.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 1105.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 1135.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 1165.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 1195.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 1225.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 1255.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 1285.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 1315.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 1345.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 1375.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 1405.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 1435.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 1465.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 1495.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 1525.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 1555.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 1585.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 1615.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 1645.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 1675.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 1705.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 1735.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 1765.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 1795.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 1825.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 1855.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 1885.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 1915.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 1945.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 1975.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 2005.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 2035.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 2065.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 2095.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 2125.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 2155.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 2185.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 2215.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 2245.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 2275.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 2305.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 2335.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 2365.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 2395.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 2425.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 2455.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 2485.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 2515.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 2545.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 2575.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 2605.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 2635.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 2665.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 2695.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 2725.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 2755.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 2785.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 2815.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 2845.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 2875.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 2905.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 2935.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 2965.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 2995.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 3025.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 3055.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 3085.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 3115.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 3145.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 3175.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 3205.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 3235.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 3265.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 3295.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 3295.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 3295.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 3325.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 3355.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 3385.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 3415.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 3445.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 3475.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);


	// スターターの生成
	//m_pStarter = CStarter::Create(D3DXVECTOR3(0, 50, 0));

	// ゲートの生成
	//CGate::Create(D3DXVECTOR3(0, 10, 0),CGate::GATE_TYPE1);
	//CGate::Create(D3DXVECTOR3(0, 10, 0), CGate::GATE_TYPE1);

	// オーナー
	m_pOwner = COwner::Create(D3DXVECTOR3(150.0f, 0.0f, 100.0f),D3DXVECTOR3(0.0f,D3DX_PI / 2,0.0f));

	// ゲージの生成
	CGauge::Create(D3DXVECTOR3(50, 80, 0), 100.0f, 100.0f);

}

//=============================================================================
// 終了処理
//=============================================================================
void CGame::Uninit(void)
{
	CPlayer::Unload();
	// オブジェクト背景の読み込み
	CObjectBG::UnLoad();
	// スターターの読み込み
	CStarter::Unload();
	// ゲートの読み込み
	CGate::Unload();
	// 馬の読み込み
	CHorse::Unload();
	// 馬2の読み込み
	CHorse2::Unload();
	// 馬3の読み込み
	CHorse3::Unload();
	// 馬4の読み込み
	CHorse4::Unload();
	// 馬5の読み込み
	CHorse5::Unload();
	// 馬6の読み込み
	CHorse6::Unload();
	// 馬7の読み込み
	CHorse7::Unload();
	// 馬8の読み込み
	CHorse8::Unload();
	// 馬9の読み込み
	CHorse9::Unload();
	// 馬10の読み込み
	CHorse10::Unload();
	// ジョッキーの読み込み
	CJockey::Unload();
	// ジョッキーの読み込み
	CJockey2::Unload();
	// ジョッキーの読み込み
	CJockey3::Unload();
	// ジョッキーの読み込み
	CJockey4::Unload();
	// ジョッキーの読み込み
	CJockey5::Unload();
	// ジョッキーの読み込み
	CJockey6::Unload();
	// ジョッキーの読み込み
	CJockey7::Unload();
	// ジョッキーの読み込み
	CJockey8::Unload();
	// ジョッキーの読み込み
	CJockey9::Unload();
	// ジョッキーの読み込み
	CJockey10::Unload();
	// オーナーの読み込み
	COwner::Unload();

	// カメラを破棄
	if (m_pCamera != NULL)
	{
		m_pCamera->Uninit();			// カメラを消す

		delete m_pCamera;
		m_pCamera = NULL;
	}

	// ライトを破棄
	if (m_pLight != NULL)
	{
		m_pLight->Uninit();				// ライトを消す

		delete m_pLight;
		m_pLight = NULL;
	}

	// プレイヤーのNULLチェック
	if (m_pPlayer != NULL)
	{
		m_pPlayer = NULL;
	}

	if (m_pObjectbg != NULL)
	{
		m_pObjectbg = NULL;
	}

	// メッシュフィールドのNULLチェック
	if (m_pMeshField != NULL)
	{
		//m_pMeshField->Uninit();
		m_pMeshField = NULL;
	}

	CScene::ReleaseAll();
}

//=============================================================================
// 更新処理
//=============================================================================
void CGame::Update(void)
{
	// キーボードを取得
	CInputKeyboard *InputKeyboard;
	InputKeyboard = CManager::GetInputKeyboard();

	// デバックを取得
	CDebugProc *m_Dubug = CRenderer::GetDebug();

	// フェードを取得
	CFade *pFade;
	pFade = CManager::GetFade();

	m_Gametimmer++;
	m_nTimer++;

	// NULLチェック
	if (m_pCamera != NULL)
	{
		m_pCamera->Update();			// カメラを更新
	}

	// NULLチェック
	if (m_pLight != NULL)
	{
		m_pLight->Update();				// ライトを更新
	}

	// デバック表示
#ifdef _DEBUG
	m_Dubug->Print("s", "Game");

#endif // DEBUG
}

//=============================================================================
// 描画処理
//=============================================================================
void CGame::Draw(void)
{
	// NULLチェック
	if (m_pCamera != NULL)
	{
		m_pCamera->SetCamera();			// カメラの設定
	}
}

//=============================================================================
// プレイヤーの取得
//=============================================================================
CPlayer *CGame::GetPlayer(void)
{
	return m_pPlayer;
}

//=============================================================================
// 敵の取得
//=============================================================================
CEnemy *CGame::GetEnemy(void)
{
	return m_pEnemy;
}

//=============================================================================
// カメラの取得
//=============================================================================
CCamera * CGame::GetCamera(void)
{
	return m_pCamera;
}

//=============================================================================
// ライトの取得
//=============================================================================
CLight * CGame::GetLight(void)
{
	return m_pLight;
}

//=============================================================================
// メッシュフィールドの取得
//=============================================================================
CMeshFiled * CGame::GetMeshFiled(void)
{
	return m_pMeshField;
}

//=============================================================================
// メッシュフィールドの取得
//=============================================================================
CWall * CGame::GetWall(void)
{
	return m_pWall;
}

//=============================================================================
// オブジェクト背景の取得
//=============================================================================
CObjectBG * CGame::GetObjectbg(void)
{
	return m_pObjectbg;
}

//=============================================================================
// スターターの取得
//=============================================================================
CStarter * CGame::GetStarter(void)
{
	return m_pStarter;
}

//=============================================================================
// 馬の取得
//=============================================================================
CHorse * CGame::GetHorse(void)
{
	return m_pHorse;
}
//=============================================================================
// 馬2の取得
//=============================================================================
CHorse2 * CGame::GetHorse2(void)
{
	return m_pHorse2;
}
//=============================================================================
// 馬3の取得
//=============================================================================
CHorse3 * CGame::GetHorse3(void)
{
	return m_pHorse3;
}
//=============================================================================
// 馬4の取得
//=============================================================================
CHorse4 * CGame::GetHorse4(void)
{
	return m_pHorse4;
}
//=============================================================================
// 馬5の取得
//=============================================================================
CHorse5 * CGame::GetHorse5(void)
{
	return m_pHorse5;
}
//=============================================================================
// 馬6の取得
//=============================================================================
CHorse6 * CGame::GetHorse6(void)
{
	return m_pHorse6;
}
//=============================================================================
// 馬7の取得
//=============================================================================
CHorse7 * CGame::GetHorse7(void)
{
	return m_pHorse7;
}
//=============================================================================
// 馬8の取得
//=============================================================================
CHorse8 * CGame::GetHorse8(void)
{
	return m_pHorse8;
}
//=============================================================================
// 馬9の取得
//=============================================================================
CHorse9 * CGame::GetHorse9(void)
{
	return m_pHorse9;
}
//=============================================================================
// 馬10の取得
//=============================================================================
CHorse10 * CGame::GetHorse10(void)
{
	return m_pHorse10;
}

//=============================================================================
// ゲートの取得
//=============================================================================
CGate * CGame::GetGate(void)
{
	return m_pGate;
}

//=============================================================================
// ジョッキー1の取得
//=============================================================================
CJockey * CGame::GetJockey(void)
{
	return m_pJockey;
}
//=============================================================================
// ジョッキー2の取得
//=============================================================================
CJockey2 * CGame::GetJockey2(void)
{
	return m_pJockey2;
}
//=============================================================================
// ジョッキー3の取得
//=============================================================================
CJockey3 * CGame::GetJockey3(void)
{
	return m_pJockey3;
}
//=============================================================================
// ジョッキー4の取得
//=============================================================================
CJockey4 * CGame::GetJockey4(void)
{
	return m_pJockey4;
}
//=============================================================================
// ジョッキー5の取得
//=============================================================================
CJockey5 * CGame::GetJockey5(void)
{
	return m_pJockey5;
}
//=============================================================================
// ジョッキー6の取得
//=============================================================================
CJockey6 * CGame::GetJockey6(void)
{
	return m_pJockey6;
}
//=============================================================================
// ジョッキー7の取得
//=============================================================================
CJockey7 * CGame::GetJocke7(void)
{
	return m_pJockey7;
}

//=============================================================================
// ジョッキー8の取得
//=============================================================================
CJockey8 * CGame::GetJocke8(void)
{
	return m_pJockey8;
}

//=============================================================================
// ジョッキー9の取得
//=============================================================================
CJockey9 * CGame::GetJockey9(void)
{
	return m_pJockey9;
}

//=============================================================================
// ジョッキー10の取得
//=============================================================================
CJockey10 * CGame::GetJockey10(void)
{
	return m_pJockey10;
}

//=============================================================================
// オーナーの取得
//=============================================================================
COwner * CGame::GetOwner(void)
{
	return m_pOwner;
}

//=============================================================================
// 合体の取得
//=============================================================================
CUnion * CGame::GetUnion(void)
{
	return m_pUnion;
}

//=============================================================================
// 3Dオブジェクトの取得
//=============================================================================
CScene3D * CGame::GetScene3D(void)
{
	return m_pScene3D;
}

//=============================================================================
// ゲージの取得
//=============================================================================
CGauge * CGame::GetGauge(void)
{
	return m_pGauge;
}

//=============================================================================
// タイム取得
//=============================================================================
int CGame::GetTime(void)
{
	return m_nTimer;
}
