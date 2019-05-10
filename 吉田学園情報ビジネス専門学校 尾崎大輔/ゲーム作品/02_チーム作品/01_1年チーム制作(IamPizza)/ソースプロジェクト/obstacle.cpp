//=============================================================================
//
// ��Q���̏������� [obstacle.cpp]
// Author : ���i�Y��
//
//=============================================================================
#include "obstacle.h"
#include "input.h"
#include "camera.h"
#include "game.h"
#include "shadow.h"
#include "particle.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define OBSTACLE_NAME0	"data\\MODEL\\Bill\\pizzaya.x"			//�e�N�X�`���̃t�@�C����
#define OBSTACLE_NAME1	"data\\MODEL\\Bill\\pizzaya��.x"		//�e�N�X�`���̃t�@�C����
#define OBSTACLE_NAME2	"data\\MODEL\\Bill\\house000.x"			//�e�N�X�`���̃t�@�C����
#define OBSTACLE_NAME3	"data\\MODEL\\Bill\\house000��.x"		//�e�N�X�`���̃t�@�C����
#define OBSTACLE_NAME4	"data\\MODEL\\Bill\\house001.x"			//�e�N�X�`���̃t�@�C����	 
#define OBSTACLE_NAME5	"data\\MODEL\\Bill\\house001��.x"		//�e�N�X�`���̃t�@�C����	 
#define OBSTACLE_NAME6	"data\\MODEL\\Bill\\house002.x"			//�e�N�X�`���̃t�@�C����
#define OBSTACLE_NAME7	"data\\MODEL\\Bill\\tatemono001.x"		//�e�N�X�`���̃t�@�C����
#define OBSTACLE_NAME8	"data\\MODEL\\Bill\\tatemono001��.x"	//�e�N�X�`���̃t�@�C����
#define OBSTACLE_NAME9	"data\\MODEL\\Bill\\tatemono002.x"		//�e�N�X�`���̃t�@�C����
#define OBSTACLE_NAME10	"data\\MODEL\\Bill\\tatemono002��.x"	//�e�N�X�`���̃t�@�C����
#define OBSTACLE_NAME11	"data\\MODEL\\Bill\\tatemono003.x"		//�e�N�X�`���̃t�@�C����
#define OBSTACLE_NAME12	"data\\MODEL\\Bill\\tatemono003��.x"	//�e�N�X�`���̃t�@�C����	 
#define OBSTACLE_NAME13	"data\\MODEL\\Bill\\tatemono004.x"		//�e�N�X�`���̃t�@�C����
#define OBSTACLE_NAME14	"data\\MODEL\\Bill\\tatemono004��.x"	//�e�N�X�`���̃t�@�C����
#define OBSTACLE_NAME15	"data\\MODEL\\Bill\\tatemono005.x"		//�e�N�X�`���̃t�@�C����	
#define OBSTACLE_NAME16	"data\\MODEL\\Bill\\tatemono005��.x"	//�e�N�X�`���̃t�@�C����	 
#define OBSTACLE_NAME17	"data\\MODEL\\Bill\\tatemono006.x"		//�e�N�X�`���̃t�@�C����
#define OBSTACLE_NAME18	"data\\MODEL\\Bill\\tatemono006��.x"	//�e�N�X�`���̃t�@�C����
#define OBSTACLE_NAME19	"data\\MODEL\\Bill\\tatemono008.x"		//�e�N�X�`���̃t�@�C����
#define OBSTACLE_NAME20	"data\\MODEL\\Bill\\tatemono008��.x"	//�e�N�X�`���̃t�@�C����
#define OBSTACLE_NAME21	"data\\MODEL\\Bill\\haikyo.x"			//�e�N�X�`���̃t�@�C����
#define OBSTACLE_NAME22	"data\\MODEL\\Bill\\pokkuruzou.x"		//�e�N�X�`���̃t�@�C����
#define OBSTACLE_NAME23	"data\\MODEL\\Bill\\hospital.x"			//�e�N�X�`���̃t�@�C����
#define OBSTACLE_NAME24	"data\\MODEL\\Bill\\hospital��.x"		//�e�N�X�`���̃t�@�C����
#define OBSTACLE_NAME25 "data\\MODEL\\Bill\\shinden.x"			//�e�N�X�`���̃t�@�C����
#define OBSTACLE_NAME26	"data\\MODEL\\Bill\\shinden��.x"		//�e�N�X�`���̃t�@�C����
#define OBSTACLE_NAME27	"data\\MODEL\\Bill\\skytree.x"			//�e�N�X�`���̃t�@�C����
#define OBSTACLE_NAME28	"data\\MODEL\\Bill\\pizzanosyatou.x"	//�e�N�X�`���̃t�@�C����
#define OBSTACLE_NAME29	"data\\MODEL\\Bill\\�I�t�B�X�r��.x"		//�e�N�X�`���̃t�@�C����
#define OBSTACLE_NAME30	"data\\MODEL\\Bill\\�I�t�B�X�r����.x"	//�e�N�X�`���̃t�@�C����
#define OBSTACLE_NAME31	"data\\MODEL\\Bill\\�I�t�B�X�r������.x"	//�e�N�X�`���̃t�@�C����
#define OBSTACLE_NAME32	"data\\MODEL\\Bill\\�I�t�B�X�r����.x"	//�e�N�X�`���̃t�@�C����
#define OBSTACLE_NAME33	"data\\MODEL\\Bill\\�I�t�B�X�r���剡.x"	//�e�N�X�`���̃t�@�C����
#define OBSTACLE_NAME34	"data\\MODEL\\Bill\\kaminarimon.x"		//�e�N�X�`���̃t�@�C����
#define OBSTACLE_NAME35	"data\\MODEL\\Bill\\kaminarimon��.x"	//�e�N�X�`���̃t�@�C����
#define OBSTACLE_NAME36	"data\\MODEL\\Bill\\�H����.x"					//�e�N�X�`���̃t�@�C����
#define OBSTACLE_NAME37	"data\\MODEL\\Bill\\�֎~�G���A�]�[��.x"			//�e�N�X�`���̃t�@�C����
#define OBSTACLE_NAME38	"data\\MODEL\\Bill\\�֎~�G���A�]�[��yoko.x"		//�e�N�X�`���̃t�@�C����
#define OBSTACLE_NAME39	"data\\MODEL\\Bill\\�H����.x"					//�e�N�X�`���̃t�@�C����
#define OBSTACLE_NAME40	"data\\MODEL\\Bill\\�H����yoko.x"				//�e�N�X�`���̃t�@�C����
#define OBSTACLE_NAME41	"data\\MODEL\\Bill\\�o���X�^.x"					//�e�N�X�`���̃t�@�C����
#define OBSTACLE_NAME42	"data\\MODEL\\Bill\\�o���X�^yoko.x"				//�e�N�X�`���̃t�@�C����
#define OBSTACLE_NAME43	"data\\MODEL\\Bill\\���m�n�E�X.x"				//�e�N�X�`���̃t�@�C����
#define OBSTACLE_NAME44	"data\\MODEL\\Bill\\���m�n�E�Xyoko.x"			//�e�N�X�`���̃t�@�C����
#define OBSTACLE_NAME45	"data\\MODEL\\Bill\\���m.x"						//�e�N�X�`���̃t�@�C����
#define OBSTACLE_NAME46	"data\\MODEL\\Bill\\���myoko.x"					//�e�N�X�`���̃t�@�C����
#define OBSTACLE_NAME47	"data\\MODEL\\Bill\\��.x"						//�e�N�X�`���̃t�@�C����
#define OBSTACLE_NAME48	"data\\MODEL\\Bill\\��.x"						//�e�N�X�`���̃t�@�C����
#define OBSTACLE_NAME49	"data\\MODEL\\Bill\\��yoko.x"					//�e�N�X�`���̃t�@�C����
#define OBSTACLE_NAME50 "data\\MODEL\\Bill\\���܂�����.x"				//�e�N�X�`���̃t�@�C����
#define OBSTACLE_NAME51	"data\\MODEL\\Bill\\���܂�����yoko.x"			//�e�N�X�`���̃t�@�C����
#define OBSTACLE_NAME52	"data\\MODEL\\Bill\\�o�X�^�[�\�[�h.x"			//�e�N�X�`���̃t�@�C����
#define OBSTACLE_NAME53	"data\\MODEL\\Bill\\�o�X�^�[�\�[�hyoko.x"		//�e�N�X�`���̃t�@�C����
#define OBSTACLE_NAME54	"data\\MODEL\\Bill\\hana.x"						//�e�N�X�`���̃t�@�C����
#define OBSTACLE_NAME55	"data\\MODEL\\Bill\\hanayoko.x"					//�e�N�X�`���̃t�@�C����
#define OBSTACLE_NAME56	"data\\MODEL\\Bill\\TENGA.x"					//�e�N�X�`���̃t�@�C����
#define OBSTACLE_NAME57	"data\\MODEL\\Bill\\mm.x"						//�e�N�X�`���̃t�@�C����
#define OBSTACLE_NAME58	"data\\MODEL\\Bill\\���.x"						//�e�N�X�`���̃t�@�C����
#define OBSTACLE_NAME59	"data\\MODEL\\Bill\\�y.x"						//�e�N�X�`���̃t�@�C����
#define OBSTACLE_NAME60	"data\\MODEL\\Bill\\pokutank.x"					//�e�N�X�`���̃t�@�C����
#define OBSTACLE_NAME61	"data\\MODEL\\Bill\\poptank.x"					//�e�N�X�`���̃t�@�C����

