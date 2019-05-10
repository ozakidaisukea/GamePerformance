//=============================================================================
//
// オブジェクト処理 [objectbg.cpp]
// Author : Ozaki
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS

#include "objectbg.h"
#include "manager.h"
#include "bullet.h"
#include "camera.h"
#include "scene3D.h"
#include "meshfield.h"
#include "model.h"
#include "meshOrbit.h"
#include "renderer.h"
#include "debugproc.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define BG_MODEL000						"data\\MODEL\\MODELBG\\keibazyo.x"
#define BG_MODEL001						"data\\MODEL\\MODELBG\\building100.x"
#define BG_MODEL002						"data\\MODEL\\MODELBG\\building200.x"
#define BG_MODEL003						"data\\MODEL\\MODELBG\\building300.x"
#define BG_MODEL004						"data\\MODEL\\MODELBG\\building400.x"
#define BG_MODELGOAL					"data\\MODEL\\MODELBG\\goal.x"
#define BG_MODELGAGE					"data\\MODEL\\MODELBG\\gage.x"

#define FAILE_NAME						"data\\TEXT\\gatemotion.txt"	// 読み込むtext名

//=============================================================================
// 変数
//=============================================================================
CObjectBG::KEY CObjectBG::m_aKeyOffset[MAX_PARTS] = {};

int	CObjectBG::m_nNumParts = {};
int	CObjectBG::m_nNumModel = {};
CObjectBG::KEY_INFO*CObjectBG::m_pKeyInfo[MAX_OBJMOTION] = {};
CObjectBG::MOTION_INFO CObjectBG::m_aMotionInfo[MAX_PARTS] = {};

//--------------------------------------------
//静的メンバ変数宣言
//--------------------------------------------
LPD3DXMESH					CObjectBG::m_pMesh[MODELTYPE_MAX] = {};				// メッシュ
LPD3DXBUFFER				CObjectBG::m_pBuffMat[MODELTYPE_MAX] = {};			// バファマット
LPDIRECT3DTEXTURE9			CObjectBG::m_pObjTexture[MODELTYPE_MAX] = {};		// テクスチャ
DWORD						CObjectBG::m_nNumMat[MODELTYPE_MAX] = {};			// モデル数
LPD3DXBUFFER				CObjectBG::m_pBuffMatModel[MAX_PARTS] = {};		// バッファ
DWORD						CObjectBG::m_nNumMatModel[MAX_PARTS] = {};			    // マテリアル情報の数
LPD3DXMESH					CObjectBG::m_pMeshModel[MAX_PARTS] = {};			// メッシュ情報へのポインタ

char						CObjectBG::m_aFileNameModel[MAX_PARTS][256] = {};
CModel*						CObjectBG::m_apModel[MAX_PARTS] = {};
int							CObjectBG::m_aIndexParent[MAX_PARTS] = {};

//--------------------------------------------
//オブジェクトクラス コンストラクタ
//--------------------------------------------
CObjectBG::CObjectBG() : CScene(3, CScene::OBJTYPE_BGMODEL)
{
	m_pos = D3DXVECTOR3(0, 0, 0);					//位置
	m_rot = D3DXVECTOR3(0, 0, 0);					//向き
	m_posold = D3DXVECTOR3(0, 0, 0);				//前回の位置
	m_move = D3DXVECTOR3(0, 0, 0);					//移動量
	D3DXMatrixIdentity(&m_mtxWorld);				//ワールドマトリックス

	m_Type = CObjectBG::MODELTYPE_BILL000,
			 CObjectBG::MODELTYPE_GOAL,
		     CObjectBG::MODELTYPE_GAGE;
}

//--------------------------------------------
//オブジェクトクラス デストラクタ
//--------------------------------------------
CObjectBG::~CObjectBG()
{
}

