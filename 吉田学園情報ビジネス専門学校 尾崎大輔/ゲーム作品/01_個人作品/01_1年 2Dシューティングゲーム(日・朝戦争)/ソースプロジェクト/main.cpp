//=============================================================================
//
// DirectX雛型処理 [main.cpp]
// Author : Ozaki
//
//=============================================================================
#include "main.h"
#include "player.h"
#include "BG.h"
#include "input.h"
#include "bullet.h"
#include "Explosion.h"
#include "enemy.h"
#include "Title.h"
#include "Game.h"
#include "Result.h"
#include "fade.h"
#include <time.h>
#include "sound.h"
#include "Gameover.h"
#include "ranking.h"
#include "rankingBG.h"
#include "rankingNumber.h"
#include "tutorial.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define CLASS_NAME		"WindowClass"		// ウインドウクラスの名前
#define WINDOW_NAME		"日・朝戦争"	// ウインドウの名前(キャプション名)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3D9 g_pD3D = NULL;					//Direct3Dオブジェクトポインタ
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;		//Direct3Dデバイスへのポインタ
MODE	g_mode = MODE_TITLE;
//=============================================================================
// メイン関数
//=============================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WindowProc,
		0,
		0,
		hInstance,

		LoadIcon(NULL, IDI_APPLICATION),
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		LoadIcon(NULL, IDI_APPLICATION)
	};
	RECT rect = { 0, 0, SCREEN_WIDTH,SCREEN_HEIGHT};
	HWND hWnd;
	MSG msg;
	//分解能
	timeBeginPeriod(1);
	DWORD dwCureniTime;
	DWORD dwExedasTime;
	dwCureniTime = 0;
	//現在時刻
	dwExedasTime = timeGetTime();
	srand((unsigned int)time(0));

	// ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	//指定したクライアント領域を確保するために必要なウィンドウ座標を計算
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

	// ウィンドウの生成
	hWnd = CreateWindowEx(0,
							CLASS_NAME,
							WINDOW_NAME,
							WS_OVERLAPPEDWINDOW,
							CW_USEDEFAULT,
							CW_USEDEFAULT,
							(rect.right - rect.left),
							(rect.bottom - rect.top),
							NULL,
							NULL,
							hInstance,
							NULL);

	// 初期化処理(ウィンドウを生成してから行う)
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{
		return -1;
	}

	// ウインドウの表示(初期化処理の後に行う)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);


	// メッセージループ
	while(1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)	// メッセージを取得しなかった場合"0"を返す
		{// Windowsの処理
			if (msg.message == WM_QUIT)
			{// "WM_QUIT"メッセージが送られてきたらループを抜ける
				break;
			}
			else
			{
				// メッセージの翻訳と送出
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{// DirectXの処理

			// 更新処理
			Update();

			// 描画処理
			Draw();
		}
	}

	// 終了処理
	Uninit();

	//分解能を戻す
	timeEndPeriod(1);

	// ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

//=============================================================================
// ウインドウプロシージャ
//=============================================================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_DESTROY:
		// "WM_QUIT"メッセージを送る
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_ESCAPE:
			// ウィンドウを破棄する("WM_DESTROY"メッセージを送る)
			DestroyWindow(hWnd);
			break;
		}
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);						// 既定の処理を返す
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;													//ディスプレイモード
	D3DPRESENT_PARAMETERS d3dpp;											//プレゼンテーションパラメーター

	// Direct3Dオブジェクトの生成
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}
	// 現在のディスプレイモードを取得
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
	return E_FAIL;
	}

	// デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));										// ワークをゼロクリア
	d3dpp.BackBufferWidth			 = SCREEN_WIDTH;						// ゲーム画面サイズ(幅)
	d3dpp.BackBufferHeight			 = SCREEN_HEIGHT; 						// ゲーム画面サイズ(高さ)
	d3dpp.BackBufferFormat			 = d3ddm.Format;						// バックバッファの形式
	d3dpp.BackBufferCount			 = 1;									// バックバッファの数
	d3dpp.SwapEffect				 = D3DSWAPEFFECT_DISCARD;				// ダブルバッファの切り替え(映像信号に同期)
	d3dpp.EnableAutoDepthStencil	 = TRUE;								// デプスバッファ(Ｚバッファ)とステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat	 = D3DFMT_D16;							// デプスバッファとして16bitを使う
	d3dpp.Windowed					 = bWindow;								// ウィンドウモード
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;				// リフレッシュレート(現在の速度に合わせる)
	d3dpp.PresentationInterval		 = D3DPRESENT_INTERVAL_DEFAULT;			// インターバル(VSyncを待って描画)

	// Direct3Dデバイスの生成
	// [デバイス作成制御]<描画>と<頂点処理>をハードウェアで行なう
	if(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,						// ディスプレイアダプタ
									D3DDEVTYPE_HAL,							// デバイスタイプ
									hWnd,									// フォーカスするウインドウへのハンドル
									D3DCREATE_HARDWARE_VERTEXPROCESSING,	// デバイス作成制御の組み合わせ
									&d3dpp,									// デバイスのプレゼンテーションパラメータ
									&g_pD3DDevice)))						// デバイスインターフェースへのポインタ
	{
		// 上記の設定が失敗したら
		// [デバイス作成制御]<描画>をハードウェアで行い、<頂点処理>はCPUで行なう
		if(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
										D3DDEVTYPE_HAL,
										hWnd,
										D3DCREATE_SOFTWARE_VERTEXPROCESSING,
										&d3dpp,
										&g_pD3DDevice)))
		{
			// 上記の設定が失敗したら
			//[デバイス作成制御]<描画>と<頂点処理>をCPUで行なう
			if(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
											D3DDEVTYPE_REF,
											hWnd,
											D3DCREATE_SOFTWARE_VERTEXPROCESSING,
											&d3dpp,
										&g_pD3DDevice)))
			{
				return E_FAIL;
			}

		}
	}

	//カリング
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//テクスチャー
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1,D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	//ポリゴン初期化処理

	InitKeyboard(hInstance,hWnd);

	InitFade(g_mode);
	InitSound(hWnd);
	SetMode(g_mode);
	InitRanking();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void Uninit(void)
{
	UninitKeyboard();
	UninitTitle();
	Uninittutorial();
	UninitGame();
	UninitResult();
	UninitFade();
	UninitSound();
	UninitRanking();

	// Direct3Dデバイスの開放
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	// Direct3Dオブジェクトの開放
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void Update(void)
{
	UpdateKeyboard();

	switch (g_mode)
	{
	//タイトル
	case MODE_TITLE:
		UpdateTitle();
		break;

	//チュートリアル
	case MODE_TUTORIAL:
		Updatetutorial();
		break;

	//ゲーム
	case MODE_GAME:
		UpdateGame();
		break;

	//リザルト
	case MODE_RESULT:
		UpdateResult();
		break;

	//ゲームオーバー
	case MODE_GAMEOVER:
		UpdateGameover();
		break;

	//ランキング
	case MODE_RANKING:
		UpdateRankingBG();
		UpdateRankingNum();
		UpdateRanking();
		break;
	}
	UpdateFade();

}

//=============================================================================
// 描画処理
//=============================================================================
void Draw(void)
{
	// バックバッファ＆Ｚバッファのクリア
	g_pD3DDevice->Clear(0,
		NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0),
		1.0f,
		0);

	//描画の開始
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{

		switch (g_mode)
		{
		//タイトル
		case MODE_TITLE:
			DrawTitle();
			break;

		//チュートリアル
		case MODE_TUTORIAL:
			Drawtutorial();
			break;

		//ゲーム
		case MODE_GAME:
			DrawGame();
			break;

		//リザルト
		case MODE_RESULT:
			DrawResult();
			break;

		//ゲームオーバー
		case MODE_GAMEOVER:
			DrawGameover();
			break;

			//ランキング
		case MODE_RANKING:
			DrawRankingBG();
			DrawRankingNum();
			DrawRanking();
			break;
		}

		DrawFade();
		// 描画の終了
		g_pD3DDevice->EndScene();
	}

// バックバッファとフロントバッファの入れ替え
g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}
//================================ポリゴン=====================================================
//デバイスを取得
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

