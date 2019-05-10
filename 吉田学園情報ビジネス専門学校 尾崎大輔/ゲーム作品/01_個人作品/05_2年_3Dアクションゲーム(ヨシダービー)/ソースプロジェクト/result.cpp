//=============================================================================
//
// �^�C�g������ [title.cpp]
// Author : Ozaki
//
//=============================================================================
#include "result.h"
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
#include "union.h"
#include "joypad.h"

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9	CResult::m_pTexture = NULL;
LPDIRECT3DVERTEXBUFFER9 CResult::m_pVtxBuff = NULL;
CSound*CResult::m_pSound = NULL;
CCamera*CResult::m_pCamera = NULL;
CLight*CResult::m_pLight = NULL;
CMeshFiled*CResult::m_pMeshFiled = NULL;
CLogo*CResult::m_pLogo = NULL;

CPlayer*CResult::m_pPlayer = NULL;
CHorse2*CResult::m_pHorse2 = NULL;
CHorse3*CResult::m_pHorse3 = NULL;
CHorse4*CResult::m_pHorse4 = NULL;
CHorse5*CResult::m_pHorse5 = NULL;
CHorse6*CResult::m_pHorse6 = NULL;
CHorse7*CResult::m_pHorse7 = NULL;
CHorse8*CResult::m_pHorse8 = NULL;
CHorse9*CResult::m_pHorse9 = NULL;
CHorse10*CResult::m_pHorse10 = NULL;
CJockey*CResult::m_pJockey = NULL;
CJockey2*CResult::m_pJockey2 = NULL;
CJockey3*CResult::m_pJockey3 = NULL;
CJockey4*CResult::m_pJockey4 = NULL;
CJockey5*CResult::m_pJockey5 = NULL;
CJockey6*CResult::m_pJockey6 = NULL;
CJockey7*CResult::m_pJockey7 = NULL;
CJockey8*CResult::m_pJockey8 = NULL;
CJockey9*CResult::m_pJockey9 = NULL;
CJockey10*CResult::m_pJockey10 = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CResult::CResult()
{
	// �����L���O�ɐ؂�ւ���^�C�}�[
	m_Titletimer = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CResult::~CResult()
{

}

//=============================================================================
// ���[�h
//=============================================================================
void CResult::Load(void)
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
void CResult::Unload(void)
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
void CResult::Init(void)
{
	m_pCamera = new CCamera;
	m_pLight = new CLight;

	//============================================================================================================================
	// �ǂݍ��ݗ�
	//============================================================================================================================

	// �J�����̏�����
	m_pCamera->Init();

	// �J�������擾
	m_pCamera->SetMode(CCamera::MODE_RESULT);

	// ���C�g�̏�����
	m_pLight->Init();

	CUnion::Load();

	// ���S�̏�����
	m_pLogo->Load();

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
	//CPressEntor::Load();

	//============================================================================================================================
	// �E
	//============================================================================================================================
	// �n9�̐���
	m_pHorse9 = CHorse9::Create(D3DXVECTOR3(100, 0, -150), D3DXVECTOR3(0, D3DX_PI / 2, 0), CHorse9::JOCKEYTYPE_RESULT);

	// �n2�̐���
	m_pHorse2 = CHorse2::Create(D3DXVECTOR3(100, 0, -100), D3DXVECTOR3(0, D3DX_PI / 2, 0), CHorse2::JOCKEYTYPE_RESULT);

	// �n3�̐���
	m_pHorse3 = CHorse3::Create(D3DXVECTOR3(100, 0, -50), D3DXVECTOR3(0, D3DX_PI / 2, 0), CHorse3::JOCKEYTYPE_RESULT);

	// �n4�̐���
	m_pHorse4 = CHorse4::Create(D3DXVECTOR3(100, 0, 0), D3DXVECTOR3(0, D3DX_PI / 2, 0), CHorse4::JOCKEYTYPE_RESULT);

	//===============================================================================================================
	// ��
	//===============================================================================================================
	 //�n7�̐���
	m_pHorse7 = CHorse7::Create(D3DXVECTOR3(-100, 0, -150), D3DXVECTOR3(0, 11, 0), CHorse7::JOCKEYTYPE_RESULT);

	// �n8�̐���
	m_pHorse8 = CHorse8::Create(D3DXVECTOR3(-100, 0, -100), D3DXVECTOR3(0, 11, 0), CHorse8::JOCKEYTYPE_RESULT);

	// �n5�̐���
	m_pHorse5 = CHorse5::Create(D3DXVECTOR3(-100, 0, -50), D3DXVECTOR3(0, 11, 0), CHorse5::JOCKEYTYPE_RESULT);

	// �n6�̐���
	m_pHorse6 = CHorse6::Create(D3DXVECTOR3(-100, 0, 0), D3DXVECTOR3(0, 11, 0), CHorse6::JOCKEYTYPE_RESULT);

	CUnion::Create(D3DXVECTOR3(0, 0, -100), D3DXVECTOR3(0, 0, 0));

	// ���b�V���t�B�[���h�̐���
	//m_pMeshFiled = CMeshFiled::Create(D3DXVECTOR3(0.0f, 0.0f, 1700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), X_SIZE, Z_SIZE, mPolygonX, mPolygonZ);

	// �v���X�G���^�[�̐���
	//CPressEntor::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 200, 0), 200.0f, 70.0f);

	// ���S�̐���
	CLogo::Create(D3DXVECTOR3(-700, SCREEN_HEIGHT - 500, 0.0f), 600.0f, 200.0f, CLogo::LOGO_RESULT);
}

//=============================================================================
// �I������
//=============================================================================
void CResult::Uninit(void)
{
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
void CResult::Update(void)
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
			pFade->SetFade(CManager::MODE_TITLE);
		}
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
void CResult::Draw(void)
{
	// NULL�`�F�b�N
	if (m_pCamera != NULL)
	{
		m_pCamera->SetCamera();			// �J�����̐ݒ�
	}
}

//=============================================================================
// �^�C�g���̐���
//=============================================================================
CResult*CResult::Create(void)
{
	CResult *pTitle;

	pTitle = new CResult;

	pTitle->Init();

	return pTitle;
}

//=============================================================================
// �J�����̎擾
//=============================================================================
CCamera * CResult::GetCamera(void)
{
	return m_pCamera;
}

//=============================================================================
// ���C�g�̎擾
//=============================================================================
CLight * CResult::GetLight(void)
{
	return m_pLight;
}

//=============================================================================
// ���b�V���t�B�[���h�̎擾
//=============================================================================
CMeshFiled * CResult::GetMeshFiled(void)
{
	return m_pMeshFiled;
}

//=============================================================================
// ���S�̎擾
//=============================================================================
CLogo * CResult::GetLogo(void)
{
	return m_pLogo;
}

//=============================================================================
// �n�̎擾
//=============================================================================
CPlayer * CResult::GetPlayer(void)
{
	return m_pPlayer;
}
//=============================================================================
// �n2�̎擾
//=============================================================================
CHorse2 * CResult::GetHorse2(void)
{
	return m_pHorse2;
}
//=============================================================================
// �n3�̎擾
//=============================================================================
CHorse3 * CResult::GetHorse3(void)
{
	return m_pHorse3;
}
//=============================================================================
// �n4�̎擾
//=============================================================================
CHorse4 * CResult::GetHorse4(void)
{
	return m_pHorse4;
}
//=============================================================================
// �n5�̎擾
//=============================================================================
CHorse5 * CResult::GetHorse5(void)
{
	return m_pHorse5;
}
//=============================================================================
// �n6�̎擾
//=============================================================================
CHorse6 * CResult::GetHorse6(void)
{
	return m_pHorse6;
}
//=============================================================================
// �n7�̎擾
//=============================================================================
CHorse7 * CResult::GetHorse7(void)
{
	return m_pHorse7;
}
//=============================================================================
// �n8�̎擾
//=============================================================================
CHorse8 * CResult::GetHorse8(void)
{
	return m_pHorse8;
}
//=============================================================================
// �n9�̎擾
//=============================================================================
CHorse9 * CResult::GetHorse9(void)
{
	return m_pHorse9;
}
//=============================================================================
// �n10�̎擾
//=============================================================================
CHorse10 * CResult::GetHorse10(void)
{
	return m_pHorse10;
}

//=============================================================================
// �W���b�L�[1�̎擾
//=============================================================================
CJockey * CResult::GetJockey(void)
{
	return m_pJockey;
}
//=============================================================================
// �W���b�L�[2�̎擾
//=============================================================================
CJockey2 * CResult::GetJockey2(void)
{
	return m_pJockey2;
}
//=============================================================================
// �W���b�L�[3�̎擾
//=============================================================================
CJockey3 * CResult::GetJockey3(void)
{
	return m_pJockey3;
}
//=============================================================================
// �W���b�L�[4�̎擾
//=============================================================================
CJockey4 * CResult::GetJockey4(void)
{
	return m_pJockey4;
}
//=============================================================================
// �W���b�L�[5�̎擾
//=============================================================================
CJockey5 * CResult::GetJockey5(void)
{
	return m_pJockey5;
}
//=============================================================================
// �W���b�L�[6�̎擾
//=============================================================================
CJockey6 * CResult::GetJockey6(void)
{
	return m_pJockey6;
}
//=============================================================================
// �W���b�L�[7�̎擾
//=============================================================================
CJockey7 * CResult::GetJocke7(void)
{
	return m_pJockey7;
}

//=============================================================================
// �W���b�L�[8�̎擾
//=============================================================================
CJockey8 * CResult::GetJocke8(void)
{
	return m_pJockey8;
}
//=============================================================================
// �W���b�L�[9�̎擾
//=============================================================================
CJockey9 * CResult::GetJockey9(void)
{
	return m_pJockey9;
}
//=============================================================================
// �W���b�L�[10�̎擾
//=============================================================================
CJockey10 * CResult::GetJockey10(void)
{
	return m_pJockey10;
}