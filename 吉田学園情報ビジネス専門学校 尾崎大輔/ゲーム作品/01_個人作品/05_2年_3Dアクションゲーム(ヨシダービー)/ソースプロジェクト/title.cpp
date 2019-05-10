//=============================================================================
//
// �^�C�g������ [title.cpp]
// Author : Ozaki
//
//=============================================================================
#include "title.h"
#include "manager.h"
#include "renderer.h"
#include "sound.h"
#include "pressentor.h"
#include "fade.h"
#include "input.h"
#include "camera.h"
#include "light.h"
#include "debugproc.h"
#include "meshfield.h"
#include "union.h"
#include "scene2D.h"
#include "logo.h"
#include "player.h"			// �v���C���[
#include "jockey.h"			// �W���b�L�[
#include "horse2.h"			// �n�Q
#include "horse3.h"
#include "horse4.h"
#include "horse5.h"
#include "horse6.h"
#include "horse7.h"
#include "horse8.h"
#include "horse9.h"
#include "horse10.h"
#include "jockey2.h"
#include "jockey3.h"
#include "jockey4.h"
#include "jockey5.h"
#include "jockey6.h"
#include "jockey7.h"
#include "jockey8.h"
#include "jockey9.h"
#include "jockey10.h"
#include "pressentor.h"
#include "joypad.h"

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9	CTitle::m_pTexture = NULL;
LPDIRECT3DVERTEXBUFFER9 CTitle::m_pVtxBuff = NULL;
CSound*CTitle::m_pSound = NULL;
CCamera*CTitle::m_pCamera = NULL;
CLight*CTitle::m_pLight = NULL;
CMeshFiled*CTitle::m_pMeshFiled = NULL;
CLogo*CTitle::m_pLogo = NULL;
CPressEntor*CTitle::m_pPressEntor = NULL;

CPlayer*CTitle::m_pPlayer = NULL;
CHorse2*CTitle::m_pHorse2 = NULL;
CHorse3*CTitle::m_pHorse3 = NULL;
CHorse4*CTitle::m_pHorse4 = NULL;
CHorse5*CTitle::m_pHorse5 = NULL;
CHorse6*CTitle::m_pHorse6 = NULL;
CHorse7*CTitle::m_pHorse7 = NULL;
CHorse8*CTitle::m_pHorse8 = NULL;
CHorse9*CTitle::m_pHorse9 = NULL;
CHorse10*CTitle::m_pHorse10 = NULL;
CJockey*CTitle::m_pJockey = NULL;
CJockey2*CTitle::m_pJockey2 = NULL;
CJockey3*CTitle::m_pJockey3 = NULL;
CJockey4*CTitle::m_pJockey4 = NULL;
CJockey5*CTitle::m_pJockey5 = NULL;
CJockey6*CTitle::m_pJockey6 = NULL;
CJockey7*CTitle::m_pJockey7 = NULL;
CJockey8*CTitle::m_pJockey8 = NULL;
CJockey9*CTitle::m_pJockey9 = NULL;
CJockey10*CTitle::m_pJockey10 = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTitle::CTitle()
{
	// �����L���O�ɐ؂�ւ���^�C�}�[
	m_Titletimer = 0;
	m_pLogo = NULL;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTitle::~CTitle()
{

}

//=============================================================================
// ���[�h
//=============================================================================
void CTitle::Load(void)
{
	CRenderer *pRenderer;

	pRenderer = new CRenderer;

	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = NULL;

	pDevice = CManager::GetRenderer()->GetDevice();
}

//=============================================================================
// �A�����[�h
//=============================================================================
void CTitle::Unload(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();

		m_pTexture = NULL;
	}
}

