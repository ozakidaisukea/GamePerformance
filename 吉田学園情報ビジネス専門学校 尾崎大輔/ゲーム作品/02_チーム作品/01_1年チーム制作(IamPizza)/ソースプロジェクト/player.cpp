//=============================================================================
//
// �v���C���[�̏��� [player.cpp]
// Author : Shun Yokomichi
//
//=============================================================================
#include "player.h"
#include "input.h"			// ���͏���
#include "shadow.h"			// �e�̏���
#include "camera.h"			// �J�����̏���
#include "effect.h"			// �G�t�F�N�g�̏���
#include "explosion.h"		// �����̏���
#include "model.h"			// ���f���̏���
#include "game.h"			// �Q�[���̏���
#include "goal.h"			// �S�[���̏���
#include "passage.h"		// �ʍs�l�̏���
#include "car.h"			// �Ԃ̏���
#include "obstacle.h"		// �I�u�W�F�N�g�̏���
#include "sound.h"
#include "inputx.h"
#include "particle.h"
#include "deathpizza.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_PLAYER			(2)									// �v���C���[�̑���
#define PLAYER_NAME000		"data/MODEL/player.x"				//	�v���C���[(�ʏ�)�̖��O
#define PLAYER_NAME001		"data/MODEL/Pizza.x"				//	�v���C���[(�o��)�̖��O
#define MOVE_PLAYER			(2.0f)								// �v���C���[�̃X�s�[�h
#define MOVE_PIZZA			(3.0f)								// Pizza���[�h�̃X�s�[�h
#define MAX_OBSTACLE		(100)								// �I�u�W�F�N�g�̍ő吔
#define MAX_OBSTACLE_TYPE   (OBSTACLE_TYPE_MAX )				// �I�u�W�F�N�g�̃^�C�v��

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
PLAYER			g_aPlayer[MAX_PLAYER];
int				g_nSwitching;					// ���[�h�ؑցi�O �ʏ� / 1 �o��)
int				g_nCntEx;						// �����o���J�E���g
float			g_fAngel;
float			g_fMove;						// �v���C���[�̈ړ����x
bool			g_bRotchang;					// �����̐؂�ւ�
JoyState g_JoyStatePlayer;
//=============================================================================
// ����������
//=============================================================================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_nSwitching = 0;
	g_fMove = 0.0f;
	g_fAngel = 0.14f;
	g_bRotchang = true;
	g_JoyStatePlayer.nJoypadState = INPUT_JOYSTATE_NOTPUSH;

	// ������
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		// �ʒu�E�����̏����ݒ�
		g_aPlayer[nCntPlayer].pos = D3DXVECTOR3(500.0f, 3.0f, -850.0f);						// pos�̏�����(����)
		g_aPlayer[nCntPlayer].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// pos�̏�����(�ړI)
		g_aPlayer[nCntPlayer].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);							// move�̏�����
		g_aPlayer[nCntPlayer].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);							// rot(����)�̏�����(�ʏ� && Pizza�̏c)		
		g_aPlayer[nCntPlayer].rotPizza = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);					// rot(����)�̏�����(Pizza�̉�)
		g_aPlayer[nCntPlayer].rotDest = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);					// rot(�ړI)�̏�����
		g_aPlayer[nCntPlayer].DiffAngle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// �v���C���[�̍����̏�����
		g_aPlayer[nCntPlayer].vtxMin = D3DXVECTOR3(100000.0f, 100000.0f, 100000.0f);		// �ŏ��l�̏ꍇ�͑��߂ɐ��l�������i��r�̂���)
		g_aPlayer[nCntPlayer].vtxMax = D3DXVECTOR3(-100000.0f, -100000.0f, -100000.0f);		// �ő�l�̏ꍇ�͏��Ȃ߂ɐ��l�������i��r�̂���)
		g_aPlayer[nCntPlayer].type = PALYERTYPE_STOP;										// �v���C���[�̎�ނ̏�����
		g_aPlayer[nCntPlayer].fXaxis = 0;
		g_aPlayer[nCntPlayer].fZaxis = -40.0f;
		g_aPlayer[nCntPlayer].pMesh = 0;
		g_aPlayer[nCntPlayer].pBuffMat = 0;
		g_aPlayer[nCntPlayer].nNumMat = 0;
		g_aPlayer[nCntPlayer].rotnum = 4;
		g_aPlayer[nCntPlayer].ChangeState = CHANGESTATE_POSSIBLE;
		g_aPlayer[nCntPlayer].PizzaMode = PLAYERPIZZA_HUMAN;
	}
	g_aPlayer[0].state = PLAYERSTATE_NORMAL;
	g_aPlayer[1].state = PLAYERSTATE_AWAKENING;
	g_aPlayer[0].nIdyShadow = SetShadow(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 15);
	g_aPlayer[0].bUse = true;
	g_aPlayer[1].bUse = false;


	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(PLAYER_NAME000, D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_aPlayer[0].pBuffMat, NULL, &g_aPlayer[0].nNumMat, &g_aPlayer[0].pMesh);
	D3DXLoadMeshFromX(PLAYER_NAME001, D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_aPlayer[1].pBuffMat, NULL, &g_aPlayer[1].nNumMat, &g_aPlayer[1].pMesh);

	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		int nNumVtx;		// ���_��
		DWORD sizeFVF;		// ���_�t�H�[�}�b�g�̃T�C�Y
		BYTE *pVtxBuff;		// ���_�o�b�t�@�ւ̃|�C���^

							// ���_���̎擾
		nNumVtx = g_aPlayer[nCntPlayer].pMesh->GetNumVertices();

		// ���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFVF = D3DXGetFVFVertexSize(g_aPlayer[nCntPlayer].pMesh->GetFVF());

		// ���_�o�b�t�@�����b�N
		g_aPlayer[nCntPlayer].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;			// ���_���W�̑��

			if (vtx.x < g_aPlayer[nCntPlayer].vtxMin.x)
			{
				g_aPlayer[nCntPlayer].vtxMin.x = vtx.x;
			}
			if (vtx.y < g_aPlayer[nCntPlayer].vtxMin.y)
			{
				g_aPlayer[nCntPlayer].vtxMin.y = vtx.y;
			}
			if (vtx.z < g_aPlayer[nCntPlayer].vtxMin.z)
			{
				g_aPlayer[nCntPlayer].vtxMin.z = vtx.z;
			}
			if (vtx.x > g_aPlayer[nCntPlayer].vtxMax.x)
			{
				g_aPlayer[nCntPlayer].vtxMax.x = vtx.x;
			}
			if (vtx.y > g_aPlayer[nCntPlayer].vtxMax.y)
			{
				g_aPlayer[nCntPlayer].vtxMax.y = vtx.y;
			}
			if (vtx.z > g_aPlayer[nCntPlayer].vtxMax.z)
			{
				g_aPlayer[nCntPlayer].vtxMax.z = vtx.z;
			}
			pVtxBuff += sizeFVF;			// �T�C�Y���̃|�C���^��i�߂�
		}
		g_aPlayer[nCntPlayer].vtxMaxBike = D3DXVECTOR3(g_aPlayer[0].vtxMax.x + 300, g_aPlayer[0].vtxMax.y, g_aPlayer[0].vtxMax.z+ 300);
		g_aPlayer[nCntPlayer].vtxMinBike = g_aPlayer[0].vtxMin;
		// ���_�o�b�t�@���A�����b�N
		g_aPlayer[nCntPlayer].pMesh->UnlockVertexBuffer();
	}

	
}

