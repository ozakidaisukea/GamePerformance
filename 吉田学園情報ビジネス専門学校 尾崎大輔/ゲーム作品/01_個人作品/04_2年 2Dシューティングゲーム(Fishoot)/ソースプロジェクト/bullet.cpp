//=============================================================================
//
// 弾の処理　[bullet.cpp]
// Author : Ozaki
//
//=============================================================================
#include "bullet.h"
#include "player.h"
#include "renderer.h"
#include "main.h"
#include "manager.h"
#include "scene2D.h"
#include "input.h"
#include "explosion.h"
#include "enemy.h"
#include "score.h"
#include "effect.h"
#include "life.h"
#include "game.h"
#include "fade.h"
#include "gameover.h"
#include "tutorial.h"
#include "sound.h"
#include "logosyake.h"

//=============================================================================
// 静的メンバ変数
//=============================================================================
LPDIRECT3DTEXTURE9 CBullet::m_pTexture[MAX_TEXBULLET] = {};
CExplosion*CBullet::m_pExplosion = NULL;
CScore*CBullet::m_pScore = NULL;
//=============================================================================
// コンストラクタ
//=============================================================================
CBullet::CBullet():CScene2D(6)
{
	m_CountState = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CBullet::~CBullet()
{

}

//=============================================================================
// 読み込み
//=============================================================================
HRESULT CBullet::Load(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = NULL;

	pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの生成 [0]
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\game\\ikura.png",
		&m_pTexture[0]);

	// テクスチャの生成 [1]
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\game\\ami.png",
		&m_pTexture[1]);

	// テクスチャの生成 [2]
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\game\\mori.png",
		&m_pTexture[2]);

	// テクスチャの生成 [3]
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\game\\turizao.png",
		&m_pTexture[3]);

	return S_OK;
}

