//=============================================================================
//
// �Q�[����ʏ��� [game.cpp]
// Author : Niwa Hodaka
//
//=============================================================================
#include "game.h"
#include "fade.h"
#include "result.h"
#include "input.h"
#include "camera.h"
#include "light.h"
#include "pause.h"
#include "pauseselect.h"
#include "pauselogo.h"
#include "rankingscore.h"
#include "sound.h"


#include "sky.h"
#include "field.h"
#include "shadow.h"
#include "player.h"
#include "effect.h"
#include "lifegauge.h"
#include "baselifegauge.h"
#include "coverlife.h"
#include "damagegauge.h"
#include "ultgauge.h"
#include "timer.h"
#include "model.h"
#include "Rush.h"

//=============================================================================
// �\���̒�`
//=============================================================================

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================

//=============================================================================
// �O���[�o���ϐ��錾
//=============================================================================
GAMESTATE g_GameState = GAMESTATE_NONE;   // �Q�[���̏��
int       g_nCounterGameState;            // �Q�[���̏�ԊǗ��J�E���^�[
bool      g_bPuase;                       // �|�[�Y�����ǂ���

//=============================================================================
// �Q�[����ʏ���������
//=============================================================================
void InitGame(void)
{
	// �J�����̏���������
	InitCamera();

	// ���C�g�̏���������
	InitLight();

	// ��̏���������
	InitSky();

	// �n�ʂ̏���������
	InitField();

	// �e�̏���������
	InitShadow();

	// �v���C���[�̏���������
	InitPlayer();

	// �G�t�F�N�g�̏���������
	InitEffect();

	// �̗̓Q�[�W�̏���������
	InitLifeGauge();

	// �̗̓Q�[�W(�x�[�X)�̍X�V����
	InitBaseLifeGauge();

	// �̗̓Q�[�W(�J�o�[)�̏���������
	InitCoverLife();

	// �̗̓Q�[�W(�_���[�W)�̏���������
	InitDamageGauge();

	// �K�E�Q�[�W�̏���������
	InitUltGauge();

	// �^�C�}�[�̏���������
	InitTimer();

	// ���f���̏���������
	InitModel();

	InitRush();

	// �|�[�Y����������
	InitPause();

	// �|�[�Y���S����������
	InitPauseLogo();

	// �|�[�Y���ڏ���������
	InitPauseSelect();

	g_GameState = GAMESTATE_NORMAL;
	g_nCounterGameState = 0;
	g_bPuase = false;
}
//=============================================================================
// �Q�[����ʏI������
//=============================================================================
void UninitGame(void)
{
	// �J�����̏I������
	UninitCamera();

	// ���C�g�̏I������
	UninitLight();

	// ��̏I������
	UninitSky();

	// ���f���̏I������
	UninitModel();

	// �n�ʂ̏I������
	UninitField();

	// �e�̏I������
	UninitShadow();

	// �v���C���[�̏I������
	UninitPlayer();

	// �G�t�F�N�g�̏I������
	UninitEffect();

	// �̗̓Q�[�W(�x�[�X)�̍X�V����
	UninitBaseLifeGauge();

	// �̗̓Q�[�W�̏I������
	UninitLifeGauge();

	// �̗̓Q�[�W(�J�o�[)�̏I������
	UninitCoverLife();

	// �̗̓Q�[�W(�_���[�W)�̏I������
	UninitDamageGauge();

	// �K�E�Q�[�W�̏I������
	UninitUltGauge();

	// �^�C�}�[�̏I������
	UninitTimer();

	// ���f���̏I������
	UninitModel();

	UninitRush();

	// �|�[�Y�I������
	UninitPause();

	// �|�[�Y���S�I������
	UninitPauseLogo();

	// �|�[�Y���ڏI������
	UninitPauseSelect();
}
//=============================================================================
// �Q�[����ʍX�V����
//=============================================================================
void UpdateGame(void)
{
	FADE fade;
	fade = GetFade();

	if (GetXInputTrigger(0, XIJS_BUTTON_4) == TRUE && fade == FADE_NONE && g_GameState == GAMESTATE_NORMAL || GetKeyboardTrigger(DIK_P) == true && fade == FADE_NONE && g_GameState == GAMESTATE_NORMAL)
	{// �|�[�YON/OFF
		g_bPuase = g_bPuase ? false : true;
	}

	if (g_bPuase == false)
	{// �|�[�YOFF
	    // �J�����̍X�V����
		UpdateCamera();

		// ���C�g�̍X�V����
		UpdateLight();

		// ���f���̏I������
		UpdateModel();

		// ��̍X�V����
		UpdateSky();

		// �n�ʂ̍X�V����
		UpdateField();

		// �e�̍X�V����
		UpdateShadow();

		// �v���C���[�̍X�V����
		UpdatePlayer();

		// �G�t�F�N�g�̍X�V����
		UpdateEffect();

		// �̗̓Q�[�W(�x�[�X)�̍X�V����
		UpdateBaseLifeGauge();

		// �̗̓Q�[�W�̍X�V����
		UpdateLifeGauge();

		// �̗̓Q�[�W(�J�o�[)�̍X�V����
		UpdateCoverLife();

		// �̗̓Q�[�W(�_���[�W)�̍X�V����
		UpdateDamageGauge();

		// �K�E�Q�[�W�̍X�V����
		UpdateUltGauge();

		// �^�C�}�[�̍X�V����
		UpdateTimer();

		// ���f���̍X�V����
		UpdateModel();

		UpdateRush();

#ifdef _DEBUG
		if (GetKeyboardTrigger(DIK_F2) && g_GameState == GAMESTATE_NORMAL)
		{// �f�o�b�N�p
			g_GameState = GAMESTATE_END;
		}
#endif

		switch (g_GameState)
		{
		case GAMESTATE_NORMAL:  // �ʏ���
			break;

		case GAMESTATE_RETRY:   // ��蒼�����
			g_nCounterGameState++;
			if (g_nCounterGameState >= 120)
			{// ��莞�Ԃ�������
				g_GameState = GAMESTATE_NONE_RETRY;
				SetFade(MODE_GAME);
			}
			break;

		case GAMESTATE_END:     //�I�����
			g_nCounterGameState++;
			if (g_nCounterGameState >= 120)
			{// ��莞�Ԃ�������
				g_GameState = GAMESTATE_NONE;
				SetFade(MODE_RESULT);
			}
			break;
		}
	}
	else
	{
		// �|�[�Y�X�V����
		UpdatePause();

		// �|�[�Y���S�X�V����
		UpdatePauseLogo();

		// �|�[�Y���ڍX�V����
		UpdatePauseSelect();

		if (GetXInputTrigger(0,XIJS_BUTTON_11) == TRUE || GetKeyboardTrigger(DIK_RETURN) == true)
		{// ����{�^���������ꂽ
			RESTART restart;
			restart = GetRestart();
			FADE fade;
			fade = GetFade();

			if (fade == FADE_NONE)
			{// �t�F�[�h��ԂłȂ�
				switch (restart)
				{
				case RESTART_CONTINUE:  // �Q�[���ĊJ
					break;
				case RESTART_RETRY:     // �Q�[����蒼��
					g_GameState = GAMESTATE_NONE;
					SetFade(MODE_GAME);
					return; // ����ȏ�Q�[����Update���Ȃ�
					break;
				case RESTART_QUIT:      // �^�C�g���J��
					g_GameState = GAMESTATE_NONE;
					SetFade(MODE_TITLE);
					return; // ����ȏ�Q�[����Update���Ȃ�
					break;
				}
				g_bPuase = g_bPuase ? false : true; // �|�[�Y�͉���
			}
		}
	}
}
//=============================================================================
// �Q�[����ʕ`�揈��
//=============================================================================
void DrawGame(void)
{
	// �J�����̐ݒ�
	SetCamera();

	// ��̕`�揈��
	DrawSky();

	// �n�ʂ̕`�揈��
	DrawField();

	// �e�̕`�揈��
	DrawShadow();

	// ���f���̍X�V����
	DrawModel();

	// �v���C���[�̕`�揈��
	DrawPlayer();

	// �G�t�F�N�g�̕`�揈��
	DrawEffect();

	// �̗̓Q�[�W(�x�[�X)�̕`�揈��
	DrawBaseLifeGauge();

	// �̗̓Q�[�W(�_���[�W)�̕`�揈��
	DrawDamageGauge();

	// �̗̓Q�[�W�̕`�揈��
	DrawLifeGauge();

	// �̗̓Q�[�W(�J�o�[)�̕`�揈��
	DrawCoverLife();

	// �K�E�Q�[�W�̕`�揈��
	DrawUltGauge();

	// �^�C�}�[�̍X�V����
	DrawTimer();
	DrawRush();

	if (g_bPuase == true)
	{// �|�[�Y���Ȃ�
		// �|�[�Y�`�揈��
		DrawPause();

		// �|�[�Y���S�`�揈��
		DrawPauseLogo();

		// �|�[�Y���ڕ`�揈��
		DrawPauseSelect();
	}
}
//=============================================================================
// �Q�[����ʐݒ菈��
//=============================================================================
void SetGameState(GAMESTATE state)
{
	g_GameState = state;
	g_nCounterGameState = 0;
}
//=============================================================================
// �Q�[����ʎ擾����
//=============================================================================
GAMESTATE GetGameState(void)
{
	return g_GameState;
}