//--------------------------------------------
//オブジェクトの生成
//--------------------------------------------
CObjectBG *CObjectBG::Create(D3DXVECTOR3 pos,D3DXVECTOR3 rot, MODELTYPE type)
{
	//オブジェクトポインタ
	CObjectBG *pObjectBG;
	pObjectBG = new CObjectBG;

	//タイプの設定
	pObjectBG->m_Type = type;

	//オブジェクトの初期化
	pObjectBG->Init();

	//初期値が入った後
	pObjectBG->m_pos = pos;
	pObjectBG->m_rot = rot;

	//オブジェクトの情報を返す
	return pObjectBG;
}

//=============================================================================
// オブジェクトの初期化処理
//=============================================================================
HRESULT CObjectBG::Init(void)
{
	//オブジェクト種類の設定
	CScene::SetObjType(CScene::OBJTYPE_BGMODEL);

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fDestAngle = D3DX_PI * 1.0f;
	m_fDiffAngle = 0;
	LPDIRECT3DVERTEXBUFFER9 VtxBuff = NULL;		// 頂点バッファへのポインタ

	//モデルを生成	オフセット設定
	m_pModel = CModel::Create(m_pos,m_rot);

	//モデルを割り当て
	m_pModel->BindModel(m_pBuffMat[m_Type],m_nNumMat[m_Type], m_pMesh[m_Type]);

	//モデルの親を指定
	m_pModel->SetParent(NULL);

	// Textファイルから読み込み
	//FileLoad();

	return S_OK;
}

//=============================================================================
// オブジェクトの終了処理
//=============================================================================
void CObjectBG::Uninit(void)
{
	if (m_pModel != NULL)
	{
		m_pModel->Uninit();
		delete m_pModel;
		m_pModel = NULL;
	}
	//自分を消す(オブジェクトを破棄)
	Release();
}

//=============================================================================
// オブジェクトの更新処理
//=============================================================================
void CObjectBG::Update(void)
{
#if 0

	//キーボード情報を取得
	CInputKeyboard *pInput = CManager::GetInputKeyboard();

	//カメラを取得
	//CCamera *pCamera = CManager::GetCamera();

	m_posold = m_pos;


	//向きの慣性
	m_fDiffAngle = m_fDestAngle - m_rot.y;
	//角度の設定
	if (m_fDiffAngle > D3DX_PI)
	{
		m_fDiffAngle -= D3DX_PI* 2.0f;
	}
	if (m_fDiffAngle < -D3DX_PI)
	{
		m_fDiffAngle += D3DX_PI* 2.0f;
	}
	m_rot.y += m_fDiffAngle * 0.1f;

	if (m_rot.y > D3DX_PI)
	{
		m_rot.y -= D3DX_PI* 2.0f;
	}
	if (m_rot.y < -D3DX_PI)
	{
		m_rot.y += D3DX_PI* 2.0f;
	}

	//減速
	m_move.x += (0.0f - m_move.x) * 0.5f;
	m_move.z += (0.0f - m_move.z) * 0.5f;

	//位置更新
	m_pos += m_move;

#endif // 0
}

//=============================================================================
// オブジェクトの描画処理
//=============================================================================
void CObjectBG::Draw(void)
{
	//デバイスを取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス
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

	CLight *pLight = CManager::GetLight();

	// ライトを無効にする
	pDevice->LightEnable(0, FALSE);
	pDevice->LightEnable(1, FALSE);
	pDevice->LightEnable(2, FALSE);
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//減算合成
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//シャドウマトリックスの初期化
	D3DXMatrixIdentity(&mtxShadow);

	// ライトの設定
	VecLight = D3DXVECTOR4(0.5f, 1.0f, -1.0f, 0.0f);

	// 影の位置設定
	pos = D3DXVECTOR3(0.0f, 0.5f, 0.0f);

	// 法線の設定
	normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//平面を作成
	D3DXPlaneFromPointNormal(&planeField, &pos, &normal);

	//影マトリックスの設定
	D3DXMatrixShadow(&mtxShadow, &VecLight, &planeField);

	//ワールドマトリックスと掛け合わせる
	D3DXMatrixMultiply(&mtxShadow, &m_mtxWorld, &mtxShadow);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &mtxShadow);

	if (m_pModel != NULL)
	{
		m_pModel->Draw();
	}
	//レンダーステイトを元に戻す
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

	if (m_pModel != NULL)
	{
		m_pModel->Draw();
	}
}

