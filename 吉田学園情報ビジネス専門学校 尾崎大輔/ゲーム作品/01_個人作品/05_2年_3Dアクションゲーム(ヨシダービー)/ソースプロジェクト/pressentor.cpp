//=============================================================================
//
// プレスエンターの処理[PressEntor.cpp]
// Author : Ozaki
//
//=============================================================================
#include "Pressentor.h"
#include "main.h"
#include "scene.h"
#include "renderer.h"
#include "manager.h"

//=============================================================================
// 静的メンバ変数
//=============================================================================
LPDIRECT3DTEXTURE9 CPressEntor::m_pTexture = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CPressEntor::CPressEntor()
{
	m_pos = D3DXVECTOR3(0, 0, 0);
}

//=============================================================================
// デストラクタ
//=============================================================================
CPressEntor::~CPressEntor()
{

}

//=============================================================================
// ロード
//=============================================================================
HRESULT CPressEntor::Load(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = NULL;

	pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの生成[4]
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\logo\\press_enter000.png",
		&m_pTexture);

	return S_OK;
}

//=============================================================================
// アンロード
//=============================================================================
void CPressEntor::Unload(void)
{
	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();

		m_pTexture = NULL;
	}
}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CPressEntor::Init(D3DXVECTOR3 pos, float widtgh, float height)
{
	// シーン2Dの初期化
	m_apScene2D = CScene2D::Create(pos,widtgh,height);

	//m_apScene2D->BindTexture(m_pTexture);

	//m_widtgh = widtgh;

	m_pos = pos;

	//m_height = height;

	// オブジェクトタイプを設定
	SetObjtType(CScene::OBJTYPE_PRESSENTOR);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CPressEntor::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CPressEntor::Update(void)
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;

	pos = GetPosition();

	m_nCntEnter++;

	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = NULL;

	// レンダラーの取得
	pDevice = CManager::GetRenderer()->GetDevice();

	// キーボードの取得
	CInputKeyboard *InputKeyboard;

	InputKeyboard = CManager::GetInputKeyboard();

	if (m_nCntEnter >= 10)
	{
		m_apScene2D->BindTexture(m_pTexture);
		m_pVtxBuff = m_apScene2D->GetVtxBG();

		if (m_fEnterTimer == 1)
		{
			m_fEnterTimer = 0.0f;
		}
		else if (m_fEnterTimer == 0)
		{
			m_fEnterTimer = 1.0f;
		}

		VERTEX_2D *pVtx;	// 頂点情報へのポインタ

		// 頂点バッファをロックし、頂点データへのポインタを取得
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, m_fEnterTimer);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, m_fEnterTimer);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, m_fEnterTimer);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, m_fEnterTimer);

		//頂点バッファをアンロック
		m_pVtxBuff->Unlock();

		m_nCntEnter = 0;
	}

	// ポジションの設定
	m_apScene2D->SetPosition(m_pos,m_rot,m_position,m_flength);
}

//=============================================================================
// 描画処理
//=============================================================================
void CPressEntor::Draw(void)
{
	m_apScene2D->Draw();
}

//=============================================================================
// プレスエンターの生成
//=============================================================================
CPressEntor *CPressEntor::Create(D3DXVECTOR3 pos, float widtgh, float height)
{
	CPressEntor *pPreesEntor;

	pPreesEntor = new CPressEntor;

	pPreesEntor->Init(pos, widtgh, height);

	// 共有テクスチャを割り当てる
	pPreesEntor->BindTexture(m_pTexture);

	return pPreesEntor;
}
