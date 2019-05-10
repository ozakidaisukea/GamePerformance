//=============================================================================
//
// ���f������ [model.cpp]
// Author : Meguro Mikiya
//
//=============================================================================
#include "model.h"
#include "input.h"
#include "shadow.h"
#include "camera.h"
#include "bullet.h"
#include "polygon.h"
#include "player.h"
#include "game.h"
#include "explosion.h"
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPD3DXMESH g_pMeshModel[MAX_MODEL_TYPE];						//���b�V�����ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatModel[MAX_MODEL_TYPE];				//�}�e���A�����ւ̃|�C���^
LPDIRECT3DTEXTURE9	g_pTextureModel[MAX_MODEL_TYPE];			//�e�N�X�`���ւ̃|�C���^
DWORD g_nNumMatModel[MAX_MODEL_TYPE] = {};					//�}�e���A�����̐�
MODEL g_aModel[MAX_MODEL];
D3DXMATERIAL *g_pMat;
VTX g_aModelVtx[MAX_MODEL_TYPE];
//=============================================================================
// ����������
//=============================================================================
void InitModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(MODEL_NAME000,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatModel[0],
		NULL,
		&g_nNumMatModel[0],
		&g_pMeshModel[0]);

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(MODEL_NAME001,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatModel[1],
		NULL,
		&g_nNumMatModel[1],
		&g_pMeshModel[1]);

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(MODEL_NAME002,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatModel[2],
		NULL,
		&g_nNumMatModel[2],
		&g_pMeshModel[2]);

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(MODEL_NAME003,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatModel[3],
		NULL,
		&g_nNumMatModel[3],
		&g_pMeshModel[3]);

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(MODEL_NAME004,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatModel[4],
		NULL,
		&g_nNumMatModel[4],
		&g_pMeshModel[4]);


	int nNumVtex;	//���_��
	DWORD sizeFvF;	//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff[MAX_MODEL];	//���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 vtx[MAX_MODEL];

	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		g_aModel[nCntModel].VtxMinModel = D3DXVECTOR3(10000, 0, 10000);
		g_aModel[nCntModel].VtxMaxModel = D3DXVECTOR3(-10000, 0, -10000);
		g_aModel[nCntModel].nType = 0;
		g_aModel[nCntModel].bUse = false;
	}
	for (int nCntTypeModel = 0; nCntTypeModel < MAX_MODEL_TYPE; nCntTypeModel++)
	{
		g_aModelVtx[nCntTypeModel].VtxMaxModel = D3DXVECTOR3(-10000, 0, -10000);
		g_aModelVtx[nCntTypeModel].VtxMinModel = D3DXVECTOR3(10000, 0, 10000);
	}

#if 0
	for (int nCntTypeModel = 0; nCntTypeModel < MAX_MODEL_TYPE; nCntTypeModel++)
	{
		//���_�����擾
		nNumVtex = g_pMeshModel[nCntTypeModel]->GetNumVertices();
		//���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFvF = D3DXGetFVFVertexSize(g_pMeshModel[nCntTypeModel]->GetFVF());
		for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
		{
			//���_�@���b�N
			g_pMeshModel[nCntTypeModel]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff[nCntModel]);
			for (int nCntVtx = 0; nCntVtx < nNumVtex; nCntVtx++)
			{	//���_���W�̑��
				D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff[nCntModel];
				if (g_aModel[nCntModel].VtxMinModel.x > vtx.x)
				{
					g_aModel[nCntModel].VtxMinModel.x = vtx.x;
				}
				if (g_aModel[nCntModel].VtxMinModel.y > vtx.y)
				{
					g_aModel[nCntModel].VtxMinModel.y = vtx.y;
				}
				if (g_aModel[nCntModel].VtxMinModel.z > vtx.z)
				{
					g_aModel[nCntModel].VtxMinModel.z = vtx.z;
				}

				if (g_aModel[nCntModel].VtxMaxModel.x < vtx.x)
				{
					g_aModel[nCntModel].VtxMaxModel.x = vtx.x;
				}
				if (g_aModel[nCntModel].VtxMaxModel.y < vtx.y)
				{
					g_aModel[nCntModel].VtxMaxModel.y = vtx.y;
				}
				if (g_aModel[nCntModel].VtxMaxModel.z < vtx.z)
				{
					g_aModel[nCntModel].VtxMaxModel.z = vtx.z;
				}
				pVtxBuff[nCntModel] += sizeFvF;
			}
			//			//���_�o�b�t�@���A�����b�N
			g_pMeshModel[nCntTypeModel]->UnlockVertexBuffer();
		}
	}
	
