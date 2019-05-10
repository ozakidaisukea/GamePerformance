//=============================================================================
//
// ���f������ [model.h]
// Author :Ozaki Ozaki
//
//=============================================================================
#ifndef _SCENEX_H_
#define _SCENEX_H_

#include "main.h"
#include "scene.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MODEL_EARTH			"data\\MODEL\\earth000.x"		// ���f���̃t�@�C����
#define FIELD_MAX_SIZE		(FIELD_SIZE - 10)
#define MAX_MODEL			(300)							// ���f���z�u�̍ő吔
#define MAX_MODEL_TYPE		(5)								// ���f����ނ̍ő吔

//*****************************************************************************
// �N���X�錾
//*****************************************************************************
class CSceneX : public CScene
{
public:
	CSceneX(int nPriority, OBJTYPE objtype = CScene::OBJTYPE_X);
	~CSceneX();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	bool CollisionModel(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 radius, D3DXVECTOR3 VtxMax, D3DXVECTOR3 VtxMin);
	void SetModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType);
	static CSceneX *Create(D3DXVECTOR3 pos);
	void BindTexture(LPDIRECT3DTEXTURE9 texture);

	D3DXVECTOR3 GetPosition(void);

	D3DXVECTOR3 GetMove(void);

	void SetMove(D3DXVECTOR3 move);

	void SetPosition(D3DXVECTOR3 pos);

	void SetRot(D3DXVECTOR3 rot);

private:

	static LPDIRECT3DTEXTURE9				m_pTexture;						// �e�N�X�`��
	LPDIRECT3DVERTEXBUFFER9					m_pVtxBuff;						// ���_�o�b�t�@�̃|�C���^
	LPD3DXMESH								m_pMeshModel;					//���b�V�����ւ̃|�C���^
	DWORD									m_nNumMatModel;					//�}�e���A�����̐�
	LPD3DXBUFFER							m_pBuffMatModel;				//�}�e���A�����ւ̃|�C���^
	D3DXMATERIAL							*m_pMat;
	DWORD									m_nNumMat = 0;					//�}�e���A�����̐�
	D3DXVECTOR3								m_pos;							//�ʒu
	D3DXVECTOR3								m_rot;							//����
	D3DXMATRIX								m_mtxWorld;						//���[���h�}�g���b�N�X
	D3DXVECTOR3								m_VtxMinModel, m_VtxMaxModel;	//���f���̍ŏ��l�A�ő�l
	D3DXVECTOR3								m_move;

	int						takumi1;
};
#endif