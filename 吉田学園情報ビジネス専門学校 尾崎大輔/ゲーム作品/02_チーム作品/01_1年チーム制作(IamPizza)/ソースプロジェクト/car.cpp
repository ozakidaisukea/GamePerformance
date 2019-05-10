//=============================================================================
//
// �ԏ��� [car.cpp]
// Author : SHUN YOKOMICHI
//
//=============================================================================
#include "car.h"
#include "shadow.h"			// �e�̏���
#include "camera.h"			// �J�����̏���
#include "game.h"

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPD3DXMESH g_pMeshCar[MAX_CAR_TYPE];						//���b�V�����ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatCar[MAX_CAR_TYPE];				//�}�e���A�����ւ̃|�C���^
LPDIRECT3DTEXTURE9	g_pTextureCar[MAX_CAR_TYPE];			//�e�N�X�`���ւ̃|�C���^
DWORD g_nNumMatCar[MAX_CAR_TYPE] = {};					//�}�e���A�����̐�
CAR g_aCar[MAX_CAR];
//D3DXMATERIAL *g_pMat;
VTXCAR g_aCarVtx[MAX_CAR_TYPE];
//=============================================================================
// ����������
//=============================================================================
void InitCar(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	
	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(CAR_NAME000, D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_pBuffMatCar[0], NULL, &g_nNumMatCar[0], &g_pMeshCar[0]);
	D3DXLoadMeshFromX(CAR_NAME001, D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_pBuffMatCar[1], NULL, &g_nNumMatCar[1], &g_pMeshCar[1]);
	D3DXLoadMeshFromX(CAR_NAME002, D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_pBuffMatCar[2], NULL, &g_nNumMatCar[2], &g_pMeshCar[2]);
	D3DXLoadMeshFromX(CAR_NAME003, D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_pBuffMatCar[3], NULL, &g_nNumMatCar[3], &g_pMeshCar[3]);
	D3DXLoadMeshFromX(CAR_NAME004, D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_pBuffMatCar[4], NULL, &g_nNumMatCar[4], &g_pMeshCar[4]);
	D3DXLoadMeshFromX(CAR_NAME005, D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_pBuffMatCar[5], NULL, &g_nNumMatCar[5], &g_pMeshCar[5]);
	D3DXLoadMeshFromX(CAR_NAME006, D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_pBuffMatCar[6], NULL, &g_nNumMatCar[6], &g_pMeshCar[6]);
	D3DXLoadMeshFromX(CAR_NAME007, D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_pBuffMatCar[7], NULL, &g_nNumMatCar[7], &g_pMeshCar[7]);

	int nNumVtex;	//���_��
	DWORD sizeFvF;	//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff[MAX_CAR];	//���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 vtx[MAX_CAR];

	for (int nCntCar = 0; nCntCar < MAX_CAR; nCntCar++)
	{
		g_aCar[nCntCar].VtxMinEnemy = D3DXVECTOR3(10000, 0, 10000);
		g_aCar[nCntCar].VtxMaxEnemy = D3DXVECTOR3(-10000, 0, -10000);
		g_aCar[nCntCar].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aCar[nCntCar].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aCar[nCntCar].nPattan = 0;
		g_aCar[nCntCar].nActiontime = 0;
		g_aCar[nCntCar].nType = 0;
		g_aCar[nCntCar].nCntTime = 0;
		g_aCar[nCntCar].fSpeed = 0.0f;
		g_aCar[nCntCar].fDestAngle = 0.0f;
		g_aCar[nCntCar].bUse = false;
		g_aCar[nCntCar].bChange = false;
	}
	for (int nCntTypeEnemy = 0; nCntTypeEnemy < MAX_CAR; nCntTypeEnemy++)
	{
		g_aCarVtx[nCntTypeEnemy].VtxMaxEnemy = D3DXVECTOR3(-10000, 0, -10000);
		g_aCarVtx[nCntTypeEnemy].VtxMinEnemy = D3DXVECTOR3(10000, 0, 10000);
	}


	for (int nCntTypeEnemy = 0; nCntTypeEnemy < MAX_CAR_TYPE; nCntTypeEnemy++)
	{
		//���_�����擾
		nNumVtex = g_pMeshCar[nCntTypeEnemy]->GetNumVertices();
		//���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFvF = D3DXGetFVFVertexSize(g_pMeshCar[nCntTypeEnemy]->GetFVF());
		//���_�@���b�N
		g_pMeshCar[nCntTypeEnemy]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff[nCntTypeEnemy]);
		for (int nCntVtx = 0; nCntVtx < nNumVtex; nCntVtx++)
		{	//���_���W�̑��
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff[nCntTypeEnemy];
			if (g_aCarVtx[nCntTypeEnemy].VtxMinEnemy.x > vtx.x)
			{
				g_aCarVtx[nCntTypeEnemy].VtxMinEnemy.x = vtx.x;
			}
			if (g_aCarVtx[nCntTypeEnemy].VtxMinEnemy.y > vtx.y)
			{
				g_aCarVtx[nCntTypeEnemy].VtxMinEnemy.y = vtx.y;
			}
			if (g_aCarVtx[nCntTypeEnemy].VtxMinEnemy.z > vtx.z)
			{
				g_aCarVtx[nCntTypeEnemy].VtxMinEnemy.z = vtx.z;
			}

			if (g_aCarVtx[nCntTypeEnemy].VtxMaxEnemy.x < vtx.x)
			{
				g_aCarVtx[nCntTypeEnemy].VtxMaxEnemy.x = vtx.x;
			}
			if (g_aCarVtx[nCntTypeEnemy].VtxMaxEnemy.y < vtx.y)
			{
				g_aCarVtx[nCntTypeEnemy].VtxMaxEnemy.y = vtx.y;
			}
			if (g_aCarVtx[nCntTypeEnemy].VtxMaxEnemy.z < vtx.z)
			{
				g_aCarVtx[nCntTypeEnemy].VtxMaxEnemy.z = vtx.z;
			}
			pVtxBuff[nCntTypeEnemy] += sizeFvF;
		}
		//			//���_�o�b�t�@���A�����b�N
		g_pMeshCar[nCntTypeEnemy]->UnlockVertexBuffer();
	}
}