#endif
	for (int nCntTypeModel = 0; nCntTypeModel < MAX_MODEL_TYPE; nCntTypeModel++)
	{
		//���_�����擾
		nNumVtex = g_pMeshModel[nCntTypeModel]->GetNumVertices();
		//���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFvF = D3DXGetFVFVertexSize(g_pMeshModel[nCntTypeModel]->GetFVF());
		//���_�@���b�N
		g_pMeshModel[nCntTypeModel]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff[nCntTypeModel]);
		for (int nCntVtx = 0; nCntVtx < nNumVtex; nCntVtx++)
		{	//���_���W�̑��
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff[nCntTypeModel];
			if (g_aModelVtx[nCntTypeModel].VtxMinModel.x > vtx.x)
			{
				g_aModelVtx[nCntTypeModel].VtxMinModel.x = vtx.x;
			}
			if (g_aModelVtx[nCntTypeModel].VtxMinModel.y > vtx.y)
			{
				g_aModelVtx[nCntTypeModel].VtxMinModel.y = vtx.y;
			}
			if (g_aModelVtx[nCntTypeModel].VtxMinModel.z > vtx.z)
			{
				g_aModelVtx[nCntTypeModel].VtxMinModel.z = vtx.z;
			}

			if (g_aModelVtx[nCntTypeModel].VtxMaxModel.x < vtx.x)
			{
				g_aModelVtx[nCntTypeModel].VtxMaxModel.x = vtx.x;
			}
			if (g_aModelVtx[nCntTypeModel].VtxMaxModel.y < vtx.y)
			{
				g_aModelVtx[nCntTypeModel].VtxMaxModel.y = vtx.y;
			}
			if (g_aModelVtx[nCntTypeModel].VtxMaxModel.z < vtx.z)
			{
				g_aModelVtx[nCntTypeModel].VtxMaxModel.z = vtx.z;
			}
			pVtxBuff[nCntTypeModel] += sizeFvF;
		}
		//			//���_�o�b�t�@���A�����b�N
		g_pMeshModel[nCntTypeModel]->UnlockVertexBuffer();
	}


	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\exclamation000.jpg",
		&g_pTextureModel[0]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\question000.jpg",
		&g_pTextureModel[1]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		MODEL_NAME002,
		&g_pTextureModel[2]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		MODEL_NAME003,
		&g_pTextureModel[3]);

	//for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	//{
	//	for (int nCntMat = 0; nCntMat < (int)g_nNumMatModel[nCntModel]; nCntMat++)
	//	{
	//		// �}�e���A���f�[�^�ւ̃|�C���^���擾
	//		g_pMat = (D3DXMATERIAL*)g_pBuffMatModel[g_aModel[nCntModel].nType]->GetBufferPointer();
	//		{
	//			D3DXCreateTextureFromFile(pDevice,
	//				g_pMat[nCntMat].pTextureFilename,
	//				&g_pTextureModel[g_aModel[nCntModel].nType]);
	//		}
	//	}
	//}

	//float testpos = 100;
	//for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	//{
	//	// �ʒu�E�����̏����ݒ�
	//	g_aModel[nCntModel].pos = D3DXVECTOR3(testpos, 0, 0);
	//	g_aModel[nCntModel].rot = D3DXVECTOR3(0, 0, 0);
	//	g_aModel[nCntModel].fShadow = 12;
	////	g_aModel[nCntModel].fDestAngle = 0;
	//	//g_aModel
	//	//�@�e�̃Z�b�g
	//	g_aModel[nCntModel].nIdxShadow = SetShadow(g_aModel[nCntModel].pos, D3DXVECTOR3(0, 0, 0), 20.0f);

	//	testpos -= 100;
	//	g_aModel[nCntModel].bUse = true;
	//}
}

