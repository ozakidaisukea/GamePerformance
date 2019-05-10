//=============================================================================
//
// �e���� [dokan.h]
// Author : ozaki
//
//=============================================================================
#ifndef _DOKAN_H_
#define _DOKAN_H_

#include "main.h"
//*****************************************************************************
// �u���b�N�̎��
//*****************************************************************************
typedef enum
{
	DokanType_Dokan,			// �y��

}Dokan_TYPE;

typedef struct
{
	D3DXVECTOR3 pos;			// �ʒu
	D3DXVECTOR3 move;			// �ړ�
	float    fwidth;			// ��
	float	fheight;			// ����
	bool       bUse;			// �g�p���Ă邩�ǂ���
	Dokan_TYPE type;			// �u���b�N�̃^�C�v
	int    nCntItem;			// 
	int       nType;
}Dokan;

typedef struct
{
	D3DXVECTOR3 pos;			// �ʒu
	float    fwidth;			// ��
	float	fheight;			// ����
	Dokan_TYPE type;			// �u���b�N�̃^�C�v
}DokanInfo;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitDokan(void);
void UninitDokan(void);
void UpdateDokan(void);
void DrawDokan(void);
void SetDokan(D3DXVECTOR3 pos, float fwidth, float fheigth, Dokan_TYPE type);
bool CollisionDokan(D3DXVECTOR3 *pPos, D3DXVECTOR3*pPosOld, D3DXVECTOR3 *pMove, float fwigth, float fheigth);

#endif