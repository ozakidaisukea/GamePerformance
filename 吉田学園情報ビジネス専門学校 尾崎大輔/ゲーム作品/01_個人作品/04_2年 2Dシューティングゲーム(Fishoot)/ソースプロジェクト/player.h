//=============================================================================
//
//�v���C���[���� [player.h]
// Author : Ozaki
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "scene2D.h"

//*****************************************************************************
// �N���X�錾
//*****************************************************************************
class CBullet;
class CEffect;
class CSound;

class CPlayer : public CScene2D
{
public:

	typedef enum
	{
		PLAYERSTATE_APPEAR = 0,
		PLAYERSTATE_NORMAL,
		PLAYERSTATE_DAMAGE,
		PLAYERSTATE_DEATH,
		PLAYERSTATE_ULTIMATE,
		PLAYERSTATE_MAX,
	}PLAYERSTATE;

	CPlayer();
	~CPlayer();

	static HRESULT Load(void);	// �ǂݍ���

	static void Unload(void);	// �J��

	HRESULT Init(D3DXVECTOR3 pos, float widtgh, float height);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static PLAYERSTATE GetState(void);

	static PLAYERSTATE state;

	static  D3DXVECTOR3 GetPlayerPos(void);

	static	CPlayer *Create(D3DXVECTOR3 pos, float widtgh, float height);

private:
	float					m_rot = 0.0f;
	float					m_position = 0.0f;
	float					m_Addposition = 1.0f;
	static D3DXVECTOR3		m_pos;
	int						m_bullettime;
	bool					m_bool;
	int						m_effecttimer = 0;

	D3DXVECTOR3				m_posold;

	D3DXVECTOR3				m_move;

	static CBullet			*m_pBullet;

	// �T�E���h
	static CSound			*m_pSound;

	int						m_ultimatetimer;
	int						m_CountState;

	// ���L�e�N�X�`���ւ̃|�C���^
	static LPDIRECT3DTEXTURE9 m_pTexture;	// �ۑ�����ꏊ

protected:
};



//*****************************************************************************
//�v���C���[�̍\����
//*****************************************************************************

//�񋓌^


#endif // _PLAYER_H_
