//=============================================================================
//
// モデル処理 [model.cpp]
// Author : Meguro Mikiya
//
//=============================================================================
#include "model.h"
#include "input.h"
#include "shadow.h"
#include "camera.h"
#include "bullet.h"
#include "polygon.h"
#include "player.h"
#include "player2.h"
#include "game.h"
#include "explosion.h"
#include "Fade.h"
#include "sound.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPD3DXMESH g_pMeshModel[MAX_MODEL_TYPE];						//メッシュ情報へのポインタ
LPD3DXBUFFER g_pBuffMatModel[MAX_MODEL_TYPE];				//マテリアル情報へのポインタ
LPDIRECT3DTEXTURE9	g_pTextureModel[MAX_MODEL_TYPE];			//テクスチャへのポインタ
DWORD g_nNumMatModel[MAX_MODEL_TYPE] = {};					//マテリアル情報の数
MODEL g_aModel[MAX_MODEL];
D3DXMATERIAL *g_pMat;
VTX g_aModelVtx[MAX_MODEL_TYPE];

int						takumi1;

//=============================================================================
// 初期化処理
//=============================================================================
void InitModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// Xファイルの読み込み
	D3DXLoadMeshFromX(MODEL_NAME000,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatModel[0],
		NULL,
		&g_nNumMatModel[0],
		&g_pMeshModel[0]);

	// Xファイルの読み込み
	D3DXLoadMeshFromX(MODEL_NAME001,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatModel[1],
		NULL,
		&g_nNumMatModel[1],
		&g_pMeshModel[1]);

	// Xファイルの読み込み
	D3DXLoadMeshFromX(MODEL_NAME002,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatModel[2],
		NULL,
		&g_nNumMatModel[2],
		&g_pMeshModel[2]);

	// Xファイルの読み込み
	D3DXLoadMeshFromX(MODEL_NAME003,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatModel[3],
		NULL,
		&g_nNumMatModel[3],
		&g_pMeshModel[3]);

	// Xファイルの読み込み
	D3DXLoadMeshFromX(MODEL_NAME004,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatModel[4],
		NULL,
		&g_nNumMatModel[4],
		&g_pMeshModel[4]);


	int nNumVtex;	//頂点数
	DWORD sizeFvF;	//頂点フォーマットのサイズ
	BYTE *pVtxBuff[MAX_MODEL];	//頂点バッファへのポインタ
	D3DXVECTOR3 vtx[MAX_MODEL];

	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		g_aModel[nCntModel].VtxMinModel = D3DXVECTOR3(10000, 0, 10000);
		g_aModel[nCntModel].VtxMaxModel = D3DXVECTOR3(-10000, 0, -10000);
		g_aModel[nCntModel].nType = 0;
		g_aModel[nCntModel].bUse = false;
		g_aModel[nCntModel].nLife = 20;
		g_aModel[nCntModel].fDistangle = 0;
		g_aModel[nCntModel].fDiftangle = 0;
		g_aModel[nCntModel].move = D3DXVECTOR3(0.0f,0.0f,0.0f);

	}
	for (int nCntTypeModel = 0; nCntTypeModel < MAX_MODEL_TYPE; nCntTypeModel++)
	{
		g_aModelVtx[nCntTypeModel].VtxMaxModel = D3DXVECTOR3(-10000, 0, -10000);
		g_aModelVtx[nCntTypeModel].VtxMinModel = D3DXVECTOR3(10000, 0, 10000);
	}

