//=============================================================================
//
// �M�~�b�N���� [gimmick.h]
// Author : Ozaki
//
//=============================================================================
#ifndef _GIMMICK_H_
#define _GIMMICK_H_

#include "main.h"
#include "scene.h"

//*****************************************************************************
// ���f��
//*****************************************************************************
#define MODEL_GIMMICK			"data\\MODEL\\gimmick000.x"
#define MODEL_TYPE			(2)
//*****************************************************************************
// �N���X�錾
//*****************************************************************************

class CGimmick : CScene
{
public:

	typedef enum
	{
		GIMMICK_NONE = 0,
		GIMMICK_HEIHT,
		GIMMICK_WIDTH,
		GIMMICK_MAX
	}GIMMICK_TYPE;

	CGimmick();
	~CGimmick();

	HRESULT Init(void);
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);
	void	BindTexture(LPDIRECT3DTEXTURE9 texture);
	float	GetLHeght(D3DXVECTOR3 pos);
	static CGimmick *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot,GIMMICK_TYPE type);

private:

	GIMMICK_TYPE				m_nType;			// �^�C�v
	D3DXVECTOR3					m_pos;				// �ʒu
	D3DXVECTOR3					m_rot;				// ����
	D3DXVECTOR3					m_move;				// ����
	static LPDIRECT3DTEXTURE9	m_pTexture;			// �e�N�X�`���̃|�C���^
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;			// ���_�o�b�t�@�̃|�C���^
	LPD3DXMESH					m_pMeshModel;		// ���b�V�����ւ̃|�C���^
	DWORD						m_nNumMatModel;		// �}�e���A�����̐�
	LPD3DXBUFFER				m_pBuffMatModel;	// �}�e���A�����ւ̃|�C���^
	D3DXMATRIX					m_mtxWorld;			//���[���h�}�g���b�N�X
	D3DXMATERIAL				*m_pMat;
	D3DXVECTOR3					m_vtxMin;			// ���f���̍ŏ��l
	D3DXVECTOR3					m_vtxMax;			// ���f���̍ő�l
};

#endif