//=============================================================================
//
// �V�[��3D ���� [scene3D.h]
// Author : Ozaki
//
//=============================================================================
#ifndef _SCENE3D_H_
#define _SCENE3D_H_

#include "main.h"
#include "scene.h"

//*****************************************************************************
// �N���X�錾
//*****************************************************************************
class CPlayer;

class CScene3D : public CScene
{
public:

	CScene3D(int nCntPriority, OBJTYPE objtype = CScene::OBJTYPE_3D);
	~CScene3D();

	HRESULT Init(void);
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);
	void	BindTexture(LPDIRECT3DTEXTURE9 texture);
	float	GetLHeght(D3DXVECTOR3 pos);
	static CScene3D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

private:

	float									m_rot = 0.0f;
	float									m_position = 0.0f;
	float									m_Addposition = 1.0f;

	static LPDIRECT3DTEXTURE9				m_pTexture;					// �e�N�X�`��
	LPDIRECT3DVERTEXBUFFER9					m_pVtxBuff;					// ���_�o�b�t�@�̃|�C���^
	D3DXVECTOR3								m_pos;						// �ʒu
	D3DXVECTOR3								m_rotpolygon;				// ����
	D3DXMATRIX								m_mtxWorldPolygon;			// ���[���h�}�g���b�N�X
	D3DXVECTOR3								m_aPos[6];
	static CPlayer							*m_Playerpos;
};
#endif