//=============================================================================
//
// �e�̏��� [bullet.h]
// Author : Ozaki
//
//=============================================================================
#pragma once
#ifndef _BULLET_H_
#define _BULLET_H_

#include "scene2D.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_BULLET		(256)		// �e�̍ő吔
#define ADD_POSITION	(50)
#define MAX_TEXBULLET	(4)
//#define MAX_PRIORITY1	(8)
//*****************************************************************************
// �N���X�錾
//*****************************************************************************
class CPlayer;
class CExplosion;
class CEnemy;
class CEffect;
class CScore;

class CBullet : public CScene2D //CPlayer
{
public:

	//�e�̎��
	typedef enum
	{
		BULLETTYPE_PLAYER = 0,		//�v���C���[�̒e
		BULLETTYPE_AMI,				//�G�̒e
		BULLETTYPE_MORI,
		BULLETTYPE_TURIZAO,
		BULLETTYPE_MAX,
	}BULLETTYPE;

	CBullet();
	~CBullet();

	static HRESULT Load(void);	// �ǂݍ���

	static void Unload(void);	// �J��

	static	CBullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float widtgh, float height, BULLETTYPE type);

	HRESULT Init(D3DXVECTOR3 pos,D3DXVECTOR3 move, float widtgh, float height, BULLETTYPE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:

	// ����
	static CExplosion				*m_pExplosion;

	// �X�R�A
	static CScore *m_pScore;

	// ���L�e�N�X�`���ւ̃|�C���^
	static LPDIRECT3DTEXTURE9		m_pTexture[MAX_TEXBULLET];				// �ۑ�����ꏊ
	LPDIRECT3DVERTEXBUFFER9			m_pVtxBuffBullet = NULL;			    // ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3						m_move;									// �ړ���
	BULLETTYPE						m_type;

	float							m_rot = 0.0f;
	float							m_position = 0.0f;
	float							m_Addposition = 1.0f;
	int								m_CountState;

protected:

	float							m_fLength = 0.0f;
};
#endif