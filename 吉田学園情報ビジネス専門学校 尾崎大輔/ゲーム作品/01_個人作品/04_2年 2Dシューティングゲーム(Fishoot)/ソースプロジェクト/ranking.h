//=============================================================================
//
// �����L���O���� [ranking.h]
// Author : Ozaki
//
//=============================================================================
#ifndef _RANKING_H_
#define _RANKING_H_

#include "scene2D.h"
#include "score.h"
#include "number.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define Title_WIDTH		(SCREEN_WIDTH)
#define Title_HEIGHT	(SCREEN_HEIGHT)
#define MAX_SCORE1		(8)
#define MAX_RANKING		(5)
//*****************************************************************************
// �N���X�錾
//*****************************************************************************
class CFade;
class CNumber;

class CRanking
{
public:

	CRanking();
	~CRanking();

	HRESULT Load(void);	// �ǂݍ���

	void Unload(void);	// �J��

	static CRanking *Create(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetScore(int nScore);
	void AddScore(int nValue);

private:

	static LPDIRECT3DTEXTURE9			m_pTexture;
	static LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;
	int									m_nRanking[MAX_RANKING];			// �X�R�A
	D3DXVECTOR3							m_posRanking;
	int									m_rankingtimer;
	static CScore						*m_apScore[MAX_RANKING];
	int									m_nRankingSave[MAX_RANKING];		// �X�R�A
};
#endif

