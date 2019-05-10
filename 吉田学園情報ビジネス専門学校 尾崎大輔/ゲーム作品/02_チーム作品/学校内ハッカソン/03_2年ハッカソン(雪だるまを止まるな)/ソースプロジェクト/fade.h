//=============================================================================
//
// �t�F�[�h�̏��� [fade.h]
// Author : Jukiya Hayakawa
//
//=============================================================================
#ifndef _FADE_H_
#define _FADE_H_

#include "main.h"
#include "scene.h"
#include "manager.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CFade
{
public:	//�N������A�N�Z�X�\
	//*************************************
	// �t�F�[�h�̏��
	//*************************************
	typedef enum
	{
		FADE_NONE = 0,		// �������Ă��Ȃ����
		FADE_IN,			// �t�F�[�h�C�����
		FADE_OUT,			// �t�F�[�h�A�E�g���
		FADE_MAX
	} FADE;

	//�����o�֐�
	CFade();
	~CFade();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void SetFade(CManager::MODE modeNext, FADE fade);
	FADE GetFade(void);				//�t�F�[�h�̎擾����

	//�ÓI�����o�֐�
	static CFade *Create(void);

private:	//�����������A�N�Z�X�\
	//�����o�ϐ�
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DTEXTURE9			m_pTexture = NULL;	// �e�N�X�`���ւ̃|�C���^

	//�ÓI�����o�ϐ�
	static FADE					m_fade;				//�t�F�[�h
	static CManager::MODE		m_modeNext;			//���̃��[�h�̏��
	static D3DXCOLOR			m_colorFade;		//�t�F�[�h�̐F
};
#endif