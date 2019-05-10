//=============================================================================
//
// �w�i�̏��� [Game.cpp]
// Author : Ozaki
//
//=============================================================================
#pragma once
#ifndef _Game_H_
#define _Game_H_

//*****************************************************************************
//�v���g�^�C�v�錾
//*****************************************************************************
typedef enum
{
	GAMESTATE_NONE = 0,			//�������Ă��Ȃ����
	GAMESTATE_NORMAL,			//�ʏ���
	GAMESTATE_END,				//�I�����
	GAMESTATE_BOSS,
	GAMESTATE_GAMEOVER,
	GAMESTATE_MAX,
}GAMESTATE;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);
void SetGameState(GAMESTATE state);
GAMESTATE GetGameState(void);

#endif // _Game_H_
