//=============================================================================
//
// �}�l�[�W���[�̏��� [manager.cpp]
// Author : Ozaki
//
//=============================================================================
#include "manager.h"
#include "main.h"
#include "renderer.h"
#include "input.h"
#include "scene.h"
#include "scene2D.h"
#include "scene3D.h"
#include "sceneX.h"
#include "sound.h"
#include "meshfield.h"
#include "camera.h"
#include "light.h"
#include "debugproc.h"
#include "billboard.h"
#include "player.h"
#include "meshorbit.h"
#include "fade.h"
#include "title.h"
#include "game.h"
#include "tutorial.h"
#include "result.h"
#include "joypad.h"

//=============================================================================
// �ÓI�����o-�ϐ��錾
//=============================================================================
CRenderer*CManager::m_pRenderer = NULL;
CInputKeyboard*CManager::m_pInputKeyboard = NULL;
CLight*CManager::m_pLight = NULL;
CScene3D*CManager::m_pScene3D = NULL;
CPlayer*CManager::m_pPlayer = NULL;
CMeshFiled*CManager::m_pMeshField = NULL;
CMeshOrbit*CManager::m_pMeshOrbit = NULL;
CSound*CManager::m_pSound = NULL;
CFade*CManager::m_pFade = NULL;
CTitle*CManager::m_pTitle = NULL;
CTutorial*CManager::m_pTutorial = NULL;
CGame*CManager::m_pGame = NULL;
CResult*CManager::m_pResult = NULL;
CRanking*CManager::m_pRanking = NULL;
CInputjoypad*CManager::m_pInputJoypad = NULL;
int	CManager::m_playertaime = NULL;
CCamera*CManager::m_pCamera = NULL;									  // �J����

CManager::MODE CManager::m_mode = CManager::MODE_TITLE;		   		  // ���[�h

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

	// ����������
	if (FAILED(m_pInputKeyboard->Init(hInstance, hWnd)))
	{
		return -1;
	}
	if (m_pInputJoypad != NULL)
	{
		m_pInputJoypad->Init(hInstance, hWnd);
	}

	// �f�o�b�N���擾
	CDebugProc *m_Dubug = CRenderer::GetDebug();

#ifdef DEBUG
	m_Dubug->Print("sss", " 1��Scene2D�폜\n", " 2��Scene3D�폜\n", " 3��SceneX���폜\n");

#endif // DEBUG

	m_pSound->InitSound(hWnd);

	// �t�F�[�h����
	m_pFade = CFade::Create();

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

	// �T�E���h
	if (m_pSound != NULL)
	{
		m_pSound->UninitSound();		// ��

		delete m_pSound;
		m_pSound = NULL;
	}

	// �L�[�{�[�h��j��
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Uninit();		// �L�[�{�[�h������

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

	// �t�F�[�h�̔j��
	if (m_pFade != NULL)
	{
		m_pFade->Uninit();

		delete m_pFade;
		m_pFade = NULL;
	}

	// �^�C�g��
	if (m_pTitle != NULL)
	{
		m_pTitle->Uninit();

		delete m_pTitle;
		m_pTitle = NULL;
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

	// NULL�`�F�b�N
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Uninit();			// �����_���[������

		delete m_pRenderer;
		m_pRenderer = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void CManager::Update(void)
{
#ifdef _DEBUG
	// �����������
	CDebugProc::ResetStr();

	// �f�o�b�N���擾
	CDebugProc *m_Dubug = CRenderer::GetDebug();

	m_playertaime++;

#endif

	// NULL�`�F�b�N
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Update();		// �L�[�{�[�h���X�V
	}

	// �p�b�h�̍X�V
	if (m_pInputJoypad != NULL)
	{
		m_pInputJoypad->Update();		// �p�b�h���X�V
	}

	// NULL�`�F�b�N
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Update();			// �����_���[���X�V
	}

	// NULL�`�F�b�N
	if (m_pFade != NULL)
	{
		m_pFade->Update();				// �t�F�[�h���X�V
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
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CManager::Draw(void)
{
	// NULL�`�F�b�N
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Draw();			// �����_���[�̕`��
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
			m_pGame = NULL;
		}
		break;

		// ���U���g
	case MODE_RESULT:
		if (m_pResult != NULL)
		{
			m_pResult->Uninit();

			pSound->StopSound(pSound->SOUND_LABEL_BGM_RESULT);
			delete m_pResult;
			m_pResult = NULL;
		}
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
			//CGame::Create();
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
// �T�E���h�̎擾
//=============================================================================
CSound * CManager::GetSound(void)
{
	return m_pSound;
}

//=============================================================================
// �f�o�C�X�̎擾
//=============================================================================
 CRenderer *CManager::GetRenderer(void)
{
	return m_pRenderer;					// �����_���[��Ԃ�
}
 //=============================================================================
 // �L�[�{�[�h�̎擾
 //=============================================================================
 CInputKeyboard *CManager::GetInputKeyboard(void)
 {
	 return m_pInputKeyboard;			// �L�[�{�[�h��Ԃ�
 }

 //=============================================================================
 // �^�C�g���̎擾
 //=============================================================================
 CTitle * CManager::GetTitle(void)
 {
	 return m_pTitle;
 }

 //=============================================================================
 // �`���[�g���A���̎擾
 //=============================================================================
 CTutorial * CManager::GetTutorial(void)
 {
	 return m_pTutorial;
 }

 //=============================================================================
 // �Q�[���̎擾
 //=============================================================================
 CGame * CManager::GetGame(void)
 {
	 return m_pGame;
 }

 //=============================================================================
 // ���U���g�̎擾
 //=============================================================================
 CResult * CManager::GetResult(void)
 {
	 return m_pResult;
 }
 //=============================================================================
 // SCcene3D�̎擾
 //=============================================================================
 CScene3D * CManager::GetScene3D(void)
 {
	 return m_pScene3D;					// �V�[��3D��Ԃ�
 }

 //=============================================================================
 // �v���C���[�̎擾
 //=============================================================================
 CPlayer * CManager::GetPlayer(void)
 {
	 return m_pPlayer;					// �v���C���[��Ԃ�
 }

 //=============================================================================
 // �t�F�[�h�̎擾
 //=============================================================================
 CFade * CManager::GetFade(void)
 {
	 return m_pFade;
 }

 //=============================================================================
 // ���b�V���t�B�[���h�̎擾
 //=============================================================================
 CMeshFiled * CManager::GetMeshField(void)
 {
	 return m_pMeshField;				// ���b�V���t�B�[���h��Ԃ�
 }

 //=============================================================================
 // ���b�V���I�[�r�b�g�̎擾
 //=============================================================================
 CMeshOrbit * CManager::GetMeshOrbit(void)
 {
	 return m_pMeshOrbit;
 }

 //=============================================================================
 // �W���C�p�b�h�̎擾
 //=============================================================================
 CInputjoypad * CManager::GetInputJoypad(void)
 {
	 return m_pInputJoypad;
 }

 //=============================================================================
 // ���C�g�̎擾
 //=============================================================================
 CLight * CManager::GetLight(void)
 {
	 return m_pLight;
 }

