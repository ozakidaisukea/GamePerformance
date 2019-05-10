//=============================================================================
//
// �_���[�W�Q�[�W�̏��� [damagegauge.h]
// Author  Jukiya Hayakawa
//
//=============================================================================
#ifndef _DAMAGEGAUGE_H_
#define _DAMAGEGAUGE_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_DAMAGEGAUGE			(2)								// �Q�[�W�̑���

//*****************************************************************************
// �Q�[�W�̍\���̂̒�`
//*****************************************************************************
typedef enum
{
	STATE_NOMAL = 0,
	STATE_MINUS,
	STATE_MAX,
}DAMAGE_STATE;
typedef struct
{
	D3DXVECTOR3  pos;                       // �ʒu
	D3DXCOLOR	 col;						// �F
	float		 fWidth;					// ��
	float		 fHeight;					// ����
	int			 nType;						//�v���C���[�̎��
	DAMAGE_STATE state;						//���
}DamageGauge;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitDamageGauge(void);
void UninitDamageGauge(void);
void UpdateDamageGauge(void);
void DrawDamageGauge(void);
void SetDamageGaugeState(DAMAGE_STATE state,int nType,float fWidth);
#endif