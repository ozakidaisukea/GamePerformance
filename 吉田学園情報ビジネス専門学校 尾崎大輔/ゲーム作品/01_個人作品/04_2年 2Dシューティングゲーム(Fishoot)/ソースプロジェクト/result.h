//=============================================================================
//
// ���U���g���� [result.h]
// Author : Ozaki
//
//=============================================================================
#ifndef _RESULT_H_
#define _RESULT_H_

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

class CResult
{
public:

	CResult();
	~CResult();

	HRESULT Load(void);	// �ǂݍ���

	void Unload(void);	// �J��

	static CResult *Create(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:

	static LPDIRECT3DTEXTURE9			m_pTexture;
	static LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;
};
#endif

