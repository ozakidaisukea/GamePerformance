//=============================================================================
//
// �V�[������ [scene.cpp]
// Author : Ozaki
//
//=============================================================================
#include "main.h"
#include "scene.h"
#include "renderer.h"
#include "debugproc.h"

//=============================================================================
// �ÓI�����o-�ϐ��錾
//=============================================================================
int CScene::m_nNumALL = 0;						// �|���S���̑���

CScene *CScene::m_pTop[MAX_PRIORITY1] = {};
CScene *CScene::m_pCur[MAX_PRIORITY1] = {};
int    CScene::m_nNumPriority[MAX_PRIORITY1] = {};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CScene::CScene(int nPriority, OBJTYPE objtype)
{
	m_pPrev = NULL;

	// �Ō���̃I�u�W�F�N�g��NULL����Ȃ�������
	if (m_pCur[nPriority] != NULL)
	{
		// �Ō���̃I�u�W�F�N�g�̃l�N�X�g��
		m_pCur[nPriority]->m_pNext = this;
	}
	else
	{
		// �擪�̃I�u�W�F�N�g�Ɏ����Ă���
		m_pTop[nPriority] = this;
	}

	// �O�̃I�u�W�F�N�g���Ō���ɂ���
	m_pPrev = m_pCur[nPriority];

	// ���̃I�u�W�F�N�g��NULL�ɂȂ�
	m_pNext = NULL;

	// �Ō���̃I�u�W�F�N�g��
	m_pCur[nPriority] = this;

	// ���S�t���O���Ȃ���
	m_bDeath = false;

	m_nPriority = nPriority;

	m_objtype = objtype;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_nNumPriority[nPriority]++;
	m_nNumALL++;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CScene::~CScene()
{

}

//=============================================================================
// �S�Ă̏I������
//=============================================================================
void CScene::ReleaseAll(void)
{
	CScene *pScene = NULL;

	for (int nCntPriority = 0; nCntPriority < MAX_PRIORITY1; nCntPriority++)
	{

		pScene = m_pTop[nCntPriority];	// �V�[���̐擪����n�߂����邽��

		// pScene��NULL����Ȃ�������
		while (pScene)
		{
			// �l�N�X�g�����Ȃ��Ȃ�܂ő��������(�X�V)
			CScene * pSceneNext = pScene->m_pNext;


			pScene->Uninit();


			pScene = pSceneNext;
		}

	}

	for (int nCntPriority = 0; nCntPriority < MAX_PRIORITY1; nCntPriority++)
	{
		pScene = m_pTop[nCntPriority];	// �V�[���̐擪����n�߂����邽��


		while (pScene)
		{
			CScene * pSceneNext = pScene->m_pNext;

			// pScene�̎��S�t���O�𗧂Ă�
			if (pScene->m_bDeath == true)
			{// �t���O����������I�u�W�F�N�g��S�ł�����
				pScene->UninitAll();
			}

			pScene = pSceneNext;
		}

	}

	for (int nCntPriority = 0; nCntPriority < MAX_PRIORITY1; nCntPriority++)
	{
		if (m_pTop[nCntPriority] != NULL)
		{
			while (m_pTop[nCntPriority])
			{
				m_pTop[nCntPriority]->Uninit();

				m_pTop[nCntPriority]->UninitAll();
			}
		}
	}
}

//=============================================================================
// �S�Ă̍X�V����
//=============================================================================
void CScene::UpdateAll(void)
{
	CScene *pScene = NULL;

	for (int nCntPriority = 0; nCntPriority < MAX_PRIORITY1; nCntPriority++)
	{
		pScene = m_pTop[nCntPriority];	// �V�[���̐擪����n�߂����邽��

		// pScene��NULL����Ȃ�������
		while (pScene)
		{// �l�N�X�g�����Ȃ��Ȃ�܂ő��������(�X�V)
			CScene * pSceneNext = pScene->m_pNext;

			//�f�X�`�F�b�N
			if (pScene->m_bDeath == false)
			{
				pScene->Update();
			}

			pScene = pSceneNext;
		}
	}

	for (int nCntPriority = 0; nCntPriority < MAX_PRIORITY1; nCntPriority++)
	{
		pScene = m_pTop[nCntPriority];	// �V�[���̐擪����n�߂����邽��

		while (pScene)
		{
			CScene * pSceneNext = pScene->m_pNext;

			// pScene�̎��S�t���O�𗧂Ă�
			if (pScene->m_bDeath == true)
			{
				// �t���O����������I�u�W�F�N�g��S�ł�����
				pScene->UninitAll();
			}

			pScene = pSceneNext;
		}
	}

#ifdef _DEBUG
	for (int nCntPriority = 0; nCntPriority < MAX_PRIORITY1; nCntPriority++)
	{
		//CDebugProc::Print("sd", "Priority : ", m_nNumPriority[nCntPriority]);
	}
#endif // DEBUG


}

//=============================================================================
// �S�Ă̕`�揈��
//=============================================================================
void CScene::DrawAll(void)
{
	for (int nCntPriority = 0; nCntPriority < MAX_PRIORITY1; nCntPriority++)
	{
		CScene *pScene;
		pScene = m_pTop[nCntPriority];	// �V�[����擪����n�߂�

			// pScene��NULL����Ȃ�������
		while (pScene)
		{// �l�N�X�g�����Ȃ��Ȃ�܂ő��������(�`��)
			CScene * pSceneNext = pScene->m_pNext;

			pScene->Draw();

			pScene = pSceneNext;
		}
	}
}

//=============================================================================
// �S�Ă̏I������
//=============================================================================
void CScene::UninitAll(void)
{
	int nPriority = m_nPriority;

	// �O�̃I�u�W�F�N�g��NULL����Ȃ�������
	if (m_pPrev != NULL)
	{// �O�̃I�u�W�F�N�g�̃l�N�X�g�����̃I�u�W�F�N�g�ɂȂ�
		m_pPrev->m_pNext = m_pNext;
	}

	// NULL��������
	else
	{// �擪�̃I�u�W�F�N�g�����̃I�u�W�F�N�g�ɂ���
		m_pTop[nPriority] = m_pNext;
	}

	// ���̃I�u�W�F�N�g��NULL��������
	if (m_pNext != NULL)
	{// ���̃I�u�W�F�N�g�̑O��O�̃I�u�W�F�N�g�ɂ���
		m_pNext->m_pPrev = m_pPrev;
	}

	else
	{// �Ō���̃I�u�W�F�N�g��O�̃I�u�W�F�N�g�ɂ���
		m_pCur[nPriority] = m_pPrev;
	}

	m_nNumPriority[nPriority]--;
	delete this;

}

//=============================================================================
// �J������
//=============================================================================
void CScene::Release(void)
{
	int nPriority = m_nPriority;

	m_bDeath = true;
}

//===================================================================================================================
// �ݒ�
//===================================================================================================================

//=============================================================================
// �I�u�W�F�N�g�^�C�v�̐ݒ�
//=============================================================================
void CScene::SetObjtType(CScene::OBJTYPE objttpe)
{
	m_objtype = objttpe;
}

//=============================================================================
// �|�W�V�����̐ݒ�
//=============================================================================
void CScene::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
// ���[�u�̐ݒ�
//=============================================================================
void CScene::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}

