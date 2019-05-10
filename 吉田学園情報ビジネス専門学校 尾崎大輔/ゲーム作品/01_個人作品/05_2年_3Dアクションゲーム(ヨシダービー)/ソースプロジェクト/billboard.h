//=============================================================================
//
// �r���{�[�h���� [billboard.h]
// Author : Ozaki
//
//=============================================================================
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

#include "main.h"
#include "scene.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define		MAX_FOER		(4)
#define		MAX_BILLBOARD	(20)

//*****************************************************************************
// �N���X�錾
//*****************************************************************************

class CBillboard : public CScene
{
public:

	CBillboard(int nPriority, OBJTYPE objtype = CScene::OBJTYPE_BILLBOARD);
	~CBillboard();

	HRESULT Init(void);
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);
	void	BindTexture(LPDIRECT3DTEXTURE9 texture);
	D3DXVECTOR3 GetPosition(void);
	void SetPosition(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetMove(void);
	void SetMove(D3DXVECTOR3 move);
	static CBillboard *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

private:

	float							m_position = 0.0f;
	float							m_Addposition = 1.0f;

	static LPDIRECT3DTEXTURE9		m_pTexture;
	LPDIRECT3DVERTEXBUFFER9			m_pVtxBuff;

	D3DXVECTOR3						m_pos;			// �ʒu
	D3DXVECTOR3						m_rot;			// ����
	D3DXVECTOR3						m_movve;		// ����
	D3DXMATRIX						m_mtxWorld;		// ���[���h�}�g���b�N�X
	bool							m_bUse;			// �g�p���Ă邩���ĂȂ���

};
#endif