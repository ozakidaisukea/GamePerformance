//=============================================================================
//
// ポーズメニュー処理 [pauseselect.cpp]
// Author : Mikiya Meguro
//
//=============================================================================
#include "input.h"
#include "fade.h"
#include "pausemenu.h"
#include "sound.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_CONTINUE		"data/TEXTURE/pause000.png"	// 読み込むテクスチャファイル名
#define	TEXTURE_RETRY			"data/TEXTURE/pause001.png"	// 読み込むテクスチャファイル名
#define	TEXTURE_QUIT			"data/TEXTURE/pause002.png"	// 読み込むテクスチャファイル名
#define POLYGON_POS_X			(200)						//頂点座標Xの移動量
#define POLYGON_POS_Y			(50)						//頂点座標Yの移動量
#define TEX_POS_X_INIT			(1.0f)						//テクスチャ座標Uの初期位置
#define TEX_POS_Y_INIT			(1.0f)						//テクスチャ座標Vの初期位置
#define TEX_LEFT				(0.0f)						//テクスチャ座標U左
#define TEX_RIGHT				(1.0f)						//テクスチャ座標U右
#define TEX_TOP					(0.0f)						//テクスチャ座標V上
#define TEX_BOT					(1.0f)						//テクスチャ座標V下
#define MAX_PAUSEMENU			(3)							//ランキングの数

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexPauseSelect(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTexturePauseSelect[MAX_PAUSEMENU] = {};		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPauseSelect = NULL;					// 頂点バッファへのポインタ
PAUSESELECT				g_aPauseMenu[MAX_PAUSEMENU];					// ポーズメニュー
D3DXVECTOR3				g_PauseMenuPos(0.0f, 0.0f, 0.0f);
SELECTMODE				g_SelectMode = SELECTMODE_NONE;
int						nSelect = 0;
					
//=============================================================================
// 初期化処理
//=============================================================================
void InitPauseSelect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	float fMenuPosY = 0;
	nSelect = 0;

	g_SelectMode = SELECTMODE_NONE;

	g_aPauseMenu[0].pos = D3DXVECTOR3(650.0f, 200.0f + (fMenuPosY), 0.0f);;
	g_aPauseMenu[0].col = D3DXCOLOR(0.0f, 0.5f, 1.0f, 1.0f);
	g_aPauseMenu[0].select = SELECTTYPE_SELECT;
	fMenuPosY += 150;
	for (int nCnt = 1; nCnt < MAX_PAUSEMENU; nCnt++)
	{
		g_aPauseMenu[nCnt].pos = D3DXVECTOR3(650.0f, 200.0f + (fMenuPosY), 0.0f);;
		g_aPauseMenu[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aPauseMenu[nCnt].select = SELECTTYPE_NONE;
		fMenuPosY += 150;
	}

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,			// デバイスへのポインタ
		TEXTURE_CONTINUE,						// ファイルの名前
		&g_pTexturePauseSelect[0]);				// テクスチャへのポインタ


	D3DXCreateTextureFromFile(pDevice,			// デバイスへのポインタ
		TEXTURE_RETRY,							// ファイルの名前
		&g_pTexturePauseSelect[1]);				// テクスチャへのポインタ

	D3DXCreateTextureFromFile(pDevice,			// デバイスへのポインタ
		TEXTURE_QUIT,							// ファイルの名前
		&g_pTexturePauseSelect[2]);				// テクスチャへのポインタ

												// 頂点情報の作成
	MakeVertexPauseSelect(pDevice);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPauseSelect(void)
{
	for (int nCnt = 0; nCnt < MAX_PAUSEMENU; nCnt++)
	{// テクスチャの開放
		if (g_pTexturePauseSelect[nCnt] != NULL)
		{
			g_pTexturePauseSelect[nCnt]->Release();
			g_pTexturePauseSelect[nCnt] = NULL;
		}
	}
	// 頂点バッファの開放
	if (g_pVtxBuffPauseSelect != NULL)
	{
		g_pVtxBuffPauseSelect->Release();
		g_pVtxBuffPauseSelect = NULL;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePauseSelect(void)
{
	// 頂点情報の作成
	VERTEX_2D *pVtx;


	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPauseSelect->Lock(0, 0, (void**)&pVtx, 0);

	if (GetKeyboardTrigger(DIK_DOWN) == true)
	{
		g_aPauseMenu[nSelect].select = SELECTTYPE_NONE;
		nSelect = (nSelect + 1) % 3;
		g_aPauseMenu[nSelect].select = SELECTTYPE_SELECT;
	}
	if (GetKeyboardTrigger(DIK_UP) == true)
	{
		g_aPauseMenu[nSelect].select = SELECTTYPE_NONE;
		nSelect = (nSelect + 2) % 3;
		g_aPauseMenu[nSelect].select = SELECTTYPE_SELECT;
	}

	for (int nCnt = 0; nCnt < MAX_PAUSEMENU; nCnt++)
	{
		if (g_aPauseMenu[nCnt].select == SELECTTYPE_SELECT)
		{//選択中の色	
			g_aPauseMenu[nCnt].col = D3DXCOLOR(0.0f, 0.5f, 1.0f, 1.0f);
		}
		else
		{//未選択の色
			g_aPauseMenu[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
		//頂点カラー
		pVtx[0].col = g_aPauseMenu[nCnt].col;
		pVtx[1].col = g_aPauseMenu[nCnt].col;
		pVtx[2].col = g_aPauseMenu[nCnt].col;
		pVtx[3].col = g_aPauseMenu[nCnt].col;
		pVtx += 4;
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffPauseSelect->Unlock();




	//エンターキー
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		if (nSelect == 0)
		{
			g_SelectMode = SELECTMODE_CONTINE;
		}
		else if (nSelect == 1)
		{
			g_SelectMode = SELECTMODE_RETRY;
		}
		else if (nSelect == 2)
		{
			g_SelectMode = SELECTMODE_QUIT;
		}

		switch (g_SelectMode)
		{
		case SELECTMODE_CONTINE:
		{
			break;
		}
		case SELECTMODE_RETRY:
		{
			SetFade(MODE_GAME);
			break;
		}
		case SELECTMODE_QUIT:
		{	
			//g_SelectMode = SELECTMODE_NONE;
			//PlaySound(SOUND_LABEL_SE_DECIDE);
			
			break;
		}
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPauseSelect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCnt;

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPauseSelect, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VRETEX_2D);

	for (nCnt = 0; nCnt < MAX_PAUSEMENU; nCnt++)
	{
		// テクスチャの設定
		pDevice->SetTexture(0, g_pTexturePauseSelect[nCnt]);

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			0 + (4 * nCnt),	//開始する頂点のインデックス
			2); //描画するプリミティブ数
	}

}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexPauseSelect(LPDIRECT3DDEVICE9 pDevice)
{
	// 頂点情報の作成
	VERTEX_2D *pVtx;
	int nCnt;

	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_PAUSEMENU,
		D3DUSAGE_WRITEONLY,
		FVF_VRETEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPauseSelect,
		NULL);

	//頂点情報を設定
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPauseSelect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCnt = 0; nCnt < MAX_PAUSEMENU; nCnt++)
	{
		//頂点座標
		pVtx[0].pos = D3DXVECTOR3(g_aPauseMenu[nCnt].pos.x - POLYGON_POS_X, g_aPauseMenu[nCnt].pos.y - POLYGON_POS_Y, g_aPauseMenu[nCnt].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_aPauseMenu[nCnt].pos.x + POLYGON_POS_X, g_aPauseMenu[nCnt].pos.y - POLYGON_POS_Y, g_aPauseMenu[nCnt].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_aPauseMenu[nCnt].pos.x - POLYGON_POS_X, g_aPauseMenu[nCnt].pos.y + POLYGON_POS_Y, g_aPauseMenu[nCnt].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_aPauseMenu[nCnt].pos.x + POLYGON_POS_X, g_aPauseMenu[nCnt].pos.y + POLYGON_POS_Y, g_aPauseMenu[nCnt].pos.z);

		//テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//頂点
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラー
		pVtx[0].col = g_aPauseMenu[nSelect].col;
		pVtx[1].col = g_aPauseMenu[nSelect].col;
		pVtx[2].col = g_aPauseMenu[nSelect].col;
		pVtx[3].col = g_aPauseMenu[nSelect].col;

		pVtx += 4;	//頂点データのポインタを4つ分進める
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffPauseSelect->Unlock();
}

//=============================================================================
// 敵の設定
//=============================================================================
void SetPauseSelect(D3DXVECTOR3 pos, D3DXCOLOR col)
{
	int nCnt;
	float fMenuPosY = 0;
	VERTEX_2D *pVtx;//頂点情報へのポインタ
					//頂点情報を設定
					//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPauseSelect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCnt = 0; nCnt < MAX_PAUSEMENU; nCnt++)
	{
		//頂点座標
		pVtx[0].pos = D3DXVECTOR3(g_aPauseMenu[nCnt].pos.x - POLYGON_POS_X, g_aPauseMenu[nCnt].pos.y - POLYGON_POS_Y, g_aPauseMenu[nCnt].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_aPauseMenu[nCnt].pos.x + POLYGON_POS_X, g_aPauseMenu[nCnt].pos.y - POLYGON_POS_Y, g_aPauseMenu[nCnt].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_aPauseMenu[nCnt].pos.x - POLYGON_POS_X, g_aPauseMenu[nCnt].pos.y + POLYGON_POS_Y, g_aPauseMenu[nCnt].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_aPauseMenu[nCnt].pos.x + POLYGON_POS_X, g_aPauseMenu[nCnt].pos.y + POLYGON_POS_Y, g_aPauseMenu[nCnt].pos.z);
		g_aPauseMenu[nCnt].pos = pos;

		//テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//頂点
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		g_aPauseMenu[nCnt].col = col;

		fMenuPosY += 100;

		pVtx += 4;	//頂点データのポインタを4つ分進める
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffPauseSelect->Unlock();
}

//=============================================================================
// セレクトモードの取得
//=============================================================================
SELECTMODE *GetPauseMode(void)
{
	return &g_SelectMode;
}