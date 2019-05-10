//=============================================================================
//
// タイトルの処理 [Title.cpp]
// Author : Ozaki
//
//=============================================================================
#include "main.h"
#include "Title.h"
#include "input.h"
#include "sound.h"
#include "Fade.h"
#include "camera.h"
#include "light.h"
#include "wall.h"
#include "polygon.h"
#include "tutorial.h"
#include "Titlerogo.h"
#include "Player2.h"
#include "shadow.h"
#include "Player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define Title_WIDTH		(500)
#define Title_HEIGHT	(500)


//*****************************************************************************
// グローバル変数
//*****************************************************************************
//VERTEX_2D g_aVertex[4];							//頂点情報を格納する
LPDIRECT3DTEXTURE9 g_pTextureTitle = NULL;				//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;		//テクスチャのポインタ

int titletimer;
//=============================================================================
// 初期化処理(ポリゴン)
//=============================================================================
void InitTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;						//デバイスのポインタ
	pDevice = GetDevice();	//デバイスの取得
	titletimer = 0;

	//ローカル変数
	VERTEX_2D*pVtx;								//頂点情報へのポインタ

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\sensou.jpg",
		&g_pTextureTitle);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL);

	//頂点バッファをロックし、頂点データのポインタの取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(Title_WIDTH, 0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0, Title_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(Title_WIDTH, Title_HEIGHT, 0.0f);

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
	g_pVtxBuffTitle->Unlock();

	// カメラの初期化処理
	InitCamera();
	// ライトの初期化処理
	InitLight();

	InitTitleRogo();

	InitWall();

	InitPlayer2();

	InitShadow();

	// フィールドの初期化
	InitPolygon();

	// メッシュウォールの初期化
	SetWall(D3DXVECTOR3(0.0f, 0.0f, -1000.0f), D3DXVECTOR3(0.0f, D3DX_PI*1.0f, 0.0f));	 // 手前
	SetWall(D3DXVECTOR3(0.0f, 0.0f, 1000.0f), D3DXVECTOR3(0.0f, -D3DX_PI*0.0f, 0.0f));	 // 奥
	SetWall(D3DXVECTOR3(-1000.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI*-0.5f, 0.0f));	 // 左
	SetWall(D3DXVECTOR3(1000.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f));	 // 右


}

//=============================================================================
// 終了処理(ポリゴン)
//=============================================================================
void UninitTitle(void)
{
	//テクスチャの破棄
	if (g_pTextureTitle != NULL)
	{
		g_pTextureTitle->Release();
		g_pTextureTitle = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}

	UninitCamera();

	UninitPolygon();

	UninitWall();

	UninitTitleRogo();

	UninitLight();

	UninitPlayer2();

	UninitShadow();

}

//=============================================================================
// 更新処理(ポリゴン)
//=============================================================================
void UpdateTitle(void)
{
	FADE Fade;
	Fade = GetFade();
	titletimer++;

	if (Fade == FADE_NONE)
	{
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			SetFade(MODE_TUTORIAL);

			PlaySound(SOUND_LABEL_SE_USHI);
		}
		if (titletimer >= 300)
		{
			SetFade(MODE_RANKING);
		}

	}

	UpdatePlayer2();

	UpdateCamera();

	UpdatePolygon();

	UpdateWall();

	UpdateTitleRogo();

	UpdateLight();

	UpdateShadow();
}

//=============================================================================
// 描画処理(ポリゴン)
//=============================================================================
void DrawTitle(void)
{
	//LPDIRECT3DDEVICE9 pDevice;

	////デヴァイスを取得
	//pDevice = GetDevice();

	////頂点バッファをデータストリームに設定
	//pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	////頂点フォーマットの設定
	//pDevice->SetFVF(FVF_VERTEX_2D);

	////テクスチャの設定
	//pDevice->SetTexture(0, g_pTextureTitle);

	////ポリゴンの描画
	//pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
	//	0,
	//	2);

	SetCamera();

	DrawPlayer2();

	DrawPolygon();

	DrawWall();

	DrawTitleRogo();

	DrawShadow();
}