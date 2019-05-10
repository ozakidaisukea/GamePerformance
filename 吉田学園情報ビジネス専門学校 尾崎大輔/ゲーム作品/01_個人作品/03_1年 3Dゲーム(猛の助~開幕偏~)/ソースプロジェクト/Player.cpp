//=============================================================================
//
// モデル処理 [Player.cpp]
// Author : Ozaki
//
//=============================================================================
#include "Player.h"
#include "Input.h"
#include "camera.h"
#include "shadow.h"
#include "bullet.h"
#include "Explosion.h"
#include "effect.h"
#include "particle.h"
#include "model.h"
#include "sound.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MOVE_PLAYER		(0.5f)
#define MOVE_BULLET		(8.0f)
#define MAX_PLAYER		(2)
//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9  g_pVtxBuffPlayer = NULL;	// 頂点バッファのポインタ
LPD3DXMESH				 g_pMeshPlayer = NULL;		// メッシュ情報へのポインタ
LPD3DXBUFFER			 g_BuffMatPlayer = NULL;	// マテリアル情報へのポインタ
D3DXVECTOR3				 g_vtxMinplayer,g_vtxMaxplayer;
DWORD					 g_nNumMatPlayer = 0;		// マテリアル情報の数
D3DXMATRIX				 g_mtxWorldPlayer;			// ワールドマトリックス
Player					 g_Player;					// プレイヤー
int						 g_nIdxShadow2;
//D3DXVECTOR3				 aPos[4];
//D3DXVECTOR3				 VecA;
//D3DXVECTOR3				 VecB;
//D3DXVECTOR3			 	 VecC;

