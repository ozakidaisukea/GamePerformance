//=============================================================================
//
// �f�o�b�O�p�̃v���V�[�W���̏��� [debugproc.cpp]
// Author : Jukiya Hayakawa
//
//=============================================================================
#include "debugproc.h"
#include "renderer.h"
#include "manager.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPD3DXFONT		CDebugProc::m_pFont;
char			CDebugProc::m_aStr[MAX_CHAR];

//=============================================================================
// �f�o�b�O�p�̃v���V�[�W���R���X�g���N�^
//=============================================================================
CDebugProc::CDebugProc()
{

}

//=============================================================================
// �f�o�b�O�p�̃v���V�[�W���f�X�g���N�^
//=============================================================================
CDebugProc::~CDebugProc()
{

}

//=============================================================================
// �f�o�b�O�p�̃v���V�[�W���̏���������
//=============================================================================
void CDebugProc::Init(void)
{
	//�����_�����O�̎擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();

#ifdef _DEBUG
	// �f�o�b�O���\���p�t�H���g�̐���
	D3DXCreateFont(pDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_pFont);
#endif
}

//=============================================================================
// �f�o�b�O�p�̃v���V�[�W���̏I������
//=============================================================================
void CDebugProc::Uninit(void)
{
#ifdef _DEBUG
	//�f�o�b�O���\���p�̃t�H���g�̔j��
	if (m_pFont != NULL)
	{
		m_pFont->Release();
		m_pFont = NULL;
	}
#endif
}

//=============================================================================
// �f�o�b�O�p�̃v���V�[�W���̍X�V����
//=============================================================================
void CDebugProc::Print(int nNumber,char *fmt, ...)
{
#ifdef _DEBUG
	char cStr[MAX_CHAR];				//�����̍ő吔
	cStr[0] = '\0';						//������
	va_list ap;							//�ψ����i�[

	va_start(ap, fmt);					//�ψ������X�g�̏���������
	vsprintf(cStr, fmt, ap);			//������������ϒ��������X�g�̃f�[�^�ɏ]���ĕ�����ɏ�������

	if (nNumber == 0)
	{
		wsprintf(&m_aStr[0], &cStr[0]);	//������������t�H�[�}�b�g��������ɏ�������
	}
	else if (nNumber == 1)
	{
		strcat(&m_aStr[0], &cStr[0]);	//�㏑��
	}
	va_end(ap);							//�ψ������X�g�̏I������
#endif
}

//=============================================================================
// �f�o�b�O�p�̃v���V�[�W���̕`��
//=============================================================================
void CDebugProc::Draw(void)
{
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	// �e�L�X�g�`��
	m_pFont->DrawText(NULL, m_aStr, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
}