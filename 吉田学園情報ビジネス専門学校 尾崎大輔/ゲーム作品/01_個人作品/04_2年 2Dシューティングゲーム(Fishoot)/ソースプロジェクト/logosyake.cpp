//=============================================================================
//
// ���S���̏���[logosyake.cpp]
// Author : Ozaki
//
//=============================================================================
#include "logosyake.h"
#include "main.h"
#include "scene.h"
#include "renderer.h"
#include "manager.h"
#include "scene2D.h"

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9 CLogosyake::m_pTexture[MAX_SYAKE] = {};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CLogosyake::CLogosyake() :CScene2D(1)
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CLogosyake::~CLogosyake()
{

}

//=============================================================================
// ���[�h
//=============================================================================
HRESULT CLogosyake::Load(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = NULL;

	pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̐���[1]
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\logo\\title_syake.png",
		&m_pTexture[0]);

	// �e�N�X�`���̐���[2]
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\game\\syake_dead.png",
		&m_pTexture[1]);

	// �e�N�X�`���̐���[3]
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\game\\syake.png",
		&m_pTexture[2]);

	// �e�N�X�`���̐���[4]
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\game\\1.png",
		&m_pTexture[3]);

	return S_OK;
}

//=============================================================================
// �A�����[�h
//=============================================================================
void CLogosyake::Unload(void)
{
	for (int nCnt = 0; nCnt < MAX_SYAKE; nCnt++)
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
HRESULT CLogosyake::Init(D3DXVECTOR3 pos, float widtgh, float height,D3DXVECTOR3 move,SYAKE_TYPE type)
{
	// �V�[��2D�̏�����
	CScene2D::Init(pos, widtgh, height);

	m_widtgh = widtgh;

	m_height = height;

	m_Type = type;

	// �I�u�W�F�N�g�^�C�v��ݒ�
	SetObjtType(CScene::OBJTYPE_LOGO);


	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CLogosyake::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CLogosyake::Update(void)
{
	D3DXVECTOR3 pos;

	pos = GetPosition();

	if (SYAKE_LOGO == m_Type)
	{
		if (pos.y >= SCREEN_HEIGHT - 470)
		{
			// �ړ���
			m_move.y += 0.05f;

			pos -= m_move;
		}
	}

	if (SYAKE_RESULT == m_Type)
	{
		if (pos.x >= 500 - 470)
		{
			// �ړ���
			m_move.x -= 0.05f;

			pos -= m_move;
		}
	}

	if (SYAKE_GAMEOVER == m_Type)
	{
		if (pos.x >= 500 - 470)
		{
			// �ړ���
			m_move.x -= 0.05f;

			pos -= m_move;
		}
	}

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
void CLogosyake::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// �G�̐���
//=============================================================================
CLogosyake *CLogosyake::Create(D3DXVECTOR3 pos, float widtgh, float height,D3DXVECTOR3 move, SYAKE_TYPE type)
{
	CLogosyake *pLogosyake;

	pLogosyake = new CLogosyake;

	pLogosyake->Init(pos, widtgh, height, move,type);

	// ���L�e�N�X�`�������蓖�Ă�
	pLogosyake->BindTexture(m_pTexture[type]);

	return pLogosyake;
}
