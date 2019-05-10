//=============================================================================
//
// �`���[�g���A������ [tutorial.h]
// Author : Ozaki
//
//=============================================================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

#include "scene2D.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TUTORIAL_WIDTH		(SCREEN_WIDTH)
#define TUTORIAL_HEIGHT		(SCREEN_HEIGHT)

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
class CLogo;
class CInputjoypad;

class CTutorial
{
public:

	typedef enum
	{
		TUTORIALSTATE_NONE = 0,			//�������Ă��Ȃ����
		TUTORIALSTATE_NORMAL,			//�ʏ���
		TUTORIALSTATE_END,				//�I�����
		TUTORIALSTATE_GAMEOVER,
		TUTORIALSTATE_MAX,
	}TUTORIALSTATE;

	CTutorial();
	~CTutorial();

	HRESULT Load(void);	// �ǂݍ���

	void Unload(void);	// �J��

	static CTutorial *Create(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �v���C���[
	static CPlayer *GetPlayer(void);

	// ���S
	static CLogo *GetLogo(void);

private:

	// �v���C���[
	static CPlayer *m_pPlayer;

	// ���S
	static CLogo *m_pLogo;

	static LPDIRECT3DTEXTURE9			m_pTexture;
	static LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;
	int									m_nCounterTutorialState;
	int									m_Tutorial;

};
#endif

