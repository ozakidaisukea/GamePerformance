//=============================================================================
//
// �w�i�̏��� [Game.cpp]
// Author : Ozaki
//
//=============================================================================
#include "main.h"								// ���C��
#include "input.h"								// ����
#include "Player.h"								// �v���C���[
#include "Game.h"								// �Q�[��
#include "fade.h"								// �t�F�[�h
#include "Player.h"								// �v���C���[
#include "camera.h"								// �J����
#include "model.h"								// ���f��
#include "light.h"								// ���C�g
#include "bullet.h"								// �e
#include "wall.h"								// ��
#include "Explosion.h"							// ���j
#include "camera.h"								// �J����
#include "polygon.h"							// �|���S��
#include "light.h"								// ���C�g
#include "model.h"								// ���f��
#include "shadow.h"								// �e
#include "wall.h"								// ��
#include "bullet.h"								// �e
#include "billboard.h"							// �r���{�[�h
#include "effect.h"								// �G�t�F�N�g
#include "Explosion.h"							// ����
#include "Player.h"								// �v���C���[
#include "score.h"								// �X�R�A
#include "Scoreframe.h"							// �X�R�A�g
#include "sound.h"								// ��
#include "Pause.h"								// �|�[�Y
#include "PauseBG.h"							// �|�[�Y�w�i
#include "pausemenu.h"							// �|�[�Y���j���[
#include "model.h"
#include "Time.h"								// �^�C��
#include "Timeframe.h"							// �^�C���g
#include "ranking.h"							// �����L���O
#include "particle.h"							// �p�[�e�B�N��
#include "Player2.h"
#include "Player3.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define Game_WIDTH	(SCREEN_WIDTH)
#define Game_HEIGHT	(SCREEN_HEIGHT)

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
GAMESTATE g_gameState = GAMESTATE_NONE;			//�Q�[���̏��
int g_nCounterGameState;						//�Q�[�����Ă���
bool g_bPouse;									//�|�[�Y�����ǂ���
SELECTMODE *g_Select;							//
int gametimer;
//=============================================================================
// ����������(�|���S��)
//=============================================================================
void InitGame(void)
{
	g_gameState = GAMESTATE_NORMAL;				//�ʏ��Ԃɐݒ�

	g_nCounterGameState = 0;

	// �e�̏���������
	InitShadow();

	//�v���C���[�̏���������
	InitPlayer();

	//�����̏���������
	//InitExplosion();

	// �J�����̏���������
	InitCamera();

	// ���C�g�̏���������
	InitLight();

	// �|���S���̏���������
	InitPolygon();

	// ���f���̏���������
	InitModel();

	// �ǂ̏�����
	InitWall();

	// �r���{�[�h����������
	InitBillboard();

	// �e�̏���������
	InitBullet();

	// �G�t�F�N�g�̏���������
	InitEffect();

	// �����̏���������
	InitExplosion();

	// �t�B�[���h�̏���������
	//InitMeshField();

	// ���b�V���ǂ̏���������
	//InitMeshWall();

	// ���b�V���~���̏���������
	//InitMeshCylinder();

	// �v���C���[�̏���������
	InitPlayer();

	//�X�R�A�̏���������
	InitScore();
	InitScoreFrame();

	//�|�[�Y�̏���������
	InitPause();

	//���Ԃ̏���������
	InitTime();
	InitTimeFrame();

	//�|�[�Y�̏���������
	InitPause();
	InitPauseSelect();

	InitParticle();
	// �v���C���[2�̏���������
	InitPlayer2();

	// �v���C���[3�̏���������
	InitPlayer3();

	SetWall(D3DXVECTOR3(0.0f, 0.0f, -1000.0f), D3DXVECTOR3(0.0f, D3DX_PI*1.0f, 0.0f));	 // ��O
	SetWall(D3DXVECTOR3(0.0f, 0.0f, 1000.0f), D3DXVECTOR3(0.0f, -D3DX_PI*0.0f, 0.0f));	 // ��
	SetWall(D3DXVECTOR3(-1000.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI*-0.5f, 0.0f));	 // ��
	SetWall(D3DXVECTOR3(1000.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f));	 // �E

	SetModel(D3DXVECTOR3(800.0f, 0.0f, -1000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetModel(D3DXVECTOR3(400.0f, 0.0f, -1000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1);
	SetModel(D3DXVECTOR3(10.0f, 0.0f, -1000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 2);
	SetModel(D3DXVECTOR3(-400.0f, 0.0f, -1000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3);
	SetModel(D3DXVECTOR3(-800.0f, 0.0f, -1000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 4);


}

//=============================================================================
// �I������(�|���S��)
//=============================================================================
void UninitGame(void)
{
	// �J�����̏I������
	UninitCamera();

	// ���C�g�̏I������
	UninitLight();

	//�v���C���[�̏I������
	UninitPlayer();

	//�v���C���[2�̏I������
	UninitPlayer2();

	//�v���C���[3�̏I������
	UninitPlayer3();

	//�����̏I������
	UninitExplosion();

	// �|���S���̏I������
	UninitPolygon();

	// ���f���̏I������
	UninitModel();

	// �e�̏I������
	UninitShadow();

	// �ǂ̏I������
	UninitWall();

	// �r���{�[�h�̏I������
	//UninitBillboard();

	// �e�̏I������
	UninitBullet();

	// �G�t�F�N�g�̏I������
	//UninitEffect();

	// �t�B�[���h�̏I������
	//UninitMeshField();

	// ���b�V���ǂ̏I������
	//UninitMeshWall();

	// ���b�V���~���̏I������
	//UninitMeshCylinder();

	////�X�R�A�̏I������
	UninitScore();
	UninitScoreFrame();

	//���Ԃ̏I������
	UninitTime();
	UninitTimeFrame();

	//�|�[�Y�̏I������
	UninitPause();
	UninitPauseSelect();

	UninitParticle();
}

//=============================================================================
// �X�V����(�|���S��)
//=============================================================================
void UpdateGame(void)
{

	if (GetKeyboardTrigger(DIK_P) == true)
	{//�|�[�Y ON/OFF
		g_bPouse = g_bPouse ? false : true;
	}
	if (g_bPouse == false)
	{
		// �J�����̍X�V����
		UpdateCamera();

		// ���C�g�̍X�V����
		UpdateLight();

		//�����̍X�V����
		UpdateExplosion();
		//�v���C���[�̍X�V����
		UpdatePlayer();
		//�X�R�A�̍X�V����
		UpdateScore();
		UpdateScoreFrame();

		//���Ԃ̍X�V����
		UpdateTime();
		UpdateTimeFrame();

		// �|���S���̍X�V����
		UpdatePolygon();

		// ���f���̍X�V����
		UpdateModel();

		// �e�̍X�V����
		UpdateShadow();

		// �ǂ̍X�V����
		UpdateWall();

		// �r���{�[�h�̍X�V����
	//	UpdateBillboard();

		// �e�̍X�V����
		UpdateBullet();

		// �G�t�F�N�g�̍X�V����
		UpdateEffect();

		// �����̍X�V����
		UpdateExplosion();

		// �t�B�[���h�̍X�V����
		//UpdateMeshField();

		// ���b�V���ǂ̍X�V����
		//UpdateMeshWall();

		// ���b�V���~���̍X�V����
		//UpdateMeshCylinder();

		// �v���C���[�̍X�V����
		UpdatePlayer();

		// �v���C���[2�̍X�V����
		UpdatePlayer2();

		// �v���C���[3�̍X�V����
		UpdatePlayer3();

		UpdateParticle();


		switch (g_gameState)
		{
		case GAMESTATE_NORMAL:
			break;
			//�Q�[���I��
		case GAMESTATE_END:
			g_nCounterGameState++;
			if (g_nCounterGameState >= 60)
			{
				g_gameState = GAMESTATE_NONE;
				//���(���[�h)�̐ݒ�
				AddRanking(GetScore());
				SetFade(MODE_RESULT);
			}
			break;
			//�Q�[���I�[�o�[
		case GAMESTATE_GAMEOVER:
			g_nCounterGameState++;
			if (g_nCounterGameState >= 100)
			{
				g_gameState = GAMESTATE_NONE;
				AddRanking(GetScore());
				//���(���[�h)�̐ݒ�
				SetFade(MODE_GAMEOVER);
			}
			break;
		}
	}
	else
	{
		UpdatePause();
		UpdatePauseSelect();
		g_Select = GetPauseMode();

		if (*g_Select == SELECTMODE_CONTINE)
		{
			g_bPouse = g_bPouse ? false : true;
			*g_Select = SELECTMODE_NONE;
			//PlaySound(SOUND_LABEL_SE_DECIDE);
		}
		if (*g_Select == SELECTMODE_RETRY)
		{
			g_bPouse = g_bPouse ? false : true;
			*g_Select = SELECTMODE_NONE;
			//PlaySound(SOUND_LABEL_SE_DECIDE);
		}
		if (*g_Select == SELECTMODE_QUIT)
		{
			g_bPouse = g_bPouse ? false : true;
			*g_Select = SELECTMODE_NONE;
			//PlaySound(SOUND_LABEL_SE_DECIDE);
			SetFade(MODE_TITLE);
		}
	}

	FADE Fade;
	Fade = GetFade();
	gametimer++;
	if (Fade == FADE_NONE)
	{
		if (GetKeyboardTrigger(DIK_Z) == true)
		{
			if (gametimer >= 3)
			{
				SetFade(MODE_RESULT);
			}


			//SetFade(MODE_TUTORIAL);
			//PlaySound(SOUND_LABEL_SE_DECIDE);
		}
	}

}

//=============================================================================
// �`�揈��(�|���S��)
//=============================================================================
void DrawGame(void)
{
	SetCamera();

	//�����̕`�揈��
	DrawExplosion();

	//�X�R�A�̕`�揈��
	DrawScore();
	DrawScoreFrame();

	//���Ԃ̕`�揈��
	DrawTime();
	DrawTimeFrame();

	//�v���C���[�̕`�揈��
	DrawPlayer();

	//�v���C���[2�̕`�揈��
	DrawPlayer2();

	//�v���C���[3�̕`�揈��
	DrawPlayer3();

	DrawPolygon();

	DrawWall();

	//DrawBillboard();

	DrawBullet();

	DrawExplosion();

	DrawModel();

	DrawShadow();

	DrawParticle();

	if (g_bPouse == true)
	{//�|�[�Y�̕`�揈��
		DrawPause();
		DrawPauseSelect();
	}

}

//=============================================================================
//
//=============================================================================
void SetGameState(GAMESTATE state)
{
	g_gameState = state;
	g_nCounterGameState = 0;
}

//=============================================================================
//
//=============================================================================
GAMESTATE GetGameState(void)
{
	return g_gameState;
}