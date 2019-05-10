//=============================================================================
//
// �v���C���[�̏��� [playerl.h]
// Author : Shun Yokomicho
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
#include "polygon.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MOVE_SIN_COS_TOP	(0.75f)							//�|���S���ړ���
#define MOVE_SIN_COS_BOT	(0.25f)							//�|���S���ړ���
#define FIELD_MAX_SIZE		(FIELD_SIZE - 10)
#define PLAYER_PARTS		(10)							//�v���C���[�p�[�c��

typedef enum
{
	PLAYERSTATE_NORMAL = 0,		// �ʏ���
	PLAYERSTATE_AWAKENING,		// Pizza���[�h���
	PLAYERSTATE_EAT,			// Pizza���H�ׂ�����
	PLAYERSTATE_GAUGEZERO,		// Gauge��0�̏ꍇ
	PLAYERSTATE_DIE,			// �v���C���[���ǂɂԂ���ꍇ
	PLAYERSTATE_MAX,			// ��Ԃ̑���
}PLAYERSTATE;

typedef enum
{
	CHANGESTATE_POSSIBLE = 0,	// �ϐg�\���
	CHANGESTATE_IMPOSSIBLE,		// �ϐg�s���
	CHANGESTATE_MAX,			// ��Ԃ̑���
}CHANGESTATE;

typedef enum
{
	PLAYERPIZZA_HUMAN = 0,	// �l�ԏ��
	PLAYERPIZZA_PIZZA,		// �s�U���
	PLAYERPIZZA_MAX,		// ��Ԃ̑���
}PLAYERPIZZA;

typedef enum
{
	PALYERTYPE_STOP = 0,
	PALYERTYPE_WAIK,
	PALYERTYPE_MAX
}PALYERTYPE;

typedef struct
{
	D3DXVECTOR3  pos;			// ���݂̈ʒu
	D3DXVECTOR3  posOld;		// �ߋ��̈ʒu
	D3DXVECTOR3  move;			// �ړ�
	D3DXVECTOR3	 rot;			// �ʏ��� && Pizza��ԏc�̌���(����)
	D3DXVECTOR3	 rotPizza;		// Pizza��ԉ��̌���(����)
	D3DXVECTOR3	 rotDest;		// ����(�ړI)
	D3DXVECTOR3	 rotPizzaDest;	// Pizza��ԉ��̌���(�ړI)
	D3DXVECTOR3	 DiffAngle;		// ����(�v���C���[�̌����̍���) 
	D3DXVECTOR3  DiffAnglePizza;// ����(Pizza�̌����̍���)
	D3DXVECTOR3  vtxMin;		// ���f���̍ŏ��l
	D3DXVECTOR3  vtxMax;		// ���f���̍ő�l
	D3DXMATRIX	 mtxWorld;		// ���[���h�}�g���b�N�X
	PLAYERSTATE  state;			// �v���C���[�̏��
	PALYERTYPE	type;			// �v���C���[�̎��
	LPD3DXMESH	 pMesh; 		//���b�V�����ւ̃|�C���^
	LPD3DXBUFFER pBuffMat;		// �}�e���A�����ւ̃|�C���^
	DWORD		nNumMat;		// �}�e���A���̏��
	int		nIdyShadow;			// �e�̔ԍ�
	int rotnum;					// �v���C���[�̌����̋L��
	float fXaxis;				// X��
	float fZaxis;				// Z��
	bool bUse;					// �g���Ă��邩�ǂ���
	CHANGESTATE ChangeState;	// �ϐg�\���ǂ���
	D3DXVECTOR3  vtxMinBike;	// �o�C�N���̍ŏ��l
	D3DXVECTOR3  vtxMaxBike;	// �o�C�N���̍ő�l
	PLAYERPIZZA PizzaMode;
}PLAYER;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
PLAYER *GetPlayer(void);

#endif