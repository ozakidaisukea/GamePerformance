//=============================================================================
//
// メッシュフィールド処理 [meshField.cpp]
// Author : OZAKI
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS

#define SAVEFILFNAME "tool.txt"

#include<stdio.h>
#include<string.h>

#include "MeshField.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "debugproc.h"
#include "player.h"

// グローバル変数
float g_aHeight[mPolygonZ][mPolygonX];	// 縦の総数と横の総数

//=============================================================================
//	静的メンバ変数の初期化
//=============================================================================

//=============================================================================
//	コンストラクタ
//=============================================================================
CMeshFiled::CMeshFiled(int nPriarity = 3,OBJTYPE objtype = OBJTYPE_MESHFIELD) : CScene(3, OBJTYPE_MESHFIELD)
{

}

//=============================================================================
//	デストラクタ
//=============================================================================
CMeshFiled::~CMeshFiled()
{

}


//=============================================================================
//	ロード
//=============================================================================
void CMeshFiled::Load(void)
{
	FILE *pFile;

	pFile = fopen("tool.bin", "rb");

	// NULLチェック
	if (pFile != NULL)
	{
		fread(&g_aHeight[0][0], sizeof(float), (mPolygonZ * mPolygonX), pFile);
		fclose(pFile);
	}

	// 頂点情報の設定
	VERTEX_3D *pVtx;						// 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntZ = 0; nCntZ < mPolygonZ; nCntZ++)
	{
		for (int nCnrX = 0; nCnrX < mPolygonX; nCnrX++)
		{
			// 頂点Z,Xをposのy代入
			pVtx->pos.y = g_aHeight[nCntZ][nCnrX];

			pVtx++;
		}
	}
	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();
}

//=============================================================================
//	アンロード
//=============================================================================
void CMeshFiled::Unload(void)
{

}

//=============================================================================
//	初期化処理
//=============================================================================
HRESULT CMeshFiled::Init(void)
{
	//オブジェクトの種類の設定
	SetObjtType(CScene::OBJTYPE_MESHFIELD);

	//	デバイスの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9	pDevice = pRenderer->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\bg\\field004.jpg", &m_pTexture);

	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * m_nNumVtx
		, D3DUSAGE_WRITEONLY
		, FVF_VRETEX_3D
		, D3DPOOL_MANAGED
		, &m_pVtxBuff
		, NULL);

	// インデックスバッファを生成
	pDevice->CreateIndexBuffer(sizeof(WORD) *m_nNumIdx
		, D3DUSAGE_WRITEONLY
		, D3DFMT_INDEX16
		, D3DPOOL_MANAGED
		, &m_pIdxBuff
		, NULL);

	// 頂点情報の設定
	VERTEX_3D *pVtx;						// 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntVtx = 0; nCntVtx < m_nNumVtx; nCntVtx++)
	{//	頂点数分回す

	 // 頂点座標の設定
		pVtx[nCntVtx].pos = D3DXVECTOR3
			/* (幅　/　2 )　+　(幅　/　Xの分割数　*　(頂点数分　% (Xの分割数 + 1 )))*/
			((-m_fWidth / 2) + (m_fWidth / m_nCutX * (nCntVtx % (m_nCutX + 1)))
				, 0.0f
				/* (奥行　/　2 )　-	(奥行　/　Zの分割数　*　(頂点数分　/ (Xの分割数 + 1 )))*/
				, (m_fDepth / 2) - (m_fDepth / m_nCutZ * (nCntVtx / (m_nCutX + 1))));

		// 法線の設定
		pVtx[nCntVtx].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	}


	for (int nCntVtx = 0; nCntVtx < m_nNumVtx; nCntVtx++)
	{//	頂点数分回す

	 // 頂点カラーの設定
		pVtx[nCntVtx].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// テクスチャ座標の設定
		pVtx[nCntVtx].tex = D3DXVECTOR2(nCntVtx % (m_nCutX + 1) * 1.0f, nCntVtx / (m_nCutX + 1) * 1.0f);
	}

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	// インデックスデータの設定
	WORD *pIdx;									// インデックスデータへのポインタ

	// インデックスバッファをロックし、インデックスデータへのポインタを取得
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	// インデックスの設定
	int nNumIdx = m_nCutX + 1;					//	メッシュの横の分割数
	for (int nCntIdx = 0; nCntIdx < m_nNumIdx; nCntIdx += 2/*インデックスの頂点2頂点文加算する*/, nNumIdx++/*for文の数だけメッシュの横の分割数増やす*/)
	{//	インデックス数文回す
		if (nNumIdx % (m_nCutX + 1) == 0 && nNumIdx != m_nCutX + 1)
		{	//	頂点のインデックスが端までいったら
			pIdx[nCntIdx] = nNumIdx - (m_nCutX + 2);	/*	横の分割数　-　(横の分割数 + 2)*/
			pIdx[nCntIdx + 1] = nNumIdx;				/*	横の分割数 */
														//	頂点バッファをずらす
			nCntIdx += 2;
		}
		pIdx[nCntIdx] = nNumIdx;	/*	横の分割数 */
		pIdx[nCntIdx + 1] = nNumIdx - (m_nCutX + 1);	/*	横の分割数　-　(横の分割数 + 2)*/
	}

	// インデックスバッファをアンロックする
	m_pIdxBuff->Unlock();


	return S_OK;
}

