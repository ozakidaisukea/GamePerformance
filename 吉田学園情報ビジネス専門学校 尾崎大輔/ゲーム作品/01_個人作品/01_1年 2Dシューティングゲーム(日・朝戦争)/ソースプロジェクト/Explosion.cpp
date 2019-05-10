//=============================================================================
//
// 弾処理 [explosion.cpp]
// Author : ozaki
//
//=============================================================================
#include "Explosion.h"
#include "sound.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MAX_EXPLOSION		(128)		// 爆発の最大数
#define MAX_MIKY			(150)
//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;				//位置
	D3DXCOLOR col;					//色
	int nCounterAnim;				//アニメーションカウンター
	int nPatternAnim;				//アニメーションパターン
	bool bUse;						//使用しているか
}Explosion;

//*****************************************************************************
// グローバル変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureExplosion = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL;	// 頂点バッファへのポインタ
Explosion g_aExplosion[MAX_EXPLOSION];				// 爆発の情報

//=============================================================================
// 初期化処理
//=============================================================================
void InitExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D*pVtx;														//頂点情報へのポインタ
	int nCntExplosion;
	//デヴァイスを取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\explosion000.png",
		&g_pTextureExplosion);


	// 弾の情報の初期化
	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		g_aExplosion[nCntExplosion].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aExplosion[nCntExplosion].col = D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f);
		g_aExplosion[nCntExplosion].bUse = false;
	}

	// 頂点情報の作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_EXPLOSION,
		D3DUSAGE_WRITEONLY,
		FVF_VRETEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffExplosion,
		NULL);

	////頂点バッファをロックし、頂点データのポインタの取得
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - MAX_MIKY, g_aExplosion[nCntExplosion].pos.y - MAX_MIKY, g_aExplosion[nCntExplosion].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + MAX_MIKY, g_aExplosion[nCntExplosion].pos.y - MAX_MIKY, g_aExplosion[nCntExplosion].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - MAX_MIKY, g_aExplosion[nCntExplosion].pos.y + MAX_MIKY, g_aExplosion[nCntExplosion].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + MAX_MIKY, g_aExplosion[nCntExplosion].pos.y + MAX_MIKY, g_aExplosion[nCntExplosion].pos.z);

		//テクスチャの設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.125f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.125f,  1.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		pVtx += 4;					//頂点データのポインタを4つ分進める
	}
	//頂点バッファをアンロック
		g_pVtxBuffExplosion->Unlock();
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitExplosion(void)
{
	// テクスチャの開放
	if (g_pTextureExplosion != NULL)
	{
		g_pTextureExplosion->Release();
		g_pTextureExplosion = NULL;
	}

	// 頂点バッファの開放
	if (g_pVtxBuffExplosion != NULL)
	{
		g_pVtxBuffExplosion->Release();
		g_pVtxBuffExplosion = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateExplosion(void)
{
	int nCntExplosion;
	VERTEX_2D*pVtx;
												//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データのポインタの取得
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == true)
		{
			g_aExplosion[nCntExplosion].nCounterAnim++;
			if ((g_aExplosion[nCntExplosion].nCounterAnim % 5) == 0)
			{
				g_aExplosion[nCntExplosion].nPatternAnim = (g_aExplosion[nCntExplosion].nPatternAnim + 1 % 8);
				//g_aExplosion[nCntExplosion].pos.y -= 10.0f;
				//頂点座標の設定
				pVtx[0].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - MAX_MIKY, g_aExplosion[nCntExplosion].pos.y - MAX_MIKY, g_aExplosion[nCntExplosion].pos.z);
				pVtx[1].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + MAX_MIKY, g_aExplosion[nCntExplosion].pos.y - MAX_MIKY, g_aExplosion[nCntExplosion].pos.z);
				pVtx[2].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - MAX_MIKY, g_aExplosion[nCntExplosion].pos.y + MAX_MIKY, g_aExplosion[nCntExplosion].pos.z);
				pVtx[3].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + MAX_MIKY, g_aExplosion[nCntExplosion].pos.y + MAX_MIKY, g_aExplosion[nCntExplosion].pos.z);

				//テクスチャの設定
				pVtx[0].tex.x = (0.0f + (0.125f * (g_aExplosion[nCntExplosion].nPatternAnim % 8)));
				pVtx[0].tex.y = (0.0f + 1.0f);

				pVtx[1].tex.x = (0.125f + (0.125f * (g_aExplosion[nCntExplosion].nPatternAnim % 8)));
				pVtx[1].tex.y = (0.0f + 1.0f);

				pVtx[2].tex.x = (0.0f + (0.125f * (g_aExplosion[nCntExplosion].nPatternAnim % 8)));
				pVtx[2].tex.y = (1.0f + 1.0f);

				pVtx[3].tex.x = (0.125f + (0.125f * (g_aExplosion[nCntExplosion].nPatternAnim % 8)));
				pVtx[3].tex.y = (1.0f + 1.0f);

				if (g_aExplosion[nCntExplosion].nPatternAnim >= 8)
				{
					g_aExplosion[nCntExplosion].bUse = false;
				}
			}
		}
		pVtx += 4;
	}

	//頂点バッファをアンロック
	g_pVtxBuffExplosion->Unlock();

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntExplosion;

	//デヴァイスを取得
	pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
    pDevice->SetStreamSource(0, g_pVtxBuffExplosion, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VRETEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureExplosion);

	// ポリゴンの描画
	for(nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == true)
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
									0 +(4 * nCntExplosion),
									2);
		}
	}
}

//=============================================================================
// 弾の設定処理
//=============================================================================
void SetExplosion(D3DXVECTOR3 pos, D3DXCOLOR col)
{
	int nCntExplosion;
	VERTEX_2D*pVtx;														//頂点情報へのポインタ

	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == false)		//弾が使用されている
		{
			g_aExplosion[nCntExplosion].pos = pos;
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - MAX_MIKY, g_aExplosion[nCntExplosion].pos.y - MAX_MIKY, g_aExplosion[nCntExplosion].pos.z);
			pVtx[1].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + MAX_MIKY, g_aExplosion[nCntExplosion].pos.y - MAX_MIKY, g_aExplosion[nCntExplosion].pos.z);
			pVtx[2].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - MAX_MIKY, g_aExplosion[nCntExplosion].pos.y + MAX_MIKY, g_aExplosion[nCntExplosion].pos.z);
			pVtx[3].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + MAX_MIKY, g_aExplosion[nCntExplosion].pos.y + MAX_MIKY, g_aExplosion[nCntExplosion].pos.z);

			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);

			g_aExplosion[nCntExplosion].nCounterAnim = 0;
			g_aExplosion[nCntExplosion].nPatternAnim = 0;
			g_aExplosion[nCntExplosion].bUse = true;
			break;
		}
		pVtx += 4;
	}
	g_pVtxBuffExplosion->Unlock();
}