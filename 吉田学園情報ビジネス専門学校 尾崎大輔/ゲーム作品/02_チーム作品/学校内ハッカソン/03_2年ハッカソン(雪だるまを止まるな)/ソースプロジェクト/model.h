//=============================================================================
//
// ���f���̏��� [model.h]
// Author : Jukiya Hayakawa
//
//=============================================================================
#ifndef _MODEL_H_
#define _MODEL_H_

#include "main.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CModel
{
public:	//�N������A�N�Z�X�\
	//�����o�֐�
	CModel();
	~CModel();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPos(D3DXVECTOR3 pos);
	void SetRot(D3DXVECTOR3 rot);
	D3DXVECTOR3 GetPos(void);
	D3DXVECTOR3 GetRot(void);
	void BindX(LPD3DXMESH mesh, LPD3DXBUFFER buffmat, DWORD nummat);
	void SetParent(CModel *pModel);
	D3DXMATRIX GetMtxWorld(void);
	void BindTexture(LPDIRECT3DTEXTURE9 tex);

	//�ÓI�����o�֐�
	static CModel *Create(D3DXVECTOR3 pos);

private:	//�����������A�N�Z�X�\
	//�����o�ϐ�
	LPDIRECT3DTEXTURE9			m_pTexture = NULL;	// �e�N�X�`���ւ̃|�C���^
	LPD3DXMESH			m_pMesh = NULL;				//���b�V�����ւ̃|�C���^
	LPD3DXBUFFER		m_pBuffMat = NULL;			//�}�e���A�����ւ̃|�C���^
	DWORD				m_nNumMat = 0;				//�}�e���A�����̐�
	D3DXMATRIX			m_mtxWorld;					//���[���h�}�g���b�N�X
	D3DXVECTOR3			m_pos;						//�ʒu
	D3DXVECTOR3			m_rot;						//����
	int					m_nIdx;						//�C���f�b�N�X�ԍ�
	CModel				*m_pParent;					//�e�q�̃|�C���^
};
#endif
