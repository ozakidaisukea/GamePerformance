//=============================================================================
//
// ���S�̏��� [logo.h]
// Author : Ozaki
//
//=============================================================================
#ifndef _LOGO_H_
#define _LOGO_H_

#include "scene2D.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_LOGO (14)

//*****************************************************************************
// �N���X�錾
//*****************************************************************************
class CScene2D;

class CLogo : public CScene2D
{
public:
	CLogo();
	~CLogo();

	typedef enum
	{
		LOGO_TITLE = 0,
		LOGO_TUTORIAL,
		LOGO_RESULT,
		LOGO_GAMEOVER,
		LOGO_RANKING,
		LOGO_SYAKE,
		LOGO_TUTORIALHAKASE,
		LOGO_RANKINGNUMBER,
		LOGO_1,
		LOGO_2,
		LOGO_3,
		LOGO_4,
		LOGO_5,
		LOGO_SOUSA,
		ENEMY_MAX
	}LOGO_TYPE;

	static HRESULT Load(void);	// �ǂݍ���

	static void Unload(void);	// �J��

	HRESULT Init(D3DXVECTOR3 pos, float widtgh,float height, LOGO_TYPE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static	CLogo *Create(D3DXVECTOR3 pos, float widtgh, float height, LOGO_TYPE type);

private:

	D3DXVECTOR3				m_move;							// �ړ���
	float					m_rot = 0.0f;
	float					m_position = 0.0f;
	float					m_Addposition = 1.0f;
	LOGO_TYPE				m_Type;

	// ���L�e�N�X�`���ւ̃|�C���^
	static LPDIRECT3DTEXTURE9	m_pTexture[MAX_LOGO];		// �ۑ�����ꏊ
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff = NULL;			// ���_�o�b�t�@�ւ̃|�C���^

	CScene2D					*m_apScene2D[MAX_LOGO];

protected:

	float						m_Perjudgment;
};
#endif