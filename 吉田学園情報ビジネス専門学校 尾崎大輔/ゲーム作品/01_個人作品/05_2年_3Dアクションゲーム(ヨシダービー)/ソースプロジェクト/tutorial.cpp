//=============================================================================
//
// �`���[�g���A������ [tutorial.cpp]
// Author : Ozaki
//
//=============================================================================
#include "tutorial.h"
#include "manager.h"
#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "scene2D.h"
#include "input.h"
#include "player.h"
#include "sound.h"
#include "title.h"
#include "fade.h"
#include "logo.h"
#include "debugproc.h"
#include "joypad.h"

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
CPlayer*CTutorial::m_pPlayer = NULL;
CLogo*CTutorial::m_pLogo = NULL;

LPDIRECT3DTEXTURE9	CTutorial::m_pTexture = NULL;
LPDIRECT3DVERTEXBUFFER9 CTutorial::m_pVtxBuff = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTutorial::CTutorial()
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTutorial::~CTutorial()
{

}

//=============================================================================
// ���[�h
//=============================================================================
HRESULT CTutorial::Load(void)
{
	return S_OK;
}

//=============================================================================
// �A�����[�h
//=============================================================================
void CTutorial::Unload(void)
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CTutorial::Init(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = NULL;

	pDevice = CManager::GetRenderer()->GetDevice();

	m_nCounterTutorialState = 0;


	//================================
	// �ǂݍ��ݗ�
	//================================
	CLogo::Load();

	//================================
	// ������
	//================================
	CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 350, 0), 900, 500, CLogo::LOGO_TUTORIAL);
	CLogo::Create(D3DXVECTOR3(1950, 350, 0), 900, 500, CLogo::LOGO_RESECARD);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CTutorial::Uninit(void)
{
	CScene::ReleaseAll();
}

//=============================================================================
// �X�V����
//=============================================================================
void CTutorial::Update(void)
{
	// �T�E���h���擾
	CSound *pSound;
	pSound = CManager::GetSound();

	// �L�[�{�[�h���擾
	CInputKeyboard *InputKeyboard;
	InputKeyboard = CManager::GetInputKeyboard();

	// �p�b�h���擾
	CInputjoypad *InputJoypad;
	InputJoypad = CManager::GetInputJoypad();

	// �t�F�[�h���擾
	CFade *pFade;
	pFade = CManager::GetFade();

	// �f�o�b�N���擾
	CDebugProc *m_Dubug = CRenderer::GetDebug();
#ifdef _DEBUG
	m_Dubug->Print("s", "Tutorial");
#endif // _DEBUG


	if (pFade->GetFade() == CFade::FADE_NONE)
	{
		if (InputKeyboard->GetTrigger(DIK_RETURN) == true || InputJoypad->GetPress(CInputjoypad::DIJS_BOTTON_B) == true)
		{
			pFade->SetFade(CManager::MODE_GAME);
			pSound->PlaySound(pSound->SOUND_LABEL_SE_DECISON2);
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CTutorial::Draw(void)
{

}

//=============================================================================
// �`���[�g���A���̐���
//=============================================================================
CTutorial*CTutorial::Create(void)
{
	CTutorial *pTutorial;

	pTutorial = new CTutorial;

	pTutorial->Init();

	return pTutorial;
}

//=============================================================================
// �v���C���[�̎擾
//=============================================================================
CPlayer *CTutorial::GetPlayer(void)
{
	return m_pPlayer;
}

//=============================================================================
// ���S�̎擾
//=============================================================================
CLogo *CTutorial::GetLogo(void)
{
	return m_pLogo;
}