//=============================================================================
//
// ���U���g�̏��� [result.h]
// Author : Jukiya Hayakawa
//
//=============================================================================
#ifndef _RESULT_H_
#define _RESULT_H_

#include "main.h"

#define MAX_RESULT (RESULT_MAX)	//���U���g�̐�

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CResult
{
public:	//�N������A�N�Z�X�\
	//=========================================================================
	// �\���̂̒�`
	//=========================================================================
	typedef enum
	{
		RESULT_NONE = 0,
		RESULT_CLEAR,		//�N���A
		RESULT_GAMEOVER,	//�Q�[���I�[�o�[
		RESULT_MAX,
	}RESULT;
	//�����o�֐�
	CResult();
	~CResult();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetResult(RESULT result);
	RESULT GetResult(void);

	//�ÓI�����o�֐�
	static CResult *Create(void);

private:	//�����������A�N�Z�X�\
	//�����o�ϐ�
	int m_nTimer;			//�^�C�}�[

	//�ÓI�����o�ϐ�
	static RESULT m_result;	//���U���g�̏��
};
#endif