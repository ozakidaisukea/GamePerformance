//=============================================================================
//
// �t�F�[�h���� [fade.h]
// Author : Ozaki
//
//=============================================================================
#ifndef _FADE_H_
#define _FADE_H_

#include "scene2D.h"
#include "score.h"
#include "manager.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define Title_WIDTH		(SCREEN_WIDTH)
#define Title_HEIGHT	(SCREEN_HEIGHT)

//*****************************************************************************
// �N���X�錾
//*****************************************************************************
class CFade
{
public:

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

	CFade();
	~CFade();

	HRESULT Load(void);	// �ǂݍ���

	void Unload(void);	// �J��

	static CFade *Create(void);

	HRESULT Init(CManager::MODE modeNext);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetFade(CManager::MODE modeNext);
	static FADE GetFade(void);

private:

	static FADE							m_fade;					// �t�F�[�h���
	static CManager::MODE				m_modeNext;				// ���̃��[�h
	static D3DXCOLOR					m_colorFade;			// �t�F�[�h�F
	static LPDIRECT3DTEXTURE9			m_pTexture;
	static LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;
};
#endif

