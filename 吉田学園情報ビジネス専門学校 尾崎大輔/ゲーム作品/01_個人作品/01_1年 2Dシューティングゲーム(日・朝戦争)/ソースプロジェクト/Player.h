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

//�񋓌^
typedef enum
{
	PLAYERSTATE_APPEAR = 0,
	PLAYERSTATE_NORMAL ,
	PLAYERSTATE_DAMAGE,
	PLAYERSTATE_DEATH,
	PLAYERSTATE_MAX,
}PLAYERSTATE;

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	PLAYERSTATE state;		//�G�̏��
	
	int nCounterState;		//��ԊǗ��J�E���^�[
	int nLife;				//�̗�
	bool bDisp;				//�g�p���Ă邩�ǂ���
}Player;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
Player *GetPlayer(void);
void HitPlayer(int nDamage);

#endif // _PLAYER_H_
