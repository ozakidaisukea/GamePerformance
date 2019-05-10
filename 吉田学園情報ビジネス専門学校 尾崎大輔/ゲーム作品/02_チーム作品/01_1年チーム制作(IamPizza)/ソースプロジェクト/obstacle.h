//=============================================================================
//
// ��Q���̏��� [obstacle.h]
// Author : ���i�Y��
//
//=============================================================================
#ifndef _OBSTACLE_H_
#define _OBSTACLE_H_

#include "main.h"

//*****************************************************************************
// ���f���̍\����
//*****************************************************************************
typedef enum
{
	OBSTACLE_TYPE_PIZZA = 0,			// �s�U��
	OBSTACLE_TYPE_PIZZA_YOKO,			// �s�U�� ��
	OBSTACLE_TYPE_HOUSE000,				// ��0
	OBSTACLE_TYPE_HOUSE000_YOKO,		// ��0 ��
	OBSTACLE_TYPE_HOUSE001,				// ��1
	OBSTACLE_TYPE_HOUSE001_YOKO,		// ��1 ��
	OBSTACLE_TYPE_HOUSE002,				// ��2
	OBSTACLE_TYPE_HOUSE003,				// ��3 tatemono001.x
	OBSTACLE_TYPE_HOUSE003_YOKO,		// ��3 ��
	OBSTACLE_TYPE_HOUSE004,				// ��4 
	OBSTACLE_TYPE_HOUSE004_YOKO,		// ��4 ��
	OBSTACLE_TYPE_HOUSE005,				// ��5
	OBSTACLE_TYPE_HOUSE005_YOKO,		// ��5 ��
	OBSTACLE_TYPE_HOUSE006,				// ��6
	OBSTACLE_TYPE_HOUSE006_YOKO,		// ��6 ��
	OBSTACLE_TYPE_HOUSE007,				// ��7
	OBSTACLE_TYPE_HOUSE007_YOKO,		// ��7 ��
	OBSTACLE_TYPE_HOUSE008,				// ��8
	OBSTACLE_TYPE_HOUSE008_YOKO,		// ��8 ��
	OBSTACLE_TYPE_HOUSE009,				// ��9
	OBSTACLE_TYPE_HOUSE009_YOKO,		// ��9 ��
	OBSTACLE_TYPE_HAIKYO,				// �p��
	OBSTACLE_TYPE_POKKURUZOU,			// �|�b�N����
	OBSTACLE_TYPE_HOSPITAL,				// �a�@
	OBSTACLE_TYPE_HOSPITAL_YOKO,		// �a�@ ��
	OBSTACLE_TYPE_TEMPLE,				// �_�a
	OBSTACLE_TYPE_TEMPLE_YOKO,			// �_�a ��
	OBSTACLE_TYPE_SKYTREE,				// �X�J�C�c���[
	OBSTACLE_TYPE_PIZZASYATOU,			// �s�U�̎Γ�
	OBSTACLE_TYPE_OFFICE000,			// �I�t�B�X0
	OBSTACLE_TYPE_OFFICE001,			// �I�t�B�X1
	OBSTACLE_TYPE_OFFICE001_YOKO,		// �I�t�B�X1 ��
	OBSTACLE_TYPE_OFFICE002,			// �I�t�B�X2
	OBSTACLE_TYPE_OFFICE002_YOKO,		// �I�t�B�X2 ��
	OBSTACLE_TYPE_KAMINARIMON,			// ����
	OBSTACLE_TYPE_KAMINARIMON_YOKO,		// ���� ��
	OBSTACLE_TYPE_KOUZISYA,				// �H����
	OBSTACLE_TYPE_KOUZIHYOUSIKI,		// �W��
	OBSTACLE_TYPE_KOUZIHYOUSIKI_YOKO,	// �W��
	OBSTACLE_TYPE_KOUZIIN,				// �H����
	OBSTACLE_TYPE_KOUZIIN_YOKO,			// �H����
	OBSTACLE_TYPE_BRIST,				// �o���X�^
	OBSTACLE_TYPE_BRIST_YOKO,			// �o���X�^��
	OBSTACLE_TYPE_HAKASEHOUSE,			// ���m
	OBSTACLE_TYPE_HAKASEHOUSE_YOKO,		// ���m��
	OBSTACLE_TYPE_HAKASE,				// ���m��
	OBSTACLE_TYPE_HAKASE_YOKO,			// ���m�Ɖ�
	OBSTACLE_TYPE_USHI,					// ��
	OBSTACLE_TYPE_SAKU,					// ��
	OBSTACLE_TYPE_SAKU_YOKO,			// ��
	OBSTACLE_TYPE_TAMAGO,				// ���܂�����
	OBSTACLE_TYPE_TAMAGO_YOKO,			// ���܂�������
	OBSTACLE_TYPE_BASTAR,				// �o�X�^�[�\�[�h
	OBSTACLE_TYPE_BASTAR_YOKO,			// �o�X�^�[�\�[�h��
	OBSTACLE_TYPE_FLOUR,				// ��
	OBSTACLE_TYPE_FLOUR_YOKO,			// ��
	OBSTACLE_TYPE_TENGA,				// TENGA
	OBSTACLE_TYPE_KANBAN,				// �Ŕ�
	OBSTACLE_TYPE_KAISYA,				// ���
	OBSTACLE_TYPE_TUTI,					// �y
	OBSTACLE_TYPE_POKUTANK,				// �|�b�N���^���N
	OBSTACLE_TYPE_POPUTANK,				// �|�v�^���N
	OBSTACLE_TYPE_MAX,
}OBSTACLE_TYPE;



typedef struct
{
	D3DXVECTOR3 pos;							// �ʒu
	D3DXVECTOR3 rot;							// ����
	D3DXVECTOR3 move;							// �ړ���
	int			nIdxShadow;						// �e
	OBSTACLE_TYPE	nType;						// ���
	D3DXMATRIX	mtxWorld;						// ���[���h�}�g���b�N�X
	float fDestAngle;							// �v���C���[�̊p�x
	float fDiffAngle;							// ����
	int nLife;									// ���C�t
	bool bUse;									// �g�p���Ă��邩�ǂ���
	float fLength;								// �J�����ƃ��f���Ƃ̋���
	float fLengthPlayer;						// �v���C���[�Ƃ̋���
	D3DXVECTOR3 LengthMax;
	D3DXVECTOR3 LengthMin;
	D3DXVECTOR3	vtxMinObstacle, vtxMaxObstacle;	// ���f���̍ŏ��l�A�ő�l
	D3DXVECTOR3	vtxMinBike, vtxMaxBike;			// �o�C�N���̓����蔻��
}OBSTACLE;

typedef struct
{
	D3DXVECTOR3 pos;		// �ʒu
	D3DXVECTOR3 rot;        // ����
	D3DXVECTOR3 move;		// �ړ���
	OBSTACLE_TYPE nType;	// ���
}OBSTACLE_INFO;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitObstacle(void);
void UninitObstacle(void);
void UpdateObstacle(void);
void DrawObstacle(void);
OBSTACLE *GetObstacle(void);
void SetObstacle(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType);
bool CollisionObstacle(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove,D3DXVECTOR3 radius);
bool CollisionObstacleBike(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 radius);

#endif
