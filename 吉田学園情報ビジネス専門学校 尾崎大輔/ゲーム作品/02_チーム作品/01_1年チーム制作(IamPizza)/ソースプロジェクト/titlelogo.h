//=============================================================================
// ���ƍ쐬
// �w�i�̏��� [titlelogo.h]
// Author : Mikiya Meguro
//
//=============================================================================
#ifndef _TITLELOGO_H_
#define _TITLELOGO_H_

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitTitleLogo(void);
void UninitTitleLogo(void);
void UpdateTitleLogo(void);
void DrawTitleLogo(void);
D3DXVECTOR3 *GetTitleLogo(void);
void SetTitleLogo(D3DXVECTOR3 TitleLogo);
#endif