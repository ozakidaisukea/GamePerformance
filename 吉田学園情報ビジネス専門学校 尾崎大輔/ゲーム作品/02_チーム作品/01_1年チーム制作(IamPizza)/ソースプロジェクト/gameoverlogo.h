//=============================================================================
// ���ƍ쐬
// �w�i�̏��� [gameoverlogo.h]
// Author : Mikiya Meguro
//
//=============================================================================
#ifndef _GAMEOVERLOGO_H_
#define _GAMEOVERLOGO_H_

#include "main.h"
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitGameoverLogo(void);
void UninitGameoverLogo(void);
void UpdateGameoverLogo(void);
void DrawGameoverLogo(void);
D3DXVECTOR3 *GetGameoverLogo(void);
void SetGameoverLogo(D3DXVECTOR3 GameoverLogo);
#endif