//=============================================================================
// �I������
//=============================================================================
void UninitModel(void)
{
	for (int nCntModel = 0; nCntModel < MAX_MODEL_TYPE; nCntModel++)
	{
		// ���b�V���̊J��
		if (g_pMeshModel[nCntModel] != NULL)
		{
			g_pMeshModel[nCntModel]->Release();
			g_pMeshModel[nCntModel] = NULL;
		}
		// �}�e���A���̊J��
		if (g_pBuffMatModel[nCntModel] != NULL)
		{
			g_pBuffMatModel[nCntModel]->Release();
			g_pBuffMatModel[nCntModel] = NULL;
		}
		//�e�N�X�`���̔j��
		if (g_pTextureModel[nCntModel] != NULL)
		{
			g_pTextureModel[nCntModel]->Release();
			g_pTextureModel[nCntModel] = NULL;
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateModel(void)
{
	
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;						//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;							//�}�e���A���f�[�^�ւ̃|�C���^

	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		if (g_aModel[nCntModel].bUse == true)	//���f�����g�p����Ă���
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aModel[nCntModel].mtxWorld);
			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aModel[nCntModel].rot.y, g_aModel[nCntModel].rot.x, g_aModel[nCntModel].rot.z);
			D3DXMatrixMultiply(&g_aModel[nCntModel].mtxWorld, &g_aModel[nCntModel].mtxWorld, &mtxRot);
			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aModel[nCntModel].pos.x, g_aModel[nCntModel].pos.y, g_aModel[nCntModel].pos.z);
			D3DXMatrixMultiply(&g_aModel[nCntModel].mtxWorld, &g_aModel[nCntModel].mtxWorld, &mtxTrans);
			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aModel[nCntModel].mtxWorld);
			// ���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);


			// �}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_pBuffMatModel[g_aModel[nCntModel].nType]->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_nNumMatModel[g_aModel[nCntModel].nType]; nCntMat++)
			{	// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
				// �e�N�X�`��

				pDevice->SetTexture(0, g_pTextureModel[2]);

				// ���f��(�p�[�c)�̕`��
				g_pMeshModel[g_aModel[nCntModel].nType]->DrawSubset(nCntMat);

			}
			// �}�e���A�����f�t�H���g�ɖ߂�
			pDevice->SetMaterial(&matDef);
		}
	}
}

