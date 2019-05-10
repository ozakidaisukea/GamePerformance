//=============================================================================
//
// �}�b�v�̏��� [mapplayer.h]
// Author : Mikiya Meguro
//
//=============================================================================
#ifndef _MAPPLAYER_H_
#define _MAPPLAYER_H_

#include "main.h"

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 posOld;	//�O��̈ʒu
	D3DXVECTOR3 move;	//�ʒu
	D3DXCOLOR col;		//�J���[
	int nMapBorder;		//�}�b�v�̋��E���ɓ��B������
}MAPPLAYER;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitMapPlayer(void);
void UninitMapPlayer(void);
void UpdateMapPlayer(void);
void DrawMapPlayer(void);

#endif