#if 0
	for (int nCntTypeModel = 0; nCntTypeModel < MAX_MODEL_TYPE; nCntTypeModel++)
	{
		//頂点数を取得
		nNumVtex = g_pMeshModel[nCntTypeModel]->GetNumVertices();
		//頂点フォーマットのサイズを取得
		sizeFvF = D3DXGetFVFVertexSize(g_pMeshModel[nCntTypeModel]->GetFVF());
		for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
		{
			//頂点　ロック
			g_pMeshModel[nCntTypeModel]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff[nCntModel]);
			for (int nCntVtx = 0; nCntVtx < nNumVtex; nCntVtx++)
			{	//頂点座標の代入
				D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff[nCntModel];
				if (g_aModel[nCntModel].VtxMinModel.x > vtx.x)
				{
					g_aModel[nCntModel].VtxMinModel.x = vtx.x;
				}
				if (g_aModel[nCntModel].VtxMinModel.y > vtx.y)
				{
					g_aModel[nCntModel].VtxMinModel.y = vtx.y;
				}
				if (g_aModel[nCntModel].VtxMinModel.z > vtx.z)
				{
					g_aModel[nCntModel].VtxMinModel.z = vtx.z;
				}

				if (g_aModel[nCntModel].VtxMaxModel.x < vtx.x)
				{
					g_aModel[nCntModel].VtxMaxModel.x = vtx.x;
				}
				if (g_aModel[nCntModel].VtxMaxModel.y < vtx.y)
				{
					g_aModel[nCntModel].VtxMaxModel.y = vtx.y;
				}
				if (g_aModel[nCntModel].VtxMaxModel.z < vtx.z)
				{
					g_aModel[nCntModel].VtxMaxModel.z = vtx.z;
				}
				pVtxBuff[nCntModel] += sizeFvF;
			}
			//			//頂点バッファをアンロック
			g_pMeshModel[nCntTypeModel]->UnlockVertexBuffer();
		}
	}

