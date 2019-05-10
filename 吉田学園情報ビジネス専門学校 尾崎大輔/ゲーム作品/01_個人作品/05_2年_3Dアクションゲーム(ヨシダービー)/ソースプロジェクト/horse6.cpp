//=============================================================================
//
// �n6���� [horse6.cpp]
// Author : Ozaki
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS

#include "horse6.h"
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

#define FAILE_NAME	"data\\TEXT\\umamotion6.txt"	// �ǂݍ���text��
#define UMA_SPEED	(1.05f)
//=============================================================================
// �ϐ�
//=============================================================================
CHorse6::KEY CHorse6::m_aKeyOffset[MAX_PARTS] = {};

int	CHorse6::m_nNumParts = {};
int	CHorse6::m_nNumModel = {};
CMeshOrbit*CHorse6::m_mesh;
CHorse6::KEY_INFO*CHorse6::m_pKeyInfo[MAX_PARTS] = {};
CHorse6::MOTION_INFO CHorse6::m_aMotionInfo[MAX_PARTS] = {};

//=============================================================================
// �ÓI�����o-�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CHorse6::m_pTexture = NULL;				// �e�N�X�`��
LPD3DXBUFFER CHorse6::m_pBuffMatModel[MAX_PARTS] = {};		// �o�b�t�@
DWORD CHorse6::m_nNumMatModel[MAX_PARTS] = {};			    // �}�e���A�����̐�
LPD3DXMESH CHorse6::m_pMeshModel[MAX_PARTS] = {};			// ���b�V�����ւ̃|�C���^
D3DXVECTOR3	CHorse6::m_pos = D3DXVECTOR3(0, 0, 0);			// �ʒu
D3DXVECTOR3 CHorse6::m_rot = D3DXVECTOR3(0, 0, 0);			// ����
char CHorse6::m_aFileNameModel[MAX_PARTS][256] = {};
CModel*CHorse6::m_apModel[MAX_PARTS] = {};
int CHorse6::m_aIndexParent[MAX_PARTS] = {};
CHorse6::PLAYERSTATE CHorse6::m_State = CHorse6::PLAYERSTATE_NONE;
CHorse6::JOCKEYTYPE CHorse6::m_nType = CHorse6::JOCKEYTYPE_NONE;

//=============================================================================
// �ǂݍ���
//=============================================================================
HRESULT CHorse6::Load(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	return S_OK;
}

