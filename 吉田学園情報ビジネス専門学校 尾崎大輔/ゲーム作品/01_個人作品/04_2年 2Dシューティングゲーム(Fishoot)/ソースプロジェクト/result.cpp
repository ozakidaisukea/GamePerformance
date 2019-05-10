//=============================================================================
//
// ���U���g���� [result.cpp]
// Author : Ozaki
//
//=============================================================================
#include "result.h"
#include "manager.h"
#include "renderer.h"
#include "fade.h"
#include "bg.h"
#include "logo.h"
#include "joypad.h"
#include "logosyake.h"

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9	CResult::m_pTexture = NULL;
LPDIRECT3DVERTEXBUFFER9 CResult::m_pVtxBuff = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CResult::CResult()
{

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
HRESULT CResult::Load(void)
{
	CRenderer *pRenderer;

	pRenderer = new CRenderer;

	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = NULL;

	pDevice = CManager::GetRenderer()->GetDevice();

	//// �e�N�X�`���̐���
	//D3DXCreateTextureFromFile(pDevice,
	//	"data\\TEXTURE\\game\\mizu.png",
	//	&m_pTexture);

	return S_OK;
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
HRESULT CResult::Init(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = NULL;

	pDevice = CManager::GetRenderer()->GetDevice();

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VRETEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// �w�i�̓ǂݍ���
	CBg::Load();

	// ���S�̓ǂݍ���
	CLogo::Load();

	// �����S�̓ǂݍ���
	CLogosyake::Load();

	// �w�i�̐���
	CBg::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0),10.0f, SCREEN_WIDTH);

	// ���S�̐���
	CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 500, 0), 650.0f, 200.0f, CLogo::LOGO_RESULT);

	// �����S�̐���
	CLogosyake::Create(D3DXVECTOR3(100, 600, 0), 100.0f, 100.0f, D3DXVECTOR3(0.5f, 0.0f, 0.0f), CLogosyake::SYAKE_RESULT);
	CLogosyake::Create(D3DXVECTOR3(50, 500, 0), 50.0f, 50.0f, D3DXVECTOR3(0.5f, 0.0f, 0.0f), CLogosyake::SYAKE_RESULT);
	CLogosyake::Create(D3DXVECTOR3(50, 550, 0), 50.0f, 50.0f, D3DXVECTOR3(0.5f, 0.0f, 0.0f), CLogosyake::SYAKE_RESULT);
	CLogosyake::Create(D3DXVECTOR3(50, 650, 0), 50.0f, 50.0f, D3DXVECTOR3(0.5f, 0.0f, 0.0f), CLogosyake::SYAKE_RESULT);
	CLogosyake::Create(D3DXVECTOR3(50, 700, 0), 50.0f, 50.0f, D3DXVECTOR3(0.5f, 0.0f, 0.0f), CLogosyake::SYAKE_RESULT);
	return S_OK;
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

	// �t�F�[�h���擾
	CFade *pFade;
	pFade = CManager::GetFade();

	// �L�[�{�[�h���擾
	CInputjoypad *InputJoypad;
	InputJoypad = CManager::GetInputJoypad();

	if (pFade->GetFade() == CFade::FADE_NONE)
	{
		if (InputKeyboard->GetTrigger(DIK_RETURN) == true || InputJoypad->GetTrigger(CInputjoypad::DIJS_BOTTON_START) == true
			|| InputJoypad->GetTrigger(CInputjoypad::DIJS_BOTTON_B) == true)
		{
			pFade->SetFade(CManager::MODE_RANKING);
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CResult::Draw(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = NULL;

	pDevice = CManager::GetRenderer()->GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VRETEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);
}

//=============================================================================
// ���U���g�̐���
//=============================================================================
CResult*CResult::Create(void)
{
	CResult *pResult;

	pResult = new CResult;

	pResult->Init();

	return pResult;
}