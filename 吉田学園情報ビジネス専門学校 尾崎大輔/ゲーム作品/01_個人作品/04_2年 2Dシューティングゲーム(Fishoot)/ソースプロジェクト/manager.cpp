//=============================================================================
//
// �}�l�[�W���[�̏��� [manager.cpp]
// Author : Ozaki
//
//=============================================================================
#include "manager.h"
#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "scene2D.h"
#include "input.h"
#include "sound.h"
#include "title.h"
#include "tutorial.h"
#include "game.h"
#include "result.h"
#include "gameover.h"
#include "ranking.h"
#include "fade.h"
#include "score.h"
#include "joypad.h"
#include "sousa.h"

//=============================================================================
// �ÓI�����o-�ϐ��錾
//=============================================================================
CRenderer*CManager::m_pRenderer = NULL;					// �����_���[
CInputKeyboard*CManager::m_pInputKeyboard = NULL;		// �L�[�{�[�h
CInputjoypad*CManager::m_pInputJoypad = NULL;			// �p�b�h
CSound*CManager::m_pSound = NULL;						// �T�E���h
CTitle*CManager::m_pTitle = NULL;						// �^�C�g��
CTutorial*CManager::m_pTutorial = NULL;					// �`���[�g���A��
CGame*CManager::m_pGame = NULL;							// �Q�[��
CResult*CManager::m_pResult = NULL;						// ���U���g
CGameover*CManager::m_pGameover = NULL;					// �Q�[���I�[�o�[
CRanking*CManager::m_pRanking = NULL;					// �����L���O
CFade*CManager::m_pFade = NULL;							// �t�F�[�h
CScore*CManager::m_pScore = NULL;						// �X�R�A
CSousa*CManager::m_pSousa = NULL;						// ������@

int CManager::m_Rankingscore[MAX_RANKING] = {};			// �����L���O�̃X�R�A

CManager::MODE CManager::m_mode;						// ���[�h

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CManager::CManager()
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CManager::~CManager()
{

}

//=============================================================================
// ���͏���
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{

	m_pRenderer = new CRenderer;
	m_pInputKeyboard = new CInputKeyboard;
	m_pInputJoypad = new CInputjoypad;
	m_pSound = new CSound;

	// ����������
	if (FAILED(m_pRenderer->Init(hWnd, bWindow)))
	{
		return -1;
	}

	if (FAILED(m_pInputKeyboard->Init(hInstance,hWnd)))
	{
		return -1;
	}

	if (m_pInputJoypad != NULL)
	{
		m_pInputJoypad->Init(hInstance, hWnd);
	}

	m_pSound->InitSound(hWnd);

	// �t�F�[�h����
	m_pFade = CFade::Create();

	// ���[�h�̐ݒ�
	m_mode = MODE_TITLE;


	for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
	{
		m_Rankingscore[nCnt] = 0;
	}

	SetMode(m_mode);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CManager::Uninit(void)
{
	// �S�Ă̏I����j��
	CScene::ReleaseAll();

	// �����_���[��j��
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Uninit();

		delete m_pRenderer;
		m_pRenderer = NULL;
	}

	// �L�[�{�[�h��j��
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Uninit();

		delete m_pInputKeyboard;
		m_pInputKeyboard = NULL;
	}

	// �p�b�h��j��
	if (m_pInputJoypad != NULL)
	{
		m_pInputJoypad->Uninit();

		delete m_pInputJoypad;
		m_pInputJoypad = NULL;
	}

	// �t�F�[�h
	if (m_pFade != NULL)
	{
		m_pFade->Uninit();

		delete m_pFade;
		m_pFade = NULL;
	}

	// �T�E���h
	if (m_pSound != NULL)
	{
		m_pSound->UninitSound();

		delete m_pSound;
		m_pSound = NULL;
	}

	// �^�C�g��
	if (m_pTitle != NULL)
	{
		m_pTitle->Uninit();

		delete m_pTitle;
		m_pTitle = NULL;
	}

	// ������@
	if (m_pSousa != NULL)
	{
		m_pSousa->Uninit();

		delete m_pSousa;
		m_pSousa = NULL;
	}

	// �`���[�g���A��
	if (m_pTutorial != NULL)
	{
		m_pTutorial->Uninit();

		delete m_pTutorial;
		m_pTutorial = NULL;
	}

	// �Q�[��
	if (m_pGame != NULL)
	{
		m_pGame->Uninit();

		delete m_pGame;
		m_pGame = NULL;
	}

	// ���U���g
	if (m_pResult != NULL)
	{
		m_pResult->Uninit();

		delete m_pResult;
		m_pResult = NULL;
	}

	// �Q�[���I�[�o�[
	if (m_pGameover != NULL)
	{
		m_pGameover->Uninit();

		delete m_pGameover;
		m_pGameover = NULL;
	}

	// �����L���O
	if (m_pRanking != NULL)
	{
		m_pRanking->Uninit();

		delete m_pRanking;
		m_pRanking = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void CManager::Update(void)
{
	// �L�[�{�[�h�̍X�V
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Update();
	}

	// �p�b�h�̍X�V
	if (m_pInputJoypad != NULL)
	{
		m_pInputJoypad->Update();
	}

	// �����_���[�̍X�V
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Update();
	}

	// �t�F�[�h�̍X�V
	if (m_pFade != NULL)
	{
		m_pFade->Update();
	}

	//�X�V�̊J�n
	switch (m_mode)
	{
		// �^�C�g��
	case MODE_TITLE:
		if (m_pTitle != NULL)
		{
 			m_pTitle->Update();
		}
		break;

		// ������@
	case MODE_SOUSA:
		if (m_pSousa != NULL)
		{
			m_pSousa->Update();
		}
		break;

		// �`���[�g���A��
	case MODE_TUTORIAL:
		if (m_pTutorial != NULL)
		{
			m_pTutorial->Update();
		}
		break;

		// �Q�[��
	case MODE_GAME:
		if (m_pGame != NULL)
		{
			m_pGame->Update();
		}
		break;

		// ���U���g
	case MODE_RESULT:
		if (m_pResult != NULL)
		{
			m_pResult->Update();
		}
		break;

		// �Q�[���I�[�o�[
	case MODE_GAMEOVER:
		if (m_pGameover != NULL)
		{
			m_pGameover->Update();
		}
		break;

		// �����L���O
	case MODE_RANKING:
		if (m_pRanking != NULL)
		{
			m_pRanking->Update();
		}
		break;
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CManager::Draw(void)
{
	// �L�[�{�[�h���擾
	CSound *pSound;
	pSound = CManager::GetSound();

	// �����_���[�̕`��
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Draw();
	}

	//�`��̊J�n
	switch (m_mode)
	{
		// �^�C�g��
	case MODE_TITLE:
		if (m_pTitle != NULL)
		{
			m_pTitle->Draw();
		}
		break;

		// ������@
	case MODE_SOUSA:
		if (m_pSousa != NULL)
		{
			m_pSousa->Draw();
		}
		break;

		// �`���[�g���A��
	case MODE_TUTORIAL:
		if (m_pTutorial != NULL)
		{
			m_pTutorial->Draw();
		}
		break;

		// �Q�[��
	case MODE_GAME:
		if (m_pGame != NULL)
		{
			m_pGame->Draw();
		}
		break;

		// ���U���g
	case MODE_RESULT:
		if (m_pResult != NULL)
		{
			m_pResult->Draw();
		}
		break;

		// �Q�[���I�[�o�[
	case MODE_GAMEOVER:
		if (m_pGameover != NULL)
		{
			m_pGameover->Draw();
		}
		break;

		// �����L���O
	case MODE_RANKING:
		if (m_pRanking != NULL)
		{
			m_pRanking->Draw();
		}
		break;
	}
}

