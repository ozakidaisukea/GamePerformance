//=============================================================================
//
// �I�u�W�F�N�g���� [objectbg.cpp]
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
// �}�N����`
//*****************************************************************************
#define BG_MODEL000						"data\\MODEL\\MODELBG\\keibazyo.x"
#define BG_MODEL001						"data\\MODEL\\MODELBG\\building100.x"
#define BG_MODEL002						"data\\MODEL\\MODELBG\\building200.x"
#define BG_MODEL003						"data\\MODEL\\MODELBG\\building300.x"
#define BG_MODEL004						"data\\MODEL\\MODELBG\\building400.x"
#define BG_MODELGOAL					"data\\MODEL\\MODELBG\\goal.x"
#define BG_MODELGAGE					"data\\MODEL\\MODELBG\\gage.x"

#define FAILE_NAME						"data\\TEXT\\gatemotion.txt"	// �ǂݍ���text��

//=============================================================================
// �ϐ�
//=============================================================================
CObjectBG::KEY CObjectBG::m_aKeyOffset[MAX_PARTS] = {};

int	CObjectBG::m_nNumParts = {};
int	CObjectBG::m_nNumModel = {};
CObjectBG::KEY_INFO*CObjectBG::m_pKeyInfo[MAX_OBJMOTION] = {};
CObjectBG::MOTION_INFO CObjectBG::m_aMotionInfo[MAX_PARTS] = {};

//--------------------------------------------
//�ÓI�����o�ϐ��錾
//--------------------------------------------
LPD3DXMESH					CObjectBG::m_pMesh[MODELTYPE_MAX] = {};				// ���b�V��
LPD3DXBUFFER				CObjectBG::m_pBuffMat[MODELTYPE_MAX] = {};			// �o�t�@�}�b�g
LPDIRECT3DTEXTURE9			CObjectBG::m_pObjTexture[MODELTYPE_MAX] = {};		// �e�N�X�`��
DWORD						CObjectBG::m_nNumMat[MODELTYPE_MAX] = {};			// ���f����
LPD3DXBUFFER				CObjectBG::m_pBuffMatModel[MAX_PARTS] = {};		// �o�b�t�@
DWORD						CObjectBG::m_nNumMatModel[MAX_PARTS] = {};			    // �}�e���A�����̐�
LPD3DXMESH					CObjectBG::m_pMeshModel[MAX_PARTS] = {};			// ���b�V�����ւ̃|�C���^

char						CObjectBG::m_aFileNameModel[MAX_PARTS][256] = {};
CModel*						CObjectBG::m_apModel[MAX_PARTS] = {};
int							CObjectBG::m_aIndexParent[MAX_PARTS] = {};

//--------------------------------------------
//�I�u�W�F�N�g�N���X �R���X�g���N�^
//--------------------------------------------
CObjectBG::CObjectBG() : CScene(3, CScene::OBJTYPE_BGMODEL)
{
	m_pos = D3DXVECTOR3(0, 0, 0);					//�ʒu
	m_rot = D3DXVECTOR3(0, 0, 0);					//����
	m_posold = D3DXVECTOR3(0, 0, 0);				//�O��̈ʒu
	m_move = D3DXVECTOR3(0, 0, 0);					//�ړ���
	D3DXMatrixIdentity(&m_mtxWorld);				//���[���h�}�g���b�N�X

	m_Type = CObjectBG::MODELTYPE_BILL000,
			 CObjectBG::MODELTYPE_GOAL,
		     CObjectBG::MODELTYPE_GAGE;
}

//--------------------------------------------
//�I�u�W�F�N�g�N���X �f�X�g���N�^
//--------------------------------------------
CObjectBG::~CObjectBG()
{
}

//--------------------------------------------
//�I�u�W�F�N�g�̐���
//--------------------------------------------
CObjectBG *CObjectBG::Create(D3DXVECTOR3 pos,D3DXVECTOR3 rot, MODELTYPE type)
{
	//�I�u�W�F�N�g�|�C���^
	CObjectBG *pObjectBG;
	pObjectBG = new CObjectBG;

	//�^�C�v�̐ݒ�
	pObjectBG->m_Type = type;

	//�I�u�W�F�N�g�̏�����
	pObjectBG->Init();

	//�����l����������
	pObjectBG->m_pos = pos;
	pObjectBG->m_rot = rot;

	//�I�u�W�F�N�g�̏���Ԃ�
	return pObjectBG;
}