D3DXVECTOR3				PlayerVtxMax;
D3DXVECTOR3				PlayerVtxMin;
//=============================================================================
// 初期化処理
//=============================================================================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();



	// Xファイルの読み込み
	D3DXLoadMeshFromX("data\\MODEL\\arista.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Player.aModel[0].pBuffMat,
		NULL,
		&g_Player.aModel[0].nNumMat,
		&g_Player.aModel[0].pMesh);

	D3DXLoadMeshFromX("data\\MODEL\\minigun.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Player.aModel[1].pBuffMat,
		NULL,
		&g_Player.aModel[1].nNumMat,
		&g_Player.aModel[1].pMesh);

	// 位置・向きの初期設定

	g_nIdxShadow2 = SetShadow(g_Player.pos, g_Player.rot);

	g_Player.aModel[0].nIdxModelParent = -1;
	g_Player.aModel[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	g_Player.aModel[1].nIdxModelParent = 0;
	g_Player.aModel[1].pos = D3DXVECTOR3(0.0f,35.0f, 0.0f);


	g_Player.pos = D3DXVECTOR3(0.0f, 0.0f, 500.0f);
	g_Player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.posold = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.rotmove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.bUse = true;
	g_Player.nCounterState = 0;
	g_Player.aModel[2];

	int						 nNumVtx;					// 頂点数

	DWORD					 sizeFVF;					// 頂点フォーマットの設定
	BYTE					 *pVtxBuff;					// 頂点バッハへのポインタを取得

       	nNumVtx = g_Player.aModel[0].pMesh->GetNumVertices();

	sizeFVF = D3DXGetFVFVertexSize(g_Player.aModel[0].pMesh->GetFVF());

	g_vtxMinplayer = D3DXVECTOR3(10000.0f, 10000.0f, 10000.0f);
	g_vtxMaxplayer = D3DXVECTOR3(-10000.0f, -10000.0f, -10000.0f);

	// 頂点バッファをロックし、
	g_Player.aModel[0].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	// 頂点座標の代入

		if (g_vtxMaxplayer.x < vtx.x)
		{
			g_vtxMaxplayer.x = vtx.x;
		}
		if (g_vtxMaxplayer.y < vtx.y)
		{
			g_vtxMaxplayer.y = vtx.y;
		}
		if (g_vtxMaxplayer.z < vtx.z)
		{
			g_vtxMaxplayer.z = vtx.z;
		}

		// min
		if (g_vtxMinplayer.x > vtx.x)
		{
			g_vtxMinplayer.x = vtx.x;
		}
		if (g_vtxMinplayer.y > vtx.y)
		{
			g_vtxMinplayer.y = vtx.y;
		}
		if (g_vtxMinplayer.z > vtx.z)
		{
			g_vtxMinplayer.z = vtx.z;
		}


		pVtxBuff += sizeFVF;							// サイズ分ポインタを進める

	}
	// 頂点バッファをアンロックする
	g_Player.aModel[0].pMesh->UnlockVertexBuffer();

	//// 頂点バッファをロックし、
	//g_pMeshPlayer->LockVertexBuffer(D3DLOCK_READONLY, (void**)&g_pVtxBuffPlayer);
	//
	//for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	//{
	//	D3DXVECTOR3 vtx = *(D3DXVECTOR3*)g_pVtxBuffPlayer;	// 頂点座標の代入

	//	g_pVtxBuffPlayer += sizeFVF;						// サイズ分ポインタを進める
	//}

	//// 頂点バッファをアンロックする
	//g_pMeshPlayer->UnlockVertexBuffer();


	PlayerVtxMax = D3DXVECTOR3(2.0f, 2.0f, 1.0f);
	PlayerVtxMin = D3DXVECTOR3(-2.0f, -2.0f, 0.0f);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPlayer(void)
{

	for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
	{

		// メッシュの開放
		if (g_Player.aModel[0].pMesh != NULL)
		{
			g_Player.aModel[0].pMesh->Release();

			g_Player.aModel[0].pMesh = NULL;
		}

	}
	// マテリアルの開放
	if (g_Player.aModel[0].pBuffMat != NULL)
	{
		g_Player.aModel[0].pBuffMat->Release();

		g_Player.aModel[0].pBuffMat = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePlayer(void)
{
	Camera *pCamera;
	pCamera = GetCamera();

	g_Player.posold = g_Player.pos;
	SetParticle(g_Player.pos, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0), 10.0f, 100);

	//移動処理
	if (GetKeyboardPress(DIK_W) == true)
	{//矢印の上							↓上移動
		if (GetKeyboardPress(DIK_D) == true)
		{
			g_Player.move.x += sinf((D3DX_PI * 0.25f) + pCamera->rot.y) * MOVE_PLAYER;
			g_Player.move.z += cosf((D3DX_PI * 0.25f) + pCamera->rot.y) * MOVE_PLAYER;

			//その方向に向く
			g_Player.rotmove.y = ((D3DX_PI * -0.75f) + pCamera->rot.y - g_Player.rot.y);
		}
		else if (GetKeyboardPress(DIK_A) == true)
		{
			g_Player.move.x += sinf((-D3DX_PI * 0.25f) + pCamera->rot.y) * MOVE_PLAYER;
			g_Player.move.z += cosf((-D3DX_PI * 0.25f) + pCamera->rot.y) * MOVE_PLAYER;

			//その方向に向く
			g_Player.rotmove.y = ((D3DX_PI * 0.75f) + pCamera->rot.y - g_Player.rot.y);
		}
		else
		{
			g_Player.move.x += sinf((D3DX_PI * 0.0f) + pCamera->rot.y) * MOVE_PLAYER;
			g_Player.move.z += cosf((D3DX_PI * 0.0f) + pCamera->rot.y) * MOVE_PLAYER;

			//その方向に向く
			g_Player.rotmove.y = ((D3DX_PI * -1.0f) + pCamera->rot.y - g_Player.rot.y);
		}
	}
	else if (GetKeyboardPress(DIK_S) == true)
	{//矢印の下							 ↓上移動
		if (GetKeyboardPress(DIK_D) == true)
		{
			g_Player.move.x += sinf((D3DX_PI * 0.75f) + pCamera->rot.y) * MOVE_PLAYER;
			g_Player.move.z += cosf((D3DX_PI * 0.75f) + pCamera->rot.y) * MOVE_PLAYER;

			//その方向に向く
			g_Player.rotmove.y = ((D3DX_PI * -0.25f) + pCamera->rot.y - g_Player.rot.y);
		}
		else if (GetKeyboardPress(DIK_A) == true)
		{
			g_Player.move.x += sinf((-D3DX_PI * 0.75f) + pCamera->rot.y) * MOVE_PLAYER;
			g_Player.move.z += cosf((-D3DX_PI * 0.75f) + pCamera->rot.y) * MOVE_PLAYER;

			//その方向に向く
			g_Player.rotmove.y = ((D3DX_PI * 0.25f) + pCamera->rot.y - g_Player.rot.y);
		}
		else
		{
			g_Player.move.x += sinf((-D3DX_PI * 1.0f) + pCamera->rot.y) * MOVE_PLAYER;
			g_Player.move.z += cosf((-D3DX_PI * 1.0f) + pCamera->rot.y) * MOVE_PLAYER;

			//その方向に向く
			g_Player.rotmove.y = ((D3DX_PI * 0.0f) + pCamera->rot.y - g_Player.rot.y);
		}
	}
	else if (GetKeyboardPress(DIK_D) == true)
	{//矢印の右							↓ 右移動
		g_Player.move.x += sinf((D3DX_PI * 0.5f) + pCamera->rot.y) * MOVE_PLAYER;
		g_Player.move.z += cosf((D3DX_PI * 0.5f) + pCamera->rot.y)* MOVE_PLAYER;

		//その方向に向く
		g_Player.rotmove.y = ((D3DX_PI * -0.5f) + pCamera->rot.y - g_Player.rot.y);
	}
	else if (GetKeyboardPress(DIK_A) == true)
	{//矢印の左							 ↓ 左移動
		g_Player.move.x += sinf((-D3DX_PI * 0.5f) + pCamera->rot.y) * MOVE_PLAYER;
		g_Player.move.z += cosf((-D3DX_PI * 0.5f) + pCamera->rot.y) * MOVE_PLAYER;

		//その方向に向く
		g_Player.rotmove.y = ((D3DX_PI * 0.5f) + pCamera->rot.y - g_Player.rot.y);
	}

	if (g_Player.pos.y <= 10)
	{
		/*if (GetKeyboardTrigger(DIK_SPACE) == true)
		{
		g_Player.move.y += 10.75f;
		}*/
	}
	//重力
	g_Player.move.y -= 0.65f;

	//回転の3.1415926535
	g_Player.rotmove.y = Rotover(g_Player.rotmove.y);

	//回転量の加算
	g_Player.rot.y += g_Player.rotmove.y * 0.10f;
	g_Player.rot.y = Rotover(g_Player.rot.y);

	//回転量のリセット
	g_Player.rotmove.y = 0.0f;

	//慣性
	g_Player.pos += g_Player.move;
	g_Player.move.x += (0.0f - g_Player.move.x) * 0.2f;
	g_Player.move.z += (0.0f - g_Player.move.z) * 0.2f;

	if (GetKeyboardPress(DIK_SPACE) == true)
	{// [SPACE]　弾の発射
		SetBullet(D3DXVECTOR3(g_Player.pos.x, 25.0f, g_Player.pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXVECTOR3(sinf(g_Player.rot.y - D3DX_PI)*MOVE_BULLET, 0.0f, cosf(g_Player.rot.y - D3DX_PI)*MOVE_BULLET));
		//PlaySound(SOUND_LABEL_SE_SHOT);
	}

	//CollisionModel(&g_Player.pos, &g_Player.posold, &g_Player.move, D3DXVECTOR3(50.0f, 50.0f, 50.0f),PlayerVtxMax,PlayerVtxMin, &g_Player.pModel);

	g_Player.pos.x += g_Player.move.x;
	g_Player.pos.y += g_Player.move.y;
	g_Player.pos.z += g_Player.move.z;

	g_Player.move.x += (0.0f - g_Player.move.x) *0.4f;
	g_Player.move.y += (0.0f - g_Player.move.y) *0.4f;
	g_Player.move.z += (0.0f - g_Player.move.z) *0.4f;

	if (g_Player.pos.x >= 950)
	{
		g_Player.pos.x = 950 - 1;
	}
	if (g_Player.pos.x <= -950)
	{
		g_Player.pos.x = -950 - 1;
	}
	if (g_Player.pos.z <= -950)
	{
		g_Player.pos.z = -950 - 1;
	}
	if (g_Player.pos.z >= 950)
	{
		g_Player.pos.z = 950 - 1;
	}

	if (g_Player.pos.y < 1.0f)
	{
		g_Player.pos.y = 1;
	}


	SetPostionShadow(g_nIdxShadow2, D3DXVECTOR3(g_Player.pos.x, 0, g_Player.pos.z));

	/*SetEffect(g_Player.pos.x, 0, g_Player.move.x);*/
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX		mtxRot, mtxTrans;				// 計算用のマトリックス
	D3DMATERIAL9	matDef;							// 現在のマテリアル保存用
	D3DXMATERIAL	*pMat;							// マテリアルデータへのポインタ
	D3DXMATRIX		mtxParent;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_Player.mtxWorld);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.rot.y, g_Player.rot.x, g_Player.rot.z);
	D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxRot);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTrans, g_Player.pos.x, g_Player.pos.y, g_Player.pos.z);
	D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_Player.mtxWorld);

	for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
	{
		if (g_Player.aModel[0].nIdxModelParent == -1)
		{
			mtxParent = g_Player.mtxWorld;
		}
		else
		{
			mtxParent = g_Player.aModel[g_Player.aModel[nCnt].nIdxModelParent].mtxWorld;
		}

		//if (g_Player.aModel[1].nIdxModelParent == 0)
		//{
		//	mtxParent = g_Player.mtxWorld;
		//}
		//else
		//{
		//	mtxParent = g_Player.aModel[1].mtxWorld;
		//}

		//=============================================================================
		// モデル（親）
		//=============================================================================

		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_Player.aModel[nCnt].mtxWorld);

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.aModel[nCnt].rot.y, g_Player.aModel[nCnt].rot.x, g_Player.aModel[nCnt
		].rot.z);
		D3DXMatrixMultiply(&g_Player.aModel[nCnt].mtxWorld, &g_Player.aModel[nCnt].mtxWorld, &mtxRot);

		// 移動を反映
		D3DXMatrixTranslation(&mtxTrans, g_Player.aModel[nCnt].pos.x, g_Player.aModel[nCnt].pos.y, g_Player.aModel[nCnt].pos.z);
		D3DXMatrixMultiply(&g_Player.aModel[nCnt].mtxWorld, &g_Player.aModel[nCnt].mtxWorld, &mtxTrans);


		D3DXMatrixMultiply(&g_Player.aModel[nCnt].mtxWorld, &g_Player.aModel[nCnt].mtxWorld, &mtxParent);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_Player.aModel[nCnt].mtxWorld);

		// 現在のマテリアルを取得
		pDevice->GetMaterial(&matDef);

		// マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)g_Player.aModel[nCnt].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_Player.aModel[nCnt].nNumMat; nCntMat++)
		{
			// マテリアルの設定
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			pDevice->SetTexture(0, NULL);

			// モデル(パーツ)の描画
			g_Player.aModel[nCnt].pMesh->DrawSubset(nCntMat);

		}

		// マテリアルをデフォルトに戻す
		pDevice->SetMaterial(&matDef);
	}
}

