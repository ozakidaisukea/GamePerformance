//=============================================================================
//
// 敵の処理[enemy.cpp]
// Author : Ozaki
//
//=============================================================================
#include "enemy.h"
#include "main.h"
#include "scene.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "scene2D.h"
#include "bullet.h"
#include "life.h"
#include "score.h"
#include "explosion.h"
#include "game.h"
#include "fade.h"
#include "player.h"
#include "tutorial.h"
#include "sound.h"

//=============================================================================
// 静的メンバ変数
//=============================================================================
LPDIRECT3DTEXTURE9 CEnemy::m_pTexture[MAX_ENEMY] = {};
int				   CEnemy::m_nCounterEnemyState = NULL;
int				   CEnemy::m_enemyall = 0;
CSound			  *CEnemy::m_pSound = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CEnemy::CEnemy():CScene2D(3)
{
	m_enemyall++;
	m_CountState = 0;
	state = ENEMYSTATE_NORMAL;
}

//=============================================================================
// デストラクタ
//=============================================================================
CEnemy::~CEnemy()
{

}

//=============================================================================
// ロード
//=============================================================================
HRESULT CEnemy::Load(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = NULL;

	pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの生成[0]
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\game\\tori.png",
		&m_pTexture[0]);

	// テクスチャの生成[1]
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\game\\baiku.png",
		&m_pTexture[1]);

	// テクスチャの生成[2]
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\game\\moutaboard.png",
		&m_pTexture[2]);

	// テクスチャの生成[3]
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\game\\gyosen.png",
		&m_pTexture[3]);

	// テクスチャの生成[4]
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\game\\utyusen1.png",
		&m_pTexture[4]);

	return S_OK;
}

//=============================================================================
// アンロード
//=============================================================================
void CEnemy::Unload(void)
{
	for (int nCnt = 0; nCnt < MAX_ENEMY; nCnt++)
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
HRESULT CEnemy::Init(D3DXVECTOR3 pos, float widtgh, float height, D3DXVECTOR3 move, int life, ENEMY_TYPE type)
{

	CScene2D::Init(pos,widtgh,height);

	m_widtgh = widtgh;
	m_height = height;
	m_move = move;
	m_nLife = life;
	m_Type = type;
	m_nCounterEnemyState = 0;

	SetObjtType(CScene::OBJTYPE_ENEMY);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CEnemy::Uninit(void)
{
	m_enemyall--;
	CScene2D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CEnemy::Update(void)
{
	D3DXVECTOR3 pos;

	pos = GetPosition();

	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = NULL;

	pDevice = CManager::GetRenderer()->GetDevice();

	CInputKeyboard *InputKeyboard;
	InputKeyboard = CManager::GetInputKeyboard();

	m_bullettime++;


	if (pos.x >= 700)
	{
		// 移動量
		m_move.x -= 0.01f;

		pos += m_move;
	}

	// 弾の生成
	if (m_bullettime == 120)
	{
		D3DXVECTOR3 Playerpos = CPlayer::GetPlayerPos();
		D3DXVECTOR3	movebullet = D3DXVECTOR3(0,0,0);
		D3DXVECTOR3 Bulletpos;
		float fAngle;

		Bulletpos.x = Playerpos.x - pos.x;
		Bulletpos.y = Playerpos.y - pos.y;

		fAngle = atan2f(Bulletpos.x, Bulletpos.y);

		movebullet.x += sinf(fAngle) * MAX_BULLETSPEED;
		movebullet.y += cosf(fAngle) * MAX_BULLETSPEED;

		CBullet::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), D3DXVECTOR3(movebullet.x,movebullet.y,movebullet.z), 80.0f,80.0f, CBullet::BULLETTYPE_AMI);

		m_bullettime = 0;
	}

	switch (state)
	{
	case ENEMYSTATE_NORMAL:

		CScene2D::SetColor(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));

		m_CountState = 0;
		break;

	case ENEMYSTATE_DEATH:

		break;

	case ENEMYSTATE_DAMAGE:

		m_CountState--;

		CScene2D::SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

		if (m_CountState <= 10)
		{
			state = ENEMYSTATE_NORMAL;
		}
		break;
	}

	 //鳥の設定
	if (pos.x >= 800)
	{
		if (CEnemy::ENEMY_TORI == m_Type)
		{
			if (pos.y <= 200)
			{
				m_move.y += 0.01f;

				pos += m_move;

			}
			else if (pos.y >= 200)
			{
				m_move.y *= -0.5f;

				pos += m_move;
			}
		}
	}

	// ポジションの設定
	SetPosition(pos, m_rot, m_position, m_flength);
}

//=============================================================================
// 描画処理
//=============================================================================
void CEnemy::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// 敵の生成
//=============================================================================
CEnemy *CEnemy::Create(D3DXVECTOR3 pos, float widtgh, float height, D3DXVECTOR3 move,int life, ENEMY_TYPE type)
{
	CEnemy *pEnemy;

	pEnemy = new CEnemy;

	pEnemy->Init(pos, widtgh,height, move,life, type);

	// 共有テクスチャを割り当てる
	pEnemy->BindTexture(m_pTexture[type]);

	return pEnemy;
}

//=============================================================================
//敵のダメージ処理
//=============================================================================
void CEnemy::HitEnemy(int nDamage)
{
	m_nLife -= nDamage;

	D3DXVECTOR3 enemypos;

	enemypos = GetPosition();

	// サウンドを取得
	CSound *pSound;
	pSound = CManager::GetSound();

	pSound->PlaySound(pSound->SOUND_LABEL_SE_DAMAGE);

	state = ENEMYSTATE_DAMAGE;


	// 敵のライフが０になったら
	if (m_nLife <= 0)
	{
		m_CountState = 15;

		// 爆発の生成
		CExplosion::Create(D3DXVECTOR3(enemypos.x, enemypos.y, 0), 300.0f, 300.0f);

		m_nCounterEnemyState++;

		// モードを取得
		CManager::MODE mode;
		mode = CManager::GetMode();

		// スコアを取得
		CScore *pScore;

		switch (mode)
		{
		case CManager::MODE_TUTORIAL:

			// スコアの取得
			pScore = CTutorial::GetScore();

			pSound->PlaySound(pSound->SOUND_LABEL_SE_EXPLOSION);

			// スコア加算
			pScore->AddScore(1000);
			break;

		case CManager::MODE_GAME:

			// スコアの取得
			pScore = CGame::GetScore();

			pSound->PlaySound(pSound->SOUND_LABEL_SE_EXPLOSION);

			// スコア加算
			pScore->AddScore(1000);
			break;
		}

		if (CManager::GetMode() == CManager::MODE_GAME)
		{
			CGame *pGame = CManager::GetGame();
			if (pGame != NULL)
			{
				pGame->SetNumEnemyAll(pGame->GetNumEnemyAll() - 1);
				if (pGame->GetNumEnemyAll() <= 0)
				{
					pGame->SetState(CGame::STATE_RESULT);
				}
				else
				{
					pGame->SetEnemy();
				}
			}
		}
		Uninit();
	}
}

//// 回転
//if (m_rot > D3DX_PI)
//{
//	m_rot -= D3DX_PI * 2;
//}
//if (m_rot < -D3DX_PI)
//{
//	m_rot += D3DX_PI * 2;
//}

//// 拡大
//if (m_position > 200)
//{
//	m_Addposition *= -1;
//}
//// 縮小
//if (m_position < -200)
//{
//	m_Addposition *= -1;
//}