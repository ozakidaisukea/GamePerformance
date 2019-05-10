//=============================================================================
//
// �J�������� [camera.cpp]
// Author : Hodaka Niwa
//
//=============================================================================
#include "camera.h"
#include "player.h"
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define CAMERA_ANGEL_VIEW  (45.0f)    // �J�����̉�p
#define CAMERA_MOVE        (10.0f)    // �J�����̈ړ���
#define AROUND_SPEED       (0.02f)    // ��荞�ݑ��x�����l
#define AROUND_TIME        (50)       // ��荞�ݑ҂����ԏ����l
#define CAMERA_UP_DOWN_SPEED (3.0f)

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
Camera g_camera;  // �J�����̏��

//=============================================================================
// �J�����̏���������
//=============================================================================
void InitCamera(void)
{

	if (GetMode() == MODE_GAME)
	{
		g_camera.posV = D3DXVECTOR3(0.0f, 300.0f, -500.0f);  // ���݂̎��_��������
		g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);     // ���݂̒����_��������
	}
	else
	{
		g_camera.posV = D3DXVECTOR3(0.0f, 100.0f, -1000.0f);  // ���݂̎��_��������
		g_camera.posR = D3DXVECTOR3(0.0f, 100.0f, 0.0f);     // ���݂̒����_��������
	}
	g_camera.posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);   // �ړI�̎��_��������
	g_camera.posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);   // �ړI�̒����_��������
	g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);       // �x�N�g����������
	g_camera.rot  = D3DXVECTOR3(0.0f, 0.0f, 0.0f);       // ���݂̌�����������
	g_camera.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);    // �ړI�̌�����������
	g_camera.state = CAMERASTATE_NORMAL;                 // �ʏ�̏�Ԃ�
	g_camera.fWaraparoundSpeed = AROUND_SPEED;           // ��荞�ݑ��x��������
	g_camera.nWaraparoundTime = AROUND_TIME;             // ��荞�ݑ҂����Ԃ�������
	g_camera.nCounterTime = 0;                           // �҂����ԃJ�E���^�[��������
	g_camera.posVAdd = D3DXVECTOR3(0.0f, 0.0f, 0.0f);    // �ړI�̎��_���W��������
	g_camera.posRAdd = D3DXVECTOR3(0.0f, 0.0f, 0.0f);    // �ړI�̒����_���W��������

