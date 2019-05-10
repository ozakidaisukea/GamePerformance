//=============================================================================
//
// ���C�g���� [light.cpp]
// Author :  Meguro Mikiya
//
//=============================================================================
#include "light.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_LIGHT			(3)	// ���C�g�̍ő吔


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
D3DLIGHT9	g_aLight[MAX_LIGHT];

//=============================================================================
// ���C�g�̏���������
//=============================================================================
void InitLight(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXVECTOR3 vecDir;

	for (int nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{
		// ���C�g���N���A����
		ZeroMemory(&g_aLight[nCntLight], sizeof(D3DLIGHT9));
	}

	// ���C�g�̎�ނ�ݒ�
	g_aLight[0].Type = D3DLIGHT_DIRECTIONAL;

	// ���C�g�̊g�U����ݒ�
	g_aLight[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// ���C�g�̕����̐ݒ�
	vecDir = D3DXVECTOR3(0.2f, -0.8f, 0.4f);
	D3DXVec3Normalize(&vecDir, &vecDir);
	g_aLight[0].Direction = vecDir;

	// ���C�g�̎�ނ�ݒ�
	g_aLight[1].Type = D3DLIGHT_DIRECTIONAL;

	// ���C�g�̊g�U����ݒ�
	g_aLight[1].Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.7f, 0.7f);

	// ���C�g�̕����̐ݒ�
	vecDir = D3DXVECTOR3(-0.7f, -0.4f, -0.4f);
	D3DXVec3Normalize(&vecDir, &vecDir);
	g_aLight[1].Direction = vecDir;

	// ���C�g�̎�ނ�ݒ�
	g_aLight[2].Type = D3DLIGHT_DIRECTIONAL;

	// ���C�g�̊g�U����ݒ�
	g_aLight[2].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);

	// ���C�g�̕����̐ݒ�
	vecDir = D3DXVECTOR3(0.8f, -0.1f, 0.4f);
	D3DXVec3Normalize(&vecDir, &vecDir);
	g_aLight[2].Direction = vecDir;

	for (int nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{
		//�O�̃��C�g�ɏ�������
		// ���C�g��ݒ肷��
		pDevice->SetLight(nCntLight, &g_aLight[nCntLight]);
		// ���C�g��L���ɂ���
		pDevice->LightEnable(nCntLight, TRUE);
	}
}

//=============================================================================
// ���C�g�̏I������
//=============================================================================
void UninitLight(void)
{
}

//=============================================================================
// ���C�g�̍X�V����
//=============================================================================
void UpdateLight(void)
{
}

