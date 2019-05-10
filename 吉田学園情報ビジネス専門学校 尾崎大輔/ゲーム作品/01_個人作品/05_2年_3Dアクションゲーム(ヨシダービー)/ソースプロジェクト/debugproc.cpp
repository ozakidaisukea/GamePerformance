//=============================================================================
//
// デバック処理 [debugpro.cpp]
// Author : Ozaki
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS
#include "debugproc.h"
#include "manager.h"
#include "main.h"
#include "renderer.h"
#include <stdio.h>
#include "input.h"

//=============================================================================
// 静的メンバ変数
//=============================================================================
LPD3DXFONT CDebugProc::m_pFont = NULL;
char CDebugProc::m_aStr[DEBUG_DATA] = {};
bool CDebugProc::m_bDisplay = NULL;
//=============================================================================
// コンストラクタ
//=============================================================================
CDebugProc::CDebugProc()
{
	m_bDisplay = false;
}

//=============================================================================
// デストラクタ
//=============================================================================
CDebugProc::~CDebugProc()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
void CDebugProc::Init(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = NULL;

	pDevice = CManager::GetRenderer()->GetDevice();

	// デバッグ情報表示用フォントの生成
	D3DXCreateFont(pDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_pFont);
}

//=============================================================================
// 終了処理
//=============================================================================
void CDebugProc::Uninit(void)
{
	m_pFont = NULL;

	for (int nCnt = 0; nCnt < DEBUG_DATA; nCnt++)
	{
		m_aStr[nCnt] = NULL;
	}
}

//=============================================================================
//
//=============================================================================
void CDebugProc::Print(char * fmt, ...)
{
	// キーボードを取得
	CInputKeyboard *InputKeyboard;
	InputKeyboard = CManager::GetInputKeyboard();


	if (InputKeyboard->GetTrigger(DIK_Z) == true)
	{
		m_bDisplay = true;
	}

	int		nNum;			// int型の取り出した物を入れる
	char	cNum[40];		// char型の取り出した物を入れる
	float	fNum;			// float型の取り出した物を入れる

	va_list  list;			// 取りまとめる変数

	va_start(list, fmt);	// 入れたい情報を一括にしてくれる

							// fmtの中身を一文字ずつ見ていく
	while (*fmt)
	{
		switch (*fmt)
		{
		case 's':			// char型

							// va_arg リストの中から取り出す
			strcat(m_aStr, va_arg(list, char*));
			break;

		case 'd':			// int型

							// int型を取り出す
			nNum = va_arg(list, int);

			sprintf(cNum, " %d ", nNum);

			// va_arg リストの中から取り出す
			strcat(m_aStr, cNum);
			break;

		case 'f':			// float型

			// float型を取り出す
			fNum = (float)(va_arg(list, double));

			sprintf(cNum, " %f ", fNum);

			// va_arg リストの中から取り出す
			strcat(m_aStr, cNum);
			break;
		}
		fmt++;				// 数字を進める
	}
	strcat(m_aStr, "\n");
	va_end(list);			// 終了
}

//=============================================================================
// 描画処理
//=============================================================================
void CDebugProc::Draw(void)
{
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };	// 描画の範囲設定

														// テキスト描画
	m_pFont->DrawText(NULL, m_aStr, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
}

//=============================================================================
// 文字を消す処理
//=============================================================================
void CDebugProc::ResetStr(void)
{
	for (int nCnt = 0; nCnt < DEBUG_DATA; nCnt++)
	{// NULLを入れる
		m_aStr[nCnt] = '\0';
	}
}