//=============================================================================
// �I������
//=============================================================================
void UninitPlayer(void)
{
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		// ���b�V���̊J��
		if (g_aPlayer[nCntPlayer].pMesh != NULL)
		{
			g_aPlayer[nCntPlayer].pMesh->Release();
			g_aPlayer[nCntPlayer].pMesh = NULL;
		}

		// �}�e���A���̊J��
		if (g_aPlayer[nCntPlayer].pBuffMat != NULL)
		{
			g_aPlayer[nCntPlayer].pBuffMat->Release();
			g_aPlayer[nCntPlayer].pBuffMat = NULL;
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePlayer(void)
{
	// �ϐ��錾
	Camera *pCamera;
	pCamera = GetCamera();
	GAMESTATE GameState = GetGameState();

	JoyState pJoyState = GetJoystate();
	XINPUT_STATE state;
	XInputGetState(0, &state);

	// ��Ԃ��Ǘ�
	switch (g_aPlayer[g_nSwitching].state)
	{
	case PLAYERSTATE_NORMAL:
		// �ʏ��Ԃ̏ꍇ

		g_nCntEx++;
		if ((g_nCntEx % 30) == 0 && g_aPlayer[0].type == PALYERTYPE_WAIK)
		{
			SetExplosion(D3DXVECTOR3(g_aPlayer[0].pos.x , g_aPlayer[0].pos.y + 20, g_aPlayer[0].pos.z) , D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f), 15, 15);
		}
		g_aPlayer[g_nSwitching].rotDest.z = D3DX_PI * 0.0f + pCamera->rotCamera.z;
		break;

	case PLAYERSTATE_AWAKENING:
		// Pizza���[�h���
		g_nCntEx++;
		if (GetKeyboardTrigger(DIK_LSHIFT) == true || GetKeyboardTrigger(DIK_RSHIFT) == true || (state.Gamepad.wButtons & XINPUT_GAMEPAD_Y  && pJoyState.bConnectionJoypad == true))
		{
			if (g_JoyStatePlayer.nJoypadState == INPUT_JOYSTATE_NOTPUSH)
			{
				g_bRotchang = g_bRotchang ? false : true;
			}

			g_JoyStatePlayer.nJoypadState = INPUT_JOYSTATE_PUSH;
		}
		if (g_bRotchang == true)
		{	// Pizza(�c��])
			g_nCntEx = 0;
			g_aPlayer[g_nSwitching].rotPizza.z = D3DX_PI * 0.0f + pCamera->rotCamera.z;
			g_aPlayer[g_nSwitching].pos.y = 20.0f;

			if (g_aPlayer[g_nSwitching].type == PALYERTYPE_WAIK)
			{	// �v���C���[�������Ă���ꍇ
				g_aPlayer[g_nSwitching].rotPizza.x -= 0.3f;
				//g_aPlayer[g_nSwitching].rotPizza.y = 0.0f;
			}
		}
		else
		{	// Pizza(����])
			g_nCntEx++;
			g_aPlayer[g_nSwitching].rotPizza.x = 0.0f;
			g_aPlayer[g_nSwitching].rotPizza.z = D3DX_PI * 0.5f + pCamera->rotCamera.z;
			g_aPlayer[g_nSwitching].pos.y = 8.0f;

			if (g_aPlayer[g_nSwitching].type == PALYERTYPE_WAIK)
			{	// �v���C���[�������Ă���ꍇ
				g_aPlayer[g_nSwitching].rotPizza.y += 0.1f;
			}

			if (g_nCntEx == 120)
			{
				g_bRotchang = true;
			}
		}
		break;
	}

	g_aPlayer[g_nSwitching].posOld = g_aPlayer[g_nSwitching].pos;		//�O��̈ʒu��ۑ�
	g_aPlayer[g_nSwitching].type = PALYERTYPE_STOP;

	if (g_aPlayer[0].state == PLAYERSTATE_NORMAL && g_aPlayer[1].state == PLAYERSTATE_AWAKENING)
	{
		// ���ꂼ��̏����œ���������ς���i�ړ��j
		if (GetKeyboardPress(DIK_S) == true || (state.Gamepad.bLeftTrigger & XINPUT_GAMEPAD_LEFT_THUMB && pJoyState.bConnectionJoypad == true))
		{	//S or �� �Ō���
			g_aPlayer[g_nSwitching].rotnum = 6;
			g_aPlayer[g_nSwitching].type = PALYERTYPE_STOP;

			if (g_aPlayer[g_nSwitching].state == PLAYERSTATE_NORMAL && GetKeyboardPress(DIK_D) == true || g_aPlayer[g_nSwitching].state == PLAYERSTATE_NORMAL && GetKeyboardPress(DIK_RIGHT) == true
				|| (state.Gamepad.sThumbLX >= XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && pJoyState.bConnectionJoypad == true))
			{
				g_aPlayer[g_nSwitching].rotDest.y = -D3DX_PI * 0.5f + pCamera->rotCamera.y;
				g_aPlayer[g_nSwitching].rotDest.z = D3DX_PI * 0.15f + pCamera->rotCamera.z;
			}
			else if (g_aPlayer[g_nSwitching].state == PLAYERSTATE_NORMAL && GetKeyboardPress(DIK_A) == true 
				|| GetKeyboardPress(DIK_W) == true || (state.Gamepad.sThumbLX <= -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && pJoyState.bConnectionJoypad == true)
				|| (state.Gamepad.bRightTrigger & XINPUT_GAMEPAD_RIGHT_THUMB && pJoyState.bConnectionJoypad == true))
			{
				g_aPlayer[g_nSwitching].rotDest.y = D3DX_PI * 0.5f + pCamera->rotCamera.y;
				g_aPlayer[g_nSwitching].rotDest.z = -D3DX_PI * 0.15f + pCamera->rotCamera.z;
			}

		}
		else if (GetKeyboardPress(DIK_A) == true ||  (state.Gamepad.sThumbLX <= -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && pJoyState.bConnectionJoypad == true))
		{
			g_aPlayer[g_nSwitching].type = PALYERTYPE_WAIK;
			if (GetKeyboardPress(DIK_W) == true ||  (state.Gamepad.bRightTrigger & XINPUT_GAMEPAD_RIGHT_THUMB && pJoyState.bConnectionJoypad == true))
			{	//�����ړ�
				g_aPlayer[g_nSwitching].rotnum = 0;

				if (g_aPlayer[g_nSwitching].state == PLAYERSTATE_NORMAL)
				{
					g_aPlayer[g_nSwitching].move.x += sinf((-D3DX_PI * 0.25f) + pCamera->rotCamera.y) * g_fMove;
					g_aPlayer[g_nSwitching].move.z += cosf((-D3DX_PI * 0.25f) + pCamera->rotCamera.y) * g_fMove;
					g_aPlayer[g_nSwitching].rotDest.z = -D3DX_PI * 0.15f + pCamera->rotCamera.z;

				}
				else if (g_aPlayer[g_nSwitching].state == PLAYERSTATE_AWAKENING)
				{
					g_aPlayer[g_nSwitching].move.x += sinf((-D3DX_PI * 0.25f) + pCamera->rotCamera.y) * MOVE_PIZZA;
					g_aPlayer[g_nSwitching].move.z += cosf((-D3DX_PI * 0.25f) + pCamera->rotCamera.y) * MOVE_PIZZA;
				}
			}
			else
			{	//���ړ�
				g_aPlayer[g_nSwitching].rotnum = 1;

				if (g_aPlayer[g_nSwitching].state == PLAYERSTATE_NORMAL)
				{
					g_aPlayer[g_nSwitching].move.x += sinf((-D3DX_PI * 0.5f) + pCamera->rotCamera.y) * g_fMove;
					g_aPlayer[g_nSwitching].move.z += cosf((-D3DX_PI * 0.5f) + pCamera->rotCamera.y) * g_fMove;
					g_aPlayer[g_nSwitching].rotDest.z = -D3DX_PI * 0.15f + pCamera->rotCamera.z;
				}
				else if (g_aPlayer[g_nSwitching].state == PLAYERSTATE_AWAKENING)
				{
					g_aPlayer[g_nSwitching].move.x += sinf((-D3DX_PI * 0.5f) + pCamera->rotCamera.y) * MOVE_PIZZA;
					g_aPlayer[g_nSwitching].move.z += cosf((-D3DX_PI * 0.5f) + pCamera->rotCamera.y) * MOVE_PIZZA;
				}
			}
		}
		else if (GetKeyboardPress(DIK_D) == true  || (state.Gamepad.sThumbLX >= XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && pJoyState.bConnectionJoypad == true))
		{
			g_aPlayer[g_nSwitching].type = PALYERTYPE_WAIK;
			if (GetKeyboardPress(DIK_W) == true || GetKeyboardPress(DIK_UP) == true || (state.Gamepad.bRightTrigger & XINPUT_GAMEPAD_RIGHT_THUMB && pJoyState.bConnectionJoypad == true))
			{	//�E���ړ�
				g_aPlayer[g_nSwitching].rotnum = 2;

				if (g_aPlayer[g_nSwitching].state == PLAYERSTATE_NORMAL)
				{
					g_aPlayer[g_nSwitching].move.x += sinf((D3DX_PI * 0.25f) + pCamera->rotCamera.y) * g_fMove;
					g_aPlayer[g_nSwitching].move.z += cosf((D3DX_PI * 0.25f) + pCamera->rotCamera.y) * g_fMove;
					g_aPlayer[g_nSwitching].rotDest.z = D3DX_PI * 0.15f + pCamera->rotCamera.z;
				}
				else if (g_aPlayer[g_nSwitching].state == PLAYERSTATE_AWAKENING)
				{
					g_aPlayer[g_nSwitching].move.x += sinf((D3DX_PI * 0.25f) + pCamera->rotCamera.y) * MOVE_PIZZA;
					g_aPlayer[g_nSwitching].move.z += cosf((D3DX_PI * 0.25f) + pCamera->rotCamera.y) * MOVE_PIZZA;
				}
			}
			else
			{	//�E�ړ�
				g_aPlayer[g_nSwitching].rotnum = 3;

				if (g_aPlayer[g_nSwitching].state == PLAYERSTATE_NORMAL)
				{
					g_aPlayer[g_nSwitching].move.x += sinf((D3DX_PI * 0.5f) + pCamera->rotCamera.y) * g_fMove;
					g_aPlayer[g_nSwitching].move.z += cosf((D3DX_PI * 0.5f) + pCamera->rotCamera.y) * g_fMove;
					g_aPlayer[g_nSwitching].rotDest.z = D3DX_PI * 0.15f + pCamera->rotCamera.z;
				}
				else if (g_aPlayer[g_nSwitching].state == PLAYERSTATE_AWAKENING)
				{
					g_aPlayer[g_nSwitching].move.x += sinf((D3DX_PI * 0.5f) + pCamera->rotCamera.y) * MOVE_PIZZA;
					g_aPlayer[g_nSwitching].move.z += cosf((D3DX_PI * 0.5f) + pCamera->rotCamera.y) * MOVE_PIZZA;
				}
			}
		}
		else if (GetKeyboardPress(DIK_W) == true || (state.Gamepad.bRightTrigger & XINPUT_GAMEPAD_RIGHT_THUMB && pJoyState.bConnectionJoypad == true))
		{	// W or �� �ňړ�
			g_aPlayer[g_nSwitching].rotnum = 4;
			g_aPlayer[g_nSwitching].type = PALYERTYPE_WAIK;

			if (g_aPlayer[g_nSwitching].state == PLAYERSTATE_NORMAL)
			{
				g_aPlayer[g_nSwitching].move.x += sinf((0) + pCamera->rotCamera.y) * g_fMove;
				g_aPlayer[g_nSwitching].move.z += cosf((0) + pCamera->rotCamera.y) * g_fMove;
			}
			else if (g_aPlayer[g_nSwitching].state == PLAYERSTATE_AWAKENING)
			{
				g_aPlayer[g_nSwitching].move.x += sinf((0) + pCamera->rotCamera.y) * MOVE_PIZZA;
				g_aPlayer[g_nSwitching].move.z += cosf((0) + pCamera->rotCamera.y) * MOVE_PIZZA;
			}
		}
		else if (GetKeyboardPress(DIK_SPACE) == true || (state.Gamepad.wButtons & XINPUT_GAMEPAD_A && pJoyState.bConnectionJoypad == true))
		{	// SPACE�L�[�Ńo�b�N�ړ�
			g_aPlayer[g_nSwitching].rotnum = 5;
			g_aPlayer[g_nSwitching].type = PALYERTYPE_WAIK;

			if (g_aPlayer[g_nSwitching].state == PLAYERSTATE_NORMAL)
			{
				g_aPlayer[g_nSwitching].move.x += sinf((D3DX_PI)+pCamera->rotCamera.y) * g_fMove / 2;
				g_aPlayer[g_nSwitching].move.z += cosf((D3DX_PI)+pCamera->rotCamera.y) * g_fMove / 2;
			}
			else if (g_aPlayer[g_nSwitching].state == PLAYERSTATE_AWAKENING)
			{
				g_aPlayer[g_nSwitching].move.x += sinf((D3DX_PI)+pCamera->rotCamera.y) * MOVE_PIZZA / 2;
				g_aPlayer[g_nSwitching].move.z += cosf((D3DX_PI)+pCamera->rotCamera.y) * MOVE_PIZZA / 2;
			}
		}

		// ���ꂼ��̊p�x
		if (g_aPlayer[g_nSwitching].rotnum == 0)
		{	// ����
			g_aPlayer[g_nSwitching].rotDest.y = D3DX_PI * 0.75f + pCamera->rotCamera.y;
		}
		if (g_aPlayer[g_nSwitching].rotnum == 1)
		{	// ��
			g_aPlayer[g_nSwitching].rotDest.y = D3DX_PI * 0.5f + pCamera->rotCamera.y;
		}
		if (g_aPlayer[g_nSwitching].rotnum == 2)
		{	// �E��
			g_aPlayer[g_nSwitching].rotDest.y = -D3DX_PI * 0.75f + pCamera->rotCamera.y;
		}
		if (g_aPlayer[g_nSwitching].rotnum == 3)
		{	// �E
			g_aPlayer[g_nSwitching].rotDest.y = -D3DX_PI * 0.5f + pCamera->rotCamera.y;
		}
		if (g_aPlayer[g_nSwitching].rotnum == 4)
		{	// ��
			g_aPlayer[g_nSwitching].rotDest.y = D3DX_PI + pCamera->rotCamera.y;
		}
		if (g_aPlayer[g_nSwitching].rotnum == 5)
		{	// �o�b�N
			g_aPlayer[g_nSwitching].rotDest.y = D3DX_PI + pCamera->rotCamera.y;
		}

		g_aPlayer[g_nSwitching].DiffAngle.y = g_aPlayer[g_nSwitching].rotDest.y - g_aPlayer[g_nSwitching].rot.y;

		//�p�x�̐ݒ�
		if (g_aPlayer[g_nSwitching].DiffAngle.y > D3DX_PI)
		{
			g_aPlayer[g_nSwitching].DiffAngle.y -= D3DX_PI* 2.0f;
		}
		if (g_aPlayer[g_nSwitching].DiffAngle.y < -D3DX_PI)
		{
			g_aPlayer[g_nSwitching].DiffAngle.y += D3DX_PI* 2.0f;
		}

		g_aPlayer[g_nSwitching].rot.y += g_aPlayer[g_nSwitching].DiffAngle.y * 0.2f;

		if (g_aPlayer[g_nSwitching].rot.y > D3DX_PI)
		{
			g_aPlayer[g_nSwitching].rot.y -= D3DX_PI* 2.0f;
		}
		if (g_aPlayer[g_nSwitching].rot.y < -D3DX_PI)
		{
			g_aPlayer[g_nSwitching].rot.y += D3DX_PI* 2.0f;
		}

		if (g_aPlayer[g_nSwitching].state == PLAYERSTATE_NORMAL)
		{	// �ʏ��Ԃ̏ꍇ
			g_aPlayer[g_nSwitching].DiffAngle.z = g_aPlayer[g_nSwitching].rotDest.z - g_aPlayer[g_nSwitching].rot.z;

			if (g_aPlayer[g_nSwitching].DiffAngle.z > D3DX_PI)
			{
				g_aPlayer[g_nSwitching].DiffAngle.z -= D3DX_PI * 2.0f;
			}
			if (g_aPlayer[g_nSwitching].DiffAngle.z < -D3DX_PI)
			{
				g_aPlayer[g_nSwitching].DiffAngle.z += D3DX_PI * 2.0f;
			}

			g_aPlayer[g_nSwitching].rot.z += g_aPlayer[g_nSwitching].DiffAngle.z * 0.1f;

			if (g_aPlayer[g_nSwitching].rot.z > D3DX_PI)
			{
				g_aPlayer[g_nSwitching].rot.z -= D3DX_PI * 2.0f;
			}
			if (g_aPlayer[g_nSwitching].rot.z < -D3DX_PI)
			{
				g_aPlayer[g_nSwitching].rot.z += D3DX_PI * 2.0f;
			}
		}
		if (g_aPlayer[g_nSwitching].state == PLAYERSTATE_AWAKENING && g_bRotchang == true)
		{	// PIzza���(�c��])�̏ꍇ
			g_aPlayer[g_nSwitching].DiffAngle.y = g_aPlayer[g_nSwitching].rotDest.y - g_aPlayer[g_nSwitching].rotPizza.y;

			if (g_aPlayer[g_nSwitching].DiffAngle.y > D3DX_PI)
			{
				g_aPlayer[g_nSwitching].DiffAngle.y -= D3DX_PI * 2.0f;
			}
			if (g_aPlayer[g_nSwitching].DiffAngle.y < -D3DX_PI)
			{
				g_aPlayer[g_nSwitching].DiffAngle.y += D3DX_PI * 2.0f;
			}

			g_aPlayer[g_nSwitching].rotPizza.y += g_aPlayer[g_nSwitching].DiffAngle.y * 0.1f;

			if (g_aPlayer[g_nSwitching].rotPizza.y > D3DX_PI)
			{
				g_aPlayer[g_nSwitching].rotPizza.y -= D3DX_PI * 2.0f;
			}
			if (g_aPlayer[g_nSwitching].rotPizza.y < -D3DX_PI)
			{
				g_aPlayer[g_nSwitching].rotPizza.y += D3DX_PI * 2.0f;
			}
		}

		// ���x����
		if (g_aPlayer[g_nSwitching].type == PALYERTYPE_STOP)
		{
			g_fMove -= 0.017f;
			g_fAngel = 0.02f;
			if (g_fMove <= 0)
			{
				g_fMove = 0.0f;
			}
		}
		else if (g_aPlayer[g_nSwitching].type == PALYERTYPE_WAIK)
		{
			g_fAngel = 0.14f;
			g_fMove += 0.005f;
			if (g_fMove >= MOVE_PLAYER)
			{
				g_fMove = MOVE_PLAYER;
			}
		}
	
		//�t�B�[���h�̑傫���̔���
		if (9000 <= g_aPlayer[g_nSwitching].pos.x)
		{
			g_aPlayer[g_nSwitching].pos.x = 9000 - 1;
		}
		if (-3000 >= g_aPlayer[g_nSwitching].pos.x)
		{
			g_aPlayer[g_nSwitching].pos.x = -3000 + 1;
		}
		if (9000 <= g_aPlayer[g_nSwitching].pos.z)
		{
			g_aPlayer[g_nSwitching].pos.z = 9000 - 1;
		}
		if (-3000 >= g_aPlayer[g_nSwitching].pos.z)
		{
			g_aPlayer[g_nSwitching].pos.z = -3000 + 1;
		}

		//����
		g_aPlayer[g_nSwitching].move.x += (0.0f - g_aPlayer[g_nSwitching].move.x) * g_fAngel;
		g_aPlayer[g_nSwitching].move.z += (0.0f - g_aPlayer[g_nSwitching].move.z) * g_fAngel;

		//�ʒu�X�V�i�ړ��j
		g_aPlayer[g_nSwitching].pos.x += g_aPlayer[g_nSwitching].move.x;
		g_aPlayer[g_nSwitching].pos.z += g_aPlayer[g_nSwitching].move.z;

		//���f���Ƃ̓����蔻��
		if (CollisionModel(&g_aPlayer[g_nSwitching].pos, &g_aPlayer[g_nSwitching].posOld, &g_aPlayer[g_nSwitching].move, g_aPlayer[g_nSwitching].vtxMax, g_aPlayer[g_nSwitching].vtxMin) == true)
		{//���f���ɒ��n�����Ƃ�

		}
		//�S�[���Ƃ̓����蔻��
		if (CollisionGoal(&g_aPlayer[g_nSwitching].pos, &g_aPlayer[g_nSwitching].posOld, &g_aPlayer[g_nSwitching].move, g_aPlayer[g_nSwitching].vtxMax, g_aPlayer[g_nSwitching].vtxMin) == true)
		{//�S�[���ɓ�����
			GOAL *pGoal = GetGoal();
			pGoal->nGoalPattern++;
		}
		// �ʍs�l�Ƃ̓��蔻��
		if (CollisionPassage(&g_aPlayer[g_nSwitching].pos, &g_aPlayer[g_nSwitching].posOld, &g_aPlayer[g_nSwitching].move, g_aPlayer[g_nSwitching].vtxMax, g_aPlayer[g_nSwitching].vtxMin) == true)
		{
			if (g_aPlayer[g_nSwitching].state == PLAYERSTATE_AWAKENING)
			{
				if (GameState != GAMESTATE_GAMEOVER)
				{
					PlaySound(SOUND_LABEL_SE_SAKEBI3);
					SetGameState(GAMESTATE_GAMEOVER);
					g_aPlayer[1].state = PLAYERSTATE_EAT;
					g_aPlayer[1].bUse = false;
					DeleteShadow(g_aPlayer[0].nIdyShadow);
					SetDeathPizza(D3DXVECTOR3(g_aPlayer[g_nSwitching].pos.x, g_aPlayer[g_nSwitching].pos.y + 10, g_aPlayer[g_nSwitching].pos.z),
						D3DXVECTOR3(0, 1, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 20, 30);
					SetParticle(D3DXVECTOR3(g_aPlayer[g_nSwitching].pos.x, g_aPlayer[g_nSwitching].pos.y + 50, g_aPlayer[g_nSwitching].pos.z)
						, D3DXVECTOR3(0.8f, 0.2f, 0.8f), D3DXVECTOR3(0, 0, 0), D3DXCOLOR(0, 0, 0, 0), 20, 30, PARTICLE_TYPE_PIZZA_DEATH);
				}
			}
		}
		// �Ԃ̓��蔻��
		if (g_aPlayer[g_nSwitching].state == PLAYERSTATE_NORMAL || g_aPlayer[g_nSwitching].state == PLAYERSTATE_AWAKENING && g_bRotchang == true)
		{
			if (CollisionCar(&g_aPlayer[g_nSwitching].pos, &g_aPlayer[g_nSwitching].posOld, &g_aPlayer[g_nSwitching].move, g_aPlayer[g_nSwitching].vtxMax, g_aPlayer[g_nSwitching].vtxMin) == true)
			{
				if (g_aPlayer[g_nSwitching].state == PLAYERSTATE_AWAKENING)
				{
					if (GameState != GAMESTATE_GAMEOVER)
					{
						PlaySound(SOUND_LABEL_SE_SAKEBI3);
						SetGameState(GAMESTATE_GAMEOVER);
						g_aPlayer[1].state = PLAYERSTATE_DIE;
						g_aPlayer[1].bUse = false;
						DeleteShadow(g_aPlayer[0].nIdyShadow);
						SetDeathPizza(D3DXVECTOR3(g_aPlayer[g_nSwitching].pos.x, g_aPlayer[g_nSwitching].pos.y + 10, g_aPlayer[g_nSwitching].pos.z),
							D3DXVECTOR3(0, 1, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 20, 30);

						SetParticle(D3DXVECTOR3(g_aPlayer[g_nSwitching].pos.x, g_aPlayer[g_nSwitching].pos.y + 50, g_aPlayer[g_nSwitching].pos.z)
							, D3DXVECTOR3(0.8f, 0.2f, 0.8f), D3DXVECTOR3(0, 0, 0), D3DXCOLOR(0, 0, 0, 0), 20, 30, PARTICLE_TYPE_PIZZA_DEATH);
					}
				}
			}
		}
		//�I�u�W�F�N�g�Ƃ̓����蔻��
		if (CollisionObstacle(&g_aPlayer[g_nSwitching].pos, &g_aPlayer[g_nSwitching].posOld, &g_aPlayer[g_nSwitching].move, g_aPlayer[g_nSwitching].vtxMax) == true)
		{//�I�u�W�F�N�g�ɓ�������

			g_aPlayer[g_nSwitching].ChangeState = CHANGESTATE_IMPOSSIBLE;

			/*if (g_aPlayer[g_nSwitching].state == PLAYERSTATE_AWAKENING)
			{
				g_aPlayer[1].bUse = false;
				DeleteShadow(g_aPlayer[0].nIdyShadow);
				g_aPlayer[g_nSwitching].state = PLAYERSTATE_DIE;
				SetDeathPizza(D3DXVECTOR3(g_aPlayer[g_nSwitching].pos.x, g_aPlayer[g_nSwitching].pos.y + 10, g_aPlayer[g_nSwitching].pos.z),
					D3DXVECTOR3(0, 1, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 20, 30);

				SetParticle(D3DXVECTOR3(g_aPlayer[g_nSwitching].pos.x, g_aPlayer[g_nSwitching].pos.y + 50, g_aPlayer[g_nSwitching].pos.z)
					, D3DXVECTOR3(0.8f, 0.2f, 0.8f), D3DXVECTOR3(0, 0, 0), D3DXCOLOR(0, 0, 0, 0), 20, 30, PARTICLE_TYPE_PIZZA_DEATH);
				if (GameState != GAMESTATE_GAMEOVER)
				{
					SetGameState(GAMESTATE_GAMEOVER);
				}
			}*/
			/*if (g_aPlayer[g_nSwitching].state == PLAYERSTATE_NORMAL)
			{
			g_aPlayer[0].rot.x = -D3DX_PI * 0.15f + pCamera->rotCamera.x;
			g_aPlayer[0].pos.y = 18.0f;
			}*/
		}

		//�o�C�N��Ԃ̓����蔻��
		if (CollisionObstacleBike(&g_aPlayer[g_nSwitching].pos, &g_aPlayer[g_nSwitching].posOld, &g_aPlayer[g_nSwitching].move, g_aPlayer[0].vtxMaxBike) == true)
		{//�I�u�W�F�N�g�ɓ�������
			//�������Ă���Ƃ��͕ϐg�ł��Ȃ�
			g_aPlayer[g_nSwitching].ChangeState = CHANGESTATE_IMPOSSIBLE;
		}
		// ENTER�L�[�Őؑ�
		if (GetKeyboardTrigger(DIK_RETURN) == true && g_aPlayer[g_nSwitching].ChangeState == CHANGESTATE_POSSIBLE || (state.Gamepad.wButtons & XINPUT_GAMEPAD_X  && pJoyState.bConnectionJoypad == true && g_aPlayer[g_nSwitching].ChangeState == CHANGESTATE_POSSIBLE))
		{
			if (g_JoyStatePlayer.nJoypadState == INPUT_JOYSTATE_NOTPUSH)
			{
				//SetEffect(D3DXVECTOR3(g_aPlayer[g_nSwitching].pos.x, g_aPlayer[g_nSwitching].pos.y + 15.0f, g_aPlayer[g_nSwitching].pos.z), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 50, 100);
				g_nSwitching = g_nSwitching ^ 1;										// ��ԕω� (0 : �ʏ�	1 : Pizza���)
				g_aPlayer[g_nSwitching ^ 1].bUse = false;
				g_aPlayer[g_nSwitching].bUse = true;
				g_aPlayer[g_nSwitching].pos = g_aPlayer[g_nSwitching ^ 1].pos;			// pos�̈��p��
				g_aPlayer[g_nSwitching].rot = g_aPlayer[g_nSwitching ^ 1].rot;			// �����̈��p��
				g_aPlayer[g_nSwitching].move = g_aPlayer[g_nSwitching ^ 1].move;		// move�̈����p��
				g_nCntEx = 0;

				if (g_nSwitching == 0)
				{	// �O�̏ꍇ�́A�ʏ��Ԃ�
					g_aPlayer[g_nSwitching].state = PLAYERSTATE_NORMAL;
					g_aPlayer[g_nSwitching].pos.y = 3.0f;
					StopSound(SOUND_LABEL_BGM_PIZZA);
					PlaySound(SOUND_LABEL_BGM_GAME);
					g_aPlayer[0].PizzaMode = PLAYERPIZZA_HUMAN;
					g_aPlayer[1].PizzaMode = PLAYERPIZZA_HUMAN;
				}
				else
				{	// �P�̏ꍇ�́APizza���[�h��Ԃ�
					SetParticle(D3DXVECTOR3(g_aPlayer[g_nSwitching].pos.x, g_aPlayer[g_nSwitching].pos.y + 50, g_aPlayer[g_nSwitching].pos.z)
						, D3DXVECTOR3(0.8f, 0.2f, 0.8f), D3DXVECTOR3(0, 0, 0), D3DXCOLOR(0, 0, 0, 0), 20, 30, PARTICLE_TYPE_PIZZA);
					g_nCntEx = 0;
					g_aPlayer[g_nSwitching].state = PLAYERSTATE_AWAKENING;
					g_aPlayer[0].PizzaMode = PLAYERPIZZA_PIZZA;
					g_aPlayer[1].PizzaMode = PLAYERPIZZA_PIZZA;
					StopSound(SOUND_LABEL_BGM_GAME);
					PlaySound(SOUND_LABEL_BGM_PIZZA);
				}
			}
			g_JoyStatePlayer.nJoypadState = INPUT_JOYSTATE_PUSH;
		}
		// �e
		SetPositionShadow(g_aPlayer[g_nSwitching].nIdyShadow, D3DXVECTOR3(g_aPlayer[g_nSwitching].pos.x, 0.1f, g_aPlayer[g_nSwitching].pos.z), 15);

		//�W���C�p�b�h�̏�ԍX�V
		if (g_JoyStatePlayer.nJoypadState == INPUT_JOYSTATE_PUSH)
		{
			g_JoyStatePlayer.nJoypadState = INPUT_JOYSTATE_NONE;
		}
		else if (g_JoyStatePlayer.nJoypadState == INPUT_JOYSTATE_NONE)
		{
			g_JoyStatePlayer.nJoypadState = INPUT_JOYSTATE_NOTPUSH;
		}
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;						// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;							// �}�e���A���f�[�^�ւ̃|�C���^

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_aPlayer[g_nSwitching].mtxWorld);
	if (g_aPlayer[g_nSwitching].state == PLAYERSTATE_AWAKENING)
	{
		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aPlayer[1].rotPizza.y, g_aPlayer[1].rotPizza.x, g_aPlayer[1].rotPizza.z);
		D3DXMatrixMultiply(&g_aPlayer[1].mtxWorld, &g_aPlayer[1].mtxWorld, &mtxRot);
	}
	else
	{
		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aPlayer[g_nSwitching].rot.y, g_aPlayer[g_nSwitching].rot.x, g_aPlayer[g_nSwitching].rot.z);
		D3DXMatrixMultiply(&g_aPlayer[g_nSwitching].mtxWorld, &g_aPlayer[g_nSwitching].mtxWorld, &mtxRot);
	}

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_aPlayer[g_nSwitching].pos.x, g_aPlayer[g_nSwitching].pos.y, g_aPlayer[g_nSwitching].pos.z);
	D3DXMatrixMultiply(&g_aPlayer[g_nSwitching].mtxWorld, &g_aPlayer[g_nSwitching].mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_aPlayer[g_nSwitching].mtxWorld);

	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	// �}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)g_aPlayer[g_nSwitching].pBuffMat->GetBufferPointer();

	if (g_aPlayer[g_nSwitching].bUse == true)
	{
		for (int nCntMat = 0; nCntMat < (int)g_aPlayer[g_nSwitching].nNumMat; nCntMat++)
		{
			// �}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, NULL);

			// ���f��(�p�[�c)�̕`��
			g_aPlayer[g_nSwitching].pMesh->DrawSubset(nCntMat);
		}
	}

	// �}�e���A�����f�t�H���g�ɖ߂�
	pDevice->SetMaterial(&matDef);

}

//=============================================================================
// �v���C���[�̎擾
//=============================================================================
PLAYER*GetPlayer(void)
{
	return &g_aPlayer[g_nSwitching];
}
