//=============================================================================
//
// �e���� [block.h]
// Author : ozaki
//
//=============================================================================
#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "main.h"
//*****************************************************************************
// �u���b�N�̎��
//*****************************************************************************
typedef enum
{
	BlockType_Normal,			// �m�[�}��
	BlockType_Dokan,			// �y��
	BlockType_Beltconveyor,		// �x���g�R���x�A�[
	BlockType_Ice,				// �X��
	BlockType_Question1,		// �H�u���b�N1
	BlockType_Question2,		// �H�u���b�N2
	BlockType_Move,				// �ړ���
	BlockType_Junp,				// �W�����v��
	BlockType_Isi,				// �΃u���b�N

}BLOCK_TYPE;

typedef struct
{
	D3DXVECTOR3 pos;			// �ʒu
	D3DXVECTOR3 move;			// �ړ�
	float    fwidth;			// ��
	float	fheight;			// ����
	bool       bUse;			// �g�p���Ă邩�ǂ���
	BLOCK_TYPE type;			// �u���b�N�̃^�C�v
	int    nCntItem;			// 
	int       nType;
}Block;

typedef struct
{
	D3DXVECTOR3 pos;			// �ʒu
	float    fwidth;			// ��
	float	fheight;			// ����
	BLOCK_TYPE type;			// �u���b�N�̃^�C�v
}BlockInfo;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitBlock(void);
void UninitBlock(void);
void UpdateBlock(void);
void DrawBlock(void);
Block *GetBlock(void);
void SetBlock(D3DXVECTOR3 pos,float fwidth,float fheigth, BLOCK_TYPE type);
bool CollisionBlock(D3DXVECTOR3 *pPos, D3DXVECTOR3*pPosOld,D3DXVECTOR3 *pMove, float fwigth,float fheigth);

#endif