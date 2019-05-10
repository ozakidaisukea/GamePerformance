//=============================================================================
//
// �e�̏��� [bullet.h]
// Author : Jukiya Hayakawa
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"
#include "billboard.h"

#define TEXTURE_NAME001		"data\\TEXTURE\\bullet000.png"			//�e�N�X�`����
#define MAX_BULLET			(3)
#define BULLET_HIT			(30)								// �����蔻��

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CBullet : public CBillboard
{
public:
	//�����o�֐�
	CBullet();
	~CBullet();
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Collision(void);
	//�ÓI�����o�֐�
	static CBullet *Create(D3DXVECTOR3 pos,float fWidth,float fHeight,D3DXVECTOR3 move);

private:
	//�����o�ϐ�
	int m_nLife;						//�̗�
	D3DXVECTOR3 m_move;					//�ړ���
	//�ÓI�����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_pTexture;
};
#endif