/*	g_camera.rot.y = -GetPlayer()->rot.y;
	g_camera.rotDest.y = -GetPlayer()->rot.y; */                                                          // �ړI�̌����͍ŏ��͓����ɂ���
	g_camera.fLength = 300.0f;  // �������v�Z
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
// �J��������̏���
#if 0
     //-----------------
     // ���_�ړ�
     //-----------------
	if (GetKeyboardPress(DIK_LEFT) == true)
	{// A�L�[�������ꂽ
		if (GetKeyboardPress(DIK_UP) == true)
		{// ������W�L�[�������ꂽ
			g_camera.posV.x -= sinf(g_camera.rot.y + (D3DX_PI * 0.75f)) * CAMERA_MOVE;
			g_camera.posV.z -= cosf(g_camera.rot.y + (D3DX_PI * 0.75f)) * CAMERA_MOVE;
		}
		else if (GetKeyboardPress(DIK_DOWN) == true)
		{// ������S�L�[�������ꂽ
			g_camera.posV.x -= sinf(g_camera.rot.y + (D3DX_PI * 0.25f)) * CAMERA_MOVE;
			g_camera.posV.z -= cosf(g_camera.rot.y + (D3DX_PI * 0.25f)) * CAMERA_MOVE;
		}
		else
		{// �����ɉ���������Ă��Ȃ�
			g_camera.posV.x -= sinf(g_camera.rot.y + (D3DX_PI * 0.5f)) * CAMERA_MOVE;
			g_camera.posV.z -= cosf(g_camera.rot.y + (D3DX_PI * 0.5f)) * CAMERA_MOVE;
		}

		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fLength;
		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fLength;
	}
	else if (GetKeyboardPress(DIK_RIGHT) == true)
	{// D�L�[�������ꂽ
		if (GetKeyboardPress(DIK_UP) == true)
		{// ������W�L�[�������ꂽ
			g_camera.posV.x -= sinf(g_camera.rot.y - (D3DX_PI * 0.75f)) * CAMERA_MOVE;
			g_camera.posV.z -= cosf(g_camera.rot.y - (D3DX_PI * 0.75f)) * CAMERA_MOVE;
		}
		else if (GetKeyboardPress(DIK_DOWN) == true)
		{// ������S�L�[�������ꂽ
			g_camera.posV.x -= sinf(g_camera.rot.y - (D3DX_PI * 0.25f)) * CAMERA_MOVE;
			g_camera.posV.z -= cosf(g_camera.rot.y - (D3DX_PI * 0.25f)) * CAMERA_MOVE;
		}
		else
		{// �����ɉ���������Ă��Ȃ�
			g_camera.posV.x -= sinf(g_camera.rot.y - (D3DX_PI * 0.5f)) * CAMERA_MOVE;
			g_camera.posV.z -= cosf(g_camera.rot.y - (D3DX_PI * 0.5f)) * CAMERA_MOVE;
		}

		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fLength;
		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fLength;
	}
	else if (GetKeyboardPress(DIK_UP) == true)
	{// W�L�[�������ꂽ
		g_camera.posV.x += sinf(g_camera.rot.y) * CAMERA_MOVE;
		g_camera.posV.z += cosf(g_camera.rot.y) * CAMERA_MOVE;

		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fLength;
		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fLength;
	}
	else if (GetKeyboardPress(DIK_DOWN) == true)
	{// S�L�[�������ꂽ
		g_camera.posV.x -= sinf(g_camera.rot.y) * CAMERA_MOVE;
		g_camera.posV.z -= cosf(g_camera.rot.y) * CAMERA_MOVE;

		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fLength;
		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fLength;
	}
	//-----------------
	// ���_����
	//-----------------
	if (GetKeyboardPress(DIK_Z) == true)
	{// Z�L�[�������ꂽ
		g_camera.rot.y -= D3DX_PI / 120;
		if (g_camera.rot.y <= -D3DX_PI)
		{
			g_camera.rot.y = D3DX_PI;
		}
		g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * g_camera.fLength;
		g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * g_camera.fLength;

	}
	if (GetKeyboardPress(DIK_C) == true)
	{// C�L�[�������ꂽ
		g_camera.rot.y += D3DX_PI / 120;
		if (g_camera.rot.y >= D3DX_PI)
		{
			g_camera.rot.y = -D3DX_PI;
		}
		g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * g_camera.fLength;
		g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * g_camera.fLength;
	}
	//-----------------
	// �����_����
	//-----------------
	if (GetKeyboardPress(DIK_Q) == true)
	{// Q�L�[�������ꂽ
		g_camera.rot.y -= D3DX_PI / 120;
		if (g_camera.rot.y < -D3DX_PI)
		{
			g_camera.rot.y = D3DX_PI;
		}
		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fLength;
		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fLength;
	}
	if (GetKeyboardPress(DIK_E) == true)
	{// E�L�[�������ꂽ
		g_camera.rot.y += D3DX_PI / 120;
		if (g_camera.rot.y >= D3DX_PI)
		{
			g_camera.rot.y = -D3DX_PI;
		}
		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fLength;
		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fLength;
	}
	//-----------------
	// �J�������Z�b�g
	//-----------------
	if (GetKeyboardPress(DIK_G) == true)
	{// SPACE�L�[�������ꂽ
		g_camera.posV = D3DXVECTOR3(0.0f, 130.0f, -250.0f);
		g_camera.posR = D3DXVECTOR3(0.0f, 00.0f, 0.0f);
		g_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		g_camera.rot.y = atan2f(g_camera.posV.x - g_camera.posR.x, g_camera.posV.z - g_camera.posR.z);
		g_camera.fLength = sqrtf((g_camera.posV.x - g_camera.posR.x) * (g_camera.posV.x - g_camera.posR.x) + (g_camera.posV.z - g_camera.posR.z) * (g_camera.posV.z - g_camera.posR.z));
	}

	//-----------------
	// �����_�㏸���~
	//-----------------
	if (GetKeyboardPress(DIK_T) == true)
	{// T�L�[�������ꂽ
		g_camera.posR.y += CAMERA_UP_DOWN_SPEED;
	}
	if (GetKeyboardPress(DIK_B) == true)
	{// B�L�[�������ꂽ
		g_camera.posR.y -= CAMERA_UP_DOWN_SPEED;
	}
	//-----------------
	// ���_�㏸���~
	//-----------------
	if (GetKeyboardPress(DIK_Y) == true)
	{// Y�L�[�������ꂽ
		g_camera.posV.y += CAMERA_UP_DOWN_SPEED;
	}
	if (GetKeyboardPress(DIK_N) == true)
	{// N�L�[�������ꂽ
		g_camera.posV.y -= CAMERA_UP_DOWN_SPEED;
	}

	//------------------------
	// �Y�[���C�� �Y�[���A�E�g
	//------------------------
	if (GetKeyboardPress(DIK_U) == true)
	{// U�L�[�������ꂽ
		if (g_camera.fLength >= 60)
		{
			g_camera.fLength -= 2.0f;
		}
	}
	if (GetKeyboardPress(DIK_M) == true)
	{// M�L�[�������ꂽ
		if (g_camera.fLength <= 350)
		{
			g_camera.fLength += 2.0f;
		}
	}
#endif

	if (GetMode() == MODE_TITLE)
	{// �^�C�g������������
		g_camera.rot.y += D3DX_PI / 1200;
		if (g_camera.rot.y >= D3DX_PI)
		{
			g_camera.rot.y = -D3DX_PI;
		}
		g_camera.posV.x = g_camera.posR.x + sinf(g_camera.rot.y) * 1000;
		g_camera.posV.z = g_camera.posR.z + cosf(g_camera.rot.y) * 1000;
	}
	else if (GetMode() == MODE_GAME)
	{// �Q�[������������
		D3DXVECTOR3 PlayerPos[MAX_PLAYER];  // �v���C���[�̍��W
		for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
		{// �v���C���[�̐l�����J��Ԃ�
			PlayerPos[nCntPlayer] = GetPlayer(nCntPlayer)->pos;
		}

		g_camera.posR.x = (PlayerPos[0].x + PlayerPos[1].x) / 2;

		if ((PlayerPos[0].x + PlayerPos[1].x) / 2 >= 150.0f)
		{// �v���C���[���m�����ꂷ���Ă���
			g_camera.fLength = (PlayerPos[0].x + PlayerPos[1].x) / 2 + 300.0f;
		}

		g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * g_camera.fLength;
		g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * g_camera.fLength;
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
		D3DXToRadian(CAMERA_ANGEL_VIEW),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		9000.0f);

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera.mtxProjection);

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera.mtxView);

	// �r���[�}�g���b�N�X���쐬
	D3DXMatrixLookAtLH(&g_camera.mtxView,
		&g_camera.posV,
		&g_camera.posR,
		&g_camera.vecU);

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