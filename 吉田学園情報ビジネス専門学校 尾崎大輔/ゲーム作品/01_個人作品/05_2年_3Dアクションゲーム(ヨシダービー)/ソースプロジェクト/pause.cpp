//=============================================================================
//
// ポーズの処理[pause.cpp]
// Author : Ozaki
//
//=============================================================================
#include "pause.h"
#include "main.h"
#include "scene.h"
#include "renderer.h"
#include "manager.h"
#include "scene2D.h"
#include "fade.h"
#include "input.h"

//=============================================================================
// 静的メンバ変数
//=============================================================================
LPDIRECT3DTEXTURE9 CPause::m_pTexture[MAX_PAUSEMENU] = {};
CPause::PAUSETYPE CPause::m_SelectMode = SELECTMODE_NONE;

//=============================================================================
// コンストラクタ
//=============================================================================
CPause::CPause()
{
	for (int nCnt = 0; nCnt < MAX_PAUSEMENU; nCnt++)
	{
		m_pScene2D[nCnt] = NULL;
	}
}

//=============================================================================
// デストラクタ
//=============================================================================
CPause::~CPause()
{

}

//=============================================================================
// ロード
//=============================================================================
HRESULT CPause::Load(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = NULL;

	pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの生成[1]	コンテニュー
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_CONTINUE,
		&m_pTexture[0]);

	// テクスチャの生成[2]	リトライ
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_RETRY,
		&m_pTexture[1]);

	// テクスチャの生成[3]	クィット
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_QUIT,
		&m_pTexture[2]);

	// テクスチャの生成[4]	背景
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_BG,
		&m_pTexture[3]);

	return S_OK;
}

