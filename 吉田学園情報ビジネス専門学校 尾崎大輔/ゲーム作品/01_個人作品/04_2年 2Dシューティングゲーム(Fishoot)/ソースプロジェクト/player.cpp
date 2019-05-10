//=============================================================================
//
// プレイヤー [player.cpp]
// Author : Ozaki
//
//=============================================================================
#include "player.h"
#include "main.h"
#include "scene.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "scene2D.h"
#include "bullet.h"
#include "effect.h"
#include "enemy.h"
#include "game.h"
#include "gauge.h"
#include "tutorial.h"
#include "explosion.h"
#include "sound.h"
#include "joypad.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define PLAYER_SPEED	(3.5f)

//=============================================================================
// 静的メンバ変数
//=============================================================================
LPDIRECT3DTEXTURE9 CPlayer::m_pTexture = NULL;
D3DXVECTOR3		   CPlayer::m_pos = D3DXVECTOR3(0,0,0);
CSound*CPlayer::m_pSound = NULL;						// サウンド
CPlayer::PLAYERSTATE CPlayer::state = {};
CBullet*CPlayer::m_pBullet = NULL;
//=============================================================================
// コンストラクタ
//=============================================================================
CPlayer::CPlayer():CScene2D(2)
{
	m_effecttimer = 0;
	m_bullettime = 0;
	m_nLife = 0;
	state = PLAYERSTATE_NORMAL;
	m_posold = D3DXVECTOR3(0, 0, 0);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pBullet = 0;
	m_ultimatetimer = 0;
	m_CountState = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CPlayer::~CPlayer()
{

}

//=============================================================================
// ロード
//=============================================================================
HRESULT CPlayer::Load(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = NULL;

	pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\game\\syake.png",
		&m_pTexture);

	return S_OK;
}

