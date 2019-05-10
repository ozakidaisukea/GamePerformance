//=============================================================================
//
// モデル処理 [Player3.cpp]
// Author : Ozaki
//
//=============================================================================
#include "Player3.h"
#include "Input.h"
#include "camera.h"
#include "shadow.h"
#include "bullet.h"
#include "Explosion.h"
#include "effect.h"
#include "particle.h"
#include "model.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MOVE_PLAYER3	(0.5f)
#define MOVE_BULLET		(8.0f)
#define MAX_PLAYER3		(2)
//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9  g_pVtxBuffPlayer3 = NULL;	// 頂点バッファのポインタ
LPD3DXMESH				 g_pMeshPlayer3 = NULL;		// メッシュ情報へのポインタ
LPD3DXBUFFER			 g_BuffMatPlayer3 = NULL;	// マテリアル情報へのポインタ
D3DXVECTOR3				 g_vtxMinplayer3, g_vtxMaxplayer3;
DWORD					 g_nNumMatPlayer3 = 0;		// マテリアル情報の数
D3DXMATRIX				 g_mtxWorldPlayer3;			// ワールドマトリックス
Player3					 g_Player3;					// プレイヤー
int						 g_nIdxShadow3;
//D3DXVECTOR3				 aPos[4];
//D3DXVECTOR3				 VecA;
//D3DXVECTOR3				 VecB;
//D3DXVECTOR3			 	 VecC;
//=============================================================================
// 初期化処理
//=============================================================================
void InitPlayer3(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	MODE Mode = GetMode();

	switch (Mode)
	{
	case MODE_TITLE:
	{
		g_Player3.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	}
	break;
	case MODE_GAME:
	{
		g_Player3.pos = D3DXVECTOR3(0.0f, 0.0f, 800.0f);
	}
	break;

	}

	g_Player3.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player3.posold = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player3.bDisp = true;
	g_Player3.nCounterState = 0;
	g_Player3.nLife = 10;
	g_Player3.aModel[2];

	// Xファイルの読み込み
	D3DXLoadMeshFromX("data\\MODEL\\saku.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Player3.aModel[0].pBuffMat,
		NULL,
		&g_Player3.aModel[0].nNumMat,
		&g_Player3.aModel[0].pMesh);

	D3DXLoadMeshFromX("data\\MODEL\\saku.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Player3.aModel[1].pBuffMat,
		NULL,
		&g_Player3.aModel[1].nNumMat,
		&g_Player3.aModel[1].pMesh);

	// 位置・向きの初期設定

	//g_nIdxShadow22 = SetShadow(g_Player3.pos, g_Player3.rot);

	g_Player3.aModel[0].nIdxModelParent = -1;
	g_Player3.aModel[0].pos = D3DXVECTOR3(100.0f, 0.0f, 0.0f);

	g_Player3.aModel[1].nIdxModelParent = 0;
	g_Player3.aModel[1].pos = D3DXVECTOR3(-100.0f, 0.0f, 0.0f);

	int						 nNumVtx;					// 頂点数

	DWORD					 sizeFVF;					// 頂点フォーマットの設定
	BYTE					 *pVtxBuff;					// 頂点バッハへのポインタを取得

	nNumVtx = g_Player3.aModel[0].pMesh->GetNumVertices();

	sizeFVF = D3DXGetFVFVertexSize(g_Player3.aModel[0].pMesh->GetFVF());

	g_vtxMinplayer3 = D3DXVECTOR3(10000.0f, 10000.0f, 10000.0f);
	g_vtxMaxplayer3 = D3DXVECTOR3(-10000.0f, -10000.0f, -10000.0f);

	// 頂点バッファをロックし、
	g_Player3.aModel[0].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	// 頂点座標の代入

		if (g_vtxMaxplayer3.x < vtx.x)
		{
			g_vtxMaxplayer3.x = vtx.x;
		}
		if (g_vtxMaxplayer3.y < vtx.y)
		{
			g_vtxMaxplayer3.y = vtx.y;
		}
		if (g_vtxMaxplayer3.z < vtx.z)
		{
			g_vtxMaxplayer3.z = vtx.z;
		}

		// min
		if (g_vtxMaxplayer3.x > vtx.x)
		{
			g_vtxMaxplayer3.x = vtx.x;
		}
		if (g_vtxMaxplayer3.y > vtx.y)
		{
			g_vtxMaxplayer3.y = vtx.y;
		}
		if (g_vtxMaxplayer3.z > vtx.z)
		{
			g_vtxMaxplayer3.z = vtx.z;
		}


		pVtxBuff += sizeFVF;							// サイズ分ポインタを進める

	}
	// 頂点バッファをアンロックする
	g_Player3.aModel[0].pMesh->UnlockVertexBuffer();

}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPlayer3(void)
{

	for (int nCnt = 0; nCnt < MAX_PLAYER3; nCnt++)
	{

		// メッシュの開放
		if (g_Player3.aModel[0].pMesh != NULL)
		{
			g_Player3.aModel[0].pMesh->Release();

			g_Player3.aModel[0].pMesh = NULL;
		}

	}
	// マテリアルの開放
	if (g_Player3.aModel[0].pBuffMat != NULL)
	{
		g_Player3.aModel[0].pBuffMat->Release();

		g_Player3.aModel[0].pBuffMat = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePlayer3(void)
{
	MODE Mode = GetMode();

	switch (Mode)
	{
	case MODE_TITLE:
	{
		g_Player3.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	}
	break;
	case MODE_GAME:
	{


		g_Player3.pos = D3DXVECTOR3(0.0f, 0.0f, 800.0f);

		g_Player3.pos.x += g_Player3.move.x;
		g_Player3.pos.y += g_Player3.move.y;
		g_Player3.pos.z += g_Player3.move.z;

		g_Player3.move.x += (0.0f - g_Player3.move.x) *0.4f;
		g_Player3.move.y += (0.0f - g_Player3.move.y) *0.4f;
		g_Player3.move.z += (0.0f - g_Player3.move.z) *0.4f;

		//if (g_Player3.pos.x >= 950)
		//{
		//	g_Player3.pos.x = 950 - 1;
		//}
		//if (g_Player3.pos.x <= -950)
		//{
		//	g_Player3.pos.x = -950 - 1;
		//}
		//if (g_Player3.pos.z <= -950)
		//{
		//	g_Player3.pos.z = -950 - 1;
		//}
		//if (g_Player3.pos.z >= 950)
		//{
		//	g_Player3.pos.z = 950 - 1;
		//}

		if (g_Player3.pos.y < 1.0f)
		{
			g_Player3.pos.y = 1;
		}



		//SetPostionShadow(g_nIdxShadow22, D3DXVECTOR3(g_Player3.pos.x, 0, g_Player3.pos.z));

		/*SetEffect(g_Player3.pos.x, 0, g_Player3.move.x);*/
	}
	break;

	}


}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPlayer3(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX		mtxRot, mtxTrans;				// 計算用のマトリックス
	D3DMATERIAL9	matDef;							// 現在のマテリアル保存用
	D3DXMATERIAL	*pMat;							// マテリアルデータへのポインタ
	D3DXMATRIX		mtxParent;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_Player3.mtxWorld);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player3.rot.y, g_Player3.rot.x, g_Player3.rot.z);
	D3DXMatrixMultiply(&g_Player3.mtxWorld, &g_Player3.mtxWorld, &mtxRot);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTrans, g_Player3.pos.x, g_Player3.pos.y, g_Player3.pos.z);
	D3DXMatrixMultiply(&g_Player3.mtxWorld, &g_Player3.mtxWorld, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_Player3.mtxWorld);

	for (int nCnt = 0; nCnt < MAX_PLAYER3; nCnt++)
	{
		if (g_Player3.aModel[0].nIdxModelParent == -1)
		{
			mtxParent = g_Player3.mtxWorld;
		}
		else
		{
			mtxParent = g_Player3.aModel[g_Player3.aModel[nCnt].nIdxModelParent].mtxWorld;
		}

		//if (g_Player3.aModel[1].nIdxModelParent == 0)
		//{
		//	mtxParent = g_Player3.mtxWorld;
		//}
		//else
		//{
		//	mtxParent = g_Player3.aModel[1].mtxWorld;
		//}

		//=============================================================================
		// モデル（親）
		//=============================================================================

		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_Player3.aModel[nCnt].mtxWorld);

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player3.aModel[nCnt].rot.y, g_Player3.aModel[nCnt].rot.x, g_Player3.aModel[nCnt
		].rot.z);
		D3DXMatrixMultiply(&g_Player3.aModel[nCnt].mtxWorld, &g_Player3.aModel[nCnt].mtxWorld, &mtxRot);

		// 移動を反映
		D3DXMatrixTranslation(&mtxTrans, g_Player3.aModel[nCnt].pos.x, g_Player3.aModel[nCnt].pos.y, g_Player3.aModel[nCnt].pos.z);
		D3DXMatrixMultiply(&g_Player3.aModel[nCnt].mtxWorld, &g_Player3.aModel[nCnt].mtxWorld, &mtxTrans);


		D3DXMatrixMultiply(&g_Player3.aModel[nCnt].mtxWorld, &g_Player3.aModel[nCnt].mtxWorld, &mtxParent);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_Player3.aModel[nCnt].mtxWorld);

		// 現在のマテリアルを取得
		pDevice->GetMaterial(&matDef);

		// マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)g_Player3.aModel[nCnt].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_Player3.aModel[nCnt].nNumMat; nCntMat++)
		{
			// マテリアルの設定
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			pDevice->SetTexture(0, NULL);

			// モデル(パーツ)の描画
			g_Player3.aModel[nCnt].pMesh->DrawSubset(nCntMat);

		}

		// マテリアルをデフォルトに戻す
		pDevice->SetMaterial(&matDef);
	}
}

//=============================================================================
// モデルの取得
//=============================================================================
Player3 *GetPlayer2(void)
{
	return &g_Player3;
}

