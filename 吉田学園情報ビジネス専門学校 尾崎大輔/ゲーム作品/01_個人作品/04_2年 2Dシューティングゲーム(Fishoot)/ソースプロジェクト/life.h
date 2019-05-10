//=============================================================================
//
// ���C�t���� [life.h]
// Author : Ozaki
//
//=============================================================================
#ifndef _LIFE_H_
#define _LIFE_H_

#include "main.h"
#include "scene2D.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_LIFE (5)

//*****************************************************************************
// �N���X�錾
//*****************************************************************************
class CLIfeScene2D;

class CLife : public CScene
{
public:
	CLife();
	~CLife();

	static HRESULT Load(void);	// �ǂݍ���

	static void Unload(void);	// �J��

	HRESULT Init(D3DXVECTOR3 pos, float widtgh, float height);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void CutLife(int nLife);

	int GetLife(int nLife);

	static	CLife *Create(D3DXVECTOR3 pos, float widtgh, float height);

	CLIfeScene2D					*m_apScene2D[MAX_LIFE];

	int								 m_nLife;

private:

	// ���L�e�N�X�`���ւ̃|�C���^
	static LPDIRECT3DTEXTURE9		m_pTexture;	// �ۑ�����ꏊ
	LPDIRECT3DVERTEXBUFFER9			m_pVtxBuff;

};
#endif