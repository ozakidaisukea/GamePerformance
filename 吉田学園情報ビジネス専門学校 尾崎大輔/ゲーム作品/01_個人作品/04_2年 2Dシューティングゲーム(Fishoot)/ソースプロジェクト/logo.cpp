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

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9 CLogo::m_pTexture[MAX_LOGO] = {};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CLogo::CLogo() :CScene2D(7)
{
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

	// �e�N�X�`���̐���[1]
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\logo\\title2.png",
		&m_pTexture[0]);

	// �e�N�X�`���̐���[2]
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\logo\\tutorial_logo.png",
		&m_pTexture[1]);

	// �e�N�X�`���̐���[3]
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\logo\\result_logo000.png",
		&m_pTexture[2]);

	// �e�N�X�`���̐���[4]
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\logo\\result_logo001.png",
		&m_pTexture[3]);

	// �e�N�X�`���̐���[5]
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\logo\\ranking_logo.png",
		&m_pTexture[4]);

	// �e�N�X�`���̐���[6]
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\logo\\title_syake.png",
		&m_pTexture[5]);

	// �e�N�X�`���̐���[7]
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\logo\\tutorialsetumei.png",
		&m_pTexture[6]);

	// �e�N�X�`���̐���[8]
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\logo\\ranking_rank1.png",
		&m_pTexture[7]);

	// �e�N�X�`���̐���[9]
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\logo\\1.png",
		&m_pTexture[8]);

	// �e�N�X�`���̐���[10]
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\logo\\2.png",
		&m_pTexture[9]);

	// �e�N�X�`���̐���[11]
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\logo\\3.png",
		&m_pTexture[10]);

	// �e�N�X�`���̐���[12]
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\logo\\4.png",
		&m_pTexture[11]);

	// �e�N�X�`���̐���[13]
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\logo\\5.png",
		&m_pTexture[12]);

	// �e�N�X�`���̐���[14]
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\logo\\sousa.png",
		&m_pTexture[13]);

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
	CScene2D::Init(pos, widtgh, height);

	m_widtgh = widtgh;

	m_height = height;

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

	pos = GetPosition();

	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = NULL;

	// �����_���[�̎擾
	pDevice = CManager::GetRenderer()->GetDevice();

	// �L�[�{�[�h�̎擾
	CInputKeyboard *InputKeyboard;

	InputKeyboard = CManager::GetInputKeyboard();

	// �|�W�V�����̐ݒ�
	SetPosition(pos, m_rot, m_position, m_flength);
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
CLogo *CLogo::Create(D3DXVECTOR3 pos, float widtgh, float height,LOGO_TYPE type)
{
	CLogo *pLogo;

	pLogo = new CLogo;

	pLogo->Init(pos, widtgh,height,type);

	// ���L�e�N�X�`�������蓖�Ă�
	pLogo->BindTexture(m_pTexture[type]);

	return pLogo;
}
