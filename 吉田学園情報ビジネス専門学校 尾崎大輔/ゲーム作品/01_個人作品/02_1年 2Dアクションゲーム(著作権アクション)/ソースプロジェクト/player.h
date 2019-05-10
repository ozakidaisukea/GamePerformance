//=============================================================================
//
// DirectX���^���� [player.h]
// Author : Ozaki
//
//=============================================================================
#pragma once
#ifndef _PLAYER_H_
#define _PLAYER_H_

//*****************************************************************************
//�v���C���[�̍\����
//*****************************************************************************
typedef enum
{
	PLAYER_NORMAL = 0,
	PLAYER_DETHSTATE,	// �v���C���[������
	PLAYER_BIGSTATE,		// 
}PLAYER;

typedef struct
{
	D3DXVECTOR3 pos;		//���݂̈ʒu
	D3DXVECTOR3 posold;		//�O��̈ʒu
	D3DXVECTOR3 move;		//�ړ���
	float        fwidth;	//��
	float       fheigth;	//�c
	int nCounterAnim;		
	int nPatternAnim;
	int nCounterState;		//��ԊǗ��J�E���^�[
	int DirectionMove0;		//�E
	int nLife;				//�̗�
	bool bDisp;				//�g�p���Ă邩�ǂ���
	bool bJunp;				//�W�����v���Ă邩�ǂ���
	//Block *spBlock;			//�Ώۂ̃u���b�N�ւ̃|�C���^
	PLAYER state;
}Player;



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
Player *GetPlayer(void);

#endif // _PLAYER_H_
