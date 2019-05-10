//=============================================================================
//
// シーン処理2D [scene2D.cpp]
// Author : Ozaki
//
//=============================================================================
#include "main.h"
#include "scene2D.h"
#include "scene.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "debugproc.h"

//=============================================================================
// 静的メンバ-変数宣言
//=============================================================================

//=============================================================================
// コンストラクタ
//=============================================================================
CScene2D::CScene2D(int nPriority, OBJTYPE objtype) :CScene(3, CScene::OBJTYPE_2D)
{
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f);
	m_pos = D3DXVECTOR3(0, 0, 0);
	m_width = 0.0f;
	m_height = 0.0f;
	m_pTexture = NULL;
	m_pVtxBuff = NULL;
}

//=============================================================================
// デストラクタ
//=============================================================================
CScene2D::~CScene2D()
{

}

//=============================================================================
// シーン2Dの生成
//=============================================================================
CScene2D *CScene2D::Create(D3DXVECTOR3 pos, float width, float height)
{
	CScene2D *pScene2D;

	pScene2D = new CScene2D(4);

	pScene2D->Init();

	pScene2D->m_pos = pos;
	pScene2D->m_width = width;
	pScene2D->m_height = height;

	return pScene2D;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CScene2D::Init(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = NULL;

	pDevice = CManager::GetRenderer()->GetDevice();

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VRETEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//ローカル変数
	VERTEX_2D*pVtx;

	//頂点バッファをロックし、頂点データのポインタの取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	// 頂点情報を設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x + sinf(-D3DX_PI * 0.75f) * m_width, m_pos.y + cosf(-D3DX_PI * 0.75f) * m_height, m_pos.z);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + sinf(D3DX_PI * 0.75f) * m_width, m_pos.y + cosf(D3DX_PI * 0.75f) * m_height, m_pos.z);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x + sinf(-D3DX_PI * 0.25f) * m_width, m_pos.y + cosf(-D3DX_PI * 0.25f) * m_height, m_pos.z);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + sinf(D3DX_PI * 0.25f) * m_width, m_pos.y + cosf(D3DX_PI * 0.25f) * m_height, m_pos.z);

	//テクスチャの設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(255, 255, 255, 255);
	pVtx[1].col = D3DXCOLOR(255, 255, 255, 255);
	pVtx[2].col = D3DXCOLOR(255, 255, 255, 255);
	pVtx[3].col = D3DXCOLOR(255, 255, 255, 255);

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();

	SetObjtType(CScene::OBJTYPE_2D);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CScene2D::Uninit(void)
{
	// テクスチャの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CScene2D::Update(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void CScene2D::Draw(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = NULL;

	pDevice = CManager::GetRenderer()->GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VRETEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);
}

//=============================================================================
// バーテック背景を取得
//=============================================================================
LPDIRECT3DVERTEXBUFFER9 CScene2D::GetVtxBG(void)
{
	return m_pVtxBuff;
}

//=============================================================================
// 位置を取得
//=============================================================================
D3DXVECTOR3 CScene2D::GetPos(void)
{
	return m_pos;
}

//=============================================================================
// ポジションの設定
//=============================================================================
void CScene2D::SetPosition(D3DXVECTOR3 pos, float frot, float position, float addposition)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = NULL;

	pDevice = CManager::GetRenderer()->GetDevice();

	//ローカル変数
	VERTEX_2D*pVtx;

	m_pos = pos;
	m_flength = addposition;

	if (m_pVtxBuff != NULL)
	{
		//頂点バッファをロックし、頂点データのポインタの取得
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点情報を設定
		pVtx[0].pos = D3DXVECTOR3(m_pos.x + sinf(-D3DX_PI * 0.75f - frot) * (m_width + position), m_pos.y + cosf(-D3DX_PI * 0.75f - frot) * (m_height + position), m_pos.z);
		pVtx[1].pos = D3DXVECTOR3(m_pos.x + sinf(D3DX_PI * 0.75f - frot) * (m_width + position), m_pos.y + cosf(D3DX_PI * 0.75f - frot) * (m_height + position), m_pos.z);
		pVtx[2].pos = D3DXVECTOR3(m_pos.x + sinf(-D3DX_PI * 0.25f - frot) * (m_width + position), m_pos.y + cosf(-D3DX_PI * 0.25f - frot) * (m_height + position), m_pos.z);
		pVtx[3].pos = D3DXVECTOR3(m_pos.x + sinf(D3DX_PI * 0.25f - frot) * (m_width + position), m_pos.y + cosf(D3DX_PI * 0.25f - frot) * (m_height + position), m_pos.z);

		//頂点バッファをアンロック
		m_pVtxBuff->Unlock();
	}

}

//=============================================================================
// 横を取得
//=============================================================================
void CScene2D::SetWidth(float width)
{
	m_width = width;
}

//=============================================================================
// 縦を取得
//=============================================================================
void CScene2D::Setheight(float heidht)
{
	m_height = heidht;
}

//=============================================================================
// カラーを取得
//=============================================================================
void CScene2D::SetColor(D3DXCOLOR col)
{
	m_col = col;

	//ローカル変数
	VERTEX_2D*pVtx;

	//頂点バッファをロックし、頂点データのポインタの取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(m_col.r, m_col.g, m_col.b, m_col.a);
	pVtx[1].col = D3DXCOLOR(m_col.r, m_col.g, m_col.b, m_col.a);
	pVtx[2].col = D3DXCOLOR(m_col.r, m_col.g, m_col.b, m_col.a);
	pVtx[3].col = D3DXCOLOR(m_col.r, m_col.g, m_col.b, m_col.a);

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();
}

//=============================================================================
// 共有テクスチャを割り当てる
//=============================================================================
void CScene2D::BindTexture(LPDIRECT3DTEXTURE9 texture)
{
	m_pTexture = texture;
}

//=============================================================================
// テクスチャを取得
//=============================================================================
LPDIRECT3DTEXTURE9 CScene2D::GetTexture(void)
{
	return m_pTexture;
}

//=============================================================================
// テクスチャの設定
//=============================================================================
void CScene2D::SetTexture(float TexU, float TexV, int nPatternAnim, int MaxPattern)
{
	float fTexU = 1 / TexU;
	float fTexV = 1 / TexV;

	//ローカル変数
	VERTEX_2D*pVtx;

	//頂点バッファをロックし、頂点データのポインタの取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャの設定
	pVtx[0].tex.x = (0.0f + (fTexU * (nPatternAnim % MaxPattern)));
	pVtx[0].tex.y = (0.0f + fTexV);

	pVtx[1].tex.x = (fTexU + (fTexU * (nPatternAnim % MaxPattern)));
	pVtx[1].tex.y = (fTexU + fTexV);

	pVtx[2].tex.x = (0.0f + (fTexU * (nPatternAnim % MaxPattern)));
	pVtx[2].tex.y = (fTexV + fTexV);

	pVtx[3].tex.x = (fTexU + (fTexU * (nPatternAnim % MaxPattern)));
	pVtx[3].tex.y = (fTexV + fTexV);

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();
}