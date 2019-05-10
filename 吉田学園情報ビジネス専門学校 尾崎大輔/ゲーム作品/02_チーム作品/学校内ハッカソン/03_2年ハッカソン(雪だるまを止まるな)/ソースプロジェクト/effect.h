//=============================================================================
//
// �e�N���X���� [effect.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "billboard.h"

//==================================================================
//	�N���X�̒�`
//==================================================================
//�v���C���[�N���X
class CEffect : public CBillboard
{
public:

	typedef enum
	{//�e�̊Ǘ��ҕ����p
		AUTHOR_NONE,
		AUTHOR_PLAYER,
		AUTHOR_ENEMY,
	}AUTHORITY;

	//�R���X�g���N�^&�f�X�g���N�^
	CEffect();
	CEffect(int nPriority,CScene::OBJTYPE type);
	~CEffect();

	static HRESULT Load(void);
	static void    Unload(void);

	HRESULT Init(void);
	void Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fSize, int nLife);

	void    Uninit(void);
	void    Update(void);
	void    Draw(void);
	void	SetParentMatrix(D3DXMATRIX* mtxParent);
	static CEffect* Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, AUTHORITY author,float fSize,D3DXCOLOR col,int nLife);
	AUTHORITY GetAuthor(void) { return m_Author; };

	void MoveScaling(float fScaling);
	void Gravity(float fGravity);
private:
	D3DXMATRIX*				  m_mtxParent;		//�e�p�[�e�B�N���̃}�g���b�N�X(���g�̃}�g���b�N�X�Ɗ|�����킹��)
	static LPDIRECT3DTEXTURE9 m_apTexture[2];	//���L�e�N�X�`���ւ̃|�C���^
	AUTHORITY				m_Author;			//�G�t�F�N�g�̌�����
	D3DXVECTOR3				m_pos;				//���W
	D3DXVECTOR3				m_move;				//�ړ���
	D3DXCOLOR				m_Col;				//�F
	int						m_nCount;			//�J�E���^
	int						m_nLife;			//�̗�
	float					m_fSize;			//�T�C�Y
protected:
};
#endif // !_PLAYER_H_
