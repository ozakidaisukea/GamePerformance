//=============================================================================
//
// ポリゴン処理 [billboard.cpp]
// Author : Ozaki
//
//=============================================================================
#include "billboard.h"
#include "shadow.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_FOER		(4)
#define BILLTEXTURENAME		"data\\TEXTURE\\bullet000.png"	// テクスチャ名

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexBillboard(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9	   g_pVtxBuffBillboard = NULL;		// 頂点バッファのポインタ
LPDIRECT3DTEXTURE9		   g_pTextureBillboard = NULL;		// テクスチャへのポインタ
Billboard				   g_aBillboard[MAX_BILLBOARD];
int						   g_nIdxShadow;

//=============================================================================
// 初期化処理
//=============================================================================
void InitBillboard(void)
{
	//LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;	// デバイスへのポインタ
	pDevice = GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, BILLTEXTURENAME, &g_pTextureBillboard);

	// 頂点情報の作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MAX_FOER * MAX_BILLBOARD,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBillboard,
		NULL);

	VERTEX_3D* pVtx; //頂点情報のポインタ


					 // 頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
	{
		// 頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-15.0, 20.0, -0);
		pVtx[1].pos = D3DXVECTOR3(15.0, 20.0, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-15.0, -0, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(15.0, -0, 0.0f);

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
	g_pVtxBuffBillboard->Unlock();

	for (int nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
	{
		g_aBillboard[nCntBillboard].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBillboard[nCntBillboard].movve = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBillboard[nCntBillboard].bUse = false;
	}
	g_nIdxShadow = SetShadow(g_aBillboard[0].pos, g_aBillboard[0].rot);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitBillboard(void)
{
	// 頂点バッファの開放
	if (g_pVtxBuffBillboard != NULL)
	{
		g_pVtxBuffBillboard->Release();
		g_pVtxBuffBillboard = NULL;
	}

	if (g_pTextureBillboard != NULL)
	{
		g_pTextureBillboard->Release();
		g_pTextureBillboard = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateBillboard(void)
{
	/*SetPostionShadow(g_nIdxShadow, D3DXVECTOR3(g_aBillboard[0].pos.x, 0,
		g_aBillboard[0].pos.z));*/
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawBillboard(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans, mtxView;


	for (int nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
	{

		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_aBillboard[nCntBillboard].mtxWorld);

		//
		pDevice->GetTransform(D3DTS_VIEW, &mtxView);
		g_aBillboard[nCntBillboard].mtxWorld._11 = mtxView._11;
		g_aBillboard[nCntBillboard].mtxWorld._12 = mtxView._21;
		g_aBillboard[nCntBillboard].mtxWorld._13 = mtxView._31;
		g_aBillboard[nCntBillboard].mtxWorld._21 = mtxView._12;
		g_aBillboard[nCntBillboard].mtxWorld._22 = mtxView._22;
		g_aBillboard[nCntBillboard].mtxWorld._23 = mtxView._32;
		g_aBillboard[nCntBillboard].mtxWorld._31 = mtxView._13;
		g_aBillboard[nCntBillboard].mtxWorld._32 = mtxView._23;
		g_aBillboard[nCntBillboard].mtxWorld._33 = mtxView._33;

		// 位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_aBillboard[nCntBillboard].pos.x, g_aBillboard[nCntBillboard].pos.y, g_aBillboard[nCntBillboard].pos.z);
		D3DXMatrixMultiply(&g_aBillboard[nCntBillboard].mtxWorld, &g_aBillboard[nCntBillboard].mtxWorld, &mtxTrans);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_aBillboard[nCntBillboard].mtxWorld);

		// 頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffBillboard, 0, sizeof(VERTEX_3D));

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pTextureBillboard);

		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

		if (g_aBillboard[nCntBillboard].bUse == true)
		{
			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0 + (4 * nCntBillboard), 2);
		}

		// レンダーステートを元に戻す
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	}
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexBillboard(LPDIRECT3DDEVICE9 pDevice)
{

}
//=============================================================================
// 壁の設定位置
//=============================================================================
void SetBillboard(D3DXVECTOR3 posBillboard, D3DXVECTOR3 rotBillboard)
{
	int nCntBillboard;

	for (nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
	{
		if (g_aBillboard[nCntBillboard].bUse == false)
		{
			g_aBillboard[nCntBillboard].pos = posBillboard;
			g_aBillboard[nCntBillboard].movve = rotBillboard;
			g_aBillboard[nCntBillboard].bUse = true;
			break;
		}
	}
}