//=============================================================================
//
// ���f������ [model.h]
// Author :Ozaki Ozaki
//
//=============================================================================
#ifndef _MODEL_H_
#define _MODEL_H_

#include "main.h"
#include "scene.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************

#define FIELD_MAX_SIZE		(FIELD_SIZE - 10)
#define MAX_MODEL			(300)							//���f���z�u�̍ő吔
#define MAX_MODEL_TYPE		(5)								//���f����ނ̍ő吔

//*****************************************************************************
// �N���X�錾
//*****************************************************************************
class CModel
{
public:

	CModel();
	~CModel();

	static HRESULT Load(void);	// �ǂݍ���
	static void Unload(void);	// �J��

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType);
	static CModel *Create(D3DXVECTOR3 pos,D3DXVECTOR3 rot);
	void BindTexture(LPDIRECT3DTEXTURE9 texture);
	void BindModel(LPD3DXBUFFER	BuffMatModel, DWORD	NumMatModel, LPD3DXMESH	MeshModel);

	D3DXVECTOR3 GetPosition(void);
	D3DXVECTOR3 GetMove(void);
	//D3DXMATRIX GetMatrix(void);

	void SetMove(D3DXVECTOR3 move);
	void SetPosition(D3DXVECTOR3 pos);
	void SetRot(D3DXVECTOR3 rot);
	void SetParent(CModel *pModel);
	//MODEL *GetModel(void);
	D3DXMATRIX GetMtxWorld(void);

private:

	CModel									*m_pModel;						// ���f���ւ̃|�C���^
	CModel									*m_pParent;						// �e���f���ւ̃|�C���^;

	static LPDIRECT3DTEXTURE9				m_pTexture;						// �e�N�X�`��
	LPDIRECT3DVERTEXBUFFER9					m_pVtxBuff;						// ���_�o�b�t�@�̃|�C���^
	LPD3DXMESH								m_pMeshModel;					// ���b�V�����ւ̃|�C���^
	DWORD									m_nNumMatModel;					// �}�e���A�����̐�
	LPD3DXBUFFER							m_pBuffMatModel;				// �}�e���A�����ւ̃|�C���^
	D3DXMATERIAL							*m_pMat;
	//DWORD									m_nNumMat;						// �}�e���A�����̐�
	D3DXVECTOR3								m_pos;							// �ʒu
	D3DXVECTOR3								m_rot;							// ����
	D3DXMATRIX								m_mtxWorld;						// ���[���h�}�g���b�N�X
	D3DXVECTOR3								m_VtxMinModel, m_VtxMaxModel;	// ���f���̍ŏ��l�A�ő�l
	D3DXVECTOR3								m_move;
};
#endif