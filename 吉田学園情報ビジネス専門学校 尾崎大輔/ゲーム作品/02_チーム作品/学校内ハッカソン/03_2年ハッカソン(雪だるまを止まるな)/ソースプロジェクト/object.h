//=============================================================================
//
// �z�u���̏��� [object.h]
// Author : Jukiya Hayakawa
//
//=============================================================================
#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "main.h"
#include "sceneX.h"

#define MAX_OBJECT (10)

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CObject : public CSceneX
{
public:	//�N������A�N�Z�X�\
		//*************************************************************************
		// �\���̒�`
		//*************************************************************************
	typedef struct
	{
		int nType;				//���
		D3DXVECTOR3 pos;		//�ʒu
		D3DXVECTOR3 rot;		//����
		D3DXVECTOR3 size;		//�傫��
		bool		bHit;		//�����蔻��
	}OBJECT_INFO;

	//�����o�֐�
	CObject(int nPriority = 3, OBJTYPE objType = OBJTYPE_OBJECT);
	~CObject();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	bool Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 *vtxMin, D3DXVECTOR3 *vtxMax, bool *bHIT);

	//�ÓI�����o�֐�
	static CObject *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, bool bHit);

private:	//�����������A�N�Z�X�\
			//�����o�ϐ�
	int							m_nNumModel;							//�I�u�W�F�N�g�̑���
};
#endif