//=============================================================================
//
// �w�i�̏��� [Game.cpp]
// Author : Ozaki
//
//=============================================================================
#include "main.h"								// ���C��
#include "bg.h"									// �w�i
#include "bg2.h"								// �w�i�Q
#include "block.h"								// �u���b�N
#include "input.h"								// ����
#include "Player.h"								// �v���C���[
#include "Game.h"								// �Q�[��
#include "item.h"								// �A�C�e��
#include "fade.h"								// �t�F�[�h
#include "score.h"								// �X�R�A
#include "Scoreframe.h"							// �X�R�A�g
#include "sound.h"								// ��
#include "Gameover.h"							// �Q�[���I�[���@�[
#include "Pause.h"								// �|�[�Y
#include "Time.h"								// ����
#include "Timeframe.h"							// ���Ԙg
#include "ranking.h"							// �����L���O
#include "rankingBG.h"							// �����L���O�w�i
#include "PauseBG.h"							// �|�[�Y�w�i
#include "pausemenu.h"							// �|�[�Y���j���[
#include "Explosion.h"							// ����
#include "dokan.h"								// �y��

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

BlockInfo g_aBlockInfo[] =						//�e�u���b�N�̈ʒu�Ǝ��
{

	{ D3DXVECTOR3(160, 200, 0.0f), 40, 40,BlockType_Normal },			// �ʏ�u���b�N(��)1
	{ D3DXVECTOR3(160, 240, 0.0f), 40, 40,BlockType_Normal },			// �ʏ�u���b�N(��)2
	{ D3DXVECTOR3(160, 280, 0.0f), 40, 40,BlockType_Normal },			// �ʏ�u���b�N(��)4
	{ D3DXVECTOR3(160, 320, 0.0f), 40, 40,BlockType_Normal },			// �ʏ�u���b�N(��)5
	{ D3DXVECTOR3(160, 360, 0.0f), 40, 40,BlockType_Normal },			// �ʏ�u���b�N(��)7
	{ D3DXVECTOR3(160, 400, 0.0f), 40, 40,BlockType_Normal },			// �ʏ�u���b�N(��)8
	{ D3DXVECTOR3(160, 440, 0.0f), 40, 40,BlockType_Normal },			// �ʏ�u���b�N(��)9
	{ D3DXVECTOR3(160, 480, 0.0f), 40, 40,BlockType_Normal },			// �ʏ�u���b�N(��)10
	{ D3DXVECTOR3(160, 520, 0.0f), 40, 40,BlockType_Normal },			// �ʏ�u���b�N(��)11
	{ D3DXVECTOR3(160, 560, 0.0f), 40, 40,BlockType_Normal },			// �ʏ�u���b�N(��)12
	{ D3DXVECTOR3(160, 600, 0.0f), 40, 40,BlockType_Normal },			// �ʏ�u���b�N(��)13
	{ D3DXVECTOR3(160, 640, 0.0f), 40, 40,BlockType_Normal },			// �ʏ�u���b�N(��)14

	{ D3DXVECTOR3(900, 630, 0.0f), 300, 50,BlockType_Beltconveyor },	// �x���g�R���x��
	{ D3DXVECTOR3(550, 350, 0.0f), 83, 50,BlockType_Ice },				// �X��

	{ D3DXVECTOR3(400, 200, 0.0f), 40, 40,BlockType_Normal },			// �ʏ�u���b�N(�E)1
	{ D3DXVECTOR3(400, 240, 0.0f), 40, 40,BlockType_Normal },			// �ʏ�u���b�N(�E)2
	{ D3DXVECTOR3(400, 280, 0.0f), 40, 40,BlockType_Normal },			// �ʏ�u���b�N(�E)3
	{ D3DXVECTOR3(400, 320, 0.0f), 40, 40,BlockType_Normal },			// �ʏ�u���b�N(�E)4
	{ D3DXVECTOR3(400, 360, 0.0f), 40, 40,BlockType_Normal },			// �ʏ�u���b�N(�E)5
	{ D3DXVECTOR3(400, 400, 0.0f), 40, 40,BlockType_Normal },			// �ʏ�u���b�N(�E)6
	{ D3DXVECTOR3(400, 440, 0.0f), 40, 40,BlockType_Normal },			// �ʏ�u���b�N(�E)7
	{ D3DXVECTOR3(400, 480, 0.0f), 40, 40,BlockType_Normal },			// �ʏ�u���b�N(�E)8
	{ D3DXVECTOR3(400, 520, 0.0f), 40, 40,BlockType_Normal },			// �ʏ�u���b�N(�E)9
	{ D3DXVECTOR3(400, 560, 0.0f), 40, 40,BlockType_Normal },			// �ʏ�u���b�N(�E)10
	{ D3DXVECTOR3(400, 600, 0.0f), 40, 40,BlockType_Normal },			// �ʏ�u���b�N(�E)11
	{ D3DXVECTOR3(400, 640, 0.0f), 40, 40,BlockType_Normal },			// �ʏ�u���b�N(�E)12

	{ D3DXVECTOR3(220, 620, 0.0f), 60, 70, BlockType_Junp },			// �W�����v��
	{ D3DXVECTOR3(310, 400, 0.0f), 90, 40, BlockType_Isi },				// �΃u���b�N
	{ D3DXVECTOR3(900, 460, 0.0f), 160, 40, BlockType_Move },			// �ړ���
	{ D3DXVECTOR3(700, 400, 0.0f), 60, 60, BlockType_Question1 },		// �H1�u���b�N
	{ D3DXVECTOR3(80, 500, 0.0f), 60, 60, BlockType_Question2 },		// �H2�u���b�N
	{ D3DXVECTOR3(-100,680, 0.0f), 1500, 40, BlockType_Normal},			// ���u���b�N
};

