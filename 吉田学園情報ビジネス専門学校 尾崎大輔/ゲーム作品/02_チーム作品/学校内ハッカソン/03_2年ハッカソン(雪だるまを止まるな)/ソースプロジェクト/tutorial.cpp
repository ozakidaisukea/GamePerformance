//=============================================================================
//
// �`���[�g���A���̏��� [tutorial.cpp]
// Author : Jukiya Hayakawa
//
//=============================================================================
#include "tutorial.h"
#include "scene.h"
#include "scene2D.h"
#include "renderer.h"
#include "input.h"
#include "manager.h"
#include "sound.h"
#include "debugproc.h"
#include "fade.h"
#include "meshfield.h"
#include "UI.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================


//=============================================================================
// �`���[�g���A���̃R���X�g���N�^
//=============================================================================
CTutorial::CTutorial()
{

}

//=============================================================================
// �`���[�g���A���̃f�X�g���N�^
//=============================================================================
CTutorial::~CTutorial()
{

}

//=============================================================================
// �`���[�g���A���̐���
//=============================================================================
CTutorial *CTutorial::Create()
{
	CTutorial *pTutorial = NULL;	//�`���[�g���A���̃|�C���^
	if (pTutorial == NULL)
	{
		pTutorial = new CTutorial;	//���I�m��
		if (pTutorial != NULL)
		{
			pTutorial->Init();		//����������
		}
	}
	return pTutorial;
}

//=============================================================================
// �`���[�g���A���̏���������
//=============================================================================
HRESULT CTutorial::Init(void)
{

	CUI::Load();
	CUI::CreateMode(CManager::MODE_TUTORIAL);

	CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), 15.0f, 15.0f);
	CMeshField::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	return S_OK;
}

//=============================================================================
// �`���[�g���A���̏I������
//=============================================================================
void CTutorial::Uninit(void)
{
	CUI::Unload();
	//�S�ẴI�u�W�F�N�g�J��
	CScene::ReleaseAll();
}

//=============================================================================
// �`���[�g���A���̍X�V����
//=============================================================================
void CTutorial::Update(void)
{
	//�L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetKeyboard();

	//�W���C�p�b�h�̎擾
	CInputJoypad *pInputJoypad;
	pInputJoypad = CManager::GetJoypad();

	//�t�F�[�h�̎擾
	CFade *pFade = CManager::GetFade();

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true ||
		pInputJoypad->GetTrigger(CInputJoypad::DIJS_BUTTON_A) == true)
	{//Enter�L�[�����������ꍇ
	 //�Q�[���֑J��
		pFade->SetFade(CManager::MODE_GAME, pFade->FADE_OUT);

	}

	//�f�o�b�O�\��
#ifdef _DEBUG
	CDebugProc::Print(1, "Tutorial");
#endif
}

//=============================================================================
// �`���[�g���A���̕`�揈��
//=============================================================================
void CTutorial::Draw(void)
{
}