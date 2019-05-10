//=============================================================================
//
// メイン処理 [main.cpp]
// Author : Ozaki
//
//=============================================================================
#include "main.h"								// メイン
#include "Input.h"								// インプット
#include "Title.h"								// タイトル
#include "Result.h"								// リザルト
#include "sound.h"								// サウンド
#include "Fade.h"								// フェード
#include "Game.h"								// ゲーム画面
#include "Titlerogo.h"							// タイトルロゴ
#include "ranking.h"							// ランキング
#include "rankingNumber.h"						// ランキング番号
#include "rankingrogo.h"						// ランキングロゴ
#include "enter.h"								// プレスエンタ
#include "Enter2.h"								// プレスエンタ２
#include "tutorial.h"							// チュートリアル
#include "Gameover.h"							// ゲームオーバー

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define CLASS_NAME		"AppClass"				// ウインドウのクラス名
#define WINDOW_NAME		"猛の助～開幕偏～"		// ウインドウのキャプション名

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);

//*****************************************************************************
// グローバル変数:
//*****************************************************************************
LPDIRECT3D9			g_pD3D = NULL;			// Direct3Dオブジェクト
LPDIRECT3DDEVICE9	g_pD3DDevice = NULL;	// デバイスオブジェクト(描画に必要)
MODE				g_mode = MODE_TITLE;

