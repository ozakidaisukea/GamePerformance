//=============================================================================
//
// �J�������� [camera.cpp]
// Author :  Meguro Mikiya
//
//=============================================================================
#include "camera.h"
#include "input.h"
#include "player.h"
#include "main.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MOVE_CAMERA			(17.3f)						//���f���ړ���
#define MOVE_SIN_COS_TOP_CAMERA	(0.75f)						//�J�����ړ���
#define MOVE_SIN_COS_BOT_CAMERA	(0.25f)						//�J�����ړ���
#define MAX_CAMERA (4)
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
Camera g_Camera[MAX_CAMERA];	//�J�����̏��
float fLength;
//=============================================================================
// �J�����̏���������
//=============================================================================
void InitCamera(void)
{
	//�r���[�|�[�g�̏�����
	g_Camera[0].Viewport.X = 0;
	g_Camera[0].Viewport.Y = 0;
	g_Camera[0].Viewport.Width = SCREEN_WIDTH;
	g_Camera[0].Viewport.Height = SCREEN_HEIGHT;
	g_Camera[0].Viewport.MinZ = 0.0f;
	g_Camera[0].Viewport.MaxZ = 1.0f;

	g_Camera[0].posV = D3DXVECTOR3(0.0f, 70.0f, -200.0f);
	g_Camera[0].posR = D3DXVECTOR3(0.0f, 50.0f, 0.0f);
	g_Camera[0].posU = D3DXVECTOR3(0.0f, 0.1f, 0.0f);
	g_Camera[0].rotCamera = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Camera[0].nCounterAngle = 0;
	fLength = sqrtf(
		//X�̋��������߂�@X�̋�����2��
		(g_Camera[0].posR.x - g_Camera[0].posV.x) * (g_Camera[0].posR.x - g_Camera[0].posV.x)
		//Z�̋��������߂�@Z�̋�����2��
		+ (g_Camera[0].posR.z - g_Camera[0].posV.z) * (g_Camera[0].posR.z - g_Camera[0].posV.z));

	//�r���[�|�[�g�̏�����
	g_Camera[1].Viewport.X = 0;
	g_Camera[1].Viewport.Y = 420;
	g_Camera[1].Viewport.Width = 300;
	g_Camera[1].Viewport.Height = SCREEN_HEIGHT;
	g_Camera[1].Viewport.MinZ = 0.0f;
	g_Camera[1].Viewport.MaxZ = 1.0f;

	g_Camera[1].posV = D3DXVECTOR3(0.0f, 6000.0f, 0.0f);
	g_Camera[1].posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Camera[1].posU = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	g_Camera[1].rotCamera = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Camera[1].nCounterAngle = 0;


	//���݂̃��[�h���擾
	MODE Mode = GetMode();
#if 0
	switch (Mode)
	{
	case MODE_GAME:
		//�r���[�|�[�g�̏�����
		g_Camera[1].Viewport.X = 0;
		g_Camera[1].Viewport.Y = 420;
		g_Camera[1].Viewport.Width = 300;
		g_Camera[1].Viewport.Height = SCREEN_HEIGHT;
		g_Camera[1].Viewport.MinZ = 0.0f;
		g_Camera[1].Viewport.MaxZ = 1.0f;

		g_Camera[1].posV = D3DXVECTOR3(0.0f, 6000.0f, 0.0f);
		g_Camera[1].posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Camera[1].posU = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		g_Camera[1].rotCamera = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Camera[1].nCounterAngle = 0;
	}
	//fLength = sqrtf(
	//	//X�̋��������߂�@X�̋�����2��
	//	(g_Camera[1].posR.x - g_Camera[1].posV.x) * (g_Camera[1].posR.x - g_Camera[1].posV.x)
	//	//Z�̋��������߂�@Z�̋�����2��
	//	+ (g_Camera[1].posR.z - g_Camera[1].posV.z) * (g_Camera[1].posR.z - g_Camera[1].posV.z));
#endif
	
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

	PLAYER *pPlayer;
	//�v���C���[�̎擾
	pPlayer = GetPlayer();
	//���݂̃��[�h���擾
	MODE Mode = GetMode();

	switch (Mode)
	{
	case MODE_GAME:
		//�Œ���̃J�������s�ړ�

		//�f�o�b�N�J����
#if 0
		//�C�ӂ̃L�[A
		if (GetKeyboardPress(DIK_LEFT) == true)
		{
			if (GetKeyboardPress(DIK_UP) == true)
			{//�����ړ�
			 //�J�����̈ړ�	�J�����̈ړ�����p�x(�J�����̌��� + �p�x) * �ړ���
				g_Camera[0].posV.x -= sinf(g_Camera[0].rotCamera.y + D3DX_PI * 0.75f) * MOVE_CAMERA;
				g_Camera[0].posV.z -= cosf(g_Camera[0].rotCamera.y + D3DX_PI * 0.75f) * MOVE_CAMERA;
				//�J�����̒����_�̈ړ� �J�����̈ʒu + �J�����̊p�x * �J�����̋���
				g_Camera[0].posR.x = g_Camera[0].posV.x + sinf(g_Camera[0].rotCamera.y) * fLength;
				g_Camera[0].posR.z = g_Camera[0].posV.z + cosf(g_Camera[0].rotCamera.y) * fLength;
			}
			else if (GetKeyboardPress(DIK_DOWN) == true)
			{//����O�ړ�
			 //�J�����̈ړ�	�J�����̈ړ�����p�x(�J�����̌��� + �p�x) * �ړ���
				g_Camera[0].posV.x -= sinf(g_Camera[0].rotCamera.y + D3DX_PI * 0.25f) * MOVE_CAMERA;
				g_Camera[0].posV.z -= cosf(g_Camera[0].rotCamera.y + D3DX_PI * 0.25f) * MOVE_CAMERA;
				//�J�����̒����_�̈ړ� �J�����̈ʒu + �J�����̊p�x * �J�����̋���
				g_Camera[0].posR.x = g_Camera[0].posV.x + sinf(g_Camera[0].rotCamera.y) * fLength;
				g_Camera[0].posR.z = g_Camera[0].posV.z + cosf(g_Camera[0].rotCamera.y) * fLength;
			}
			else
			{
				//�J�����̈ړ�	�J�����̈ړ�����p�x(�J�����̌��� + �p�x) * �ړ���
				g_Camera[0].posV.x -= sinf(g_Camera[0].rotCamera.y + D3DX_PI * 0.5f) * MOVE_CAMERA;
				g_Camera[0].posV.z -= cosf(g_Camera[0].rotCamera.y + D3DX_PI * 0.5f) * MOVE_CAMERA;
				//�J�����̒����_�̈ړ� �J�����̈ʒu + �J�����̊p�x * �J�����̋���
				g_Camera[0].posR.x = g_Camera[0].posV.x + sinf(g_Camera[0].rotCamera.y) * fLength;
				g_Camera[0].posR.z = g_Camera[0].posV.z + cosf(g_Camera[0].rotCamera.y) * fLength;
			}
		}
		//�C�ӂ̃L�[D
		else if (GetKeyboardPress(DIK_RIGHT) == true)
		{
			if (GetKeyboardPress(DIK_UP) == true)
			{//�E���ړ�
			 //�J�����̈ړ�	�J�����̈ړ�����p�x(�J�����̌��� + �p�x) * �ړ���
				g_Camera[0].posV.x -= sinf(g_Camera[0].rotCamera.y - D3DX_PI * 0.75f) * MOVE_CAMERA;
				g_Camera[0].posV.z -= cosf(g_Camera[0].rotCamera.y - D3DX_PI * 0.75f) * MOVE_CAMERA;
				//�J�����̒����_�̈ړ� �J�����̈ʒu + �J�����̊p�x * �J�����̋���
				g_Camera[0].posR.x = g_Camera[0].posV.x + sinf(g_Camera[0].rotCamera.y) * fLength;
				g_Camera[0].posR.z = g_Camera[0].posV.z + cosf(g_Camera[0].rotCamera.y) * fLength;
			}
			else if (GetKeyboardPress(DIK_DOWN) == true)
			{//�E��O�ړ�
			 //�J�����̈ړ�	�J�����̈ړ�����p�x(�J�����̌��� + �p�x) * �ړ���
				g_Camera[0].posV.x -= sinf(g_Camera[0].rotCamera.y - D3DX_PI * 0.25f) * MOVE_CAMERA;
				g_Camera[0].posV.z -= cosf(g_Camera[0].rotCamera.y - D3DX_PI * 0.25f) * MOVE_CAMERA;
				//�J�����̒����_�̈ړ� �J�����̈ʒu + �J�����̊p�x * �J�����̋���
				g_Camera[0].posR.x = g_Camera[0].posV.x + sinf(g_Camera[0].rotCamera.y) * fLength;
				g_Camera[0].posR.z = g_Camera[0].posV.z + cosf(g_Camera[0].rotCamera.y) * fLength;
			}
			else
			{
				//�J�����̈ړ�	�J�����̈ړ�����p�x(�J�����̌��� + �p�x) * �ړ���
				g_Camera[0].posV.x += sinf(g_Camera[0].rotCamera.y + D3DX_PI * 0.5f) * MOVE_CAMERA;
				g_Camera[0].posV.z += cosf(g_Camera[0].rotCamera.y + D3DX_PI * 0.5f) * MOVE_CAMERA;
				//�J�����̒����_�̈ړ� �J�����̈ʒu + �J�����̊p�x * �J�����̋���
				g_Camera[0].posR.x = g_Camera[0].posV.x + sinf(g_Camera[0].rotCamera.y) * fLength;
				g_Camera[0].posR.z = g_Camera[0].posV.z + cosf(g_Camera[0].rotCamera.y) * fLength;
			}
		}
		else if (GetKeyboardPress(DIK_UP) == true)
		{//���ړ�
		 //�J�����̈ړ�	�J�����̈ړ�����p�x(�J�����̌��� + �p�x) * �ړ���
			g_Camera[0].posV.x += sinf(g_Camera[0].rotCamera.y) * MOVE_CAMERA;
			g_Camera[0].posV.z += cosf(g_Camera[0].rotCamera.y) * MOVE_CAMERA;
			//�J�����̒����_�̈ړ� �J�����̈ʒu + �J�����̊p�x * �J�����̋���
			g_Camera[0].posR.x = g_Camera[0].posV.x + sinf(g_Camera[0].rotCamera.y) * fLength;
			g_Camera[0].posR.z = g_Camera[0].posV.z + cosf(g_Camera[0].rotCamera.y) * fLength;


		}
		else if (GetKeyboardPress(DIK_DOWN) == true)
		{//��O�ړ�
		 //�J�����̈ړ�	�J�����̈ړ�����p�x(�J�����̌��� + �p�x) * �ړ���
			g_Camera[0].posV.x -= sinf(g_Camera[0].rotCamera.y) * MOVE_CAMERA;
			g_Camera[0].posV.z -= cosf(g_Camera[0].rotCamera.y) * MOVE_CAMERA;
			//�J�����̒����_�̈ړ� �J�����̈ʒu + �J�����̊p�x * �J�����̋���
			g_Camera[0].posR.x = g_Camera[0].posV.x + sinf(g_Camera[0].rotCamera.y) * fLength;
			g_Camera[0].posR.z = g_Camera[0].posV.z + cosf(g_Camera[0].rotCamera.y) * fLength;
		}

		//�C�ӂ̃L�[V
		if (GetKeyboardPress(DIK_V) == true)
		{
			g_Camera[0].rotCamera.y -= 0.05f;
			// -3.14���������
			if (g_Camera[0].rotCamera.y < -D3DX_PI)
			{
				// -3.14�� 3.14�ɂ���
				g_Camera[0].rotCamera.y += D3DX_PI * 2.0f;
			}
			g_Camera[0].posV.x = g_Camera[0].posR.x + sinf(g_Camera[0].rotCamera.y + D3DX_PI)* fLength;
			g_Camera[0].posV.z = g_Camera[0].posR.z + cosf(g_Camera[0].rotCamera.y + D3DX_PI)* fLength;

		}
		//�C�ӂ̃L�[B
		if (GetKeyboardPress(DIK_B) == true)
		{
			g_Camera[0].rotCamera.y += 0.05f;
			// 3.14��������
			if (g_Camera[0].rotCamera.y > D3DX_PI)
			{
				// 3.14�� -3.14�ɂ���
				g_Camera[0].rotCamera.y -= D3DX_PI * 2.0f;
			}
			g_Camera[0].posV.x = g_Camera[0].posR.x + sinf(g_Camera[0].rotCamera.y + D3DX_PI)* fLength;
			g_Camera[0].posV.z = g_Camera[0].posR.z + cosf(g_Camera[0].rotCamera.y + D3DX_PI)* fLength;

	}
		//�C�ӂ̃L�[Q
		if (GetKeyboardPress(DIK_Q) == true)
		{
			g_Camera[0].rotCamera.y -= 0.05f;
			// -3.14���������
			if (g_Camera[0].rotCamera.y < -D3DX_PI)
			{
				// -3.14�� 3.14�ɂ���
				g_Camera[0].rotCamera.y += D3DX_PI * 2.0f;
			}
			g_Camera[0].posR.x = g_Camera[0].posV.x + sinf(g_Camera[0].rotCamera.y)* fLength;
			g_Camera[0].posR.z = g_Camera[0].posV.z + cosf(g_Camera[0].rotCamera.y)* fLength;

		}
		//�C�ӂ̃L�[E
		if (GetKeyboardPress(DIK_E) == true)
		{
			g_Camera[0].rotCamera.y += 0.05f;
			// 3.14��������
			if (g_Camera[0].rotCamera.y > D3DX_PI)
			{
				// 3.14�� -3.14�ɂ���
				g_Camera[0].rotCamera.y -= D3DX_PI * 2.0f;
			}
			g_Camera[0].posR.x = g_Camera[0].posV.x + sinf(g_Camera[0].rotCamera.y)* fLength;
			g_Camera[0].posR.z = g_Camera[0].posV.z + cosf(g_Camera[0].rotCamera.y)* fLength;

		}

		//�C�ӂ̃L�[T
		if (GetKeyboardPress(DIK_T) == true)
		{
			g_Camera[0].rotCamera.x += 2.5f;
			g_Camera[0].posR.y = g_Camera[0].rotCamera.x;
		}
		//�C�ӂ̃L�[G
		if (GetKeyboardPress(DIK_G) == true)
		{
			g_Camera[0].rotCamera.x -= 2.5f;
			g_Camera[0].posR.y = g_Camera[0].rotCamera.x;
		}
		//�C�ӂ̃L�[Y
		if (GetKeyboardPress(DIK_Y) == true)
		{
			g_Camera[0].posV.y += 2.0f;
		}
		//�C�ӂ̃L�[N
		if (GetKeyboardPress(DIK_H) == true)
		{
			g_Camera[0].posV.y -= 2.0f;
		}
#endif // 0

		//�Q�[���J����
#if 1
		g_Camera[0].posRDest.x = pPlayer->pos.x - sinf(pPlayer->rot.y) * 10;
		//g_Camera[0].posRDest.y = pPlayer->pos.y - sinf(pPlayer->rot.x) * 30;
		g_Camera[0].posRDest.z = pPlayer->pos.z - cosf(pPlayer->rot.y) * 30;
		//
		g_Camera[0].posVDest.x = pPlayer->pos.x - sinf(g_Camera[0].rotCamera.y) * fLength / 1.5f;
		//g_Camera[0].posVDest.y = pPlayer->pos.y - sinf(g_Camera[0].rotCamera.x) * fLength;
		g_Camera[0].posVDest.z = pPlayer->pos.z - cosf(g_Camera[0].rotCamera.y) * fLength / 1.5f;

		////����
		g_Camera[0].posR.x += (g_Camera[0].posRDest.x - g_Camera[0].posR.x) * 0.2f + pPlayer->move.x;
		//g_Camera[0].posR.y += (g_Camera[0].posRDest.y - g_Camera[0].posR.y) * 0.2f;
		g_Camera[0].posR.z += (g_Camera[0].posRDest.z - g_Camera[0].posR.z) * 0.2f + pPlayer->move.z;

		g_Camera[0].posV.x += ((g_Camera[0].posVDest.x - g_Camera[0].posV.x) * 0.2f);
		//g_Camera[0].posV.y += ((g_Camera[0].posVDest.y - g_Camera[0].posV.y) * 0.2f) + 20;
		g_Camera[0].posV.z += ((g_Camera[0].posVDest.z - g_Camera[0].posV.z) * 0.2f);

		if (pPlayer->type == PALYERTYPE_WAIK)
		{
			//�J�������v���C���[�̌��ɂ���
			g_Camera[0].rotDest.y = (pPlayer->rot.y + D3DX_PI);
			//�J�����ƃv���C���[�̋��������߂�		
			//g_Camera[0].DiffAngle.x = g_Camera[0].rotDest.x - g_Camera[0].rotCamera.x;
			g_Camera[0].DiffAngle.y = g_Camera[0].rotDest.y - g_Camera[0].rotCamera.y;
			//g_Camera[0].DiffAngle.z = g_Camera[0].rotDest.z - g_Camera[0].rotCamera.z;

			//�p�x�̐ݒ�
			if (g_Camera[0].DiffAngle.y > D3DX_PI)
			{
				g_Camera[0].DiffAngle.y -= D3DX_PI* 2.0f;
			}
			if (g_Camera[0].DiffAngle.y < -D3DX_PI)
			{
				g_Camera[0].DiffAngle.y += D3DX_PI* 2.0f;
			}
			//
			g_Camera[0].rotCamera.y += g_Camera[0].DiffAngle.y * 0.03f;

			if (g_Camera[0].rotCamera.y > D3DX_PI)
			{
				g_Camera[0].rotCamera.y -= D3DX_PI* 2.0f;
			}
			if (g_Camera[0].rotCamera.y < -D3DX_PI)
			{
				g_Camera[0].rotCamera.y += D3DX_PI* 2.0f;
			}

		}

		//�ォ��J����
		g_Camera[1].posV = D3DXVECTOR3(pPlayer->pos.x, 6000.0f, pPlayer->pos.z - 900.0f);
		g_Camera[1].posR = D3DXVECTOR3(pPlayer->pos.x ,0.0f, pPlayer->pos.z - 900.0f);
#endif
		break;

	case MODE_TITLE:
		//�J�E���^�[�̉��Z
		g_Camera[0].nCounterAngle++;
		if (g_Camera[0].nCounterAngle < 300)
		{		
			g_Camera[0].rotCamera.y = 0.0f * D3DX_PI;
			g_Camera[0].posV = D3DXVECTOR3(300.0f, 150.0f, 0.0f);
			g_Camera[0].posR = D3DXVECTOR3(330, 150, -610);
		}
		if (g_Camera[0].nCounterAngle == 300)
		{
			g_Camera[0].rotCamera.y = 0.0f * D3DX_PI;
			g_Camera[0].posV = D3DXVECTOR3(1000.0f, 1500.0f, -2000.0f);
			g_Camera[0].posR = D3DXVECTOR3(1000.0f, 1000.0f, 3000.0f);	
		}
		if (g_Camera[0].nCounterAngle == 600)
		{
			g_Camera[0].rotCamera.y = 0.3f * D3DX_PI;
			g_Camera[0].posV = D3DXVECTOR3(7200.0f, 500.0f, 7500.0f);
			g_Camera[0].posR = D3DXVECTOR3(7200.0f, 480.0f, 7500.0f);

		}
		if (g_Camera[0].nCounterAngle == 900)
		{
			g_Camera[0].rotCamera.y = 0.0f * D3DX_PI;
			g_Camera[0].posV = D3DXVECTOR3(1900.0f, 300.0f, 6600.0f);
			g_Camera[0].posR = D3DXVECTOR3(1900.0f, 450.0f, 6600.0f);
		}
		if (g_Camera[0].nCounterAngle == 1200)
		{
			g_Camera[0].nCounterAngle = 0;
			g_Camera[0].rotCamera.y = 0.0f * D3DX_PI;
		}

		g_Camera[0].rotCamera.y += 0.003f;
		// 3.14��������
		if (g_Camera[0].rotCamera.y > D3DX_PI)
		{
			// 3.14�� -3.14�ɂ���
			g_Camera[0].rotCamera.y -= D3DX_PI * 2.0f;
		}
		g_Camera[0].posV.x = g_Camera[0].posR.x + sinf(g_Camera[0].rotCamera.y + D3DX_PI)* fLength;
		g_Camera[0].posV.z = g_Camera[0].posR.z + cosf(g_Camera[0].rotCamera.y + D3DX_PI)* fLength;
		break;
	}
}