//=============================================================================
// オブジェクトの位置設定
//=============================================================================
void CObjectBG::Setpos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
// テクスチャの読み込み処理
//=============================================================================
HRESULT CObjectBG::Load(void)
{
	//デバイスを取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATERIAL *pMat;							//マテリアルデータへのポインタ

	// Xファイルの読み込み
	D3DXLoadMeshFromX(BG_MODEL000, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[0], NULL, &m_nNumMat[0], &m_pMesh[0]);
	D3DXLoadMeshFromX(BG_MODEL001, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[1], NULL, &m_nNumMat[1], &m_pMesh[1]);
	D3DXLoadMeshFromX(BG_MODEL002, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[2], NULL, &m_nNumMat[2], &m_pMesh[2]);
	D3DXLoadMeshFromX(BG_MODEL003, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[3], NULL, &m_nNumMat[3], &m_pMesh[3]);
	D3DXLoadMeshFromX(BG_MODELGOAL,D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[4], NULL, &m_nNumMat[4], &m_pMesh[4]);
	D3DXLoadMeshFromX(BG_MODELGAGE,D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[5], NULL, &m_nNumMat[5], &m_pMesh[5]);

	//テクスチャの読み込み
	for (int nCnt = 0; nCnt < MODELTYPE_MAX; nCnt++)
	{
		//マテリアル情報からテクスチャの取得
		pMat = (D3DXMATERIAL*)m_pBuffMat[nCnt]->GetBufferPointer();

		for (int nCntMatTex = 0; nCntMatTex < (int)m_nNumMat[nCnt]; nCntMatTex++)
		{
			if (pMat[nCntMatTex].pTextureFilename != NULL)
			{
				// テクスチャの設定
				D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
					pMat[nCntMatTex].pTextureFilename,	// ファイルの名前
					&m_pObjTexture[nCnt]);				// テクスチャへのポインタ
			}
		}
	}

	return S_OK;
}

//=============================================================================
// テクスチャの破棄処理
//=============================================================================
void CObjectBG::UnLoad(void)
{
	for (int nCnt = 0; nCnt < MODELTYPE_MAX; nCnt++)
	{
		// メッシュの開放
		if (m_pMesh[nCnt] != NULL)
		{
			m_pMesh[nCnt]->Release();
			m_pMesh[nCnt] = NULL;
		}
		// マテリアルの開放
		if (m_pBuffMat[nCnt] != NULL)
		{
			m_pBuffMat[nCnt]->Release();
			m_pBuffMat[nCnt] = NULL;
		}

		//テクスチャの破棄
		if (m_pObjTexture[nCnt] != NULL)
		{
			m_pObjTexture[nCnt]->Release();
			m_pObjTexture[nCnt] = NULL;
		}
	}
}
//=============================================================================
// オブジェクトの位置
//=============================================================================
D3DXVECTOR3 CObjectBG::GetPos(void)
{
	return m_pos;
}

#if 0

//=============================================================================
// 読み込むファイル
//=============================================================================
void CObjectBG::FileLoad(void)
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
				m_pos.z + m_aKeyOffset[nIndex].fPosZ));

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

#endif // 0
//=============================================================================
// モーションの更新処理
//=============================================================================
void CObjectBG::UpdateMotion(void)
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
	m_Dubug->Print("sdsd", "\nフレーム数", m_nCountFlame, "/", m_aMotionInfo[1].aKeyInfo[m_nKey].nFrame);
	m_Dubug->Print("sd", "キーの数", m_nKey);
	m_Dubug->Print("sfsfsf", "\nパーツの位置 x", rotMotion.x, "y", rotMotion.y, "z", rotMotion.z);

#endif // DEBUG
}

//=============================================================================
// 1行分(256)の読み込み
//=============================================================================
char * CObjectBG::ReadLine(FILE *pFile, char * pDest)
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
char * CObjectBG::GetLineTop(char * pSrc)
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
int CObjectBG::PopString(char * pSrc, char * pDest)
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