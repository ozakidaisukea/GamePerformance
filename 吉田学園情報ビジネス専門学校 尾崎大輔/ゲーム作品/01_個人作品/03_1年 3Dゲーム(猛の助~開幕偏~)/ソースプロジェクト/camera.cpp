//=============================================================================
//
// �J�������� [camera.cpp]
// Author : Ozaki
//
//=============================================================================
#include "camera.h"
#include "Input.h"
#include "Player.h"
#include "main.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MOVE			(30.0f)
#define MAX_X			(250)
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
Camera		g_camera;			// �J�����̏��
float		fLength;
//=============================================================================
// �J�����̏���������
//=============================================================================
void InitCamera(void)
{
	g_camera.posV	  = D3DXVECTOR3(0.0f, 220.0f, -320.0f);
	g_camera.posR	   = D3DXVECTOR3(0.0f, 0.0f, 0.0f); 
	g_camera.posVDest = D3DXVECTOR3(0.0f, 220.0f, -320.0f);
	g_camera.posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.posU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	g_camera.rot.y = atan2f(g_camera.posR.x - g_camera.posV.x ,g_camera.posR.z - g_camera.posV.z);
	g_camera.rotDest = g_camera.rot;
	g_camera.rotDiff = 0.0f;
	g_camera.nCounterAngle = 0;
	g_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.flength = sqrtf((g_camera.posRDest.x - g_camera.posVDest.x)*(g_camera.posRDest.x - g_camera.posVDest.x)
						+	(g_camera.posRDest.z - g_camera.posVDest.z)*(g_camera.posRDest.z - g_camera.posVDest.z));
	//g_camera.angle = sqrtf((g_camera.rot.x - g_camera.rot));
}

//=============================================================================
// �J�����̏I������
//=============================================================================
void UninitCamera(void)
{

}

