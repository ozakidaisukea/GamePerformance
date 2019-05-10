//=============================================================================
//
// ���S�̏���[logo.cpp]
// Author : Ozaki
//
//=============================================================================
#include "logo.h"
#include "main.h"
#include "scene.h"
#include "renderer.h"
#include "manager.h"
#include "scene2D.h"
#include "input.h"
#include "joypad.h"

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9 CLogo::m_pTexture[MAX_LOGO] = {};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CLogo::CLogo() :CScene2D(4)
{
	m_pos = D3DXVECTOR3(0, 0, 0);
	m_nCntEnter = 0;
	m_fEnterTimer = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CLogo::~CLogo()
{

}

//=============================================================================
// ���[�h
//=============================================================================
HRESULT CLogo::Load(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = NULL;

	pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̐���[1]	// �^�C�g��
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\logo\\title.png",
		&m_pTexture[0]);

	// �e�N�X�`���̐���[2]	// �o�n�\
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\logo\\card.png",
		&m_pTexture[1]);

	// �e�N�X�`���̐���[3]	// �`���[�g���A��
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\logo\\tutorial.png",
		&m_pTexture[2]);

	// �e�N�X�`���̐���[4]	// ���U���g
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\logo\\Result.png",
		&m_pTexture[3]);

	// �e�N�X�`���̐���[4]	// �v���X�G���^�[
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\logo\\press_enter000.png",
		&m_pTexture[4]);

	return S_OK;
}

//=============================================================================
// �A�����[�h
//=============================================================================
void CLogo::Unload(void)
{
	for (int nCnt = 0; nCnt < MAX_LOGO; nCnt++)
	{
		// �e�N�X�`���̔j��
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();

			m_pTexture[nCnt] = NULL;
		}
	}
}
//=============================================================================
// ����������
//=============================================================================
HRESULT CLogo::Init(D3DXVECTOR3 pos, float widtgh, float height, LOGO_TYPE type)
{
	// �V�[��2D�̏�����
	CScene2D::Init();

	SetWidth(widtgh);
	Setheight(height);

	// ���L�e�N�X�`�������蓖�Ă�
	BindTexture(m_pTexture[type]);

	// �I�u�W�F�N�g�^�C�v��ݒ�
	SetObjtType(CScene::OBJTYPE_LOGO);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CLogo::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CLogo::Update(void)
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;

	pos = GetPos();
	m_nCntEnter++;

	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = NULL;

	// �����_���[�̎擾
	pDevice = CManager::GetRenderer()->GetDevice();

	// �L�[�{�[�h�̎擾
	CInputKeyboard *InputKeyboard;
	InputKeyboard = CManager::GetInputKeyboard();

	// �p�b�h���擾
	CInputjoypad *InputJoypad;
	InputJoypad = CManager::GetInputJoypad();

	switch (m_Type)
	{
	case LOGO_TITLE:

		pos.y += 2;

		if (pos.y >= 300)
		{
			pos.y =  300;
		}

		break;
	case LOGO_RESECARD:
		if (InputKeyboard->GetPress(DIK_SPACE) == true || InputJoypad->GetPress(CInputjoypad::DIJS_BOTTON_LT) == true)
		{
			pos.x -= 5;

			if (pos.x <= -800)
			{
				pos.x = 2000;
			}
		}
		break;

	case LOGO_RESULT:

		pos.x += 50;

		if (pos.x >= SCREEN_WIDTH / 2)
		{
			pos.x = SCREEN_WIDTH / 2;
		}

		break;

	case LOGO_PRESSENTOR:

		if (m_nCntEnter >= 10)
		{
			LPDIRECT3DVERTEXBUFFER9 pVtxBuff = CScene2D::GetVtxBG();

			if (m_fEnterTimer == 1)
			{
				m_fEnterTimer = 0.0f;
			}
			else if (m_fEnterTimer == 0)
			{
				m_fEnterTimer = 1.0f;
			}

			if (pVtxBuff != NULL)
			{
				VERTEX_2D *pVtx;	// ���_���ւ̃|�C���^

				// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
				pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, m_fEnterTimer);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, m_fEnterTimer);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, m_fEnterTimer);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, m_fEnterTimer);

				//���_�o�b�t�@���A�����b�N
				pVtxBuff->Unlock();
			}

			m_nCntEnter = 0;
		}
		break;
	}

	// �|�W�V�����̐ݒ�
	SetPosition(pos,0.0f,0.0f,0.0f);
}

//=============================================================================
// �`�揈��
//=============================================================================
void CLogo::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// �G�̐���
//=============================================================================
CLogo *CLogo::Create(D3DXVECTOR3 pos, float widtgh, float height, LOGO_TYPE type)
{
	CLogo *pLogo;

	pLogo = new CLogo();

	pLogo->Init(pos, widtgh, height, type);
	pLogo->SetPosition(pos,0.0f,0.0f,0.0f);
	pLogo->m_Type = type;

	return pLogo;
}