//*****************************************************************************
//���f���|�C���^����
//*****************************************************************************
MODEL *GetModel(void)
{
	return &g_aModel[0];
}
//*****************************************************************************
//���f���Ƃ̓����蔻�菈��
//*****************************************************************************
bool CollisionModel(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 VtxMax, D3DXVECTOR3 VtxMin/*, MODEL **pModel*/)
{
	bool bLand = false;

	GAMESTATE GameState;
	GameState = GetGameState();

	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		if (g_aModel[nCntModel].bUse == true)
		{
#if 0
			//���f����Y���̒�
			if (pPos->y < g_aModel[nCntModel].pos.y + g_aModel[nCntModel].VtxMaxModel.y
				&& pPos->y > g_aModel[nCntModel].pos.y + g_aModel[nCntModel].VtxMinModel.y)
			{
				//���f����Z���̒�
				if (pPos->z + VtxMin.z < g_aModel[nCntModel].pos.z + g_aModel[nCntModel].VtxMaxModel.z
					&& pPos->z + VtxMax.z > g_aModel[nCntModel].pos.z + g_aModel[nCntModel].VtxMinModel.z)
				{
					//���f����X���̒�
					if (pPos->x + VtxMin.x < g_aModel[nCntModel].pos.x + g_aModel[nCntModel].VtxMaxModel.x
						&& pPos->x + VtxMax.x > g_aModel[nCntModel].pos.x + g_aModel[nCntModel].VtxMinModel.x)
					{
#if 1
						if (g_aModel[nCntModel].nType == 1)
						{

							//X���̓����蔻��
							if (pPosOld->x + 1 > g_aModel[nCntModel].pos.x + g_aModel[nCntModel].VtxMaxModel.x)
							{
								pPos->x = g_aModel[nCntModel].pos.x + g_aModel[nCntModel].VtxMaxModel.x + VtxMax.x;
								pPosOld->x = g_aModel[nCntModel].pos.x + g_aModel[nCntModel].VtxMaxModel.x + VtxMax.x;
							}
							else if (pPosOld->x - 1 < g_aModel[nCntModel].pos.x + g_aModel[nCntModel].VtxMinModel.x)
							{
								pPos->x = g_aModel[nCntModel].pos.x + g_aModel[nCntModel].VtxMinModel.x + VtxMin.x;
								pPosOld->x = g_aModel[nCntModel].pos.x + g_aModel[nCntModel].VtxMinModel.x + VtxMin.x;
							}

							//Z���̓����蔻��
							if (pPosOld->z + 1 > g_aModel[nCntModel].pos.z + g_aModel[nCntModel].VtxMaxModel.z)
							{
								pPos->z = g_aModel[nCntModel].pos.z + g_aModel[nCntModel].VtxMaxModel.z + VtxMax.z;
								pPosOld->z = g_aModel[nCntModel].pos.z + g_aModel[nCntModel].VtxMaxModel.z + VtxMax.z;
							}
							else if (pPosOld->z - 1 < g_aModel[nCntModel].pos.z + g_aModel[nCntModel].VtxMinModel.z)
							{
								pPos->z = g_aModel[nCntModel].pos.z + g_aModel[nCntModel].VtxMinModel.z + VtxMin.z;
								pPosOld->z = g_aModel[nCntModel].pos.z + g_aModel[nCntModel].VtxMinModel.z + VtxMin.z;
							}
							//Y���̓����蔻��
							if (pPosOld->y >= g_aModel[nCntModel].pos.y + g_aModel[nCntModel].VtxMaxModel.y)
							{
								pPos->y = g_aModel[nCntModel].pos.y + g_aModel[nCntModel].VtxMaxModel.y;
								pPosOld->y = g_aModel[nCntModel].pos.y + g_aModel[nCntModel].VtxMaxModel.y;

							}
							else if (pPosOld->y <= g_aModel[nCntModel].pos.y + g_aModel[nCntModel].VtxMinModel.y)
							{
								pPos->y = g_aModel[nCntModel].pos.y + g_aModel[nCntModel].VtxMinModel.y;
								pPosOld->y = g_aModel[nCntModel].pos.y + g_aModel[nCntModel].VtxMinModel.y;
							}
#endif
						}
					}
				}
			}
#endif

#if 1
			//���f����Y���̒�
			if (pPos->y < g_aModel[nCntModel].pos.y + g_aModelVtx[g_aModel[nCntModel].nType].VtxMaxModel.y
				&& pPos->y > g_aModel[nCntModel].pos.y + g_aModelVtx[g_aModel[nCntModel].nType].VtxMinModel.y)
			{
				//���f����Z���̒�
				if (pPos->z + VtxMin.z < g_aModel[nCntModel].pos.z + g_aModelVtx[g_aModel[nCntModel].nType].VtxMaxModel.z
					&& pPos->z + VtxMax.z > g_aModel[nCntModel].pos.z + g_aModelVtx[g_aModel[nCntModel].nType].VtxMinModel.z)
				{
					//���f����X���̒�
					if (pPos->x + VtxMin.x < g_aModel[nCntModel].pos.x + g_aModelVtx[g_aModel[nCntModel].nType].VtxMaxModel.x
						&& pPos->x + VtxMax.x > g_aModel[nCntModel].pos.x + g_aModelVtx[g_aModel[nCntModel].nType].VtxMinModel.x)
					{
#if 1
							//X���̓����蔻��
							if (pPosOld->x + 1 > g_aModel[nCntModel].pos.x + g_aModelVtx[g_aModel[nCntModel].nType].VtxMaxModel.x)
							{
								pPos->x = g_aModel[nCntModel].pos.x + g_aModelVtx[g_aModel[nCntModel].nType].VtxMaxModel.x + VtxMax.x;
								pPosOld->x = g_aModel[nCntModel].pos.x + g_aModelVtx[g_aModel[nCntModel].nType].VtxMaxModel.x + VtxMax.x;
							}
							else if (pPosOld->x - 1 < g_aModel[nCntModel].pos.x + g_aModelVtx[g_aModel[nCntModel].nType].VtxMinModel.x)
							{
								pPos->x = g_aModel[nCntModel].pos.x + g_aModelVtx[g_aModel[nCntModel].nType].VtxMinModel.x + VtxMin.x;
								pPosOld->x = g_aModel[nCntModel].pos.x + g_aModelVtx[g_aModel[nCntModel].nType].VtxMinModel.x + VtxMin.x;
							}

							//Z���̓����蔻��
							else if (pPosOld->z + 1 > g_aModel[nCntModel].pos.z + g_aModelVtx[g_aModel[nCntModel].nType].VtxMaxModel.z)
							{
								pPos->z = g_aModel[nCntModel].pos.z + g_aModelVtx[g_aModel[nCntModel].nType].VtxMaxModel.z + VtxMax.z;
								pPosOld->z = g_aModel[nCntModel].pos.z + g_aModelVtx[g_aModel[nCntModel].nType].VtxMaxModel.z + VtxMax.z;
							}
							else if (pPosOld->z - 1 < g_aModel[nCntModel].pos.z + g_aModelVtx[g_aModel[nCntModel].nType].VtxMinModel.z)
							{
								pPos->z = g_aModel[nCntModel].pos.z + g_aModelVtx[g_aModel[nCntModel].nType].VtxMinModel.z + VtxMin.z;
								pPosOld->z = g_aModel[nCntModel].pos.z + g_aModelVtx[g_aModel[nCntModel].nType].VtxMinModel.z + VtxMin.z;
							}
							//Y���̓����蔻��
							else if (pPosOld->y >= g_aModel[nCntModel].pos.y + g_aModelVtx[g_aModel[nCntModel].nType].VtxMaxModel.y)
							{
								pPos->y = g_aModel[nCntModel].pos.y + g_aModelVtx[g_aModel[nCntModel].nType].VtxMaxModel.y;
								pPosOld->y = g_aModel[nCntModel].pos.y + g_aModelVtx[g_aModel[nCntModel].nType].VtxMaxModel.y;

							}
							else if (pPosOld->y <= g_aModel[nCntModel].pos.y + g_aModelVtx[g_aModel[nCntModel].nType].VtxMinModel.y)
							{
								pPos->y = g_aModel[nCntModel].pos.y + g_aModelVtx[g_aModel[nCntModel].nType].VtxMinModel.y;
								pPosOld->y = g_aModel[nCntModel].pos.y + g_aModelVtx[g_aModel[nCntModel].nType].VtxMinModel.y;
							}
#endif
					}
				}
			}
#endif


		}
	}
	return bLand;
}