//=============================================================================
// �����̐ݒ�
//=============================================================================
void CScene::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//===================================================================================================================
// �擾
//===================================================================================================================

//=============================================================================
// �I�u�W�F�N�g�^�C�v���擾
//=============================================================================
CScene::OBJTYPE CScene::GetObjtType(void)
{
	return m_objtype;
}

//=============================================================================
// �|�W�V�������擾
//=============================================================================
D3DXVECTOR3 CScene::GetPosition(void)
{
	return m_pos;
}

//=============================================================================
// �������擾
//=============================================================================
D3DXVECTOR3 CScene::GetMove(void)
{
	return m_move;
}

//=============================================================================
//�I�u�W�F�N�g�^�C�v�ݒ菈��
//=============================================================================
void CScene::SetObjType(OBJTYPE ObjType)
{
	m_objtype = ObjType;
}
//=============================================================================
//�I�u�W�F�N�g�^�C�v�擾����
//=============================================================================
CScene::OBJTYPE CScene::GetObjType(void)
{
	return m_objtype;
}
//while (pScene != NULL)	//while (pScene) or while(!pScene)
//{// �l�N�X�g�����Ȃ��Ȃ�܂ő��������
//	// �_���ȗ��R:������Update�Ŏ��ʂƂ��l�N�X�g�ɍs���⌾���c���Ȃ��Ȃ邩��
//	pScene->Update();
//	pScene = pScene->m_pNext;
//}