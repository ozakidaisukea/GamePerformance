//=============================================================================
//
// ���쏈�� [sousa.cpp]
// Author : Ozaki
//
//=============================================================================
#include "sousa.h"
#include "manager.h"
#include "renderer.h"
#include "bg.h"
#include "fade.h"
#include "logo.h"
#include "logosyake.h"
#include "Pressentor.h"
#include "sound.h"
#include "joypad.h"
#include "item.h"

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9	CSousa::m_pTexture = NULL;
LPDIRECT3DVERTEXBUFFER9 CSousa::m_pVtxBuff = NULL;
CSound*CSousa::m_pSound = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CSousa::CSousa()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CSousa::~CSousa()
{

}

//=============================================================================
// ���[�h
//=============================================================================
HRESULT CSousa::Load(void)
{
	CRenderer *pRenderer;

	pRenderer = new CRenderer;

	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = NULL;

	pDevice = CManager::GetRenderer()->GetDevice();

	return S_OK;
}

//=============================================================================
// �A�����[�h
//=============================================================================
void CSousa::Unload(void)
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
HRESULT CSousa::Init(void)
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

	//���[�J���ϐ�
	VERTEX_2D*pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^�̎擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//�e�N�X�`���̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

	// ���S�̓ǂݍ���
	CLogo::Load();

	// �v���X�G���^�[�̓ǂݍ���
	CPressEntor::Load();

	// ���S�̐���
	CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0), 900.0f, 500.0f, CLogo::LOGO_SOUSA);

	// �v���X�G���^�[�̐���
	CPressEntor::Create(D3DXVECTOR3( 1050.0f, 600.0f, 0), 200.0f, 70.0f);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CSousa::Uninit(void)
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
void CSousa::Update(void)
{
	// �L�[�{�[�h���擾
	CInputKeyboard *InputKeyboard;
	InputKeyboard = CManager::GetInputKeyboard();

	// �L�[�{�[�h���擾
	CInputjoypad *InputJoypad;
	InputJoypad = CManager::GetInputJoypad();

	// �T�E���h���擾
	CSound *pSound;
	pSound = CManager::GetSound();

	m_pSound = pSound;

	// �t�F�[�h���擾
	CFade *pFade;
	pFade = CManager::GetFade();

	if (pFade->GetFade() == CFade::FADE_NONE)
	{
		if (InputKeyboard->GetTrigger(DIK_RETURN) == true || InputJoypad->GetPress(CInputjoypad::DIJS_BOTTON_START) == true
			|| InputJoypad->GetTrigger(CInputjoypad::DIJS_BOTTON_B) == true)
		{
			pFade->SetFade(CManager::MODE_TUTORIAL);

			pSound->PlaySound(pSound->SOUND_LABEL_SE_DECISON);
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CSousa::Draw(void)
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
// �^�C�g���̐���
//=============================================================================
CSousa*CSousa::Create(void)
{
	CSousa *pSousa;

	pSousa = new CSousa;

	pSousa->Init();

	return pSousa;
}