//=============================================================================
// ����������
//=============================================================================
void CTitle::Init(void)
{
	m_pCamera = new CCamera;
	m_pLight = new CLight;

	// �J�������擾
	m_pCamera->SetMode(CCamera::MODE_TITLE);

	//============================================================================================================================
	// �ǂݍ��ݗ�
	//============================================================================================================================

	// �J�����̏�����
	m_pCamera->Init();

	// ���C�g�̏�����
	m_pLight->Init();

	CUnion::Load();

	// ���S�̏�����
	CLogo::Load();

	// �n�̓ǂݍ���
	CHorse2::Load();
	// �n�̓ǂݍ���
	CHorse3::Load();
	// �n�̓ǂݍ���
	CHorse4::Load();
	// �n�̓ǂݍ���
	CHorse5::Load();
	// �n�̓ǂݍ���
	CHorse6::Load();
	// �n�̓ǂݍ���
	CHorse7::Load();
	// �n�̓ǂݍ���
	CHorse8::Load();
	// �n�̓ǂݍ���
	CHorse9::Load();
	// �n�̓ǂݍ���
	CHorse10::Load();
	// �v���C���[��ǂݍ���
	CPlayer::Load();

	// �W���b�L�[�̓ǂݍ���
	CJockey::Load();
	// �W���b�L�[�̓ǂݍ���
	CJockey2::Load();
	// �W���b�L�[�̓ǂݍ���
	CJockey3::Load();
	// �W���b�L�[�̓ǂݍ���
	CJockey4::Load();
	// �W���b�L�[�̓ǂݍ���
	CJockey5::Load();
	// �W���b�L�[�̓ǂݍ���
	CJockey6::Load();
	// �W���b�L�[�̓ǂݍ���
	CJockey7::Load();
	// �W���b�L�[�̓ǂݍ���
	CJockey8::Load();
	// �W���b�L�[�̓ǂݍ���
	CJockey9::Load();
	// �W���b�L�[�̓ǂݍ���
	CJockey10::Load();

	// �v���X�G���^�[�̓ǂݍ���
	CPressEntor::Load();

	//============================================================================================================================
	// ������
	//============================================================================================================================

	//============================================================================================================================
	// �E�ړ�
	//============================================================================================================================
	// �v���C���[�̐���
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(100, 0, 0), D3DXVECTOR3(0, D3DX_PI / 2, 0), CPlayer::JOCKEYTYPE_TITLE);
	// �W���b�L�[�̐���
	m_pJockey = CJockey::Create(D3DXVECTOR3(100, 20, 0), D3DXVECTOR3(0, D3DX_PI / 2, 0), CJockey::JOCKEYTYPE_TITLE);

	// �n2�̐���
	m_pHorse2 = CHorse2::Create(D3DXVECTOR3(100, 0, 50), D3DXVECTOR3(0, D3DX_PI / 2, 0), CHorse2::JOCKEYTYPE_TITLE);
	// �W���b�L�[�Q�̐���
	m_pJockey2 = CJockey2::Create(D3DXVECTOR3(100, 20, 50), D3DXVECTOR3(0, D3DX_PI / 2, 0), CJockey2::JOCKEYTYPE_TITLE);

	//===============================================================================================================
	// ���ړ�
	//===============================================================================================================
	// �n3�̐���
	m_pHorse3 = CHorse3::Create(D3DXVECTOR3(-100, 0, 25), D3DXVECTOR3(0,11, 0), CHorse3::JOCKEYTYPE_TITLE);
	// �W���b�L�[3�̐���
	m_pJockey3 = CJockey3::Create(D3DXVECTOR3(-100, 20, 25), D3DXVECTOR3(0, 11, 0), CJockey3::JOCKEYTYPE_TITLE);

	// �n4�̐���
	m_pHorse4 = CHorse4::Create(D3DXVECTOR3(-100, 0, 75), D3DXVECTOR3(0, 11, 0), CHorse4::JOCKEYTYPE_TITLE);
	// �W���b�L�[4�̐���
	m_pJockey4 = CJockey4::Create(D3DXVECTOR3(-100, 20, 75), D3DXVECTOR3(0, 11, 0), CJockey4::JOCKEYTYPE_TITLE);

	//===============================================================================================================
	// �O���ړ�
	//===============================================================================================================
	// �n5�̐���
	m_pHorse5 = CHorse5::Create(D3DXVECTOR3(-20, 0, -200), D3DXVECTOR3(0, D3DX_PI, 0), CHorse5::JOCKEYTYPE_TITLE);
	// �W���b�L�[5�̐���
	m_pJockey5 = CJockey5::Create(D3DXVECTOR3(-20, 20, -200), D3DXVECTOR3(0, D3DX_PI, 0), CJockey5::JOCKEYTYPE_TITLE);

	// �n6�̐���
	m_pHorse6 = CHorse6::Create(D3DXVECTOR3(20, 0, -200), D3DXVECTOR3(0, D3DX_PI, 0), CHorse6::JOCKEYTYPE_TITLE);
	// �W���b�L�[6�̐���
	m_pJockey6 = CJockey6::Create(D3DXVECTOR3(20, 20, -200), D3DXVECTOR3(0, D3DX_PI, 0), CJockey6::JOCKEYTYPE_TITLE);

	//===============================================================================================================
	// ����ړ�
	//===============================================================================================================
	// �n7�̐���
	m_pHorse7 = CHorse7::Create(D3DXVECTOR3(0, 0, 200), D3DXVECTOR3(0, 0, 0), CHorse7::JOCKEYTYPE_TITLE);
	// �W���b�L�[7�̐���
	m_pJockey7 = CJockey7::Create(D3DXVECTOR3(0, 20, 200), D3DXVECTOR3(0, 0, 0), CJockey7::JOCKEYTYPE_TITLE);

	// �n8�̐���
	m_pHorse8 = CHorse8::Create(D3DXVECTOR3(45, 0, 200), D3DXVECTOR3(0, 0, 0), CHorse8::JOCKEYTYPE_TITLE);
	// �W���b�L�[8�̐���
	m_pJockey8 = CJockey8::Create(D3DXVECTOR3(45, 20, 200), D3DXVECTOR3(0, 0, 0), CJockey8::JOCKEYTYPE_TITLE);

	//===============================================================================================================
	// �ォ��
	//===============================================================================================================
	// �n9�̐���
	m_pHorse9 = CHorse9::Create(D3DXVECTOR3(-20, 300, 0), D3DXVECTOR3(0, 0, 0), CHorse9::JOCKEYTYPE_TITLE);
	// �W���b�L�[9�̐���
	m_pJockey9 = CJockey9::Create(D3DXVECTOR3(-20, 320, 0), D3DXVECTOR3(0, 0, 0), CJockey9::JOCKEYTYPE_TITLE);

	// �n10�̐���
	m_pHorse10 = CHorse10::Create(D3DXVECTOR3(20, 300, 0), D3DXVECTOR3(0, 0, 0), CHorse10::JOCKEYTYPE_TITLE);
	// �W���b�L�[10�̐���
	m_pJockey10 = CJockey10::Create(D3DXVECTOR3(20, 320, 0), D3DXVECTOR3(0, 0, 0), CJockey10::JOCKEYTYPE_TITLE);

	// ���b�V���t�B�[���h�̐���
	//m_pMeshFiled = CMeshFiled::Create(D3DXVECTOR3(0.0f, 0.0f, 1700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), X_SIZE, Z_SIZE, mPolygonX, mPolygonZ);

	// ���S�̐���
	CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, -500, 0.0f), 600.0f, 200.0f, CLogo::LOGO_TITLE);

	// �v���X�G���^�[�̐���
	//m_pPressEntor = CPressEntor::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 200, 0), 200.0f, 70.0f);
	// �v���X�G���^�[�̐���
	CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 200, 0), 200.0f, 70.0f, CLogo::LOGO_PRESSENTOR);
}

