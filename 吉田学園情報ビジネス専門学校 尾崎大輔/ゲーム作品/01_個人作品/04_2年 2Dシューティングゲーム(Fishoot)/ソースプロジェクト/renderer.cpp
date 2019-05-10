//=============================================================================
//
// �����_�����O���� [renderer.cpp]
// Author : Ozaki
//
//=============================================================================
#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "scene2D.h"
#include "fade.h"
#include "pause.h"
#include "input.h"
#include "manager.h"
#include "joypad.h"

CPause *CRenderer::m_pPause = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CRenderer::CRenderer()
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CRenderer::~CRenderer()
{

}

//=============================================================================
// ���͏���
//=============================================================================
HRESULT CRenderer::Init(HWND hWnd, bool bWindow)
{
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;

	// Direct3D�I�u�W�F�N�g�̍쐬
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_pD3D == NULL)
	{
		return E_FAIL;
	}

	// ���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));							// ���[�N���[���N���A
	d3dpp.BackBufferCount = 1;									// �o�b�N�o�b�t�@�̐�
	d3dpp.BackBufferWidth = SCREEN_WIDTH;						// �Q�[����ʃT�C�Y(��)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;						// �Q�[����ʃT�C�Y(����)
	d3dpp.BackBufferFormat = d3ddm.Format;						// �J���[���[�h�̎w��
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;					// �f���M���ɓ������ăt���b�v����
	d3dpp.EnableAutoDepthStencil = TRUE;						// �f�v�X�o�b�t�@�i�y�o�b�t�@�j�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;					// �f�v�X�o�b�t�@�Ƃ���16bit���g��
	d3dpp.Windowed = bWindow;									// �E�B���h�E���[�h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	// ���t���b�V�����[�g
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	// �C���^�[�o��

																// �f�o�C�X�̐���
																// �f�B�X�v���C�A�_�v�^��\�����߂̃f�o�C�X���쐬
	// �`��ƒ��_�������n�[�h�E�F�A�ōs�Ȃ�
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp, &m_pD3DDevice)))
	{
		// ��L�̐ݒ肪���s������
		// �`����n�[�h�E�F�A�ōs���A���_������CPU�ōs�Ȃ�
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp, &m_pD3DDevice)))
		{
			// ��L�̐ݒ肪���s������
			// �`��ƒ��_������CPU�ōs�Ȃ�
			if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF, hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp, &m_pD3DDevice)))
			{
				// �������s
				return E_FAIL;
			}
		}
	}

	// �����_�[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// �T���v���[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	// �e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

#ifdef _DEBUG
	// �f�o�b�O���\���p�t�H���g�̐���
	D3DXCreateFont(m_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_pFont);
#endif

	m_bPause = false;

	// �Q�[�W�̓ǂݍ���
	CPause::Load();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CRenderer::Uninit(void)
{
#ifdef _DEBUG

	// �f�o�b�O���\���p�t�H���g�̔j��
	if (m_pFont != NULL)
	{
		m_pFont->Release();
		m_pFont = NULL;
	}
#endif

	// �f�o�C�X�̔j��
	if (m_pD3DDevice != NULL)
	{
		m_pD3DDevice->Release();
		m_pD3DDevice = NULL;
	}

	// Direct3D�I�u�W�F�N�g�̔j��
	if (m_pD3D != NULL)
	{
		m_pD3D->Release();
		m_pD3D = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void CRenderer::Update(void)
{
	// �L�[�{�[�h���擾
	CInputKeyboard *InputKeyboard;
	InputKeyboard = CManager::GetInputKeyboard();

	// �L�[�{�[�h���擾
	CInputjoypad *InputJoypad;
	InputJoypad = CManager::GetInputJoypad();

	// ���[�h���擾
	CManager::MODE mode;
	mode = CManager::GetMode();

	CFade::FADE fade;
	fade = CFade::GetFade();

	if (mode == CManager::MODE_GAME)
	{
		// P�{�^�������Ń|�[�Y
		if (InputKeyboard->GetTrigger(DIK_P) == true && fade == CFade::FADE_NONE ||
			InputJoypad->GetTrigger(CInputjoypad::DIJS_BOTTON_START) == true)
		{

			m_bPause = m_bPause ? false : true;
		}

		if (m_bPause == true)
		{
			// �|�[�Y�̐���
			if (m_pPause == NULL)
			{
				m_pPause = CPause::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0), 500.0f, SCREEN_WIDTH);
			}
		}
		else
		{
			if (fade == CFade::FADE_NONE)
			{
				// �S�Ă̍X�V
				CScene::UpdateAll();

				if (m_pPause != NULL)
				{
					m_pPause->Uninit();
					m_pPause = NULL;
				}
			}
		}


		if (m_bPause == true)
		{
			if (m_pPause != NULL)
			{
				m_pPause->Update();

				if (InputKeyboard->GetTrigger(DIK_RETURN) == true ||
					InputJoypad->GetTrigger(CInputjoypad::DIJS_BOTTON_B) == true)
				{

					CPause::PAUSETYPE select;
					CPause *pPause = NULL;
					select = pPause->GetPause();

					// �t�F�[�h���擾
					CFade *pFade;
					pFade = CManager::GetFade();

					switch (select)
					{
					case CPause::SELECTMODE_CONTINE:

						break;

					case CPause::SELECTMODE_RETRY:
						if (pFade->GetFade() == CFade::FADE_NONE)
						{
							pFade->SetFade(CManager::MODE_GAME);
						}
						break;

					case CPause::SELECTMODE_QUIT:

						if (pFade->GetFade() == CFade::FADE_NONE)
						{
							pFade->SetFade(CManager::MODE_TITLE);
						}
						break;
					}
					m_bPause = m_bPause ? false : true;

					m_pPause->Uninit();
					m_pPause = NULL;
				}
			}
		}
	}
	else
	{
		CScene::UpdateAll();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CRenderer::Draw(void)
{
	// �o�b�N�o�b�t�@���y�o�b�t�@�̃N���A
	m_pD3DDevice->Clear(0,
		NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0),
		1.0f,
		0);

	// Direct3D�ɂ��`��̊J�n
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{
		// �|���S���̕`�揈��
		CScene::DrawAll();

#ifdef _DEBUG
		// FPS�\��
		DrawFPS();
#endif
		// �L�[�{�[�h���擾
		CFade *pFade;
		pFade = CManager::GetFade();

		if (pFade != NULL)
		{
			pFade->Draw();
		}

		// Direct3D�ɂ��`��̏I��
		m_pD3DDevice->EndScene();
	}

	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

#ifdef _DEBUG
//=============================================================================
// FPS�\��
//=============================================================================
void CRenderer::DrawFPS(void)
{
	int nCountFPS;

	//FPS���擾
	nCountFPS = GetFPS();

	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	char str[256];

#ifdef _DEBUG
	wsprintf(str, "FPS:%d\n", nCountFPS);
#endif
	// �e�L�X�g�`��
	m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
}
#endif

//=============================================================================
// �f�o�C�X�̎擾
//=============================================================================
LPDIRECT3DDEVICE9 CRenderer::GetDevice(void)
{
	return m_pD3DDevice;
}