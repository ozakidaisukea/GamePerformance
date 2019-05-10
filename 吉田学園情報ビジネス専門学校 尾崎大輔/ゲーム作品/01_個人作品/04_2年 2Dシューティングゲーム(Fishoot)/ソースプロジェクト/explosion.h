//=============================================================================
//
// �����̏��� [explosion.h]
// Author : Ozaki
//
//=============================================================================
#pragma once
#ifndef _EXPLPSION_H_
#define _EXPLOSION_H_

#include "scene2D.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_EXPLOSION	(256)		// �����̍ő吔
#define MAX_MIKY		(50)		// �����̑傫��
#define TEX_U			(8)			// �e�N�X�`�����̕�����
#define TEX_V			(1)			// �e�N�X�`���c�̕�����

//*****************************************************************************
// �N���X�錾
//*****************************************************************************
class CBullet;

class CExplosion : public CScene2D //CPlayer
{
public:

	CExplosion();
	~CExplosion();

	static HRESULT Load(void);	// �ǂݍ���

	static void Unload(void);	// �J��

	static CExplosion *Create(D3DXVECTOR3 pos, float widtgh, float height);

	HRESULT Init(D3DXVECTOR3 pos, float widtgh, float height);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:

	// ���L�e�N�X�`���ւ̃|�C���^
	static LPDIRECT3DTEXTURE9	m_pTexture;					// �ۑ�����ꏊ
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;

	D3DXVECTOR3					m_move;						//�ړ���
	float						m_rot = 0.0f;
	float						m_position = 0.0f;
	float						m_Addposition = 1.0f;

protected:

	int							m_nCounterAnim;				//�A�j���[�V�����J�E���^�[
	int							m_nPatternAnim;				//�A�j���[�V�����p�^�[��

	//int m_nCounterState;		//��ԊǗ��J�E���^�[
	//int m_nLife;				//�̗�
	//bool m_bDisp;				//�g�p���Ă邩�ǂ���
};
#endif