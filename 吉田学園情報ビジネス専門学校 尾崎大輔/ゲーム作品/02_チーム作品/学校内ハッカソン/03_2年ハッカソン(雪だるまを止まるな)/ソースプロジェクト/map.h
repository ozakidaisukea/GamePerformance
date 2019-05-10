//=============================================================================
//
// �}�b�v�̏���[map.h]
// Auther:Jukiya Hayakawa
//
//=============================================================================
#ifndef _MAP_H_
#define _MAP_H_

#include "main.h"

//�O���錾
class CModelCreate;

//*****************************************************************************
// �}�N����`
//*****************************************************************************

class CObject;
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CMap
{
public:    // �N������A�N�Z�X�\
	CMap();
	~CMap();
	void Init(void);
	void Uninit(void);

	//�ÓI�����o�֐�
	static CMap *Create(void);
private:   //�����������A�N�Z�X�\
	void SaveObject(void);
	void FieldLoad(char *pFieldFileName, char *pStrCur, char *pLine);
	void LoadObject(char *pFileNameObject, char *pStrCur, char *pLine);

	CModelCreate		*m_pModelCreate;		// ���f�������̃|�C���^
};

#endif