//=============================================================================
// �I������
//=============================================================================
void UninitCar(void)
{
	for (int nCntCar = 0; nCntCar < MAX_CAR_TYPE; nCntCar++)
	{
		// ���b�V���̊J��
		if (g_pMeshCar[nCntCar] != NULL)
		{
			g_pMeshCar[nCntCar]->Release();
			g_pMeshCar[nCntCar] = NULL;
		}
		// �}�e���A���̊J��
		if (g_pBuffMatCar[nCntCar] != NULL)
		{
			g_pBuffMatCar[nCntCar]->Release();
			g_pBuffMatCar[nCntCar] = NULL;
		}
		//�e�N�X�`���̔j��
		if (g_pTextureCar[nCntCar] != NULL)
		{
			g_pTextureCar[nCntCar]->Release();
			g_pTextureCar[nCntCar] = NULL;
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateCar(void)
{
	// �ϐ��錾
	Camera *pCamera;
	pCamera = GetCamera();

	for (int nCntCar = 0; nCntCar < MAX_CAR; nCntCar++)
	{
		if (g_aCar[nCntCar].bUse == true)
		{
			g_aCar[nCntCar].nCntTime++;

			//�J�����Ƃ̋��������߂�
			double length = pow((g_aCar[nCntCar].pos.x - pCamera->posV.x)*(g_aCar[nCntCar].pos.x - pCamera->posV.x)
				+ (g_aCar[nCntCar].pos.z - pCamera->posV.z)*(g_aCar[nCntCar].pos.z - pCamera->posV.z), 0.5);

			//float�^�ɕϊ�
			g_aCar[nCntCar].fLength = (float)length;

			if (g_aCar[nCntCar].nCntTime <= g_aCar[nCntCar].nActiontime)
			{
				if (g_aCar[nCntCar].nPattan == 0)
				{
					if (g_aCar[nCntCar].bChange == true)
					{
						// �E�ړ�
						g_aCar[nCntCar].move.x += sinf(D3DX_PI * 0.5f) * g_aCar[nCntCar].fSpeed;
						g_aCar[nCntCar].move.z += cosf(D3DX_PI * 0.5f) * g_aCar[nCntCar].fSpeed;
					}
					else
					{
						// ���ړ�
						g_aCar[nCntCar].move.x += sinf(-D3DX_PI * 0.5f) * g_aCar[nCntCar].fSpeed;
						g_aCar[nCntCar].move.z += cosf(-D3DX_PI * 0.5f) * g_aCar[nCntCar].fSpeed;
					}
				}
				else
				{
					if (g_aCar[nCntCar].bChange == true)
					{
						// ���ړ�
						g_aCar[nCntCar].move.x += sinf(D3DX_PI) * g_aCar[nCntCar].fSpeed;
						g_aCar[nCntCar].move.z += cosf(D3DX_PI) * g_aCar[nCntCar].fSpeed;
					}
					else
					{
						// ��ړ�
						g_aCar[nCntCar].move.x += sinf(0) * g_aCar[nCntCar].fSpeed;
						g_aCar[nCntCar].move.z += cosf(0) * g_aCar[nCntCar].fSpeed;
					}
				}
			}
			if (g_aCar[nCntCar].nCntTime >= g_aCar[nCntCar].nActiontime + 1 && g_aCar[nCntCar].nCntTime <= g_aCar[nCntCar].nActiontime + 120)
			{	// �~�܂鎞��
				g_aCar[nCntCar].move.x += 0.0f;
				g_aCar[nCntCar].move.z += 0.0f;


				if (g_aCar[nCntCar].nCntTime >= g_aCar[nCntCar].nActiontime + 120)
				{
					g_aCar[nCntCar].bChange = g_aCar[nCntCar].bChange ? false : true;			// �s���̐ؑ�
					g_aCar[nCntCar].nCntTime = 0;					// �J�E���g��������

				}
			}

			//�t�B�[���h�̑傫���̔���
			if (FIELD_MAX_SIZE * 3.1 <= g_aCar[nCntCar].pos.x)
			{
				g_aCar[nCntCar].bUse = false;
				DeleteShadow(g_aCar[nCntCar].nIdxShadow);
			}
			if (-FIELD_MAX_SIZE * 1.1 >= g_aCar[nCntCar].pos.x)
			{
				g_aCar[nCntCar].bUse = false;
				DeleteShadow(g_aCar[nCntCar].nIdxShadow);
			}
			if (FIELD_MAX_SIZE * 3.1 <= g_aCar[nCntCar].pos.z)
			{
				g_aCar[nCntCar].bUse = false;
				DeleteShadow(g_aCar[nCntCar].nIdxShadow);
			}
			if (-FIELD_MAX_SIZE * 1.1 >= g_aCar[nCntCar].pos.z)
			{
				g_aCar[nCntCar].bUse = false;
				DeleteShadow(g_aCar[nCntCar].nIdxShadow);
			}

			// ����
			g_aCar[nCntCar].move.x += (0.0f - g_aCar[nCntCar].move.x) * 0.15f;
			g_aCar[nCntCar].move.z += (0.0f - g_aCar[nCntCar].move.z) * 0.15f;

			// �ʒu�X�V
			g_aCar[nCntCar].pos += g_aCar[nCntCar].move;

			SetPositionShadow(g_aCar[nCntCar].nIdxShadow, D3DXVECTOR3(g_aCar[nCntCar].pos.x, 0.1f, g_aCar[nCntCar].pos.z), 60.0f);


		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawCar(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;						//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;							//�}�e���A���f�[�^�ւ̃|�C���^

	for (int nCntCar = 0; nCntCar < MAX_CAR; nCntCar++)
	{
		if (g_aCar[nCntCar].bUse == true)	//���f�����g�p����Ă���
		{
			if (g_aCar[nCntCar].fLength < 2500)
			{//���f���ƃv���C���[�̋����ŕ`�悷�邩���߂�

			// ���[���h�}�g���b�N�X�̏�����
				D3DXMatrixIdentity(&g_aCar[nCntCar].mtxWorld);
				// ��]�𔽉f
				D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aCar[nCntCar].rot.y, g_aCar[nCntCar].rot.x, g_aCar[nCntCar].rot.z);
				D3DXMatrixMultiply(&g_aCar[nCntCar].mtxWorld, &g_aCar[nCntCar].mtxWorld, &mtxRot);
				// �ʒu�𔽉f
				D3DXMatrixTranslation(&mtxTrans, g_aCar[nCntCar].pos.x, g_aCar[nCntCar].pos.y, g_aCar[nCntCar].pos.z);
				D3DXMatrixMultiply(&g_aCar[nCntCar].mtxWorld, &g_aCar[nCntCar].mtxWorld, &mtxTrans);
				// ���[���h�}�g���b�N�X�̐ݒ�
				pDevice->SetTransform(D3DTS_WORLD, &g_aCar[nCntCar].mtxWorld);
				// ���݂̃}�e���A�����擾
				pDevice->GetMaterial(&matDef);


				// �}�e���A���f�[�^�ւ̃|�C���^���擾
				pMat = (D3DXMATERIAL*)g_pBuffMatCar[g_aCar[nCntCar].nType]->GetBufferPointer();

				for (int nCntMat = 0; nCntMat < (int)g_nNumMatCar[g_aCar[nCntCar].nType]; nCntMat++)
				{	// �}�e���A���̐ݒ�
					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
					// �e�N�X�`��

					pDevice->SetTexture(0, NULL);

					// ���f��(�p�[�c)�̕`��
					g_pMeshCar[g_aCar[nCntCar].nType]->DrawSubset(nCntMat);

				}
				// �}�e���A�����f�t�H���g�ɖ߂�
				pDevice->SetMaterial(&matDef);
				pDevice->SetTexture(0, NULL);
			}
		}
	}
}

//*****************************************************************************
//���f���|�C���^����
//*****************************************************************************
CAR *GetCar(void)
{
	return &g_aCar[0];
}
//*****************************************************************************
//�ʍs�l�Ƃ̓����蔻�菈��
//*****************************************************************************
bool CollisionCar(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 VtxMax, D3DXVECTOR3 VtxMin)
{
	bool bLand = false;

	GAMESTATE GameState;
	GameState = GetGameState();

	for (int nCntCar = 0; nCntCar < MAX_CAR; nCntCar++)
	{
		if (g_aCar[nCntCar].bUse == true)
		{
#if 1
			//���f����Y���̒�
			if (pPos->y < g_aCar[nCntCar].pos.y + g_aCarVtx[g_aCar[nCntCar].nType].VtxMaxEnemy.y
				&& pPos->y > g_aCar[nCntCar].pos.y + g_aCarVtx[g_aCar[nCntCar].nType].VtxMinEnemy.y)
			{
				//���f����Z���̒�
				if (pPos->z + VtxMin.z < g_aCar[nCntCar].pos.z + g_aCarVtx[g_aCar[nCntCar].nType].VtxMaxEnemy.z
					&& pPos->z + VtxMax.z > g_aCar[nCntCar].pos.z + g_aCarVtx[g_aCar[nCntCar].nType].VtxMinEnemy.z)
				{
					//���f����X���̒�
					if (pPos->x + VtxMin.x < g_aCar[nCntCar].pos.x + g_aCarVtx[g_aCar[nCntCar].nType].VtxMaxEnemy.x
						&& pPos->x + VtxMax.x > g_aCar[nCntCar].pos.x + g_aCarVtx[g_aCar[nCntCar].nType].VtxMinEnemy.x)
					{
#if 1
							//X���̓����蔻��
							if (pPosOld->x + 1 > g_aCar[nCntCar].pos.x + g_aCarVtx[g_aCar[nCntCar].nType].VtxMaxEnemy.x)
							{
								pPos->x = g_aCar[nCntCar].pos.x + g_aCarVtx[g_aCar[nCntCar].nType].VtxMaxEnemy.x + VtxMax.x;
								pPosOld->x = g_aCar[nCntCar].pos.x + g_aCarVtx[g_aCar[nCntCar].nType].VtxMaxEnemy.x + VtxMax.x;
								bLand = true;
							}
							else if (pPosOld->x - 1 < g_aCar[nCntCar].pos.x + g_aCarVtx[g_aCar[nCntCar].nType].VtxMinEnemy.x)
							{
								pPos->x = g_aCar[nCntCar].pos.x + g_aCarVtx[g_aCar[nCntCar].nType].VtxMinEnemy.x + VtxMin.x;
								pPosOld->x = g_aCar[nCntCar].pos.x + g_aCarVtx[g_aCar[nCntCar].nType].VtxMinEnemy.x + VtxMin.x;
								bLand = true;
							}

							//Z���̓����蔻��
							else if (pPosOld->z + 1 > g_aCar[nCntCar].pos.z + g_aCarVtx[g_aCar[nCntCar].nType].VtxMaxEnemy.z)
							{
								pPos->z = g_aCar[nCntCar].pos.z + g_aCarVtx[g_aCar[nCntCar].nType].VtxMaxEnemy.z + VtxMax.z;
								pPosOld->z = g_aCar[nCntCar].pos.z + g_aCarVtx[g_aCar[nCntCar].nType].VtxMaxEnemy.z + VtxMax.z;
								bLand = true;
							}
							else if (pPosOld->z - 1 < g_aCar[nCntCar].pos.z + g_aCarVtx[g_aCar[nCntCar].nType].VtxMinEnemy.z)
							{
								pPos->z = g_aCar[nCntCar].pos.z + g_aCarVtx[g_aCar[nCntCar].nType].VtxMinEnemy.z + VtxMin.z;
								pPosOld->z = g_aCar[nCntCar].pos.z + g_aCarVtx[g_aCar[nCntCar].nType].VtxMinEnemy.z + VtxMin.z;
								bLand = true;
							}
							//Y���̓����蔻��
							else if (pPosOld->y >= g_aCar[nCntCar].pos.y + g_aCarVtx[g_aCar[nCntCar].nType].VtxMaxEnemy.y)
							{
								pPos->y = g_aCar[nCntCar].pos.y + g_aCarVtx[g_aCar[nCntCar].nType].VtxMaxEnemy.y;
								pPosOld->y = g_aCar[nCntCar].pos.y + g_aCarVtx[g_aCar[nCntCar].nType].VtxMaxEnemy.y;
								bLand = true;
							}
							else if (pPosOld->y <= g_aCar[nCntCar].pos.y + g_aCarVtx[g_aCar[nCntCar].nType].VtxMinEnemy.y)
							{
								pPos->y = g_aCar[nCntCar].pos.y + g_aCarVtx[g_aCar[nCntCar].nType].VtxMinEnemy.y;
								pPosOld->y = g_aCar[nCntCar].pos.y + g_aCarVtx[g_aCar[nCntCar].nType].VtxMinEnemy.y;
								bLand = true;
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
void SetCar(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType, int nPattan, int nActiontime, float fSpeed, bool bChange)
{
	int nNumVtex;	//���_��
	DWORD sizeFvF;	//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff[MAX_CAR];	//���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 vtx[MAX_CAR];

	for (int nCntCar = 0; nCntCar < MAX_CAR; nCntCar++)
	{
		if (g_aCar[nCntCar].bUse == false)
		{
#if 1

			//for (int nCntTypeEnemy = 0; nCntTypeEnemy < MAX_ENEMY_TYPE; nCntTypeEnemy++)
			//{
				//���_�����擾
				nNumVtex = g_pMeshCar[nType]->GetNumVertices();
				//���_�t�H�[�}�b�g�̃T�C�Y���擾
				sizeFvF = D3DXGetFVFVertexSize(g_pMeshCar[nType]->GetFVF());
			//	for (int nCntCar = 0; nCntCar < MAX_ENEMY; nCntCar++)
				//{
					//���_�@���b�N
					g_pMeshCar[nType]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff[nType]);
					for (int nCntVtx = 0; nCntVtx < nNumVtex; nCntVtx++)
					{	//���_���W�̑��
						D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff[nType];
						if (g_aCar[nCntCar].VtxMinEnemy.x > vtx.x)
						{
							g_aCar[nCntCar].VtxMinEnemy.x = vtx.x;
						}
						if (g_aCar[nCntCar].VtxMinEnemy.y > vtx.y)
						{
							g_aCar[nCntCar].VtxMinEnemy.y = vtx.y;
						}
						if (g_aCar[nCntCar].VtxMinEnemy.z > vtx.z)
						{
							g_aCar[nCntCar].VtxMinEnemy.z = vtx.z;
						}

						if (g_aCar[nCntCar].VtxMaxEnemy.x < vtx.x)
						{
							g_aCar[nCntCar].VtxMaxEnemy.x = vtx.x;
						}
						if (g_aCar[nCntCar].VtxMaxEnemy.y < vtx.y)
						{
							g_aCar[nCntCar].VtxMaxEnemy.y = vtx.y;
						}
						if (g_aCar[nCntCar].VtxMaxEnemy.z < vtx.z)
						{
							g_aCar[nCntCar].VtxMaxEnemy.z = vtx.z;
						}
						pVtxBuff[nCntCar] += sizeFvF;
					}
					//			//���_�o�b�t�@���A�����b�N
					g_pMeshCar[nType]->UnlockVertexBuffer();
				//}
			//}
			// �ʒu�E�����̏����ݒ�
#endif
			g_aCar[nCntCar].pos = pos;
			g_aCar[nCntCar].rot = rot;
			g_aCar[nCntCar].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aCar[nCntCar].fShadow = 6;
			g_aCar[nCntCar].nType = nType;
			g_aCar[nCntCar].nActiontime = nActiontime;		// �s������
			g_aCar[nCntCar].nCntTime = 0;
			g_aCar[nCntCar].nPattan = nPattan;			// �s���p�^�[��( 0 : ���ړ� / 1 :�c�ړ�)
			g_aCar[nCntCar].bChange = bChange;			// �s���̕ω��̑��(�X�V�ŕω�)
			g_aCar[nCntCar].fSpeed = fSpeed;
			//�@�e�̃Z�b�g
			g_aCar[nCntCar].nIdxShadow = SetShadow(D3DXVECTOR3(g_aCar[nCntCar].pos.x, g_aCar[nCntCar].pos.y + 0.1f, g_aCar[nCntCar].pos.z), D3DXVECTOR3(0, 0, 0), 20.0f);
			g_aCar[nCntCar].bUse = true;
			break;
		}
	}
}
