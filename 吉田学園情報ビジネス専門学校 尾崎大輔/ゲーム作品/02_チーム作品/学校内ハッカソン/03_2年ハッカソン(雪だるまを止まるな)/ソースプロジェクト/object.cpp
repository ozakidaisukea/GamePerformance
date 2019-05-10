//=============================================================================
//
// �z�u���̏��� [object.cpp]
// Author : Jukiya Hayakawa
//
//=============================================================================
#include "object.h"
#include "manager.h"
#include "renderer.h"
#include "loadfilefunction.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CObject::CObject(int nPrioriry, OBJTYPE objtype) : CSceneX(nPrioriry, objtype)
{

}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CObject::~CObject()
{


}

//=============================================================================
// �I�u�W�F�N�gX�̐���
//=============================================================================
CObject *CObject::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, bool bHit)
{
	CObject *pObject = NULL;		//�z�u���̃|�C���^

	if (pObject == NULL)
	{
		pObject = new CObject;		//���I�m��
		if (pObject != NULL)
		{
			pObject->SetPos(pos);	//�ʒu�̐ݒu����
			pObject->SetRot(rot);	//�����̐ݒu����
			pObject->SetSize(size);	//�傫���̐ݒu����
			pObject->SetHit(bHit);	//�����蔻��̐ݒu����
			pObject->Init();		//����������
		}
	}
	return pObject;
}
//=============================================================================
// ����������
//=============================================================================
HRESULT CObject::Init(void)
{
	//����������
	CSceneX::Init();
	//�I�u�W�F�N�g�̎�ސݒ�
	SetObjType(OBJTYPE_OBJECT);
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CObject::Uninit(void)
{
	CSceneX::Uninit();
	//�I�u�W�F�N�g�̔j��
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CObject::Update(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void CObject::Draw(void)
{
	//�`�揈��
	CSceneX::Draw();
}


//=============================================================================
// �z�u���̓����蔻��
//=============================================================================
bool CObject::Collision(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 * pMove, D3DXVECTOR3 *VtxMin, D3DXVECTOR3 *VtxMax, bool* bHIT)
{
	bool bLand = false;	//����Ă��邩�ǂ���

	D3DXVECTOR3 pos = GetPos();				//�ʒu�̎擾
	D3DXVECTOR3 vtxMax = GetVtxMax();		//���_���W�ő�l�̎擾
	D3DXVECTOR3 vtxMin = GetVtxMin();		//���_���W�ŏ��l�̎擾
	bool		bHit = GetHit();			//�����蔻��̎擾
											//if (pPos->x >= pos.x + vtxMin.x&&
											//	pPos->x <= pos.x + vtxMax.x &&
											//	pPos->z >= pos.z + vtxMin.z &&
											//	pPos->z <= pos.z + vtxMax.z)
											//{
											//	if (pPosOld->x <= pos.x + vtxMin.x&&
											//		pPos->x >= pos.x + vtxMin.x)
											//	{//������߂荞�񂾏ꍇ
											//		bLand = true;
											//		pPos->x = pos.x + vtxMin.x;
											//	}
											//	else if (pPosOld->x >= pos.x + vtxMax.x&&
											//		pPos->x <= pos.x + vtxMax.x)
											//	{//�E����߂荞��
											//		bLand = true;
											//		pPos->x = pos.x + vtxMax.x;

											//	}
											//	else if (pPosOld->z <= pos.z + vtxMin.z &&
											//		pPos->z >= pos.z + vtxMin.z)
											//	{//�O����߂荞��
											//		bLand = true;
											//		pPos->z = pos.z + vtxMin.z;

											//	}
											//	else if (pPosOld->z >= pos.z + vtxMax.z &&
											//		pPos->z <= pos.z + vtxMax.z)
											//	{//�ォ��߂荞��
											//		bLand = true;
											//		pPos->z = pos.z + vtxMax.z;

											//	}
											//}
	if (bHit == true)
	{
		if (/*pPos->y <= pos.y + vtxMax.y - (VtxMax->y)
			&& pPos->y >= pos.y + vtxMax.y - (VtxMax->y)
			||*/ pPos->y >= pos.y + vtxMin.y
			&& pPos->y <= pos.y + vtxMin.y
			|| pPos->y <= pos.y + vtxMax.y - (VtxMax->y)
			&& pPos->y >= pos.y + vtxMin.y)
		{// y�͈̔͂̒�
			if (pPos->z <= pos.z + vtxMax.z && pPos->z >= pos.z + vtxMin.z)
			{// z�͈̔͂̒�
				if (pPosOld->x <= pos.x + vtxMin.x
					&& pPos->x > pos.x + vtxMin.x)
				{// X���W�̒��ɍ����������
					pPos->x = pPosOld->x;
					pMove->x = 0.0f;
				}
				else if (pPosOld->x >= pos.x + vtxMax.x
					&& pPos->x < pos.x + vtxMax.x)
				{// X���W�̒��ɉE���������
					pPos->x = pPosOld->x;
					pMove->x = 0.0f;
				}
			}
			if (pPos->x <= pos.x + vtxMax.x && pPos->x >= pos.x + vtxMin.x)
			{// x�͈̔͂̒�
				if (pPosOld->z - (VtxMax->z) <= pos.z + vtxMin.z
					&& pPos->z  + (VtxMax->z)> pos.z + vtxMin.z)
				{// Z���W�̒��Ɏ�O���������
					pPos->z = pPosOld->z;
					pMove->z = 0.0f;
					*bHIT = true;
				}
				else if (pPosOld->z >= pos.z + vtxMax.z
					&& pPos->z < pos.z + vtxMax.z)
				{// Z���W�̒��Ɍ�납�������
					pPos->z = pPosOld->z;
					pMove->z = 0.0f;
				}
			}
		}

		if (pPos->x  < pos.x + vtxMax.x - (VtxMax->x) && pPos->x > pos.x + vtxMin.x + (VtxMax->x)
			&& pPos->z <= pos.z + vtxMax.z - (VtxMax->z) && pPos->z >= pos.z + vtxMin.z + (VtxMax->z))
		{// ��Q���̓����ɏ����
			if (pPosOld->y >= pos.y + vtxMax.y && pPos->y < pos.y + vtxMax.y
				|| pPos->y <= pos.y + vtxMax.y && pPosOld->y > pos.y + vtxMax.y)
			{// �ォ��u���b�N�ɓ��������Ƃ�
				bLand = true;  // ����������Ԃ�
				pPos->y = pos.y + vtxMax.y;
				pMove->y = 0.0f;  // �ړ��ʂ��Ȃ���
			}

			if (pPosOld->y  < pos.y + vtxMin.y && pPos->y >= pos.y + vtxMin.y
				|| pPos->y  > pos.y + vtxMin.y && pPosOld->y <= pos.y + vtxMin.y)
			{// ������u���b�N�ɓ��������Ƃ�
				pPos->y = pos.y + vtxMin.y;
				pMove->y = 0.0f;  // �ړ��ʂ��Ȃ���
			}
		}
	}
	return bLand;
}