//=============================================================================
// �J��
//=============================================================================
void CHorse6::Unload(void)
{
	for (int nCnt = 0; nCnt < NUM_PLAYER_MODEL; nCnt++)
	{
		// �}�e���A�����ւ̃|�C���^��j��
		if (m_pBuffMatModel[nCnt] != NULL)
		{
			m_pBuffMatModel[nCnt]->Release();
			m_pBuffMatModel[nCnt] = NULL;
		}

		// ���b�V�����ւ̃|�C���^��j��
		if (m_pMeshModel[nCnt] != NULL)
		{
			m_pMeshModel[nCnt]->Release();
			m_pMeshModel[nCnt] = NULL;
		}

		//�e�N�X�`���̔j��
		if (m_pTexture != NULL)
		{
			m_pTexture->Release();
			m_pTexture = NULL;
		}
	}
}

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CHorse6::CHorse6(int nPriority, OBJTYPE objtype) :CScene(1, OBJTYPE_PLAYER)
{
	m_nCntA = 0;
	m_nCntB = 0;
	for (int nCnt = 0; nCnt < MAX_MOTION; nCnt++)
	{
		m_pKeyInfo[nCnt] = NULL;		//�L�[���ւ̃|�C���^
	}
	m_nKey = {};						//���݂̃L�[�i���o�[
	D3DXMatrixIdentity(&m_mtxRot);
	m_State = CHorse6::PLAYERSTATE_NONE;
	m_nMotionType = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CHorse6::~CHorse6()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CHorse6::Init(void)
{
	//	�f�o�C�X�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9	pDevice = pRenderer->GetDevice();

	// �������ϐ�
	m_rot = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fDestAngle = D3DX_PI * 1.0f;
	m_fDiffAngle = 0;
	m_bBrake = false;
	m_testCnt = 0;

	//���[�V�����p�ϐ�
	m_nKey = 0;			//���݂̃L�[
	m_nCountFlame = 0;	//���݂̃t���[��
	m_nMotionType = 0;	//���݂̃��[�V�����^�C�v


	// Text�t�@�C������ǂݍ���
	FileLoad();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CHorse6::Uninit(void)
{
	for (int nCnt = 0; nCnt < m_nNumParts; nCnt++)
	{
		if (m_apModel[nCnt] != NULL)
		{
			// ���f������ɂ���
			m_apModel[nCnt]->Uninit();

			// ���f�����폜
			delete m_apModel[nCnt];

			// NULL�ɂ���
			m_apModel[nCnt] = NULL;
		}
	}
	// ���f���̔j��
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CHorse6::Update(void)
{
#if 1
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = NULL;

	// �t�F�[�h���擾
	CFade *pFade;
	pFade = CManager::GetFade();

	// �����_���[���擾
	pDevice = CManager::GetRenderer()->GetDevice();

	// �f�o�b�N�\�����擾
	CDebugProc *m_Dubug = CRenderer::GetDebug();

	// �L�[�{�[�h���擾
	CInputKeyboard *InputKeyboard;
	InputKeyboard = CManager::GetInputKeyboard();

	// ���b�V���t�B�[���h���擾
	CMeshFiled *pMeshFiled;
	pMeshFiled = CGame::GetMeshFiled();

	// ���b�V���I�[�r�b�g���擾
	CMeshOrbit *pMeshOrbit;
	pMeshOrbit = CManager::GetMeshOrbit();

	// ���[�J���ϐ�
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 rotMotion;

	// �ʒu�A�����A�������擾
	pos = CScene::GetPosition();
	move = CScene::GetMove();
	CManager *pManager = NULL;
	//CGame *pGame = NULL;

	//rot = CGame::GetCamera()->GetRot();

	switch (m_nType)
	{
	case JOCKEYTYPE_TITLE:
		m_pos.z += 2;
		if (m_pos.z >= 800)
		{
			Uninit();
		}
		// ���[�V�����؂�ւ�
		if (m_bBrake == false)
		{
			m_nMotionType = 1;
		}
		break;

	case JOCKEYTYPE_GAME:


		//========================================================
		// ��ړ�
		//========================================================
		if (m_pos.z >= 0)
		{
			m_pos.z += UMA_SPEED;
			m_pos.z += rand() % 10 * 0.1f;

			// ���[�V�����؂�ւ�
			if (m_bBrake == false)
			{
				m_nMotionType = 1;
			}
		}

		else
		{
			// �ړ����Ă��Ȃ� �j���[�g�������
			if (m_bBrake == false)
			{
				// ���[�V�����؂�ւ�
				m_nMotionType = 0;
			}
		}
		break;
		// ���U���g
	case JOCKEYTYPE_RESULT:

		// ���[�V�����؂�ւ�
		if (m_bBrake == false)
		{
			m_nMotionType = 2;
		}
		else
		{
			// �ړ����Ă��Ȃ� �j���[�g�������
			if (m_bBrake == false)
			{
				// ���[�V�����؂�ւ�
				m_nMotionType = 0;
			}
		}
	}
	//���[�V�����X�V
	UpdateMotion();


	switch (m_State)
	{

		// �v���C���[���ʏ펞
	case PLAYERSTATE_NONE:
		// �v���C���[�̈ړ���
		if (m_pos.z >= 3800)
		{
			m_pos.z = 3800;
		}
		break;

	}

	// �ʒu�A�����A�����̐ݒ�
	CScene::SetPosition(m_pos);
	CScene::SetMove(move);
	CScene::SetRot(m_rot);

#endif

#ifdef _DEBUG
	// �͈͐ݒ�̃f�o�b�N
	//m_Dubug->Print("ssfsfsf", "\n[ house �ʒu ] ", "X", m_pos.x, "Y", m_pos.y, "Z", m_pos.z);

#endif
}

//=============================================================================
// �`�揈��
//=============================================================================
void CHorse6::Draw(void)
{
	//�f�o�C�X���擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;		//�v�Z�p�}�g���b�N�X
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

	// ���C�g�̎擾
	CLight *pLight = CManager::GetLight();

	// ���C�g�𖳌��ɂ���
	pDevice->LightEnable(0, FALSE);
	pDevice->LightEnable(1, FALSE);
	pDevice->LightEnable(2, FALSE);
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ���Z����
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);


	// �V���h�E�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxShadow);

	// ���C�g�̐ݒ�
	VecLight = D3DXVECTOR4(0.5f, 1.0f, -1.0f, 0.0f);

	// �e�̈ʒu�ݒ�
	pos = D3DXVECTOR3(0.0f, 0.5f, 0.0f);

	// �@���̐ݒ�
	normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	// ���ʂ��쐬
	D3DXPlaneFromPointNormal(&planeField, &pos, &normal);

	// �e�}�g���b�N�X�̐ݒ�
	D3DXMatrixShadow(&mtxShadow, &VecLight, &planeField);

	// ���[���h�}�g���b�N�X�Ɗ|�����킹��
	D3DXMatrixMultiply(&mtxShadow, &m_mtxWorld, &mtxShadow);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxShadow);

	for (int nCnt = 0; nCnt < m_nNumParts; nCnt++)
	{
		if (m_apModel[nCnt] != NULL)
		{
			m_apModel[nCnt]->Draw();
		}
	}

	// �����_�[�X�e�C�g�����ɖ߂�
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


	for (int nCnt = 0; nCnt < m_nNumParts; nCnt++)
	{
		if (m_apModel[nCnt] != NULL)
		{
			m_apModel[nCnt]->Draw();
		}
	}
}

//=============================================================================
// �v���C���[�̐���
//=============================================================================
CHorse6 *CHorse6::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CHorse6::JOCKEYTYPE type)
{
	CHorse6 *pPlayer = NULL;

	if (pPlayer == NULL)
	{
		pPlayer = new CHorse6(1);

		pPlayer->Init();

		pPlayer->m_pos = pos;
		pPlayer->m_rot = rot;
		pPlayer->m_nType = type;
	}
	return pPlayer;
}

