//=============================================================================
//
// ライフシーン処理2D [lifescene2D.cpp]
// Author : Ozaki
//
//=============================================================================
#include "main.h"
#include "lifescene2D.h"
#include "scene.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "bg.h"

//=============================================================================
//
//============================================================================

//=============================================================================
// コンストラクタ
//=============================================================================
CLIfeScene2D::CLIfeScene2D()
{

}

//=============================================================================
// デストラクタ
//=============================================================================
CLIfeScene2D::~CLIfeScene2D()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CLIfeScene2D::Init(D3DXVECTOR3 pos, float widtgh, float height)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = NULL;

	pDevice = CManager::GetRenderer()->GetDevice();

	// ポリゴンの位置を設定
	m_pos = pos;
	m_fwidtgh = widtgh;
	m_fheight = height;

	m_Perjudgment = widtgh,height - 40.0f;

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
	pVtx[0].pos = D3DXVECTOR3(m_pos.x + sinf(-D3DX_PI * 0.75f) * m_fwidtgh, m_pos.y + cosf(-D3DX_PI * 0.75f) * m_fheight, m_pos.z);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + sinf(D3DX_PI * 0.75f) * m_fwidtgh, m_pos.y + cosf(D3DX_PI * 0.75f) * m_fheight, m_pos.z);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x + sinf(-D3DX_PI * 0.25f) * m_fwidtgh, m_pos.y + cosf(-D3DX_PI * 0.25f) * m_fheight, m_pos.z);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + sinf(D3DX_PI * 0.25f) * m_fwidtgh, m_pos.y + cosf(D3DX_PI * 0.25f) * m_fheight, m_pos.z);

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
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CLIfeScene2D::Uninit(void)
{
	// 頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void CLIfeScene2D::Update(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void CLIfeScene2D::Draw(void)
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
CLIfeScene2D *CLIfeScene2D::Create(D3DXVECTOR3 pos, float widtgh, float height)
{
	CLIfeScene2D *pScene2D = NULL;

	pScene2D = new CLIfeScene2D;

	pScene2D->Init(pos,widtgh,height);

	pScene2D->m_pos = pos;
	pScene2D->m_fwidtgh = widtgh;
	pScene2D->m_fheight = height;

	return pScene2D;
}

//=============================================================================
// セット
//=============================================================================
void CLIfeScene2D::SetPosition(D3DXVECTOR3 pos, float rot, float position, float addposition)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = NULL;

	pDevice = CManager::GetRenderer()->GetDevice();

	//ローカル変数
	VERTEX_2D*pVtx;

	m_pos = pos;
	m_fwidtgh, m_fheight = addposition;

	//頂点バッファをロックし、頂点データのポインタの取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報を設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x + sinf(-D3DX_PI * 0.75f - rot) * (m_fwidtgh + position), m_pos.y + cosf(-D3DX_PI * 0.75f - rot) * (m_fheight + position), m_pos.z);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + sinf(D3DX_PI * 0.75f - rot) * (m_fwidtgh + position), m_pos.y + cosf(D3DX_PI * 0.75f - rot) * (m_fheight + position), m_pos.z);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x + sinf(-D3DX_PI * 0.25f - rot) * (m_fwidtgh + position), m_pos.y + cosf(-D3DX_PI * 0.25f - rot) * (m_fheight + position), m_pos.z);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + sinf(D3DX_PI * 0.25f - rot) * (m_fwidtgh + position), m_pos.y + cosf(D3DX_PI * 0.25f - rot) * (m_fheight + position), m_pos.z);

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();

	//if (bUse == false)
	//{
	//	bUse = true;
	//	Release();
	//}
}

//=============================================================================
// ポジションを取得
//=============================================================================
D3DXVECTOR3 CLIfeScene2D::GetPosition(void)
{
	return m_pos;
}

//=============================================================================
// 幅を取得
//=============================================================================
float CLIfeScene2D::GetLength(void)
{
	return m_Perjudgment;
}


//=============================================================================
// 共有テクスチャを割り当てる
//=============================================================================
void CLIfeScene2D::BindTexture(LPDIRECT3DTEXTURE9 texture)
{
	m_pTexture = texture;
}

void CLIfeScene2D::SetTexture(float TexU, float TexV, int nPatternAnim, int MaxPattern)
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
LPDIRECT3DVERTEXBUFFER9 CLIfeScene2D::GetVtxBG(void)
{
	return m_pVtxBuff;
}