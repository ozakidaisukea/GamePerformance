//=============================================================================
//
// ビルボード処理 [billboard.cpp]
// Author : Ozaki
//
//=============================================================================
#include "main.h"
#include "billboard.h"
#include "scene.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "debugproc.h"
#include "player.h"

//=============================================================================
// 静的メンバ-変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9 CBillboard::m_pTexture = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CBillboard::CBillboard(int nCntPriority, OBJTYPE objtype) :CScene(4, CScene::OBJTYPE_BILLBOARD)
{
	// ポリゴンの位置を設定
	m_pos = D3DXVECTOR3(0, 0, 0.0f);
}

//=============================================================================
// デストラクタ
//=============================================================================
CBillboard::~CBillboard()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CBillboard::Init(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = NULL;

	pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\game\\name.png",
		&m_pTexture);

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VRETEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//ローカル変数 頂点情報のポインタ
	VERTEX_3D*pVtx;

	//頂点バッファをロックし、頂点データのポインタの取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-10.0, 20.0, -0);
	pVtx[1].pos = D3DXVECTOR3(50.0, 20.0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-10.0, -0, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(50.0, -0, 0.0f);

	// 法線情報
	pVtx[0].nor = D3DXVECTOR3(0, 0, -1);
	pVtx[1].nor = D3DXVECTOR3(0, 0, -1);
	pVtx[2].nor = D3DXVECTOR3(0, 0, -1);
	pVtx[3].nor = D3DXVECTOR3(0, 0, -1);

	// 頂点カラー
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();

	SetObjtType(CScene::OBJTYPE_3D);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CBillboard::Uninit(void)
{
	// 頂点バッファの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}

	// テクスチャの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	CScene::Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CBillboard::Update(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = NULL;

	// マネージャーを取得
	pDevice = CManager::GetRenderer()->GetDevice();

	// キーボードを取得
	CInputKeyboard *InputKeyboard;
	InputKeyboard = CManager::GetInputKeyboard();

	m_pos = CPlayer::Getpos();
	m_pos.y += 50.0f;

	CDebugProc *m_Dubug = CRenderer::GetDebug();

#ifdef _DEBUG
	m_Dubug->Print("ssfsfsf", "[ ビルボード 位置 ] ", "X", m_pos.x, "Y", m_pos.y, "Z", m_pos.z);
#endif
}

//=============================================================================
// 描画処理
//=============================================================================
void CBillboard::Draw(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = NULL;

	pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans, mtxView;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);
	m_mtxWorld._11 = mtxView._11;
	m_mtxWorld._12 = mtxView._21;
	m_mtxWorld._13 = mtxView._31;
	m_mtxWorld._21 = mtxView._12;
	m_mtxWorld._22 = mtxView._22;
	m_mtxWorld._23 = mtxView._32;
	m_mtxWorld._31 = mtxView._13;
	m_mtxWorld._32 = mtxView._23;
	m_mtxWorld._33 = mtxView._33;

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VRETEX_3D);

	// テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	// アルファテスト
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	// レンダーステートを元に戻す

	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//=============================================================================
// シーン3Dの生成
//=============================================================================
CBillboard *CBillboard::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CBillboard *pScene3D;

	pScene3D = new CBillboard(4);

	pScene3D->Init();

	pScene3D->m_pos = pos;
	pScene3D->m_rot = rot;

	// 共有テクスチャを割り当てる
	pScene3D->BindTexture(m_pTexture);

	return pScene3D;
}

//=============================================================================
// 共有テクスチャを割り当てる
//=============================================================================
void CBillboard::BindTexture(LPDIRECT3DTEXTURE9 texture)
{
	m_pTexture = texture;
}

//=============================================================================
// ポジションを取得
//=============================================================================
D3DXVECTOR3 CBillboard::GetPosition(void)
{
	return m_pos;
}

//=============================================================================
// ポジションの設定
//=============================================================================
void CBillboard::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
// ポジションを取得
//=============================================================================
D3DXVECTOR3 CBillboard::GetMove(void)
{
	return m_movve;
}

//=============================================================================
// ポジションの設定
//=============================================================================
void CBillboard::SetMove(D3DXVECTOR3 move)
{
	m_movve = move;
}