#define OBSTACLE_SIZE		(5.0f)							// ���f���̑傫��
#define MAX_OBSTACLE		(100)							// �I�u�W�F�N�g�̍ő吔
#define MAX_OBSTACLE_TYPE   (OBSTACLE_TYPE_MAX )			// �I�u�W�F�N�g�̃^�C�v��


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPD3DXMESH		    g_pMeshObstacle[MAX_OBSTACLE_TYPE];	              // ���b�V�����i���_���j�ւ̃|�C���^
LPD3DXBUFFER	    g_pBuffMatObstacle[MAX_OBSTACLE_TYPE];	          // �}�e���A�����ւ̃|�C���^
LPDIRECT3DTEXTURE9* g_pTextureObstacle[MAX_OBSTACLE_TYPE];            // �e�N�X�`�����ւ̃|�C���^
DWORD			    g_nNumMatObstacle[MAX_OBSTACLE_TYPE] = {};		  // �}�e���A�����̐�
OBSTACLE	        g_aObstacle[MAX_OBSTACLE_TYPE][MAX_OBSTACLE];     // ��Q���̏��
int g_nMoveTimer;
//=============================================================================
// ����������
//=============================================================================
void InitObstacle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	g_nMoveTimer = 0;
	char aXFileName[MAX_OBSTACLE_TYPE][64] = { 
		OBSTACLE_NAME0,
		OBSTACLE_NAME1,
		OBSTACLE_NAME2,
		OBSTACLE_NAME3,
		OBSTACLE_NAME4,
		OBSTACLE_NAME5,
		OBSTACLE_NAME6,
		OBSTACLE_NAME7,
		OBSTACLE_NAME8,
		OBSTACLE_NAME9,
		OBSTACLE_NAME10,
		OBSTACLE_NAME11,
		OBSTACLE_NAME12,
		OBSTACLE_NAME13,
		OBSTACLE_NAME14,
		OBSTACLE_NAME15,
		OBSTACLE_NAME16,
		OBSTACLE_NAME17,
		OBSTACLE_NAME18,
		OBSTACLE_NAME19,
		OBSTACLE_NAME20,
		OBSTACLE_NAME21,
		OBSTACLE_NAME22,
		OBSTACLE_NAME23,
		OBSTACLE_NAME24,
		OBSTACLE_NAME25,
		OBSTACLE_NAME26,
		OBSTACLE_NAME27,
		OBSTACLE_NAME28,
		OBSTACLE_NAME29,
		OBSTACLE_NAME30,
		OBSTACLE_NAME31,
		OBSTACLE_NAME32,
		OBSTACLE_NAME33,
		OBSTACLE_NAME34,
		OBSTACLE_NAME35,
		OBSTACLE_NAME36,
		OBSTACLE_NAME37,
		OBSTACLE_NAME38,
		OBSTACLE_NAME39,
		OBSTACLE_NAME40,
		OBSTACLE_NAME41,
		OBSTACLE_NAME42,
		OBSTACLE_NAME43,
		OBSTACLE_NAME44,
		OBSTACLE_NAME45,
		OBSTACLE_NAME46,
		OBSTACLE_NAME47,
		OBSTACLE_NAME48,
		OBSTACLE_NAME49,
		OBSTACLE_NAME50,
		OBSTACLE_NAME51,
		OBSTACLE_NAME52,
		OBSTACLE_NAME53,
		OBSTACLE_NAME54,
		OBSTACLE_NAME55,
		OBSTACLE_NAME56,
		OBSTACLE_NAME57,
		OBSTACLE_NAME58,
		OBSTACLE_NAME59,
		OBSTACLE_NAME60,
		OBSTACLE_NAME61,

	};

	for (int nCntType = 0; nCntType < MAX_OBSTACLE_TYPE; nCntType++)
	{// ��Q���̎�ނ����J��Ԃ�
	 // X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(aXFileName[nCntType],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_pBuffMatObstacle[nCntType],
			NULL,
			&g_nNumMatObstacle[nCntType],
			&g_pMeshObstacle[nCntType]);

		// �}�e���A����񂩂�e�N�X�`���������o��
		D3DXMATERIAL* pMat = (D3DXMATERIAL*)g_pBuffMatObstacle[nCntType]->GetBufferPointer();
		D3DMATERIAL9* pMatBuff = new D3DMATERIAL9[g_nNumMatObstacle[nCntType]];
		g_pTextureObstacle[nCntType] = new LPDIRECT3DTEXTURE9[g_nNumMatObstacle[nCntType]];

		for (DWORD nCntMat = 0; nCntMat < g_nNumMatObstacle[nCntType]; nCntMat++)
		{// ���_���̐������J��Ԃ� 
		 // �}�e���A������ǂݍ���
			pMatBuff[nCntMat] = pMat[nCntMat].MatD3D;

			// ����������������
			pMatBuff[nCntMat].Ambient = pMatBuff[nCntMat].Diffuse;

			// �e�N�X�`������������
			g_pTextureObstacle[nCntType][nCntMat] = NULL;

			// �e�N�X�`���̏���ǂݍ���
			if (pMat[nCntMat].pTextureFilename != NULL &&
				lstrlen(pMat[nCntMat].pTextureFilename) > 0)
			{// �e�N�X�`���̃t�@�C����������
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_pTextureObstacle[nCntType][nCntMat]);
			}
		}

		for (int nCntObstacle = 0; nCntObstacle < MAX_OBSTACLE; nCntObstacle++)
		{// ��Q���̐������J��Ԃ�
		 // ��Q�����̏�����
			g_aObstacle[nCntType][nCntObstacle].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ���W��������
			g_aObstacle[nCntType][nCntObstacle].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ��������������
			g_aObstacle[nCntType][nCntObstacle].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ړ��ʂ���������
			g_aObstacle[nCntType][nCntObstacle].nType = (OBSTACLE_TYPE)nCntType;		// ��ނ���������
			g_aObstacle[nCntType][nCntObstacle].bUse = false;							// �g�p���Ă��Ȃ���Ԃɂ���

			if (nCntObstacle == 0)
			{// 1��ڂ�������
				int nNumVtx;	 // ���_��
				DWORD sizeFVF;	 // ���_�t�H�[�}�b�g�̃T�C�Y
				BYTE *pVtxBuff;  // ���_�o�b�t�@�ւ̃|�C���^

				// �ŏ��l�̐ݒ�
				g_aObstacle[nCntType][nCntObstacle].vtxMinObstacle = D3DXVECTOR3(10000.0f, 10000.0f, 10000.0f);
				g_aObstacle[nCntType][nCntObstacle].vtxMaxObstacle = D3DXVECTOR3(-10000.0f, -10000.0f, -10000.0f);

				// ���_�����擾
				nNumVtx = g_pMeshObstacle[nCntType]->GetNumVertices();

				// ���_�t�H�[�}�b�g�̃T�C�Y���擾
				sizeFVF = D3DXGetFVFVertexSize(g_pMeshObstacle[nCntType]->GetFVF());

				// ���_�o�b�t�@�����b�N
				g_pMeshObstacle[nCntType]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

				for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
				{// ���f���̒��_�������J��Ԃ�
					D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	// ���_���W�̑��

					if (vtx.x < g_aObstacle[nCntType][nCntObstacle].vtxMinObstacle.x)
					{// X���W����菬����
						g_aObstacle[nCntType][nCntObstacle].vtxMinObstacle.x = vtx.x;
					}
					if (vtx.y < g_aObstacle[nCntType][nCntObstacle].vtxMinObstacle.y)
					{// Y���W����菬����
						g_aObstacle[nCntType][nCntObstacle].vtxMinObstacle.y = vtx.y;
					}
					if (vtx.z < g_aObstacle[nCntType][nCntObstacle].vtxMinObstacle.z)
					{// Z���W����菬����
						g_aObstacle[nCntType][nCntObstacle].vtxMinObstacle.z = vtx.z;
					}

					if (vtx.x > g_aObstacle[nCntType][nCntObstacle].vtxMaxObstacle.x)
					{// X���W�����傫��
						g_aObstacle[nCntType][nCntObstacle].vtxMaxObstacle.x = vtx.x;
					}
					if (vtx.y > g_aObstacle[nCntType][nCntObstacle].vtxMaxObstacle.y)
					{// Y���W�����傫��
						g_aObstacle[nCntType][nCntObstacle].vtxMaxObstacle.y = vtx.y;
					}
					if (vtx.z > g_aObstacle[nCntType][nCntObstacle].vtxMaxObstacle.z)
					{// Z���W�����傫��
						g_aObstacle[nCntType][nCntObstacle].vtxMaxObstacle.z = vtx.z;
					}

					pVtxBuff += sizeFVF;	// �T�C�Y���|�C���^��i�߂�
				}

				// ���_�o�b�t�@���A�����b�N
				g_pMeshObstacle[nCntType]->UnlockVertexBuffer();
			}
			else
			{// ����ȍ~
				g_aObstacle[nCntType][nCntObstacle].vtxMaxObstacle = g_aObstacle[nCntType][nCntObstacle - 1].vtxMaxObstacle;
				g_aObstacle[nCntType][nCntObstacle].vtxMinObstacle = g_aObstacle[nCntType][nCntObstacle - 1].vtxMinObstacle;
			}
		}
	}
}

