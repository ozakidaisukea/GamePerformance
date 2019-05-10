//=============================================================================
//
// �|�[�Y���� [pause.h]
// Author : Jukiya Hayakawa
//
//=============================================================================
#ifndef _PAUSE_H_
#define _PAUSE_H_

#include "main.h"
#include "scene.h"

#define MAX_PAUSE_SELECT     (SELECT_MAX)               // �|�[�Y�I���ł��鍀�ڂ̐�
#define MAX_PAUSE_TEXTURE	 (4)						// �|�[�Y�̃e�N�X�`������

class CScene2D;
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CPause
{
public:
	//*************************************
	// ���ڂ̏��
	//*************************************
	typedef enum
	{
		PAUSESELECT_NONE = 0,   // �I������Ă��Ȃ����
		PAUSESELECT_SELECT,     // �I������Ă�����
		PAUSESELECT_MAX
	}PAUSESELECT;

	typedef enum
	{
		SELECT_CONTINUE = 0,// �R���e�B�j���[
		SELECT_RETRY,		// �Q�[�����g���C
		SELECT_QUIT,		// �^�C�g���J��
		SELECT_MAX
	}SELECT;

	//�����o�֐�
	CPause();
	~CPause();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static HRESULT Load(void);
	static void Unload(void);

	//�ÓI�����o�֐�
	static CPause *Create(void);

private:
	//�����o�ϐ�
	CScene2D			*m_pScene2D;					//�I�u�W�F�N�g2D�̃|�C���^
	CScene2D			*m_apSelect[MAX_PAUSE_SELECT];	//�I�𐔕��̃I�u�W�F�N�g2D�̃|�C���^
	D3DXCOLOR			m_aCol[MAX_PAUSE_SELECT];		//�I�𐔕��̐F���
	float				m_fCol;							// �F�̕ω��Ɏg�p
	PAUSESELECT			m_aSelect[MAX_PAUSE_SELECT];	//�I����Ԃ̏��
	SELECT				m_select;
	int					m_nSelect;
	//�ÓI�����o�ϐ�
	static LPDIRECT3DTEXTURE9	m_apTexture[MAX_PAUSE_TEXTURE];	//�e�N�X�`���̃|�C���^
protected:
};
#endif