//=============================================================================
// �I�u�W�F�N�g�̏���������
//=============================================================================
HRESULT CObjectBG::Init(void)
{
	//�I�u�W�F�N�g��ނ̐ݒ�
	CScene::SetObjType(CScene::OBJTYPE_BGMODEL);

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fDestAngle = D3DX_PI * 1.0f;
	m_fDiffAngle = 0;
	LPDIRECT3DVERTEXBUFFER9 VtxBuff = NULL;		// ���_�o�b�t�@�ւ̃|�C���^

	//���f���𐶐�	�I�t�Z�b�g�ݒ�
	m_pModel = CModel::Create(m_pos,m_rot);

	//���f�������蓖��
	m_pModel->BindModel(m_pBuffMat[m_Type],m_nNumMat[m_Type], m_pMesh[m_Type]);

	//���f���̐e���w��
	m_pModel->SetParent(NULL);

	// Text�t�@�C������ǂݍ���
	//FileLoad();

	return S_OK;
}

//=============================================================================
// �I�u�W�F�N�g�̏I������
//=============================================================================
void CObjectBG::Uninit(void)
{
	if (m_pModel != NULL)
	{
		m_pModel->Uninit();
		delete m_pModel;
		m_pModel = NULL;
	}
	//����������(�I�u�W�F�N�g��j��)
	Release();
}

//=============================================================================
// �I�u�W�F�N�g�̍X�V����
//=============================================================================
void CObjectBG::Update(void)
{
#if 0

	//�L�[�{�[�h�����擾
	CInputKeyboard *pInput = CManager::GetInputKeyboard();

	//�J�������擾
	//CCamera *pCamera = CManager::GetCamera();

	m_posold = m_pos;


	//�����̊���
	m_fDiffAngle = m_fDestAngle - m_rot.y;
	//�p�x�̐ݒ�
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

	//����
	m_move.x += (0.0f - m_move.x) * 0.5f;
	m_move.z += (0.0f - m_move.z) * 0.5f;

	//�ʒu�X�V
	m_pos += m_move;

#endif // 0
}

//=============================================================================
// �I�u�W�F�N�g�̕`�揈��
//=============================================================================
void CObjectBG::Draw(void)
{
	//�f�o�C�X���擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxParent;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);
	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);
	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//�e�̕`�揈��
	D3DXMATRIX	mtxShadow;
	D3DXPLANE	planeField;
	D3DXVECTOR4 VecLight;
	D3DXVECTOR3 pos, normal;

	CLight *pLight = CManager::GetLight();

	// ���C�g�𖳌��ɂ���
	pDevice->LightEnable(0, FALSE);
	pDevice->LightEnable(1, FALSE);
	pDevice->LightEnable(2, FALSE);
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//���Z����
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//�V���h�E�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxShadow);

	// ���C�g�̐ݒ�
	VecLight = D3DXVECTOR4(0.5f, 1.0f, -1.0f, 0.0f);

	// �e�̈ʒu�ݒ�
	pos = D3DXVECTOR3(0.0f, 0.5f, 0.0f);

	// �@���̐ݒ�
	normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//���ʂ��쐬
	D3DXPlaneFromPointNormal(&planeField, &pos, &normal);

	//�e�}�g���b�N�X�̐ݒ�
	D3DXMatrixShadow(&mtxShadow, &VecLight, &planeField);

	//���[���h�}�g���b�N�X�Ɗ|�����킹��
	D3DXMatrixMultiply(&mtxShadow, &m_mtxWorld, &mtxShadow);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxShadow);

	if (m_pModel != NULL)
	{
		m_pModel->Draw();
	}
	//�����_�[�X�e�C�g�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// ���C�g��L���ɂ���
	pDevice->LightEnable(0, TRUE);
	pDevice->LightEnable(1, TRUE);
	pDevice->LightEnable(2, TRUE);
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	if (m_pModel != NULL)
	{
		m_pModel->Draw();
	}
}

