//=============================================================================
// ���ƍ쐬
// �w�i�̏��� [resultlogo.h]
// Author : Mikiya Meguro
//
//=============================================================================
#ifndef _RESULTLOGO_H_
#define _RESULTLOGO_H_

#include "main.h"
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitResultLogo(void);
void UninitResultLogo(void);
void UpdateResultLogo(void);
void DrawResultLogo(void);
D3DXVECTOR3 *GetResultLogo(void);
void SetResultLogo(D3DXVECTOR3 ResultLogo);
#endif