//=============================================================================
//
// �A�C�e���̏��� [item.h]
// Author : Ozaki
//
//=============================================================================
#pragma once
#ifndef _ITEM_H_
#define _ITEM_H_

#include "scene2D.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_ITEM		(256)		// �A�C�e���̍ő吔
#define MAX_MIKY		(50)		// �A�C�e���̑傫��
#define TEX_U			(8)			// �e�N�X�`�����̕�����
#define TEX_V			(1)			// �e�N�X�`���c�̕�����

//*****************************************************************************
// �N���X�錾
//*****************************************************************************
class CPlayer;
class CGauge;
class CScore;

class CItem : public CScene2D
{
public:

	typedef enum
	{
		ITEM_NORMAL0 = 0,
		ITEM_HIGH0,
		ITEM_NORMAL1,
		ITEM_HIGH1,
		ITEM_MAX
	}ITEM_TYPE;

	CItem();
	~CItem();

	static HRESULT Load(void);	// �ǂݍ���

	static void Unload(void);	// �J��

	static CItem *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float widtgh, float height,ITEM_TYPE type);

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, float widtgh, float height, ITEM_TYPE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	// �X�R�A
	static CScore				*m_apScore;

	// ���L�e�N�X�`���ւ̃|�C���^
	static LPDIRECT3DTEXTURE9	m_pTexture[MAX_ITEM];	// �ۑ�����ꏊ
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;
	//CGauge						*f_gauge;				// �Q�[�W�̒l
	ITEM_TYPE					m_type;
	D3DXVECTOR3					m_move;					//�ړ���
	float						m_rot = 0.0f;
	float						m_pos = 0.0f;
	float						m_Addposition = 1.0f;

protected:
};
#endif