ItemInfo g_aItemInfo[] =						//�e�A�C�e���̈ʒu
{
	{D3DXVECTOR3(500, 450, 0.0f), 30,50,ITEMSTATE_COIN },
	{D3DXVECTOR3(850, 550, 0.0f), 30,50,ITEMSTATE_COIN },
	{D3DXVECTOR3(200, 160, 0.0f), 30,50,ITEMSTATE_COIN },
	{D3DXVECTOR3(100, 250, 0.0f), 30,50,ITEMSTATE_COIN },
	{D3DXVECTOR3(10,  500, 0.0f), 30,50,ITEMSTATE_COIN },
	{D3DXVECTOR3(250, 160, 0.0f), 30,50,ITEMSTATE_COIN },
	{D3DXVECTOR3(400, 160, 0.0f), 30,50,ITEMSTATE_COIN },
	{D3DXVECTOR3(360, 600, 0.0f), 30,50,ITEMSTATE_COIN },
};

//=============================================================================
// ����������(�|���S��)
//=============================================================================
void InitGame(void)
{
	g_gameState = GAMESTATE_NORMAL;				//�ʏ��Ԃɐݒ�

	g_nCounterGameState = 0;

	//�w�i�̏���������
	Initbg();
	//�w�i�̏���������
	Initbg2();
	//�u���b�N�̏���������
	InitBlock();
	InitDokan();
	//�v���C���[�̏���������
	InitPlayer();
	//�A�C�e���̏���������
	InitItem();
	//�����̏���������
	InitExplosion();
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

	int nCntBlock = 0;
	int nCntItem = 0;
	//�u���b�N�̏����ʒu(���ʒu,�c�ʒu,����),����,����,�u���b�N��);
	for ( nCntBlock = 0; nCntBlock < sizeof g_aBlockInfo / sizeof(BlockInfo); nCntBlock++)
	{
		SetBlock(g_aBlockInfo[nCntBlock].pos, g_aBlockInfo[nCntBlock].fwidth, g_aBlockInfo[nCntBlock].fheight, g_aBlockInfo[nCntBlock].type);
	}

	//�R�C���̏����ʒu(���ʒu,�c�ʒu,�����x),�Ȃ�)
	for (nCntItem = 0; nCntItem < sizeof g_aItemInfo / sizeof(ItemInfo); nCntItem++)
	{
		SetItem(g_aItemInfo[nCntItem].pos, g_aItemInfo[nCntItem].fwidth, g_aItemInfo[nCntItem].fheigth, g_aItemInfo[nCntItem].type);
	}

	SetDokan(D3DXVECTOR3(680, 600, 0.0f), 100, 100, DokanType_Dokan);
}

//=============================================================================
// �I������(�|���S��)
//=============================================================================
void UninitGame(void)
{
	//�w�i�̏I������
	Uninitbg();
	Uninitbg2();
	//�u���b�N�̏I������
	UninitBlock();
	UninitDokan();
	//�v���C���[�̏I������
	UninitPlayer();
	//�A�C�e���̏I������
	UninitItem();
	//�����̏I������
	UninitExplosion();
	//�X�R�A�̏I������
	UninitScore();
	UninitScoreFrame();
	//���Ԃ̏I������
	UninitTime();
	UninitTimeFrame();
	//�|�[�Y�̏I������
	UninitPause();
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
		Updatebg();
		Updatebg2();
		//�A�C�e���̍X�V����
		UpdateItem();
		//�����̍X�V����
		UpdateExplosion();
		//�u���b�N�̍X�V����
		UpdateBlock();
		UpdateDokan();
		//�v���C���[�̍X�V����
		UpdatePlayer();
		//�X�R�A�̍X�V����
		UpdateScore();
		UpdateScoreFrame();
		//���Ԃ̍X�V����
		UpdateTime();
		UpdateTimeFrame();


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
	Drawbg();
	Drawbg2();
	//�u���b�N�̕`�揈��
	DrawBlock();
	//�A�C�e���`�揈��
	DrawItem();
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
	DrawDokan();

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