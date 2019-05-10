//=============================================================================
//
// ���C�g���� [light.cpp]
// Author : Jukiya Hayakawa
//
//=============================================================================
#include "light.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//=============================================================================
// ���C�g�̃R���X�g���N�^
//=============================================================================
CLight::CLight()
{

}
//=============================================================================
// ���C�g�̃f�X�g���N�^
//=============================================================================
CLight::~CLight()
{

}

//=============================================================================
// ���C�g�̐���
//=============================================================================
CLight *CLight::Create(void)
{
	CLight *pLight = NULL;		//���C�g�̃|�C���^

	if (pLight == NULL)
	{
		pLight = new CLight;	//���I�m��
		if (pLight != NULL)
		{
			pLight->Init();		//����������
		}
	}
	return pLight;
}

//=============================================================================
// ���C�g�̏���������
//=============================================================================
void CLight::Init(void)
{
	//�����_�����O�̎擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();

	D3DXVECTOR3 vecDir;

	// ���C�g���N���A����
	ZeroMemory(&m_light, sizeof(D3DLIGHT9));

	// ���C�g�̎�ނ�ݒ�
	m_light[0].Type = D3DLIGHT_DIRECTIONAL;
	m_light[1].Type = D3DLIGHT_DIRECTIONAL;
	m_light[2].Type = D3DLIGHT_DIRECTIONAL;

	// ���C�g�̊g�U����ݒ�
	m_light[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_light[1].Diffuse = D3DXCOLOR(0.65f, 0.65f, 0.65f, 1.0f);
	m_light[2].Diffuse = D3DXCOLOR(0.15f, 0.15f, 0.15f, 0.15f);

	// ���C�g�̕����̐ݒ�
	vecDir= D3DXVECTOR3(-0.25f, -0.87f, 0.44f);
	//vecDir = D3DXVECTOR3(0.8f, -0.5f, -0.2f);

	D3DXVec3Normalize(&vecDir, &vecDir);		//���K������

	m_light[0].Direction = vecDir;

	// ���C�g�̕����̐ݒ�
	vecDir = D3DXVECTOR3(-0.18f, 0.88f, -0.44f);

	D3DXVec3Normalize(&vecDir, &vecDir);		//���K������

	m_light[1].Direction = vecDir;

	// ���C�g�̕����̐ݒ�
	vecDir = D3DXVECTOR3(0.89f, -0.11f, 0.44f);

	D3DXVec3Normalize(&vecDir, &vecDir);		//���K������

	m_light[2].Direction = vecDir;

	if (pDevice != NULL)
	{
		// ���C�g��ݒ肷��
		pDevice->SetLight(0, &m_light[0]);
		pDevice->SetLight(1, &m_light[1]);
		pDevice->SetLight(2, &m_light[2]);
		// ���C�g��L���ɂ���
		pDevice->LightEnable(0, TRUE);
		// ���C�g��L���ɂ���
		pDevice->LightEnable(1, FALSE);
		// ���C�g��L���ɂ���
		pDevice->LightEnable(2, FALSE);
	}
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