//=============================================================================
//	終了処理
//=============================================================================
void CMeshFiled::Uninit(void)
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

	//インデックスバッファの開放
	if (m_pIdxBuff != NULL)
	{//	インデックスバッファが使われていたら
		m_pIdxBuff->Release();

		// インデックスを空にする
		m_pIdxBuff = NULL;
	}
	//自分自身の破棄
	CMeshFiled::Release();
}

//=============================================================================
//	更新処理
//=============================================================================
void CMeshFiled::Update(void)
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

	//ローカル変数
	VERTEX_3D*pVtx;

	//頂点バッファをロックし、頂点データのポインタの取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ローカル変数
	D3DXVECTOR3 aNor[MAX_NOR];
	int nCntZ2 = 0;
	int nCnt3 = 0;

	for (int nCntZ = 0; nCntZ < mPolygonZ; nCntZ++)
	{
		for (int nCntX = 0; nCntX < mPolygonX; nCntX++)
		{
			D3DXVECTOR3 *pPos0, *pPos1, *pPos2, *pPos3;
			D3DXVECTOR3 Vec0, Vec1, Vec2;
			D3DXVECTOR3 nor;

			// 法線の求め
			pPos0 = &pVtx[nCntZ + nCntX + nCntZ2].pos;
			pPos1 = &pVtx[nCntZ + nCntX + nCntZ2 + (mPolygonX + 1)].pos;
			pPos2 = &pVtx[nCntZ + nCntX + nCntZ2 + (mPolygonX + 1) + 1].pos;
			pPos3 = &pVtx[nCntZ + nCntX + nCntZ2 + 1].pos;

			// ベクトルの求め
			Vec0 = *pPos1 - *pPos0;
			Vec1 = *pPos2 - *pPos0;
			Vec2 = *pPos3 - *pPos0;

			// Vec1 Vec0
			D3DXVec3Cross(&nor, &Vec1, &Vec0);
			// 正規化
			D3DXVec3Normalize(&nor, &nor);

			// for分に入った時にnCntZ2が２入る
			aNor[((nCntZ * 2) + (nCntX * 2)) + nCnt3] = nor;

			// Vec2 Vec1
			D3DXVec3Cross(&nor, &Vec2, &Vec1);
			// 正規化
			D3DXVec3Normalize(&nor, &nor);

			aNor[(nCntZ * 2) + (nCntX * 2) + nCnt3 + 1] = nor;
		}
		nCntZ2 += mPolygonX;
		nCnt3 += (mPolygonX * 2) - 2;
	}

	// 法則性 各頂点の法線を求める
	for (int nCntZZ = 0; nCntZZ <= mPolygonZ; nCntZZ++)
	{
		for (int nCntXX = 0; nCntXX <= mPolygonX; nCntXX++)
		{
			// 上端  Zが0
			if (nCntZZ == 0)
			{
				// 左上 Xが0
				if (nCntXX == 0)
				{
					pVtx[0].nor = (aNor[0] + aNor[1]) / 2;
				}
				// 右下 Xが2
				else if (nCntXX == mPolygonX)
				{
					pVtx[mPolygonX].nor = aNor[mPolygonX * 2 - 1];
				}
				// 中央 Xが1
				else
				{
					pVtx[mPolygonX].nor = (aNor[nCntXX * mPolygonX] + aNor[nCntXX * mPolygonX - 1] + aNor[nCntXX * mPolygonX + 1]) / 3;
				}
			}
			// 下端  Zが3
			else if (nCntZZ == mPolygonZ)
			{
				// Xが0
				if (nCntXX == 0)
				{
					pVtx[mPolygonX].nor = aNor[(mPolygonX * 2) * (mPolygonX - 1)];
				}
				// Xが2
				else if (nCntXX == mPolygonX)
				{
					pVtx[mPolygonX].nor = (aNor[(mPolygonX * mPolygonZ) * 2 - 1] + aNor[(mPolygonX * mPolygonZ) * 2 - 2]) / 2;

				}
				// Xが1
				else
				{
					pVtx[mPolygonX].nor = (aNor[(mPolygonX * 2) * (nCntZZ - 1) + nCntXX * mPolygonX] +
						aNor[(mPolygonX * 2) * (nCntZZ - 1) + nCntXX * mPolygonX - 1] +
						aNor[(mPolygonX * 2) * (nCntZZ - 1) + nCntXX * mPolygonX + 1]) / 3;
				}
			}
			// 中央 Zが1
			else
			{
				// Xが0
				if (nCntXX == 0)
				{
					pVtx[mPolygonX].nor = ((aNor[(mPolygonX * 2) * (nCntZZ - 1)]) + (aNor[(mPolygonX * 2) * nCntZZ]) + (aNor[(mPolygonX * 2) * nCntZZ] + 1)) / 3;
				}
				// Xが2
				else if (nCntXX == mPolygonX)
				{
					pVtx[mPolygonX].nor = (aNor[((mPolygonX * nCntZZ) * 2) - 1] + aNor[((mPolygonX * nCntZZ) * 2) - 2] + aNor[((mPolygonX * nCntZZ + 1) * 2) - 1]) / 3;
				}
				// Xが1
				else
				{
					pVtx[mPolygonX].nor = (aNor[(mPolygonX * 2) * (nCntZZ - 1) + (nCntXX * 2 - 1)] +
						aNor[(mPolygonX * 2) * (nCntZZ - 1) + (nCntXX * 2)] +
						aNor[(mPolygonX * 2) * (nCntZZ - 1) + (nCntXX * 2 + 1)] +
						aNor[(mPolygonX * 2) * nCntZZ + (nCntXX * 2 - 1)] +
						aNor[(mPolygonX * 2) * nCntZZ + (nCntXX * 2)] +
						aNor[(mPolygonX * 2) * nCntZZ + (nCntXX * 2 + 1)]) / 6;
				}
			}
		}
	}
	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();

