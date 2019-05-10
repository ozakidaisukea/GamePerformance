//=============================================================================
//
// UI���� [UIe.cpp]
// Author : YUTARO ABE
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "ui.h"				// �^�C�g���t���[��
#include "manager.h"		// �}�l�[�W���[
#include "renderer.h"		// �����_���[
#include "input.h"			// ����
#include "particle2D.h"
#include "player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_TITLE000		"data\\TEXTURE\\UI\\titlelogo.png"			// �^�C�g�����S�e�N�X�`��
#define	TEXTURE_PRESS			"data\\TEXTURE\\UI\\press.png"				// PRESS
#define	TEXTURE_TUTORIAL000		"data\\TEXTURE\\7.png"			// �`���[�g���A��
#define	TEXTURE_GAME000			"data\\TEXTURE\\UI\\playersizeui.png"		// �v���C���[�̃T�C�Y��UI
#define	TEXTURE_GAME001			"data\\TEXTURE\\UI\\minmapplayer.png"		// �~�j�}�b�v�̃v���C���[
#define	TEXTURE_GAME002			"data\\TEXTURE\\UI\\minmap.png"				// �~�j�}�b�v
#define	TEXTURE_RESULT000		"data\\TEXTURE\\UI\\resultlogo.png"			// �t�B�j�b�V��
#define	TEXTURE_PLAYER			"data\\TEXTURE\\UI\\player.png"				// �v���C���[

#define	TEXTURE_GAMEMOVEUI000	"data\\TEXTURE\\UI\\move.png"				// �ړ��L�[
#define	TEXTURE_GAMEMOVEUI001	"data\\TEXTURE\\UI\\jump.png"				// �W�����v
#define	TEXTURE_GAMEMOVEUI002	"data\\TEXTURE\\UI\\small.png"				// �k��
#define	TEXTURE_GAMEMOVEUI003	"data\\TEXTURE\\UI\\bikku.png"				// �g��

#define	TEXTURE_RANKING			"data\\TEXTURE\\UI\\rankinglogo.png"		// �����L���O���S
#define	TEXTURE_RANKING1		"data\\TEXTURE\\UI\\ranking1.png"		// 1
#define	TEXTURE_RANKING2		"data\\TEXTURE\\UI\\ranking2.png"		// 2
#define	TEXTURE_RANKING345		"data\\TEXTURE\\UI\\ranking345.png"		// 345


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9	CUI::m_pTexture[UI_TEXMAX] = {};			// �e�N�X�`�����ւ̃|�C���^

																//=============================================================================
																// �R���X�g���N�^
																//=============================================================================
CUI::CUI() : CScene2D(7, OBJTYPE_SCENE2D)
{
	m_nType = 0;								//	���
	m_nCounterAnim = 0;							//	�A�j���[�V�����p�J�E���^�[
	m_nPatternAnim = 0;							//	�A�j���[�V�����p�^�[��
	fWidthOld = 0.0f;							//	�����̑傫���̈ʒu
	bFlash = false;								//	�_�ł��Ȃ�
	nSizeCount = 0;								//	�傫���̃J�E���g
	nFlashType = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CUI::~CUI()
{

}
//=============================================================================
// ���[�h����
//=============================================================================
HRESULT CUI::Load(void)
{
	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_TITLE000, &m_pTexture[0]);		//	�^�C�g�����S
	D3DXCreateTextureFromFile(pDevice, TEXTURE_PRESS, &m_pTexture[1]);			//	PRESS
	D3DXCreateTextureFromFile(pDevice, TEXTURE_TUTORIAL000, &m_pTexture[2]);	//	�^�C�g�����S
	D3DXCreateTextureFromFile(pDevice, TEXTURE_GAME000, &m_pTexture[3]);		//	�v���C���[�̃T�C�Y��UI
	D3DXCreateTextureFromFile(pDevice, TEXTURE_GAME001, &m_pTexture[4]);		//	�v���C���[�̃T�C�Y��UI
	D3DXCreateTextureFromFile(pDevice, TEXTURE_GAME002, &m_pTexture[5]);		//	�~�j�}�b�v
	D3DXCreateTextureFromFile(pDevice, TEXTURE_RESULT000, &m_pTexture[6]);		//	�t�B�j�b�V��
	D3DXCreateTextureFromFile(pDevice, TEXTURE_PLAYER, &m_pTexture[7]);			//	�v���C���[

	D3DXCreateTextureFromFile(pDevice, TEXTURE_GAMEMOVEUI000, &m_pTexture[8]);	//	�ړ�
	D3DXCreateTextureFromFile(pDevice, TEXTURE_GAMEMOVEUI001, &m_pTexture[9]);	//	�W�����v
	D3DXCreateTextureFromFile(pDevice, TEXTURE_GAMEMOVEUI002, &m_pTexture[10]);	//	�k��
	D3DXCreateTextureFromFile(pDevice, TEXTURE_GAMEMOVEUI003, &m_pTexture[11]);	//	�g��

	D3DXCreateTextureFromFile(pDevice, TEXTURE_RANKING, &m_pTexture[12]);		//	�����L���O���S
	D3DXCreateTextureFromFile(pDevice, TEXTURE_RANKING1, &m_pTexture[13]);		//	1
	D3DXCreateTextureFromFile(pDevice, TEXTURE_RANKING2, &m_pTexture[14]);		//	2
	D3DXCreateTextureFromFile(pDevice, TEXTURE_RANKING345, &m_pTexture[15]);	//	345

	return S_OK;
}

