//=============================================================================
//
// アイテムの処理 [item.cpp]
// Author : Ozaki
//
//=============================================================================
#include "item.h"
#include "player.h"
#include "renderer.h"
#include "main.h"
#include "manager.h"
#include "scene2D.h"
#include "input.h"
#include "gauge.h"
#include "sound.h"
#include "score.h"
#include "game.h"

//=============================================================================
// 静的メンバ変数
//=============================================================================
LPDIRECT3DTEXTURE9 CItem::m_pTexture[MAX_ITEM] = {};
CScore*CItem::m_apScore = NULL;
//=============================================================================
// コンストラクタ
//=============================================================================
CItem::CItem() :CScene2D(3)
{

}

//=============================================================================
// デストラクタ
//=============================================================================
CItem::~CItem()
{

}

//=============================================================================
// ロード
//=============================================================================
HRESULT CItem::Load(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = NULL;

	pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの生成0
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\game\\item0.png",
		&m_pTexture[0]);

	// テクスチャの生成1
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\game\\item0_high.png",
		&m_pTexture[1]);

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\game\\item1.png",
		&m_pTexture[2]);

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\game\\item1_high.png",
		&m_pTexture[3]);

	return S_OK;
}

//=============================================================================
// アンロード
//=============================================================================
void CItem::Unload(void)
{
	for (int nCnt = 0; nCnt < MAX_ITEM; nCnt++)
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
HRESULT CItem::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, float widtgh, float height, ITEM_TYPE type)
{
	CScene2D::Init(pos, widtgh,height);
	m_move = move;
	m_widtgh = widtgh;
	m_height = height;

	SetObjtType(CScene::OBJTYPE_ITEM);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CItem::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CItem::Update(void)
{
	D3DXVECTOR3 Itempos;
	D3DXVECTOR3 Itemposold;

	Itempos = GetPosition();

	Itempos.y += m_move.y;

	// 移動量
	m_move.x -= 0.01f;

	Itempos.x += m_move.x;

	// ポジションの設定
	SetPosition(Itempos, m_rot, m_pos, m_flength);

	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = NULL;

	pDevice = CManager::GetRenderer()->GetDevice();

	// サウンドを取得
	CSound *pSound;
	pSound = CManager::GetSound();

	// オブジェクトタイプを取得
	for (int nCntPriority = 0; nCntPriority < MAX_PRIORITY1; nCntPriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
		{
			CScene2D *pScene;
			pScene = (CScene2D*)CScene::GetSCene(nCntScene,nCntPriority);

			// NULLチェック
			if (pScene != NULL)
			{
				CScene::OBJTYPE objttype;

				objttype = pScene->GetObjtType();

				if (objttype == CScene::OBJTYPE_PLAYER)
				{
					// プレイヤーのposを取得
					D3DXVECTOR3 playerpos;

					playerpos = pScene->GetPosition();

					if (Itempos.x < 0)
					{
						Itempos.x = SCREEN_WIDTH;
						Itemposold.x = Itempos.x;
					}

					if (Itempos.x > SCREEN_WIDTH)
					{
						Itempos.x = 0;
						Itemposold.x = Itempos.x;
					}

					// アイテムとプレイヤーの当たり判定
					if (Itempos.x - pScene->GetWidth() < playerpos.x && Itempos.x + pScene->GetWidth() > playerpos.x &&
						Itempos.y - pScene->GetHeigth() < playerpos.y && Itempos.y + pScene->GetHeigth() > playerpos.y)
					{
						CGauge::AddGauge(20);

						pSound->PlaySound(pSound->SOUND_LABEL_SE_SOSYAKU);

						Uninit();

					}
				}
			}
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CItem::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// 爆発の生成
//=============================================================================
CItem *CItem::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float widtgh, float height, ITEM_TYPE type)
{
	CItem *pItem;

	pItem = new CItem;

	pItem->Init(pos, move, widtgh,height,type);

	pItem->m_type = type;

	// 共有テクスチャを割り当てる
	pItem->BindTexture(m_pTexture[type]);

	return pItem;
}