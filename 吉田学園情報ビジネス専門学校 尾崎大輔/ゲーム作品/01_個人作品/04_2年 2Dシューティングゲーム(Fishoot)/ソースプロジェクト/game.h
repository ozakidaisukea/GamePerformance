//=============================================================================
//
// �Q�[������ [game.h]
// Author : Ozaki
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "scene2D.h"
#include "score.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define GAME_WIDTH		(SCREEN_WIDTH)
#define GAME_HEIGHT		(SCREEN_HEIGHT)
#define MAX_ENEMY		(5)
#define MAX_GAUGE		(3)
#define ENEMYLIFE_NO1	(3)
#define ENEMYLIFE_NO2	(5)
#define ENEMYLIFE_NO3	(10)
#define ENEMYLIFE_NO4	(15)
#define ENEMYLIFE_NO5	(40)

//*****************************************************************************
// �N���X�錾
//*****************************************************************************
class CBullet;
class CRenderer;
class CInputKeyboard;
class CPlayer;
class CExplosion;
class CScore;
class CLife;
class CEffect;
class CEnemy;
class CLIfe;
class CFade;
class CItem;
class CGauge;

class CGame
{
public:

	typedef enum
	{
		STATE_NONE = 0,			//�������Ă��Ȃ����
		STATE_NORMAL,			//�ʏ���
		STATE_RESULT,			//�I�����
		STATE_GAMEOVER,
		STATE_MAX,
	}STATE;

	CGame();
	~CGame();

	void Load(void);	// �ǂݍ���

	void Unload(void);	// �J��

	static CGame *Create(void);

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �v���C���[
	static CPlayer *GetPlayer(void);

	// �G
	static CEnemy *GetEnemy(int nIdx);

	static void SetEnemy(int nIdx, CEnemy* pEnemy);

	// �X�R�A
	static CScore *GetScore(void);

	// ���C�t
	static CLife *GetLife(void);

	// �A�C�e��
	static CItem *GetItem(void);

	// �Q�[�W
	static CGauge *GetGauge(void);

	int GetNumEnemy(void);
	int GetNumEnemyAll(void);

	void SetNumEnemy(int nNumEnemy);
	void SetNumEnemyAll(int nNumEnemyAll);
	static void SetState(STATE state);

	void SetEnemy(void);

private:

	void	SetEnemy00(void);
	void	SetEnemy01(void);
	void	SetEnemy02(void);
	void	SetEnemy03(void);
	void	SetEnemy04(void);


	static LPDIRECT3DTEXTURE9			m_pTexture;
	static LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;
	int									m_nCounterGameState;
	//static int							m_Creattimer;


	// �v���C���[
	static CPlayer *m_pPlayer;

	// �G
	static CEnemy *m_pEnemy[MAX_ENEMY];

	// �X�R�A
	static CScore *m_pScore;

	// ���C�t
	static CLife *m_pLife;

	// �A�C�e��
	static CItem *m_pItem;

	// �Q�[�W
	static CGauge *m_pGauge[MAX_GAUGE];

	static STATE m_State;
	int	m_nNumEnemy;
	int m_nNumEnemyAll;
	int	m_nIndex;
	int	m_ItemTimer;

};
#endif

