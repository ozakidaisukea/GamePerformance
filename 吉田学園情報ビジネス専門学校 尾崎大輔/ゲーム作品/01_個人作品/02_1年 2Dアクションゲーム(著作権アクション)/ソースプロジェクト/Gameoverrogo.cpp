//=============================================================================
//
// 背景の処理 [Gameoverrogo.cpp]
// Author : Ozaki
//
//=============================================================================
#include "main.h"
#include "Gameoverrogo.h"
#include "Fade.h"
#include "sound.h"
#include "Input.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define BG_WIDTH	(SCREEN_WIDTH)
#define BG_HEIGHT	(70)

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureGameoverRogo = NULL;				//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGameoverRogo = NULL;		//テクスチャのポインタ
int		GameOvertimer;
//=============================================================================
// 初期化処理(ポリゴン)
//=============================================================================
void InitGameoverRogo(void)
{
	LPDIRECT3DDEVICE9 pDevise;						//デバイスのポインタ
													//デバイスの取得
	pDevise = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevise,
		"data\\TEXTURE\\result_logo001.png",
		&g_pTextureGameoverRogo);

	//頂点バッファの生成
	pDevise->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VRETEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffGameoverRogo,
		NULL);

	//ローカル変数
	VERTEX_2D*pVtx;								//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データのポインタの取得
	g_pVtxBuffGameoverRogo->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	// テクスチャ座標の設定
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
	g_pVtxBuffGameoverRogo->Unlock();
}

//=============================================================================
// 終了処理(ポリゴン)
//=============================================================================
void UninitGameoverRogo(void)
{
	//テクスチャの破棄
	if (g_pTextureGameoverRogo != NULL)
	{
		g_pTextureGameoverRogo->Release();
		g_pTextureGameoverRogo = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffGameoverRogo != NULL)
	{
		g_pVtxBuffGameoverRogo->Release();
		g_pVtxBuffGameoverRogo = NULL;
	}
}

//=============================================================================
// 更新処理(ポリゴン)
//=============================================================================
void UpdateGameoverRogo(void)
{
	FADE Fade;
	Fade = GetFade();
	GameOvertimer++;

	if (Fade == FADE_NONE)
	{
		if (GetKeyboardTrigger(DIK_RETURN) == true && Fade == FADE_NONE)
		{
			SetFade(MODE_RANKING);
			PlaySound(SOUND_LABEL_SE_DECIDE);

		}
		if (GameOvertimer >= 700)
		{
			SetFade(MODE_RANKING);
		}

	}

}

//=============================================================================
// 描画処理(ポリゴン)
//=============================================================================
void DrawGameoverRogo(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デヴァイスを取得
	pDevice = GetDevice();


	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffGameoverRogo, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VRETEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureGameoverRogo);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);
} 