//=============================================================================
// アンロード
//=============================================================================
void CPlayer::Unload(void)
{
	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();

		m_pTexture = NULL;
	}
}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CPlayer::Init(D3DXVECTOR3 pos, float widtgh, float height)
{
	CScene2D::Init(pos,widtgh,height);

	m_widtgh = widtgh;

	m_height = height;

	SetObjtType(CScene::OBJTYPE_PLAYER);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CPlayer::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CPlayer::Update(void)
{
	D3DXVECTOR3 posold;
	D3DXVECTOR3 Enemypos[MAX_ENEMY] = {};
	D3DXVECTOR3	moveplayer = D3DXVECTOR3(0, 0, 0);
	D3DXVECTOR3 move = m_move;
	D3DXVECTOR3 TargetPos;
	D3DXVECTOR3 lengthpos;
	int			nCntEnemy = 0;
	float fAngle;

	m_pos = GetPosition();
	m_bullettime++;
	m_effecttimer++;

	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = NULL;

	pDevice = CManager::GetRenderer()->GetDevice();

	// キーボードを取得
	CInputKeyboard *InputKeyboard;
	InputKeyboard = CManager::GetInputKeyboard();

	// キーボードを取得
	CInputjoypad *InputJoypad;
	InputJoypad = CManager::GetInputJoypad();

	// サウンドを取得
	CSound *pSound;
	pSound = CManager::GetSound();

	//====================================================
	// キーボード
	//====================================================

	// 上移動[Wキー↑]
	if (InputKeyboard->GetPress(DIK_W) == true)
	{
		m_pos.y -= PLAYER_SPEED;
	}

	// 下移動[Sキー↓]
	if (InputKeyboard->GetPress(DIK_S) == true)
	{
		m_pos.y += PLAYER_SPEED;
	}

	// 左移動[Aキー →]
	if (InputKeyboard->GetPress(DIK_A) == true)
	{
		m_pos.x -= PLAYER_SPEED;
	}

	// 右移動[Dキー ←]
	if (InputKeyboard->GetPress(DIK_D) == true)
	{
		m_pos.x += PLAYER_SPEED;
	}

	//======================================================================
	// 左スティック
	//======================================================================

	// 上移動
	if (InputJoypad->GetPress(CInputjoypad::DIJS_STICK_LEFT_UP) == true)
	{
		m_pos.y -= PLAYER_SPEED;
	}

	// 下移動
	if (InputJoypad->GetPress(CInputjoypad::DIJS_STICK_LEFT_DOWN) == true)
	{
		m_pos.y += PLAYER_SPEED;

	}

	// 左移動
	if (InputJoypad->GetPress(CInputjoypad::DIJS_STICK_LEFT_LEFT) == true)
	{
		m_pos.x -= PLAYER_SPEED;
	}

	// 右移動
	if (InputJoypad->GetPress(CInputjoypad::DIJS_STICK_LEFT_RIGTH) == true)
	{
		m_pos.x += PLAYER_SPEED;

	}

	//======================================================================
	// 十字キー
	//======================================================================

	if (InputJoypad->GetPress(CInputjoypad::DIJS_STICK_POV_UP) == true || InputJoypad->GetPress(CInputjoypad::DIJS_STICK_POV_DOWN) == true
		|| InputJoypad->GetPress(CInputjoypad::DIJS_STICK_POV_LEFT) == true || InputJoypad->GetPress(CInputjoypad::DIJS_STICK_POV_RIGTH) == true)
	{
		m_pos.x += sinf(InputJoypad->GetRadiom()) * PLAYER_SPEED;
		m_pos.y -= cosf(InputJoypad->GetRadiom()) * PLAYER_SPEED;
	}

	// 弾[SPACEキー]
	if (InputKeyboard->GetTrigger(DIK_SPACE) == true || InputJoypad->GetTrigger(CInputjoypad::DIJS_BOTTON_A) == true
		|| InputJoypad->GetTrigger(CInputjoypad::DIJS_BOTTON_RT) == true)
	{
		if (m_bool == false)
		{
			// 弾の生成
			CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z), D3DXVECTOR3(PLAYER_SPEED, -10.0f, move.z), 50.0f, 50.0f, CBullet::BULLETTYPE_PLAYER);

			pSound->PlaySound(pSound->SOUND_LABEL_SE_SHOT);

			m_bool = true;
		}
	}

	if (m_bool == true)
	{
		m_bullettime++;
		if (m_bullettime >= 120)
		{
			m_bool = false;

			pSound->StopSound(pSound->SOUND_LABEL_SE_SHOT);
			m_bullettime = 0;
		}
	}

	if (CGauge::m_fGauge >= 250.0f)
	{
		 // 必殺技
		if (InputKeyboard->GetPress(DIK_Q) == true && InputKeyboard->GetPress(DIK_E) == true ||
			InputJoypad->GetPress(CInputjoypad::DIJS_BOTTON_LB) == true && InputJoypad->GetPress(CInputjoypad::DIJS_BOTTON_RB) == true)
		{
			// プレイヤーが必殺技状
			state = PLAYERSTATE_ULTIMATE;

			pSound->PlaySound(pSound->SOUND_LABEL_SE_SUPERDRY);

			CGauge::AddGauge(-250.0f);
		}
	}

	switch (state)
	{

		// プレイヤーが必殺技を打つ
	case PLAYERSTATE_ULTIMATE:

		// エフェクトの生成
		CEffect::Create(D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), 100.0f, 100.0f);

		// オブジェクトタイプを取得
		for (int nCntPriority = 0; nCntPriority < MAX_PRIORITY1; nCntPriority++)
		{
			for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
			{
				CScene2D *pScene;
				pScene = (CScene2D*)CScene::GetSCene(nCntScene, nCntPriority);

				if (pScene != NULL)
				{
					CScene::OBJTYPE objttpe;

					objttpe = pScene->GetObjtType();

					// 敵の当たり判定
					if (objttpe == CScene::OBJTYPE_ENEMY)
					{
						Enemypos[0] = pScene->GetPosition();
						// プレイヤー位置と敵の位置の当たり判定
						if ((Enemypos[0].x) - pScene->GetWidth() < m_pos.x && (Enemypos[0].x) + pScene->GetWidth() > m_pos.x &&
							(Enemypos[0].y) - pScene->GetHeigth() < m_pos.y && (Enemypos[0].y) + pScene->GetHeigth() > m_pos.y)
						{
							// モードを取得
							CManager::MODE mode;
							mode = CManager::GetMode();

							switch (mode)
							{

								//======================
								// チュートリアル
								//======================
							case CManager::MODE_TUTORIAL:

								// 敵を取得
								CEnemy *ppEnemy;
								ppEnemy = CTutorial::GetEnemy();

								if (ppEnemy != NULL)
								{
									// 敵へのダメージ
									ppEnemy->HitEnemy(20);

									// プレイヤーを元にいた位置に戻す
									m_pos = D3DXVECTOR3(300, 600, 0);

									state = PLAYERSTATE_NORMAL;

									pSound->StopSound(pSound->SOUND_LABEL_SE_SUPERDRY);

								}
								break;

								//======================
								// ゲーム
								//======================
							case CManager::MODE_GAME:

								// 敵を取得
								CEnemy *pEnemy;
								pEnemy = CGame::GetEnemy(CManager::GetGame()->GetNumEnemy());

								if (pEnemy != NULL)
								{
									// 敵へのダメージ
									pEnemy->HitEnemy(20);

									// プレイヤーを元にいた位置に戻す
									m_pos = D3DXVECTOR3(300, 600, 0);

									state = PLAYERSTATE_NORMAL;

									pSound->StopSound(pSound->SOUND_LABEL_SE_SUPERDRY);
									break;
								}
							}
							m_bullettime = 0;
						}
					}
				}
			}
		}

		// 自分の目的地を敵の目的地に移行
		TargetPos.x = Enemypos[0].x - m_pos.x;
		TargetPos.y = Enemypos[0].y - m_pos.y;

		fAngle = atan2f(TargetPos.x, TargetPos.y);

		moveplayer.x += sinf(fAngle) * 15;
		moveplayer.y += cosf(fAngle) * 15;

		m_pos.x += moveplayer.x;
		m_pos.y += moveplayer.y;

		// エフェクトの時間
		if (m_effecttimer == 60)
		{
			// 普通時になる
			state = PLAYERSTATE_NORMAL;

			// プレイヤーを元にいた位置に戻す
			m_pos = m_posold;

			m_effecttimer = 0;
		}
		break;

		// プレイヤーが通常時
	case PLAYERSTATE_NORMAL:

		// プレイヤー位置
		m_posold = m_pos;

		CScene2D::SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		m_CountState = 0;

		// プレイヤーの移動範
		if (m_pos.x <= 160)
		{
			// 左
			m_pos.x = 160;
		}

		else if (m_pos.x >= 1230)
		{
			// 右
			m_pos.x = 1230;
		}

		// 縦の制限
		if (m_pos.y >= 700)
		{
			m_pos.y = 700;
		}
		else if (m_pos.y <= 450)
		{
			m_pos.y = 450;
		}
		break;

		// プレイヤーのダメージ状態
	case PLAYERSTATE_DAMAGE:

		m_CountState--;

		CScene2D::SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

		if (m_CountState <= 10)
		{
			state = PLAYERSTATE_NORMAL;
		}
		break;

	}
	SetPosition(m_pos, m_rot, m_position, m_flength);
}

//=============================================================================
// 描画処理
//=============================================================================
void CPlayer::Draw(void)
{
	CScene2D::Draw();
}


//=============================================================================
// プレイヤーのステートを取得
//=============================================================================
CPlayer::PLAYERSTATE CPlayer::GetState(void)
{
	return state;
}


//=============================================================================
// プレイヤーの位置を取得
//=============================================================================
D3DXVECTOR3 CPlayer::GetPlayerPos(void)
{
	return m_pos;
}

//=============================================================================
// プレイヤーの生成
//=============================================================================
CPlayer *CPlayer::Create(D3DXVECTOR3 pos, float widtgh, float height)
{
	CPlayer *pPlayer;

	pPlayer = new CPlayer;

	pPlayer->Init(pos,widtgh,height);

	pPlayer->m_widtgh = widtgh;

	pPlayer->m_height = height;

	// 共有テクスチャを割り当てる
	pPlayer->BindTexture(m_pTexture);

	return pPlayer;
}