//=============================================================================
// ���[�h�̐ݒ菈��
//=============================================================================
void CManager::SetMode(MODE mode)
{
	// �T�E���h���擾
	CSound *pSound;
	pSound = CManager::GetSound();

	// �I��
	switch (m_mode)
	{
		// �^�C�g��
	case MODE_TITLE:
		if (m_pTitle != NULL)
		{
			m_pTitle->Uninit();

			pSound->StopSound(pSound->SOUND_LABEL_BGM_TITLE);
			delete m_pTitle;
			m_pTitle = NULL;
		}
		break;

		// �`���[�g���A��
	case MODE_SOUSA:
		if (m_pSousa != NULL)
		{
			m_pSousa->Uninit();

			pSound->StopSound(pSound->SOUND_LABEL_BGM_TUTORIAL);
			delete m_pSousa;
			m_pSousa = NULL;
		}
		break;

		// �`���[�g���A��
	case MODE_TUTORIAL:
		if (m_pTutorial != NULL)
		{
			m_pTutorial->Uninit();

			pSound->StopSound(pSound->SOUND_LABEL_BGM_TUTORIAL);
			delete m_pTutorial;
			m_pTutorial = NULL;
		}
		break;

		// �Q�[��
	case MODE_GAME:
		if (m_pGame != NULL)
		{
			m_pGame->Uninit();

			pSound->StopSound(pSound->SOUND_LABEL_BGM_GAME);
			delete m_pGame;
		}
		m_pGame = NULL;
		break;

		// ���U���g
	case MODE_RESULT:
		if (m_pResult != NULL)
		{
			m_pResult->Uninit();

			pSound->StopSound(pSound->SOUND_LABEL_BGM_RESULT);
			delete m_pResult;
		}
		m_pResult = NULL;
		break;

		// �Q�[���I�[�o�[
	case MODE_GAMEOVER:
		if (m_pGameover != NULL)
		{
			m_pGameover->Uninit();

			pSound->StopSound(pSound->SOUND_LABEL_BGM_GAMEOVER);
			delete m_pGameover;
		}
		m_pGameover = NULL;
		break;

		// �����L���O
	case MODE_RANKING:
		if (m_pRanking != NULL)
		{
			m_pRanking->Uninit();

			pSound->StopSound(pSound->SOUND_LABEL_BGM_RANKING);
			delete m_pRanking;
		}
		m_pRanking = NULL;
		break;
	}

	// ������
	switch (mode)
	{
		// �^�C�g��
	case MODE_TITLE:
		if (m_pTitle == NULL)
		{
			m_pTitle = CTitle::Create();

			pSound->PlaySound(pSound->SOUND_LABEL_BGM_TITLE);
		}
		break;

		// ������@
	case MODE_SOUSA:
		if (m_pSousa == NULL)
		{
			m_pSousa = CSousa::Create();

			pSound->PlaySound(pSound->SOUND_LABEL_BGM_TUTORIAL);
		}
		break;

		// �`���[�g���A��
	case MODE_TUTORIAL:
		if (m_pTutorial == NULL)
		{
			m_pTutorial = CTutorial::Create();

			pSound->PlaySound(pSound->SOUND_LABEL_BGM_TUTORIAL);
		}
		break;

		// �Q�[��
	case MODE_GAME:
		if (m_pGame == NULL)
		{
			m_pGame = CGame::Create();

			pSound->PlaySound(pSound->SOUND_LABEL_BGM_GAME);
		}
		break;

		// ���U���g
	case MODE_RESULT:
		if (m_pResult == NULL)
		{
			m_pResult = CResult::Create();

			pSound->PlaySound(pSound->SOUND_LABEL_BGM_RESULT);
		}
		break;

		// �Q�[���I�[�o�[
	case MODE_GAMEOVER:
		if (m_pGameover == NULL)
		{
			m_pGameover = CGameover::Create();

			pSound->PlaySound(pSound->SOUND_LABEL_BGM_GAMEOVER);
		}
		break;

		// �����L���O
	case MODE_RANKING:
		if (m_pRanking == NULL)
		{
			m_pRanking = CRanking::Create();

			pSound->PlaySound(pSound->SOUND_LABEL_BGM_RANKING);
		}
		break;
	}
	m_mode = mode;
}

