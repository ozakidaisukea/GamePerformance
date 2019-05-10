//=============================================================================
//
// ジョッキー8処理 [jockey8.cpp]
// Author : Ozaki
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS

#include "jockey8.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "debugproc.h"
#include "camera.h"
#include "bullet.h"
#include "scene3D.h"
#include "model.h"
#include "meshfield.h"
#include "meshorbit.h"
#include "game.h"
#include "camera.h"
#include "light.h"
#include "fade.h"
#include "horse8.h"

#define FAILE_NAME	"data\\TEXT\\jockeymotion.txt"	// 読み込むtext名
#define JOCKEY_SPEED	(0.78f)
//=============================================================================
// 変数
//=============================================================================
CJockey8::KEY CJockey8::m_aKeyOffset[MAX_PARTS] = {};

int	CJockey8::m_nNumParts = {};
int	CJockey8::m_nNumModel = {};
CMeshOrbit*CJockey8::m_mesh;
CJockey8::KEY_INFO*CJockey8::m_pKeyInfo[MAX_PARTS] = {};
CJockey8::MOTION_INFO CJockey8::m_aMotionInfo[MAX_PARTS] = {};

//=============================================================================
// 静的メンバ-変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9 CJockey8::m_pTexture = NULL;				// テクスチャ
LPD3DXBUFFER CJockey8::m_pBuffMatModel[MAX_PARTS] = {};		// バッファ
DWORD CJockey8::m_nNumMatModel[MAX_PARTS] = {};			    // マテリアル情報の数
LPD3DXMESH CJockey8::m_pMeshModel[MAX_PARTS] = {};			// メッシュ情報へのポインタ
D3DXVECTOR3	CJockey8::m_pos = D3DXVECTOR3(0, 0, 0);			// 位置
D3DXVECTOR3 CJockey8::m_rot = D3DXVECTOR3(0, 0, 0);			// 向き
char CJockey8::m_aFileNameModel[MAX_PARTS][256] = {};
CModel*CJockey8::m_apModel[MAX_PARTS] = {};
int CJockey8::m_aIndexParent[MAX_PARTS] = {};
CJockey8::JOCKEYSTATE CJockey8::m_State = CJockey8::JOCKEYSTATE_NONE;
CJockey8::JOCKEYTYPE CJockey8::m_nType = CJockey8::JOCKEYTYPE_NONE;

//=============================================================================
// 読み込み
//=============================================================================
HRESULT CJockey8::Load(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	return S_OK;
}

//=============================================================================
// 開放
//=============================================================================
void CJockey8::Unload(void)
{
	for (int nCnt = 0; nCnt < NUM_PLAYER_MODEL; nCnt++)
	{
		// マテリアル情報へのポインタを破棄
		if (m_pBuffMatModel[nCnt] != NULL)
		{
			m_pBuffMatModel[nCnt]->Release();
			m_pBuffMatModel[nCnt] = NULL;
		}

		// メッシュ情報へのポインタを破棄
		if (m_pMeshModel[nCnt] != NULL)
		{
			m_pMeshModel[nCnt]->Release();
			m_pMeshModel[nCnt] = NULL;
		}

		//テクスチャの破棄
		if (m_pTexture != NULL)
		{
			m_pTexture->Release();
			m_pTexture = NULL;
		}
	}
}