void SetMode(MODE mode)
{
	switch (g_mode)
	{
	//タイトル
	case MODE_TITLE:
		StopSound(SOUND_LABEL_BGM000);
		UninitTitle();
		break;

	//チュートリアル
	case MODE_TUTORIAL:
		StopSound(SOUND_LABEL_BGM000);
		Uninittutorial();
		break;

	//ゲーム
	case MODE_GAME:
		StopSound(SOUND_LABEL_BGM001);
		UninitGame();
		break;

	//リザルト
	case MODE_RESULT:
		StopSound(SOUND_LABEL_BGM002);
		UninitResult();
		break;

	//ゲームオーバー
	case MODE_GAMEOVER:
		StopSound(SOUND_LABEL_BGM004);
		UninitGameover();
		break;

	//ランキング
	case MODE_RANKING:
		StopSound(SOUND_LABEL_BGM003);
		UninitRankingBG();
		UninitRankingNum();
		break;
	}
	switch (mode)
	{
	//タイトル
	case MODE_TITLE:
		InitTitle();
		PlaySound(SOUND_LABEL_BGM000);
		break;

	//チュートリアル
	case MODE_TUTORIAL:
		Inittutorial();
		PlaySound(SOUND_LABEL_BGM000);
		break;

	//ゲーム
	case MODE_GAME:
		InitGame();
		PlaySound(SOUND_LABEL_BGM001);
		break;

	//リザルト
	case MODE_RESULT:
		InitResult();
		PlaySound(SOUND_LABEL_BGM002);
		break;

	//ゲームオーバー
	case MODE_GAMEOVER:
		InitGameover();
		PlaySound(SOUND_LABEL_BGM004);
		break;

	//ランキング
	case MODE_RANKING:
		InitRankingBG();
		InitRankingNum();
		PlaySound(SOUND_LABEL_BGM003);
		break;
	}
	g_mode = mode;
}

MODE GetMode(void)
{
	return g_mode;
}