#endif
	for (int nCntTypeModel = 0; nCntTypeModel < MAX_MODEL_TYPE; nCntTypeModel++)
	{
		//頂点数を取得
		nNumVtex = g_pMeshModel[nCntTypeModel]->GetNumVertices();
		//頂点フォーマットのサイズを取得
		sizeFvF = D3DXGetFVFVertexSize(g_pMeshModel[nCntTypeModel]->GetFVF());
		//頂点　ロック
		g_pMeshModel[nCntTypeModel]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff[nCntTypeModel]);
		for (int nCntVtx = 0; nCntVtx < nNumVtex; nCntVtx++)
		{	//頂点座標の代入
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff[nCntTypeModel];
			if (g_aModelVtx[nCntTypeModel].VtxMinModel.x > vtx.x)
			{
				g_aModelVtx[nCntTypeModel].VtxMinModel.x = vtx.x;
			}
			if (g_aModelVtx[nCntTypeModel].VtxMinModel.y > vtx.y)
			{
				g_aModelVtx[nCntTypeModel].VtxMinModel.y = vtx.y;
			}
			if (g_aModelVtx[nCntTypeModel].VtxMinModel.z > vtx.z)
			{
				g_aModelVtx[nCntTypeModel].VtxMinModel.z = vtx.z;
			}

			if (g_aModelVtx[nCntTypeModel].VtxMaxModel.x < vtx.x)
			{
				g_aModelVtx[nCntTypeModel].VtxMaxModel.x = vtx.x;
			}
			if (g_aModelVtx[nCntTypeModel].VtxMaxModel.y < vtx.y)
			{
				g_aModelVtx[nCntTypeModel].VtxMaxModel.y = vtx.y;
			}
			if (g_aModelVtx[nCntTypeModel].VtxMaxModel.z < vtx.z)
			{
				g_aModelVtx[nCntTypeModel].VtxMaxModel.z = vtx.z;
			}
			pVtxBuff[nCntTypeModel] += sizeFvF;
		}
		//			//頂点バッファをアンロック
		g_pMeshModel[nCntTypeModel]->UnlockVertexBuffer();
	}


	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\exclamation000.jpg",
		&g_pTextureModel[0]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\question000.jpg",
		&g_pTextureModel[1]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		MODEL_NAME002,
		&g_pTextureModel[2]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		MODEL_NAME003,
		&g_pTextureModel[3]);

	//for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	//{
	//	for (int nCntMat = 0; nCntMat < (int)g_nNumMatModel[nCntModel]; nCntMat++)
	//	{
	//		// マテリアルデータへのポインタを取得
	//		g_pMat = (D3DXMATERIAL*)g_pBuffMatModel[g_aModel[nCntModel].nType]->GetBufferPointer();
	//		{
	//			D3DXCreateTextureFromFile(pDevice,
	//				g_pMat[nCntMat].pTextureFilename,
	//				&g_pTextureModel[g_aModel[nCntModel].nType]);
	//		}
	//	}
	//}

	//float testpos = 100;
	//for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	//{
	//	// 位置・向きの初期設定
	//	g_aModel[nCntModel].pos = D3DXVECTOR3(testpos, 0, 0);
	//	g_aModel[nCntModel].rot = D3DXVECTOR3(0, 0, 0);
	//	g_aModel[nCntModel].fShadow = 12;
	////	g_aModel[nCntModel].fDestAngle = 0;
	//	//g_aModel
	//	//　影のセット
	//	g_aModel[nCntModel].nIdxShadow = SetShadow(g_aModel[nCntModel].pos, D3DXVECTOR3(0, 0, 0), 20.0f);

	//	testpos -= 100;
	//	g_aModel[nCntModel].bUse = true;
	//}

	takumi1 = 0;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitModel(void)
{
	for (int nCntModel = 0; nCntModel < MAX_MODEL_TYPE; nCntModel++)
	{
		// メッシュの開放
		if (g_pMeshModel[nCntModel] != NULL)
		{
			g_pMeshModel[nCntModel]->Release();
			g_pMeshModel[nCntModel] = NULL;
		}
		// マテリアルの開放
		if (g_pBuffMatModel[nCntModel] != NULL)
		{
			g_pBuffMatModel[nCntModel]->Release();
			g_pBuffMatModel[nCntModel] = NULL;
		}
		//テクスチャの破棄
		if (g_pTextureModel[nCntModel] != NULL)
		{
			g_pTextureModel[nCntModel]->Release();
			g_pTextureModel[nCntModel] = NULL;
		}
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateModel(void)
{
	Player2 *pPlayer2;
	pPlayer2 = GetPlayer2();

	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		if (g_aModel[nCntModel].bUse == true)
		{
			g_aModel[nCntModel].fDistangle = atan2f((pPlayer2->pos.x - sinf(pPlayer2->rot.y) - g_aModel[nCntModel].pos.x),
				(pPlayer2->pos.z - cosf(pPlayer2->rot.y) - g_aModel[nCntModel].pos.z));

			g_aModel[nCntModel].fDiftangle = g_aModel[nCntModel].fDistangle - g_aModel[nCntModel].rot.y;

			if (g_aModel[nCntModel].fDiftangle > D3DX_PI)
			{
				g_aModel[nCntModel].fDiftangle -= D3DX_PI * 2.0f;
			}
			if (g_aModel[nCntModel].fDiftangle < -D3DX_PI)
			{
				g_aModel[nCntModel].fDiftangle += D3DX_PI * 2.0f;
			}

			g_aModel[nCntModel].rot.y += g_aModel[nCntModel].fDiftangle * 1.0f;

			if (g_aModel[nCntModel].rot.y > D3DX_PI)
			{
				g_aModel[nCntModel].rot.y -= D3DX_PI * 2.0f;
			}
			if (g_aModel[nCntModel].rot.y < -D3DX_PI)
			{
				g_aModel[nCntModel].rot.y += D3DX_PI * 2.0f;
			}
			g_aModel[nCntModel].move.x = sinf(g_aModel[nCntModel].rot.y) * 2.5f;
			g_aModel[nCntModel].move.z = cosf(g_aModel[nCntModel].rot.y) * 2.5f;
			g_aModel[nCntModel].pos += g_aModel[nCntModel].move;

			/*g_aModel[nCntModel].nLife--;*/

			// 弾の寿命
			if (g_aModel[nCntModel].nLife <= 0)
			{
				g_aModel[nCntModel].bUse = false;
				//DeleteShadow(g_aBullet[nCntBullet].nIdxShadow);
				SetExplosion(g_aModel[nCntModel].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),D3DXCOLOR(255,255,0,0.0f));
				SetFade(MODE_RESULT);
				takumi1++;
			}

			FADE Fade;
			Fade = GetFade();

			if (takumi1 == 5)
			{
				SetFade(MODE_RESULT);
			}

			if (g_aModel[nCntModel].pos.y < 1.0f)
			{
				g_aModel[nCntModel].pos.y = 1;
			}
			//SetPostionShadow(g_nIdxShado, D3DXVECTOR3(g_aModel[nCntModel].pos.x, 0, g_aModel[nCntModel].pos.z));
		}
	}
}
//=============================================================================
// 描画処理
//=============================================================================
void DrawModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;				//計算用マトリックス
	D3DMATERIAL9 matDef;						//現在のマテリアル保存用
	D3DXMATERIAL *pMat;							//マテリアルデータへのポインタ

	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		if (g_aModel[nCntModel].bUse == true)	//モデルが使用されている
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aModel[nCntModel].mtxWorld);
			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aModel[nCntModel].rot.y, g_aModel[nCntModel].rot.x, g_aModel[nCntModel].rot.z);
			D3DXMatrixMultiply(&g_aModel[nCntModel].mtxWorld, &g_aModel[nCntModel].mtxWorld, &mtxRot);
			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aModel[nCntModel].pos.x, g_aModel[nCntModel].pos.y, g_aModel[nCntModel].pos.z);
			D3DXMatrixMultiply(&g_aModel[nCntModel].mtxWorld, &g_aModel[nCntModel].mtxWorld, &mtxTrans);
			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aModel[nCntModel].mtxWorld);
			// 現在のマテリアルを取得
			pDevice->GetMaterial(&matDef);


			// マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_pBuffMatModel[g_aModel[nCntModel].nType]->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_nNumMatModel[g_aModel[nCntModel].nType]; nCntMat++)
			{	// マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
				// テクスチャ

				pDevice->SetTexture(0, g_pTextureModel[2]);

				// モデル(パーツ)の描画
				g_pMeshModel[g_aModel[nCntModel].nType]->DrawSubset(nCntMat);

			}
			// マテリアルをデフォルトに戻す
			pDevice->SetMaterial(&matDef);
		}
	}
}