//=============================================================================
// �I������
//=============================================================================
void CTitle::Uninit(void)
{
	// �e�N�X�`���̉��
	CLogo::Unload();
	CUnion::Unload();
	CHorse2::Unload();
	CHorse3::Unload();
	CHorse4::Unload();
	CHorse5::Unload();
	CHorse6::Unload();
	CHorse7::Unload();
	CHorse8::Unload();
	CHorse9::Unload();
	CHorse10::Unload();
	CPlayer::Unload();
	CJockey::Unload();
	CJockey2::Unload();
	CJockey3::Unload();
	CJockey4::Unload();
	CJockey5::Unload();
	CJockey6::Unload();
	CJockey7::Unload();
	CJockey8::Unload();
	CJockey9::Unload();
	CJockey10::Unload();

	// �v���X�G���^�[�̓ǂݍ���
	CPressEntor::Load();

	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();

		m_pTexture = NULL;
	}

	// �J������j��
	if (m_pCamera != NULL)
	{
		m_pCamera->Uninit();			// �J����������

		delete m_pCamera;
		m_pCamera = NULL;
	}

	// ���C�g��j��
	if (m_pLight != NULL)
	{
		m_pLight->Uninit();				// ���C�g������

		delete m_pLight;
		m_pLight = NULL;
	}

	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	CScene::ReleaseAll();
}

