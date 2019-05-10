//=============================================================================
//
// �Q�[���̏��� [game.h]
// Author : Mikiya Meguro
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"
#include "player.h"
#include "input.h"
#include "time.h"
//#include "item.h"
//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef enum
{
	GAMESTATE_NONE = 0,		//�����Ȃ����
	GAMESTATE_TUTORIAL,		//�`���[�g���A�����
	GAMESTATE_NORMAL,		//�ʏ���
	GAMESTATE_GAMECLEAR,	//�I�����
	GAMESTATE_GAMEOVER,		//�Q�[���I�[�o�[���
	GAMESTATE_RANKING,		//�����L���O���
	GAMESTATE_MAX			//��Ԃ̑���
}GAMESTATE;				//�񋓌^

//typedef struct
//{
//	D3DXVECTOR3 pos;		//���_���W
//	float	fWidth;			//��
//	float	fHeight;		//����
//	BLOCKSTATE BlockType;	//�u���b�N�^�C�v
//	int		moveCounter;
//}BlockInfo;

//typedef struct
//{
//	D3DXVECTOR3 pos;		//���_���W
//	D3DXCOLOR col;			//�J���[
//	ITEMTYPE ItemType;		//�A�C�e���^�C�v
//}ItemInfo;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);
void SetGameState(GAMESTATE state);
GAMESTATE GetGameState(void);
void SetGaugeState(bool bChange);

#endif
