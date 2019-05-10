//=============================================================================
//
// メッシュフィールド処理 [meshField.cpp]
// Author : OZAKI
//
//=============================================================================
#include "meshorbit.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "debugproc.h"
#include "player.h"

//=============================================================================
//	静的メンバ変数の初期化
//=============================================================================
LPDIRECT3DTEXTURE9 CMeshOrbit::m_pTexture = NULL;

//=============================================================================
//	コンストラクタ
//=============================================================================
CMeshOrbit::CMeshOrbit(int nPriarity = 1, OBJTYPE objtype = OBJTYPE_MESHORBIT) : CScene(1, OBJTYPE_MESHORBIT)
{
}

//=============================================================================
//	デストラクタ
//=============================================================================
CMeshOrbit::~CMeshOrbit()
{

}

//=============================================================================
//	初期化処理
//=============================================================================
HRESULT CMeshOrbit::Init(void)
{
	//オブジェクトの種類の設定
	SetObjtType(CScene::OBJTYPE_MESHORBIT);

	//	デバイスの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9	pDevice = pRenderer->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\bg\\gradation008.jpg", &m_pTexture);

	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 400
		, D3DUSAGE_WRITEONLY
		, FVF_VRETEX_3D
		, D3DPOOL_MANAGED
		, &m_pVtxBuff
		, NULL);

	// 頂点情報の設定
	VERTEX_3D *pVtx;						// 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 横の分割数
	m_nWidth = 100;
	for (int nCnt = 0; nCnt < m_nWidth; nCnt++)
	{
		pVtx[nCnt].pos = D3DXVECTOR3(0.0, 0.0, 0.0);
		pVtx[nCnt].nor = D3DXVECTOR3(0, 1, 0);
		pVtx[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[nCnt].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx++;
	}

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
//	終了処理
//=============================================================================
void CMeshOrbit::Uninit(void)
{
	//テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}

	//頂点バッファの開放
	if (m_pVtxBuff != NULL)
	{//	頂点バッファが使われていたら
		m_pVtxBuff->Release();
		// 空にする
		m_pVtxBuff = NULL;
	}
	//自分自身の破棄
	CMeshOrbit::Release();
}

//=============================================================================
//	更新処理
//=============================================================================
void CMeshOrbit::Update(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = NULL;

	// マネージャーを取得
	pDevice = CManager::GetRenderer()->GetDevice();

	// キーボードを取得
	CInputKeyboard *InputKeyboard;
	InputKeyboard = CManager::GetInputKeyboard();

	// デバック表示を取得
	CDebugProc *m_Dubug = CRenderer::GetDebug();

	// 頂点情報の設定
	VERTEX_3D *pVtx;						// 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 古いとこから最新にスライド
	for (int nCnt = m_nWidth; nCnt > 0; nCnt--)
	{
		pVtx[nCnt * 2] = pVtx[nCnt * 2 - 2];			// 8から6に代入
		pVtx[nCnt * 2 + 1] = pVtx[nCnt * 2 - 2 + 1];	// 9から7に代入
	}

	// オフセットの設定
	pVtx[0].pos = D3DXVECTOR3(m_pMtxParent->_41, m_pMtxParent->_42, m_pMtxParent->_43);
	pVtx[1].pos = D3DXVECTOR3(m_pMtxParent->_41, m_pMtxParent->_42 + 50.0f, m_pMtxParent->_43);

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

#ifdef _DEBUG
	//m_Dubug->Print("ssfsfsf", "\n[ pVtxの位置 ] ", "X", pVtx->pos.x, "Y", pVtx->pos.y, "Z", pVtx->pos.z);
#endif
}

//=============================================================================
//	更新処理
//=============================================================================
void CMeshOrbit::Draw(void)
{
	//	デバイスの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;				// 計算用マトリックス

	D3DXVECTOR3 aPosVertex[MAX_NUM];

	// カリング
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	// αブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxworld);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxworld);

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VRETEX_3D);

	// テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		200);

	//// 親のマトリックスと掛け合わせる	(新しい頂点座標)
	//m_pos.x = m_mtxworld._41;
	//m_pos.y = m_mtxworld._42;
	//m_pos.z = m_mtxworld._43;

	// カリングを戻す
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

//=============================================================================
//ポリゴンの生成処理
//=============================================================================
CMeshOrbit *CMeshOrbit::Create(D3DXMATRIX mtxWorld)
{
	CMeshOrbit *pMeshOrbit;

	pMeshOrbit = new CMeshOrbit;

	pMeshOrbit->Init();

	pMeshOrbit->m_pMtxParent = &mtxWorld;

	pMeshOrbit->BindTexture(m_pTexture);

	return pMeshOrbit;
}

//=============================================================================
//ポリゴンの親子設定
//=============================================================================
void CMeshOrbit::SetMtxParent(D3DXMATRIX * pMtx)
{
	m_pMtxParent = pMtx;
}

//=============================================================================
//共有テクスチャを設定
//=============================================================================
void CMeshOrbit::BindTexture(LPDIRECT3DTEXTURE9 texture)
{
	m_pTexture = texture;
}