//=============================================================================
// �v���C���[�̃|�W�V�����擾
//=============================================================================
D3DXVECTOR3 CHorse6::GetPlayerpos(D3DXVECTOR3 pos)
{
	m_pos = pos;

	return m_pos;
}

//=============================================================================
// �v���C���[�̈ʒu�擾
//=============================================================================
D3DXVECTOR3 CHorse6::Getpos(void)
{
	return m_pos;
}

//=============================================================================
// �v���C���[�̌����擾
//=============================================================================
D3DXVECTOR3 CHorse6::Getrot(void)
{
	return m_rot;
}

//=============================================================================
// �v���C���[�̓����擾
//=============================================================================
D3DXVECTOR3 CHorse6::Getmove(void)
{
	return m_move;
}

//=============================================================================
// �ǂݍ��ރt�@�C��
//=============================================================================
void CHorse6::FileLoad(void)
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
				m_pos.z + m_aKeyOffset[nIndex].fPosZ), D3DXVECTOR3(
				m_rot.x + m_aKeyOffset[nIndex].fRotX,
				m_rot.y + m_aKeyOffset[nIndex].fRotY,
				m_rot.z + m_aKeyOffset[nIndex].fRotZ));

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

//=============================================================================
// ���[�V�����̍X�V����
//=============================================================================
void CHorse6::UpdateMotion(void)
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
	//m_Dubug->Print("sdsd", "\n�t���[����", m_nCountFlame, "/", m_aMotionInfo[1].aKeyInfo[m_nKey].nFrame);
	//m_Dubug->Print("sd", "�L�[�̐�", m_nKey);
	//m_Dubug->Print("sfsfsf", "\n�p�[�c�̈ʒu x", rotMotion.x, "y", rotMotion.y, "z", rotMotion.z);

#endif // DEBUG
}

//=============================================================================
// �v���C���[��nCntA���擾
//=============================================================================
int CHorse6::GetCntA(void)
{
	return m_nCntA;
}

//=============================================================================
// �v���C���[��nCntB���擾
//=============================================================================
int CHorse6::GetCntB(void)
{
	return m_nCntB;
}

//=============================================================================
// 1�s��(256)�̓ǂݍ���
//=============================================================================
char * CHorse6::ReadLine(FILE *pFile, char * pDest)
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
char * CHorse6::GetLineTop(char * pSrc)
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
int CHorse6::PopString(char * pSrc, char * pDest)
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