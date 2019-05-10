//=============================================================================
//
// �I�u�W�F�N�g3D���� [scene3D.h]
// Author : Jukiya Hayakawa
//
//=============================================================================
#ifndef _SCENE3D_H_
#define _SCENE3D_H_

#include "main.h"
#include "scene.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CScene3D : public CScene
{
public:	//�N������A�N�Z�X�\
	//�����o�֐�
	CScene3D(int nPriority = 2, OBJTYPE objtype = OBJTYPE_SCENE3D);
	~CScene3D();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	D3DXVECTOR3 GetPos(void);
	float GetSizeX(void);
	float GetSizeZ(void);
	D3DXVECTOR3 GetNor(void);
	float GetHeight(D3DXVECTOR3 pos,bool bR);
	void SetPos(D3DXVECTOR3 pos);
	void SetSizeX(float sizeX);
	void SetSizeZ(float sizeZ);
	void BindTexture(LPDIRECT3DTEXTURE9 texture);

	//�ÓI�����o�֐�
	static CScene3D *Create(void);

private:	//�����������A�N�Z�X�\
	//�����o�֐�
	void SetNor(void);
	void MovePos(void);
	//�����o�ϐ�
	D3DXVECTOR3					m_pos;								//�ʒu
	D3DXVECTOR3					m_rot;								//����
	float						m_fSizeX;							//X�T�C�Y
	float						m_fSizeZ;							//Z�T�C�Y
	D3DXMATRIX					m_mtxWorld;							//�}�g���b�N�X
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff = NULL;					// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DTEXTURE9			m_pTexture = NULL;					// �e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3					m_vec0, m_vec1;						//�x�N�g��
	D3DXVECTOR3					m_nor0, m_nor1;						//�@��
	D3DXVECTOR3					m_dData;							//�f�[�^�i�[

	//�ÓI�����o�ϐ�
};
#endif
