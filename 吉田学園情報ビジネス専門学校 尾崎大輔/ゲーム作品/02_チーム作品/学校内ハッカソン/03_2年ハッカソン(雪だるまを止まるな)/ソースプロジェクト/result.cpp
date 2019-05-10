//=============================================================================
//
// ���U���g���� [manager.cpp]
// Author : Jukiya Hayakawa
//
//=============================================================================
#include "result.h"
#include "scene.h"
#include "scene2D.h"
#include "renderer.h"
#include "input.h"
#include "manager.h"
#include "debugproc.h"
#include "player.h"
#include "fade.h"
#include "UI.h"
#include "particle2D.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
CResult::RESULT CResult::m_result = RESULT_NONE;		//���U���g�̃|�C���^

//=============================================================================
// ���U���g�̃R���X�g���N�^
//=============================================================================
CResult::CResult()
{
	m_nTimer = 0;	//�^�C�}�[�̏����l
}

//=============================================================================
// ���U���g�̃f�X�g���N�^
//=============================================================================
CResult::~CResult()
{

}

//=============================================================================
// ���U���g�̃f�X�g���N�^
//=============================================================================
CResult *CResult::Create()
{
	CResult *pResult = NULL;	//���U���g�̃|�C���^
	if (pResult == NULL)
	{
		pResult = new CResult;	//���I�m��
		if (pResult != NULL)
		{
			pResult->Init();	//����������
		}
	}
	return pResult;
}

//=============================================================================
// ���U���g�̏���������
//=============================================================================
HRESULT CResult::Init(void)
{
	m_nTimer = 0;	//�^�C�}�[�̏���������

	CParticle2D::Load();

	CUI::Load();
	CUI::CreateMode(CManager::MODE_RESULT);

	//CPlayer::Create(D3DXVECTOR3( 0.0f, 0.0f, 0.0f));
	return S_OK;
}

//=============================================================================
// ���U���g�̏I������
//=============================================================================
void CResult::Uninit(void)
{
	CParticle2D::Unload();
	CUI::Unload();
	//�S�ẴI�u�W�F�N�g�J��
	CScene::ReleaseAll();
}

//=============================================================================
// ���U���g�̍X�V����
//=============================================================================
void CResult::Update(void)
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
	 //�����L���O�֑J��
		pFade->SetFade(CManager::MODE_RANKING, pFade->FADE_OUT);
	}

	//�f�o�b�O�\��
#ifdef _DEBUG
	CDebugProc::Print(1, "Result");

#endif
}

//=============================================================================
// ���U���g�̕`�揈��
//=============================================================================
void CResult::Draw(void)
{
}

//=============================================================================
// ���U���g�̐ݒu����
//=============================================================================
void CResult::SetResult(RESULT result)
{
	m_result = result;
}
//=============================================================================
// ���U���g�̎擾����
//=============================================================================
CResult::RESULT CResult::GetResult(void)
{
	return m_result;
}