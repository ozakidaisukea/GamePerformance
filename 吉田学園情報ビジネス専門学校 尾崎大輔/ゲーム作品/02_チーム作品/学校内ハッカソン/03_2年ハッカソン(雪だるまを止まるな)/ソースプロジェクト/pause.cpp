//=============================================================================
//
// �|�[�Y���� [pause.cpp]
// Author : Jukiya Hayakawa
//
//=============================================================================
#include "pause.h"
#include "renderer.h"
#include "fade.h"
#include "input.h"
#include "sound.h"
#include "scene2D.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CPause::m_apTexture[MAX_PAUSE_TEXTURE] = {};

//=============================================================================
// �}�N����`
//=============================================================================

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================

//=============================================================================
// �|�[�Y�̃R���X�g���N�^
//=============================================================================
CPause::CPause()
{
}
//=============================================================================
// �|�[�Y�̃f�X�g���N�^
//=============================================================================
CPause::~CPause()
{
}
//=============================================================================
// �I�u�W�F�N�g�̃e�N�X�`���ǂݍ���
//=============================================================================
HRESULT CPause::Load(void)
{
	//�����_�����O�̎擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\pause.jpg",
		&m_apTexture[0]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\pause000.png",
		&m_apTexture[1]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\pause001.png",
		&m_apTexture[2]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\pause002.png",
		&m_apTexture[3]);
	return S_OK;
}

//=============================================================================
// �I�u�W�F�N�g�̃e�N�X�`���j��
//=============================================================================
void CPause::Unload(void)
{
	for (int nCnt = 0; nCnt < MAX_PAUSE_SELECT; nCnt++)
	{
		// �e�N�X�`���̔j��
		if (m_apTexture[nCnt] != NULL)
		{
			m_apTexture[nCnt]->Release();
			m_apTexture[nCnt] = NULL;
		}
	}
}

//=============================================================================
//�|�[�Y�̐���
//=============================================================================
CPause *CPause::Create(void)
{
	CPause *pPause = NULL;
	if (pPause == NULL)
	{
		pPause = new CPause;		//�V�[���̓��I�m��
		if (pPause != NULL)
		{
			pPause->Init();					//����������
		}
	}
	return pPause;					//�l��Ԃ�
}

//=============================================================================
// �|�[�Y�̏���������
//=============================================================================
HRESULT CPause::Init(void)
{
	//�w�i�̏�����
	m_pScene2D = new CScene2D(7);
	m_pScene2D->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
	m_pScene2D->SetWidth(250.0f);
	m_pScene2D->SetHeight(250.0f);
	m_pScene2D->Init();
	m_pScene2D->BindTexture(m_apTexture[0]);

	//CONTINUE�̏�����
	float Pos = 0;
	for (int nCnt = 0; nCnt < MAX_PAUSE_SELECT; nCnt++)
	{
		m_apSelect[nCnt] = new CScene2D(7);
		m_apSelect[nCnt]->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, 250.0f + Pos, 0.0f));
		m_apSelect[nCnt]->SetWidth(160);
		m_apSelect[nCnt]->SetHeight(80);
		m_apSelect[nCnt]->Init();
		m_apSelect[nCnt]->BindTexture(m_apTexture[nCnt + 1]);
		Pos += 130;
	}
	m_aCol[0] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);						// �F��������
	m_aSelect[0] = PAUSESELECT_SELECT;									// �X�^�[�g��CONTINUE����
	for (int nCnt = 1; nCnt < MAX_PAUSE_SELECT; nCnt++)
	{
		m_aCol[nCnt] = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);				//�F��������
		m_aSelect[nCnt] = PAUSESELECT_NONE;								//�X�^�[�g��CONTINUE����
	}
	m_fCol = 0.01f;														//�F�̕ω���������
	m_nSelect = 0;														// �I������Ă���ԍ���CONTINUE��
	m_select = SELECT_CONTINUE;											//�Q�[���ĊJ��Ԃɂ��Ă���

	for (int nCnt = 0; nCnt < MAX_PAUSE_SELECT; nCnt++)
	{
		m_apSelect[nCnt]->SetCol(m_aCol[nCnt]);
	}
	return S_OK;
}

//=============================================================================
// �|�[�Y�̏I������
//=============================================================================
void CPause::Uninit(void)
{
	//�|�[�Y�w�i�̏I������
	if (m_pScene2D != NULL)
	{
		m_pScene2D->Uninit();
		m_pScene2D = NULL;
	}

	//�|�[�Y�I���̏I������
	for (int nCntPause = 0; nCntPause < MAX_PAUSE_SELECT; nCntPause++)
	{
		if (m_apSelect[nCntPause] != NULL)
		{
			m_apSelect[nCntPause]->Uninit();
			m_apSelect[nCntPause] = NULL;
		}
	}
	//Release();
}

