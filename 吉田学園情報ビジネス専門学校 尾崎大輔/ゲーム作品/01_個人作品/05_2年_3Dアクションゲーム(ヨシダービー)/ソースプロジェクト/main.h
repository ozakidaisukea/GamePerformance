//=============================================================================
//
// メイン処理 [main.h]
// Author : Ozaki
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include <windows.h>
#include "d3dx9.h"						//描画処理に必要
#define DIRECTINPUT_VERSION (0x0800)	//ビルド時の警告対処用マクロ
#include "dinput.h"

#include "xaudio2.h"

#include <crtdbg.h>

#ifdef _DEBUG
#include <crtdbg.h>
//#define malloc(X) _malloc_dbg(X,_NORMAL_BLOCK,__FILE__,__LINE__)
//#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
//#define _CRTDBG_MAP_ALLOC
#endif // DEBUG

//*****************************************************************************
// ライブラリファイルのリンク
//*****************************************************************************
#pragma comment(lib,"d3d9.lib")			// 描画処理に必要
#pragma comment(lib,"d3dx9.lib")		// [d3d9.lib]の拡張のライブラリ
#pragma comment(lib,"dxguid.lib")		// DirectXコンボーネット(部品)使用に必要
#pragma comment(lib,"winmm.lib")		// システム時刻取得が必要
#pragma comment(lib,"dinput8.lib")		// システム時刻取得が必要

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SCREEN_WIDTH	(1280)		// ウインドウの幅
#define SCREEN_HEIGHT	(720)		// ウインドウの高さ
#define FVF_VRETEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define FVF_VRETEX_3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;				// 頂点座標
	float rhw;						// 1.0fで固定
	D3DCOLOR col;					// 頂点カラー
	D3DXVECTOR2 tex;				// テクスチャ座標

}VERTEX_2D;

typedef struct
{
	D3DXVECTOR3 pos;				// 頂点座標
	D3DXVECTOR3 nor;				// 法線ベクトル
	D3DCOLOR	col;				// 頂点カラー
	D3DXVECTOR2 tex;				// テクスチャ座標
}VERTEX_3D;

// 前方宣言
class CRenderer;
class CScene;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
int				GetFPS(void);
CRenderer		*GetRenderer(void);

#endif