//=============================================================================
//
// �^�C�g���̏��� [title.cpp]
// Author : Jukiya Hayakawa
//
//=============================================================================
#include "title.h"
#include "scene.h"
#include "scene2D.h"
#include "renderer.h"
#include "input.h"
#include "manager.h"
#include "debugproc.h"
#include "meshfield.h"
#include "fade.h"
#include "UI.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================


//=============================================================================
// �^�C�g���̃R���X�g���N�^
//=============================================================================
CTitle::CTitle()
{
}

//=============================================================================
// �^�C�g���̃f�X�g���N�^
//=============================================================================
CTitle::~CTitle()
{

}

//=============================================================================
// �^�C�g���̃f�X�g���N�^
//=============================================================================
CTitle *CTitle::Create()
{
	CTitle *pTitle = NULL;	//�^�C�g���̃|�C���^

	if (pTitle == NULL)
	{
		pTitle = new CTitle;	//���I�m��
		if (pTitle != NULL)
		{
			pTitle->Init();		//����������
		}
	}
	return pTitle;
}

//=============================================================================
// �^�C�g���̏���������
//=============================================================================
HRESULT CTitle::Init(void)
{

	CUI::Load();
	CUI::CreateMode(CManager::MODE_TITLE);


	//CMeshField::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	return S_OK;
}

//=============================================================================
// �^�C�g���̏I������
//=============================================================================
void CTitle::Uninit(void)
{

	CUI::Unload();
	//�S�ẴI�u�W�F�N�g�J��
	CScene::ReleaseAll();
}

//=============================================================================
// �^�C�g���̍X�V����
//=============================================================================
void CTitle::Update(void)
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
		//�`���[�g���A���֑J��
		pFade->SetFade(CManager::MODE_TUTORIAL, pFade->FADE_OUT);

	}

	//�f�o�b�O�\��
#ifdef _DEBUG
	CDebugProc::Print(1, "Title");
#endif
}

//=============================================================================
// �^�C�g���̕`�揈��
//=============================================================================
void CTitle::Draw(void)
{

}