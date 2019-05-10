//=============================================================================
//
// �^�C�g����ʏ��� [title.cpp]
// Author : Niwa Hodaka
//
//=============================================================================
#include "title.h"
#include "pressenter.h"
#include "fade.h"
#include "input.h"
#include "titlelogo.h"
#include "sound.h"

#include "camera.h"
#include "light.h"
#include "sky.h"
#include "shadow.h"
#include "field.h"
#include "model.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
int            g_nCounterTitle;          // �����L���O��ʂɑJ�ڂ���^�C�~���O

//=============================================================================
// ����������
//=============================================================================
void InitTitle(void)
{
	// �J�����̏���������
	InitCamera();

	// ���C�g�̏���������
	InitLight();

	// ��̏���������
	InitSky();

	// �n�ʂ̏���������
	InitField();

	// ���f���̏���������
	InitModel();

	// �e�̏���������
	InitShadow();

	InitTitleLogo();

	InitPressEnter();
	SetPressEnter(D3DXVECTOR3(SCREEN_WIDTH / 2, 570.0f, 0.0f), 500, 100);

	g_nCounterTitle = 0;   // �J�E���^�[��0��
}
//=============================================================================
// �I������
//=============================================================================
void UninitTitle(void)
{
	// �J�����̏I������
	UninitCamera();

	// ���C�g�̏I������
	UninitLight();

	// ��̏I������
	UninitSky();

	// �n�ʂ̏I������
	UninitField();

	// ���f���̏I������
	UninitModel();

	// �e�̏���������
	UninitShadow();

	UninitTitleLogo();

	UninitPressEnter();
}
//=============================================================================
// �X�V����
//=============================================================================
void UpdateTitle(void)
{
	// �J�����̍X�V����
	UpdateCamera();

	// ���C�g�̏I������
	UpdateLight();

	// ��̏I������
	UpdateSky();

	// �n�ʂ̏I������
	UpdateField();

	// ���f���̏I������
	UpdateModel();

	UpdateTitleLogo();

	//
	UpdatePressEnter();

	FADE fade;
	fade = GetFade();
	//bool *disp;
	//disp = GetDispPressEnter();

	g_nCounterTitle++;

	if (GetFade() == FADE_NONE)
	{// �t�F�[�h��Ԃł͂Ȃ�
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{// ��ʑJ��
			SetFade(MODE_TUTORIAL);
		}

		for (int nCntPad = 0; nCntPad < 2; nCntPad++)
		{
			for (int nCntButton = XIJS_BUTTON_4; nCntButton < XIJS_BUTTON_16; nCntButton++)
			{// ��������{�^�����̐������J��Ԃ�
				if (GetXInputTrigger(nCntPad, (XIJS_BUTTON)nCntButton) == TRUE)
				{
					SetFade(MODE_TUTORIAL);
				}
			}
		}
		if (g_nCounterTitle % 1200 == 0)
		{// ��莞�Ԃ�����
			SetFade(MODE_TITLE);
		}
	}
}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawTitle(void)
{
	// �J�����̕`�揈��
	SetCamera();

	// ��̏I������
	DrawSky();

	// �n�ʂ̏I������
	DrawField();

	// ���f���̏I������
	DrawModel();

	DrawTitleLogo();

	DrawPressEnter();
}