//=============================================================================
// �X�V����
//=============================================================================
void CTitle::Update(void)
{
	// �L�[�{�[�h���擾
	CInputKeyboard *InputKeyboard;
	InputKeyboard = CManager::GetInputKeyboard();

	// �p�b�h���擾
	CInputjoypad *InputJoypad;
	InputJoypad = CManager::GetInputJoypad();

	// �T�E���h���擾
	CSound *pSound;
	pSound = CManager::GetSound();

	m_pSound = pSound;

	// �f�o�b�N���擾
	CDebugProc *m_Dubug = CRenderer::GetDebug();

#ifdef _DEBUG
	m_Dubug->Print("s", "Title");

#endif // DEBUG


	m_Titletimer++;

	// �t�F�[�h���擾
	CFade *pFade;
	pFade = CManager::GetFade();

	if (pFade->GetFade() == CFade::FADE_NONE)
	{
		if (InputKeyboard->GetTrigger(DIK_RETURN) == true || InputJoypad->GetPress(CInputjoypad::DIJS_BOTTON_B) == true)
		{
			pFade->SetFade(CManager::MODE_TUTORIAL);
			pSound->PlaySound(pSound->SOUND_LABEL_SE_DECISON1);
		}
	}

	if (m_Titletimer == 2400)
	{
		pFade->SetFade(CManager::MODE_TITLE);
	}

	// NULL�`�F�b�N
	if (m_pCamera != NULL)
	{
		m_pCamera->Update();			// �J�������X�V
	}

	// NULL�`�F�b�N
	if (m_pLight != NULL)
	{
		m_pLight->Update();				// ���C�g���X�V
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CTitle::Draw(void)
{
	 //NULL�`�F�b�N
	if (m_pCamera != NULL)
	{
		m_pCamera->SetCamera();			// �J�����̐ݒ�
	}
}

//=============================================================================
// �^�C�g���̐���
//=============================================================================
CTitle*CTitle::Create(void)
{
	CTitle *pTitle;

	pTitle = new CTitle;

	pTitle->Init();

	return pTitle;
}

//=============================================================================
// �J�����̎擾
//=============================================================================
CCamera * CTitle::GetCamera(void)
{
	return m_pCamera;
}

//=============================================================================
// ���C�g�̎擾
//=============================================================================
CLight * CTitle::GetLight(void)
{
	return m_pLight;
}

//=============================================================================
// ���b�V���t�B�[���h�̎擾
//=============================================================================
CMeshFiled * CTitle::GetMeshFiled(void)
{
	return m_pMeshFiled;
}

//=============================================================================
// ���S�̎擾
//=============================================================================
CLogo * CTitle::GetLogo(void)
{
	return m_pLogo;
}

//=============================================================================
// �n�̎擾
//=============================================================================
CPlayer * CTitle::GetPlayer(void)
{
	return m_pPlayer;
}
//=============================================================================
// �n2�̎擾
//=============================================================================
CHorse2 * CTitle::GetHorse2(void)
{
	return m_pHorse2;
}
//=============================================================================
// �n3�̎擾
//=============================================================================
CHorse3 * CTitle::GetHorse3(void)
{
	return m_pHorse3;
}
//=============================================================================
// �n4�̎擾
//=============================================================================
CHorse4 * CTitle::GetHorse4(void)
{
	return m_pHorse4;
}
//=============================================================================
// �n5�̎擾
//=============================================================================
CHorse5 * CTitle::GetHorse5(void)
{
	return m_pHorse5;
}
//=============================================================================
// �n6�̎擾
//=============================================================================
CHorse6 * CTitle::GetHorse6(void)
{
	return m_pHorse6;
}
//=============================================================================
// �n7�̎擾
//=============================================================================
CHorse7 * CTitle::GetHorse7(void)
{
	return m_pHorse7;
}
//=============================================================================
// �n8�̎擾
//=============================================================================
CHorse8 * CTitle::GetHorse8(void)
{
	return m_pHorse8;
}
//=============================================================================
// �n9�̎擾
//=============================================================================
CHorse9 * CTitle::GetHorse9(void)
{
	return m_pHorse9;
}
//=============================================================================
// �n10�̎擾
//=============================================================================
CHorse10 * CTitle::GetHorse10(void)
{
	return m_pHorse10;
}

//=============================================================================
// �W���b�L�[1�̎擾
//=============================================================================
CJockey * CTitle::GetJockey(void)
{
	return m_pJockey;
}
//=============================================================================
// �W���b�L�[2�̎擾
//=============================================================================
CJockey2 * CTitle::GetJockey2(void)
{
	return m_pJockey2;
}
//=============================================================================
// �W���b�L�[3�̎擾
//=============================================================================
CJockey3 * CTitle::GetJockey3(void)
{
	return m_pJockey3;
}
//=============================================================================
// �W���b�L�[4�̎擾
//=============================================================================
CJockey4 * CTitle::GetJockey4(void)
{
	return m_pJockey4;
}
//=============================================================================
// �W���b�L�[5�̎擾
//=============================================================================
CJockey5 * CTitle::GetJockey5(void)
{
	return m_pJockey5;
}
//=============================================================================
// �W���b�L�[6�̎擾
//=============================================================================
CJockey6 * CTitle::GetJockey6(void)
{
	return m_pJockey6;
}
//=============================================================================
// �W���b�L�[7�̎擾
//=============================================================================
CJockey7 * CTitle::GetJocke7(void)
{
	return m_pJockey7;
}

//=============================================================================
// �W���b�L�[8�̎擾
//=============================================================================
CJockey8 * CTitle::GetJocke8(void)
{
	return m_pJockey8;
}
//=============================================================================
// �W���b�L�[9�̎擾
//=============================================================================
CJockey9 * CTitle::GetJockey9(void)
{
	return m_pJockey9;
}
//=============================================================================
// �W���b�L�[10�̎擾
//=============================================================================
CJockey10 * CTitle::GetJockey10(void)
{
	return m_pJockey10;
}
//=============================================================================
// �W���b�L�[10�̎擾
//=============================================================================
CPressEntor * CTitle::GetEntor(void)
{
	return m_pPressEntor;
}