//=============================================================================
// �|�[�Y�̍X�V����
//=============================================================================
void CPause::Update(void)
{
	//�L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetKeyboard();

	//�W���C�p�b�h�̎擾
	CInputJoypad *pInputJoypad;
	pInputJoypad = CManager::GetJoypad();

	//�T�E���h�̎擾
	CSound *pSound;
	pSound = CManager::GetSound();

	/*for (int nCntSelect = 0; nCntSelect < MAX_PAUSE_SELECT; nCntSelect++)
	{
	if (m_apSelect[nCntSelect] != NULL)
	{
	m_apSelect[nCntSelect]->Update();
	}
	}*/

	// �I�����ڈړ�����
	if (pInputKeyboard->GetTrigger(DIK_S) == true ||
		pInputJoypad->GetTrigger(CInputJoypad::DIJS_BUTTON_DOWN) == true ||
		pInputJoypad->GetTrigger(CInputJoypad::DIJS_BUTTON_LSTICK_DOWN) == true)
	{// S�L�[�܂��͏\�����܂��͍��X�e�B�b�N���������ꂽ
		m_aSelect[m_nSelect] = PAUSESELECT_NONE;
		m_aSelect[(m_nSelect + 1) % MAX_PAUSE_SELECT] = PAUSESELECT_SELECT;
		m_nSelect = (m_nSelect + 1) % MAX_PAUSE_SELECT;
	}
	if (pInputKeyboard->GetTrigger(DIK_W) == true ||
		pInputJoypad->GetTrigger(CInputJoypad::DIJS_BUTTON_UP) == true ||
		pInputJoypad->GetTrigger(CInputJoypad::DIJS_BUTTON_LSTICK_UP) == true)
	{// W�L�[�܂��͏\����܂��͍��X�e�B�b�N�オ�����ꂽ
		m_aSelect[m_nSelect] = PAUSESELECT_NONE;
		m_aSelect[(m_nSelect + (MAX_PAUSE_SELECT - 1)) % MAX_PAUSE_SELECT] = PAUSESELECT_SELECT;
		m_nSelect = (m_nSelect + (MAX_PAUSE_SELECT - 1)) % MAX_PAUSE_SELECT;
	}

	for (int nCntPauseSelect = 0; nCntPauseSelect < MAX_PAUSE_SELECT; nCntPauseSelect++)
	{// ���ڂ̐������J��Ԃ�
		if (m_aSelect[nCntPauseSelect] == PAUSESELECT_SELECT)
		{// �I������Ă�����
			m_aCol[nCntPauseSelect].r += m_fCol;
			m_aCol[nCntPauseSelect].g += m_fCol;
			m_aCol[nCntPauseSelect].b += m_fCol;

			if (m_aCol[nCntPauseSelect].r < 0.2f || m_aCol[nCntPauseSelect].r >= 1.0f)
			{// �F������̒l�ɒB����
				m_fCol *= -1;
			}
		}
		else if (m_aSelect[nCntPauseSelect] == PAUSESELECT_NONE)
		{// �I������Ă��Ȃ�������
			m_aCol[nCntPauseSelect].r = 0.2f;
			m_aCol[nCntPauseSelect].g = 0.2f;
			m_aCol[nCntPauseSelect].b = 0.2f;
		}
		// ���_�J���[�̍X�V
		m_apSelect[nCntPauseSelect]->SetCol(m_aCol[nCntPauseSelect]);
	}
	// ��ʑJ��
	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true ||
		pInputJoypad->GetTrigger(CInputJoypad::DIJS_BUTTON_B) == true)
	{// ENTER�L�[�������ꂽ
	 //pSound->PlaySound(CSound::SOUND_LABEL_SE_PAUSESELECT);
		CFade::FADE fade;
		CFade *pFade = NULL;
		fade = pFade->GetFade();

		//if (fade == CFade::FADE_NONE)
		//{// �t�F�[�h��ԂłȂ�

		if (m_nSelect == SELECT_CONTINUE)
		{
			m_select = SELECT_CONTINUE; // �Q�[���ĊJ��Ԃ�
		}
		else if (m_nSelect == SELECT_RETRY)
		{
			m_select = SELECT_RETRY;    // �Q�[����蒼����Ԃ�
		}
		else if (m_nSelect == SELECT_QUIT)
		{
			m_select = SELECT_QUIT;     // �^�C�g���J�ڏ�Ԃ�
		}

		switch (m_select)
		{
		case CPause::SELECT_CONTINUE:  // �Q�[���ĊJ
			break;
		case CPause::SELECT_RETRY:     // �Q�[����蒼��
			pFade->SetFade(CManager::MODE_GAME, pFade->FADE_OUT);
			break;
		case CPause::SELECT_QUIT:      // �^�C�g���J��
			pFade->SetFade(CManager::MODE_TITLE, pFade->FADE_OUT);
			break;
		}
		CManager::GetRenderer()->RelesePause();
	}

	if (pInputKeyboard->GetTrigger(DIK_P) == true ||
		pInputJoypad->GetTrigger(CInputJoypad::DIJS_BUTTON_START) == true)
	{// �|�[�Y���������ꂽ
		m_aCol[0] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		// �F��������
		m_aSelect[0] = PAUSESELECT_SELECT;					// �X�^�[�g��CONTINUE����
		for (int nCntPauseSelect = 1; nCntPauseSelect < MAX_PAUSE_SELECT; nCntPauseSelect++)
		{// ���ڂ̐������J��Ԃ�
			m_aCol[nCntPauseSelect] = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);		// �F��������
			m_aSelect[nCntPauseSelect] = PAUSESELECT_NONE;						// �I������Ă��Ȃ���Ԃɂ���
		}
		m_nSelect = 0;      // �I������Ă���ԍ���CONTINUE��

		for (int nCntPauseSelect = 1; nCntPauseSelect < MAX_PAUSE_SELECT; nCntPauseSelect++)
		{
			m_apSelect[nCntPauseSelect]->SetCol(m_aCol[nCntPauseSelect]);
		}
	}
}

//=============================================================================
// �|�[�Y�̕`�揈��
//=============================================================================
void CPause::Draw(void)
{
	/*for (int nCntSelect = 0; nCntSelect < MAX_PAUSE_SELECT; nCntSelect++)
	{
	if (m_apSelect != NULL)
	{
	m_apSelect[nCntSelect]->Draw();
	}
	}*/
}