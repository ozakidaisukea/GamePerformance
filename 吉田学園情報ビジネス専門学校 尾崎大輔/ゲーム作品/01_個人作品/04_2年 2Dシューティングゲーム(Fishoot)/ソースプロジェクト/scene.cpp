//=============================================================================
//
// シーン処理 [scene.cpp]
// Author : Ozaki
//
//=============================================================================
#include "main.h"
#include "scene.h"
#include "renderer.h"

//=============================================================================
// 静的メンバ-変数宣言
//=============================================================================
int CScene::m_nNumALL = 0;		// ポリゴンの総数
CScene *CScene::m_apCscene[MAX_PRIORITY1][MAX_POLYGON] = {};

//=============================================================================
// コンストラクタ
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
// デストラクタ
//=============================================================================
CScene::~CScene()
{

}

//=============================================================================
// 全ての終了処理
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
// 全ての更新処理
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
// 全ての描画処理
//=============================================================================
void CScene::DrawAll(void)
{
	for (int nCntPriority = 0; nCntPriority < MAX_PRIORITY1; nCntPriority++)
	{
		for (int nCntPolygon = 0; nCntPolygon < MAX_POLYGON; nCntPolygon++)
		{
			if (m_apCscene[nCntPriority][nCntPolygon] != NULL)
			{
				// 描画処理
				m_apCscene[nCntPriority][nCntPolygon]->Draw();
			}
		}
	}
}

//=============================================================================
// 開放処理
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