//=============================================================================
// モデルの取得
//=============================================================================
Player *GetPlayer(void)
{
	return &g_Player;
}

//=============================================================================
// プレイヤーの当たり判定
//=============================================================================
bool CollisionPlayer(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 radius, MODEL **pPlayer)
{
	bool bLand = false;  // 乗ったかどうか

	/*Model1 *pPlayer = GetPlayer();*/

	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{// 障害物の数だけ繰り返し
		if (g_Player.bUse == true)
		{// 障害物が使用されている
			if (pPos->y <= g_Player.pos.y + g_Player.VtxMaxModel.y && pPos->y + radius.y > g_Player.pos.y + g_Player.VtxMinModel.y
				|| pPos->y + radius.y > g_Player.pos.y + g_Player.VtxMaxModel.y && pPos->y < g_Player.pos.y + g_Player.VtxMinModel.y
				|| pPos->y + radius.y > g_Player.pos.y + g_Player.VtxMaxModel.y && pPos->y < g_Player.pos.y + g_Player.VtxMinModel.y)
			{// 障害物のY座標の中にいる
				if (pPos->z - radius.z <= g_Player.pos.z + g_Player.VtxMaxModel.z && pPos->z + radius.z >= g_Player.pos.z + g_Player.VtxMinModel.z)
				{// 障害物のZ座標の中にいる
					if (pPosOld->x + radius.x <= g_Player.pos.x + g_Player.VtxMinModel.x
						&& pPos->x + radius.x > g_Player.pos.x + g_Player.VtxMinModel.x)
					{// X座標の中に左から入った
					 // 跳ね返る
						g_Player.move.x += pMove->x + 5;

						pPos->x = g_Player.pos.x + g_Player.VtxMinModel.x - radius.x;
						pMove->x = -4.0f;

						bLand = true;
					}
					else if (pPosOld->x - radius.x >= g_Player.pos.x + g_Player.VtxMaxModel.x
						&& pPos->x - radius.x < g_Player.pos.x + g_Player.VtxMaxModel.x)
					{// X座標の中に右から入った
					 // 跳ね返る
						g_Player.move.x += pMove->x - 5;

						pPos->x = g_Player.pos.x + g_Player.VtxMaxModel.x + radius.x + 0.1f;
						pMove->x = 4.0f;

						bLand = true;
					}
				}
				if (pPos->x - radius.x <= g_Player.pos.x + g_Player.VtxMaxModel.x && pPos->x + radius.x >= g_Player.pos.x + g_Player.VtxMinModel.x)
				{// 障害物のX座標の中にいる
					if (pPosOld->z + radius.z <= g_Player.pos.z + g_Player.VtxMinModel.z
						&& pPos->z + radius.z > g_Player.pos.z + g_Player.VtxMinModel.z)
					{// Z座標の中に前から入った
					 // 跳ね返る
						g_Player.move.z += pMove->z + 5;

						pPos->z = g_Player.pos.z + g_Player.VtxMinModel.z - radius.z;
						pMove->z = -4.0f;

						bLand = true;
					}
					else if (pPosOld->z - radius.z >= g_Player.pos.z + g_Player.VtxMaxModel.z
						&& pPos->z - radius.z < g_Player.pos.z + g_Player.VtxMaxModel.z)
					{// Z座標の中に後ろから入った
					 // 跳ね返る
						g_Player.move.z += pMove->z - 5;

						pPos->z = g_Player.pos.z + g_Player.VtxMaxModel.z + radius.z + 0.1f;
						pMove->z = 4.0f;

						bLand = true;
					}
				}

				//if (pPos->x - radius.x < g_Player.pos.x + g_Player.VtxMaxModel.x - 2.0f&& pPos->x + radius.x > g_Player.pos.x + g_Player.VtxMinModel.x + 2.0f
				//	&& pPos->z - radius.z <= g_Player.pos.z + g_Player.VtxMaxModel.z - 2.0f && pPos->z + radius.z >= g_Player.pos.z + g_Player.VtxMinModel.z + 2.0f)
				//{// 障害物の内側に乗った
				//	bLand = true;  // 乗った判定を返す
				//	pPos->y = g_Player.pos.y + g_Player.VtxMaxModel.y;
				//	pMove->y = 0.0f;  // 移動量をなくす
				//}
			}
		}
	}

	return bLand;   // 乗ったかどうかを返す
}