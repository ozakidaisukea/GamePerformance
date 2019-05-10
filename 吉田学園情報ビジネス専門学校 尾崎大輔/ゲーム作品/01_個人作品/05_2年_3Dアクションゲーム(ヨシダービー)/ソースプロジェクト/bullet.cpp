//=============================================================================
//
// bullet処理 [bullet.cpp]
// Author : Ozaki
//
//=============================================================================
#include "main.h"
#include "bullet.h"
#include "scene.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "debugproc.h"
#include "scene.h"

//=============================================================================
// 静的メンバ-変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9 CBullet::m_pTexture = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CBullet::CBullet(int nCntPriority, OBJTYPE objtype) :CBillboard(4, CScene::OBJTYPE_BULLET)
{
	// ポリゴンの位置を設定
	m_pos = D3DXVECTOR3(0, 0, 0.0f);

	m_nLife = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CBullet::~CBullet()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CBullet::Init(void)
{
	CBillboard::SetPosition(m_pos);

	CBillboard::Init();

	m_nLife = 100;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CBullet::Uninit(void)
{
	// 頂点バッファの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}

	// テクスチャの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	CScene::Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CBullet::Update(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = NULL;

	// マネージャーを取得
	pDevice = CManager::GetRenderer()->GetDevice();

	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;

	pos = CBillboard::GetPosition();

	pos += m_move;

	m_nLife -= 1;

	CBillboard::SetPosition(pos);

	// 表示時間が0になると消す
	if (m_nLife <= 0)
	{
		Uninit();
	}

	// 壁の当たり判定
	if (pos.x >= 150)
	{
		pos.x = 150 - 1;
		Uninit();
	}
	if (pos.x <= -150)
	{
		pos.x = -150 - 1;
		Uninit();
	}
	if (pos.z <= -150)
	{
		pos.z = -150 - 1;
		Uninit();
	}
	if (pos.z >= 150)
	{
		pos.z = 150 - 1;
		Uninit();
	}

	float fgsk[4];

	// 奥
	m_VecA = m_aPos[0] - m_aPos[1];
	m_VecC = pos - m_aPos[0];
	fgsk[0] = ((m_VecA.z * m_VecC.x) - (m_VecA.x * m_VecC.z));
	if (fgsk[0] > 0)
	{
		Uninit();
	}

	// 手前
	m_VecA = m_aPos[0] - m_aPos[1];
	m_VecC = pos - m_aPos[0];
	fgsk[1] = ((m_VecA.z * m_VecC.x) - (m_VecA.x * m_VecC.z));
	if (fgsk[1] > 0)
	{
		Uninit();
	}

	// 右
	m_VecA = m_aPos[0] - m_aPos[1];
	m_VecC = pos - m_aPos[0];
	fgsk[2] = ((m_VecA.z * m_VecC.x) - (m_VecA.x * m_VecC.z));
	if (fgsk[2] > 0)
	{
		Uninit();
	}

	// 左
	m_VecA = m_aPos[0] - m_aPos[1];
	m_VecC = pos - m_aPos[0];
	fgsk[3] = ((m_VecA.z * m_VecC.x) - (m_VecA.x * m_VecC.z));
	if (fgsk[3] > 0)
	{
		Uninit();
	}

	m_VecA = m_aPos[0] - m_aPos[1];
	m_VecC = pos - m_aPos[0];
	fgsk[0] = ((m_VecA.z * m_VecC.x) - (m_VecA.x * m_VecC.z));
	if (fgsk[0] > 0)
	{
		Uninit();
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CBullet::Draw(void)
{
	CBillboard::Draw();
}

//=============================================================================
// シーン3Dの生成
//=============================================================================
CBullet *CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	CBullet *pBullet;

	pBullet = new CBullet(5);

	pBullet->m_pos = pos;
	pBullet->m_move = move;
	pBullet->Init();


	// 共有テクスチャを割り当てる
	pBullet->BindTexture(m_pTexture);

	return pBullet;
}

//=============================================================================
// 共有テクスチャを割り当てる
//=============================================================================
void CBullet::BindTexture(LPDIRECT3DTEXTURE9 texture)
{
	m_pTexture = texture;
}