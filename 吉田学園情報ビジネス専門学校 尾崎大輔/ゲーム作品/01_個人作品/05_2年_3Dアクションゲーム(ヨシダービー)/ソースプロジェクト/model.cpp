//=============================================================================
//
// モデル処理 [model.cpp]
// Author : Ozaki
//
//=============================================================================
#include "model.h"
#include "input.h"
#include "camera.h"
#include "sound.h"
#include "manager.h"
#include "renderer.h"
#include "debugproc.h"
#include "player.h"

//=============================================================================
// 静的メンバ変数
//=============================================================================
LPDIRECT3DTEXTURE9 CModel::m_pTexture = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CModel::CModel()
{
	m_pBuffMatModel = NULL;
	m_pMeshModel = NULL;
	// ポリゴンの動きを設定
	m_move = D3DXVECTOR3(0, 0, 0);
	// ポリゴンの位置を設定
	m_pos = D3DXVECTOR3(0, 0, 0);
	// ポリゴンの向きを設定
	m_rot = D3DXVECTOR3(0, 0, 0);

	m_pParent = NULL;
}

//=============================================================================
// デストラクタ
//=============================================================================
CModel::~CModel()
{
}

//=============================================================================
// 読み込み
//=============================================================================
HRESULT CModel::Load(void)
{
	// レンダラーを取得
	CRenderer *pRenderer;
	pRenderer = new CRenderer;

	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();

	return S_OK;
}

//=============================================================================
// 開放
//=============================================================================
void CModel::Unload(void)
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CModel::Init(void)
{
	// ポリゴンの動きを設定
	m_move = D3DXVECTOR3(0, 0, 0);
	// ポリゴンの位置を設定
	m_pos = D3DXVECTOR3(0, 0, 0);
	// ポリゴンの向きを設定
	m_rot = D3DXVECTOR3(0, 0, 0);

	m_pParent = NULL;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CModel::Uninit(void)
{
}

//=============================================================================
// 更新処理
//=============================================================================
void CModel::Update(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void CModel::Draw(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();

	// ワールドマトリックスの初期化
	D3DXMATRIX mtxRot, mtxTrans, mtxParent;		//計算用マトリックス
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

	// 親のマトリックスと掛け合わせる
	if (m_pParent != NULL)
	{// 親モデルのマトリックスを取得
		mtxParent = m_pParent->GetMtxWorld();
	}
	// 親モデルがいない時
	else
	{// 現在(最新)のマトリックスを取得
		pDevice->GetTransform(D3DTS_WORLD, &mtxParent);
	}

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// 現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	// マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_pBuffMatModel->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_nNumMatModel; nCntMat++)
	{
		//pMat[nCntMat].MatD3D.Diffuse.r = 1.0f;
		//pMat[nCntMat].MatD3D.Diffuse.g = 1.0f;
		//pMat[nCntMat].MatD3D.Diffuse.b = 1.0f;

		// マテリアルの設定
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
// モデルの生成
//=============================================================================
CModel * CModel::Create(D3DXVECTOR3 pos,D3DXVECTOR3 rot)
{
	CModel *pModel = NULL;

	if (pModel == NULL)
	{
		pModel = new CModel;

		// 初期化
		pModel->Init();

		// 位置
		pModel->m_pos = pos;
		// 向き
		pModel->m_rot = rot;
	}

	pModel->BindTexture(m_pTexture);

	// モデルを返す
	return pModel;
}

//=============================================================================
// 共有テクスチャを割り当てる
//=============================================================================
void CModel::BindTexture(LPDIRECT3DTEXTURE9 texture)
{
	m_pTexture = texture;
}

//=============================================================================
// 共有モデルを割り当てる
//=============================================================================
void CModel::BindModel(LPD3DXBUFFER BuffMatModel, DWORD NumMatModel, LPD3DXMESH MeshModel)
{
	m_pBuffMatModel = BuffMatModel;
	m_nNumMatModel = NumMatModel;
	m_pMeshModel = MeshModel;
}

////=============================================================================
//// ワールドマトリックスの取得
////=============================================================================
//D3DXMATRIX CModel::GetMatrix(void)
//{
//	return m_mtxWorld;
//}

//=============================================================================
// ポジションを取得
//=============================================================================
D3DXVECTOR3 CModel::GetPosition(void)
{
	return m_pos;
}

//=============================================================================
// 動きを取得
//=============================================================================
D3DXVECTOR3 CModel::GetMove(void)
{
	return m_move;
}

//=============================================================================
//プレイヤーのワールドマトリックスの設定
//=============================================================================
D3DXMATRIX CModel::GetMtxWorld(void)
{
	return m_mtxWorld;
}

//=============================================================================
// ポジションの設定
//=============================================================================
void CModel::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
// 向きの設定
//=============================================================================
void CModel::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//=============================================================================
// ムーブの設定
//=============================================================================
void CModel::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}

//=============================================================================
// 親モデルを設定
//=============================================================================
void CModel::SetParent(CModel *pModel)
{
	m_pParent = pModel;
}