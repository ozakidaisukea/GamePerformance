//=============================================================================
//
// �X�R�A�̏��� [score.h]
// Author : Jukiya Hayakawa
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

#include "main.h"
#include "scene.h"

class CNumber;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CScore : public CScene
{
public:
	//�����o�֐�
	CScore();
	~CScore();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetScore(int nScore);
	int GetScore(void);
	void AddScore(int nValue);
	void SetCol(D3DXCOLOR col);
	D3DXCOLOR GetCol(void);
	//�ÓI�����o�֐�
	static CScore *Create(D3DXVECTOR3 pos, float fWight, float fHeight);

private:
	D3DXVECTOR3		m_pos;						// �ʒu
	float								m_fWight;
	float								m_fHeight;
	//�ÓI�����o�ϐ�
	CNumber			*m_apNumber[SCORE_DIGIT];	// �e�N�X�`���ւ̃|�C���^
	static int		m_nScore;
	D3DXCOLOR		m_col;
protected:
};
#endif