//=============================================================================
// コンストラクタ
//=============================================================================
CJockey8::CJockey8(int nPriority, OBJTYPE objtype) :CScene(1, OBJTYPE_PLAYER)
{
	m_nCntA = 0;
	m_nCntB = 0;
	for (int nCnt = 0; nCnt < MAX_MOTION; nCnt++)
	{
		m_pKeyInfo[nCnt] = NULL;		//キー情報へのポインタ
	}
	m_nKey = {};						//現在のキーナンバー
										//m_nCountFlame = 0;					//フレーム数
	D3DXMatrixIdentity(&m_mtxRot);
	m_State = CJockey8::JOCKEYSTATE_NONE;
	m_nMotionType = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CJockey8::~CJockey8()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CJockey8::Init(void)
{
	//	デバイスの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9	pDevice = pRenderer->GetDevice();

	// 初期化変数
	m_rot = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fDestAngle = D3DX_PI * 1.0f;
	m_fDiffAngle = 0;
	m_bBrake = false;
	m_testCnt = 0;

	//モーション用変数
	m_nKey = 0;			//現在のキー
	m_nCountFlame = 0;	//現在のフレーム
	m_nMotionType = 0;	//現在のモーションタイプ

						//m_mesh = CMeshOrbit::Create(m_mtxWorld);

						// Textファイルから読み込み
	FileLoad();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CJockey8::Uninit(void)
{
	for (int nCnt = 0; nCnt < m_nNumParts; nCnt++)
	{
		if (m_apModel[nCnt] != NULL)
		{
			// モデルを空にする
			m_apModel[nCnt]->Uninit();

			// モデルを削除
			delete m_apModel[nCnt];

			// NULLにする
			m_apModel[nCnt] = NULL;
		}
	}
	// モデルの破棄
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CJockey8::Update(void)
{
#if 1
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = NULL;

	// フェードを取得
	CFade *pFade;
	pFade = CManager::GetFade();

	// レンダラーを取得
	pDevice = CManager::GetRenderer()->GetDevice();

	// デバック表示を取得
	CDebugProc *m_Dubug = CRenderer::GetDebug();

	// キーボードを取得
	CInputKeyboard *InputKeyboard;
	InputKeyboard = CManager::GetInputKeyboard();

	// メッシュフィールドを取得
	CMeshFiled *pMeshFiled;
	pMeshFiled = CGame::GetMeshFiled();

	// メッシュオービットを取得
	CMeshOrbit *pMeshOrbit;
	pMeshOrbit = CManager::GetMeshOrbit();

	// ローカル変数
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 rotMotion;

	// 位置、動き、向きを取得
	pos = CScene::GetPosition();
	move = CScene::GetMove();
	CManager *pManager = NULL;
	m_pos = CHorse8::Getpos();
	m_rot = CHorse8::Getrot();

	//========================================================
	// 上移動
	//========================================================
	m_pos.y = 20.0f;
	// モーション切り替え
	if (m_bBrake == false)
	{
		m_nMotionType = 1;
	}

	// 移動していない ニュートラル状態
	else if (m_bBrake == false)
	{
		// モーション切り替え
		m_nMotionType = 0;
	}

	//モーション更新
	UpdateMotion();

	// 位置、動き、向きの設定
	CScene::SetPosition(m_pos);
	CScene::SetMove(move);
	CScene::SetRot(m_rot);

#endif

#ifdef _DEBUG
	// 範囲設定のデバック
	//m_Dubug->Print("ssfsfsf", "\n[ Jockey 位置 ] ", "X", m_pos.x, "Y", m_pos.y, "Z", m_pos.z);

#endif
}

//=============================================================================
// 描画処理
//=============================================================================
void CJockey8::Draw(void)
{
	//デバイスを取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;		//計算用マトリックス
	D3DXMATRIX mtxParent;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//影の描画処理
	D3DXMATRIX	mtxShadow;
	D3DXPLANE	planeField;
	D3DXVECTOR4 VecLight;
	D3DXVECTOR3 pos, normal;

	// ライトの取得
	CLight *pLight = CManager::GetLight();

	// ライトを無効にする
	pDevice->LightEnable(0, FALSE);
	pDevice->LightEnable(1, FALSE);
	pDevice->LightEnable(2, FALSE);
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// 減算合成
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// シャドウマトリックスの初期化
	D3DXMatrixIdentity(&mtxShadow);

	// ライトの設定
	VecLight = D3DXVECTOR4(0.5f, 1.0f, -1.0f, 0.0f);

	// 影の位置設定
	pos = D3DXVECTOR3(0.0f, 0.5f, 0.0f);

	// 法線の設定
	normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	// 平面を作成
	D3DXPlaneFromPointNormal(&planeField, &pos, &normal);

	// 影マトリックスの設定
	D3DXMatrixShadow(&mtxShadow, &VecLight, &planeField);

	// ワールドマトリックスと掛け合わせる
	D3DXMatrixMultiply(&mtxShadow, &m_mtxWorld, &mtxShadow);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &mtxShadow);

	for (int nCnt = 0; nCnt < m_nNumParts; nCnt++)
	{
		if (m_apModel[nCnt] != NULL)
		{
			m_apModel[nCnt]->Draw();
		}
	}

	// レンダーステイトを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// ライトを有効にする
	pDevice->LightEnable(0, TRUE);
	pDevice->LightEnable(1, TRUE);
	pDevice->LightEnable(2, TRUE);
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	for (int nCnt = 0; nCnt < m_nNumParts; nCnt++)
	{
		if (m_apModel[nCnt] != NULL)
		{
			m_apModel[nCnt]->Draw();
		}
	}
}

//=============================================================================
// プレイヤーの生成
//=============================================================================
CJockey8 *CJockey8::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CJockey8::JOCKEYTYPE type)
{
	CJockey8 *pPlayer = NULL;

	if (pPlayer == NULL)
	{
		pPlayer = new CJockey8(1);

		pPlayer->Init();

		pPlayer->m_pos = pos;
		pPlayer->m_rot = rot;
		pPlayer->m_nType = type;
	}
	return pPlayer;
}

//=============================================================================
// プレイヤーのポジション取得
//=============================================================================
D3DXVECTOR3 CJockey8::GetPlayerpos(D3DXVECTOR3 pos)
{
	m_pos = pos;

	return m_pos;
}

//=============================================================================
// プレイヤーの位置取得
//=============================================================================
D3DXVECTOR3 CJockey8::Getpos(void)
{
	return m_pos;
}

//=============================================================================
// プレイヤーの向き取得
//=============================================================================
D3DXVECTOR3 CJockey8::Getrot(void)
{
	return m_rot;
}

//=============================================================================
// プレイヤーの動き取得
//=============================================================================
D3DXVECTOR3 CJockey8::Getmove(void)
{
	return m_move;
}

//=============================================================================
// 読み込むファイル
//=============================================================================
void CJockey8::FileLoad(void)
{
	//デバイスを取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// ローカル変数
	FILE * pFile;												// ファイルポインタ
	char * pStrCur;												// 文字列の先頭へのポインタ
	char aLine[256];											// 文字列の読み込み用(1行分)
	char aStr[256];												// 文字列の抜き出し用
	int	 nIndex = 0;											// 現在のインデックス
	int  nCnt = 0;
	int  nWord = 0;
	int	 nCntModel = 0;
	int	 nCntParts = 0;
	int	 nCntKey = 0;
	int	 nMotionCnt = 0;

	pFile = fopen(FAILE_NAME, "r");

	// 1行分(256文字分)読み込み)
	while (fgets(&aLine[0], 256, pFile) != NULL)
	{// キャラクターの設定が終わるまで繰り返す

	 // 文字列の先頭を設定
		pStrCur = ReadLine(pFile, &aLine[0]);
		strcpy(aStr, pStrCur);									// 文字列を取り出す

																//============================================================================================
																// モデルの数 NumModel
																//============================================================================================
		if (memcmp("NUM_MODEL = ", &aStr[0], strlen("NUM_MODEL = ")) == 0)
		{
			// 文字列が出るまで読み込み
			ReadLine(pFile, &aLine[0]);

			// 頭出し
			pStrCur += strlen("NUM_MODEL = ");

			// 対象の文字列抜き出し
			strcpy(aStr, pStrCur);
			m_nNumModel = atoi(aStr);
		}

		//============================================================================================
		// モデルのファイルネーム ModelFilename
		//============================================================================================
		if (memcmp("MODEL_FILENAME = ", &aStr[0], strlen("MODEL_FILENAME = ")) == 0)
		{
			// 文字列が出るまで読み込み
			ReadLine(pFile, &aLine[0]);

			// 頭出し
			pStrCur += strlen("MODEL_FILENAME = ");

			// 対象の文字列抜き出し
			strcpy(aStr, pStrCur);

			//必要な文字列の最後の文字までの文字数を数える
			int nNULLNum = PopString(pStrCur, &aStr[0]);

			// 文字列を取り戻す
			strcpy(aStr, pStrCur);

			// 最後の文字をNULL文字を入れる
			aStr[nNULLNum - 1] = '\0';

			// 対象の文字列から抜き出し
			strcpy(&m_aFileNameModel[nCntModel][0], aStr);

			// Xファイルの読み込み
			D3DXLoadMeshFromX(m_aFileNameModel[nCntModel],
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&m_pBuffMatModel[nCntModel],
				NULL,
				&m_nNumMatModel[nCntModel],
				&m_pMeshModel[nCntModel]);

			nCntModel++;
		}

		//============================================================================================
		// キャラクターセット numparts
		//============================================================================================
		if (memcmp(pStrCur, "CHARACTERSET", strlen("CHARACTERSET")) == 0)
		{
			// 文字列が出るまで読み込み
			ReadLine(pFile, &aLine[0]);

			// 頭出し
			pStrCur += strlen("CHARACTERSET");

			// 対象の文字列抜き出し
			strcpy(aStr, pStrCur);
		}

		//============================================================================================
		// パーツ数 numparts
		//============================================================================================
		if (memcmp(pStrCur, "NUM_PARTS = ", strlen("NUM_PARTS = ")) == 0)
		{
			// 文字列が出るまで読み込み
			ReadLine(pFile, &aLine[0]);

			// 頭出し
			pStrCur += strlen("NUM_PARTS = ");

			// 対象の文字列抜き出し
			strcpy(aStr, pStrCur);
			m_nNumParts = atoi(aStr);
		}

		//===================================================================================
		// パーツの設定 partsset
		//===================================================================================
		if (memcmp(pStrCur, "PARTSSET", strlen("PARTSSET")) == 0)
		{
			// 文字列が出るまで読み込み
			ReadLine(pFile, &aLine[0]);

			// 頭出し
			pStrCur += strlen("PARTSSET");

			// 対象の文字列抜き出し
			strcpy(aStr, pStrCur);
		}

		//===================================================================================
		// インデックス index
		//===================================================================================
		if (memcmp(pStrCur, "INDEX = ", strlen("INDEX = ")) == 0)
		{
			// 文字列が出るまで読み込み
			ReadLine(pFile, &aLine[0]);

			// 頭出し
			pStrCur += strlen("INDEX = ");

			// 対象の文字列抜き出し
			strcpy(aStr, pStrCur);

			nIndex = atoi(aStr);
		}

		//===================================================================================
		// ペアレント parent
		//===================================================================================
		if (memcmp(pStrCur, "PARENT = ", strlen("PARENT = ")) == 0)
		{
			// 文字列が出るまで読み込み
			ReadLine(pFile, &aLine[0]);

			// 頭出し
			pStrCur += strlen("PARENT = ");

			// 対象の文字列抜き出し
			strcpy(aStr, pStrCur);

			m_aIndexParent[nIndex] = atoi(aStr);
		}

		//===================================================================================
		// 位置 pos
		//===================================================================================
		if (memcmp(pStrCur, "POS = ", strlen("POS = ")) == 0)
		{
			// 文字列が出るまで読み込み
			ReadLine(pFile, &aLine[0]);

			// 頭出し
			pStrCur += strlen("POS = ");

			// POS_Xの座標
			// 対象の文字列抜き出し
			strcpy(aStr, pStrCur);
			nWord = PopString(pStrCur, &aStr[0]);
			m_aKeyOffset[nIndex].fPosX = (float)atof(pStrCur);
			pStrCur += nWord;

			// POS_Yの座標
			// 対象の文字列抜き出し
			strcpy(aStr, pStrCur);
			nWord = PopString(pStrCur, &aStr[0]);
			m_aKeyOffset[nIndex].fPosY = (float)atof(pStrCur);
			pStrCur += nWord;

			// POS_Zの座標
			// 対象の文字列抜き出し
			strcpy(aStr, pStrCur);
			nWord = PopString(pStrCur, &aStr[0]);
			m_aKeyOffset[nIndex].fPosZ = (float)atof(pStrCur);
			pStrCur += nWord;
		}

		//===================================================================================
		// 向き rot
		//===================================================================================
		if (memcmp(pStrCur, "ROT = ", strlen("ROT = ")) == 0)
		{
			// 文字列が出るまで読み込み
			ReadLine(pFile, &aLine[0]);

			// 頭出し
			pStrCur += strlen("ROT = ");

			// ROT_Xの座標
			// 対象の文字列抜き出し
			strcpy(aStr, pStrCur);
			nWord = PopString(pStrCur, &aStr[0]);
			m_aKeyOffset[nIndex].fRotX = (float)atof(pStrCur);
			pStrCur += nWord;

			// ROT_Yの座標
			// 対象の文字列抜き出し
			strcpy(aStr, pStrCur);
			nWord = PopString(pStrCur, &aStr[0]);
			m_aKeyOffset[nIndex].fRotY = (float)atof(pStrCur);
			pStrCur += nWord;

			// ROT_Zの座標
			// 対象の文字列抜き出し
			strcpy(aStr, pStrCur);
			nWord = PopString(pStrCur, &aStr[0]);
			m_aKeyOffset[nIndex].fRotZ = (float)atof(pStrCur);
			pStrCur += nWord;
		}

		//===================================================================================
		// パーツ設定終了 endpartsset
		//===================================================================================
		else if (memcmp(pStrCur, "END_PARTSSET", strlen("END_PARTSSET")) == 0)
		{
			// 文字列が出るまで読み込み
			ReadLine(pFile, &aLine[0]);

			// モデルを生成	オフセット設定
			m_apModel[nIndex] = CModel::Create(D3DXVECTOR3(
				m_pos.x + m_aKeyOffset[nIndex].fPosX,
				m_pos.y + m_aKeyOffset[nIndex].fPosY,
				m_pos.z + m_aKeyOffset[nIndex].fPosZ), D3DXVECTOR3(
				m_rot.x + m_aKeyOffset[nIndex].fRotX,
				m_rot.y + m_aKeyOffset[nIndex].fRotY,
				m_rot.z + m_aKeyOffset[nIndex].fRotZ));

			// モデルを割り当て
			m_apModel[nIndex]->BindModel(m_pBuffMatModel[nIndex], m_nNumMatModel[nIndex], m_pMeshModel[nIndex]);

			if (m_aIndexParent[nIndex] == -1)
			{
				// モデルの親を指定
				m_apModel[nIndex]->SetParent(NULL);

			}
			else
			{
				// モデルの親を指定
				m_apModel[nIndex]->SetParent(m_apModel[m_aIndexParent[nIndex]]);
			}
		}
		else if (memcmp(pStrCur, "END_CHARACTERSET", strlen("END_CHARACTERSET")) == 0)
		{// キャラ設定を終了
		 //break;
		}

		//=====================================================================================================================
		//モーション読み込み
		//======================================================================================================================
		//============================================================================
		// MOTIONSET モーションの設定
		//============================================================================
		if (memcmp(pStrCur, "MOTIONSET", strlen("MOTIONSET")) == 0)
		{
			// 文字列の先頭を設定
			pStrCur = ReadLine(pFile, &aLine[0]);

			// 頭出し
			pStrCur += strlen("MOTIONSET");

			// 文字列を取り出す
			strcpy(aStr, pStrCur);
		}

		//============================================================================
		// LOOP ループ
		//============================================================================
		if (memcmp(pStrCur, "LOOP = ", strlen("LOOP = ")) == 0)
		{
			// 文字数を返してもらう
			PopString(pStrCur, aStr);

			// 文字列の先頭を設定
			pStrCur = ReadLine(pFile, &aLine[0]);

			// 頭出し
			pStrCur += strlen("LOOP = ");

			// 文字列の先頭を設定
			strcpy(aStr, pStrCur);

			switch (atoi(pStrCur))
			{
			case 0:
				// 文字列抜き出し
				m_aMotionInfo[nMotionCnt].bLoop = false;
				break;
			case 1:
				// 文字列抜き出し
				m_aMotionInfo[nMotionCnt].bLoop = true;
				break;
			}
		}

		//============================================================================
		// NUM_KEY キー数
		//============================================================================
		if (memcmp(pStrCur, "NUM_KEY = ", strlen("NUM_KEY = ")) == 0)
		{
			// 文字数を返してもらう
			//PopString(pStrCur, aStr);

			// 文字列の先頭を設定
			pStrCur = ReadLine(pFile, &aLine[0]);

			// 頭出し
			pStrCur += strlen("NUM_KEY = ");

			// 文字列の先頭を設定
			strcpy(aStr, pStrCur);

			// 文字列抜き出し
			m_aMotionInfo[nMotionCnt].nNumKey = atoi(pStrCur);
		}

		//============================================================================
		// KEYSET キーの設定
		//============================================================================
		if (memcmp(pStrCur, "KEYSET", strlen("KEYSET")) == 0)
		{
			// 文字数を返してもらう
			PopString(pStrCur, aStr);

			// 頭出し
			pStrCur += strlen("KEYSET");

			// １行読み込み
			fgets(&aLine[0], 256, pFile);

			// 文字列の先頭を設定
			pStrCur = ReadLine(pFile, &aLine[0]);

			// 文字列の先頭を設定
			strcpy(aStr, pStrCur);
		}

		//============================================================================
		// FRAME フレーム設定
		//============================================================================
		if (memcmp(pStrCur, "FRAME = ", strlen("FRAME = ")) == 0)
		{
			// 文字列の先頭を設定
			pStrCur = ReadLine(pFile, &aLine[0]);

			// 頭出し
			pStrCur += strlen("FRAME = ");

			// 文字列の先頭を設定
			strcpy(aStr, pStrCur);

			m_aMotionInfo[nMotionCnt].aKeyInfo[nCntKey].nFrame = atoi(pStrCur);

			// １行読み込み
			fgets(&aLine[0], 256, pFile);

			// 文字列の先頭を設定
			pStrCur = ReadLine(pFile, &aLine[0]);

			// 文字列の先頭を設定
			strcpy(aStr, pStrCur);
		}

		//============================================================================
		// KEY キー
		//============================================================================
		if (memcmp(pStrCur, "KEY", strlen("KEY")) == 0)
		{
			// 文字列の先頭を設定
			pStrCur = ReadLine(pFile, &aLine[0]);

			// １行読み込み
			fgets(&aLine[0], 256, pFile);
			// 文字列の先頭を設定　\t \n " "	とばす
			pStrCur = ReadLine(pFile, &aLine[0]);

			// 文字列の先頭を設定
			strcpy(aStr, pStrCur);
		}

		//============================================================================
		// POS 位置モーション
		//============================================================================
		if (memcmp(pStrCur, "POS = ", strlen("POS = ")) == 0)
		{
			// 頭出し
			pStrCur += strlen("POS = ");

			// 文字列の先頭を設定
			strcpy(aStr, pStrCur);

			//===================================
			// POSX
			//===================================

			// 文字数を返してもらう
			nWord = PopString(pStrCur, &aStr[0]);

			// POS.X代入
			m_aMotionInfo[nMotionCnt].aKeyInfo[nCntKey].aKey[nCntParts].fPosX = (float)atof(pStrCur);

			// 文字数分進める
			pStrCur += nWord;

			//===================================
			// POSY
			//===================================

			// 文字数を返してもらう
			nWord = PopString(pStrCur, &aStr[0]);

			// POS.Y代入
			m_aMotionInfo[nMotionCnt].aKeyInfo[nCntKey].aKey[nCntParts].fPosY = (float)atof(pStrCur);

			// 文字数分進める
			pStrCur += nWord;

			//===================================
			// POSZ
			//===================================

			// 文字数を返してもらう
			nWord = PopString(pStrCur, &aStr[0]);

			// POS.Z代入
			m_aMotionInfo[nMotionCnt].aKeyInfo[nCntKey].aKey[nCntParts].fPosZ = (float)atof(pStrCur);

			// 文字列の先頭を設定
			pStrCur = ReadLine(pFile, &aLine[0]);

			// １行読み込み
			fgets(&aLine[0], 256, pFile);

			// 文字列の先頭を設定
			pStrCur = ReadLine(pFile, &aLine[0]);

			// 文字列の先頭を設定
			strcpy(aStr, pStrCur);
		}

		//============================================================================
		// ROT 向きモーション
		//============================================================================
		if (memcmp(pStrCur, "ROT = ", strlen("ROT = ")) == 0)
		{
			// 頭出し
			pStrCur += strlen("ROT = ");

			// 文字列の先頭を設定
			strcpy(aStr, pStrCur);

			//===================================
			// ROTX
			//===================================
			// 文字数を返してもらう
			nWord = PopString(pStrCur, &aStr[0]);
			// RotX
			m_aMotionInfo[nMotionCnt].aKeyInfo[nCntKey].aKey[nCntParts].fRotX = (float)atof(pStrCur);
			// 文字数分進める
			pStrCur += nWord;

			//===================================
			// ROTY
			//===================================
			// 文字数を返してもらう
			nWord = PopString(pStrCur, &aStr[0]);
			// RotY
			m_aMotionInfo[nMotionCnt].aKeyInfo[nCntKey].aKey[nCntParts].fRotY = (float)atof(pStrCur);
			// 文字数分進める
			pStrCur += nWord;

			//===================================
			// ROTZ
			//===================================
			// 文字数を返してもらう
			nWord = PopString(pStrCur, &aStr[0]);
			// RotZ
			m_aMotionInfo[nMotionCnt].aKeyInfo[nCntKey].aKey[nCntParts].fRotZ = (float)atof(pStrCur);
			// 文字列の先頭を設定
			pStrCur = ReadLine(pFile, &aLine[0]);
			// １行読み込み
			fgets(&aLine[0], 256, pFile);
			// 文字列の先頭を設定
			pStrCur = ReadLine(pFile, &aLine[0]);
			// 文字列の先頭を設定
			strcpy(aStr, pStrCur);
		}

		//============================================================================
		// END_KEY キーの終了
		//============================================================================
		if (memcmp(pStrCur, "END_KEY", strlen("END_KEY")) == 0)
		{
			// 頭出し
			pStrCur += strlen("END_KEY");

			// １行読み込み
			fgets(&aLine[0], 256, pFile);


			// 文字列の先頭を設定
			pStrCur = ReadLine(pFile, &aLine[0]);

			// 文字列の先頭を設定
			strcpy(aStr, pStrCur);

			// パーツのカウントを進める
			nCntParts++;
		}

		//============================================================================
		// END_KEYSET キーの設定の終了
		//============================================================================
		if (memcmp(pStrCur, "END_KEYSET", strlen("END_KEYSET")) == 0)
		{
			// 文字列の先頭を設定
			pStrCur = ReadLine(pFile, &aLine[0]);

			// カウントを進める
			nCntKey++;

			nCntParts = 0;
		}
		else
		{
			// 文字列の先頭を設定
			pStrCur = ReadLine(pFile, &aLine[0]);
		}

		//============================================================================
		// END_MOTIONSET モーションの設定の終了
		//============================================================================
		if (memcmp(pStrCur, "END_MOTIONSET", strlen("END_MOTIONSET")) == 0)
		{
			// モーションの情報をセット
			m_pKeyInfo[nMotionCnt] = &m_aMotionInfo[nMotionCnt].aKeyInfo[0];
			nCntKey = 0;
			nMotionCnt++;
		}

		//============================================================================
		// END_SCRIPT スクリプトの終わり
		//============================================================================
		if (memcmp(pStrCur, "END_SCRIPT	", strlen("END_SCRIPT")) == 0)
		{
			break;
		}
	}
	fclose(pFile);
}

//=============================================================================
// モーションの更新処理
//=============================================================================
void CJockey8::UpdateMotion(void)
{
	KEY			*pKey, *pKeyNext;			// 現在のキー、次のキー

	float fRateMotion;						//モーションカウンターの相対値
	float fDiffMotion;						//差分
	D3DXVECTOR3 rotMotion;


	if (m_aMotionInfo[m_nMotionType].nNumKey <= m_nKey)
	{
		m_nKey = 0;
	}

	for (int nCntModel = 0; nCntModel < m_nNumParts; nCntModel++)
	{
		if (m_apModel[nCntModel] != NULL)
		{
			// 現在のキー
			pKey = &m_pKeyInfo[m_nMotionType][m_nKey].aKey[nCntModel];

			// 次のキー
			pKeyNext = &m_pKeyInfo[m_nMotionType][(m_nKey + 1) % m_aMotionInfo[m_nMotionType].nNumKey].aKey[nCntModel];

			// 相対値
			fRateMotion = (float)m_nCountFlame / (float)m_pKeyInfo[m_nMotionType][m_nKey].nFrame;

			// X差分
			fDiffMotion = pKeyNext->fRotX - pKey->fRotX;
			rotMotion.x = pKey->fRotX + (fDiffMotion * fRateMotion);

			// Y差分
			fDiffMotion = pKeyNext->fRotY - pKey->fRotY;
			rotMotion.y = pKey->fRotY + (fDiffMotion * fRateMotion);

			// Z差分
			fDiffMotion = pKeyNext->fRotZ - pKey->fRotZ;
			rotMotion.z = pKey->fRotZ + (fDiffMotion * fRateMotion);

			m_apModel[nCntModel]->SetRot(rotMotion);
		}
	}

	if (m_nKey <= m_aMotionInfo[m_nMotionType].nNumKey)
	{
		m_nCountFlame++;
	}

	if (m_nCountFlame > m_pKeyInfo[m_nMotionType][m_nKey].nFrame)
	{
		m_nKey = (m_nKey + 1) % m_aMotionInfo[m_nMotionType].nNumKey;

		m_nCountFlame = 0;
	}
	/*else
	{
	m_nKey += 1;
	}*/

#ifdef _DEBUG
	// デバック表示を取得
	CDebugProc *m_Dubug = CRenderer::GetDebug();
	//m_Dubug->Print("sdsd", "\nフレーム数", m_nCountFlame, "/", m_aMotionInfo[1].aKeyInfo[m_nKey].nFrame);
	//m_Dubug->Print("sd", "キーの数", m_nKey);
	//m_Dubug->Print("sfsfsf", "\nパーツの位置 x", rotMotion.x, "y", rotMotion.y, "z", rotMotion.z);

#endif // DEBUG
}

//=============================================================================
// プレイヤーのnCntAを取得
//=============================================================================
int CJockey8::GetCntA(void)
{
	return m_nCntA;
}

//=============================================================================
// プレイヤーのnCntBを取得
//=============================================================================
int CJockey8::GetCntB(void)
{
	return m_nCntB;
}

//=============================================================================
// 1行分(256)の読み込み
//=============================================================================
char * CJockey8::ReadLine(FILE *pFile, char * pDest)
{
	// 1行分(256文字分)読み込み)
	while (1)
	{// 有効な文字列が見つかるまで回す

		if (memcmp(pDest, "#", strlen("#")) == 0)
		{// コメント行の場合、次の行へ進む
			pDest += strlen("\n");
			//break;
		}
		else if (memcmp(pDest, " ", strlen(" ")) == 0)
		{// スペース行の場合、次の行へ進む

			pDest++;

			// まだスペースがある場合なくなるまで回す
			while (memcmp(pDest, " ", strlen(" ")) == 0)
			{
				if (memcmp(pDest, " ", strlen(" ")) == 0)
				{// スペースの場合、次の行へ進む
					pDest++;
				}
				else
				{
					// スペースがなくなったら終了
					break;
				}
			}
			// スペースがなくなったら終了
			break;
		}
		else if (memcmp(pDest, "\n", strlen("\n")) == 0)
		{// 改行の場合、次の行へ進む
			pDest += strlen("\n");
		}
		else if (memcmp(pDest, "\t", strlen("\t")) == 0)
		{// TAB行の場合、次の行へ進む

			pDest += strlen("\t");

			// まだTABがあったら回す
			while (memcmp(pDest, "\t", strlen("\t")) == 0)
			{
				if (memcmp(pDest, "\t", strlen("\t")) == 0)
				{// TAB行の場合、次の行へ進む
					pDest += strlen("\t");
				}
				else
				{
					// TABがなくなったら終了
					break;
				}
			}
			// TABがなくなったら終了
			break;
		}
		// 有効な文字列があれば終了する
		else
		{
			break;
		}
	}
	return pDest;
}

//=============================================================================
// 文字列の先頭を取得
//=============================================================================
char * CJockey8::GetLineTop(char * pSrc)
{
	while (1)
	{// 有効な文字列が見つかるまで回す

		if (memcmp(pSrc, "\t", 2) == 0)
		{// TAB行の場合、次の行へ進む
			pSrc += strlen("\t");			// 頭出し
		}
		if (memcmp(pSrc, " ", 1) == 0)
		{// スペース行の場合、次の行へ進む
			pSrc += strlen(" ");			// 頭出し
		}
		else
		{// 有効な文字列があれば終了する
			break;
		}
	}

	return S_OK;
}

//=============================================================================
// 文字列を抜き出す
//=============================================================================
int CJockey8::PopString(char * pSrc, char * pDest)
{
	int Word = 0;

	while (1)
	{// スペースの後に文字列があるまで回す
	 // 頭出し
		pSrc += 1;
		Word += 1;

		// 頭出し
		if (memcmp(pSrc, " ", strlen(" ")) == 0)
		{
			pSrc = "\0";
			Word += 1;
			break;
		}

		// 頭出し
		if (memcmp(pSrc, "\t", strlen("\t")) == 0)
		{
			pSrc = "\0";
			Word += strlen("\t");
			break;
		}

		// 文字列のデータ、比較する文字列、比較する
		else if (memcmp(pSrc, "\n", strlen("\n")) == 0)
		{
			// 頭出し
			Word += strlen("\n");
			break;
		}
	}
	strcpy(pDest, pSrc);
	// 文字列分の数を進める
	return Word;
}