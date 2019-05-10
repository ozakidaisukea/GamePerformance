//=============================================================================
//
// カメラ処理 [camera.cpp]
// Author : Ozaki
//
//=============================================================================
#include "camera.h"
#include "manager.h"
#include "renderer.h"
#include "scene3D.h"
#include "scene2D.h"
#include "input.h"
#include "player.h"
#include "owner.h"
#include "game.h"

//=============================================================================
// 静的メンバ変数
//=============================================================================
//CScene2D CCamera::m_Scene2D = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CCamera::CCamera()
{
	m_rot = D3DXVECTOR3(0, 0, 0);
}

//=============================================================================
// デストラクタ
//=============================================================================
CCamera::~CCamera()
{

}

//=============================================================================
// 入力処理
//=============================================================================
HRESULT CCamera::Init(void)
{
	m_camera.posV = D3DXVECTOR3(0.0f, 100.0f, -320.0f);
	m_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_camera.posVDest = D3DXVECTOR3(0.0f, 220.0f, -320.0f);
	m_camera.posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_camera.posU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_camera.rot.y = atan2f(m_camera.posR.x - m_camera.posV.x, m_camera.posR.z - m_camera.posV.z);
	m_camera.rotDest = m_camera.rot;
	m_camera.rotDiff = 0.0f;
	m_camera.nCounterAngle = 0;
	m_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_camera.flength = sqrtf((m_camera.posRDest.x - m_camera.posVDest.x)*(m_camera.posRDest.x - m_camera.posVDest.x)
	+ (m_camera.posRDest.z - m_camera.posVDest.z)*(m_camera.posRDest.z - m_camera.posVDest.z));

	fLength = sqrtf(
		//Xの距離を求める　Xの距離の2乗
		(m_camera.posR.x - m_camera.posV.x) * (m_camera.posR.x - m_camera.posV.x)
		//Zの距離を求める　Zの距離の2乗
		+ (m_camera.posR.z - m_camera.posV.z) * (m_camera.posR.z - m_camera.posV.z));
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CCamera::Uninit(void)
{

}

//=============================================================================
// 更新処理
//=============================================================================
void CCamera::Update(void)
{
	// キーボードを取得
	CInputKeyboard *InputKeyboard;
	InputKeyboard = CManager::GetInputKeyboard();
#if 1

#ifdef _DEBUG

	// ゴール前カメラ
	if (InputKeyboard->GetTrigger(DIK_1) == true)
	{
		//m_camera.posV = D3DXVECTOR3(300.0f, 120.0f, 3000.0f);
		//m_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 3000.0f);
	}


#endif // DEBUG


#endif // 0
	switch (m_mode)
	{
	// ゲーム時のカメラ
	case MODE_GAME:

		COwner *pOwner;
		pOwner = CGame::GetOwner();

		if (pOwner != NULL)
		{
			for (int nCnrCamera = 0; nCnrCamera < MAX_CAMERA; nCnrCamera++)
			{
				m_camera.posRDest.x = pOwner->Getpos().x - sinf(pOwner->Getrot().y) * 10;
				m_camera.posRDest.z = pOwner->Getpos().z - cosf(pOwner->Getrot().y) * 30;

				//
				m_camera.posVDest.x = pOwner->Getpos().x - sinf(m_camera.rot.y) * fLength / 1.5f;
				m_camera.posVDest.z = pOwner->Getpos().z - cosf(m_camera.rot.y) * fLength / 1.5f;

				//減速
				m_camera.posR.x += (m_camera.posRDest.x - m_camera.posR.x) * 0.2f + pOwner->Getmove().x;
				m_camera.posR.z += (m_camera.posRDest.z - m_camera.posR.z) * 0.2f + pOwner->Getmove().z;

				m_camera.posV.x += ((m_camera.posVDest.x - m_camera.posV.x) * 0.2f);
				m_camera.posV.z += ((m_camera.posVDest.z - m_camera.posV.z) * 0.2f);

				//カメラをプレイヤーの後ろにする
				m_camera.rotDest.y = (pOwner->Getrot().y + D3DX_PI);
				//カメラとプレイヤーの距離を求める
				m_camera.rotDiff = m_camera.rotDest.y - m_camera.rot.y;

				//角度の設定
				if (m_camera.rotDiff > D3DX_PI)
				{
					m_camera.rotDiff -= D3DX_PI* CAMERA_MOVE;
				}
				if (m_camera.rotDiff < -D3DX_PI)
				{
					m_camera.rotDiff += D3DX_PI* CAMERA_MOVE;
				}
				//
				m_camera.rot.y += m_camera.rotDiff * 0.5f;

				if (m_camera.rot.y > D3DX_PI)
				{
					m_camera.rot.y -= D3DX_PI* CAMERA_MOVE;
				}
				if (m_camera.rot.y < -D3DX_PI)
				{
					m_camera.rot.y += D3DX_PI* CAMERA_MOVE;
				}
			}
		}
		break;
	}


#ifdef _DEBUG


	//任意のキーA
	if (InputKeyboard->GetPress(DIK_LEFT) == true)
	{
		if (InputKeyboard->GetPress(DIK_UP) == true)
		{//左奥移動
		 //カメラの移動	カメラの移動する角度(カメラの向き + 角度) * 移動量
			m_camera.posV.x -= sinf(m_camera.rot.y + D3DX_PI * 0.75f) * 1.0f;
			m_camera.posV.z -= cosf(m_camera.rot.y + D3DX_PI * 0.75f) * 1.0f;
			//カメラの注視点の移動 カメラの位置 + カメラの角度 * カメラの距離
			m_camera.posR.x = m_camera.posV.x + sinf(m_camera.rot.y) * fLength;
			m_camera.posR.z = m_camera.posV.z + cosf(m_camera.rot.y) * fLength;
		}
		else if (InputKeyboard->GetPress(DIK_DOWN) == true)
		{//左手前移動
		 //カメラの移動	カメラの移動する角度(カメラの向き + 角度) * 移動量
			m_camera.posV.x -= sinf(m_camera.rot.y + D3DX_PI * 0.25f) * 1.0f;
			m_camera.posV.z -= cosf(m_camera.rot.y + D3DX_PI * 0.25f) * 1.0f;
			//カメラの注視点の移動 カメラの位置 + カメラの角度 * カメラの距離
			m_camera.posR.x = m_camera.posV.x + sinf(m_camera.rot.y) * fLength;
			m_camera.posR.z = m_camera.posV.z + cosf(m_camera.rot.y) * fLength;
		}
		else
		{
			//カメラの移動	カメラの移動する角度(カメラの向き + 角度) * 移動量
			m_camera.posV.x -= sinf(m_camera.rot.y + D3DX_PI * 0.5f) * 1.0f;
			m_camera.posV.z -= cosf(m_camera.rot.y + D3DX_PI * 0.5f) * 1.0f;
			//カメラの注視点の移動 カメラの位置 + カメラの角度 * カメラの距離
			m_camera.posR.x = m_camera.posV.x + sinf(m_camera.rot.y) * fLength;
			m_camera.posR.z = m_camera.posV.z + cosf(m_camera.rot.y) * fLength;
		}
	}
	//任意のキーD
	else if (InputKeyboard->GetPress(DIK_RIGHT) == true)
	{
		if (InputKeyboard->GetPress(DIK_UP) == true)
		{//右奥移動
		 //カメラの移動	カメラの移動する角度(カメラの向き + 角度) * 移動量
			m_camera.posV.x -= sinf(m_camera.rot.y - D3DX_PI * 0.75f) * 1.0f;
			m_camera.posV.z -= cosf(m_camera.rot.y - D3DX_PI * 0.75f) * 1.0f;
			//カメラの注視点の移動 カメラの位置 + カメラの角度 * カメラの距離
			m_camera.posR.x = m_camera.posV.x + sinf(m_camera.rot.y) * fLength;
			m_camera.posR.z = m_camera.posV.z + cosf(m_camera.rot.y) * fLength;
		}
		else if (InputKeyboard->GetPress(DIK_DOWN) == true)
		{//右手前移動
		 //カメラの移動	カメラの移動する角度(カメラの向き + 角度) * 移動量
			m_camera.posV.x -= sinf(m_camera.rot.y - D3DX_PI * 0.25f) * 1.0f;
			m_camera.posV.z -= cosf(m_camera.rot.y - D3DX_PI * 0.25f) * 1.0f;
			//カメラの注視点の移動 カメラの位置 + カメラの角度 * カメラの距離
			m_camera.posR.x = m_camera.posV.x + sinf(m_camera.rot.y) * fLength;
			m_camera.posR.z = m_camera.posV.z + cosf(m_camera.rot.y) * fLength;
		}
		else
		{
			//カメラの移動	カメラの移動する角度(カメラの向き + 角度) * 移動量
			m_camera.posV.x += sinf(m_camera.rot.y + D3DX_PI * 0.5f) * 1.0f;
			m_camera.posV.z += cosf(m_camera.rot.y + D3DX_PI * 0.5f) * 1.0f;
			//カメラの注視点の移動 カメラの位置 + カメラの角度 * カメラの距離
			m_camera.posR.x = m_camera.posV.x + sinf(m_camera.rot.y) * fLength;
			m_camera.posR.z = m_camera.posV.z + cosf(m_camera.rot.y) * fLength;
		}
	}
	if (InputKeyboard->GetPress(DIK_UP) == true)
	{//奥移動
	 //カメラの移動	カメラの移動する角度(カメラの向き + 角度) * 移動量
		m_camera.posV.x += sinf(m_camera.rot.y) * 1.0f;
		m_camera.posV.z += cosf(m_camera.rot.y) * 1.0f;
		//カメラの注視点の移動 カメラの位置 + カメラの角度 * カメラの距離
		m_camera.posR.x = m_camera.posV.x + sinf(m_camera.rot.y) * fLength;
		m_camera.posR.z = m_camera.posV.z + cosf(m_camera.rot.y) * fLength;
	}
	if (InputKeyboard->GetPress(DIK_DOWN) == true)
	{//手前移動
	 //カメラの移動	カメラの移動する角度(カメラの向き + 角度) * 移動量
		m_camera.posV.x -= sinf(m_camera.rot.y) * 1.0f;
		m_camera.posV.z -= cosf(m_camera.rot.y) * 1.0f;
		//カメラの注視点の移動 カメラの位置 + カメラの角度 * カメラの距離
		m_camera.posR.x = m_camera.posV.x + sinf(m_camera.rot.y) * fLength;
		m_camera.posR.z = m_camera.posV.z + cosf(m_camera.rot.y) * fLength;
	}


	//任意のキーT
	if (InputKeyboard->GetPress(DIK_T) == true)
	{
		m_camera.rot.x += 2.0f;

		m_camera.posR.y = m_camera.rot.x;
	}
	//任意のキーG
	if (InputKeyboard->GetPress(DIK_G) == true)
	{
		m_camera.rot.x -= 2.0f;

		m_camera.posR.y = m_camera.rot.x;
	}

	if (InputKeyboard->GetPress(DIK_Z) == true)
	{//視点回転
		m_camera.rot.y += 0.025f;

		m_camera.posV.x = m_camera.posR.x + sinf(m_camera.rot.y + D3DX_PI)* m_camera.flength;
		m_camera.posV.z = m_camera.posR.z + cosf(m_camera.rot.y + D3DX_PI)* m_camera.flength;

	}
	if (InputKeyboard->GetPress(DIK_C) == true)
	{// 視点回転
		m_camera.rot.y -= 0.025f;

		m_camera.posV.x = m_camera.posR.x + sinf(m_camera.rot.y + D3DX_PI)* m_camera.flength;
		m_camera.posV.z = m_camera.posR.z + cosf(m_camera.rot.y + D3DX_PI)* m_camera.flength;
	}

	//任意のキーY
	if (InputKeyboard->GetPress(DIK_Y) == true)
	{
		m_camera.posV.y += 2.0f;
	}
	//任意のキーN
	if (InputKeyboard->GetPress(DIK_H) == true)
	{
		m_camera.posV.y -= 2.0f;
	}

#endif // DEBUG
}

//=============================================================================
// カメラの設定処理
//=============================================================================
void CCamera::SetCamera(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = NULL;

	pDevice = CManager::GetRenderer()->GetDevice();

	// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_camera.mtxProjection);

	// プロジェクションマトリックスを作成
	D3DXMatrixPerspectiveFovLH(&m_camera.mtxProjection,
		D3DXToRadian(45.0f),		// 視野角
		(float)SCREEN_WIDTH /
		(float)SCREEN_HEIGHT,
		1.0f,						// 手前
		4000.0f);					// 奥行


	// プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_camera.mtxProjection);

	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_camera.mtxView);

	// ビューマトリックスを作成
	D3DXMatrixLookAtLH(&m_camera.mtxView,
		&m_camera.posV,
		&m_camera.posR,
		&m_camera.posU);

	// ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_camera.mtxView);
}
//=============================================================================
// カメラの取得
//=============================================================================
CCamera::Camera CCamera::GetCamera(void)
{
	return m_camera;
}

//=============================================================================
// モードの設定
//=============================================================================
void CCamera::SetMode(MODE mode)
{
	m_mode = mode;
}

//=============================================================================
// 向きを取得
//=============================================================================
D3DXVECTOR3 CCamera::GetRot(void)
{
	return m_camera.rot;
}