#ifdef _DEBUG

	//m_Dubug->Print("ssfsfsf", "\n[ pVtx[0]法線０ ] ", "X", pVtx[0].nor.x, "Y", pVtx[0].nor.y, "Z", pVtx[0].nor.z);
	//m_Dubug->Print("ssfsfsf", "\n[ pVtx[1]法線１ ] ", "X", pVtx[1].nor.x, "Y", pVtx[1].nor.y, "Z", pVtx[1].nor.z);
	//m_Dubug->Print("ssfsfsf", "\n[ pVtx[2]法線２ ] ", "X", pVtx[2].nor.x, "Y", pVtx[2].nor.y, "Z", pVtx[2].nor.z);
	//m_Dubug->Print("ssfsfsf", "\n[ pVtx[3]法線３ ] ", "X", pVtx[3].nor.x, "Y", pVtx[3].nor.y, "Z", pVtx[3].nor.z);
	//m_Dubug->Print("ssfsfsf", "\n[ pVtx[4]法線４ ] ", "X", pVtx[4].nor.x, "Y", pVtx[4].nor.y, "Z", pVtx[4].nor.z);
	//m_Dubug->Print("ssfsfsf", "\n[ pVtx[5]法線５ ] ", "X", pVtx[5].nor.x, "Y", pVtx[5].nor.y, "Z", pVtx[5].nor.z);
	//m_Dubug->Print("ssfsfsf", "\n[ pVtx[6]法線６ ] ", "X", pVtx[6].nor.x, "Y", pVtx[6].nor.y, "Z", pVtx[6].nor.z);
	//m_Dubug->Print("ssfsfsf", "\n[ pVtx[7]法線７ ] ", "X", pVtx[7].nor.x, "Y", pVtx[7].nor.y, "Z", pVtx[7].nor.z);
	//m_Dubug->Print("ssfsfsf", "\n[ pVtx[8]法線８ ] ", "X", pVtx[8].nor.x, "Y", pVtx[8].nor.y, "Z", pVtx[8].nor.z);
	//m_Dubug->Print("s", "\n");
	//m_Dubug->Print("ssfsfsf", "\n[ pVtxの位置 ] ", "X", pVtx->pos.x, "Y", pVtx->pos.y, "Z", pVtx->pos.z);
