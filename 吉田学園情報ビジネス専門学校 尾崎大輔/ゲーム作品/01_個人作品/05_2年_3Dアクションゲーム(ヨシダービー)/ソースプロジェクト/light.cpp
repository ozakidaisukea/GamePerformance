//=============================================================================
//
// ライト処理 [light.cpp]
// Author : Ozaki
//
//=============================================================================
#include "light.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CLight::CLight()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CLight::~CLight()
{
}

//=============================================================================
// ライトの初期化処理
//=============================================================================
HRESULT CLight::Init(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = NULL;

	pDevice = CManager::GetRenderer()->GetDevice();

	D3DXVECTOR3 vecDir;

	// ライトをクリアする
	ZeroMemory(&m_light[0], sizeof(D3DLIGHT9));
	ZeroMemory(&m_light[1], sizeof(D3DLIGHT9));
	ZeroMemory(&m_light[2], sizeof(D3DLIGHT9));

	// ライトの種類を設定
	m_light[0].Type = D3DLIGHT_DIRECTIONAL;
	m_light[1].Type = D3DLIGHT_DIRECTIONAL;
	m_light[2].Type = D3DLIGHT_DIRECTIONAL;

	// ライトの拡散光を設定
	m_light[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_light[1].Diffuse = D3DXCOLOR(0.65f, 0.65f, 0.65f, 1.0f);
	m_light[2].Diffuse = D3DXCOLOR(0.15f, 0.15f, 0.15f, 1.0f);

	// ライトの方向の設定
	vecDir = D3DXVECTOR3(0.22f, -0.87f, 0.44f);

	D3DXVec3Normalize(&vecDir, &vecDir);

	m_light[0].Direction = vecDir;

	// ライトの方向の設定
	vecDir = D3DXVECTOR3(-0.18f, 0.88f, -0.44f);

	D3DXVec3Normalize(&vecDir, &vecDir);

	m_light[1].Direction = vecDir;

	// ライトの方向の設定
	vecDir = D3DXVECTOR3(0.89f, -0.11f, 0.44f);

	D3DXVec3Normalize(&vecDir, &vecDir);

	m_light[2].Direction = vecDir;

	// ライトを設定する
	pDevice->SetLight(0, &m_light[0]);
	pDevice->SetLight(1, &m_light[1]);
	pDevice->SetLight(2, &m_light[2]);

	// ライトを有効にする
	pDevice->LightEnable(0, TRUE);
	pDevice->LightEnable(1, TRUE);
	pDevice->LightEnable(2, TRUE);

	return S_OK;
}

//=============================================================================
// ライトの終了処理
//=============================================================================
void CLight::Uninit(void)
{
}

//=============================================================================
// ライトの更新処理
//=============================================================================
void CLight::Update(void)
{
}

