//=============================================================================
//
// �����L���O���� [ranking.cpp]
// Author : Niwa Hodaka
//
//=============================================================================
#include "ranking.h"
#include "rankingscore.h"
#include "rankingrank.h"
#include "rankinglogo.h"
#include "rankingscore.h"
#include "fade.h"
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
int        g_nCounterRanking;          // �^�C�g����ʂɑJ�ڂ���^�C�~���O

//=============================================================================
// ����������
//=============================================================================
void InitRanking(void)
{
	// ���ʏ���������
	InitRankingRank();

	// ���S����������
	InitRankingLogo();

	g_nCounterRanking = 0;  // �J�E���^�[��0��
}
//=============================================================================
// �I������
//=============================================================================
void UninitRanking(void)
{
	// ���ʏI������
	UninitRankingRank();

	// ���S�I������
	UninitRankingLogo();
}
//=============================================================================
// �X�V����
//=============================================================================
void UpdateRanking(void)
{
	// ���ʍX�V����
	UpdateRankingRank();

	// ���S�X�V����
	UpdateRankingLogo();

	// �X�R�A�X�V����
	UpdateRankingScore();

	FADE fade;
	fade = GetFade();

	g_nCounterRanking++;

	if (GetFade() == FADE_NONE)
	{// �t�F�[�h��Ԃł͂Ȃ�
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{// ��ʑJ��
			SetFade(MODE_TITLE);
		}

		for (int nCntPad = 0; nCntPad < 2; nCntPad++)
		{
			for (int nCntButton = XIJS_BUTTON_4; nCntButton < XIJS_BUTTON_16; nCntButton++)
			{// ��������{�^�����̐������J��Ԃ�
				if (GetXInputTrigger(nCntPad, (XIJS_BUTTON)nCntButton) == TRUE)
				{
					SetFade(MODE_TITLE);
				}
			}
		}
	}

	// �����L���O�X�R�A�̎擾
	RANKINGSCORE *rankingscore;
	rankingscore = GetRankingScore();

	for (int nCntRankingScore = 0; nCntRankingScore < MAX_RANKINGSCORE; nCntRankingScore++, rankingscore++)
	{// �����L���O�X�R�A�̐������J��Ԃ�
		if (rankingscore->state == RANKINGSCORESTATE_UPDATE)
		{// �X�V��ԂɂȂ��Ă�����
			rankingscore->state = RANKINGSCORESTATE_NONE;
			rankingscore->col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
		}
	}
}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawRanking(void)
{
	// ���ʕ`�揈��
	DrawRankingRank();

	// ���S�`�揈��
	DrawRankingLogo();

	// �X�R�A�`�揈��
	DrawRankingScore();
}