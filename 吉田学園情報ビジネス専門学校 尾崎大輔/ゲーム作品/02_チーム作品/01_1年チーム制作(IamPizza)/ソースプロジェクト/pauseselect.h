//=============================================================================
//
// �|�[�Y���j���[���� [pauseselect.h]
// Author : Mikiya Meguro
//
//=============================================================================
#ifndef _PAUSESELECT_H_
#define _PAUSESELECT_H_

#include "main.h"

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef enum
{
	SELECTMODE_NONE = 0,
	SELECTMODE_CONTINUE,		//���s���
	SELECTMODE_RETRY,			//���g���C���
	SELECTMODE_QUIT,			//�I��
	SELECTMODE_MAX				//��Ԃ̑���
}SELECTMODE;						//�񋓌^

typedef enum
{
	SELECTTYPE_NONE = 0,	//�I�΂�Ă��Ȃ����
	SELECTTYPE_SELECT,		//�I�΂�Ă���	���
	SELECTTYPE_MAX				//��Ԃ̑���
}SELECT;

typedef struct
{
	SELECT		select;		//�Z���N�g
	D3DXVECTOR3 pos;		//�ʒu
	D3DXCOLOR	col;		//�J���[
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