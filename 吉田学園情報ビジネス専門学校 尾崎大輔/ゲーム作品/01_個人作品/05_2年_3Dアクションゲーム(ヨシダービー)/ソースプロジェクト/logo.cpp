//=============================================================================
//
// ロゴの処理[logo.cpp]
// Author : Ozaki
//
//=============================================================================
#include "logo.h"
#include "main.h"
#include "scene.h"
#include "renderer.h"
#include "manager.h"
#include "scene2D.h"
#include "input.h"
#include "joypad.h"

//=============================================================================
// 静的メンバ変数
//=============================================================================
LPDIRECT3DTEXTURE9 CLogo::m_pTexture[MAX_LOGO] = {};

//=============================================================================
// コンストラクタ
//=============================================================================
CLogo::CLogo() :CScene2D(4)
{
	m_pos = D3DXVECTOR3(0, 0, 0);
	m_nCntEnter = 0;
	m_fEnterTimer = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CLogo::~CLogo()
{

}

//=============================================================================
// ロード
//=============================================================================
HRESULT CLogo::Load(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = NULL;

	pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの生成[1]	// タイトル
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\logo\\title.png",
		&m_pTexture[0]);

	// テクスチャの生成[2]	// 出馬表
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\logo\\card.png",
		&m_pTexture[1]);

	// テクスチャの生成[3]	// チュートリアル
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\logo\\tutorial.png",
		&m_pTexture[2]);

	// テクスチャの生成[4]	// リザルト
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\logo\\Result.png",
		&m_pTexture[3]);

	// テクスチャの生成[4]	// プレスエンター
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\logo\\press_enter000.png",
		&m_pTexture[4]);

	return S_OK;
}

//=============================================================================
// アンロード
//=============================================================================
void CLogo::Unload(void)
{
	for (int nCnt = 0; nCnt < MAX_LOGO; nCnt++)
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
HRESULT CLogo::Init(D3DXVECTOR3 pos, float widtgh, float height, LOGO_TYPE type)
{
	// シーン2Dの初期化
	CScene2D::Init();

	SetWidth(widtgh);
	Setheight(height);

	// 共有テクスチャを割り当てる
	BindTexture(m_pTexture[type]);

	// オブジェクトタイプを設定
	SetObjtType(CScene::OBJTYPE_LOGO);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CLogo::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CLogo::Update(void)
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;

	pos = GetPos();
	m_nCntEnter++;

	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = NULL;

	// レンダラーの取得
	pDevice = CManager::GetRenderer()->GetDevice();

	// キーボードの取得
	CInputKeyboard *InputKeyboard;
	InputKeyboard = CManager::GetInputKeyboard();

	// パッドを取得
	CInputjoypad *InputJoypad;
	InputJoypad = CManager::GetInputJoypad();

	switch (m_Type)
	{
	case LOGO_TITLE:

		pos.y += 2;

		if (pos.y >= 300)
		{
			pos.y =  300;
		}

		break;
	case LOGO_RESECARD:
		if (InputKeyboard->GetPress(DIK_SPACE) == true || InputJoypad->GetPress(CInputjoypad::DIJS_BOTTON_LT) == true)
		{
			pos.x -= 5;

			if (pos.x <= -800)
			{
				pos.x = 2000;
			}
		}
		break;

	case LOGO_RESULT:

		pos.x += 50;

		if (pos.x >= SCREEN_WIDTH / 2)
		{
			pos.x = SCREEN_WIDTH / 2;
		}

		break;

	case LOGO_PRESSENTOR:

		if (m_nCntEnter >= 10)
		{
			LPDIRECT3DVERTEXBUFFER9 pVtxBuff = CScene2D::GetVtxBG();

			if (m_fEnterTimer == 1)
			{
				m_fEnterTimer = 0.0f;
			}
			else if (m_fEnterTimer == 0)
			{
				m_fEnterTimer = 1.0f;
			}

			if (pVtxBuff != NULL)
			{
				VERTEX_2D *pVtx;	// 頂点情報へのポインタ

				// 頂点バッファをロックし、頂点データへのポインタを取得
				pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, m_fEnterTimer);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, m_fEnterTimer);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, m_fEnterTimer);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, m_fEnterTimer);

				//頂点バッファをアンロック
				pVtxBuff->Unlock();
			}

			m_nCntEnter = 0;
		}
		break;
	}

	// ポジションの設定
	SetPosition(pos,0.0f,0.0f,0.0f);
}

//=============================================================================
// 描画処理
//=============================================================================
void CLogo::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// 敵の生成
//=============================================================================
CLogo *CLogo::Create(D3DXVECTOR3 pos, float widtgh, float height, LOGO_TYPE type)
{
	CLogo *pLogo;

	pLogo = new CLogo();

	pLogo->Init(pos, widtgh, height, type);
	pLogo->SetPosition(pos,0.0f,0.0f,0.0f);
	pLogo->m_Type = type;

	return pLogo;
}
