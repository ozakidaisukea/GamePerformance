//=============================================================================
// ���ƍ쐬
// �w�i�̏��� [pressenter.h]
// Author : Mikiya Meguro
//
//=============================================================================
#ifndef _PRESSENTER_H_
#define _PRESSENTER_H_

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXCOLOR col;			//�J���[
	int		PressEnterCnt;
	float	PressEnterChange;
	bool	bUse;
	float	fWIdth;
	float	fHeight;
	bool	bDraw;
}PRESSENTER;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitPressEnter(void);
void UninitPressEnter(void);
void UpdatePressEnter(void);
void DrawPressEnter(void);
void SetPressEnter(D3DXVECTOR3 pos, D3DXCOLOR col,float fWIdth, float fHeight );
PRESSENTER *GetPressEnter(void);

#endif