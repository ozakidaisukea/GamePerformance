//=============================================================================
//
// �w�i�̏��� [bg.h]
// Author : Ozaki
//
//=============================================================================
#ifndef _BG_H_
#define _BG_H_

#include "scene.h"
#include "title.h"
#include "result.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_BG		(3)		// �w�i�̍ő吔

//*****************************************************************************
// �N���X�錾
//*****************************************************************************
class CScene2D;

class CBg :public CScene
{
public:

	typedef enum
	{
		MODE_TITLE = 0,		// �^�C�g��
		MODE_GAME,			// �Q�[��
		MODE_RESULT,		// ���U���g
		MODE_GAMEOVER,		// �Q�[���I�[�o�[
		MODE_RANKING,		// �����L���O
		MODE_TUTORIAL,		// �`���[�g���A��
		MODE_MAX
	}MODE;

	CBg();
	~CBg();

	static HRESULT Load(void);	// �ǂݍ���

	static void Unload(void);	// �J��

	static	CBg *Create(D3DXVECTOR3 pos, float widtgh, float height);

	HRESULT Init(D3DXVECTOR3 pos, float widtgh, float height);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// ���[�h�̐ݒ�
	static void SetMode(MODE mode);

private:

	// ���[�h
	static MODE m_mode;

	// ���L�e�N�X�`���ւ̃|�C���^
	static LPDIRECT3DTEXTURE9	m_apTexture[MAX_BG];	// �ۑ�����ꏊ
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;

	D3DXVECTOR3					m_move;					//�ړ���
	CScene2D					*m_apScene2D[MAX_BG];

	float						m_fTex;
protected:

	int							m_nCounterAnim;				//�A�j���[�V�����J�E���^�[
	int							m_nPatternAnim;				//�A�j���[�V�����p�^�[��
};
#endif