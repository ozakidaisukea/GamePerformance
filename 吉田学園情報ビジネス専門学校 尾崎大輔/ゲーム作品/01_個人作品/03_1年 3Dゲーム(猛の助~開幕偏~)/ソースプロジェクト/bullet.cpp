//=============================================================================
//
// ポリゴン処理 [Bullet.cpp]
// Author : Ozaki
//
//=============================================================================
#include "bullet.h"
//#include "shadow.h"
#include "Explosion.h"
#include "effect.h"
#include "model.h"
#include "Score.h"
#include "sound.h"
#include "Fade.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_FOER		(4)
#define BILLTEXTURENAME		"data\\TEXTURE\\bullet000.png"	// テクスチャ名
#define BULLET_MOVE		(20)
//#define MAX_SHADOW		(256)
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexBullet(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;		// 頂点バッファのポインタ
LPDIRECT3DTEXTURE9		g_pTextureBullet = NULL;		// テクスチャへのポインタ
BULLET					g_aBullet[MAX_BULLET];

D3DXVECTOR3				aPos[4];
D3DXVECTOR3				VecA;
D3DXVECTOR3				VecB;
D3DXVECTOR3				VecC;
D3DXVECTOR3				BulletVtxMax;
D3DXVECTOR3				BulletVtxMin;

int						takumi;

//=============================================================================
// 初期化処理
//=============================================================================
void InitBullet(void)
{
	//LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;	// デバイスへのポインタ
	pDevice = GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, BILLTEXTURENAME, &g_pTextureBullet);
	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(-10.0f, 15.0f, 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].nLife = 0;
		g_aBullet[nCntBullet].bUse = false;
	}

	// 頂点情報の作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MAX_FOER * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL);

	VERTEX_3D* pVtx; //頂点情報のポインタ

	// 頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		// 頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-2.0, 2.0, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(2.0, 2.0, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-2.0, 0.0, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(2.0, 0.0, 0.0f);

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

		pVtx += 4;					//頂点データのポインタを4つ分進める

	}
	//頂点バッファをアンロックドする
	g_pVtxBuffBullet->Unlock();

	//g_nIdxShadow2 = SetShadow(g_aBullet[MAX_BULLET].pos, g_aBullet[MAX_BULLET].move);

	aPos[0] = D3DXVECTOR3(-1000, 0, 1000);
	aPos[1] = D3DXVECTOR3(1000, 0, 1000);
	aPos[2] = D3DXVECTOR3(1000, 0, -1000);
	aPos[3] = D3DXVECTOR3(-1000, 0, -1000);

	BulletVtxMax = D3DXVECTOR3(2.0f, 2.0f, 1.0f);
	BulletVtxMin = D3DXVECTOR3(-2.0f, -2.0f, 0.0f);

	takumi = 0;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitBullet(void)
{
	// 頂点バッファの開放
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}

	if (g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateBullet(void)
{
	int nCntBullet;

	VERTEX_3D*pVtx;	//頂点情報へのポインタ

	MODEL *pModel;
	pModel = GetModel();

	FADE Fade;
	Fade = GetFade();

	//頂点バッファをロックし、頂点データのポインタの取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{
			g_aBullet[nCntBullet].posold = g_aBullet[nCntBullet].pos;

			g_aBullet[nCntBullet].pos += g_aBullet[nCntBullet].move;
			//SetPostionShadow(g_aBullet[nCntBullet].nIdxShadow, D3DXVECTOR3(g_aBullet[nCntBullet].pos.x, 0, g_aBullet[nCntBullet].pos.z));

			g_aBullet[nCntBullet].nLife--;

			// 弾の寿命
			if (g_aBullet[nCntBullet].nLife <= 0)
			{
				g_aBullet[nCntBullet].bUse = false;
				//DeleteShadow(g_aBullet[nCntBullet].nIdxShadow);
				SetExplosion(g_aBullet[nCntBullet].pos, D3DXVECTOR3(0.0f,0.0f,0.0f),D3DXCOLOR(1.0f, 0.0f, 0.0f,1.0f));
			}

			if (pModel->bUse == true)
			{
				pModel->pos.x < g_aBullet[nCntBullet].pos.x && pModel->pos.x > g_aBullet[nCntBullet].pos.x
					&& pModel->pos.z < g_aBullet[nCntBullet].pos.z && pModel->pos.z > g_aBullet[nCntBullet].pos.z;
			}

			if (CollisionModel(&g_aBullet[nCntBullet].pos, &g_aBullet[nCntBullet].posold, &g_aBullet[nCntBullet].move,D3DXVECTOR3(10.0f, 10.0f, 10.0f), BulletVtxMax,BulletVtxMin,&g_aBullet[nCntBullet].pModel) == true)
			{
				g_aBullet[nCntBullet].bUse = false;
				SetExplosion(g_aBullet[nCntBullet].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
				AddScore(100);

				g_aBullet[nCntBullet].pModel->nLife -= 1;
						if (g_aBullet[nCntBullet].pModel->nLife <= 0)
						{
							SetExplosion(g_aBullet[nCntBullet].pModel->pos, g_aBullet[nCntBullet].pModel->rot,D3DXCOLOR(1.0f,0.0f,1.0,0.0f));
							PlaySound(SOUND_LABEL_SE_EXPLOSION);
							g_aBullet[nCntBullet].pModel->bUse = false;
							//AddScore(10000);
							//SetGameState(GAMESTATE_END);
							//SetFade(MODE_RESULT);
 							takumi++;
						}

						if (takumi == 4)
						{
							SetFade(MODE_RESULT);
						}
			}

			// 壁の当たり判定
		/*	if (g_aBullet[nCntBullet].pos.x >= 1000)
			{
				g_aBullet[nCntBullet].pos.x = 1000 - 1;
				g_aBullet[nCntBullet].bUse = false;
				DeleteShadow(g_aBullet[nCntBullet].nIdxShadow);
				SetExplosion(g_aBullet[nCntBullet].pos, D3DXVECTOR3(1.0f, 0.0f, 0.0f));

			}
			if (g_aBullet[nCntBullet].pos.x <= -1000)
			{
				g_aBullet[nCntBullet].pos.x = -1000 - 1;
				g_aBullet[nCntBullet].bUse = false;
				DeleteShadow(g_aBullet[nCntBullet].nIdxShadow);
				SetExplosion(g_aBullet[nCntBullet].pos, D3DXVECTOR3(1.0f, 0.0f, 0.0f));
			}
			if (g_aBullet[nCntBullet].pos.z <= -1000)
			{
				g_aBullet[nCntBullet].pos.z = -1000 - 1;
				g_aBullet[nCntBullet].bUse = false;
				DeleteShadow(g_aBullet[nCntBullet].nIdxShadow);
				SetExplosion(g_aBullet[nCntBullet].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			}
			if (g_aBullet[nCntBullet].pos.z >= 1000)
			{
				g_aBullet[nCntBullet].pos.z = 1000 - 1;
				g_aBullet[nCntBullet].bUse = false;
				DeleteShadow(g_aBullet[nCntBullet].nIdxShadow);
				SetExplosion(g_aBullet[nCntBullet].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			}*/
			float fgsk[4];

			// 奥
			VecA = aPos[0] - aPos[1];
			VecC = g_aBullet[nCntBullet].pos - aPos[0];
			fgsk[0] = ((VecA.z * VecC.x) - (VecA.x * VecC.z));
			if (fgsk[0] > 0)
			{
				g_aBullet[nCntBullet].bUse = false;
				//DeleteShadow(g_aBullet[nCntBullet].nIdxShadow);
				SetExplosion(g_aBullet[nCntBullet].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
			}

			// 手前
			VecA = aPos[0] - aPos[1];
			VecC = g_aBullet[nCntBullet].pos - aPos[0];
			fgsk[1] = ((VecA.z * VecC.x) - (VecA.x * VecC.z));
			if (fgsk[1] > 0)
			{
				g_aBullet[nCntBullet].bUse = false;
				//DeleteShadow(g_aBullet[nCntBullet].nIdxShadow);
				SetExplosion(g_aBullet[nCntBullet].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
			}

			// 右
			VecA = aPos[0] - aPos[1];
			VecC = g_aBullet[nCntBullet].pos - aPos[0];
			fgsk[2] = ((VecA.z * VecC.x) - (VecA.x * VecC.z));
			if (fgsk[2] > 0)
			{
				g_aBullet[nCntBullet].bUse = false;
				//DeleteShadow(g_aBullet[nCntBullet].nIdxShadow);
				SetExplosion(g_aBullet[nCntBullet].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
			}

			// 左
			VecA = aPos[0] - aPos[1];
			VecC = g_aBullet[nCntBullet].pos - aPos[0];
			fgsk[3] = ((VecA.z * VecC.x) - (VecA.x * VecC.z));
			if (fgsk[3] > 0)
			{
				g_aBullet[nCntBullet].bUse = false;
				//DeleteShadow(g_aBullet[nCntBullet].nIdxShadow);
				SetExplosion(g_aBullet[nCntBullet].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
			}

			VecA = aPos[0] - aPos[1];
			VecC = g_aBullet[nCntBullet].pos - aPos[0];
			fgsk[0] = ((VecA.z * VecC.x) - (VecA.x * VecC.z));
			if (fgsk[0] > 0)
			{
				g_aBullet[nCntBullet].bUse = false;
			//	DeleteShadow(g_aBullet[nCntBullet].nIdxShadow);
				SetExplosion(g_aBullet[nCntBullet].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
			}
			SetEffect(g_aBullet[nCntBullet].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, 0);
		}

		pVtx += 4;
	}
	//頂点バッファをアンロック
	g_pVtxBuffBullet->Unlock();


}

//=============================================================================
// 描画処理
//=============================================================================
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans, mtxView;
	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_3D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{

		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_aBullet[nCntBullet].mtxWorld);

		//
		pDevice->GetTransform(D3DTS_VIEW, &mtxView);
		g_aBullet[nCntBullet].mtxWorld._11 = mtxView._11;
		g_aBullet[nCntBullet].mtxWorld._12 = mtxView._21;
		g_aBullet[nCntBullet].mtxWorld._13 = mtxView._31;
		g_aBullet[nCntBullet].mtxWorld._21 = mtxView._12;
		g_aBullet[nCntBullet].mtxWorld._22 = mtxView._22;
		g_aBullet[nCntBullet].mtxWorld._23 = mtxView._32;
		g_aBullet[nCntBullet].mtxWorld._31 = mtxView._13;
		g_aBullet[nCntBullet].mtxWorld._32 = mtxView._23;
		g_aBullet[nCntBullet].mtxWorld._33 = mtxView._33;

		// 位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_aBullet[nCntBullet].pos.x, g_aBullet[nCntBullet].pos.y, g_aBullet[nCntBullet].pos.z);
		D3DXMatrixMultiply(&g_aBullet[nCntBullet].mtxWorld, &g_aBullet[nCntBullet].mtxWorld, &mtxTrans);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_aBullet[nCntBullet].mtxWorld);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pTextureBullet);

		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

		if (g_aBullet[nCntBullet].bUse == true)
		{
			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0 + (4 * nCntBullet), 2);
		}

		// レンダーステートを元に戻す
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	}
}
//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexBullet(LPDIRECT3DDEVICE9 pDevice)
{

}
//=============================================================================
// 壁の設定位置
//=============================================================================
void SetBullet(D3DXVECTOR3 posbullet, D3DXVECTOR3 rotbullet, D3DXVECTOR3 movebullet )
{
	int nCntBullet;


	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == false)
		{
			g_aBullet[nCntBullet].pos = posbullet;
			g_aBullet[nCntBullet].move = movebullet;
 		//	g_aBullet[nCntBullet].nIdxShadow = SetShadow(g_aBullet[nCntBullet].pos, D3DXVECTOR3(0.0,0.0,0.0f));
			g_aBullet[nCntBullet].nLife = 100;
			g_aBullet[nCntBullet].bUse = true;
			break;
		}
	}
}