//=============================================================================
//
// �Q�[�W�̏��� [gauge.h]
// Author  Jukiya Hayakawa
//
//=============================================================================
#ifndef _ULTGAUGE_H_
#define _ULTGAUGE_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_ULTGAUGE			(2)								// �Q�[�W�̑���
#define ULTGAUGE_WIDTH		(230)								// �Q�[�W�̕�

//*****************************************************************************
// �Q�[�W�̍\���̂̒�`
//*****************************************************************************
typedef enum
{
	ULTGAUGE_NOMAL = 0,			//�ʏ���
	ULTGAUGE_READY,				//�g�p�\���
	ULTGAUGE_USE,				//�g�p���
	ULTGAUGE_MAX,
}ULTGAUGE_STATE;
typedef struct
{
	D3DXVECTOR3  pos;                       // �ʒu
	D3DXCOLOR	 col;						// �F
	float		 fWidth;					// ��
	float		 fHeight;					// ����
	int			 nType;						// �v���C���[�̎��
	ULTGAUGE_STATE state;					// ���

}UltGauge;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitUltGauge(void);
void UninitUltGauge(void);
void UpdateUltGauge(void);
void DrawUltGauge(void);
void SetUltGauge(float fWidth, int nType);
void SetUltGaugeState(ULTGAUGE_STATE state, int nType);
float GetUltGaugeWidth(int nType);
void UseUltGauge(int nType);
ULTGAUGE_STATE GetUltGaugeState(int nType);
#endif