//=============================================================================
// �ݒ菈��
//=============================================================================
void SetModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType)
{
	int nNumVtex;	//���_��
	DWORD sizeFvF;	//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff[MAX_MODEL];	//���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 vtx[MAX_MODEL];

	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		if (g_aModel[nCntModel].bUse == false)
		{
#if 1

			//for (int nCntTypeModel = 0; nCntTypeModel < MAX_MODEL_TYPE; nCntTypeModel++)
			//{
				//���_�����擾
				nNumVtex = g_pMeshModel[nType]->GetNumVertices();
				//���_�t�H�[�}�b�g�̃T�C�Y���擾
				sizeFvF = D3DXGetFVFVertexSize(g_pMeshModel[nType]->GetFVF());
			//	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
				//{
					//���_�@���b�N
					g_pMeshModel[nType]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff[nType]);
					for (int nCntVtx = 0; nCntVtx < nNumVtex; nCntVtx++)
					{	//���_���W�̑��
						D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff[nType];
						if (g_aModel[nCntModel].VtxMinModel.x > vtx.x)
						{
							g_aModel[nCntModel].VtxMinModel.x = vtx.x;
						}
						if (g_aModel[nCntModel].VtxMinModel.y > vtx.y)
						{
							g_aModel[nCntModel].VtxMinModel.y = vtx.y;
						}
						if (g_aModel[nCntModel].VtxMinModel.z > vtx.z)
						{
							g_aModel[nCntModel].VtxMinModel.z = vtx.z;
						}

						if (g_aModel[nCntModel].VtxMaxModel.x < vtx.x)
						{
							g_aModel[nCntModel].VtxMaxModel.x = vtx.x;
						}
						if (g_aModel[nCntModel].VtxMaxModel.y < vtx.y)
						{
							g_aModel[nCntModel].VtxMaxModel.y = vtx.y;
						}
						if (g_aModel[nCntModel].VtxMaxModel.z < vtx.z)
						{
							g_aModel[nCntModel].VtxMaxModel.z = vtx.z;
						}
						pVtxBuff[nCntModel] += sizeFvF;
					}
					//			//���_�o�b�t�@���A�����b�N
					g_pMeshModel[nType]->UnlockVertexBuffer();
				//}
			//}
			// �ʒu�E�����̏����ݒ�
#endif
			g_aModel[nCntModel].pos = pos;
			g_aModel[nCntModel].rot = D3DXVECTOR3(0, 0, 0);
			g_aModel[nCntModel].fShadow = 12;
			g_aModel[nCntModel].nType = nType;
			//�@�e�̃Z�b�g
			g_aModel[nCntModel].nIdxShadow = SetShadow(g_aModel[nCntModel].pos, D3DXVECTOR3(0, 0, 0), 20.0f);
			g_aModel[nCntModel].bUse = true;
			break;
		}
	}
}
