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
#include "bg.h"

//=============================================================================
//
//=============================================================================
bool bUse;

//=============================================================================
// コンストラクタ
//=============================================================================
CScene2D::CScene2D(int nCntPriority) : CScene(nCntPriority)
{
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
}

//=============================================================================
// デストラクタ
//=============================================================================
CScene2D::~CScene2D()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CScene2D::Init(D3DXVECTOR3 pos, float widtgh, float height)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = NULL;

	pDevice = CManager::GetRenderer()->GetDevice();

	// ポリゴンの位置を設定
	m_pos = pos;
	m_widtgh = widtgh;
	m_height = height;

	//m_Perjudgment = widtgh,height - 40.0f;

	bUse = false;

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

	// 頂点情報を設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x + sinf(-D3DX_PI * 0.75f) * m_widtgh, m_pos.y + cosf(-D3DX_PI * 0.75f) * m_height, m_pos.z);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + sinf(D3DX_PI * 0.75f) * m_widtgh, m_pos.y + cosf(D3DX_PI * 0.75f) * m_height, m_pos.z);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x + sinf(-D3DX_PI * 0.25f) * m_widtgh, m_pos.y + cosf(-D3DX_PI * 0.25f) * m_height, m_pos.z);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + sinf(D3DX_PI * 0.25f) * m_widtgh, m_pos.y + cosf(D3DX_PI * 0.25f) * m_height, m_pos.z);

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
	pVtx[0].col = D3DXCOLOR(m_col.r, m_col.g, m_col.b, m_col.a);
	pVtx[1].col = D3DXCOLOR(m_col.r, m_col.g, m_col.b, m_col.a);
	pVtx[2].col = D3DXCOLOR(m_col.r, m_col.g, m_col.b, m_col.a);
	pVtx[3].col = D3DXCOLOR(m_col.r, m_col.g, m_col.b, m_col.a);

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CScene2D::Uninit(void)
{
	// 頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		//m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CScene2D::Update(void)
{
	//// デバイスを取得
	//LPDIRECT3DDEVICE9 pDevice = NULL;

	//pDevice = CManager::GetRenderer()->GetDevice();

	////ローカル変数
	//VERTEX_2D*pVtx;

	////頂点バッファをロックし、頂点データのポインタの取得
	//m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//// 頂点情報を設定
	//pVtx[0].pos = D3DXVECTOR3(m_pos.x + sinf(-D3DX_PI * 0.75f) * (100.0f), m_pos.y + cosf(-D3DX_PI * 0.75f ) * (100.0f), m_pos.z);
	//pVtx[1].pos = D3DXVECTOR3(m_pos.x + sinf(D3DX_PI * 0.75f) * (100.0f), m_pos.y + cosf(D3DX_PI * 0.75f) * (100.0f), m_pos.z);
	//pVtx[2].pos = D3DXVECTOR3(m_pos.x + sinf(-D3DX_PI * 0.25f) * (100.0f), m_pos.y + cosf(-D3DX_PI * 0.25f) * (100.0f), m_pos.z);
	//pVtx[3].pos = D3DXVECTOR3(m_pos.x + sinf(D3DX_PI * 0.25f) * (100.0f), m_pos.y + cosf(D3DX_PI * 0.25f) * (100.0f), m_pos.z);

	////頂点バッファをアンロック
	//m_pVtxBuff->Unlock();

	//if (bUse == false)
	//{
	//	bUse = true;
	//	Release();
	//}
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
// シーン2Dの生成
//=============================================================================
CScene2D *CScene2D::Create(D3DXVECTOR3 pos, float widtgh, float height)
{
	CScene2D *pScene2D = NULL;

	pScene2D = new CScene2D(3);

	pScene2D->Init(pos, widtgh,height);

	pScene2D->m_pos = pos;


	return pScene2D;
}

//=============================================================================
// セット
//=============================================================================
void CScene2D::SetPosition(D3DXVECTOR3 pos,float rot, float position, float addposition)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = NULL;

	pDevice = CManager::GetRenderer()->GetDevice();

	//ローカル変数
	VERTEX_2D*pVtx;

	m_pos = pos;
	m_flength = addposition;

	//頂点バッファをロックし、頂点データのポインタの取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報を設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x + sinf(-D3DX_PI * 0.75f - rot) * (m_widtgh + position), m_pos.y + cosf(-D3DX_PI * 0.75f - rot) * (m_height + position), m_pos.z);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + sinf(D3DX_PI * 0.75f - rot) * (m_widtgh + position), m_pos.y + cosf(D3DX_PI * 0.75f - rot) * (m_height + position), m_pos.z);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x + sinf(-D3DX_PI * 0.25f - rot) * (m_widtgh + position), m_pos.y + cosf(-D3DX_PI * 0.25f - rot) * (m_height + position), m_pos.z);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + sinf(D3DX_PI * 0.25f - rot) * (m_widtgh + position), m_pos.y + cosf(D3DX_PI * 0.25f - rot) * (m_height + position), m_pos.z);

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();
}

//=============================================================================
// ポジションを取得
//=============================================================================
D3DXVECTOR3 CScene2D::GetPosition(void)
{
	return m_pos;
}

////=============================================================================
//// 幅を取得
////=============================================================================
//float CScene2D::GetLength(void)
//{
//	return m_Perjudgment;
//}

//=============================================================================
// 幅を取得
//=============================================================================
float CScene2D::GetWidth(void)
{
	return m_widtgh;
}

//=============================================================================
// 縦を取得
//=============================================================================
float CScene2D::GetHeigth(void)
{
	return m_height;
}

//=============================================================================
// 共有テクスチャを割り当てる
//=============================================================================
void CScene2D::BindTexture(LPDIRECT3DTEXTURE9 texture)
{
	m_pTexture = texture;
}

void CScene2D::SetTexture(float TexU, float TexV,int nPatternAnim,int MaxPattern)
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

//=============================================================================
// バーテック背景を取得
//=============================================================================
LPDIRECT3DVERTEXBUFFER9 CScene2D::GetVtxBG(void)
{
	return m_pVtxBuff;
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