//*****************************************************************************
//モデルポインタ処理
//*****************************************************************************
MODEL *GetModel(void)
{
	return &g_aModel[0];
}
//*****************************************************************************
//モデルとの当たり判定処理
//*****************************************************************************
bool CollisionModel(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 radius,D3DXVECTOR3 VtxMax, D3DXVECTOR3 VtxMin ,MODEL **pModel)
{
	//bool bLand = false;  // 乗ったかどうか

	//Player *pPlayer = GetPlayer();

	//D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//D3DXMATRIX mtxMax, mtxMin, mtxRot, mtxTrans;


	//for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	//{// 障害物の数だけ繰り返し
	//	if (g_aModel[nCntModel].bUse == true)
	//	{// 障害物が使用されている

	//		//[MAX]

	//		// ワールドマトリックスの初期化
	//		D3DXMatrixIdentity(&mtxMax);
	//		// 回転を反映
	//		D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	//		D3DXMatrixMultiply(&mtxMax, &mtxMax, &mtxRot);
	//		// 位置を反映
	//		D3DXMatrixTranslation(&mtxTrans, g_aModel[nCntModel].VtxMaxModel.x, g_aModel[nCntModel].VtxMaxModel.y, g_aModel[nCntModel].VtxMaxModel.z);
	//		D3DXMatrixMultiply(&mtxMax, &mtxMax, &mtxTrans);

	//		D3DXMatrixMultiply(&mtxMax, &mtxMax, &g_aModel[nCntModel].mtxWorld);

	//		//[MIN]
	//		// ワールドマトリックスの初期化
	//		D3DXMatrixIdentity(&mtxMin);
	//		// 回転を反映
	//		D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	//		D3DXMatrixMultiply(&mtxMin, &mtxMin, &mtxRot);
	//		// 位置を反映
	//		D3DXMatrixTranslation(&mtxTrans, g_aModel[nCntModel].VtxMinModel.x, g_aModel[nCntModel].VtxMinModel.y, g_aModel[nCntModel].VtxMinModel.z);
	//		D3DXMatrixMultiply(&mtxMin, &mtxMin, &mtxTrans);

	//		D3DXMatrixMultiply(&mtxMin, &mtxMin, &g_aModel[nCntModel].mtxWorld);


	//		//if (pPos->y <= mtxMax._42 && pPos->y + radius.y > mtxMin._42
	//		//	|| pPos->y + radius.y > mtxMax._42 && pPos->y < mtxMin._42
	//		//	|| pPos->y + radius.y > mtxMax._42 && pPos->y < mtxMin._42)
	//		//{// 障害物のY座標の中にいる
	//			if (pPos->z - radius.z <= mtxMax._43 && pPos->z + radius.z >= mtxMin._43)
	//			{// 障害物のZ座標の中にいる
	//				if (pPosOld->x + radius.x <= mtxMin._41
	//					&& pPos->x + radius.x > mtxMin._41)
	//				{// X座標の中に左から入った
	//				 // 跳ね返る
	//					//g_aModel[nCntModel].move.x += pMove->x + 5;
	//					pPos->x = mtxMax._41 - radius.x;
	//					pMove->x = 0.0f;
	//					*pModel = &g_aModel[nCntModel];
	//				}
	//				else if (pPosOld->x - radius.x >= mtxMax._41
	//					&& pPos->x - radius.x <  mtxMax._41)
	//				{// X座標の中に右から入った
	//				 // 跳ね返る
	//					//g_aModel[nCntModel].move.x += pMove->x - 5;

	//					pPos->x = mtxMax._41 + radius.x + 0.1f;
	//					pMove->x = 0.0f;
	//					*pModel = &g_aModel[nCntModel];
	//				}
	//			}
	//			if (pPos->x - radius.x <= mtxMax._41 && pPos->x + radius.x >=  mtxMin._41)
	//			{// 障害物のX座標の中にいる
	//				if (pPosOld->z + radius.z <= mtxMin._43
	//					&& pPos->z + radius.z > mtxMin._43)
	//				{// Z座標の中に前から入った
	//				 // 跳ね返る
	//					//g_aModel[nCntModel].move.z += pMove->z + 5;
	//					SetExplosion(g_aModel[nCntModel].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(255, 255, 255, 0.0f));
	//					g_aModel[nCntModel].bUse = false;
	//					pPos->z = mtxMax._43 - radius.z;
	//					pMove->z = 0.0f;
	//					*pModel = &g_aModel[nCntModel];
	//					bLand = true;
	//					FADE Fade;
	//					Fade = GetFade();
	//					if (Fade == FADE_NONE)
	//					{

	//						SetFade(MODE_RESULT);
	//						PlaySound(SOUND_LABEL_SE_SAKEBI);
	//					}
	//				}
	//				else if (pPosOld->z - radius.z >= mtxMax._43
	//					&& pPos->z - radius.z < mtxMax._43)
	//				{// Z座標の中に後ろから入った
	//				 // 跳ね返る
	//					//g_aModel[nCntModel].move.z += pMove->z - 5;

	//					pPos->z = mtxMax._43 + radius.z + 0.1f;
	//					pMove->z = 0.0f;
	//					*pModel = &g_aModel[nCntModel];
	//				}
	//			}

	//			//if (pPos->x - radius.x < g_aModel[nCntModel].pos.x + g_aModel[nCntModel].VtxMaxModel.x - 2.0f&& pPos->x + radius.x > g_aModel[nCntModel].pos.x + g_aModel[nCntModel].VtxMinModel.x + 2.0f
	//			//	&& pPos->z - radius.z <= g_aModel[nCntModel].pos.z + g_aModel[nCntModel].VtxMaxModel.z - 2.0f && pPos->z + radius.z >= g_aModel[nCntModel].pos.z + g_aModel[nCntModel].VtxMinModel.z + 2.0f)
	//			//{// 障害物の内側に乗った
	//			//	bLand = true;  // 乗った判定を返す
	//			//	pPos->y = g_aModel[nCntModel].pos.y + g_aModel[nCntModel].VtxMaxModel.y;
	//			//	pMove->y = 0.0f;  // 移動量をなくす
	//			//}
	//

	//		//pPos->x + fwigth - X_Y >= g_aBlock[nCntBlock].pos.x
	//		//	&& pPos->x - fwigth + X_Y <= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fwidth)


	//		// X
	//		//if (pPos->x - radius.x >= mtxMin._41 && pPos->x + radius.x >= mtxMin._41)
	//		//{
	//		//	if (pPosOld->x -radius.x <= mtxMax._41 && pPosOld->x + radius.x <= mtxMax._41)
	//		//	{

	//		//	}
	//		//}


	//		//if (pPos->y <= mtxMax._42 && pPos->y + radius.y > mtxMin._42
	//		//	|| pPos->y + radius.y > mtxMax._42 && pPos->y < mtxMin._42
	//		//	|| pPos->y + radius.y > mtxMax._42 && pPos->y < mtxMin._42)
	//		//{
	//		//	if (pPos->x <= mtxMax._41 && pPos->x + radius.x > mtxMin._41
	//		//		|| pPos->x + radius.x > mtxMax._41 && pPos->x < mtxMin._41
	//		//		|| pPos->x + radius.x > mtxMax._41 && pPos->x < mtxMin._41)
	//		//	{
	//		//		if (pPos->z > mtxMin._43 && pPosOld->z < mtxMin._43)
	//		//		{
	//		//			bLand = true;  // 乗った判定を返す
	//		//			pPos->z = mtxMin._43;  // 移動量をなくす
	//		//			pMove->z = 0.0f;  // 移動量をなくす
	//		//		}
	//		//	}
	//		//}
	//	}
	//}

	//return bLand;   // 乗ったかどうかを返す

bool bLand = false;  // 乗ったかどうか

Player *pPlayer = GetPlayer();

for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
{// 障害物の数だけ繰り返し
	if (g_aModel[nCntModel].bUse == true)
	{// 障害物が使用されている
		if (pPos->y <= g_aModel[nCntModel].pos.y + g_aModel[nCntModel].VtxMaxModel.y && pPos->y + radius.y > g_aModel[nCntModel].pos.y + g_aModel[nCntModel].VtxMinModel.y
			|| pPos->y + radius.y > g_aModel[nCntModel].pos.y + g_aModel[nCntModel].VtxMaxModel.y && pPos->y < g_aModel[nCntModel].pos.y + g_aModel[nCntModel].VtxMinModel.y
			|| pPos->y + radius.y > g_aModel[nCntModel].pos.y + g_aModel[nCntModel].VtxMaxModel.y && pPos->y < g_aModel[nCntModel].pos.y + g_aModel[nCntModel].VtxMinModel.y)
		{// 障害物のY座標の中にいる
			if (pPos->z - radius.z <= g_aModel[nCntModel].pos.z + g_aModel[nCntModel].VtxMaxModel.z && pPos->z + radius.z >= g_aModel[nCntModel].pos.z + g_aModel[nCntModel].VtxMinModel.z)
			{// 障害物のZ座標の中にいる
				if (pPosOld->x + radius.x <= g_aModel[nCntModel].pos.x + g_aModel[nCntModel].VtxMinModel.x
					&& pPos->x + radius.x > g_aModel[nCntModel].pos.x + g_aModel[nCntModel].VtxMinModel.x)
				{// X座標の中に左から入った
				 // 跳ね返る
					//g_aModel[nCntModel].move.x += pMove->x + 5;

					pPos->x = g_aModel[nCntModel].pos.x + g_aModel[nCntModel].VtxMinModel.x - radius.x;
					pMove->x = 0.0f;
					*pModel = &g_aModel[nCntModel];
					bLand = true;
				}
				else if (pPosOld->x - radius.x >= g_aModel[nCntModel].pos.x + g_aModel[nCntModel].VtxMaxModel.x
					&& pPos->x - radius.x < g_aModel[nCntModel].pos.x + g_aModel[nCntModel].VtxMaxModel.x)
				{// X座標の中に右から入った
				 // 跳ね返る
					//g_aModel[nCntModel].move.x += pMove->x - 5;

					pPos->x = g_aModel[nCntModel].pos.x + g_aModel[nCntModel].VtxMaxModel.x + radius.x + 0.1f;
					pMove->x = 0.0f;
					*pModel = &g_aModel[nCntModel];
					bLand = true;
				}
			}
			if (pPos->x - radius.x <= g_aModel[nCntModel].pos.x + g_aModel[nCntModel].VtxMaxModel.x && pPos->x + radius.x >= g_aModel[nCntModel].pos.x + g_aModel[nCntModel].VtxMinModel.x)
			{// 障害物のX座標の中にいる
				if (pPosOld->z + radius.z <= g_aModel[nCntModel].pos.z + g_aModel[nCntModel].VtxMinModel.z
					&& pPos->z + radius.z > g_aModel[nCntModel].pos.z + g_aModel[nCntModel].VtxMinModel.z)
				{// Z座標の中に前から入った
				 // 跳ね返る
					//g_aModel[nCntModel].move.z += pMove->z + 5;

					pPos->z = g_aModel[nCntModel].pos.z + g_aModel[nCntModel].VtxMinModel.z - radius.z;
					pMove->z = 0.0f;
					*pModel = &g_aModel[nCntModel];
					bLand = true;

				}
				else if (pPosOld->z - radius.z >= g_aModel[nCntModel].pos.z + g_aModel[nCntModel].VtxMaxModel.z
					&& pPos->z - radius.z < g_aModel[nCntModel].pos.z + g_aModel[nCntModel].VtxMaxModel.z)
				{// Z座標の中に後ろから入った
				 // 跳ね返る
				//	g_aModel[nCntModel].move.z += pMove->z - 5;
					pPos->z = g_aModel[nCntModel].pos.z + g_aModel[nCntModel].VtxMinModel.z - radius.z;
					pMove->z = 0.0f;
					*pModel = &g_aModel[nCntModel];
					g_aModel[nCntModel].bUse = false;
				}
			}

			//if (pPos->x - radius.x < g_aModel[nCntModel].pos.x + g_aModel[nCntModel].VtxMaxModel.x - 2.0f&& pPos->x + radius.x > g_aModel[nCntModel].pos.x + g_aModel[nCntModel].VtxMinModel.x + 2.0f
			//	&& pPos->z - radius.z <= g_aModel[nCntModel].pos.z + g_aModel[nCntModel].VtxMaxModel.z - 2.0f && pPos->z + radius.z >= g_aModel[nCntModel].pos.z + g_aModel[nCntModel].VtxMinModel.z + 2.0f)
			//{// 障害物の内側に乗った
			//	bLand = true;  // 乗った判定を返す
			//	pPos->y = g_aModel[nCntModel].pos.y + g_aModel[nCntModel].VtxMaxModel.y;
			//	pMove->y = 0.0f;  // 移動量をなくす
			//}
		}
	}
}

return bLand;   // 乗ったかどうかを返す
}


