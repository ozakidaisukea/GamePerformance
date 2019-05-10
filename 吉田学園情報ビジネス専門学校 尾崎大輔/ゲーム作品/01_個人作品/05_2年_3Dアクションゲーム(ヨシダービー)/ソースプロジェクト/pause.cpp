//=============================================================================
//
// �|�[�Y�̏���[pause.cpp]
// Author : Ozaki
//
//=============================================================================
#include "pause.h"
#include "main.h"
#include "scene.h"
#include "renderer.h"
#include "manager.h"
#include "scene2D.h"
#include "fade.h"
#include "input.h"

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9 CPause::m_pTexture[MAX_PAUSEMENU] = {};
CPause::PAUSETYPE CPause::m_SelectMode = SELECTMODE_NONE;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CPause::CPause()
{
	for (int nCnt = 0; nCnt < MAX_PAUSEMENU; nCnt++)
	{
		m_pScene2D[nCnt] = NULL;
	}
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CPause::~CPause()
{

}

//=============================================================================
// ���[�h
//=============================================================================
HRESULT CPause::Load(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = NULL;

	pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̐���[1]	�R���e�j���[
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_CONTINUE,
		&m_pTexture[0]);

	// �e�N�X�`���̐���[2]	���g���C
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_RETRY,
		&m_pTexture[1]);

	// �e�N�X�`���̐���[3]	�N�B�b�g
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_QUIT,
		&m_pTexture[2]);

	// �e�N�X�`���̐���[4]	�w�i
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_BG,
		&m_pTexture[3]);

	return S_OK;
}

