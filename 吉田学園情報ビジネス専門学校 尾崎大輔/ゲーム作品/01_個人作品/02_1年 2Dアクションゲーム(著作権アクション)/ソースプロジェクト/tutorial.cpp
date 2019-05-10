//=============================================================================
//
// チュートリアルの処理 [tutorial.cpp]
// Author : Ozaki
//
//=============================================================================
#include "main.h"
#include "tutorial.h"
#include "input.h"
#include "fade.h"
#include "sound.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define tutorial_WIDTH	(SCREEN_WIDTH)
#define tutorial_HEIGHT	(SCREEN_HEIGHT)

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTexturetutorial = NULL;			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufftutorial = NULL;		//テクスチャのポインタ

//=============================================================================
// 初期化処理(ポリゴン)
//=============================================================================
void Inittutorial(void)
{
	LPDIRECT3DDEVICE9 pDevice;						//デバイスのポインタ					
	pDevice = GetDevice();	//デバイスの取得

							//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\tutorial_bg001.jpg",
		&g_pTexturetutorial);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VRETEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBufftutorial,
		NULL);
	//ローカル変数
	VERTEX_2D*pVtx;								//頂点情報へのポインタ


												//頂点バッファをロックし、頂点データのポインタの取得
	g_pVtxBufftutorial->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//テクスチャの設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//頂点バッファをアンロック
	g_pVtxBufftutorial->Unlock();
}

//=============================================================================
// 終了処理(ポリゴン)
//=============================================================================
void Uninittutorial(void)
{
	//テクスチャの破棄
	if (g_pTexturetutorial != NULL)
	{
		g_pTexturetutorial->Release();
		g_pTexturetutorial = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBufftutorial != NULL)
	{
		g_pVtxBufftutorial->Release();
		g_pVtxBufftutorial = NULL;
	}
}

//=============================================================================
// 更新処理(ポリゴン)
//=============================================================================
void Updatetutorial(void)
{
	FADE Fade;
	Fade = GetFade();

	if (Fade == FADE_NONE)
	{
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			SetFade(MODE_GAME);
			PlaySound(SOUND_LABEL_SE_DECIDE);
		}
	}

}

//=============================================================================
// 描画処理(ポリゴン)
//=============================================================================
void Drawtutorial(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デヴァイスを取得
	pDevice = GetDevice();


	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBufftutorial, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VRETEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTexturetutorial);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);
}