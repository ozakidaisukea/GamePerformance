//=============================================================================
//
// �����L���O�̏��� [ranking.h]
// Author : Jukiya Hayakawa
//
//=============================================================================
#ifndef _RANKING_H_
#define _RANKING_H_

#include "main.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CRanking
{
public:	//�N������A�N�Z�X�\
	//�����o�֐�
	CRanking();
	~CRanking();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	//�ÓI�����o�֐�
	static CRanking *Create(void);

private:	//�����������A�N�Z�X�\
	int m_nTimer;	//�^�C�}�[
};
#endif