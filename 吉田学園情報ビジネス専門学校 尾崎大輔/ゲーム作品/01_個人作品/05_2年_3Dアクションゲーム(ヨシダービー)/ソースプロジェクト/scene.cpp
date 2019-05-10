//=============================================================================
//
// シーン処理 [scene.cpp]
// Author : Ozaki
//
//=============================================================================
#include "main.h"
#include "scene.h"
#include "renderer.h"
#include "debugproc.h"

//=============================================================================
// 静的メンバ-変数宣言
//=============================================================================
int CScene::m_nNumALL = 0;						// ポリゴンの総数

CScene *CScene::m_pTop[MAX_PRIORITY1] = {};
CScene *CScene::m_pCur[MAX_PRIORITY1] = {};
int    CScene::m_nNumPriority[MAX_PRIORITY1] = {};

//=============================================================================
// コンストラクタ
//=============================================================================
CScene::CScene(int nPriority, OBJTYPE objtype)
{
	m_pPrev = NULL;

	// 最後尾のオブジェクトがNULLじゃなかったら
	if (m_pCur[nPriority] != NULL)
	{
		// 最後尾のオブジェクトのネクストが
		m_pCur[nPriority]->m_pNext = this;
	}
	else
	{
		// 先頭のオブジェクトに持ってくる
		m_pTop[nPriority] = this;
	}

	// 前のオブジェクトを最後尾にする
	m_pPrev = m_pCur[nPriority];

	// 次のオブジェクトがNULLになる
	m_pNext = NULL;

	// 最後尾のオブジェクトを
	m_pCur[nPriority] = this;

	// 死亡フラグをなくす
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
	CScene *pScene = NULL;

	for (int nCntPriority = 0; nCntPriority < MAX_PRIORITY1; nCntPriority++)
	{

		pScene = m_pTop[nCntPriority];	// シーンの先頭から始めさせるため

		// pSceneがNULLじゃなかったら
		while (pScene)
		{
			// ネクストがいなくなるまで代入し直す(更新)
			CScene * pSceneNext = pScene->m_pNext;


			pScene->Uninit();


			pScene = pSceneNext;
		}

	}

	for (int nCntPriority = 0; nCntPriority < MAX_PRIORITY1; nCntPriority++)
	{
		pScene = m_pTop[nCntPriority];	// シーンの先頭から始めさせるため


		while (pScene)
		{
			CScene * pSceneNext = pScene->m_pNext;

			// pSceneの死亡フラグを立てる
			if (pScene->m_bDeath == true)
			{// フラグが立ったらオブジェクトを全滅させる
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
// 全ての更新処理
//=============================================================================
void CScene::UpdateAll(void)
{
	CScene *pScene = NULL;

	for (int nCntPriority = 0; nCntPriority < MAX_PRIORITY1; nCntPriority++)
	{
		pScene = m_pTop[nCntPriority];	// シーンの先頭から始めさせるため

		// pSceneがNULLじゃなかったら
		while (pScene)
		{// ネクストがいなくなるまで代入し直す(更新)
			CScene * pSceneNext = pScene->m_pNext;

			//デスチェック
			if (pScene->m_bDeath == false)
			{
				pScene->Update();
			}

			pScene = pSceneNext;
		}
	}

	for (int nCntPriority = 0; nCntPriority < MAX_PRIORITY1; nCntPriority++)
	{
		pScene = m_pTop[nCntPriority];	// シーンの先頭から始めさせるため

		while (pScene)
		{
			CScene * pSceneNext = pScene->m_pNext;

			// pSceneの死亡フラグを立てる
			if (pScene->m_bDeath == true)
			{
				// フラグが立ったらオブジェクトを全滅させる
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
// 全ての描画処理
//=============================================================================
void CScene::DrawAll(void)
{
	for (int nCntPriority = 0; nCntPriority < MAX_PRIORITY1; nCntPriority++)
	{
		CScene *pScene;
		pScene = m_pTop[nCntPriority];	// シーンを先頭から始める

			// pSceneがNULLじゃなかったら
		while (pScene)
		{// ネクストがいなくなるまで代入し直す(描画)
			CScene * pSceneNext = pScene->m_pNext;

			pScene->Draw();

			pScene = pSceneNext;
		}
	}
}

//=============================================================================
// 全ての終了処理
//=============================================================================
void CScene::UninitAll(void)
{
	int nPriority = m_nPriority;

	// 前のオブジェクトがNULLじゃなかったら
	if (m_pPrev != NULL)
	{// 前のオブジェクトのネクストが次のオブジェクトになる
		m_pPrev->m_pNext = m_pNext;
	}

	// NULLだったら
	else
	{// 先頭のオブジェクトを次のオブジェクトにする
		m_pTop[nPriority] = m_pNext;
	}

	// 次のオブジェクトがNULLだったら
	if (m_pNext != NULL)
	{// 次のオブジェクトの前を前のオブジェクトにする
		m_pNext->m_pPrev = m_pPrev;
	}

	else
	{// 最後尾のオブジェクトを前のオブジェクトにする
		m_pCur[nPriority] = m_pPrev;
	}

	m_nNumPriority[nPriority]--;
	delete this;

}

//=============================================================================
// 開放処理
//=============================================================================
void CScene::Release(void)
{
	int nPriority = m_nPriority;

	m_bDeath = true;
}

//===================================================================================================================
// 設定
//===================================================================================================================

//=============================================================================
// オブジェクトタイプの設定
//=============================================================================
void CScene::SetObjtType(CScene::OBJTYPE objttpe)
{
	m_objtype = objttpe;
}

//=============================================================================
// ポジションの設定
//=============================================================================
void CScene::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
// ムーブの設定
//=============================================================================
void CScene::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}

//=============================================================================
// 向きの設定
//=============================================================================
void CScene::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//===================================================================================================================
// 取得
//===================================================================================================================

//=============================================================================
// オブジェクトタイプを取得
//=============================================================================
CScene::OBJTYPE CScene::GetObjtType(void)
{
	return m_objtype;
}

//=============================================================================
// ポジションを取得
//=============================================================================
D3DXVECTOR3 CScene::GetPosition(void)
{
	return m_pos;
}

//=============================================================================
// 動きを取得
//=============================================================================
D3DXVECTOR3 CScene::GetMove(void)
{
	return m_move;
}

//=============================================================================
//オブジェクトタイプ設定処理
//=============================================================================
void CScene::SetObjType(OBJTYPE ObjType)
{
	m_objtype = ObjType;
}
//=============================================================================
//オブジェクトタイプ取得処理
//=============================================================================
CScene::OBJTYPE CScene::GetObjType(void)
{
	return m_objtype;
}
//while (pScene != NULL)	//while (pScene) or while(!pScene)
//{// ネクストがいなくなるまで代入し直す
//	// ダメな理由:自分がUpdateで死ぬときネクストに行く遺言が残せなくなるから
//	pScene->Update();
//	pScene = pScene->m_pNext;
//}