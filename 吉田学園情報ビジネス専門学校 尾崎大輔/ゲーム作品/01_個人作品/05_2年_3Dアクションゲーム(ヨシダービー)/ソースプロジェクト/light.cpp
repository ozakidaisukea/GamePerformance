//=============================================================================
//
// ���C�g���� [light.cpp]
// Author : Ozaki
//
//=============================================================================
#include "light.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CLight::CLight()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CLight::~CLight()
{
}

//=============================================================================
// ���C�g�̏���������
//=============================================================================
HRESULT CLight::Init(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = NULL;

	pDevice = CManager::GetRenderer()->GetDevice();

	D3DXVECTOR3 vecDir;

	// ���C�g���N���A����
	ZeroMemory(&m_light[0], sizeof(D3DLIGHT9));
	ZeroMemory(&m_light[1], sizeof(D3DLIGHT9));
	ZeroMemory(&m_light[2], sizeof(D3DLIGHT9));

	// ���C�g�̎�ނ�ݒ�
	m_light[0].Type = D3DLIGHT_DIRECTIONAL;
	m_light[1].Type = D3DLIGHT_DIRECTIONAL;
	m_light[2].Type = D3DLIGHT_DIRECTIONAL;

	// ���C�g�̊g�U����ݒ�
	m_light[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_light[1].Diffuse = D3DXCOLOR(0.65f, 0.65f, 0.65f, 1.0f);
	m_light[2].Diffuse = D3DXCOLOR(0.15f, 0.15f, 0.15f, 1.0f);

	// ���C�g�̕����̐ݒ�
	vecDir = D3DXVECTOR3(0.22f, -0.87f, 0.44f);

	D3DXVec3Normalize(&vecDir, &vecDir);

	m_light[0].Direction = vecDir;

	// ���C�g�̕����̐ݒ�
	vecDir = D3DXVECTOR3(-0.18f, 0.88f, -0.44f);

	D3DXVec3Normalize(&vecDir, &vecDir);

	m_light[1].Direction = vecDir;

	// ���C�g�̕����̐ݒ�
	vecDir = D3DXVECTOR3(0.89f, -0.11f, 0.44f);

	D3DXVec3Normalize(&vecDir, &vecDir);

	m_light[2].Direction = vecDir;

	// ���C�g��ݒ肷��
	pDevice->SetLight(0, &m_light[0]);
	pDevice->SetLight(1, &m_light[1]);
	pDevice->SetLight(2, &m_light[2]);

	// ���C�g��L���ɂ���
	pDevice->LightEnable(0, TRUE);
	pDevice->LightEnable(1, TRUE);
	pDevice->LightEnable(2, TRUE);

	return S_OK;
}

//=============================================================================
// ���C�g�̏I������
//=============================================================================
void CLight::Uninit(void)
{
}

//=============================================================================
// ���C�g�̍X�V����
//=============================================================================
void CLight::Update(void)
{
}

