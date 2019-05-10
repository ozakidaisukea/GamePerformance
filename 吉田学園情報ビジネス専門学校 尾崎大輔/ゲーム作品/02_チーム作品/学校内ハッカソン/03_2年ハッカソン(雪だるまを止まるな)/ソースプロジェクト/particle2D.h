//=============================================================================
//
// �p�[�e�B�N������ [particle.h]
// Author : Jukiya Hayakawa
//
//=============================================================================
#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "main.h"
#include "scene2D.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CParticle2D : public CScene2D
{
public:
	//�����o�֐�
	CParticle2D();
	~CParticle2D();
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//�ÓI�����o�֐�
	static CParticle2D *Create(D3DXVECTOR3 pos,D3DXVECTOR3 move, D3DXCOLOR col,float fLength);

private:
	//�����o�ϐ�
	int m_nLife;		//�̗�
	D3DXVECTOR3 m_move;	//�ړ���
	//�ÓI�����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_pTexture;
};
#endif