//=============================================================================
//
// �G���� [enemy.h]
// Author : Ozaki
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_ENEMY	(256)	// �G�̍ő吔

//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//�񋓌^
typedef enum
{
	ENEMYSTATE_NORMAL = 0,
	ENEMYSTATE_DAMAGE,
	ENEMYSTATE_MAX,
}ENEMYSTATE;

typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	int nType;				//���
	ENEMYSTATE state;		//�G�̏��
	int nCounterState;		//��ԊǗ��J�E���^�[
	int nLife;				//�̗�
	bool bUse;				//�g�p���Ă邩�ǂ���
	int nCounterAnim;		//�A�j���[�V�����J�E���^�[
	int nPatternAnim;		//�A�j���[�V�����p�^�[��
}Enemy;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void SetEnemy(D3DXVECTOR3 pos, int nType);
void HitEnemy(int nCntEnemy, int nDamage);
Enemy *GetEnemy(void);

#endif
