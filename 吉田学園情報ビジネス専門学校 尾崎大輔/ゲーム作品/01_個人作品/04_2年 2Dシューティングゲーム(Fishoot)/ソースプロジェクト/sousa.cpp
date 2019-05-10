//=============================================================================
//
// 操作処理 [sousa.cpp]
// Author : Ozaki
//
//=============================================================================
#include "sousa.h"
#include "manager.h"
#include "renderer.h"
#include "bg.h"
#include "fade.h"
#include "logo.h"
#include "logosyake.h"
#include "Pressentor.h"
#include "sound.h"
#include "joypad.h"
#include "item.h"

//=============================================================================
// 静的メンバ変数
//=============================================================================
LPDIRECT3DTEXTURE9	CSousa::m_pTexture = NULL;
LPDIRECT3DVERTEXBUFFER9 CSousa::m_pVtxBuff = NULL;
CSound*CSousa::m_pSound = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CSousa::CSousa()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CSousa::~CSousa()
{

}

//=============================================================================
// ロード
//=============================================================================
HRESULT CSousa::Load(void)
{
	CRenderer *pRenderer;

	pRenderer = new CRenderer;

	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = NULL;

	pDevice = CManager::GetRenderer()->GetDevice();

	return S_OK;
}

//=============================================================================
// アンロード
//=============================================================================
void CSousa::Unload(void)
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
HRESULT CSousa::Init(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = NULL;

	pDevice = CManager::GetRenderer()->GetDevice();

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VRETEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//ローカル変数
	VERTEX_2D*pVtx;

	//頂点バッファをロックし、頂点データのポインタの取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

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
	m_pVtxBuff->Unlock();

	// ロゴの読み込み
	CLogo::Load();

	// プレスエンターの読み込み
	CPressEntor::Load();

	// ロゴの生成
	CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0), 900.0f, 500.0f, CLogo::LOGO_SOUSA);

	// プレスエンターの生成
	CPressEntor::Create(D3DXVECTOR3( 1050.0f, 600.0f, 0), 200.0f, 70.0f);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CSousa::Uninit(void)
{
	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();

		m_pTexture = NULL;
	}
	CScene::ReleaseAll();
}

//=============================================================================
// 更新処理
//=============================================================================
void CSousa::Update(void)
{
	// キーボードを取得
	CInputKeyboard *InputKeyboard;
	InputKeyboard = CManager::GetInputKeyboard();

	// キーボードを取得
	CInputjoypad *InputJoypad;
	InputJoypad = CManager::GetInputJoypad();

	// サウンドを取得
	CSound *pSound;
	pSound = CManager::GetSound();

	m_pSound = pSound;

	// フェードを取得
	CFade *pFade;
	pFade = CManager::GetFade();

	if (pFade->GetFade() == CFade::FADE_NONE)
	{
		if (InputKeyboard->GetTrigger(DIK_RETURN) == true || InputJoypad->GetPress(CInputjoypad::DIJS_BOTTON_START) == true
			|| InputJoypad->GetTrigger(CInputjoypad::DIJS_BOTTON_B) == true)
		{
			pFade->SetFade(CManager::MODE_TUTORIAL);

			pSound->PlaySound(pSound->SOUND_LABEL_SE_DECISON);
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CSousa::Draw(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = NULL;

	pDevice = CManager::GetRenderer()->GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VRETEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);
}

//=============================================================================
// タイトルの生成
//=============================================================================
CSousa*CSousa::Create(void)
{
	CSousa *pSousa;

	pSousa = new CSousa;

	pSousa->Init();

	return pSousa;
}