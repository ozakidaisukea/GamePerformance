//=============================================================================
//
// モデル処理 [model.cpp]
// Author : Meguro Mikiya
//
//=============================================================================
#include "sceneX.h"
#include "input.h"
#include "camera.h"
#include "sound.h"
#include "manager.h"
#include "renderer.h"
#include "debugproc.h"

#define MOVE_PLAYER			(2.8f)

LPDIRECT3DTEXTURE9 CSceneX::m_pTexture = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CSceneX::CSceneX(int nPriority, OBJTYPE objtype):CScene(1,CScene::OBJTYPE_X)
{
	m_move = D3DXVECTOR3(0, 0, 0);
}

//=============================================================================
// デストラクタ
//=============================================================================
CSceneX::~CSceneX()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CSceneX::Init(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = NULL;

	pDevice = CManager::GetRenderer()->GetDevice();

	// ポリゴンの位置を設定
	m_pos = D3DXVECTOR3(0, 0, 0.0f);

	// Xファイルの読み込み
	D3DXLoadMeshFromX(MODEL_EARTH,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMatModel,
		NULL,
		&m_nNumMatModel,
		&m_pMeshModel);

	m_VtxMinModel = D3DXVECTOR3(10000, 0, 10000);
	m_VtxMaxModel = D3DXVECTOR3(-10000, 0, -10000);


	m_VtxMaxModel = D3DXVECTOR3(-10000, 0, -10000);
	m_VtxMinModel = D3DXVECTOR3(10000, 0, 10000);

#if 0
	for (int nCntTypeModel = 0; nCntTypeModel < MAX_MODEL_TYPE; nCntTypeModel++)
	{
		//頂点数を取得
		nNumVtex = m_pMeshModel[nCntTypeModel]->GetNumVertices();
		//頂点フォーマットのサイズを取得
		sizeFvF = D3DXGetFVFVertexSize(m_pMeshModel[nCntTypeModel]->GetFVF());
		for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
		{
			//頂点　ロック
			m_pMeshModel[nCntTypeModel]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff[nCntModel]);
			for (int nCntVtx = 0; nCntVtx < nNumVtex; nCntVtx++)
			{	//頂点座標の代入
				D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff[nCntModel];
				if (m_aModel.VtxMinModel.x > vtx.x)
				{
					m_aModel.VtxMinModel.x = vtx.x;
				}
				if (m_aModel.VtxMinModel.y > vtx.y)
				{
					m_aModel.VtxMinModel.y = vtx.y;
				}
				if (m_aModel.VtxMinModel.z > vtx.z)
				{
					m_aModel.VtxMinModel.z = vtx.z;
				}

				if (m_aModel.VtxMaxModel.x < vtx.x)
				{
					m_aModel.VtxMaxModel.x = vtx.x;
				}
				if (m_aModel.VtxMaxModel.y < vtx.y)
				{
					m_aModel.VtxMaxModel.y = vtx.y;
				}
				if (m_aModel.VtxMaxModel.z < vtx.z)
				{
					m_aModel.VtxMaxModel.z = vtx.z;
				}
				pVtxBuff[nCntModel] += sizeFvF;
			}
			//			//頂点バッファをアンロック
			m_pMeshModel[nCntTypeModel]->UnlockVertexBuffer();
		}
	}

#endif

	SetObjtType(CScene::OBJTYPE_X);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CSceneX::Uninit(void)
{

	CScene:: Release();

}

//=============================================================================
// 更新処理
//=============================================================================
void CSceneX::Update(void)
{
	// キーボードを取得
	CInputKeyboard *InputKeyboard;
	InputKeyboard = CManager::GetInputKeyboard();
	// ローカル変数
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 rotMotion;

	////頂点バッファをアンロック
	//m_pVtxBuff->Unlock();
	CDebugProc *m_Dubug = CRenderer::GetDebug();

#ifdef _DEBUG
//	m_Dubug->Print("ssfsfsf", "[ Model 位置 ] ", "X", m_pos.x, "Y", m_pos.y, "Z", m_pos.z);
#endif
}
//=============================================================================
// 描画処理
//=============================================================================
void CSceneX::Draw(void)
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
// モデルの生成
//=============================================================================
CSceneX * CSceneX::Create(D3DXVECTOR3 pos)
{
	CSceneX *pSceneX;

	pSceneX = new CSceneX(1);

	pSceneX->Init();

	pSceneX->m_pos = pos;

	// 共有テクスチャを割り当てる
	pSceneX->BindTexture(m_pTexture);

	return pSceneX;
}

//=============================================================================
// 共有テクスチャを割り当てる
//=============================================================================
void CSceneX::BindTexture(LPDIRECT3DTEXTURE9 texture)
{
	m_pTexture = texture;
}

//=============================================================================
// ポジションを取得
//=============================================================================
D3DXVECTOR3 CSceneX::GetPosition(void)
{
	return m_pos;
}

//=============================================================================
// 動きを取得
//=============================================================================
D3DXVECTOR3 CSceneX::GetMove(void)
{
	return m_move;
}

//=============================================================================
// ポジションの設定
//=============================================================================
void CSceneX::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
// ムーブの設定
//=============================================================================
void CSceneX::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}

//=============================================================================
// ムーブの設定
//=============================================================================
void CSceneX::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}