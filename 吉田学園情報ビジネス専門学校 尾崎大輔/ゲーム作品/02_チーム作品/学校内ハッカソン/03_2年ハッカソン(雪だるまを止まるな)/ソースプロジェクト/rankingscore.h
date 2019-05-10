//=============================================================================
//
// �����L���O�X�R�A�̏��� [rankingscore.h]
// Author : Jukiya Hayakawa
//
//=============================================================================
#ifndef _RANKINGSCORE_H_
#define _RANKINGSCORE_H_

#include "main.h"
#include "scene.h"
class CScore;
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_RANKINGSCORE        (5)             // �����L���O�X�R�A�̐�

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CRankingScore : public CScene
{
public:
	//=========================================================================
	// �\���̂̒�`
	//=========================================================================
	typedef enum
	{
		RANKINGSCORESTATE_NONE = 0, // �X�V����Ă��Ȃ����
		RANKINGSCORESTATE_UPDATE,   // �X�V���ꂽ���
		RANKINGSCORESTATE_MAX
	}RANKINGSCORESTATE;


	//�����o�֐�
	CRankingScore();
	~CRankingScore();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	//RANKINGSCORE *GetRankingScore(void);
	//�ÓI�����o�֐�
	static CRankingScore *Create(D3DXVECTOR3 pos, float fWight, float fHeight);

private:
	D3DXVECTOR3		m_pos;				// �ʒu
	float			m_fWight;
	float			m_fHeight;
	CScore			*m_apScore[MAX_RANKINGSCORE];	// �e�N�X�`���ւ̃|�C���^
	static int		m_aRankingScore[MAX_RANKINGSCORE];
	int				m_nCountCol;
	D3DXCOLOR		m_col;
};
#endif