//=============================================================================
//
// �e�̏��� [shadow.h]
// Author : Ozaki
//
//=============================================================================
#ifndef _SHADOW_H_
#define _SHADOW_H_

#include "main.h"
                                                                                                                                                                      
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitShadow(void);
void UninitShadow(void);
void UpdateShadow(void);
void DrawShadow(void);
int  SetShadow(D3DXVECTOR3 pos,D3DXVECTOR3 rot);
void SetPostionShadow(int nIdxShadow, D3DXVECTOR3 pos);
void DeleteShadow(int nIdxShadow);
#endif
