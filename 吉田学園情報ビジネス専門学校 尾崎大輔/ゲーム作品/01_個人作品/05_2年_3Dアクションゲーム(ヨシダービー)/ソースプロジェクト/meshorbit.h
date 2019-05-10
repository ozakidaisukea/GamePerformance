//=============================================================================
//
// ���b�V���I�[�r�b�g�̏��� [meshorbit.h]
// Author : Ozaki
//
//=============================================================================
#ifndef _MESHORBIT_H_
#define _MESHORBIT_H_

#include "main.h"
#include "scene.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_NOR		(10000)			//
#define MAX_NUM		(10)			// ���_�̍ő吔
#define NUM_OFFSET	(2)				// �I�t�Z�b�g��
//=============================================================================
//	���b�V���I�[�r�b�g�N���X�i�V�[���̔h���N���X�j
//=============================================================================
class CMeshOrbit : public CScene
{
public:
	CMeshOrbit(int nPriarity, CScene::OBJTYPE objtype);		//	�R���X�g���N�^
	~CMeshOrbit();											//	�f�X�g���N�^
	HRESULT Init(void);										//	����������
	void Uninit(void);										//	�I������
	void Update(void);										//	�X�V����
	void Draw(void);										//	�`�揈��
	static CMeshOrbit * Create(D3DXMATRIX mtxWorld);
	void SetMtxParent(D3DXMATRIX *pMtx);
	void BindTexture(LPDIRECT3DTEXTURE9 texture);

private:

	static LPDIRECT3DTEXTURE9	m_pTexture;						//�@�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;						//�@���_�o�b�t�@�ւ̃|�C���^

	D3DXVECTOR3					m_pos;							//�@�ʒu
	D3DXVECTOR3					m_rot;							//�@����
	D3DXVECTOR3					m_aPosVertex[MAX_NUM];			//	�Z�o�������_���W
	D3DXVECTOR3					m_affset[NUM_OFFSET];			//	���[�̃I�t�Z�b�g
	D3DXMATRIX					m_mtxworld;						//	���[���h�}�g���b�N�X
	D3DXMATRIX					*m_pMtxParent;					//	�e�̃}�g���b�N�X�ւ̃|�C���^
	int							m_nWidth;

protected:
};
#endif