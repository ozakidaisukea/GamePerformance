//=============================================================================
//
// �Q�[���I�[�o�[���� [gameover.h]
// Author : Ozaki
//
//=============================================================================
#ifndef _GAMEOVER_H_
#define _GAMEOVER_H_

#include "scene2D.h"
#include "score.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define Title_WIDTH		(SCREEN_WIDTH)
#define Title_HEIGHT	(SCREEN_HEIGHT)

//*****************************************************************************
// �N���X�錾
//*****************************************************************************
class CFade;

class CGameover
{
public:

	CGameover();
	~CGameover();

	HRESULT Load(void);	// �ǂݍ���

	void Unload(void);	// �J��

	static CGameover *Create(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:

	static LPDIRECT3DTEXTURE9			m_pTexture;
	static LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;
};
#endif

