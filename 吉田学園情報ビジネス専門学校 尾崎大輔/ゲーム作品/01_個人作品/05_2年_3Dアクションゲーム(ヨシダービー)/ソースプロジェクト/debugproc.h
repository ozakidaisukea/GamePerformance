//=============================================================================
//
// �f�o�b�N���� [debugproc.h]
// Author : Ozaki
//
//=============================================================================
#ifndef _DEBUGPROC_H_
#define _DEBUGPROC_H_

#include "main.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define DEBUG_DATA	(1024)

//*****************************************************************************
// �N���X�錾
//*****************************************************************************
class CDebugProc
{
public:
	CDebugProc();
	~CDebugProc();

	void Init(void);
	void Uninit(void);

	static void Print(char*fmt, ...);
	static void Draw(void);
	static void ResetStr(void);
private:
	static LPD3DXFONT		m_pFont;
	static char				m_aStr[1024];
	static bool				m_bDisplay;		// �f�o�b�N��ON OFF ��\������
};
#endif
