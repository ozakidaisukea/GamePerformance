//=============================================================================
//
// ライフ処理 [life.cpp]
// Author : Ozaki
//
//=============================================================================
#include "life.h"
#include "renderer.h"
#include "manager.h"
#include "scene.h"
#include "scene2D.h"
#include "lifescene2D.h"
#include "player.h"

//=============================================================================
// 静的メンバ変数
//=============================================================================
LPDIRECT3DTEXTURE9 CLife::m_pTexture = NULL;

//=============================================================================
// ロード
//=============================================================================
HRESULT CLife::Load(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = NULL;

	pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\game\\fishlife.png",
		&m_pTexture);

	return S_OK;
}

//=============================================================================
// アンロード
//=============================================================================
void CLife::Unload(void)
{
		// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();

		m_pTexture = NULL;
	}
}

//=============================================================================
// コンストラクタ
//=============================================================================
CLife::CLife()
{

}

//=============================================================================
// デストラクタ
//=============================================================================
CLife::~CLife()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CLife::Init(D3DXVECTOR3 pos, float widtgh, float height)
{
	SetObjtType(CScene2D::OBJTYPE_LIFE);

	m_nLife = MAX_LIFE;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CLife::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_LIFE; nCnt++)
	{
		if (m_apScene2D[nCnt] != NULL)
		{
			m_apScene2D[nCnt]->Uninit();

			delete m_apScene2D[nCnt];
			m_apScene2D[nCnt] = NULL;
		}
	}
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CLife::Update(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void CLife::Draw(void)
{
	for (int nCnt = 0; nCnt < m_nLife; nCnt++)
	{
		m_apScene2D[nCnt]->Draw();
	}
}

//=============================================================================
// ライフを減らす処理
//=============================================================================
void CLife::CutLife(int nLife)
{
	if (CPlayer::GetState() != CPlayer::PLAYERSTATE_ULTIMATE)
	{
		m_nLife -= nLife;
	}
}


//=============================================================================
// ライフの生成
//=============================================================================
CLife *CLife::Create(D3DXVECTOR3 pos, float widtgh, float height)
{
	CLife *pLife;

	pLife = new CLife;

	for (int nCnt = 0; nCnt < MAX_LIFE; nCnt++)
	{
		pLife->m_apScene2D[nCnt] = new CLIfeScene2D;

		pLife->m_apScene2D[nCnt]->BindTexture(m_pTexture);

		pLife->m_apScene2D[nCnt]->Init(D3DXVECTOR3(pos.x + (50 * nCnt), pos.y, pos.z), widtgh,height);
	}
	pLife->Init(pos, widtgh,height);

	return pLife;
}

//=============================================================================
// ライフを取得
//=============================================================================
int CLife::GetLife(int nLife)
{
	return m_nLife;
}