#endif
}

//=============================================================================
//	更新処理
//=============================================================================
void CMeshFiled::Draw(void)
{
	//	デバイスの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;				// 計算用マトリックス

												// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxworld);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxworld, &m_mtxworld, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxworld, &m_mtxworld, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxworld);

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// インデックスバッファをデータストリームに設定
	pDevice->SetIndices(m_pIdxBuff);

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VRETEX_3D);

	// テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	// ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_nNumVtx, 0, m_nNumPolygon);
}

//=============================================================================
//ポリゴンの生成処理
//=============================================================================
CMeshFiled *CMeshFiled::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fDepth, int nCutX, int nCutZ)
{
	CMeshFiled *pSmeshFiled = {};

	if (pSmeshFiled == NULL)
	{//	3Dポリゴンの生成
		pSmeshFiled = new CMeshFiled;
		if (pSmeshFiled != NULL)
		{//	3Dポリゴンが生成されたら
		 // ポリゴンの初期化処理
			pSmeshFiled->m_pos = pos;		//	位置
			pSmeshFiled->m_rot = rot;		//	回転
			pSmeshFiled->m_fWidth = fWidth;	//	幅
			pSmeshFiled->m_fDepth = fDepth;	//	奥行
			pSmeshFiled->m_nCutX = nCutX;	//	横の分割数
			pSmeshFiled->m_nCutZ = nCutZ;	//	奥行の分割数
			pSmeshFiled->m_nNumVtx = (nCutX + 1) *(nCutZ + 1);					//	インデックス用の頂点数の計算
			pSmeshFiled->m_nNumPolygon = nCutX * nCutZ * 2 + (nCutZ - 1) * 4;	//	ポリゴン数のポリゴン数の計算
			pSmeshFiled->m_nNumIdx = pSmeshFiled->m_nNumPolygon + 2;			//	インデックス用のポリゴン数の計算
			pSmeshFiled->Init();
		}
	}
	return pSmeshFiled;
}

//=============================================================================
//	共通テクスチャを割り当てる
//=============================================================================
void CMeshFiled::BindTexture(LPDIRECT3DTEXTURE9		pTexture)
{
	m_pTexture = pTexture;
}

//=============================================================================
//	地面の高さの取得
//=============================================================================
void CMeshFiled::SetHigth(D3DXVECTOR3 pos, float fValue, float fRange)
{
	//// 頂点情報の設定
	//VERTEX_3D *pVtx;						// 頂点情報へのポインタ

	//// 頂点バッファをロックし、頂点データへのポインタを取得
	//m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//for (int nCntZ = 0; nCntZ < mPolygonZ + 1; nCntZ++)
	//{
	//	for (int nCnrX = 0; nCnrX < mPolygonX + 1; nCnrX++)
	//	{
	//		float fLength = sqrt((pos.x - pVtx->pos.x) * (pos.x - pVtx->pos.x)
	//			+ (pos.z - pVtx->pos.z) * (pos.z - pVtx->pos.z));

	//		// 対象の頂点範囲内
	//		if (fLength < fRange)
	//		{
	//			float fHeight = cosf((D3DX_PI * 0.5f) * (fLength / fRange))* fValue;

	//			pVtx->pos.y += fHeight;

	//		}

	//		pVtx++;
	//	}
	//}

	//// デバック表示を取得
	//CDebugProc *m_Dubug = CRenderer::GetDebug();

	////頂点バッファをアンロック
	//m_pVtxBuff->Unlock();
}

//=============================================================================
//	セーブ
//=============================================================================
void CMeshFiled::Save(void)
{
	FILE *pFile;

	// 頂点情報の設定
	VERTEX_3D *pVtx;						// 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntZ = 0; nCntZ < mPolygonZ; nCntZ++)
	{
		for (int nCnrX = 0; nCnrX < mPolygonX; nCnrX++)
		{
			// 頂点Z,Xをposのy代入
			g_aHeight[nCntZ][nCnrX] = pVtx->pos.y;

			pVtx++;
		}
	}
//頂点バッファをアンロック
	m_pVtxBuff->Unlock();

	pFile = fopen("tool.bin", "wb");

	if (pFile != NULL)
	{

		fwrite(&g_aHeight[0][0], sizeof(float), (mPolygonZ * mPolygonX), pFile);
		fclose(pFile);
	}


}