//=============================================================================
// �J�����̍X�V����
//=============================================================================
void UpdateCamera(void)
{

	Player *pPlayer;
	pPlayer = GetPlayer();


	//if (GetKeyboardPress(DIK_T) == true)
	//{// ���_
	//	g_camera.rot.x += 0.05f;

	//	g_camera.posR.y = g_camera.rot.x;
	//}
	//else if (GetKeyboardPress(DIK_B) == true)
	//{// ���_
	//	g_camera.rot.x -= 0.05f;

	//	g_camera.posR.y = g_camera.rot.x;
	//}
	//else if (GetKeyboardPress(DIK_Z) == true)
	//{//���_��]
	//	g_camera.rot.y += 0.025f;

	//	g_camera.posV.x = g_camera.posR.x + sinf(g_camera.rot.y + D3DX_PI)* g_camera.flength;
	//	g_camera.posV.z = g_camera.posR.z + cosf(g_camera.rot.y + D3DX_PI)* g_camera.flength;

	//}
	//else if (GetKeyboardPress(DIK_C) == true)
	//{// ���_��]
	//	g_camera.rot.y -= 0.025f;

	//	g_camera.posV.x = g_camera.posR.x + sinf(g_camera.rot.y + D3DX_PI)* g_camera.flength;
	//	g_camera.posV.z = g_camera.posR.z + cosf(g_camera.rot.y + D3DX_PI)* g_camera.flength;
	//}

	//g_camera.posV.x = pPlayer->pos.x;
	//g_camera.posV.y = pPlayer->pos.y + 50;
	//g_camera.posV.z = pPlayer->pos.z - 100;

	//g_camera.posR.x = pPlayer->pos.x;
	//g_camera.posR.y = pPlayer->pos.y;
	//g_camera.posR.z = pPlayer->pos.z; 

	//���݂̃��[�h���擾
	MODE Mode = GetMode();

	switch (Mode)
	{
	case MODE_GAME:

		g_camera.posRDest.x = pPlayer->pos.x - sinf(pPlayer->rot.y)*MOVE;
		g_camera.posRDest.y = pPlayer->pos.y + sinf(pPlayer->rot.x)*MOVE / 2;
		g_camera.posRDest.z = pPlayer->pos.z - cosf(pPlayer->rot.y)*MOVE;
		//
		g_camera.posVDest.x = pPlayer->pos.x - sinf(g_camera.rot.y)*g_camera.flength;
		g_camera.posVDest.y = pPlayer->pos.y - sinf(g_camera.rot.x)*g_camera.flength;
		g_camera.posVDest.z = pPlayer->pos.z - cosf(g_camera.rot.y)*g_camera.flength;

		g_camera.posR.x += (g_camera.posRDest.x - g_camera.posR.x)* 0.5f;
		g_camera.posR.y += (g_camera.posRDest.y - g_camera.posR.y)* 0.5f;
		g_camera.posR.z += (g_camera.posRDest.z - g_camera.posR.z)* 0.5f;

		g_camera.posV.x += (g_camera.posVDest.x - g_camera.posV.x)* 0.5f;
		g_camera.posV.y += (g_camera.posVDest.y - g_camera.posV.y)* 0.5f + 50;
		g_camera.posV.z += (g_camera.posVDest.z - g_camera.posV.z)* 0.5f;

		g_camera.posVDest.x += pPlayer->posRDest.x;

		if (pPlayer->move.x >= -0.01f && pPlayer->move.x <= 0.01f && pPlayer->move.z >= -0.01f && pPlayer->move.z <= 0.01f)
		{
			g_camera.rotDest.y = pPlayer->rot.y + D3DX_PI;
			g_camera.rotDiff = g_camera.rotDest.y - g_camera.rot.y;

			if (g_camera.rotDiff > D3DX_PI)
			{
				g_camera.rotDiff -= D3DX_PI * 2;
			}
			if (g_camera.rotDiff < -D3DX_PI)
			{
				g_camera.rotDiff += D3DX_PI * 2;
			}

			g_camera.rot.y += g_camera.rotDiff * 0.1f;
			if (g_camera.rot.y > D3DX_PI)
			{
				g_camera.rot.y -= D3DX_PI * 2;
			}
			if (g_camera.rot.y < -D3DX_PI)
			{
				g_camera.rot.y += D3DX_PI * 2;
			}
		}
		break;

	case MODE_TITLE:
		//�J�E���^�[�̉��Z
		g_camera.nCounterAngle++;

		if (g_camera.nCounterAngle == 300)
		{
			g_camera.posV = D3DXVECTOR3(200.0f, 60.0f, 0.0f);
		}
		if (g_camera.nCounterAngle == 600)
		{
			g_camera.posV = D3DXVECTOR3(200.0f, 60.0f, 0.0f);
			g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			fLength = 200;
		}
		if (g_camera.nCounterAngle == 900)
		{
			g_camera.nCounterAngle = 0;
		}
		if (g_camera.nCounterAngle < 300)
		{
			g_camera.posV = D3DXVECTOR3(0.0f, 100.0f, -200.0f);
		}

		g_camera.rot.y += 0.003f;
		// 3.14��������
		if (g_camera.rot.y > D3DX_PI)
		{
			// 3.14�� -3.14�ɂ���
			g_camera.rot.y -= D3DX_PI * 2.0f;
		}
		//g_camera.posV.x = g_camera.posR.x + sinf(g_camera.rot.y + D3DX_PI)* fLength;
		//g_camera.posV.z = g_camera.posR.z + cosf(g_camera.rot.y + D3DX_PI)* fLength;

		g_camera.posV.x = g_camera.posR.x + sinf(g_camera.rot.y + D3DX_PI)* g_camera.flength;
		g_camera.posV.z = g_camera.posR.z + cosf(g_camera.rot.y + D3DX_PI)* g_camera.flength;

		break;
	}
}
//=============================================================================
// �J�����̐ݒ菈��
//=============================================================================
void SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera.mtxProjection);

	// �v���W�F�N�V�����}�g���b�N�X���쐬
	D3DXMatrixPerspectiveFovLH(&g_camera.mtxProjection,
		D3DXToRadian(45.0f),		// ����p
		(float)SCREEN_WIDTH /
		(float)SCREEN_HEIGHT,
		10.0f,						// ��O
		2000.0f);					// ���s


// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera.mtxProjection);

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera.mtxView);

	// �r���[�}�g���b�N�X���쐬
	D3DXMatrixLookAtLH(&g_camera.mtxView,
		&g_camera.posV,
		&g_camera.posR,
		&g_camera.posU);

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &g_camera.mtxView);
}
//=============================================================================
// �J�����̎擾
//=============================================================================
Camera *GetCamera(void)
{
	return &g_camera;
}
