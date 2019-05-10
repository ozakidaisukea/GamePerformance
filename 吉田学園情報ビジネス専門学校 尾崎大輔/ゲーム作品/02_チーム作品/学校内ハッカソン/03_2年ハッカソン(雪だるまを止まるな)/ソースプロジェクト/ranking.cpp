//=============================================================================
//
// �����L���O�̏��� [ranking.cpp]
// Author : Jukiya Hayakawa
//
//=============================================================================
#include "ranking.h"
#include "scene.h"
#include "scene2D.h"
#include "renderer.h"
#include "input.h"
#include "manager.h"
#include "debugproc.h"
#include "billboard.h"
#include "fade.h"
#include "number.h"
#include "rankingscore.h"
#include "UI.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================


//=============================================================================
// �����L���O�̃R���X�g���N�^
//=============================================================================
CRanking::CRanking()
{
	m_nTimer = 0;	//�^�C�}�[�̏�����
}

//=============================================================================
// �����L���O�̃f�X�g���N�^
//=============================================================================
CRanking::~CRanking()
{

}

//=============================================================================
// �����L���O�̃f�X�g���N�^
//=============================================================================
CRanking *CRanking::Create()
{
	CRanking *pRanking = NULL;	//�����L���O�̃|�C���^
	if (pRanking == NULL)
	{
		pRanking = new CRanking;	//���I�m��
		if (pRanking != NULL)
		{
			pRanking->Init();		//����������
		}
	}
	return pRanking;
}

//=============================================================================
// �����L���O�̏���������
//=============================================================================
HRESULT CRanking::Init(void)
{
	//	UI�̓ǂݍ���
	CUI::Load();
	//	UI�̐���
	CUI::CreateMode(CManager::MODE_RANKING);
	//�����̓ǂݍ���
	CNumber::Load();
	//�X�R�A�̐���
	CRankingScore::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 450, SCREEN_HEIGHT / 2 - 160, 0.0f), 50.0f, 60.0f);

	return S_OK;
}

//=============================================================================
// �����L���O�̏I������
//=============================================================================
void CRanking::Uninit(void)
{
	//	UI�̔j��
	CUI::Unload();
	//�����̔j��
	CNumber::Unload();

	//�S�ẴI�u�W�F�N�g�J��
	CScene::ReleaseAll();
}

//=============================================================================
// �����L���O�̍X�V����
//=============================================================================
void CRanking::Update(void)
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
	 //�^�C�g���֑J��
		pFade->SetFade(CManager::MODE_TITLE, pFade->FADE_OUT);
	}

	//�f�o�b�O�\��
#ifdef _DEBUG
	CDebugProc::Print(1, "Ranking");
#endif
}

//=============================================================================
// �����L���O�̕`�揈��
//=============================================================================
void CRanking::Draw(void)
{
}