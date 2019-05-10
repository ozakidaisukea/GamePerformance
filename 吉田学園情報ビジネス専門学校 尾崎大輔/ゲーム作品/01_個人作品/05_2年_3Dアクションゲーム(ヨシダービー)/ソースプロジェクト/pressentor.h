//=============================================================================
//
// �v���X�G���^�[�̏��� [Pressentor.h]
// Author : Ozaki
//
//=============================================================================
#ifndef _PRESSENTOR_H_
#define _PRESSENTOR_H_

#include "scene2D.h"
#include "logo.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_ENTOR (8)

//*****************************************************************************
// �N���X�錾
//*****************************************************************************
class CPressEntor : public CLogo
{
public:
	CPressEntor();
	~CPressEntor();

	static HRESULT Load(void);	// �ǂݍ���

	static void Unload(void);	// �J��

	HRESULT Init(D3DXVECTOR3 pos, float widtgh, float height);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static	CPressEntor *Create(D3DXVECTOR3 pos, float widtgh, float height);

private:

	D3DXVECTOR3						m_move;							// �ړ���
	float							m_rot = 0.0f;
	float							m_position = 0.0f;
	D3DXVECTOR3						m_pos;
	float							m_flength;
	// �v���X�G���^�[
	int								m_nCntEnter = 0;
	float							m_fEnterTimer = 0.0f;

	// ���L�e�N�X�`���ւ̃|�C���^
	static LPDIRECT3DTEXTURE9		m_pTexture;					// �ۑ�����ꏊ
	LPDIRECT3DVERTEXBUFFER9			m_pVtxBuff = NULL;			// ���_�o�b�t�@�ւ̃|�C���^

	CScene2D						*m_apScene2D;

protected:

	float							m_Perjudgment;
};
#endif