//=============================================================================
// 開放
//=============================================================================
void CBullet::Unload(void)
{
	for (int nCnt = 0; nCnt < MAX_TEXBULLET; nCnt++)
	{
		// テクスチャの破棄
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();

			m_pTexture[nCnt] = NULL;
		}
	}
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CBullet::Init(D3DXVECTOR3 pos,D3DXVECTOR3 move, float widtgh, float height, BULLETTYPE type)
{
	CScene2D::Init(pos,widtgh,height);
	m_move = move;
	m_widtgh = widtgh;
	m_height = height;

	SetObjtType(CScene::OBJTYPE_BULLET);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CBullet::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CBullet::Update(void)
{

	D3DXVECTOR3 bulletpos;

	bulletpos = GetPosition();

	bulletpos.x += m_move.x;

	// 移動量
	m_move.y += 0.1f;

	bulletpos.y += m_move.y;

	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();

	// ポジションの設定
	SetPosition(bulletpos, m_rot, m_position, m_fLength);

	// 弾の範囲
	if (bulletpos.x > SCREEN_WIDTH)
	{
		Uninit();
	}

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
				if (objttpe == CScene::OBJTYPE_ENEMY && m_type == BULLETTYPE_PLAYER)
				{
					// エフェクトの生成
					CEffect::Create(D3DXVECTOR3(bulletpos.x, bulletpos.y, bulletpos.z), D3DXCOLOR(1.0f, 0.0f, 1.0f, 0.5f), 50.0f, 20.0f);

					// 敵のposを取得
					D3DXVECTOR3 enemypos;

					enemypos = pScene->GetPosition();

					// スコアを取得
					CScore *pScore;

					//=========================================================================
					// プレイヤーの弾と敵の当たり判定
					//=========================================================================
					if ((enemypos.x) - pScene->GetWidth() < bulletpos.x && (enemypos.x) + pScene->GetWidth() > bulletpos.x &&
						(enemypos.y) - pScene->GetHeigth() < bulletpos.y && (enemypos.y) + pScene->GetHeigth() > bulletpos.y)
					{
						// モードを取得
						CManager::MODE mode;
						mode = CManager::GetMode();

						switch (mode)
						{
							//=====================================================
							// チュートリアル
							//=====================================================
						case CManager::MODE_TUTORIAL:

							// 爆発の生成
							//CExplosion::Create(D3DXVECTOR3(bulletpos.x, bulletpos.y, 0), 150.0f, 150.0f);

							// 敵を取得
							CEnemy *pEnemy;
							pEnemy = CTutorial::GetEnemy();

							CBullet::Uninit();

							if (pEnemy != NULL && pEnemy->state == CEnemy::ENEMYSTATE_NORMAL)
							{
								// 敵へのダメージ量
								pEnemy->HitEnemy(1);

								// スコアの取得
								pScore = CTutorial::GetScore();

								// スコアの加算
								pScore->AddScore(100);

								break;
							}

							break;

							//=====================================================
							// ゲーム
							//=====================================================
						case CManager::MODE_GAME:

							// 敵を取得
							CEnemy *ppEnemy;

							CBullet::Uninit();

							for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
							{
								ppEnemy = CGame::GetEnemy(nCntEnemy);

								if (ppEnemy != NULL && ppEnemy->state == CEnemy::ENEMYSTATE_NORMAL)
								{
									// 敵へのダメージ量
									ppEnemy->HitEnemy(1);

									// ゲームのスコアを取得
									pScore = CGame::GetScore();

									// スコアの加算
									pScore->AddScore(100);

									break;
								}

							}
							break;
							break;
						}
					}
				}

				//=========================================================================
				// 敵の弾とプレイヤーとの当たり判定
				//=========================================================================
				if (objttpe == CScene::OBJTYPE_PLAYER && m_type == BULLETTYPE_AMI)
				{
					// プレイヤーのposを取得
					D3DXVECTOR3 playerpos;

					playerpos = pScene->GetPosition();

					// 敵の弾とプレイヤーとの当たり判定
					if ((playerpos.x) - pScene->GetWidth() + 50.0f < bulletpos.x && (playerpos.x) + pScene->GetWidth() - 50.0f > bulletpos.x &&
						(playerpos.y) - pScene->GetHeigth() + 50.0f < bulletpos.y && (playerpos.y) + pScene->GetHeigth() - 50.0f > bulletpos.y)
					{
						// モードを取得
						CManager::MODE mode;
						mode = CManager::GetMode();

						// サウンドを取得
						CSound *pSound;
						pSound = CManager::GetSound();

						pSound->PlaySound(pSound->SOUND_LABEL_SE_DAMAGE);

						m_CountState--;

						CPlayer::PLAYERSTATE_DAMAGE;

						CScene2D::SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

						if (m_CountState <= 10)
						{
							CPlayer::PLAYERSTATE_NORMAL;
						}

						switch (mode)
						{
							//=====================================================
							// チュートリアル
							//=====================================================
						case CManager::MODE_TUTORIAL:

							// ライフを取得
							CLife *ppLife;
							ppLife = CTutorial::GetLife();

							// ライフを減らす
							ppLife->CutLife(1);

							// ライフが０になったら
							if (ppLife->m_nLife <= 0)
							{
								// シャケ死亡画像 生成
								CLogosyake::Create(D3DXVECTOR3(bulletpos.x, bulletpos.y, 0), 100.0f, 150.0f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), CLogosyake::SYAKE_DEATH);

								// プレイヤーの取得
								CPlayer *pPlayer;
								pPlayer = CTutorial::GetPlayer();

								pPlayer->Uninit();

								// フェードを取得
								CFade *pFade;
								pFade = CManager::GetFade();

								if (pFade->GetFade() == CFade::FADE_NONE)
								{
									pFade->SetFade(CManager::MODE_TUTORIAL);
								}
							}
							break;

							//=====================================================
							// ゲームでの処理
							//=====================================================
						case CManager::MODE_GAME:

							// ライフを取得
							CLife *pLife = NULL;
							pLife = CGame::GetLife();

							// ライフを減らす
							pLife->CutLife(1);

							// ライフが０になったら
							if (pLife->m_nLife <= 0)
							{
								// シャケ死亡画像 生成
								CLogosyake::Create(D3DXVECTOR3(bulletpos.x, bulletpos.y, 0), 100.0f, 150.0f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), CLogosyake::SYAKE_DEATH);

								// プレイヤーの取得
								CPlayer *pPlayer;
								pPlayer = CGame::GetPlayer();

								pPlayer->Uninit();

								// フェードを取得
								CFade *pFade;
								pFade = CManager::GetFade();

								if (pFade->GetFade() == CFade::FADE_NONE)
								{
									CGame::SetState(CGame::STATE_GAMEOVER);
								}
							}
							break;
						}
						Uninit();
					}
				}
			}
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CBullet::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// 弾の生成
//=============================================================================
CBullet *CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float widtgh, float height, BULLETTYPE type)
{
	CBullet *pBullet;

	pBullet = new CBullet;

	pBullet->Init(pos,move,widtgh,height,type);

	pBullet->m_type = type;

	// 共有テクスチャを割り当てる
	pBullet->BindTexture(m_pTexture[type]);

	return pBullet;
}