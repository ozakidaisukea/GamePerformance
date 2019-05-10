//=============================================================================
//
// �G�t�F�N�g�̏��� [effect.h]
// Author : Ozaki
//
//=============================================================================
#pragma once
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "scene2D.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_EFFECT		(256)		// �e�̍ő吔
#define ADD_POSITION	(50)
#define MAX_TEXEFFECT	(2)
//*****************************************************************************
// �N���X�錾
//*****************************************************************************
class CPlayer;
class CExplosion;
class CEnemy;

class CEffect : public CScene2D
{
public:

	CEffect();
	~CEffect();

	static HRESULT Load(void);	// �ǂݍ���

	static void Unload(void);	// �J��

	static	CEffect *Create(D3DXVECTOR3 pos, D3DXCOLOR col, float widtgh, float height);

	HRESULT Init(D3DXVECTOR3 pos, D3DXCOLOR col, float widtgh, float height);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:

	// ����
	static CExplosion *m_pExplosion;

	// ���L�e�N�X�`���ւ̃|�C���^
	static LPDIRECT3DTEXTURE9	m_pTexture;									// �ۑ�����ꏊ
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuffBullet = NULL;				    // ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3					m_move;										// �ړ���
	D3DXCOLOR					m_col;										// �F
	int							m_nLife;									// �\������(����)
	float						m_rot = 0.0f;
	float						m_position = 0.0f;
	float						m_Addposition = 1.0f;
	float						m_bUse;

protected:
	float					m_fLength = 0.0f;

};
#endif