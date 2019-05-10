//=============================================================================
//
// 敵の処理 [enemy.h]
// Author : Ozaki
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "scene2D.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_ENEMY (5)
#define MAX_BULLETSPEED (15)
//*****************************************************************************
// クラス宣言
//*****************************************************************************
class CBullet;
class CLife;
class CGauge;
class CPalyer;
class CSound;

class CEnemy : public CScene2D
{
public:
	CEnemy();
	~CEnemy();

	typedef enum
	{
		ENEMY_TORI = 0,
		ENEMY_BIKE,
		ENEMY_BOARD,
		ENEMY_GYOSEN,
		ENEMY_UTYUSEN,
		ENEMY_MAX
	}ENEMY_TYPE;

	typedef enum
	{
		ENEMYSTATE_NORMAL,
		ENEMYSTATE_DEATH,
		ENEMYSTATE_DAMAGE,
		ENEMYSTATE_MAX,
	}ENEMYSTATE;

	static HRESULT Load(void);	// 読み込み
	static void Unload(void);	// 開放

	HRESULT Init(D3DXVECTOR3 pos, float widtgh, float height,D3DXVECTOR3 move,int life, ENEMY_TYPE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void HitEnemy(int nDamage);


	static	CEnemy *Create(D3DXVECTOR3 pos, float widtgh,float height, D3DXVECTOR3 move, int life,ENEMY_TYPE type);

	int						m_nLife;
	static int				m_nCounterEnemyState;		//状態管理カウンター
	ENEMY_TYPE				m_Type;

	static int				m_enemyall;

private:

	D3DXVECTOR3				m_move;						// 移動量
	float					m_rot = 0.0f;				// 向き
	float					m_position = 0.0f;			// 位置，方向，姿勢
	float					m_Addposition = 1.0f;		// positionに加える
	int						m_bullettime = 0;

	int						m_CountState;
	bool m_bUse;
	// サウンド
	static CSound			*m_pSound;

	// 共有テクスチャへのポインタ
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_ENEMY];	// 保存する場所

protected:

	float					m_Perjudgment;
public:
	ENEMYSTATE state;

};
#endif