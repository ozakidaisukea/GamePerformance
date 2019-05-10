#pragma once
//=============================================================================
//
// ���͏��� [paseaselct.h]
// Author :  Ozaki
//
//=============================================================================
#ifndef _PAUSESELECT_H_
#define _PAUSESELECT_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_Pausecont	(10)	// �G�̍ő吔

//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//�񋓌^
typedef enum
{
	SELECTMODE_NONE = 0,
	SELECTMODE_CONTINE,
	SELECTMODE_RETRY,
	SELECTMODE_QUIT,
	SELECTMODE_MAX,
}SELECTMODE;

typedef enum
{
	SELECTTYPE_NONE = 0,
	SELECTTYPE_SELECT,
	SELECTTYPE_MAX
}SELECT;

typedef struct
{
	SELECT		select;		//�Z���N�g
	D3DXVECTOR3 pos;		//�ʒu
	D3DXCOLOR   col;		//�J���[

}PAUSESELECT;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitPauseSelect(void);
void UninitPauseSelect(void);
void UpdatePauseSelect(void);
void DrawPauseSelect(void);
void SetPauseSelect(D3DXVECTOR3 pos, D3DXCOLOR col);
SELECTMODE *GetPauseMode(void);

#endif