//=============================================================================
// �A�����[�h
//=============================================================================
void CPause::Unload(void)
{
	for (int nCnt = 0; nCnt < MAX_PAUSEMENU; nCnt++)
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
HRESULT CPause::Init(void)
{
	//���[�J���ϐ�
	VERTEX_2D*pVtx;

	// �I�u�W�F�N�g�^�C�v��ݒ�
	SetObjtType(CScene::OBJTYPE_PAUSE);

	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = NULL;

	pDevice = CManager::GetRenderer()->GetDevice();

	for (int nCnt = 0; nCnt < MAX_PAUSEMENU; nCnt++)
	{
		if (m_pScene2D[nCnt] == NULL)
		{
			if (nCnt == 3)
			{

				m_pScene2D[nCnt] = new CScene2D(3);
			}
			else
			{
				m_pScene2D[nCnt] = new CScene2D(4);
			}

			if (m_pScene2D[nCnt] != NULL)
			{
				m_pScene2D[nCnt]->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0, 0);
				m_pScene2D[nCnt]->SetWidth(0.0f);
				m_pScene2D[nCnt]->Setheight(0.0f);

				m_pScene2D[nCnt]->CScene2D::Init();
				m_pScene2D[nCnt]->BindTexture(m_pTexture[nCnt]);
				m_pVtxBuff[nCnt] = m_pScene2D[nCnt]->GetVtxBG();

				m_pVtxBuff[nCnt]->Lock(0, 0, (void**)&pVtx, 0);

				// �w�i
				if (nCnt == 3)
				{
					//���_���W�̐ݒ�
					pVtx[0].pos = D3DXVECTOR3(300.0f, 60.0f, 0.0f);
					pVtx[1].pos = D3DXVECTOR3(1000.0f, 60.0f, 0.0f);
					pVtx[2].pos = D3DXVECTOR3(300.0f, 620.0f, 0.0f);
					pVtx[3].pos = D3DXVECTOR3(1000.0f, 620.0f, 0.0f);
				}

				// �R���e�j���[
				if (nCnt == 0)
				{
					//���_���W�̐ݒ�
					pVtx[0].pos = D3DXVECTOR3(350.0f, 90.0f, 0.0f);
					pVtx[1].pos = D3DXVECTOR3(900.0f, 90.0f, 0.0f);
					pVtx[2].pos = D3DXVECTOR3(350.0f, 250.0f, 0.0f);
					pVtx[3].pos = D3DXVECTOR3(900.0f, 250.0f, 0.0f);
				}

				// ���g���C
				if (nCnt == 1)
				{
					//���_���W�̐ݒ�
					pVtx[0].pos = D3DXVECTOR3(350.0f, 240.0f, 0.0f);
					pVtx[1].pos = D3DXVECTOR3(900.0f, 240.0f, 0.0f);
					pVtx[2].pos = D3DXVECTOR3(350.0f, 410.0f, 0.0f);
					pVtx[3].pos = D3DXVECTOR3(900.0f, 410.0f, 0.0f);
				}

				// �N�B�b�g
				if (nCnt == 2)
				{
					//���_���W�̐ݒ�
					pVtx[0].pos = D3DXVECTOR3(350.0f, 400.0f, 0.0f);
					pVtx[1].pos = D3DXVECTOR3(900.0f, 400.0f, 0.0f);
					pVtx[2].pos = D3DXVECTOR3(350.0f, 590.0f, 0.0f);
					pVtx[3].pos = D3DXVECTOR3(900.0f, 590.0f, 0.0f);
				}

				pVtx += 4;

				// ���_�o�b�t�@���A�����b�N����
				m_pVtxBuff[nCnt]->Unlock();
			}
		}
	}
	m_nSelect = 0;

	m_aPauseMenu[0].select = SELECTTYPE_SELECT;

	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void CPause::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_PAUSE; nCnt++)
	{
		// �e�N�X�`���̔j��
		if (m_pScene2D[nCnt] != NULL)
		{
			m_pScene2D[nCnt]->Uninit();

			//delete m_pScene2D[nCnt];
			m_pScene2D[nCnt] = NULL;
		}
	}
	CScene::Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CPause::Update(void)
{
	//���[�J���ϐ�
	VERTEX_2D*pVtx;

	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = NULL;

	// �����_���[�̎擾
	pDevice = CManager::GetRenderer()->GetDevice();

	// �L�[�{�[�h�̎擾
	CInputKeyboard *InputKeyboard;
	InputKeyboard = CManager::GetInputKeyboard();

	// �L�[�{�[�h���擾
	//CInputjoypad *InputJoypad;
	//InputJoypad = CManager::GetInputJoypad();

	if (InputKeyboard->GetTrigger(DIK_DOWN) == true /*||
		InputJoypad->GetTrigger(CInputjoypad::DIJS_STICK_POV_DOWN) == true
		|| InputJoypad->GetTrigger(CInputjoypad::DIJS_STICK_LEFT_DOWN) == true*/)
	{
		m_aPauseMenu[m_nSelect].select = SELECTTYPE_NONE;
		m_nSelect = (m_nSelect + 1) % 3;
		m_aPauseMenu[m_nSelect].select = SELECTTYPE_SELECT;
	}
	if (InputKeyboard->GetTrigger(DIK_UP) == true /*||
		InputJoypad->GetTrigger(CInputjoypad::DIJS_STICK_POV_UP) == true
		|| InputJoypad->GetTrigger(CInputjoypad::DIJS_STICK_LEFT_UP) == true*/)
	{
		m_aPauseMenu[m_nSelect].select = SELECTTYPE_NONE;
		m_nSelect = (m_nSelect + 2) % 3;
		m_aPauseMenu[m_nSelect].select = SELECTTYPE_SELECT;
	}

	for (int nCnt = 0; nCnt < MAX_PAUSEMENU; nCnt++)
	{
		if (m_pScene2D[nCnt] != NULL)
		{// NULL�`�F�b�N
			m_pVtxBuff[nCnt] = m_pScene2D[nCnt]->GetVtxBG();
			if (m_pVtxBuff[nCnt] != NULL)
			{// NULL�`�F�b�N
				m_pVtxBuff[nCnt]->Lock(0, 0, (void**)&pVtx, 0);

				if (m_aPauseMenu[nCnt].select == SELECTTYPE_SELECT)
				{//�I�𒆂̐F
					m_aPauseMenu[nCnt].col = D3DXCOLOR(1.0f, 0.7f, 0.2f, 1.0f);
				}
				else
				{// ���I���̐F
					m_aPauseMenu[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				}
				// ���_�J���[
				pVtx[0].col = m_aPauseMenu[nCnt].col;
				pVtx[1].col = m_aPauseMenu[nCnt].col;
				pVtx[2].col = m_aPauseMenu[nCnt].col;
				pVtx[3].col = m_aPauseMenu[nCnt].col;

				// ���_�o�b�t�@���A�����b�N����
				m_pVtxBuff[nCnt]->Unlock();
			}
		}
	}


	//�G���^�[�L�[
	if (InputKeyboard->GetTrigger(DIK_RETURN) == true /*||
		InputJoypad->GetTrigger(CInputjoypad::DIJS_BOTTON_B) == true*/)
	{
		if (m_nSelect == 0)
		{
			m_SelectMode = SELECTMODE_CONTINE;
		}
		else if (m_nSelect == 1)
		{
			m_SelectMode = SELECTMODE_RETRY;
		}
		else if (m_nSelect == 2)
		{
			m_SelectMode = SELECTMODE_QUIT;
		}

		switch (m_SelectMode)
		{
		case SELECTMODE_CONTINE:
		{
			break;
		}
		case SELECTMODE_RETRY:
		{
			// �t�F�[�h���擾
			CFade *pFade;
			pFade = CManager::GetFade();

			if (pFade->GetFade() == CFade::FADE_NONE)
			{
				pFade->SetFade(CManager::MODE_GAME);
			}
			break;
		}
		case SELECTMODE_QUIT:
		{
			break;
		}
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CPause::Draw(void)
{

}

//=============================================================================
//	�|�[�Y�̐���
//=============================================================================
CPause *CPause::Create(D3DXVECTOR3 pos, float widtgh, float height)
{
	CPause *pPause;

	pPause = new CPause;

	pPause->Init();

	return pPause;
}

//=============================================================================
//	�|�[�Y
//=============================================================================
CPause::PAUSETYPE CPause::GetPause(void)
{
	return m_SelectMode;
}


