//=============================================================================
//
// �|�b�N������ [pokuru.h]
// Author : Meguro Mikiya
//
//=============================================================================
#ifndef _POKURU_H_
#define _POKURU_H_

#include "main.h"
#include "polygon.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define POKURU_NAME		 "data\\MODEL\\�|�b�N��\\karada.x"		//�e�N�X�`���̃t�@�C����
#define POKURU_NAME1	 "data\\MODEL\\�|�b�N��\\kao.x"		//�e�N�X�`���̃t�@�C����
#define POKURU_NAME2	 "data\\MODEL\\�|�b�N��\\migiude.x"		//�e�N�X�`���̃t�@�C����
#define POKURU_NAME3	 "data\\MODEL\\�|�b�N��\\migite.x"		//�e�N�X�`���̃t�@�C����
#define POKURU_NAME4	 "data\\MODEL\\�|�b�N��\\hidariude.x"		//�e�N�X�`���̃t�@�C����
#define POKURU_NAME5	 "data\\MODEL\\�|�b�N��\\hidarite.x"		//�e�N�X�`���̃t�@�C����
#define POKURU_NAME6	 "data\\MODEL\\�|�b�N��\\migimomo.x"		//�e�N�X�`���̃t�@�C����
#define POKURU_NAME7	 "data\\MODEL\\�|�b�N��\\migiashi.x"		//�e�N�X�`���̃t�@�C����
#define POKURU_NAME8	 "data\\MODEL\\�|�b�N��\\hidarimomo.x"		//�e�N�X�`���̃t�@�C����
#define POKURU_NAME9	 "data\\MODEL\\�|�b�N��\\hidariashi.x"		//�e�N�X�`���̃t�@�C����
#define POKURU_NAME10	 "data\\MODEL\\�|�b�N��\\99_hat.x"		//�e�N�X�`���̃t�@�C����
#define POKURU_NAME11	 "data\\MODEL\\���.x"			//�e�N�X�`���̃t�@�C����

#define MOVE_POKURU			(0.3f)							//�|�b�N���ړ���
#define MOVE_SIN_COS_TOP	(0.75f)							//�|���S���ړ���
#define MOVE_SIN_COS_BOT	(0.25f)							//�|���S���ړ���
#define FIELD_MAX_SIZE		(FIELD_SIZE - 10)
#define POKURU_PARTS		(10)							//�|�b�N���p�[�c��
//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef enum
{
	POKURUSTATE_APPEAR = 0,	//���G
	POKURUSTATE_NORMAL,		//�ʏ���
	POKURUSTATE_STOP,		//�ʏ���
	POKURUSTATE_MOVE,		//�ʏ���
	POKURUSTATE_DAMAGE,		//�_���[�W���
	POKURUSTATE_DEATH,		//���S
	POKURUSTATE_MAX			//��Ԃ̑���
}POKURUSTATE;				//�񋓌^

typedef struct
{
	LPD3DXMESH pMesh;			//���b�V�����ւ̃|�C���^
	LPD3DXBUFFER pBuffMat;		//�}�e���A�����ւ̃|�C���^
	DWORD nNumMat;				//�}�e���A�����̐�
	D3DXMATRIX mtxWorld;		//���[���h�}�g���b�N�X
	D3DXVECTOR3 pos;			//�ʒu
	D3DXVECTOR3 rot;			//����
	int nIdxModelParent;		//�e���f���̃C���f�b�N�X
}Model;

typedef struct
{
	DWORD nNumMatPokuru = 0;			//�}�e���A�����̐�
	D3DXVECTOR3 pos;					//�ʒu
	D3DXVECTOR3 posold;					//�O��̈ʒu
	D3DXVECTOR3 move;					//�ړ���
	D3DXVECTOR3 rot;					//����
	D3DXMATRIX	mtxWorld;				//���[���h�}�g���b�N�X
	float fShadow;						//�e�̑傫��
	int nIdxShadow;						//�e�̃C���f�b�N�X
	float fDestAngle;					//�|�b�N���̊p�x
	float fDiffAngle;					//����
	float fWidth;
	float fHeight;
	POKURUSTATE state;					//�|�b�N���̏��
	D3DXVECTOR3 VtxMin, VtxMax;			//�|�b�N���ŏ��l�A�ő�l
	float fLength;
	Model aModel[POKURU_PARTS];			//���f���̃p�[�c��
} POKURU;


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitPokuru(void);
void UninitPokuru(void);
void UpdatePokuru(void);
void DrawPokuru(void);
POKURU *GetPokuru(void);

#endif