//=============================================================================
// アンロード
//=============================================================================
void CPause::Unload(void)
{
	for (int nCnt = 0; nCnt < MAX_PAUSEMENU; nCnt++)
	{
		// テクスチャの破棄
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();

			m_pTexture[nCnt] = NULL;
		}
	}
}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CPause::Init(void)
{
	//ローカル変数
	VERTEX_2D*pVtx;

	// オブジェクトタイプを設定
	SetObjtType(CScene::OBJTYPE_PAUSE);

	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = NULL;

	pDevice = CManager::GetRenderer()->GetDevice();

	for (int nCnt = 0; nCnt < MAX_PAUSEMENU; nCnt++)
	{
		if (m_pScene2D[nCnt] == NULL)
		{
			if (nCnt == 3)
			{

				m_pScene2D[nCnt] = new CScene2D(3);
			}
			else
			{
				m_pScene2D[nCnt] = new CScene2D(4);
			}

			if (m_pScene2D[nCnt] != NULL)
			{
				m_pScene2D[nCnt]->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0, 0);
				m_pScene2D[nCnt]->SetWidth(0.0f);
				m_pScene2D[nCnt]->Setheight(0.0f);

				m_pScene2D[nCnt]->CScene2D::Init();
				m_pScene2D[nCnt]->BindTexture(m_pTexture[nCnt]);
				m_pVtxBuff[nCnt] = m_pScene2D[nCnt]->GetVtxBG();

				m_pVtxBuff[nCnt]->Lock(0, 0, (void**)&pVtx, 0);

				// 背景
				if (nCnt == 3)
				{
					//頂点座標の設定
					pVtx[0].pos = D3DXVECTOR3(300.0f, 60.0f, 0.0f);
					pVtx[1].pos = D3DXVECTOR3(1000.0f, 60.0f, 0.0f);
					pVtx[2].pos = D3DXVECTOR3(300.0f, 620.0f, 0.0f);
					pVtx[3].pos = D3DXVECTOR3(1000.0f, 620.0f, 0.0f);
				}

				// コンテニュー
				if (nCnt == 0)
				{
					//頂点座標の設定
					pVtx[0].pos = D3DXVECTOR3(350.0f, 90.0f, 0.0f);
					pVtx[1].pos = D3DXVECTOR3(900.0f, 90.0f, 0.0f);
					pVtx[2].pos = D3DXVECTOR3(350.0f, 250.0f, 0.0f);
					pVtx[3].pos = D3DXVECTOR3(900.0f, 250.0f, 0.0f);
				}

				// リトライ
				if (nCnt == 1)
				{
					//頂点座標の設定
					pVtx[0].pos = D3DXVECTOR3(350.0f, 240.0f, 0.0f);
					pVtx[1].pos = D3DXVECTOR3(900.0f, 240.0f, 0.0f);
					pVtx[2].pos = D3DXVECTOR3(350.0f, 410.0f, 0.0f);
					pVtx[3].pos = D3DXVECTOR3(900.0f, 410.0f, 0.0f);
				}

				// クィット
				if (nCnt == 2)
				{
					//頂点座標の設定
					pVtx[0].pos = D3DXVECTOR3(350.0f, 400.0f, 0.0f);
					pVtx[1].pos = D3DXVECTOR3(900.0f, 400.0f, 0.0f);
					pVtx[2].pos = D3DXVECTOR3(350.0f, 590.0f, 0.0f);
					pVtx[3].pos = D3DXVECTOR3(900.0f, 590.0f, 0.0f);
				}

				pVtx += 4;

				// 頂点バッファをアンロックする
				m_pVtxBuff[nCnt]->Unlock();
			}
		}
	}
	m_nSelect = 0;

	m_aPauseMenu[0].select = SELECTTYPE_SELECT;

	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void CPause::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_PAUSE; nCnt++)
	{
		// テクスチャの破棄
		if (m_pScene2D[nCnt] != NULL)
		{
			m_pScene2D[nCnt]->Uninit();

			//delete m_pScene2D[nCnt];
			m_pScene2D[nCnt] = NULL;
		}
	}
	CScene::Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CPause::Update(void)
{
	//ローカル変数
	VERTEX_2D*pVtx;

	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = NULL;

	// レンダラーの取得
	pDevice = CManager::GetRenderer()->GetDevice();

	// キーボードの取得
	CInputKeyboard *InputKeyboard;
	InputKeyboard = CManager::GetInputKeyboard();

	// キーボードを取得
	//CInputjoypad *InputJoypad;
	//InputJoypad = CManager::GetInputJoypad();

	if (InputKeyboard->GetTrigger(DIK_DOWN) == true /*||
		InputJoypad->GetTrigger(CInputjoypad::DIJS_STICK_POV_DOWN) == true
		|| InputJoypad->GetTrigger(CInputjoypad::DIJS_STICK_LEFT_DOWN) == true*/)
	{
		m_aPauseMenu[m_nSelect].select = SELECTTYPE_NONE;
		m_nSelect = (m_nSelect + 1) % 3;
		m_aPauseMenu[m_nSelect].select = SELECTTYPE_SELECT;
	}
	if (InputKeyboard->GetTrigger(DIK_UP) == true /*||
		InputJoypad->GetTrigger(CInputjoypad::DIJS_STICK_POV_UP) == true
		|| InputJoypad->GetTrigger(CInputjoypad::DIJS_STICK_LEFT_UP) == true*/)
	{
		m_aPauseMenu[m_nSelect].select = SELECTTYPE_NONE;
		m_nSelect = (m_nSelect + 2) % 3;
		m_aPauseMenu[m_nSelect].select = SELECTTYPE_SELECT;
	}

	for (int nCnt = 0; nCnt < MAX_PAUSEMENU; nCnt++)
	{
		if (m_pScene2D[nCnt] != NULL)
		{// NULLチェック
			m_pVtxBuff[nCnt] = m_pScene2D[nCnt]->GetVtxBG();
			if (m_pVtxBuff[nCnt] != NULL)
			{// NULLチェック
				m_pVtxBuff[nCnt]->Lock(0, 0, (void**)&pVtx, 0);

				if (m_aPauseMenu[nCnt].select == SELECTTYPE_SELECT)
				{//選択中の色
					m_aPauseMenu[nCnt].col = D3DXCOLOR(1.0f, 0.7f, 0.2f, 1.0f);
				}
				else
				{// 未選択の色
					m_aPauseMenu[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				}
				// 頂点カラー
				pVtx[0].col = m_aPauseMenu[nCnt].col;
				pVtx[1].col = m_aPauseMenu[nCnt].col;
				pVtx[2].col = m_aPauseMenu[nCnt].col;
				pVtx[3].col = m_aPauseMenu[nCnt].col;

				// 頂点バッファをアンロックする
				m_pVtxBuff[nCnt]->Unlock();
			}
		}
	}


	//エンターキー
	if (InputKeyboard->GetTrigger(DIK_RETURN) == true /*||
		InputJoypad->GetTrigger(CInputjoypad::DIJS_BOTTON_B) == true*/)
	{
		if (m_nSelect == 0)
		{
			m_SelectMode = SELECTMODE_CONTINE;
		}
		else if (m_nSelect == 1)
		{
			m_SelectMode = SELECTMODE_RETRY;
		}
		else if (m_nSelect == 2)
		{
			m_SelectMode = SELECTMODE_QUIT;
		}

		switch (m_SelectMode)
		{
		case SELECTMODE_CONTINE:
		{
			break;
		}
		case SELECTMODE_RETRY:
		{
			// フェードを取得
			CFade *pFade;
			pFade = CManager::GetFade();

			if (pFade->GetFade() == CFade::FADE_NONE)
			{
				pFade->SetFade(CManager::MODE_GAME);
			}
			break;
		}
		case SELECTMODE_QUIT:
		{
			break;
		}
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CPause::Draw(void)
{

}

//=============================================================================
//	ポーズの生成
//=============================================================================
CPause *CPause::Create(D3DXVECTOR3 pos, float widtgh, float height)
{
	CPause *pPause;

	pPause = new CPause;

	pPause->Init();

	return pPause;
}

//=============================================================================
//	ポーズ
//=============================================================================
CPause::PAUSETYPE CPause::GetPause(void)
{
	return m_SelectMode;
}


