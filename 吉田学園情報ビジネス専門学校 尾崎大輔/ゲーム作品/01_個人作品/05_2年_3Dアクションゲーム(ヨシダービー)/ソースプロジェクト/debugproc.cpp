//=============================================================================
//
// �f�o�b�N���� [debugpro.cpp]
// Author : Ozaki
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS
#include "debugproc.h"
#include "manager.h"
#include "main.h"
#include "renderer.h"
#include <stdio.h>
#include "input.h"

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
LPD3DXFONT CDebugProc::m_pFont = NULL;
char CDebugProc::m_aStr[DEBUG_DATA] = {};
bool CDebugProc::m_bDisplay = NULL;
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CDebugProc::CDebugProc()
{
	m_bDisplay = false;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CDebugProc::~CDebugProc()
{
}

//=============================================================================
// ����������
//=============================================================================
void CDebugProc::Init(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = NULL;

	pDevice = CManager::GetRenderer()->GetDevice();

	// �f�o�b�O���\���p�t�H���g�̐���
	D3DXCreateFont(pDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_pFont);
}

//=============================================================================
// �I������
//=============================================================================
void CDebugProc::Uninit(void)
{
	m_pFont = NULL;

	for (int nCnt = 0; nCnt < DEBUG_DATA; nCnt++)
	{
		m_aStr[nCnt] = NULL;
	}
}

//=============================================================================
//
//=============================================================================
void CDebugProc::Print(char * fmt, ...)
{
	// �L�[�{�[�h���擾
	CInputKeyboard *InputKeyboard;
	InputKeyboard = CManager::GetInputKeyboard();


	if (InputKeyboard->GetTrigger(DIK_Z) == true)
	{
		m_bDisplay = true;
	}

	int		nNum;			// int�^�̎��o������������
	char	cNum[40];		// char�^�̎��o������������
	float	fNum;			// float�^�̎��o������������

	va_list  list;			// ���܂Ƃ߂�ϐ�

	va_start(list, fmt);	// ���ꂽ�������ꊇ�ɂ��Ă����

							// fmt�̒��g���ꕶ�������Ă���
	while (*fmt)
	{
		switch (*fmt)
		{
		case 's':			// char�^

							// va_arg ���X�g�̒�������o��
			strcat(m_aStr, va_arg(list, char*));
			break;

		case 'd':			// int�^

							// int�^�����o��
			nNum = va_arg(list, int);

			sprintf(cNum, " %d ", nNum);

			// va_arg ���X�g�̒�������o��
			strcat(m_aStr, cNum);
			break;

		case 'f':			// float�^

			// float�^�����o��
			fNum = (float)(va_arg(list, double));

			sprintf(cNum, " %f ", fNum);

			// va_arg ���X�g�̒�������o��
			strcat(m_aStr, cNum);
			break;
		}
		fmt++;				// ������i�߂�
	}
	strcat(m_aStr, "\n");
	va_end(list);			// �I��
}

//=============================================================================
// �`�揈��
//=============================================================================
void CDebugProc::Draw(void)
{
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };	// �`��͈̔͐ݒ�

														// �e�L�X�g�`��
	m_pFont->DrawText(NULL, m_aStr, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
}

//=============================================================================
// ��������������
//=============================================================================
void CDebugProc::ResetStr(void)
{
	for (int nCnt = 0; nCnt < DEBUG_DATA; nCnt++)
	{// NULL������
		m_aStr[nCnt] = '\0';
	}
}