//=============================================================================
// ���[�h�̎擾
//=============================================================================
CManager::MODE CManager::GetMode(void)
{
	return m_mode;
}

//=============================================================================
// �f�o�C�X�̎擾
//=============================================================================
 CRenderer *CManager::GetRenderer(void)
{
	return m_pRenderer;
}

 //=============================================================================
 // �L�[�{�[�h�擾
 //=============================================================================
 CInputKeyboard *CManager::GetInputKeyboard(void)
 {
	 return m_pInputKeyboard;
 }

 //=============================================================================
 // �p�b�h�擾
 //=============================================================================
 CInputjoypad *CManager::GetInputJoypad(void)
 {
	 return m_pInputJoypad;
 }

 //=============================================================================
 // �T�E���h�擾
 //=============================================================================
 CSound *CManager::GetSound(void)
 {
	 return m_pSound;
 }

 //=============================================================================
 // �t�F�[�h�̎擾
 //=============================================================================
 CFade *CManager::GetFade(void)
 {
	 return m_pFade;
 }

 //=============================================================================
 // �X�R�A�̎擾
 //=============================================================================
 CScore *CManager::GetScore(void)
 {
	 return m_pScore;
 }

 //=============================================================================
 // �`���[�g���A���̎擾
 //=============================================================================
 CTutorial * CManager::GetTutorial(void)
 {
	 return m_pTutorial;
 }

 //=============================================================================
 // ������@�̎擾
 //=============================================================================
 CSousa * CManager::GetSousa(void)
 {
	 return m_pSousa;
 }

 //=============================================================================
 // �Q�[���̎擾
 //=============================================================================
 CGame * CManager::GetGame(void)
 {
	 return m_pGame;
 }


 //=============================================================================
 // �����L���O�̕��ёւ�
 //=============================================================================
 void CManager::RankingScore(int nScore)
 {
	 int nData = 0;

	 for (int nCnt = 4; nCnt >= 0; nCnt--)
	 {
		 if ((m_Rankingscore[nCnt] <= nScore))
		 {
			 m_Rankingscore[nCnt] = nScore;
			 break;
		 }
	 }

	 for (int nCount = 0; nCount < MAX_RANKING - 1; nCount++)
	 {
		 for (int nCount2 = nCount + 1; nCount2 < MAX_RANKING; nCount2++)
		 {
			 if (m_Rankingscore[nCount] < m_Rankingscore[nCount2])
			 {
  				 nData = m_Rankingscore[nCount];
				 m_Rankingscore[nCount] = m_Rankingscore[nCount2];
				 m_Rankingscore[nCount2] = nData;
			 }

		 }

	 }
 }

 //=============================================================================
 // �X�R�A��n��
 //=============================================================================
 int CManager::GetRankingScore(int nIdx)
 {
	 return m_Rankingscore[nIdx];
 }