//=============================================================================
// 設定処理
//=============================================================================
void SetModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType)
{
	int nNumVtex;	//頂点数
	DWORD sizeFvF;	//頂点フォーマットのサイズ
	BYTE *pVtxBuff[MAX_MODEL];	//頂点バッファへのポインタ
	D3DXVECTOR3 vtx[MAX_MODEL];

	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		if (g_aModel[nCntModel].bUse == false)
		{


			//for (int nCntTypeModel = 0; nCntTypeModel < MAX_MODEL_TYPE; nCntTypeModel++)
			//{
			//頂点数を取得
			nNumVtex = g_pMeshModel[nType]->GetNumVertices();
			//頂点フォーマットのサイズを取得
			sizeFvF = D3DXGetFVFVertexSize(g_pMeshModel[nType]->GetFVF());
			//	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
			//{
			//頂点　ロック
			g_pMeshModel[nType]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff[nType]);
			for (int nCntVtx = 0; nCntVtx < nNumVtex; nCntVtx++)
			{	//頂点座標の代入
				D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff[nType];
				if (g_aModel[nCntModel].VtxMinModel.x > vtx.x)
				{
					g_aModel[nCntModel].VtxMinModel.x = vtx.x;
				}
				if (g_aModel[nCntModel].VtxMinModel.y > vtx.y)
				{
					g_aModel[nCntModel].VtxMinModel.y = vtx.y;
				}
				if (g_aModel[nCntModel].VtxMinModel.z > vtx.z)
				{
					g_aModel[nCntModel].VtxMinModel.z = vtx.z;
				}

				if (g_aModel[nCntModel].VtxMaxModel.x < vtx.x)
				{
					g_aModel[nCntModel].VtxMaxModel.x = vtx.x;
				}
				if (g_aModel[nCntModel].VtxMaxModel.y < vtx.y)
				{
					g_aModel[nCntModel].VtxMaxModel.y = vtx.y;
				}
				if (g_aModel[nCntModel].VtxMaxModel.z < vtx.z)
				{
					g_aModel[nCntModel].VtxMaxModel.z = vtx.z;
				}
				pVtxBuff[nCntModel] += sizeFvF;
			}
			//			//頂点バッファをアンロック
			g_pMeshModel[nType]->UnlockVertexBuffer();
			//}
			//}
			// 位置・向きの初期設定

			g_aModel[nCntModel].pos = pos;
			g_aModel[nCntModel].rot = D3DXVECTOR3(0, 0, 0);
			g_aModel[nCntModel].fShadow = 12;
			g_aModel[nCntModel].nType = nType;
			//　影のセット
			g_aModel[nCntModel].nIdxShadow = SetShadow(g_aModel[nCntModel].pos, D3DXVECTOR3(0, 0, 0));
			g_aModel[nCntModel].bUse = true;
			break;
		}
	}
}