//=============================================================================
// メイン関数
//=============================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		NULL,
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		NULL
	};
	RECT rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
	HWND hWnd;
	MSG msg;
	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;

	// ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	// 指定したクライアント領域を確保するために必要なウィンドウ座標を計算
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

	// ウィンドウの作成
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

	// 初期化処理(ウィンドウを作成してから行う)
	if(FAILED(Init(hInstance, hWnd, TRUE)))
	{
		return -1;
	}

	// 分解能を設定
	timeBeginPeriod(1);

	// フレームカウント初期化
	dwExecLastTime =
	dwFPSLastTime = timeGetTime();
	dwCurrentTime =
	dwFrameCount = 0;

	// ウインドウの表示(初期化処理の後に呼ばないと駄目)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// メッセージループ
	while(1)
	{
        if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
			{// PostQuitMessage()が呼ばれたらループ終了
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
		{
			dwCurrentTime = timeGetTime();

			if((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{// 1/60秒経過
				dwExecLastTime = dwCurrentTime;

				// 更新処理
				Update();

				// 描画処理
				Draw();

				dwFrameCount++;
			}
		}
	}

	// 終了処理
	Uninit();

	// 分解能を戻す
	timeEndPeriod(1);

	// ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

//=============================================================================
// プロシージャ
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
		}
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DPRESENT_PARAMETERS d3dpp;
    D3DDISPLAYMODE d3ddm;

	// Direct3Dオブジェクトの作成
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if(g_pD3D == NULL)
	{
		return E_FAIL;
	}

	// 現在のディスプレイモードを取得
    if(FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));								// ワークをゼロクリア
	d3dpp.BackBufferCount			 = 1;							// バックバッファの数
	d3dpp.BackBufferWidth			 = SCREEN_WIDTH;				// ゲーム画面サイズ(幅)
	d3dpp.BackBufferHeight			 = SCREEN_HEIGHT;				// ゲーム画面サイズ(高さ)
	d3dpp.BackBufferFormat			 = d3ddm.Format;				// バックバッファフォーマットはディスプレイモードに合わせて使う
	d3dpp.SwapEffect				 = D3DSWAPEFFECT_DISCARD;		// 映像信号に同期してフリップする
	d3dpp.EnableAutoDepthStencil	 = TRUE;						// デプスバッファ（Ｚバッファ）とステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat	 = D3DFMT_D16;					// デプスバッファとして16bitを使う
	d3dpp.Windowed					 = bWindow;						// ウィンドウモード
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		// リフレッシュレート
	d3dpp.PresentationInterval       = D3DPRESENT_INTERVAL_DEFAULT;	// インターバル

	// デバイスオブジェクトの生成
	// [デバイス作成制御]<描画>と<頂点処理>をハードウェアで行なう
	if(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
										D3DDEVTYPE_HAL,
										hWnd,
										D3DCREATE_HARDWARE_VERTEXPROCESSING,
										&d3dpp, &g_pD3DDevice)))
	{
		// 上記の設定が失敗したら
		// [デバイス作成制御]<描画>をハードウェアで行い、<頂点処理>はCPUで行なう
		if(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
										D3DDEVTYPE_HAL,
										hWnd,
										D3DCREATE_SOFTWARE_VERTEXPROCESSING,
										&d3dpp, &g_pD3DDevice)))
		{
			// 上記の設定が失敗したら
			// [デバイス作成制御]<描画>と<頂点処理>をCPUで行なう
			if(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
										D3DDEVTYPE_REF,
										hWnd,
										D3DCREATE_SOFTWARE_VERTEXPROCESSING,
										&d3dpp, &g_pD3DDevice)))
			{
				// 初期化失敗
				return E_FAIL;
			}
		}
	}

	// レンダーステートの設定
    g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// 裏面をカリング
	g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);						// Zバッファを使用
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// αブレンドを行う
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);						// ライティングモード有効
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// αソースカラーの指定
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// αデスティネーションカラーの指定

	// サンプラーステートの設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// テクスチャアドレッシング方法(U値)を設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// テクスチャアドレッシング方法(V値)を設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// テクスチャ縮小フィルタモードを設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// テクスチャ拡大フィルタモードを設定

	// テクスチャステージステートの設定
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// アルファブレンディング処理を設定
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// 最初のアルファ引数
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// ２番目のアルファ引数


	//キーボードの初期化処理
	InitKeyboard(hInstance, hWnd);

	// フェードの初期化処理
	InitFade(g_mode);

	InitSound(hWnd);

	SetMode(g_mode);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void Uninit(void)
{
	// キーボードの終了処理
	UninitKeyboard();

	// タイトルの終了処理
	UninitTitle();

	// タイトルロゴの初期化処理
	UninitTitleRogo();

	// リザルトの終了処理
	UninitResult();

	// サウンドの終了処理
	//UninitSound();

	// フェードの終了処理
	UninitFade();

	// ランキングの終了処理
	UninitRanking();

	// ランキング番号の終了処理
	UninitRankingNum();

	// ランキングロゴの終了処理
	UninitRankingRogo();

	// エンターの終了処理
	UninitEnter();

	// エンター2の終了処理
	UninitEnter2();

	// チュートリアルの終了処理
	Uninittutorial();

	// ゲームオーバーの終了処理
	UninitGameover();

	// ゲーム画面の終了処理
	UninitGame();

	UninitSound();

	if(g_pD3DDevice != NULL)
	{// デバイスオブジェクトの開放
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	if(g_pD3D != NULL)
	{// Direct3Dオブジェクトの開放
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void Update(void)
{
	// キーボードの更新処理
	UpdateKeyboard();

	switch (g_mode)
	{
		//タイトル
	case MODE_TITLE:
		UpdateTitleRogo();
		UpdateTitle();
		UpdateEnter();
		//UpdateEnter();
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
		//UpdateResultRogo();

		break;

		//ゲームオーバー
	case MODE_GAMEOVER:
		UpdateGameover();
		//UpdateGameoverRogo();
		break;

		//ランキング
	case MODE_RANKING:
		UpdateRankingRogo();
		UpdateRankingNum();
		UpdateRanking();
		UpdateEnter2();
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
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	// 描画の開始
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		switch (g_mode)
		{
			//タイトル
		case MODE_TITLE:

			DrawTitle();
			DrawEnter();
			DrawTitleRogo();
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
			//DrawResultRogo();
			break;

		//	//ゲームオーバー
		case MODE_GAMEOVER:
			DrawGameover();
		//	//DrawGameoverRogo();
			break;

			//ランキング
		case MODE_RANKING:
			DrawRankingRogo();
			DrawRankingNum();
			DrawRanking();
			DrawEnter2();
			break;
		}

		DrawFade();

		// 描画の終了
		g_pD3DDevice->EndScene();
	}

	// バックバッファとフロントバッファの入れ替え
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void SetMode(MODE mode)
{
	switch (g_mode)
	{
		//タイトル
	case MODE_TITLE:
		StopSound(SOUND_LABEL_TITLE);
		UninitTitle();
		break;

		//チュートリアル
	case MODE_TUTORIAL:
		StopSound(SOUND_LABEL_TUTORIAL);
		Uninittutorial();
		break;

		//ゲーム
	case MODE_GAME:
		StopSound(SOUND_LABEL_GAME);
		UninitGame();
		break;

		//リザルト
	case MODE_RESULT:
		StopSound(SOUND_LABEL_CLEAR);
		UninitResult();
		break;

		//ゲームオーバー
	case MODE_GAMEOVER:
		StopSound(SOUND_LABEL_GAMEOVER);
	//	StopSound(SOUND_LABEL_BGM0014);
		UninitGameover();
		break;

		//ランキング
	case MODE_RANKING:
		StopSound(SOUND_LABEL_RUNKING);
		UninitRankingNum();
		break;
	}
	g_mode = mode;

	switch (mode)
	{
		//タイトル
	case MODE_TITLE:
		InitTitle();
		InitEnter();
		InitTitleRogo();
		PlaySound(SOUND_LABEL_TITLE);
		break;

		//チュートリアル
	case MODE_TUTORIAL:
		Inittutorial();
		PlaySound(SOUND_LABEL_TUTORIAL);
		break;

		//ゲーム
	case MODE_GAME:
		InitGame();
		PlaySound(SOUND_LABEL_GAME);
		break;

		//リザルト
	case MODE_RESULT:
		InitResult();
		PlaySound(SOUND_LABEL_CLEAR);
		break;

		//ゲームオーバー
	case MODE_GAMEOVER:
		InitGameover();
	//	//PlaySound(SOUND_LABEL_SE_MARIO_DETH);
		PlaySound(SOUND_LABEL_GAMEOVER);
		break;

		//ランキング
	case MODE_RANKING:
		InitRankingNum();
		InitRanking();
		InitRankingRogo();
		InitEnter2();
		PlaySound(SOUND_LABEL_RUNKING);
		break;
	}
}

//=============================================================================
// デバイスの取得
//=============================================================================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

MODE GetMode(void)
{
	return g_mode;
}

float Rotover(float rot)
{
	if (rot < -D3DX_PI)
	{
		rot += D3DX_PI * 2.0f;
	}
	if (rot >  D3DX_PI)
	{
		rot -= D3DX_PI * 2.0f;
	}
	return rot;
}