//=============================================================================
// �I������
//=============================================================================
void UninitObstacle(void)
{
	for (int nCntType = 0; nCntType < MAX_OBSTACLE_TYPE; nCntType++)
	{
		// ���b�V���̊J��
		if (g_pMeshObstacle[nCntType] != NULL)
		{
			g_pMeshObstacle[nCntType]->Release();
			g_pMeshObstacle[nCntType] = NULL;
		}
		// �}�e���A���̊J��
		if (g_pBuffMatObstacle[nCntType] != NULL)
		{
			g_pBuffMatObstacle[nCntType]->Release();
			g_pBuffMatObstacle[nCntType] = NULL;
		}
		// �e�N�X�`���̊J��
		for (DWORD nCntMat = 0; nCntMat < g_nNumMatObstacle[nCntType]; nCntMat++)
		{
			if (g_pTextureObstacle[nCntType][nCntMat] != NULL)
			{
				g_pTextureObstacle[nCntType][nCntMat]->Release();
				g_pTextureObstacle[nCntType][nCntMat] = NULL;
			}
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateObstacle(void)
{
	PLAYER *pPlayer;
	pPlayer = GetPlayer();
	Camera *pCamera;
	pCamera = GetCamera();
	
	int nCntCollision = 0;
	int nTrueObj = 0;
	//���݂̃��[�h���擾
	MODE Mode = GetMode();

	switch (Mode)
	{
	case MODE_GAME:
		for (int nCntType = 0; nCntType < MAX_OBSTACLE_TYPE; nCntType++)
		{// ��Q���̎�ނ̐������J��Ԃ�
			for (int nCntObstacle = 0; nCntObstacle < MAX_OBSTACLE; nCntObstacle++)
			{// ��Q���̐������J��Ԃ�
				if (g_aObstacle[nCntType][nCntObstacle].bUse == true)
				{// ��Q�����g�p����Ă���
					nTrueObj++;
					//�J�����Ƃ̋��������߂�
					double length = pow((g_aObstacle[nCntType][nCntObstacle].pos.x - pCamera->posV.x)
						*(g_aObstacle[nCntType][nCntObstacle].pos.x - pCamera->posV.x)
						+ (g_aObstacle[nCntType][nCntObstacle].pos.z - pCamera->posV.z)
						*(g_aObstacle[nCntType][nCntObstacle].pos.z - pCamera->posV.z), 0.5);

					//float�^�ɕϊ�
					g_aObstacle[nCntType][nCntObstacle].fLength = (float)length;

					//�v���C���[�Ƃ̋��������߂�
					double lengthPlayer = pow((g_aObstacle[nCntType][nCntObstacle].pos.x - pPlayer->pos.x)
						*(g_aObstacle[nCntType][nCntObstacle].pos.x - pPlayer->pos.x)
						+ (g_aObstacle[nCntType][nCntObstacle].pos.z - pPlayer->pos.z)
						*(g_aObstacle[nCntType][nCntObstacle].pos.z - pPlayer->pos.z), 0.5);
					//float�^�ɕϊ�
					g_aObstacle[nCntType][nCntObstacle].fLengthPlayer = (float)lengthPlayer;

					//�v���C���[�Ƃ̋��������߂�
					double lengthMaxX = pow(((g_aObstacle[nCntType][nCntObstacle].vtxMaxObstacle.x  )- pPlayer->vtxMinBike.x)
						*((g_aObstacle[nCntType][nCntObstacle].vtxMaxObstacle.x) - pPlayer->vtxMinBike.x)
						+(g_aObstacle[nCntType][nCntObstacle].vtxMaxObstacle.z - pPlayer->vtxMinBike.z)
						*(g_aObstacle[nCntType][nCntObstacle].vtxMaxObstacle.z - pPlayer->vtxMinBike.z), 0.5);
					//float�^�ɕϊ�
					g_aObstacle[nCntType][nCntObstacle].LengthMax.x = (float)lengthMaxX;

					//�v���C���[�Ƃ̋��������߂�
					double lengthMinX = pow(((g_aObstacle[nCntType][nCntObstacle].vtxMinObstacle.x) - pPlayer->vtxMaxBike.x)
						*((g_aObstacle[nCntType][nCntObstacle].vtxMinObstacle.x) - pPlayer->vtxMaxBike.x)
						+ (g_aObstacle[nCntType][nCntObstacle].vtxMinObstacle.z - pPlayer->vtxMaxBike.z)
						*(g_aObstacle[nCntType][nCntObstacle].vtxMinObstacle.z - pPlayer->vtxMaxBike.z), 0.5);
					//float�^�ɕϊ�
					g_aObstacle[nCntType][nCntObstacle].LengthMin.x = (float)lengthMinX;

					//if (g_aObstacle[nCntType][nCntObstacle].LengthMax.x > 200)
					//{
					//	nCntCollision++;
					//	if (nCntCollision > 100)
					//	{
					//		pPlayer->ChangeState = CHANGESTATE_POSSIBLE;
					//	}
					//}

					g_aObstacle[nCntType][nCntObstacle].vtxMaxBike.x = (pPlayer->pos.x + pPlayer->vtxMaxBike.x) - (g_aObstacle[nCntType][nCntObstacle].pos.x + g_aObstacle[nCntType][nCntObstacle].vtxMinObstacle.x);
					g_aObstacle[nCntType][nCntObstacle].vtxMinBike.x = (pPlayer->pos.x + pPlayer->vtxMinBike.x) - (g_aObstacle[nCntType][nCntObstacle].pos.x + g_aObstacle[nCntType][nCntObstacle].vtxMaxObstacle.x);
					g_aObstacle[nCntType][nCntObstacle].vtxMaxBike.z = (pPlayer->pos.z + pPlayer->vtxMaxBike.z) - (g_aObstacle[nCntType][nCntObstacle].pos.z + g_aObstacle[nCntType][nCntObstacle].vtxMinObstacle.z);
					g_aObstacle[nCntType][nCntObstacle].vtxMinBike.z = (pPlayer->pos.z + pPlayer->vtxMinBike.z) - (g_aObstacle[nCntType][nCntObstacle].pos.z + g_aObstacle[nCntType][nCntObstacle].vtxMaxObstacle.z);

					////�v���C���[�ƍő咸�_�̋��������߂�
					//double dLengthMin = pow((g_aObstacle[nCntType][nCntObstacle].vtxMinObstacle.x - pPlayer->pos.x)*(g_aObstacle[nCntType][nCntObstacle].vtxMinObstacle.x - pPlayer->pos.x)
					//	+ (g_aObstacle[nCntType][nCntObstacle].vtxMinObstacle.z - pPlayer->pos.z)*(g_aObstacle[nCntType][nCntObstacle].vtxMinObstacle.z - pPlayer->pos.z), 0.5);
					////float�^�ɕϊ�
					//float fLengthMin = (float)dLengthMin;

					//if (fLengthMax < 300 && fLengthMin < 300)
					//{
					//	pPlayer->ChangeState = CHANGESTATE_IMPOSSIBLE;
					//}


					if (pPlayer->pos.z - pPlayer->vtxMaxBike.z <= g_aObstacle[nCntType][nCntObstacle].pos.z + g_aObstacle[nCntType][nCntObstacle].vtxMaxObstacle.z && pPlayer->pos.z + pPlayer->vtxMaxBike.z >= g_aObstacle[nCntType][nCntObstacle].pos.z + g_aObstacle[nCntType][nCntObstacle].vtxMinObstacle.z)
					{// ��Q����Z���W�̒��ɂ���
						if (pPlayer->posOld.x + pPlayer->vtxMaxBike.x <= g_aObstacle[nCntType][nCntObstacle].pos.x + g_aObstacle[nCntType][nCntObstacle].vtxMinObstacle.x
							&& pPlayer->pos.x + pPlayer->vtxMaxBike.x > g_aObstacle[nCntType][nCntObstacle].pos.x + g_aObstacle[nCntType][nCntObstacle].vtxMinObstacle.x)
						{// X���W�̒��ɍ����������
							pPlayer->ChangeState = CHANGESTATE_IMPOSSIBLE;
						}
						else if (pPlayer->posOld.x - pPlayer->vtxMaxBike.x >= g_aObstacle[nCntType][nCntObstacle].pos.x + g_aObstacle[nCntType][nCntObstacle].vtxMaxObstacle.x
							&& pPlayer->pos.x - pPlayer->vtxMaxBike.x < g_aObstacle[nCntType][nCntObstacle].pos.x + g_aObstacle[nCntType][nCntObstacle].vtxMaxObstacle.x)
						{// X���W�̒��ɉE���������
							pPlayer->ChangeState = CHANGESTATE_IMPOSSIBLE;
						}
					}
					if (pPlayer->pos.x - pPlayer->vtxMaxBike.x <= g_aObstacle[nCntType][nCntObstacle].pos.x + g_aObstacle[nCntType][nCntObstacle].vtxMaxObstacle.x && pPlayer->pos.x + pPlayer->vtxMaxBike.x >= g_aObstacle[nCntType][nCntObstacle].pos.x + g_aObstacle[nCntType][nCntObstacle].vtxMinObstacle.x)
					{// ��Q����X���W�̒��ɂ���
						if (pPlayer->posOld.z + pPlayer->vtxMaxBike.z <= g_aObstacle[nCntType][nCntObstacle].pos.z + g_aObstacle[nCntType][nCntObstacle].vtxMinObstacle.z
							&& pPlayer->pos.z + pPlayer->vtxMaxBike.z > g_aObstacle[nCntType][nCntObstacle].pos.z + g_aObstacle[nCntType][nCntObstacle].vtxMinObstacle.z)
						{// Z���W�̒��ɑO���������
							pPlayer->ChangeState = CHANGESTATE_IMPOSSIBLE;
						}
						else if (pPlayer->posOld.z - pPlayer->vtxMaxBike.z >= g_aObstacle[nCntType][nCntObstacle].pos.z + g_aObstacle[nCntType][nCntObstacle].vtxMaxObstacle.z
							&& pPlayer->pos.z - pPlayer->vtxMaxBike.z < g_aObstacle[nCntType][nCntObstacle].pos.z + g_aObstacle[nCntType][nCntObstacle].vtxMaxObstacle.z)
						{// Z���W�̒��Ɍ�납�������
							pPlayer->ChangeState = CHANGESTATE_IMPOSSIBLE;
						}
					}
				}
			}
		}
		for (int nCntType = 0; nCntType < MAX_OBSTACLE_TYPE; nCntType++)
		{// ��Q���̎�ނ̐������J��Ԃ�
			for (int nCntObstacle = 0; nCntObstacle < MAX_OBSTACLE; nCntObstacle++)
			{// ��Q���̐������J��Ԃ�
				if (g_aObstacle[nCntType][nCntObstacle].bUse == true)
				{// ��Q�����g�p����Ă���

					if (g_aObstacle[nCntType][nCntObstacle].fLengthPlayer > 300 /*|| g_aObstacle[nCntType][nCntObstacle].LengthMin.x < 80*/)
					{
						nCntCollision++;
						if (nCntCollision == nTrueObj)
						{							
							pPlayer->ChangeState = CHANGESTATE_POSSIBLE;
						}
					}
				}
			}
		}

		break;
	case MODE_TITLE:
		for (int nCntType = 0; nCntType < MAX_OBSTACLE_TYPE; nCntType++)
		{// ��Q���̎�ނ̐������J��Ԃ�
			for (int nCntObstacle = 0; nCntObstacle < MAX_OBSTACLE; nCntObstacle++)
			{// ��Q���̐������J��Ԃ�
				if (g_aObstacle[nCntType][nCntObstacle].bUse == true)
				{// ��Q�����g�p����Ă���
				 //�J�����Ƃ̋��������߂�
					double length = pow((g_aObstacle[nCntType][nCntObstacle].pos.x - pCamera->posV.x)*(g_aObstacle[nCntType][nCntObstacle].pos.x - pCamera->posV.x)
						+ (g_aObstacle[nCntType][nCntObstacle].pos.z - pCamera->posV.z)*(g_aObstacle[nCntType][nCntObstacle].pos.z - pCamera->posV.z), 0.5);
					//float�^�ɕϊ�
					g_aObstacle[nCntType][nCntObstacle].fLength = (float)length;
				}
			}
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawObstacle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X

	D3DMATERIAL9 matDef;						//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;							//�}�e���A���f�[�^�ւ̃|�C���^
	//���݂̃��[�h���擾
	MODE Mode = GetMode();


	for (int nCntType = 0; nCntType< MAX_OBSTACLE_TYPE; nCntType++)
	{// ��Q���̎�ނ̐������J��Ԃ�
		for (int nCntObstacle = 0; nCntObstacle < MAX_OBSTACLE; nCntObstacle++)
		{// ��Q���̐������J��Ԃ�
			if (g_aObstacle[nCntType][nCntObstacle].bUse == true)
			{// ��Q�����g�p����Ă���
				switch (Mode)
				{
				case MODE_GAME:
					if (g_aObstacle[nCntType][nCntObstacle].fLength < 2100)
					{//���f���ƃv���C���[�̋����ŕ`�悷�邩���߂�

						// ���[���h�}�g���b�N�X�̏�����
						D3DXMatrixIdentity(&g_aObstacle[nCntType][nCntObstacle].mtxWorld);

						// ��]�𔽉f
						D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aObstacle[nCntType][nCntObstacle].rot.y, g_aObstacle[nCntType][nCntObstacle].rot.x, g_aObstacle[nCntType][nCntObstacle].rot.z);
						D3DXMatrixMultiply(&g_aObstacle[nCntType][nCntObstacle].mtxWorld, &g_aObstacle[nCntType][nCntObstacle].mtxWorld, &mtxRot);

						// �ʒu�𔽉f
						D3DXMatrixTranslation(&mtxTrans, g_aObstacle[nCntType][nCntObstacle].pos.x, g_aObstacle[nCntType][nCntObstacle].pos.y, g_aObstacle[nCntType][nCntObstacle].pos.z);
						D3DXMatrixMultiply(&g_aObstacle[nCntType][nCntObstacle].mtxWorld, &g_aObstacle[nCntType][nCntObstacle].mtxWorld, &mtxTrans);

						// ���[���h�}�g���b�N�X�̐ݒ�
						pDevice->SetTransform(D3DTS_WORLD, &g_aObstacle[nCntType][nCntObstacle].mtxWorld);

						// ���݂̃}�e���A�����擾
						pDevice->GetMaterial(&matDef);

						// �}�e���A���f�[�^�ւ̃|�C���^���擾
						pMat = (D3DXMATERIAL*)g_pBuffMatObstacle[nCntType]->GetBufferPointer();
						for (int nCntMat = 0; nCntMat < (int)g_nNumMatObstacle[nCntType]; nCntMat++)
						{
							// �}�e���A���̐ݒ�
							pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

							// �e�N�X�`���̐ݒ�
							pDevice->SetTexture(0, g_pTextureObstacle[nCntType][nCntMat]);

							// ���f��(�p�[�c)�̕`��
							g_pMeshObstacle[nCntType]->DrawSubset(nCntMat);
						}
						// �}�e���A�����f�t�H���g�ɖ߂�
						pDevice->SetMaterial(&matDef);
					}
					break;
				case MODE_TITLE:
					if (g_aObstacle[nCntType][nCntObstacle].fLength < 2300)
					{//���f���ƃv���C���[�̋����ŕ`�悷�邩���߂�
					// ���[���h�}�g���b�N�X�̏�����
						D3DXMatrixIdentity(&g_aObstacle[nCntType][nCntObstacle].mtxWorld);

						// ��]�𔽉f
						D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aObstacle[nCntType][nCntObstacle].rot.y, g_aObstacle[nCntType][nCntObstacle].rot.x, g_aObstacle[nCntType][nCntObstacle].rot.z);
						D3DXMatrixMultiply(&g_aObstacle[nCntType][nCntObstacle].mtxWorld, &g_aObstacle[nCntType][nCntObstacle].mtxWorld, &mtxRot);

						// �ʒu�𔽉f
						D3DXMatrixTranslation(&mtxTrans, g_aObstacle[nCntType][nCntObstacle].pos.x, g_aObstacle[nCntType][nCntObstacle].pos.y, g_aObstacle[nCntType][nCntObstacle].pos.z);
						D3DXMatrixMultiply(&g_aObstacle[nCntType][nCntObstacle].mtxWorld, &g_aObstacle[nCntType][nCntObstacle].mtxWorld, &mtxTrans);

						// ���[���h�}�g���b�N�X�̐ݒ�
						pDevice->SetTransform(D3DTS_WORLD, &g_aObstacle[nCntType][nCntObstacle].mtxWorld);

						// ���݂̃}�e���A�����擾
						pDevice->GetMaterial(&matDef);

						// �}�e���A���f�[�^�ւ̃|�C���^���擾
						pMat = (D3DXMATERIAL*)g_pBuffMatObstacle[nCntType]->GetBufferPointer();
						for (int nCntMat = 0; nCntMat < (int)g_nNumMatObstacle[nCntType]; nCntMat++)
						{
							// �}�e���A���̐ݒ�
							pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

							// �e�N�X�`���̐ݒ�
							pDevice->SetTexture(0, g_pTextureObstacle[nCntType][nCntMat]);

							// ���f��(�p�[�c)�̕`��
							g_pMeshObstacle[nCntType]->DrawSubset(nCntMat);
						}
						// �}�e���A�����f�t�H���g�ɖ߂�
						pDevice->SetMaterial(&matDef);
					}
				}
			}
		}
	}
}
//=============================================================================
// ��Q���̐ݒ菈��
//=============================================================================
void SetObstacle(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType)
{
	for (int nCntObstacle = 0; nCntObstacle < MAX_OBSTACLE; nCntObstacle++)
	{// ��Q���̐������J��Ԃ�
		if (g_aObstacle[nType][nCntObstacle].bUse == false)
		{// ��Q�����g�p����Ă��Ȃ�
		 // �ʒu�E�����̏����ݒ�
			g_aObstacle[nType][nCntObstacle].pos = pos;
			g_aObstacle[nType][nCntObstacle].rot = rot;
			//�@�e�̃Z�b�g
			//g_aModel[nCntModel].nIdxShadow = SetShadow(g_aModel[nCntModel].pos, D3DXVECTOR3(0, 0, 0), 20.0f);
			//g_aObstacle[nType][nCntObstacle].nIdxShadow = SetShadow(g_aObstacle[nType][nCntObstacle].pos, D3DXVECTOR3(0, 0, 0), 20.0f);
			g_aObstacle[nType][nCntObstacle].bUse = true;
			//g_nNumObstacle++;
			break;
		}
	}

}

//=============================================================================
// ��Q���̎擾
//=============================================================================
OBSTACLE *GetObstacle(void)
{
	return &g_aObstacle[0][0];
}

//=============================================================================
// ��Q���̓����蔻��
//=============================================================================
bool CollisionObstacle(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 radius)
{
	PLAYER *pPlayer;
	pPlayer = GetPlayer();

	bool bLand = false;  // ��������ǂ���

	for (int nCntType = 0; nCntType < MAX_OBSTACLE_TYPE; nCntType++)
	{// ��Q���̎�ނ����J��Ԃ�
		for (int nCntObstacle = 0; nCntObstacle < MAX_OBSTACLE; nCntObstacle++)
		{// ��Q���̐������J��Ԃ�
			if (g_aObstacle[nCntType][nCntObstacle].bUse == true)
			{// ��Q�����g�p����Ă���
				if (pPos->y <= g_aObstacle[nCntType][nCntObstacle].pos.y + g_aObstacle[nCntType][nCntObstacle].vtxMaxObstacle.y && pPos->y + radius.y > g_aObstacle[nCntType][nCntObstacle].pos.y + g_aObstacle[nCntType][nCntObstacle].vtxMinObstacle.y
					|| pPos->y + radius.y > g_aObstacle[nCntType][nCntObstacle].pos.y + g_aObstacle[nCntType][nCntObstacle].vtxMaxObstacle.y && pPos->y < g_aObstacle[nCntType][nCntObstacle].pos.y + g_aObstacle[nCntType][nCntObstacle].vtxMinObstacle.y
					|| pPos->y + radius.y > g_aObstacle[nCntType][nCntObstacle].pos.y + g_aObstacle[nCntType][nCntObstacle].vtxMaxObstacle.y && pPos->y < g_aObstacle[nCntType][nCntObstacle].pos.y + g_aObstacle[nCntType][nCntObstacle].vtxMinObstacle.y)
				{// ��Q����Y���W�̒��ɂ���
					if (pPos->z - radius.z <= g_aObstacle[nCntType][nCntObstacle].pos.z + g_aObstacle[nCntType][nCntObstacle].vtxMaxObstacle.z && pPos->z + radius.z >= g_aObstacle[nCntType][nCntObstacle].pos.z + g_aObstacle[nCntType][nCntObstacle].vtxMinObstacle.z)
					{// ��Q����Z���W�̒��ɂ���
						if (pPosOld->x + radius.x <= g_aObstacle[nCntType][nCntObstacle].pos.x + g_aObstacle[nCntType][nCntObstacle].vtxMinObstacle.x
							&& pPos->x + radius.x > g_aObstacle[nCntType][nCntObstacle].pos.x + g_aObstacle[nCntType][nCntObstacle].vtxMinObstacle.x)
						{// X���W�̒��ɍ����������
							pPos->x = g_aObstacle[nCntType][nCntObstacle].pos.x + g_aObstacle[nCntType][nCntObstacle].vtxMinObstacle.x - radius.x;
							pMove->x = 0.0f;
							bLand = true;
						}
						else if (pPosOld->x - radius.x >= g_aObstacle[nCntType][nCntObstacle].pos.x + g_aObstacle[nCntType][nCntObstacle].vtxMaxObstacle.x
							&& pPos->x - radius.x < g_aObstacle[nCntType][nCntObstacle].pos.x + g_aObstacle[nCntType][nCntObstacle].vtxMaxObstacle.x)
						{// X���W�̒��ɉE���������
							pPos->x = g_aObstacle[nCntType][nCntObstacle].pos.x + g_aObstacle[nCntType][nCntObstacle].vtxMaxObstacle.x + radius.x + 0.1f;
							pMove->x = 0.0f;
							bLand = true;
						}
					}
					if (pPos->x - radius.x <= g_aObstacle[nCntType][nCntObstacle].pos.x + g_aObstacle[nCntType][nCntObstacle].vtxMaxObstacle.x && pPos->x + radius.x >= g_aObstacle[nCntType][nCntObstacle].pos.x + g_aObstacle[nCntType][nCntObstacle].vtxMinObstacle.x)
					{// ��Q����X���W�̒��ɂ���
						if (pPosOld->z + radius.z <= g_aObstacle[nCntType][nCntObstacle].pos.z + g_aObstacle[nCntType][nCntObstacle].vtxMinObstacle.z
							&& pPos->z + radius.z > g_aObstacle[nCntType][nCntObstacle].pos.z + g_aObstacle[nCntType][nCntObstacle].vtxMinObstacle.z)
						{// Z���W�̒��ɑO���������
							pPos->z = g_aObstacle[nCntType][nCntObstacle].pos.z + g_aObstacle[nCntType][nCntObstacle].vtxMinObstacle.z - radius.z;
							pMove->z = 0.0f;
							bLand = true;
						}
						else if (pPosOld->z - radius.z >= g_aObstacle[nCntType][nCntObstacle].pos.z + g_aObstacle[nCntType][nCntObstacle].vtxMaxObstacle.z
							&& pPos->z - radius.z < g_aObstacle[nCntType][nCntObstacle].pos.z + g_aObstacle[nCntType][nCntObstacle].vtxMaxObstacle.z)
						{// Z���W�̒��Ɍ�납�������
							pPos->z = g_aObstacle[nCntType][nCntObstacle].pos.z + g_aObstacle[nCntType][nCntObstacle].vtxMaxObstacle.z + radius.z + 0.1f;
							pMove->z = 0.0f;
							bLand = true;
						}
					}
				}
			}
		}
	}

	return bLand;   // ��������ǂ�����Ԃ�
}

//=============================================================================
// ��Q���̃o�C�N�p�̓����蔻��
//=============================================================================
bool CollisionObstacleBike(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 radius)
{
	PLAYER *pPlayer;
	pPlayer = GetPlayer();

	bool bLand = false;  // ��������ǂ���

	for (int nCntType = 0; nCntType < MAX_OBSTACLE_TYPE; nCntType++)
	{// ��Q���̎�ނ����J��Ԃ�
		for (int nCntObstacle = 0; nCntObstacle < MAX_OBSTACLE; nCntObstacle++)
		{// ��Q���̐������J��Ԃ�
			if (g_aObstacle[nCntType][nCntObstacle].bUse == true)
			{// ��Q�����g�p����Ă���
				if (pPos->y <= g_aObstacle[nCntType][nCntObstacle].pos.y + g_aObstacle[nCntType][nCntObstacle].vtxMaxObstacle.y && pPos->y + radius.y > g_aObstacle[nCntType][nCntObstacle].pos.y + g_aObstacle[nCntType][nCntObstacle].vtxMinObstacle.y
					|| pPos->y + radius.y > g_aObstacle[nCntType][nCntObstacle].pos.y + g_aObstacle[nCntType][nCntObstacle].vtxMaxObstacle.y && pPos->y < g_aObstacle[nCntType][nCntObstacle].pos.y + g_aObstacle[nCntType][nCntObstacle].vtxMinObstacle.y
					|| pPos->y + radius.y > g_aObstacle[nCntType][nCntObstacle].pos.y + g_aObstacle[nCntType][nCntObstacle].vtxMaxObstacle.y && pPos->y < g_aObstacle[nCntType][nCntObstacle].pos.y + g_aObstacle[nCntType][nCntObstacle].vtxMinObstacle.y)
				{// ��Q����Y���W�̒��ɂ���
					if (pPos->z - radius.z <= g_aObstacle[nCntType][nCntObstacle].pos.z + g_aObstacle[nCntType][nCntObstacle].vtxMaxObstacle.z && pPos->z + radius.z >= g_aObstacle[nCntType][nCntObstacle].pos.z + g_aObstacle[nCntType][nCntObstacle].vtxMinObstacle.z)
					{// ��Q����Z���W�̒��ɂ���
						if (pPosOld->x + radius.x <= g_aObstacle[nCntType][nCntObstacle].pos.x + g_aObstacle[nCntType][nCntObstacle].vtxMinObstacle.x
							&& pPos->x + radius.x > g_aObstacle[nCntType][nCntObstacle].pos.x + g_aObstacle[nCntType][nCntObstacle].vtxMinObstacle.x)
						{// X���W�̒��ɍ����������
							bLand = true;
						}
						else if (pPosOld->x - radius.x >= g_aObstacle[nCntType][nCntObstacle].pos.x + g_aObstacle[nCntType][nCntObstacle].vtxMaxObstacle.x
							&& pPos->x - radius.x < g_aObstacle[nCntType][nCntObstacle].pos.x + g_aObstacle[nCntType][nCntObstacle].vtxMaxObstacle.x)
						{// X���W�̒��ɉE���������
							bLand = true;
						}
					}
					if (pPos->x - radius.x <= g_aObstacle[nCntType][nCntObstacle].pos.x + g_aObstacle[nCntType][nCntObstacle].vtxMaxObstacle.x && pPos->x + radius.x >= g_aObstacle[nCntType][nCntObstacle].pos.x + g_aObstacle[nCntType][nCntObstacle].vtxMinObstacle.x)
					{// ��Q����X���W�̒��ɂ���
						if (pPosOld->z + radius.z <= g_aObstacle[nCntType][nCntObstacle].pos.z + g_aObstacle[nCntType][nCntObstacle].vtxMinObstacle.z
							&& pPos->z + radius.z > g_aObstacle[nCntType][nCntObstacle].pos.z + g_aObstacle[nCntType][nCntObstacle].vtxMinObstacle.z)
						{// Z���W�̒��ɑO���������	
							bLand = true;
						}
						else if (pPosOld->z - radius.z >= g_aObstacle[nCntType][nCntObstacle].pos.z + g_aObstacle[nCntType][nCntObstacle].vtxMaxObstacle.z
							&& pPos->z - radius.z < g_aObstacle[nCntType][nCntObstacle].pos.z + g_aObstacle[nCntType][nCntObstacle].vtxMaxObstacle.z)
						{// Z���W�̒��Ɍ�납�������					
							bLand = true;
						}
					}
				}
			}
		}
	}
	return bLand;   // ��������ǂ�����Ԃ�
}