//=============================================================================
//
// ���S�̏��� [logo.h]
// Author : Ozaki
//
//=============================================================================
#ifndef _LOGO_H_
#define _LOGO_H_

#include "scene2D.h"
#include "scene.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_LOGO (5)

//*****************************************************************************
// �N���X�錾
//*****************************************************************************
class CLogo : public CScene2D
{
public:
	CLogo();
	~CLogo();

	typedef enum
	{
		LOGO_TITLE = 0,		// �^�C�g��
		LOGO_RESECARD,		// �o�n�\
		LOGO_TUTORIAL,		// �`���[�g���A��
		LOGO_RESULT,		// ���U���g
		LOGO_PRESSENTOR,	// �v���X�G���^�[
		ENEMY_MAX
	}LOGO_TYPE;

	typedef enum
	{
		LOGOSTATE_NONE = 0,		//�������
		LOGOSTATE_NORMAL,		//�ʏ�
		LOGOSTATE_MOVE,			//����
		LOGOSTATE_MAX,			//�ő吔
	}LOGOSTATE;

	static HRESULT Load(void);	// �ǂݍ���

	static void Unload(void);	// �J��

	HRESULT Init(D3DXVECTOR3 pos, float widtgh, float height, LOGO_TYPE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static	CLogo *Create(D3DXVECTOR3 pos, float widtgh, float height, LOGO_TYPE type);

private:

	D3DXVECTOR3				m_pos;							// �ʒu
	D3DXVECTOR3				m_move;							// �ړ���
	float					m_rot = 0.0f;
	float					m_position = 0.0f;
	float					m_Addposition = 1.0f;
	LOGO_TYPE				m_Type;							// �^�C�v
	LOGOSTATE				m_State;
	float					m_widtgh;						// ��
	float					m_height;						// �c
															// �v���X�G���^�[
	int						m_nCntEnter;
	float					m_fEnterTimer;


	// ���L�e�N�X�`���ւ̃|�C���^
	static LPDIRECT3DTEXTURE9	m_pTexture[MAX_LOGO];		// �ۑ�����ꏊ

	CScene2D					*m_apScene2D;

protected:

	float						m_Perjudgment;
};
#endif