//=============================================================================
// �A�����[�h����
//=============================================================================
void CUI::Unload(void)
{
	for (int nCntTex = 0; nCntTex < UI_TEXMAX; nCntTex++)
	{
		if (m_pTexture[nCntTex] != NULL)
		{// NULL�̏ꍇ
		 // �e�N�X�`���̐���
			m_pTexture[nCntTex]->Release();		// ���
			m_pTexture[nCntTex] = NULL;			// NULL��
		}
	}
}

//=============================================================================
// ��������
//=============================================================================
CUI *CUI::Create(D3DXVECTOR3 pos, float height, float width, D3DXCOLOR col, D3DXVECTOR2 uv, int nType)
{
	CUI *pUI = {};				// Ui�|�C���^

	if (pUI == NULL)
	{// NULL�̏ꍇ// �������m��
		pUI = new CUI;
		if (pUI != NULL)
		{// NULL�ȊO�̏ꍇ
			pUI->Init(pos, height, width, col, uv, nType);			// ����������
		}
	}
	return pUI;
}

//=============================================================================
// UI�쐬���郂�[�h
//=============================================================================
void CUI::CreateMode(CManager::MODE mode)
{
	switch (mode)
	{
	case CManager::MODE_TITLE://		�^�C�g��			-------------------------------------------------------------------------------------------------------------------------------------
		CUI::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 - 400, SCREEN_HEIGHT / 2 - 100, 0.0f), 200.0f, 200.0f, D3DXCOLOR(1.0, 1.0, 1.0f, 1.0), D3DXVECTOR2(1.0f, 1.0f), 7);		//	�v���C���[
		CUI::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 400, SCREEN_HEIGHT / 2 - 100, 0.0f), 200.0f, 200.0f, D3DXCOLOR(1.0, 1.0, 1.0f, 1.0), D3DXVECTOR2(1.0f, 1.0f), 7);		//	�v���C���[
		CUI::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 100, 0.0f), 200.0f, 400.0f, D3DXCOLOR(0.8f, 0.8f, 1.0f, 1.0), D3DXVECTOR2(1.0f, 1.0f), 0);			//	�^�C�g�����S
		CUI::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 200, 0.0f), 100.0f, 400.0f, D3DXCOLOR(1.0, 1.0, 1.0f, 1.0), D3DXVECTOR2(1.0f, 1.0f), 1);				//	PRESS
		break;
	case CManager::MODE_TUTORIAL://		�`���[�g���A��		-------------------------------------------------------------------------------------------------------------------------------------
		CUI::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2, D3DXCOLOR(1.0, 1.0, 1.0f, 1.0), D3DXVECTOR2(1.0f, 1.0f), 2);	//	�`���[�g���A��
		CUI::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 200, SCREEN_HEIGHT / 2 + 300, 0.0f), 100.0f, 400.0f, D3DXCOLOR(1.0, 1.0, 1.0f, 1.0), D3DXVECTOR2(1.0f, 1.0f), 1);		//	PRESS
		break;
	case CManager::MODE_GAME://			�Q�[��				-------------------------------------------------------------------------------------------------------------------------------------
		CUI::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 - 450, SCREEN_HEIGHT / 2 - 200, 0.0f), 100.0f, 100.0f, D3DXCOLOR(1.0, 1.0, 1.0f, 1.0), D3DXVECTOR2(1.0f, 1.0f), 3);		//	�v���C���[�̃T�C�Y��UI
		CUI::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 550, SCREEN_HEIGHT / 2 - 150, 0.0f), 150.0f, 30.0f, D3DXCOLOR(1.0, 1.0, 1.0f, 1.0), D3DXVECTOR2(1.0f, 1.0f), 5);			//	�~�j�}�b�v
		CUI::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 550, SCREEN_HEIGHT / 2, 0.0f), 30.0f, 30.0f, D3DXCOLOR(1.0, 1.0, 1.0f, 1.0), D3DXVECTOR2(1.0f, 1.0f), 4);				//	�v���C���[�̃T�C�Y��UI

		CUI::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 - 500, SCREEN_HEIGHT / 2 + 60, 0.0f), 40, 70, D3DXCOLOR(1.0, 1.0, 1.0f, 1.0), D3DXVECTOR2(1.0f, 1.0f), 8);					//	�ړ�
		CUI::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 - 500, SCREEN_HEIGHT / 2 + 140, 0.0f), 40, 70, D3DXCOLOR(1.0, 1.0, 1.0f, 1.0), D3DXVECTOR2(1.0f, 1.0f), 9);				//	�W�����v
		CUI::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 - 500, SCREEN_HEIGHT / 2 + 210, 0.0f), 40, 70, D3DXCOLOR(1.0, 1.0, 1.0f, 1.0), D3DXVECTOR2(1.0f, 1.0f), 10);				//	�k��
		CUI::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 - 500, SCREEN_HEIGHT / 2 + 280, 0.0f), 40, 70, D3DXCOLOR(1.0, 1.0, 1.0f, 1.0), D3DXVECTOR2(1.0f, 1.0f), 11);				//	�g��

		break;
	case CManager::MODE_RESULT://		���U���g			-------------------------------------------------------------------------------------------------------------------------------------
		CUI::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 100, 0.0f), 100.0f, 400.0f, D3DXCOLOR(1.0, 1.0, 1.0f, 1.0), D3DXVECTOR2(1.0f, 1.0f), 6);				//	�t�B�j�b�V��
		CUI::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 200, SCREEN_HEIGHT / 2 + 300, 0.0f), 100.0f, 400.0f, D3DXCOLOR(1.0, 1.0, 1.0f, 1.0), D3DXVECTOR2(1.0f, 1.0f), 1);		//	PRESS
		break;
	case CManager::MODE_RANKING://		�����L���O			-------------------------------------------------------------------------------------------------------------------------------------
		CUI::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 - 400, SCREEN_HEIGHT / 2, 0.0f), 350.0f, 300.0f, D3DXCOLOR(1.0, 1.0, 1.0f, 1.0), D3DXVECTOR2(1.0f, 1.0f), 7);				//	�v���C���[
		CUI::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 290, 0.0f), 80.0f, 350.0f, D3DXCOLOR(1.0, 1.0, 1.0f, 1.0), D3DXVECTOR2(1.0f, 1.0f), 12);				//	�����L���O���S
		CUI::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2 - 180, 0.0f), 90.0f, 110.0f, D3DXCOLOR(0.5, 0.5, 0.5, 1.0), D3DXVECTOR2(1.0f, 1.0f), 13);			//	1
		CUI::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2 - 50, 0.0f), 80.0f, 100.0f, D3DXCOLOR(0.5, 0.5, 0.5, 1.0), D3DXVECTOR2(1.0f, 1.0f), 14);			//	2
		CUI::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2 + 160, 0.0f), 160.0f, 100.0f, D3DXCOLOR(1.0, 1.0, 1.0f, 1.0), D3DXVECTOR2(1.0f, 1.0f), 15);			//	345
		CUI::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 250, SCREEN_HEIGHT / 2 + 350, 0.0f), 50.0f, 200.0f, D3DXCOLOR(1.0, 1.0, 1.0f, 1.0), D3DXVECTOR2(1.0f, 1.0f), 1);			//	PRESS

		break;
	}
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CUI::Init(D3DXVECTOR3 pos, float height, float width, D3DXCOLOR col, D3DXVECTOR2 uv, int nType)
{
	CScene2D::Init();							//	����������
	CScene2D::SetHeight(height);				//	���̐ݒ�
	CScene2D::SetWidth(width);					//	�����̐ݒ�
	CScene2D::SetVtxPos(pos);					//	�ʒu�̐ݒ�
	CScene2D::SetCol(col);						//	�F�̐ݒ�
	CScene2D::BindTexture(m_pTexture[nType]);	//	�e�N�X�`�����蓖��
												//	��ނ̐ݒ�
	m_nType = nType;
	//	���̏����ʒu
	fWidthOld = width;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CUI::Uninit(void)
{
	CScene2D::Uninit();						// �I������
}

//=============================================================================
// �X�V����
//=============================================================================
void CUI::Update(void)
{
	//�L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetKeyboard();

	//�W���C�p�b�h�̎擾
	CInputJoypad *pInputJoypad;
	pInputJoypad = CManager::GetJoypad();

	D3DXVECTOR3 pos = CScene2D::GetPos();		//	�ʒu�̎擾
	float fWidth = CScene2D::GetWidth();		//	���̎擾
	float fHeight = CScene2D::GetHeight();		//	�傫���̎擾
	D3DXCOLOR col = CScene2D::GetCol();			//	�F�̎擾

	m_nCounterAnim++;

	if (m_nType == 1)
	{//	Press
		if (pInputKeyboard->GetTrigger(DIK_RETURN) == true || pInputJoypad->GetTrigger(pInputJoypad->DIJS_BUTTON_A) == true)
		{
			nFlashType = 1;
		}
		switch (nFlashType)
		{
		case 0:	//	�_�ő�������
			if ((m_nCounterAnim % 60) == 0)
			{
				bFlash = bFlash ? false : true;
			}
			break;
		case 1:	//	�_�Œx������
			if ((m_nCounterAnim % 6) == 0)
			{
				bFlash = bFlash ? false : true;
			}
			break;
		}
		if (bFlash == true)
		{//	�T�C�Y���Ȃ���
			fWidth = 0;
		}
		else if (bFlash == false)
		{//	�T�C�Y�������̑�؂���C�߂�
			fWidth = fWidthOld;
		}
	}
	if (m_nType == 3)
	{//	�v���C���[�̑傫��UI
		if (pInputKeyboard->GetTrigger(DIK_K) == true || pInputJoypad->GetTrigger(pInputJoypad->DIJS_BUTTON_RB) == true)
		{//	�g��
			if (nSizeCount < 2)
			{
				nSizeCount += 1;
				fWidth += 15;
				fHeight += 15;
			}
		}
		else if (pInputKeyboard->GetTrigger(DIK_J) == true || pInputJoypad->GetTrigger(pInputJoypad->DIJS_BUTTON_LB) == true)
		{//	�k��
			if (nSizeCount >= 0)
			{
				nSizeCount -= 1;
				fWidth -= 15;
				fHeight -= 15;
			}
		}
	}
	if (m_nType == 4)
	{//	�~�j�}�b�v�̃v���C���[

		if (pos.y >= 100.0f)
		{
			pos.y -= 0.2f;
		}
	}
	if (m_nType == 6)
	{//	�t�B�j�b�V��
		if ((m_nCounterAnim % 30) == 0)
		{
			bCol = bCol ? false : true;
		}
		if (bCol == true)
		{
			col.r = 0.1f;
			fWidth += 2;
			fHeight += 2;
		}
		else if (bCol == false)
		{
			CParticle2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 - 300, SCREEN_HEIGHT / 2, 0.0f),
				D3DXVECTOR3((sinf((rand() % 628) / 100.0f) * ((rand() % (int)10))), (cosf((rand() % 628) / 100.0f) * ((rand() % (int)10))), 0.0f), D3DXCOLOR(1.0, 1.0, 1.0f, 1.0), 50);
			CParticle2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 300, SCREEN_HEIGHT / 2, 0.0f),
				D3DXVECTOR3((sinf((rand() % 628) / 100.0f) * ((rand() % (int)10))), (cosf((rand() % 628) / 100.0f) * ((rand() % (int)10))), 0.0f), D3DXCOLOR(1.0, 1.0, 1.0f, 1.0), 50);
			col.r = 1.0f;
			fWidth -= 2;
			fHeight -= 2;
		}
	}
	if (m_nType == 7)
	{//	�v���C���[���S
		if ((m_nCounterAnim % 6) == 0)
		{
			bFlash = bFlash ? false : true;
		}
		if (bFlash == true)
		{//	�v���C���[�傫���ύX
			fHeight += 2;
			fWidth -= 2;
		}
		if (bFlash == false)
		{//	�v���C���[�傫���ύX
			fHeight -= 2;
			fWidth += 2;
		}
	}
	if (m_nType == 8)
	{//	�ړ��L�[
		if (pInputKeyboard->GetPress(DIK_A) == true || pInputKeyboard->GetPress(DIK_D) == true
			|| pInputJoypad->GetPress(pInputJoypad->DIJS_BUTTON_LSTICK_LEFT) == true
			|| pInputJoypad->GetPress(pInputJoypad->DIJS_BUTTON_LSTICK_RIGHT) == true
			|| pInputJoypad->GetPress(pInputJoypad->DIJS_BUTTON_LEFT) == true
			|| pInputJoypad->GetPress(pInputJoypad->DIJS_BUTTON_RIGHT) == true)
		{//	�F�ő�l
			col.r = 1.0f;
			col.g = 1.0f;
			col.b = 1.0f;
		}
		else
		{//	�F����
			col.r = 0.5f;
			col.g = 0.5f;
			col.b = 0.5f;
		}
	}
	if (m_nType == 9)
	{//	�W�����v
		if (pInputKeyboard->GetPress(DIK_SPACE) == true || pInputJoypad->GetPress(pInputJoypad->DIJS_BUTTON_A) == true)
		{
			col.r = 1.0f;
			col.g = 1.0f;
			col.b = 1.0f;
		}
		else
		{//	�F����
			col.r = 0.5f;
			col.g = 0.5f;
			col.b = 0.5f;
		}
	}
	if (m_nType == 10)
	{//	�k��
		if (pInputKeyboard->GetPress(DIK_J) == true || pInputJoypad->GetPress(pInputJoypad->DIJS_BUTTON_LB) == true)
		{
			col.r = 1.0f;
			col.g = 1.0f;
			col.b = 1.0f;
		}
		else
		{//	�F����
			col.r = 0.5f;
			col.g = 0.5f;
			col.b = 0.5f;
		}
	}
	if (m_nType == 11)
	{//	�g��
		if (pInputKeyboard->GetPress(DIK_K) == true || pInputJoypad->GetPress(pInputJoypad->DIJS_BUTTON_RB) == true)
		{
			col.r = 1.0f;
			col.g = 1.0f;
			col.b = 1.0f;
		}
		else
		{//	�F����
			col.r = 0.5f;
			col.g = 0.5f;
			col.b = 0.5f;
		}
	}

	if (m_nType == 13)
	{//	1��
		if ((m_nCounterAnim % 6) == 0)
		{
			bFlash = bFlash ? false : true;
		}
		if (bFlash == true)
		{//	�v���C���[�傫���ύX
			fHeight += 2;
			fWidth -= 2;
		}
		if (bFlash == false)
		{//	�v���C���[�傫���ύX
			fHeight -= 2;
			fWidth += 2;
			col.r = 1.0f;
		}
	}
	if (m_nType == 14)
	{//	2��
		if ((m_nCounterAnim % 12) == 0)
		{
			bFlash = bFlash ? false : true;
		}
		if (bFlash == true)
		{//	�v���C���[�傫���ύX
			fHeight += 2;
			fWidth -= 2;
		}
		if (bFlash == false)
		{//	�v���C���[�傫���ύX
			fHeight -= 2;
			fWidth += 2;
			col.b = 1.0f;
		}
	}

	CScene2D::SetVtxPos(pos);					//	�ʒu�̐ݒ�
	CScene2D::SetWidth(fWidth);					//	���̐ݒ�
	CScene2D::SetHeight(fHeight);				//	�����̐ݒ�
	CScene2D::SetCol(col);						//	�F�̐ݒ�
}

//=============================================================================
// �`�揈��
//=============================================================================
void CUI::Draw(void)
{
	CScene2D::Draw();						// �`�揈��
}