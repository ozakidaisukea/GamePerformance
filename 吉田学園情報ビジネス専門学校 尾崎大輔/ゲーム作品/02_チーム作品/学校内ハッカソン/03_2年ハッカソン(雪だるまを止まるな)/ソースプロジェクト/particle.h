//=============================================================================
//
// �p�[�e�B�N������ [particle.h]
// Author : Yuto Kodama
//
//=============================================================================
#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "main.h"
#include "scene.h"
#include "effect.h"

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CParticle : public CScene
{
public:
	typedef enum
	{
		PARTICLE_TYPE1 = 0,
		PARTICLE_MAX,
	}PARTICLE_TYPE;

	CParticle();
	CParticle(int nPriority, CScene::OBJTYPE type);

	~CParticle();

	static CParticle* Create(D3DXVECTOR3 pos,D3DXVECTOR3 rot,int nLife, PARTICLE_TYPE type);

	HRESULT Init(void) { return S_OK; };
	void Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife, PARTICLE_TYPE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void CreateParticlePattern();
private:
	PARTICLE_TYPE m_type;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	D3DXMATRIX m_mtxWorld;
	CEffect** m_pEffect;	//�G�t�F�N�g�̃|�C���^(�K�v�����������I�m�ۂ��邽�߃_�u���|�C���^�ɂ��Ă���)
	int m_nMasterLife;		//�p�[�e�B�N���̗̑�(����𒴂�����G�t�F�N�g�����ׂĉ������)
	float m_fMoveScale;		//�G�t�F�N�g�̈ړ��ʂɕ␳���|����Ƃ��p�̕ϐ�
	int m_nEffectNum;
	int m_nCount;
};

#endif // !_PARTICLE_H_
