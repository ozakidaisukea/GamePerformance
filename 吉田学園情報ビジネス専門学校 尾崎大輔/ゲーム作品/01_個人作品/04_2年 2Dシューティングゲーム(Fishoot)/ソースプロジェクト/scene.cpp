//=============================================================================
//
// �V�[������ [scene.cpp]
// Author : Ozaki
//
//=============================================================================
#include "main.h"
#include "scene.h"
#include "renderer.h"

//=============================================================================
// �ÓI�����o-�ϐ��錾
//=============================================================================
int CScene::m_nNumALL = 0;		// �|���S���̑���
CScene *CScene::m_apCscene[MAX_PRIORITY1][MAX_POLYGON] = {};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CScene::CScene(int nPriority)
{
	for (int nCntPolygon = 0; nCntPolygon < MAX_POLYGON; nCntPolygon++)
	{
		if (m_apCscene[nPriority][nCntPolygon] == NULL)
		{
			m_apCscene[nPriority][nCntPolygon] = this;

			m_nID = nCntPolygon;
			m_nPriority = nPriority;

			m_nNumALL++;
			break;
		}
	}
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
	for (int nCntPriority = 0; nCntPriority < MAX_PRIORITY1; nCntPriority++)
	{
		for (int nCntPolygon = 0; nCntPolygon < MAX_POLYGON; nCntPolygon++)
		{
			if (m_apCscene[nCntPriority][nCntPolygon] != NULL)
			{
				m_apCscene[nCntPriority][nCntPolygon]->Uninit();
			}
		}
	}
}

//=============================================================================
// �S�Ă̍X�V����
//=============================================================================
void CScene::UpdateAll(void)
{
	for (int nCntPriority = 0; nCntPriority < MAX_PRIORITY1; nCntPriority++)
	{
		for (int nCntPolygon = 0; nCntPolygon < MAX_POLYGON; nCntPolygon++)
		{
			if (m_apCscene[nCntPriority][nCntPolygon] != NULL)
			{
				m_apCscene[nCntPriority][nCntPolygon]->Update();
			}
		}
	}
}

//=============================================================================
// �S�Ă̕`�揈��
//=============================================================================
void CScene::DrawAll(void)
{
	for (int nCntPriority = 0; nCntPriority < MAX_PRIORITY1; nCntPriority++)
	{
		for (int nCntPolygon = 0; nCntPolygon < MAX_POLYGON; nCntPolygon++)
		{
			if (m_apCscene[nCntPriority][nCntPolygon] != NULL)
			{
				// �`�揈��
				m_apCscene[nCntPriority][nCntPolygon]->Draw();
			}
		}
	}
}

//=============================================================================
// �J������
//=============================================================================
void CScene::Release(void)
{
	if (m_apCscene[m_nPriority][m_nID] != NULL)
	{
		int nID = m_nID;
		int nPriority = m_nPriority;

 		delete m_apCscene[nPriority][nID];
		m_apCscene[nPriority][nID] = NULL;
		m_nNumALL--;
	}
}

//=============================================================================
//
//=============================================================================
void CScene::SetObjtType(CScene::OBJTYPE objttype)
{
	m_objtype = objttype;
}

//=============================================================================
//
//=============================================================================
CScene::OBJTYPE CScene::GetObjtType(void)
{
	return m_objtype;
}

//=============================================================================
//
//=============================================================================
CScene*CScene::GetSCene(int nIdex,int nPriority)
{
	return m_apCscene[nPriority][nIdex];
}