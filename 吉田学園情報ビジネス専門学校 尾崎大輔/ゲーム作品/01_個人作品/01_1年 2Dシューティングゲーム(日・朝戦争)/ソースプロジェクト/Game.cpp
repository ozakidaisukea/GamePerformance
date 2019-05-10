//=============================================================================
//
// �w�i�̏��� [Game.cpp]
// Author : Ozaki
//
//=============================================================================
#include "main.h"
#include "BG.h"
#include "bullet.h"
#include "input.h"
#include "Explosion.h"
#include "enemy.h"
#include "Player.h"
#include "Game.h"
#include "score.h"
#include "effect.h"
#include "fade.h"
#include "sound.h"
#include "Gameover.h"
#include "Pause.h"
#include "Time.h"
#include "ranking.h"
#include "boss.h"
#include "rankingBG.h"
#include "PauseBG.h"
#include "pausemenu.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define Game_WIDTH	(SCREEN_WIDTH)
#define Game_HEIGHT	(SCREEN_HEIGHT)

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
GAMESTATE g_gameState = GAMESTATE_NONE;			//�Q�[���̏��
int g_nCounterGameState ;
bool g_bPouse;									//�|�[�Y�����ǂ���
int g_CounterBoss;                              // �{�X�̑���
SELECTMODE *g_Select;
//=============================================================================
// ����������(�|���S��)
//=============================================================================
void InitGame(void)
{
	g_gameState = GAMESTATE_NORMAL;				//�ʏ��Ԃɐݒ�
	
	g_nCounterGameState = 0;
	g_CounterBoss = 0;

	//�w�i�̏���������
	InitBG();
	//�v���C���[�̏���������
	InitPlayer();
	//�e�̏���������
	InitBullet();
	//�����̏���������
	InitExplosion();
	//�G�̏���������
	InitEnemy();
	//�{�X�̏���������
	InitBoss();
	//�X�R�A�̏���������
	InitScore();
	//�G�t�F�N�g�̏���������
	InitEffect();
	//�|�[�Y�̏���������
	InitPause();
	//���Ԃ̏���������
	InitTime();
	//�|�[�Y�w�i�̏���������
	//InitPauseBG();
	//�|�[�Y�w�i�̏���������
	//InitPausecont();
	InitPauseSelect();

	//�G�̈ʒu
	SetEnemy(D3DXVECTOR3(100, 100, 0), 0);
	SetEnemy(D3DXVECTOR3(300, 100, 0), 1);
	SetEnemy(D3DXVECTOR3(500, 100, 0), 2);
	SetEnemy(D3DXVECTOR3(800, 150, 0), 3);
	SetEnemy(D3DXVECTOR3(1000,150, 0), 4);
	SetEnemy(D3DXVECTOR3(200, 270, 0), 5);
	SetEnemy(D3DXVECTOR3(400, 270, 0), 6);
	SetEnemy(D3DXVECTOR3(600, 270, 0), 7);
	SetEnemy(D3DXVECTOR3(900, 270, 0), 8);
	SetEnemy(D3DXVECTOR3(1100,270, 0), 9);

}

//=============================================================================
// �I������(�|���S��)
//=============================================================================
void UninitGame(void)
{
	//�w�i�̏I������
	UninitBG();
	//�v���C���[�̏I������
	UninitPlayer();
	//�o���b�g�̏I������
	UninitBullet();
	//�����̏I������
	UninitExplosion();
	//�G�̏I������
	UninitEnemy();
	//�{�X�̏I������
	UninitBoss();
	//�X�R�A�̏I������
	UninitScore();
	//�G�t�F�N�g�̏I������
	UninitEffect();
	//�|�[�Y�̏I������
	UninitPause();
	//���Ԃ̏I������
	UninitTime();
	//�|�[�Y�w�i�̏I������
	//UninitPauseBG();
	//�|�[�Y�w�i�̏I������
//	UninitPausecont();
	UninitPauseSelect();
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
		//�w�i�̍X�V����
		UpdateBG();
		//�e�̍X�V����
		UpdateBullet();
		//�G�t�F�N�g�̍X�V����
		UpdateEffect();
		//�����̍X�V����
		UpdateExplosion();
		//�G�̍X�V����
		UpdateEnemy();
		//�{�X�̍X�V����
		UpdateBoss();
		//�v���C���[�̍X�V����
		UpdatePlayer();
		//�X�R�A�̍X�V����
		UpdateScore();
		//���Ԃ̍X�V����
		UpdateTime();



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
			if (g_nCounterGameState >= 60)
			{
				g_gameState = GAMESTATE_NONE;
				AddRanking(GetScore());
				//���(���[�h)�̐ݒ�
				SetFade(MODE_GAMEOVER);
			}
			break;

			//�{�X
		case GAMESTATE_BOSS:
			if (g_CounterBoss <= 0)
			{
				SetBoss(D3DXVECTOR3(230, 180, 0.0f), 0);
				g_CounterBoss++;
			}

			break;
		
		}
	}
	else
	{
		UpdatePause();
		//UpdatePauseBG();
		//UpdatePausecont();
		UpdatePauseSelect();
		g_Select = GetPauseMode();

		if(*g_Select == SELECTMODE_CONTINE)
		{
			g_bPouse = g_bPouse ? false : true;
			*g_Select = SELECTMODE_NONE;
			PlaySound(SOUND_LABEL_SE_DECIDE);
		}
		if (*g_Select == SELECTMODE_RETRY)
		{
			g_bPouse = g_bPouse ? false : true;
			*g_Select = SELECTMODE_NONE;
			PlaySound(SOUND_LABEL_SE_DECIDE);
		}
		if (*g_Select == SELECTMODE_QUIT)
		{
			g_bPouse = g_bPouse ? false : true;
			*g_Select = SELECTMODE_NONE;
			PlaySound(SOUND_LABEL_SE_DECIDE);
			SetFade(MODE_TITLE);
		}
	}

}

//=============================================================================
// �`�揈��(�|���S��)
//=============================================================================
void DrawGame(void)
{
		//�w�i�̕`�揈��
		DrawBG();
		//�G�t�F�N�g�̕`�揈��
		DrawEffect();
		//�v���C���[�̕`�揈��
		DrawPlayer();
		//�o���b�g�̕`�揈��
		DrawBullet();
		//�����̕`�揈��
		DrawExplosion();
		//�G�̕`�揈��
		DrawEnemy();
		//�{�X�`�揈��
		DrawBoss();
		//�X�R�A�̕`�揈��
		DrawScore();
		//���Ԃ̕`�揈��
		DrawTime();

		if (g_bPouse == true)
	{//�|�[�Y�̕`�揈��
		DrawPause();
		//DrawPauseBG();
		//DrawPausecont();
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