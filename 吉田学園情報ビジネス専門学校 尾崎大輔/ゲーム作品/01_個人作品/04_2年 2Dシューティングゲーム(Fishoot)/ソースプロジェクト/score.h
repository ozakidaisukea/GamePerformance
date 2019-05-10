//=============================================================================
//
// スコア処理 [score.h]
// Author : Ozaki
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

#include "scene2D.h"
#include "number.h"
#include "scene.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_SCORE (7)

//*****************************************************************************
// クラス宣言
//*****************************************************************************
class CNumber;

class CScore :public CScene
{
public:
	CScore();
	~CScore();

	static CScore*Create(D3DXVECTOR3 pos, float widtgh, float height);

	HRESULT Init(D3DXVECTOR3 pos, float widtgh, float height);
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);
	void	SetScore(int nScore);
	int 	GetScore(void);
	void    AddScore(int nValue);

private:

	CNumber *m_apNumber[MAX_SCORE];	// スコアの桁数
	int		 m_mScore;
	int		 m_mScoreda[MAX_SCORE];
};
#endif