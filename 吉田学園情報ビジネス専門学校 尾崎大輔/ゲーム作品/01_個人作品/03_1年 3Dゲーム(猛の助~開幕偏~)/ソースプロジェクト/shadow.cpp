//=============================================================================
//
// 影の処理 [shadoe.cpp]
// Author : Ozaki
//
//=============================================================================
#include "shadow.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_FOER		(4)
#define ENTER_TEXTURENAME		"data\\TEXTURE\\shadow000.jpg"	// テクスチャ名
#define MAX_SHADOW		(100)
//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;			// 位置
	D3DXVECTOR3	rot;			// 向き
	D3DXMATRIX	mtxWorld;		//
	D3DXCOLOR	col;			// 色
	float		fRadius;		// 半径(大きさ)
	bool		bUse;			// 使用しているかどうか
}SHADOW;
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexShadow(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffShadow = NULL;		// 頂点バッファのポインタ
LPDIRECT3DTEXTURE9		g_pTextureShadow = NULL;		// テクスチャへのポインタ
//D3DXVECTOR3				g_posShadow;					// 位置
//D3DXVECTOR3				g_rotShadow;					// 向き
//D3DXMATRIX				g_aShadow[nCntShadow].mtxWorld;				// ワールドマトリックス
SHADOW					g_aShadow[MAX_SHADOW];
//=============================================================================
// 初期化処理
//=============================================================================
void InitShadow(void)
{
	//LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;	// デバイスへのポインタ
	pDevice = GetDevice();

	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		g_aShadow[nCntShadow].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aShadow[nCntShadow].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aShadow[nCntShadow].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}
	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, ENTER_TEXTURENAME, &g_pTextureShadow);

	// 頂点情報の作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MAX_FOER * MAX_SHADOW,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffShadow,
		NULL);
	VERTEX_3D* pVtx;			//頂点情報のポインタ

	// 頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		// 頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-12.5, 0.0, 12.5);
		pVtx[1].pos = D3DXVECTOR3(12.5, 0.0, 12.5);
		pVtx[2].pos = D3DXVECTOR3(-12.5, 0.0, -12.5);
		pVtx[3].pos = D3DXVECTOR3(12.5, 0.0, -12.5);

		// 法線情報
		pVtx[0].nor = D3DXVECTOR3(0, 1, 0);
		pVtx[1].nor = D3DXVECTOR3(0, 1, 0);
		pVtx[2].nor = D3DXVECTOR3(0, 1, 0);
		pVtx[3].nor = D3DXVECTOR3(0, 1, 0);

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
	g_pVtxBuffShadow->Unlock();

}

//=============================================================================
// 終了処理
//=============================================================================
void UninitShadow(void)
{
	// 頂点バッファの開放
	if (g_pVtxBuffShadow != NULL)
	{
		g_pVtxBuffShadow->Release();
		g_pVtxBuffShadow = NULL;
	}

	if (g_pTextureShadow != NULL)
	{
		g_pTextureShadow->Release();
		g_pTextureShadow = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateShadow(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DXMATRIX mtxRot[MAX_SHADOW], mtxTrans[MAX_SHADOW];

	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);


	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{

		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_aShadow[nCntShadow].mtxWorld);

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot[nCntShadow], g_aShadow[nCntShadow].rot.y, g_aShadow[nCntShadow].rot.x, g_aShadow[nCntShadow].rot.z);
		D3DXMatrixMultiply(&g_aShadow[nCntShadow].mtxWorld, &g_aShadow[nCntShadow].mtxWorld, &mtxRot[nCntShadow]);

		// 位置を反映
		D3DXMatrixTranslation(&mtxTrans[nCntShadow], g_aShadow[nCntShadow].pos.x, g_aShadow[nCntShadow].pos.y, g_aShadow[nCntShadow].pos.z);
		D3DXMatrixMultiply(&g_aShadow[nCntShadow].mtxWorld, &g_aShadow[nCntShadow].mtxWorld, &mtxTrans[nCntShadow]);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_aShadow[nCntShadow].mtxWorld);

		// 頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffShadow, 0, sizeof(VERTEX_3D));

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);
		if (g_aShadow[nCntShadow].bUse == true)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, g_pTextureShadow);

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0 + (4 * nCntShadow), 2);
		}
	}
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexShadow(LPDIRECT3DDEVICE9 pDevice)
{
}

//=============================================================================
// 影の設定
//=============================================================================
int SetShadow(D3DXVECTOR3 pos,D3DXVECTOR3 rot)
{
	int nCntShadow;
	VERTEX_3D*pVtx;					//頂点情報へのポインタ

	// 頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (g_aShadow[nCntShadow].bUse == false)
		{
			g_aShadow[nCntShadow].pos = pos;
			g_aShadow[nCntShadow].rot = rot;

			// 頂点座標の設定
			/*pVtx[0].pos = D3DXVECTOR3(-12.5, 0.0, 12.5);
			pVtx[1].pos = D3DXVECTOR3(12.5, 0.0, 12.5);
			pVtx[2].pos = D3DXVECTOR3(-12.5, 0.0, -12.5);
			pVtx[3].pos = D3DXVECTOR3(12.5, 0.0, -12.5);*/

			g_aShadow[nCntShadow].bUse = true;
			break;
		}
		pVtx += 4;					//頂点データのポインタを4つ分進める
	}
	return nCntShadow;				// 使用している影の番号(インデックス)を返す

	//頂点バッファをアンロックドする
	g_pVtxBuffShadow->Unlock();
}
//=============================================================================
// 影の位置を設定
//=============================================================================
void SetPostionShadow(int nIdxShadow, D3DXVECTOR3 pos)
{
	g_aShadow[nIdxShadow].pos = pos;
}
//=============================================================================
// 影の削除
//=============================================================================
void DeleteShadow(int nIdxShadow)
{
	g_aShadow[nIdxShadow].bUse = false;
}