//=============================================================================
//
// 爆発の処理 [explosion.cpp]
// Author : Ozaki
//
//=============================================================================
#include "explosion.h"
#include "player.h"
#include "renderer.h"
#include "main.h"
#include "manager.h"
#include "scene2D.h"
#include "input.h"

//=============================================================================
// 静的メンバ変数
//=============================================================================
LPDIRECT3DTEXTURE9 CExplosion::m_pTexture = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CExplosion::CExplosion():CScene2D(5)
{

}

//=============================================================================
// デストラクタ
//=============================================================================
CExplosion::~CExplosion()
{

}

//=============================================================================
// ロード
//=============================================================================
HRESULT CExplosion::Load(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = NULL;

	pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\game\\explosion001.png",
		&m_pTexture);

	return S_OK;
}

//=============================================================================
// アンロード
//=============================================================================
void CExplosion::Unload(void)
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
HRESULT CExplosion::Init(D3DXVECTOR3 pos, float widtgh, float height)
{
	CScene2D::Init(pos,widtgh,height);

	//m_flength = flength;
	m_widtgh = widtgh;
	m_height = height;

	CScene2D::SetTexture(TEX_U, TEX_V, 1, 8);

	SetObjtType(CScene::OBJTYPE_EXPLOSION);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CExplosion::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CExplosion::Update(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = NULL;

	pDevice = CManager::GetRenderer()->GetDevice();

	// 爆発のアニメーション
	m_nCounterAnim++;

	if ((m_nCounterAnim % 3)== 0)
	{
		m_nPatternAnim = (m_nPatternAnim + 1 % 8);

		CScene2D::SetTexture(TEX_U,TEX_V,m_nPatternAnim,8);

		if (m_nPatternAnim >= 7)
		{
			Uninit();
		}
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void CExplosion::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// 爆発の生成
//=============================================================================
CExplosion *CExplosion::Create(D3DXVECTOR3 pos, float widtgh, float height)
{
	CExplosion *pExplosion;

	pExplosion = new CExplosion;

	pExplosion->Init(pos,widtgh,height);

	// 共有テクスチャを割り当てる
	pExplosion->BindTexture(m_pTexture);

	return pExplosion;
}

