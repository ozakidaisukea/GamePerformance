//=============================================================================
//
// �I�u�W�F�N�gX�̏��� [sceneX.h]
// Author : Jukiya Hayakawa
//
//=============================================================================
#ifndef _SCENEX_H_
#define _SCENEX_H_

#include "main.h"
#include "scene.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CSceneX : public CScene
{
public:	//�N������A�N�Z�X�\
	CSceneX(int nPriority = 3, OBJTYPE objtype = OBJTYPE_SCENEX);
	~CSceneX();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPos(D3DXVECTOR3 pos);
	void SetRot(D3DXVECTOR3 rot);
	void SetSize(D3DXVECTOR3 size);
	void SetVtxMax(D3DXVECTOR3 vtxMax);
	void SetVtxMin(D3DXVECTOR3 vtxMin);
	void SetHit(bool bHit);
	D3DXVECTOR3 GetPos(void);
	D3DXVECTOR3 GetVtxMax(void);
	D3DXVECTOR3 GetVtxMin(void);
	bool GetHit(void);

	void BindX(LPD3DXMESH mesh, LPD3DXBUFFER buffmat, DWORD nummat);

	//�ÓI�����o�֐�
	static CSceneX *Create(void);
private:	//�����������A�N�Z�X�\
	LPD3DXMESH			m_pMesh;					//���b�V�����ւ̃|�C���^
	LPD3DXBUFFER		m_pBuffMat;					//�}�e���A�����ւ̃|�C���^
	DWORD				m_nNumMat;					//�}�e���A�����̐�
	LPDIRECT3DTEXTURE9	*m_pTexture;				//�e�N�X�`���̃|�C���^
	D3DXVECTOR3			m_pos;						//�ʒu
	D3DXVECTOR3			m_rot;						//����
	D3DXMATRIX			m_mtxWorld;					//���[���h�}�g���b�N�X
	D3DXVECTOR3			m_vtxMax;					//���_���W�̍ő�l
	D3DXVECTOR3			m_vtxMin;					//���_���W�̍ŏ��l
	D3DXVECTOR3			m_size;						//�傫��
	bool				m_bHit;						//�����蔻��
};
#endif