//=============================================================================
// �I�u�W�F�N�g�̈ʒu�ݒ�
//=============================================================================
void CObjectBG::Setpos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
// �e�N�X�`���̓ǂݍ��ݏ���
//=============================================================================
HRESULT CObjectBG::Load(void)
{
	//�f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATERIAL *pMat;							//�}�e���A���f�[�^�ւ̃|�C���^

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(BG_MODEL000, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[0], NULL, &m_nNumMat[0], &m_pMesh[0]);
	D3DXLoadMeshFromX(BG_MODEL001, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[1], NULL, &m_nNumMat[1], &m_pMesh[1]);
	D3DXLoadMeshFromX(BG_MODEL002, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[2], NULL, &m_nNumMat[2], &m_pMesh[2]);
	D3DXLoadMeshFromX(BG_MODEL003, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[3], NULL, &m_nNumMat[3], &m_pMesh[3]);
	D3DXLoadMeshFromX(BG_MODELGOAL,D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[4], NULL, &m_nNumMat[4], &m_pMesh[4]);
	D3DXLoadMeshFromX(BG_MODELGAGE,D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[5], NULL, &m_nNumMat[5], &m_pMesh[5]);

	//�e�N�X�`���̓ǂݍ���
	for (int nCnt = 0; nCnt < MODELTYPE_MAX; nCnt++)
	{
		//�}�e���A����񂩂�e�N�X�`���̎擾
		pMat = (D3DXMATERIAL*)m_pBuffMat[nCnt]->GetBufferPointer();

		for (int nCntMatTex = 0; nCntMatTex < (int)m_nNumMat[nCnt]; nCntMatTex++)
		{
			if (pMat[nCntMatTex].pTextureFilename != NULL)
			{
				// �e�N�X�`���̐ݒ�
				D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
					pMat[nCntMatTex].pTextureFilename,	// �t�@�C���̖��O
					&m_pObjTexture[nCnt]);				// �e�N�X�`���ւ̃|�C���^
			}
		}
	}

	return S_OK;
}

//=============================================================================
// �e�N�X�`���̔j������
//=============================================================================
void CObjectBG::UnLoad(void)
{
	for (int nCnt = 0; nCnt < MODELTYPE_MAX; nCnt++)
	{
		// ���b�V���̊J��
		if (m_pMesh[nCnt] != NULL)
		{
			m_pMesh[nCnt]->Release();
			m_pMesh[nCnt] = NULL;
		}
		// �}�e���A���̊J��
		if (m_pBuffMat[nCnt] != NULL)
		{
			m_pBuffMat[nCnt]->Release();
			m_pBuffMat[nCnt] = NULL;
		}

		//�e�N�X�`���̔j��
		if (m_pObjTexture[nCnt] != NULL)
		{
			m_pObjTexture[nCnt]->Release();
			m_pObjTexture[nCnt] = NULL;
		}
	}
}
//=============================================================================
// �I�u�W�F�N�g�̈ʒu
//=============================================================================
D3DXVECTOR3 CObjectBG::GetPos(void)
{
	return m_pos;
}

#if 0

