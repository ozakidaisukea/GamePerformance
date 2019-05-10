//=============================================================================
//
// �e���� [item.h]
// Author : ozaki
//
//=============================================================================
#ifndef _ITEM_H_
#define _ITEM_H_

#include "main.h"

//*****************************************************************************
//�A�C�e���̍\����
//*****************************************************************************
typedef enum
{
	ITEMSTATE_COIN = 0,		// �R�C��
	ITEMSTATE_MUSHROOMS,	// �L�m�R
	ITEMSTATE_BIGMUSHROOMS,	// �r�b�O�L�m�R
	ITEMSTATE_MAX,
}ITEMTYPE;

typedef struct
{
	D3DXVECTOR3 pos;		//���݂̈ʒu
	D3DXVECTOR3 posold;		//�O��̈ʒu
	D3DXVECTOR3 move;		//�ړ���
	D3DXVECTOR3 col;		//�F
	float fwidth;			//����
	float fheigth;			//�c��
	int       nType;
	int nCounterAnim;		//�A�j���[�V�����J�E���^�[
	int nPatternAnim;		//�A�j���[�V�������p�^�[����
	ITEMTYPE type;			//���
	bool bUse;				//�g�p���Ă邩�ǂ���
}Item;

typedef struct
{
	D3DXVECTOR3 pos;		// ���݂̈ʒu
	float fwidth;			// ����
	float fheigth;			// �c��
	ITEMTYPE type;			// ���

}ItemInfo;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitItem(void);
void UninitItem(void);
void UpdateItem(void);
void DrawItem(void);
void SetItem(D3DXVECTOR3 pos, float fwidth, float fheigth, ITEMTYPE type);
Item *GetItem(void);
void CollisionItem(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pMove, float fwidth,float fheigth);
#endif
