//=============================================================================
//
// ロゴ鮭の処理[logosyake.cpp]
// Author : Ozaki
//
//=============================================================================
#include "logosyake.h"
#include "main.h"
#include "scene.h"
#include "renderer.h"
#include "manager.h"
#include "scene2D.h"

//=============================================================================
// 静的メンバ変数
//=============================================================================
LPDIRECT3DTEXTURE9 CLogosyake::m_pTexture[MAX_SYAKE] = {};

//=============================================================================
// コンストラクタ
//=============================================================================
CLogosyake::CLogosyake() :CScene2D(1)
{

}

//=============================================================================
// デストラクタ
//=============================================================================
CLogosyake::~CLogosyake()
{

}

//=============================================================================
// ロード
//=============================================================================
HRESULT CLogosyake::Load(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = NULL;

	pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの生成[1]
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\logo\\title_syake.png",
		&m_pTexture[0]);

	// テクスチャの生成[2]
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\game\\syake_dead.png",
		&m_pTexture[1]);

	// テクスチャの生成[3]
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\game\\syake.png",
		&m_pTexture[2]);

	// テクスチャの生成[4]
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\game\\1.png",
		&m_pTexture[3]);

	return S_OK;
}

//=============================================================================
// アンロード
//=============================================================================
void CLogosyake::Unload(void)
{
	for (int nCnt = 0; nCnt < MAX_SYAKE; nCnt++)
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
HRESULT CLogosyake::Init(D3DXVECTOR3 pos, float widtgh, float height,D3DXVECTOR3 move,SYAKE_TYPE type)
{
	// シーン2Dの初期化
	CScene2D::Init(pos, widtgh, height);

	m_widtgh = widtgh;

	m_height = height;

	m_Type = type;

	// オブジェクトタイプを設定
	SetObjtType(CScene::OBJTYPE_LOGO);


	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CLogosyake::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CLogosyake::Update(void)
{
	D3DXVECTOR3 pos;

	pos = GetPosition();

	if (SYAKE_LOGO == m_Type)
	{
		if (pos.y >= SCREEN_HEIGHT - 470)
		{
			// 移動量
			m_move.y += 0.05f;

			pos -= m_move;
		}
	}

	if (SYAKE_RESULT == m_Type)
	{
		if (pos.x >= 500 - 470)
		{
			// 移動量
			m_move.x -= 0.05f;

			pos -= m_move;
		}
	}

	if (SYAKE_GAMEOVER == m_Type)
	{
		if (pos.x >= 500 - 470)
		{
			// 移動量
			m_move.x -= 0.05f;

			pos -= m_move;
		}
	}

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
void CLogosyake::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// 敵の生成
//=============================================================================
CLogosyake *CLogosyake::Create(D3DXVECTOR3 pos, float widtgh, float height,D3DXVECTOR3 move, SYAKE_TYPE type)
{
	CLogosyake *pLogosyake;

	pLogosyake = new CLogosyake;

	pLogosyake->Init(pos, widtgh, height, move,type);

	// 共有テクスチャを割り当てる
	pLogosyake->BindTexture(m_pTexture[type]);

	return pLogosyake;
}
