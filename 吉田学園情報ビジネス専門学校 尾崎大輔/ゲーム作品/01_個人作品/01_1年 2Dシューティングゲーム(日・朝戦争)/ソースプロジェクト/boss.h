//=============================================================================
//
// �G���� [boss.h]
// Author : Ozaki
//
//=============================================================================
#ifndef _BOSS_H_
#define _BOSS_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_BOSS	(256)	// �G�̍ő吔

//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//�񋓌^
typedef enum
{
	BOSSSTATE_NORMAL = 0,
	BOSSSTATE_DAMAGE,
	BOSSSTATE_MAX,
}BOSSSTATE;

typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	int nType;				//���
	BOSSSTATE state;		//�G�̏��
	int nCounterState;		//��ԊǗ��J�E���^�[
	int nLife;				//�̗�
	bool bUse;				//�g�p���Ă邩�ǂ���
	int nCounterAnim;		//�A�j���[�V�����J�E���^�[
	int nPatternAnim;		//�A�j���[�V�����p�^�[��
}Boss;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitBoss(void);
void UninitBoss(void);
void UpdateBoss(void);
void DrawBoss(void);
void SetBoss(D3DXVECTOR3 pos, int nType);
void HitBoss(int nCntBoss, int nDamage);
Boss *GetBoss(void);

#endif

