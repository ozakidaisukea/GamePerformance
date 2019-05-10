//=============================================================================
//
// エフェクトの処理　[effect.cpp]
// Author : Ozaki
//
//=============================================================================
#include "effect.h"
#include "renderer.h"
#include "main.h"
#include "manager.h"
#include "scene2D.h"
#include "input.h"

//=============================================================================
// 静的メンバ変数
//=============================================================================
LPDIRECT3DTEXTURE9 CEffect::m_pTexture = NULL;
CExplosion*CEffect::m_pExplosion = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CEffect::CEffect():CScene2D(7)
{

}

//=============================================================================
// デストラクタ
//=============================================================================
CEffect::~CEffect()
{

}

//=============================================================================
// ロード
//=============================================================================
HRESULT CEffect::Load(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = NULL;

	pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\game\\effect000.jpg",
		&m_pTexture);

	return S_OK;
}

//=============================================================================
// アンロード
//=============================================================================
void CEffect::Unload(void)
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
HRESULT CEffect::Init(D3DXVECTOR3 pos, D3DXCOLOR col, float widtgh, float height)
{
	CScene2D::Init(pos, widtgh,height);
	//m_fLength = flength;
	m_widtgh = widtgh;
	m_height = height;
	m_col = col;

	SetObjtType(CScene::OBJTYPE_EFFECT);

	// エフェクトの表示時間
	m_nLife = 40;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CEffect::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CEffect::Update(void)
{
	D3DXVECTOR3 effectpos;

	effectpos = GetPosition();


	// 色
	m_col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.5f);

	// ライフ
	m_nLife -= 1;

	// 大きさ
	m_widtgh,m_height -= 1;


	LPDIRECT3DVERTEXBUFFER9 VtxBuff;

		VtxBuff = GetVtxBG();
		//ローカル変数
		VERTEX_2D*pVtx;

		//頂点バッファをロックし、頂点データのポインタの取得
		VtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//頂点カラーの設定
		pVtx[0].col = m_col;
		pVtx[1].col = m_col;
		pVtx[2].col = m_col;
		pVtx[3].col = m_col;

		//頂点バッファをアンロック
		VtxBuff->Unlock();

	SetPosition(effectpos, m_rot, m_position, m_fLength);

	// 表示時間が0になると消す
	if (m_nLife <= 0)
	{
		Uninit();
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CEffect::Draw(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = NULL;

	pDevice = CManager::GetRenderer()->GetDevice();

	// αブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	CScene2D::Draw();

	// αブレンディングを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//=============================================================================
// 弾の生成
//=============================================================================
CEffect *CEffect::Create(D3DXVECTOR3 pos, D3DXCOLOR col, float widtgh, float height)
{
	CEffect *pEffect;

	pEffect = new CEffect;

	pEffect->Init(pos,col,widtgh,height);

	// 共有テクスチャを割り当てる
	pEffect->BindTexture(m_pTexture);

	return pEffect;
}