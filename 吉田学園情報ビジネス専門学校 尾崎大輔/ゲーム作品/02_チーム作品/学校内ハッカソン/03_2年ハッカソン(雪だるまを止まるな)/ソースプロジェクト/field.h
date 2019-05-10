//=============================================================================
//
// �t�B�[���h�̏��� [field.h]
// Author : Jukiya Hayakawa
//
//=============================================================================
#ifndef _FIELD_H_
#define _FIELD_H_

#include "main.h"
#include "scene3D.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CField : public CScene3D
{
public:	//�N������A�N�Z�X�\
	//�����o�֐�
	CField();
	~CField();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	//�ÓI�����o�֐�
	static CField *Create(D3DXVECTOR3 pos,float sizeX,float sizeZ);
	static HRESULT Load(void);
	static void Unload(void);

private:	//�����������A�N�Z�X�\
	//�ÓI�����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_pTexture;			//�e�N�X�`���ւ̃|�C���^
	//�����o�ϐ�
};
#endif
