//=============================================================================
//
// �`���[�g���A���̏��� [tutorial.h]
// Author : Jukiya Hayakawa
//
//=============================================================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

#include "main.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CTutorial
{
public:	//�N������A�N�Z�X�\
	//�����o�֐�
	CTutorial();
	~CTutorial();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	//�ÓI�����o�֐�
	static CTutorial *Create(void);

private:	//�����������A�N�Z�X�\
};
#endif