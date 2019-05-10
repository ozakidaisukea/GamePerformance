//=============================================================================
//
// ギミック処理 [gimmick.cpp]
// Author : Ozaki
//
//=============================================================================
#include "gimmick.h"
#include "manager.h"
#include "input.h"
#include "renderer.h"
#include "debugproc.h"

//=============================================================================
// 静的メンバ変数
//=============================================================================
LPDIRECT3DTEXTURE9 CGimmick::m_pTexture = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CGimmick::CGimmick() : CScene(2, OBJTYPE_GIMMICK)
{
	// ポリゴンの動きを設定
	m_move = D3DXVECTOR3(0, 0, 0);
	// ポリゴンの位置を設定
	m_pos = D3DXVECTOR3(0, 0, 0);
	// ポリゴンの向きを設定
	m_rot = D3DXVECTOR3(0, 0, 0);

	m_nType = GIMMICK_NONE;
}

//=============================================================================
// デストラクタ
//=============================================================================
CGimmick::~CGimmick()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CGimmick::Init(void)
{
	// オブジェクトタイプの設定
	SetObjtType(CScene::OBJTYPE_GIMMICK);

	//	デバイスの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9	pDevice = pRenderer->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\bg\\gimmick000.jpg",
		&m_pTexture);

	// Xファイルの読み込み
	D3DXLoadMeshFromX(MODEL_GIMMICK,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMatModel,
		NULL,
		&m_nNumMatModel,
		&m_pMeshModel);

	// 最小値/最大値の設定 後にSceneで取得
	m_vtxMin = D3DXVECTOR3(100, 0, 100);
	m_vtxMax = D3DXVECTOR3(-100, 0, -100);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CGimmick::Uninit(void)
{
	// ギミックを破棄
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CGimmick::Update(void)
{
	// デバック表示を取得
	CDebugProc *m_Dubug = CRenderer::GetDebug();

	// キーボードを取得
	CInputKeyboard *InputKeyboard;
	InputKeyboard = CManager::GetInputKeyboard();

	if (CGimmick::GIMMICK_HEIHT == m_nType)
	{
		if (m_pos.y <= 50)
		{
			m_move.y += 0.01f;

			m_pos += m_move;

		}
		else if (m_pos.y >= 50)
		{
			m_move.y -= 0.01f;

			m_pos += m_move;
		}
	}

	if (CGimmick::GIMMICK_WIDTH == m_nType)
	{
		if (m_pos.x <= 25)
		{
			m_move.x += 0.01f;

			m_pos += m_move;

		}
		else if (m_pos.x >= 25)
		{
			m_move.x -= 0.01f;

			m_pos += m_move;
		}
	}

#ifdef _DEBUG
	// 範囲設定のデバック
	//m_Dubug->Print("ssfsfsf", "\n[ ギミックの位置 ] ", "X", m_pos.x, "Y", m_pos.y, "Z", m_pos.z);
#endif
}

//=============================================================================
// 描画処理
//=============================================================================
void CGimmick::Draw(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = NULL;

	pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;				//計算用マトリックス
	D3DMATERIAL9 matDef;						//現在のマテリアル保存用
	D3DXMATERIAL *pMat;							//マテリアルデータへのポインタ

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);
	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);
	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);
	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
	// 現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	// マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_pBuffMatModel->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_nNumMatModel; nCntMat++)
	{	// マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
		// テクスチャ
		pDevice->SetTexture(0, m_pTexture);

		// モデル(パーツ)の描画
		m_pMeshModel->DrawSubset(nCntMat);
	}

	// マテリアルをデフォルトに戻す
	pDevice->SetMaterial(&matDef);
}

//=============================================================================
// ギミックの生成
//=============================================================================
CGimmick * CGimmick::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot,GIMMICK_TYPE type)
{
	CGimmick *pGimmick = NULL;

	// NULLにチェック
	if (pGimmick == NULL)
	{
		pGimmick = new CGimmick();

		// 初期化
		pGimmick->Init();
		// 位置
		pGimmick->m_pos = pos;
		// 向き
		pGimmick->m_rot = rot;
		// タイプ
		pGimmick->m_nType = type;
	}

	// 共有テクスチャを割り当てる
	pGimmick->BindTexture(m_pTexture);

	return pGimmick;
}

//=============================================================================
// 共有テクスチャ
//=============================================================================
void CGimmick::BindTexture(LPDIRECT3DTEXTURE9 texture)
{
	m_pTexture = texture;
}