//=============================================================================
// �ǂݍ��ރt�@�C��
//=============================================================================
void CObjectBG::FileLoad(void)
{
	//�f�o�C�X���擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// ���[�J���ϐ�
	FILE * pFile;												// �t�@�C���|�C���^
	char * pStrCur;												// ������̐擪�ւ̃|�C���^
	char aLine[256];											// ������̓ǂݍ��ݗp(1�s��)
	char aStr[256];												// ������̔����o���p
	int	 nIndex = 0;											// ���݂̃C���f�b�N�X
	int  nCnt = 0;
	int  nWord = 0;
	int	 nCntModel = 0;
	int	 nCntParts = 0;
	int	 nCntKey = 0;
	int	 nMotionCnt = 0;

	pFile = fopen(FAILE_NAME, "r");

	// 1�s��(256������)�ǂݍ���)
	while (fgets(&aLine[0], 256, pFile) != NULL)
	{// �L�����N�^�[�̐ݒ肪�I���܂ŌJ��Ԃ�

	 // ������̐擪��ݒ�
		pStrCur = ReadLine(pFile, &aLine[0]);
		strcpy(aStr, pStrCur);									// ����������o��

		//============================================================================================
		// ���f���̐� NumModel
		//============================================================================================
		if (memcmp("NUM_MODEL = ", &aStr[0], strlen("NUM_MODEL = ")) == 0)
		{
			// �����񂪏o��܂œǂݍ���
			ReadLine(pFile, &aLine[0]);

			// ���o��
			pStrCur += strlen("NUM_MODEL = ");

			// �Ώۂ̕����񔲂��o��
			strcpy(aStr, pStrCur);
			m_nNumModel = atoi(aStr);
		}

		//============================================================================================
		// ���f���̃t�@�C���l�[�� ModelFilename
		//============================================================================================
		if (memcmp("MODEL_FILENAME = ", &aStr[0], strlen("MODEL_FILENAME = ")) == 0)
		{
			// �����񂪏o��܂œǂݍ���
			ReadLine(pFile, &aLine[0]);

			// ���o��
			pStrCur += strlen("MODEL_FILENAME = ");

			// �Ώۂ̕����񔲂��o��
			strcpy(aStr, pStrCur);

			//�K�v�ȕ�����̍Ō�̕����܂ł̕������𐔂���
			int nNULLNum = PopString(pStrCur, &aStr[0]);

			// ����������߂�
			strcpy(aStr, pStrCur);

			// �Ō�̕�����NULL����������
			aStr[nNULLNum - 1] = '\0';

			// �Ώۂ̕����񂩂甲���o��
			strcpy(&m_aFileNameModel[nCntModel][0], aStr);

			// X�t�@�C���̓ǂݍ���
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
		// �L�����N�^�[�Z�b�g numparts
		//============================================================================================
		if (memcmp(pStrCur, "CHARACTERSET", strlen("CHARACTERSET")) == 0)
		{
			// �����񂪏o��܂œǂݍ���
			ReadLine(pFile, &aLine[0]);

			// ���o��
			pStrCur += strlen("CHARACTERSET");

			// �Ώۂ̕����񔲂��o��
			strcpy(aStr, pStrCur);
		}

		//============================================================================================
		// �p�[�c�� numparts
		//============================================================================================
		if (memcmp(pStrCur, "NUM_PARTS = ", strlen("NUM_PARTS = ")) == 0)
		{
			// �����񂪏o��܂œǂݍ���
			ReadLine(pFile, &aLine[0]);

			// ���o��
			pStrCur += strlen("NUM_PARTS = ");

			// �Ώۂ̕����񔲂��o��
			strcpy(aStr, pStrCur);
			m_nNumParts = atoi(aStr);
		}

		//===================================================================================
		// �p�[�c�̐ݒ� partsset
		//===================================================================================
		if (memcmp(pStrCur, "PARTSSET", strlen("PARTSSET")) == 0)
		{
			// �����񂪏o��܂œǂݍ���
			ReadLine(pFile, &aLine[0]);

			// ���o��
			pStrCur += strlen("PARTSSET");

			// �Ώۂ̕����񔲂��o��
			strcpy(aStr, pStrCur);
		}

		//===================================================================================
		// �C���f�b�N�X index
		//===================================================================================
		if (memcmp(pStrCur, "INDEX = ", strlen("INDEX = ")) == 0)
		{
			// �����񂪏o��܂œǂݍ���
			ReadLine(pFile, &aLine[0]);

			// ���o��
			pStrCur += strlen("INDEX = ");

			// �Ώۂ̕����񔲂��o��
			strcpy(aStr, pStrCur);

			nIndex = atoi(aStr);
		}

		//===================================================================================
		// �y�A�����g parent
		//===================================================================================
		if (memcmp(pStrCur, "PARENT = ", strlen("PARENT = ")) == 0)
		{
			// �����񂪏o��܂œǂݍ���
			ReadLine(pFile, &aLine[0]);

			// ���o��
			pStrCur += strlen("PARENT = ");

			// �Ώۂ̕����񔲂��o��
			strcpy(aStr, pStrCur);

			m_aIndexParent[nIndex] = atoi(aStr);
		}

		//===================================================================================
		// �ʒu pos
		//===================================================================================
		if (memcmp(pStrCur, "POS = ", strlen("POS = ")) == 0)
		{
			// �����񂪏o��܂œǂݍ���
			ReadLine(pFile, &aLine[0]);

			// ���o��
			pStrCur += strlen("POS = ");

			// POS_X�̍��W
			// �Ώۂ̕����񔲂��o��
			strcpy(aStr, pStrCur);
			nWord = PopString(pStrCur, &aStr[0]);
			m_aKeyOffset[nIndex].fPosX = (float)atof(pStrCur);
			pStrCur += nWord;

			// POS_Y�̍��W
			// �Ώۂ̕����񔲂��o��
			strcpy(aStr, pStrCur);
			nWord = PopString(pStrCur, &aStr[0]);
			m_aKeyOffset[nIndex].fPosY = (float)atof(pStrCur);
			pStrCur += nWord;

			// POS_Z�̍��W
			// �Ώۂ̕����񔲂��o��
			strcpy(aStr, pStrCur);
			nWord = PopString(pStrCur, &aStr[0]);
			m_aKeyOffset[nIndex].fPosZ = (float)atof(pStrCur);
			pStrCur += nWord;
		}

		//===================================================================================
		// ���� rot
		//===================================================================================
		if (memcmp(pStrCur, "ROT = ", strlen("ROT = ")) == 0)
		{
			// �����񂪏o��܂œǂݍ���
			ReadLine(pFile, &aLine[0]);

			// ���o��
			pStrCur += strlen("ROT = ");

			// ROT_X�̍��W
			// �Ώۂ̕����񔲂��o��
			strcpy(aStr, pStrCur);
			nWord = PopString(pStrCur, &aStr[0]);
			m_aKeyOffset[nIndex].fRotX = (float)atof(pStrCur);
			pStrCur += nWord;

			// ROT_Y�̍��W
			// �Ώۂ̕����񔲂��o��
			strcpy(aStr, pStrCur);
			nWord = PopString(pStrCur, &aStr[0]);
			m_aKeyOffset[nIndex].fRotY = (float)atof(pStrCur);
			pStrCur += nWord;

			// ROT_Z�̍��W
			// �Ώۂ̕����񔲂��o��
			strcpy(aStr, pStrCur);
			nWord = PopString(pStrCur, &aStr[0]);
			m_aKeyOffset[nIndex].fRotZ = (float)atof(pStrCur);
			pStrCur += nWord;
		}

		//===================================================================================
		// �p�[�c�ݒ�I�� endpartsset
		//===================================================================================
		else if (memcmp(pStrCur, "END_PARTSSET", strlen("END_PARTSSET")) == 0)
		{
			// �����񂪏o��܂œǂݍ���
			ReadLine(pFile, &aLine[0]);

			// ���f���𐶐�	�I�t�Z�b�g�ݒ�
			m_apModel[nIndex] = CModel::Create(D3DXVECTOR3(
				m_pos.x + m_aKeyOffset[nIndex].fPosX,
				m_pos.y + m_aKeyOffset[nIndex].fPosY,
				m_pos.z + m_aKeyOffset[nIndex].fPosZ));

			// ���f�������蓖��
			m_apModel[nIndex]->BindModel(m_pBuffMatModel[nIndex], m_nNumMatModel[nIndex], m_pMeshModel[nIndex]);

			if (m_aIndexParent[nIndex] == -1)
			{
				// ���f���̐e���w��
				m_apModel[nIndex]->SetParent(NULL);

			}
			else
			{
				// ���f���̐e���w��
				m_apModel[nIndex]->SetParent(m_apModel[m_aIndexParent[nIndex]]);
			}
		}
		else if (memcmp(pStrCur, "END_CHARACTERSET", strlen("END_CHARACTERSET")) == 0)
		{// �L�����ݒ���I��
		 //break;
		}

		//=====================================================================================================================
		//���[�V�����ǂݍ���
		//======================================================================================================================
		//============================================================================
		// MOTIONSET ���[�V�����̐ݒ�
		//============================================================================
		if (memcmp(pStrCur, "MOTIONSET", strlen("MOTIONSET")) == 0)
		{
			// ������̐擪��ݒ�
			pStrCur = ReadLine(pFile, &aLine[0]);

			// ���o��
			pStrCur += strlen("MOTIONSET");

			// ����������o��
			strcpy(aStr, pStrCur);
		}

		//============================================================================
		// LOOP ���[�v
		//============================================================================
		if (memcmp(pStrCur, "LOOP = ", strlen("LOOP = ")) == 0)
		{
			// ��������Ԃ��Ă��炤
			PopString(pStrCur, aStr);

			// ������̐擪��ݒ�
			pStrCur = ReadLine(pFile, &aLine[0]);

			// ���o��
			pStrCur += strlen("LOOP = ");

			// ������̐擪��ݒ�
			strcpy(aStr, pStrCur);

			switch (atoi(pStrCur))
			{
			case 0:
				// �����񔲂��o��
				m_aMotionInfo[nMotionCnt].bLoop = false;
				break;
			case 1:
				// �����񔲂��o��
				m_aMotionInfo[nMotionCnt].bLoop = true;
				break;
			}
		}

		//============================================================================
		// NUM_KEY �L�[��
		//============================================================================
		if (memcmp(pStrCur, "NUM_KEY = ", strlen("NUM_KEY = ")) == 0)
		{
			// ��������Ԃ��Ă��炤
			//PopString(pStrCur, aStr);

			// ������̐擪��ݒ�
			pStrCur = ReadLine(pFile, &aLine[0]);

			// ���o��
			pStrCur += strlen("NUM_KEY = ");

			// ������̐擪��ݒ�
			strcpy(aStr, pStrCur);

			// �����񔲂��o��
			m_aMotionInfo[nMotionCnt].nNumKey = atoi(pStrCur);
		}

		//============================================================================
		// KEYSET �L�[�̐ݒ�
		//============================================================================
		if (memcmp(pStrCur, "KEYSET", strlen("KEYSET")) == 0)
		{
			// ��������Ԃ��Ă��炤
			PopString(pStrCur, aStr);

			// ���o��
			pStrCur += strlen("KEYSET");

			// �P�s�ǂݍ���
			fgets(&aLine[0], 256, pFile);

			// ������̐擪��ݒ�
			pStrCur = ReadLine(pFile, &aLine[0]);

			// ������̐擪��ݒ�
			strcpy(aStr, pStrCur);
		}

		//============================================================================
		// FRAME �t���[���ݒ�
		//============================================================================
		if (memcmp(pStrCur, "FRAME = ", strlen("FRAME = ")) == 0)
		{
			// ������̐擪��ݒ�
			pStrCur = ReadLine(pFile, &aLine[0]);

			// ���o��
			pStrCur += strlen("FRAME = ");

			// ������̐擪��ݒ�
			strcpy(aStr, pStrCur);

			m_aMotionInfo[nMotionCnt].aKeyInfo[nCntKey].nFrame = atoi(pStrCur);

			// �P�s�ǂݍ���
			fgets(&aLine[0], 256, pFile);

			// ������̐擪��ݒ�
			pStrCur = ReadLine(pFile, &aLine[0]);

			// ������̐擪��ݒ�
			strcpy(aStr, pStrCur);
		}

		//============================================================================
		// KEY �L�[
		//============================================================================
		if (memcmp(pStrCur, "KEY", strlen("KEY")) == 0)
		{
			// ������̐擪��ݒ�
			pStrCur = ReadLine(pFile, &aLine[0]);

			// �P�s�ǂݍ���
			fgets(&aLine[0], 256, pFile);
			// ������̐擪��ݒ�@\t \n " "	�Ƃ΂�
			pStrCur = ReadLine(pFile, &aLine[0]);

			// ������̐擪��ݒ�
			strcpy(aStr, pStrCur);
		}

		//============================================================================
		// POS �ʒu���[�V����
		//============================================================================
		if (memcmp(pStrCur, "POS = ", strlen("POS = ")) == 0)
		{
			// ���o��
			pStrCur += strlen("POS = ");

			// ������̐擪��ݒ�
			strcpy(aStr, pStrCur);

			//===================================
			// POSX
			//===================================

			// ��������Ԃ��Ă��炤
			nWord = PopString(pStrCur, &aStr[0]);

			// POS.X���
			m_aMotionInfo[nMotionCnt].aKeyInfo[nCntKey].aKey[nCntParts].fPosX = (float)atof(pStrCur);

			// ���������i�߂�
			pStrCur += nWord;

			//===================================
			// POSY
			//===================================

			// ��������Ԃ��Ă��炤
			nWord = PopString(pStrCur, &aStr[0]);

			// POS.Y���
			m_aMotionInfo[nMotionCnt].aKeyInfo[nCntKey].aKey[nCntParts].fPosY = (float)atof(pStrCur);

			// ���������i�߂�
			pStrCur += nWord;

			//===================================
			// POSZ
			//===================================

			// ��������Ԃ��Ă��炤
			nWord = PopString(pStrCur, &aStr[0]);

			// POS.Z���
			m_aMotionInfo[nMotionCnt].aKeyInfo[nCntKey].aKey[nCntParts].fPosZ = (float)atof(pStrCur);

			// ������̐擪��ݒ�
			pStrCur = ReadLine(pFile, &aLine[0]);

			// �P�s�ǂݍ���
			fgets(&aLine[0], 256, pFile);

			// ������̐擪��ݒ�
			pStrCur = ReadLine(pFile, &aLine[0]);

			// ������̐擪��ݒ�
			strcpy(aStr, pStrCur);
		}

		//============================================================================
		// ROT �������[�V����
		//============================================================================
		if (memcmp(pStrCur, "ROT = ", strlen("ROT = ")) == 0)
		{
			// ���o��
			pStrCur += strlen("ROT = ");

			// ������̐擪��ݒ�
			strcpy(aStr, pStrCur);

			//===================================
			// ROTX
			//===================================
			// ��������Ԃ��Ă��炤
			nWord = PopString(pStrCur, &aStr[0]);
			// RotX
			m_aMotionInfo[nMotionCnt].aKeyInfo[nCntKey].aKey[nCntParts].fRotX = (float)atof(pStrCur);
			// ���������i�߂�
			pStrCur += nWord;

			//===================================
			// ROTY
			//===================================
			// ��������Ԃ��Ă��炤
			nWord = PopString(pStrCur, &aStr[0]);
			// RotY
			m_aMotionInfo[nMotionCnt].aKeyInfo[nCntKey].aKey[nCntParts].fRotY = (float)atof(pStrCur);
			// ���������i�߂�
			pStrCur += nWord;

			//===================================
			// ROTZ
			//===================================
			// ��������Ԃ��Ă��炤
			nWord = PopString(pStrCur, &aStr[0]);
			// RotZ
			m_aMotionInfo[nMotionCnt].aKeyInfo[nCntKey].aKey[nCntParts].fRotZ = (float)atof(pStrCur);
			// ������̐擪��ݒ�
			pStrCur = ReadLine(pFile, &aLine[0]);
			// �P�s�ǂݍ���
			fgets(&aLine[0], 256, pFile);
			// ������̐擪��ݒ�
			pStrCur = ReadLine(pFile, &aLine[0]);
			// ������̐擪��ݒ�
			strcpy(aStr, pStrCur);
		}

		//============================================================================
		// END_KEY �L�[�̏I��
		//============================================================================
		if (memcmp(pStrCur, "END_KEY", strlen("END_KEY")) == 0)
		{
			// ���o��
			pStrCur += strlen("END_KEY");

			// �P�s�ǂݍ���
			fgets(&aLine[0], 256, pFile);


			// ������̐擪��ݒ�
			pStrCur = ReadLine(pFile, &aLine[0]);

			// ������̐擪��ݒ�
			strcpy(aStr, pStrCur);

			// �p�[�c�̃J�E���g��i�߂�
			nCntParts++;
		}

		//============================================================================
		// END_KEYSET �L�[�̐ݒ�̏I��
		//============================================================================
		if (memcmp(pStrCur, "END_KEYSET", strlen("END_KEYSET")) == 0)
		{
			// ������̐擪��ݒ�
			pStrCur = ReadLine(pFile, &aLine[0]);

			// �J�E���g��i�߂�
			nCntKey++;

			nCntParts = 0;
		}
		else
		{
			// ������̐擪��ݒ�
			pStrCur = ReadLine(pFile, &aLine[0]);
		}

		//============================================================================
		// END_MOTIONSET ���[�V�����̐ݒ�̏I��
		//============================================================================
		if (memcmp(pStrCur, "END_MOTIONSET", strlen("END_MOTIONSET")) == 0)
		{
			// ���[�V�����̏����Z�b�g
			m_pKeyInfo[nMotionCnt] = &m_aMotionInfo[nMotionCnt].aKeyInfo[0];
			nCntKey = 0;
			nMotionCnt++;
		}

		//============================================================================
		// END_SCRIPT �X�N���v�g�̏I���
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
// ���[�V�����̍X�V����
//=============================================================================
void CObjectBG::UpdateMotion(void)
{
	KEY			*pKey, *pKeyNext;			// ���݂̃L�[�A���̃L�[

	float fRateMotion;						//���[�V�����J�E���^�[�̑��Βl
	float fDiffMotion;						//����
	D3DXVECTOR3 rotMotion;


	if (m_aMotionInfo[m_nMotionType].nNumKey <= m_nKey)
	{
		m_nKey = 0;
	}

	for (int nCntModel = 0; nCntModel < m_nNumParts; nCntModel++)
	{
		if (m_apModel[nCntModel] != NULL)
		{
			// ���݂̃L�[
			pKey = &m_pKeyInfo[m_nMotionType][m_nKey].aKey[nCntModel];

			// ���̃L�[
			pKeyNext = &m_pKeyInfo[m_nMotionType][(m_nKey + 1) % m_aMotionInfo[m_nMotionType].nNumKey].aKey[nCntModel];

			// ���Βl
			fRateMotion = (float)m_nCountFlame / (float)m_pKeyInfo[m_nMotionType][m_nKey].nFrame;

			// X����
			fDiffMotion = pKeyNext->fRotX - pKey->fRotX;
			rotMotion.x = pKey->fRotX + (fDiffMotion * fRateMotion);

			// Y����
			fDiffMotion = pKeyNext->fRotY - pKey->fRotY;
			rotMotion.y = pKey->fRotY + (fDiffMotion * fRateMotion);

			// Z����
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
	// �f�o�b�N�\�����擾
	CDebugProc *m_Dubug = CRenderer::GetDebug();
	m_Dubug->Print("sdsd", "\n�t���[����", m_nCountFlame, "/", m_aMotionInfo[1].aKeyInfo[m_nKey].nFrame);
	m_Dubug->Print("sd", "�L�[�̐�", m_nKey);
	m_Dubug->Print("sfsfsf", "\n�p�[�c�̈ʒu x", rotMotion.x, "y", rotMotion.y, "z", rotMotion.z);

#endif // DEBUG
}

//=============================================================================
// 1�s��(256)�̓ǂݍ���
//=============================================================================
char * CObjectBG::ReadLine(FILE *pFile, char * pDest)
{
	// 1�s��(256������)�ǂݍ���)
	while (1)
	{// �L���ȕ����񂪌�����܂ŉ�

		if (memcmp(pDest, "#", strlen("#")) == 0)
		{// �R�����g�s�̏ꍇ�A���̍s�֐i��
			pDest += strlen("\n");
			//break;
		}
		else if (memcmp(pDest, " ", strlen(" ")) == 0)
		{// �X�y�[�X�s�̏ꍇ�A���̍s�֐i��

			pDest++;

			// �܂��X�y�[�X������ꍇ�Ȃ��Ȃ�܂ŉ�
			while (memcmp(pDest, " ", strlen(" ")) == 0)
			{
				if (memcmp(pDest, " ", strlen(" ")) == 0)
				{// �X�y�[�X�̏ꍇ�A���̍s�֐i��
					pDest++;
				}
				else
				{
					// �X�y�[�X���Ȃ��Ȃ�����I��
					break;
				}
			}
			// �X�y�[�X���Ȃ��Ȃ�����I��
			break;
		}
		else if (memcmp(pDest, "\n", strlen("\n")) == 0)
		{// ���s�̏ꍇ�A���̍s�֐i��
			pDest += strlen("\n");
		}
		else if (memcmp(pDest, "\t", strlen("\t")) == 0)
		{// TAB�s�̏ꍇ�A���̍s�֐i��

			pDest += strlen("\t");

			// �܂�TAB�����������
			while (memcmp(pDest, "\t", strlen("\t")) == 0)
			{
				if (memcmp(pDest, "\t", strlen("\t")) == 0)
				{// TAB�s�̏ꍇ�A���̍s�֐i��
					pDest += strlen("\t");
				}
				else
				{
					// TAB���Ȃ��Ȃ�����I��
					break;
				}
			}
			// TAB���Ȃ��Ȃ�����I��
			break;
		}
		// �L���ȕ����񂪂���ΏI������
		else
		{
			break;
		}
	}
	return pDest;
}

//=============================================================================
// ������̐擪���擾
//=============================================================================
char * CObjectBG::GetLineTop(char * pSrc)
{
	while (1)
	{// �L���ȕ����񂪌�����܂ŉ�

		if (memcmp(pSrc, "\t", 2) == 0)
		{// TAB�s�̏ꍇ�A���̍s�֐i��
			pSrc += strlen("\t");			// ���o��
		}
		if (memcmp(pSrc, " ", 1) == 0)
		{// �X�y�[�X�s�̏ꍇ�A���̍s�֐i��
			pSrc += strlen(" ");			// ���o��
		}
		else
		{// �L���ȕ����񂪂���ΏI������
			break;
		}
	}

	return S_OK;
}

//=============================================================================
// ������𔲂��o��
//=============================================================================
int CObjectBG::PopString(char * pSrc, char * pDest)
{
	int Word = 0;

	while (1)
	{// �X�y�[�X�̌�ɕ����񂪂���܂ŉ�
	 // ���o��
		pSrc += 1;
		Word += 1;

		// ���o��
		if (memcmp(pSrc, " ", strlen(" ")) == 0)
		{
			pSrc = "\0";
			Word += 1;
			break;
		}

		// ���o��
		if (memcmp(pSrc, "\t", strlen("\t")) == 0)
		{
			pSrc = "\0";
			Word += strlen("\t");
			break;
		}

		// ������̃f�[�^�A��r���镶����A��r����
		else if (memcmp(pSrc, "\n", strlen("\n")) == 0)
		{
			// ���o��
			Word += strlen("\n");
			break;
		}
	}
	strcpy(pDest, pSrc);
	// �����񕪂̐���i�߂�
	return Word;
}