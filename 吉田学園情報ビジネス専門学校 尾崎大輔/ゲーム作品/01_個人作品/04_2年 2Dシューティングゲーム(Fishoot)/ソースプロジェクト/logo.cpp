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

//=============================================================================
// 静的メンバ変数
//=============================================================================
LPDIRECT3DTEXTURE9 CLogo::m_pTexture[MAX_LOGO] = {};

//=============================================================================
// コンストラクタ
//=============================================================================
CLogo::CLogo() :CScene2D(7)
{
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

	// テクスチャの生成[1]
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\logo\\title2.png",
		&m_pTexture[0]);

	// テクスチャの生成[2]
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\logo\\tutorial_logo.png",
		&m_pTexture[1]);

	// テクスチャの生成[3]
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\logo\\result_logo000.png",
		&m_pTexture[2]);

	// テクスチャの生成[4]
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\logo\\result_logo001.png",
		&m_pTexture[3]);

	// テクスチャの生成[5]
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\logo\\ranking_logo.png",
		&m_pTexture[4]);

	// テクスチャの生成[6]
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\logo\\title_syake.png",
		&m_pTexture[5]);

	// テクスチャの生成[7]
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\logo\\tutorialsetumei.png",
		&m_pTexture[6]);

	// テクスチャの生成[8]
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\logo\\ranking_rank1.png",
		&m_pTexture[7]);

	// テクスチャの生成[9]
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\logo\\1.png",
		&m_pTexture[8]);

	// テクスチャの生成[10]
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\logo\\2.png",
		&m_pTexture[9]);

	// テクスチャの生成[11]
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\logo\\3.png",
		&m_pTexture[10]);

	// テクスチャの生成[12]
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\logo\\4.png",
		&m_pTexture[11]);

	// テクスチャの生成[13]
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\logo\\5.png",
		&m_pTexture[12]);

	// テクスチャの生成[14]
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\logo\\sousa.png",
		&m_pTexture[13]);

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
	CScene2D::Init(pos, widtgh, height);

	m_widtgh = widtgh;

	m_height = height;

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

	pos = GetPosition();

	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = NULL;

	// レンダラーの取得
	pDevice = CManager::GetRenderer()->GetDevice();

	// キーボードの取得
	CInputKeyboard *InputKeyboard;

	InputKeyboard = CManager::GetInputKeyboard();

	// ポジションの設定
	SetPosition(pos, m_rot, m_position, m_flength);
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
CLogo *CLogo::Create(D3DXVECTOR3 pos, float widtgh, float height,LOGO_TYPE type)
{
	CLogo *pLogo;

	pLogo = new CLogo;

	pLogo->Init(pos, widtgh,height,type);

	// 共有テクスチャを割り当てる
	pLogo->BindTexture(m_pTexture[type]);

	return pLogo;
}