//=============================================================================
// �J�����̐ݒ菈��
//=============================================================================
void SetCamera(int nIdxCamera)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾


												//�@�r���[�|�[�g�̐ݒ�
	pDevice->SetViewport(&g_Camera[nIdxCamera].Viewport);

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_Camera[nIdxCamera].mtxProjection);

	if (nIdxCamera == 0)
	{
		// �v���W�F�N�V�����}�g���b�N�X���쐬
		D3DXMatrixPerspectiveFovLH(&g_Camera[nIdxCamera].mtxProjection,
			D3DXToRadian(45.0f),
			(float)g_Camera[nIdxCamera].Viewport.Width / (float)g_Camera[nIdxCamera].Viewport.Height,
			10.0f,
			6000.0f);
	}
	if (nIdxCamera == 1)
	{
		// �v���W�F�N�V�����}�g���b�N�X���쐬
		D3DXMatrixPerspectiveFovLH(&g_Camera[nIdxCamera].mtxProjection,
			D3DXToRadian(30.0f),
			(float)g_Camera[nIdxCamera].Viewport.Width  / (float)g_Camera[nIdxCamera].Viewport.Height,
			10.0f,
			6000.0f);
	}
	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &g_Camera[nIdxCamera].mtxProjection);

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_Camera[nIdxCamera].mtxView);

	// �r���[�}�g���b�N�X���쐬
	D3DXMatrixLookAtLH(&g_Camera[nIdxCamera].mtxView,
		&g_Camera[nIdxCamera].posV,
		&g_Camera[nIdxCamera].posR,
		&g_Camera[nIdxCamera].posU);

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &g_Camera[nIdxCamera].mtxView);
}

//=============================================================================
// �J�����̎擾
//=============================================================================
Camera *GetCamera(void)
{
	return &g_Camera[0];
}