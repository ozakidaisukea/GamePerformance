//=============================================================================
//
// �G���^�[�̏���[Entor.cpp]
// Author : Ozaki
//
//=============================================================================
#include "enter.h"
#include "main.h"
#include "scene.h"
#include "renderer.h"
#include "manager.h"
#include "scene2D.h"

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9 CEntor::m_pTexture = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CEntor::CEntor()
{
	m_pos = D3DXVECTOR3(0, 0, 0);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CEntor::~CEntor()
{

}

//=============================================================================
// ���[�h
//=============================================================================
HRESULT CEntor::Load(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = NULL;

	pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̐���[1]
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\logo\\ent.png",
		&m_pTexture);


	return S_OK;
}

//=============================================================================
// �A�����[�h
//=============================================================================
void CEntor::Unload(void)
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
HRESULT CEntor::Init(D3DXVECTOR3 pos, float widtgh, float height)
{
	// �V�[��2D�̏�����
	m_apScene2D = CScene2D::Create(pos, widtgh, height);

	m_apScene2D->BindTexture(m_pTexture);

	m_widtgh = widtgh;

	m_pos = pos;

	m_height = height;

	// �I�u�W�F�N�g�^�C�v��ݒ�
	SetObjtType(CScene::OBJTYPE_PRESSENTOR);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CEntor::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CEntor::Update(void)
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;

	pos = GetPosition();

	m_nCntEnter++;

	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = NULL;

	// �����_���[�̎擾
	pDevice = CManager::GetRenderer()->GetDevice();

	// �L�[�{�[�h�̎擾
	CInputKeyboard *InputKeyboard;
	InputKeyboard = CManager::GetInputKeyboard();

	if (m_nCntEnter >= 30)
	{
		//m_apScene2D->BindTexture(m_pTexture);
		m_pVtxBuff = m_apScene2D->GetVtxBG();

		if (m_fEnterTimer == 1)
		{
			m_fEnterTimer = 0.0f;
		}
		else if (m_fEnterTimer == 0)
		{
			m_fEnterTimer = 1.0f;
		}

		VERTEX_2D *pVtx;	// ���_���ւ̃|�C���^

		// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, m_fEnterTimer);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, m_fEnterTimer);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, m_fEnterTimer);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, m_fEnterTimer);

		//���_�o�b�t�@���A�����b�N
		m_pVtxBuff->Unlock();

		m_nCntEnter = 0;
	}

	// �|�W�V�����̐ݒ�
	m_apScene2D->SetPosition(m_pos, m_rot, m_position, m_flength);
}

//=============================================================================
// �`�揈��
//=============================================================================
void CEntor::Draw(void)
{
	m_apScene2D->Draw();
}

//=============================================================================
// �v���X�G���^�[�̐���
//=============================================================================
CEntor *CEntor::Create(D3DXVECTOR3 pos, float widtgh, float height)
{
	CEntor *pEntor;

	pEntor = new CEntor;

	pEntor->Init(pos, widtgh, height);

	// ���L�e�N�X�`�������蓖�Ă�
	//pPreesEntor->BindTexture(m_pTexture);

	return pEntor;
}
