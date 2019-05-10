//=============================================================================
//
// UI���� [ui.h]
// Author : YUTARO ABE
//
//=============================================================================
#ifndef _UI_H_
#define _UI_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"		// ���C��
#include "scene2d.h"	// �V�[��2D
#include "manager.h"	// �}�l�[�W���[

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define UI_TEXMAX		(16)

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CUI : public CScene2D
{// UI �N���X
public:
	CUI();								// �R���X�g���N�^
	~CUI();								// �f�X�g���N�^

	static HRESULT Load(void);			// ���[�h
	static void Unload(void);			// �A�����[�h
										// ����
	static CUI *Create(D3DXVECTOR3 pos, float height, float width, D3DXCOLOR col, D3DXVECTOR2 uv, int nType);
	// ����������
	HRESULT Init(D3DXVECTOR3 pos, float height, float width, D3DXCOLOR col, D3DXVECTOR2 uv, int nType);
	void Uninit(void);					// �I������
	void Update(void);					// �X�V����
	void Draw(void);					// �`�揈��
	static void CreateMode(CManager::MODE mode);

private:
	static LPDIRECT3DTEXTURE9	m_pTexture[UI_TEXMAX];		//  �e�N�X�`�����ւ̃|�C���^
	int m_nType;											//  ���
	int m_nCounterAnim;										//	�A�j���[�V�����p�J�E���^�[
	int m_nPatternAnim;										//	�A�j���[�V�����p�^�[��
	float fWidthOld;										//	�����̑傫���̎擾
	bool bFlash;											//	�_��
	bool bCol;												//	�F�̕ύX�_��
	int nFlashType;											//	�_�ł̎��
	int nSizeCount;											//	�傫���̃J�E���g

protected:

};

#endif