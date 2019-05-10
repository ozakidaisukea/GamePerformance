//=============================================================================
//
// �ʍs�l���� [passage.cpp]
// Author : SHUN YOKOMICHI
//
//=============================================================================
#include "passage.h"
#include "shadow.h"			// �e�̏���
#include "camera.h"			// �J�����̏���
#include "game.h"

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPD3DXMESH g_pMeshPassage[MAX_PASSAGE_TYPE];						//���b�V�����ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatPassage[MAX_PASSAGE_TYPE];				//�}�e���A�����ւ̃|�C���^
LPDIRECT3DTEXTURE9	g_pTexturePassage[MAX_PASSAGE_TYPE];			//�e�N�X�`���ւ̃|�C���^
DWORD g_nNumMatPassage[MAX_PASSAGE_TYPE] = {};					//�}�e���A�����̐�
PASSAGE g_aPassage[MAX_PASSAGE];
//D3DXMATERIAL *g_pMat;
VTXPASSAGE g_aPassageVtx[MAX_PASSAGE_TYPE];
//=============================================================================
// ����������
//=============================================================================
void InitPassage(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(PASSAGE_NAME000,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatPassage[0],
		NULL,
		&g_nNumMatPassage[0],
		&g_pMeshPassage[0]);


	int nNumVtex;	//���_��
	DWORD sizeFvF;	//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff[MAX_PASSAGE];	//���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 vtx[MAX_PASSAGE];

	for (int nCntPassage = 0; nCntPassage < MAX_PASSAGE; nCntPassage++)
	{
		g_aPassage[nCntPassage].VtxMinEnemy = D3DXVECTOR3(10000, 0, 10000);
		g_aPassage[nCntPassage].VtxMaxEnemy = D3DXVECTOR3(-10000, 0, -10000);
		g_aPassage[nCntPassage].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPassage[nCntPassage].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPassage[nCntPassage].nPattan = 0;
		g_aPassage[nCntPassage].nActiontime = 0;
		g_aPassage[nCntPassage].nType = 0;
		g_aPassage[nCntPassage].nCntTime = 0;
		g_aPassage[nCntPassage].fSpeed = 0.0f;
		g_aPassage[nCntPassage].fDestAngle = 0.0f;
		g_aPassage[nCntPassage].bUse = false;
		g_aPassage[nCntPassage].bChange = false;
	}
	for (int nCntTypeEnemy = 0; nCntTypeEnemy < MAX_PASSAGE; nCntTypeEnemy++)
	{
		g_aPassageVtx[nCntTypeEnemy].VtxMaxEnemy = D3DXVECTOR3(-10000, 0, -10000);
		g_aPassageVtx[nCntTypeEnemy].VtxMinEnemy = D3DXVECTOR3(10000, 0, 10000);
	}


	for (int nCntTypeEnemy = 0; nCntTypeEnemy < MAX_PASSAGE_TYPE; nCntTypeEnemy++)
	{
		//���_�����擾
		nNumVtex = g_pMeshPassage[nCntTypeEnemy]->GetNumVertices();
		//���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFvF = D3DXGetFVFVertexSize(g_pMeshPassage[nCntTypeEnemy]->GetFVF());
		//���_�@���b�N
		g_pMeshPassage[nCntTypeEnemy]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff[nCntTypeEnemy]);
		for (int nCntVtx = 0; nCntVtx < nNumVtex; nCntVtx++)
		{	//���_���W�̑��
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff[nCntTypeEnemy];
			if (g_aPassageVtx[nCntTypeEnemy].VtxMinEnemy.x > vtx.x)
			{
				g_aPassageVtx[nCntTypeEnemy].VtxMinEnemy.x = vtx.x;
			}
			if (g_aPassageVtx[nCntTypeEnemy].VtxMinEnemy.y > vtx.y)
			{
				g_aPassageVtx[nCntTypeEnemy].VtxMinEnemy.y = vtx.y;
			}
			if (g_aPassageVtx[nCntTypeEnemy].VtxMinEnemy.z > vtx.z)
			{
				g_aPassageVtx[nCntTypeEnemy].VtxMinEnemy.z = vtx.z;
			}

			if (g_aPassageVtx[nCntTypeEnemy].VtxMaxEnemy.x < vtx.x)
			{
				g_aPassageVtx[nCntTypeEnemy].VtxMaxEnemy.x = vtx.x;
			}
			if (g_aPassageVtx[nCntTypeEnemy].VtxMaxEnemy.y < vtx.y)
			{
				g_aPassageVtx[nCntTypeEnemy].VtxMaxEnemy.y = vtx.y;
			}
			if (g_aPassageVtx[nCntTypeEnemy].VtxMaxEnemy.z < vtx.z)
			{
				g_aPassageVtx[nCntTypeEnemy].VtxMaxEnemy.z = vtx.z;
			}
			pVtxBuff[nCntTypeEnemy] += sizeFvF;
		}
		//			//���_�o�b�t�@���A�����b�N
		g_pMeshPassage[nCntTypeEnemy]->UnlockVertexBuffer();
	}
}

//=============================================================================
// �I������
//=============================================================================
void UninitPassage(void)
{
	for (int nCntPassage = 0; nCntPassage < MAX_PASSAGE_TYPE; nCntPassage++)
	{
		// ���b�V���̊J��
		if (g_pMeshPassage[nCntPassage] != NULL)
		{
			g_pMeshPassage[nCntPassage]->Release();
			g_pMeshPassage[nCntPassage] = NULL;
		}
		// �}�e���A���̊J��
		if (g_pBuffMatPassage[nCntPassage] != NULL)
		{
			g_pBuffMatPassage[nCntPassage]->Release();
			g_pBuffMatPassage[nCntPassage] = NULL;
		}
		//�e�N�X�`���̔j��
		if (g_pTexturePassage[nCntPassage] != NULL)
		{
			g_pTexturePassage[nCntPassage]->Release();
			g_pTexturePassage[nCntPassage] = NULL;
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePassage(void)
{
	// �ϐ��錾
	Camera *pCamera;
	pCamera = GetCamera();

	for (int nCntPassage = 0; nCntPassage < MAX_PASSAGE; nCntPassage++)
	{
		if (g_aPassage[nCntPassage].bUse == true)
		{
			g_aPassage[nCntPassage].nCntTime++;
		
			//�J�����Ƃ̋��������߂�
			double length = pow((g_aPassage[nCntPassage].pos.x - pCamera->posV.x)*(g_aPassage[nCntPassage].pos.x - pCamera->posV.x)
				+ (g_aPassage[nCntPassage].pos.z - pCamera->posV.z)*(g_aPassage[nCntPassage].pos.z - pCamera->posV.z), 0.5);

			//float�^�ɕϊ�
			g_aPassage[nCntPassage].fLength = (float)length;

			if (g_aPassage[nCntPassage].nCntTime <= g_aPassage[nCntPassage].nActiontime)
			{
				if (g_aPassage[nCntPassage].nPattan == 0)
				{
					if (g_aPassage[nCntPassage].bChange == true)
					{
						// �E�ړ�
						g_aPassage[nCntPassage].move.x += sinf(D3DX_PI * 0.5f) * g_aPassage[nCntPassage].fSpeed;
						g_aPassage[nCntPassage].move.z += cosf(D3DX_PI * 0.5f) * g_aPassage[nCntPassage].fSpeed;
						g_aPassage[nCntPassage].rotDest.y = D3DX_PI * 0.5f;
					}
					else
					{
						// ���ړ�
						g_aPassage[nCntPassage].move.x += sinf(-D3DX_PI * 0.5f) * g_aPassage[nCntPassage].fSpeed;
						g_aPassage[nCntPassage].move.z += cosf(-D3DX_PI * 0.5f) * g_aPassage[nCntPassage].fSpeed;
					
						g_aPassage[nCntPassage].rotDest.y = -D3DX_PI * 0.5f;
					}
				}
				else
				{
					if (g_aPassage[nCntPassage].bChange == true)
					{
						// ���ړ�
						g_aPassage[nCntPassage].move.x += sinf(D3DX_PI) * g_aPassage[nCntPassage].fSpeed;
						g_aPassage[nCntPassage].move.z += cosf(D3DX_PI) * g_aPassage[nCntPassage].fSpeed;
						g_aPassage[nCntPassage].rotDest.y = D3DX_PI;
					}
					else
					{
						// ��ړ�
						g_aPassage[nCntPassage].move.x += sinf(0) * g_aPassage[nCntPassage].fSpeed;
						g_aPassage[nCntPassage].move.z += cosf(0) * g_aPassage[nCntPassage].fSpeed;
						g_aPassage[nCntPassage].rotDest.y = 0;
					}
				}
			}
			if (g_aPassage[nCntPassage].nCntTime >= g_aPassage[nCntPassage].nActiontime + 1 && g_aPassage[nCntPassage].nCntTime <= g_aPassage[nCntPassage].nActiontime + 120)
			{	// �~�܂鎞��
				g_aPassage[nCntPassage].move.x += 0.0f;
				g_aPassage[nCntPassage].move.z += 0.0f;


				if (g_aPassage[nCntPassage].nCntTime >= g_aPassage[nCntPassage].nActiontime + 120)
				{
					g_aPassage[nCntPassage].bChange = g_aPassage[nCntPassage].bChange ? false : true;			// �s���̐ؑ�
					g_aPassage[nCntPassage].nCntTime = 0;					// �J�E���g��������

				}

				g_aPassage[nCntPassage].fDestAngle = g_aPassage[nCntPassage].rotDest.y - g_aPassage[nCntPassage].rot.y;

				//�p�x�̐ݒ�
				if (g_aPassage[nCntPassage].fDestAngle > D3DX_PI)
				{
					g_aPassage[nCntPassage].fDestAngle -= D3DX_PI* 2.0f;
				}
				if (g_aPassage[nCntPassage].fDestAngle < -D3DX_PI)
				{
					g_aPassage[nCntPassage].fDestAngle += D3DX_PI* 2.0f;
				}

				g_aPassage[nCntPassage].rot.y += g_aPassage[nCntPassage].fDestAngle * 0.05f;

				if (g_aPassage[nCntPassage].rot.y > D3DX_PI)
				{
					g_aPassage[nCntPassage].rot.y -= D3DX_PI* 2.0f;
				}
				if (g_aPassage[nCntPassage].rot.y < -D3DX_PI)
				{
					g_aPassage[nCntPassage].rot.y += D3DX_PI* 2.0f;
				}
			}

			// ����
			g_aPassage[nCntPassage].move.x += (0.0f - g_aPassage[nCntPassage].move.x) * 0.15f;
			g_aPassage[nCntPassage].move.z += (0.0f - g_aPassage[nCntPassage].move.z) * 0.15f;

			// �ʒu�X�V
			g_aPassage[nCntPassage].pos += g_aPassage[nCntPassage].move;

			SetPositionShadow(g_aPassage[nCntPassage].nIdxShadow, D3DXVECTOR3(g_aPassage[nCntPassage].pos.x, 0.1f, g_aPassage[nCntPassage].pos.z), 20.0f);


		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPassage(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;						//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;							//�}�e���A���f�[�^�ւ̃|�C���^

	for (int nCntPassage = 0; nCntPassage < MAX_PASSAGE; nCntPassage++)
	{
		if (g_aPassage[nCntPassage].bUse == true)	//���f�����g�p����Ă���
		{
			if (g_aPassage[nCntPassage].fLength < 2500)
			{//���f���ƃv���C���[�̋����ŕ`�悷�邩���߂�
			// ���[���h�}�g���b�N�X�̏�����
				D3DXMatrixIdentity(&g_aPassage[nCntPassage].mtxWorld);
				// ��]�𔽉f
				D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aPassage[nCntPassage].rot.y, g_aPassage[nCntPassage].rot.x, g_aPassage[nCntPassage].rot.z);
				D3DXMatrixMultiply(&g_aPassage[nCntPassage].mtxWorld, &g_aPassage[nCntPassage].mtxWorld, &mtxRot);
				// �ʒu�𔽉f
				D3DXMatrixTranslation(&mtxTrans, g_aPassage[nCntPassage].pos.x, g_aPassage[nCntPassage].pos.y, g_aPassage[nCntPassage].pos.z);
				D3DXMatrixMultiply(&g_aPassage[nCntPassage].mtxWorld, &g_aPassage[nCntPassage].mtxWorld, &mtxTrans);
				// ���[���h�}�g���b�N�X�̐ݒ�
				pDevice->SetTransform(D3DTS_WORLD, &g_aPassage[nCntPassage].mtxWorld);
				// ���݂̃}�e���A�����擾
				pDevice->GetMaterial(&matDef);


				// �}�e���A���f�[�^�ւ̃|�C���^���擾
				pMat = (D3DXMATERIAL*)g_pBuffMatPassage[g_aPassage[nCntPassage].nType]->GetBufferPointer();

				for (int nCntMat = 0; nCntMat < (int)g_nNumMatPassage[g_aPassage[nCntPassage].nType]; nCntMat++)
				{	// �}�e���A���̐ݒ�
					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
					// �e�N�X�`��

					pDevice->SetTexture(0, NULL);

					// ���f��(�p�[�c)�̕`��
					g_pMeshPassage[g_aPassage[nCntPassage].nType]->DrawSubset(nCntMat);

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
PASSAGE *GetPassage(void)
{
	return &g_aPassage[0];
}
//*****************************************************************************
//�ʍs�l�Ƃ̓����蔻�菈��
//*****************************************************************************
bool CollisionPassage(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 VtxMax, D3DXVECTOR3 VtxMin)
{
	bool bLand = false;

	GAMESTATE GameState;
	GameState = GetGameState();

	for (int nCntPassage = 0; nCntPassage < MAX_PASSAGE; nCntPassage++)
	{
		if (g_aPassage[nCntPassage].bUse == true)
		{
#if 1
			//���f����Y���̒�
			if (pPos->y < g_aPassage[nCntPassage].pos.y + g_aPassageVtx[g_aPassage[nCntPassage].nType].VtxMaxEnemy.y
				&& pPos->y > g_aPassage[nCntPassage].pos.y + g_aPassageVtx[g_aPassage[nCntPassage].nType].VtxMinEnemy.y)
			{
				//���f����Z���̒�
				if (pPos->z + VtxMin.z < g_aPassage[nCntPassage].pos.z + g_aPassageVtx[g_aPassage[nCntPassage].nType].VtxMaxEnemy.z
					&& pPos->z + VtxMax.z > g_aPassage[nCntPassage].pos.z + g_aPassageVtx[g_aPassage[nCntPassage].nType].VtxMinEnemy.z)
				{
					//���f����X���̒�
					if (pPos->x + VtxMin.x < g_aPassage[nCntPassage].pos.x + g_aPassageVtx[g_aPassage[nCntPassage].nType].VtxMaxEnemy.x
						&& pPos->x + VtxMax.x > g_aPassage[nCntPassage].pos.x + g_aPassageVtx[g_aPassage[nCntPassage].nType].VtxMinEnemy.x)
					{
#if 1
							//X���̓����蔻��
							if (pPosOld->x + 1 > g_aPassage[nCntPassage].pos.x + g_aPassageVtx[g_aPassage[nCntPassage].nType].VtxMaxEnemy.x)
							{
								pPos->x = g_aPassage[nCntPassage].pos.x + g_aPassageVtx[g_aPassage[nCntPassage].nType].VtxMaxEnemy.x + VtxMax.x;
								pPosOld->x = g_aPassage[nCntPassage].pos.x + g_aPassageVtx[g_aPassage[nCntPassage].nType].VtxMaxEnemy.x + VtxMax.x;
								bLand = true;
							}
							else if (pPosOld->x - 1 < g_aPassage[nCntPassage].pos.x + g_aPassageVtx[g_aPassage[nCntPassage].nType].VtxMinEnemy.x)
							{
								pPos->x = g_aPassage[nCntPassage].pos.x + g_aPassageVtx[g_aPassage[nCntPassage].nType].VtxMinEnemy.x + VtxMin.x;
								pPosOld->x = g_aPassage[nCntPassage].pos.x + g_aPassageVtx[g_aPassage[nCntPassage].nType].VtxMinEnemy.x + VtxMin.x;
								bLand = true;
							}

							//Z���̓����蔻��
							else if (pPosOld->z + 1 > g_aPassage[nCntPassage].pos.z + g_aPassageVtx[g_aPassage[nCntPassage].nType].VtxMaxEnemy.z)
							{
								pPos->z = g_aPassage[nCntPassage].pos.z + g_aPassageVtx[g_aPassage[nCntPassage].nType].VtxMaxEnemy.z + VtxMax.z;
								pPosOld->z = g_aPassage[nCntPassage].pos.z + g_aPassageVtx[g_aPassage[nCntPassage].nType].VtxMaxEnemy.z + VtxMax.z;
								bLand = true;
							}
							else if (pPosOld->z - 1 < g_aPassage[nCntPassage].pos.z + g_aPassageVtx[g_aPassage[nCntPassage].nType].VtxMinEnemy.z)
							{
								pPos->z = g_aPassage[nCntPassage].pos.z + g_aPassageVtx[g_aPassage[nCntPassage].nType].VtxMinEnemy.z + VtxMin.z;
								pPosOld->z = g_aPassage[nCntPassage].pos.z + g_aPassageVtx[g_aPassage[nCntPassage].nType].VtxMinEnemy.z + VtxMin.z;
								bLand = true;
							}
							//Y���̓����蔻��
							else if (pPosOld->y >= g_aPassage[nCntPassage].pos.y + g_aPassageVtx[g_aPassage[nCntPassage].nType].VtxMaxEnemy.y)
							{
								pPos->y = g_aPassage[nCntPassage].pos.y + g_aPassageVtx[g_aPassage[nCntPassage].nType].VtxMaxEnemy.y;
								pPosOld->y = g_aPassage[nCntPassage].pos.y + g_aPassageVtx[g_aPassage[nCntPassage].nType].VtxMaxEnemy.y;
								bLand = true;
							}
							else if (pPosOld->y <= g_aPassage[nCntPassage].pos.y + g_aPassageVtx[g_aPassage[nCntPassage].nType].VtxMinEnemy.y)
							{
								pPos->y = g_aPassage[nCntPassage].pos.y + g_aPassageVtx[g_aPassage[nCntPassage].nType].VtxMinEnemy.y;
								pPosOld->y = g_aPassage[nCntPassage].pos.y + g_aPassageVtx[g_aPassage[nCntPassage].nType].VtxMinEnemy.y;
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
void SetPassage(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType, int nPattan, int nActiontime, float fSpeed, bool bChange)
{
	int nNumVtex;	//���_��
	DWORD sizeFvF;	//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff[MAX_PASSAGE];	//���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 vtx[MAX_PASSAGE];

	for (int nCntPassage = 0; nCntPassage < MAX_PASSAGE; nCntPassage++)
	{
		if (g_aPassage[nCntPassage].bUse == false)
		{
#if 1

			//for (int nCntTypeEnemy = 0; nCntTypeEnemy < MAX_ENEMY_TYPE; nCntTypeEnemy++)
			//{
				//���_�����擾
				nNumVtex = g_pMeshPassage[nType]->GetNumVertices();
				//���_�t�H�[�}�b�g�̃T�C�Y���擾
				sizeFvF = D3DXGetFVFVertexSize(g_pMeshPassage[nType]->GetFVF());
			//	for (int nCntPassage = 0; nCntPassage < MAX_ENEMY; nCntPassage++)
				//{
					//���_�@���b�N
					g_pMeshPassage[nType]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff[nType]);
					for (int nCntVtx = 0; nCntVtx < nNumVtex; nCntVtx++)
					{	//���_���W�̑��
						D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff[nType];
						if (g_aPassage[nCntPassage].VtxMinEnemy.x > vtx.x)
						{
							g_aPassage[nCntPassage].VtxMinEnemy.x = vtx.x;
						}
						if (g_aPassage[nCntPassage].VtxMinEnemy.y > vtx.y)
						{
							g_aPassage[nCntPassage].VtxMinEnemy.y = vtx.y;
						}
						if (g_aPassage[nCntPassage].VtxMinEnemy.z > vtx.z)
						{
							g_aPassage[nCntPassage].VtxMinEnemy.z = vtx.z;
						}

						if (g_aPassage[nCntPassage].VtxMaxEnemy.x < vtx.x)
						{
							g_aPassage[nCntPassage].VtxMaxEnemy.x = vtx.x;
						}
						if (g_aPassage[nCntPassage].VtxMaxEnemy.y < vtx.y)
						{
							g_aPassage[nCntPassage].VtxMaxEnemy.y = vtx.y;
						}
						if (g_aPassage[nCntPassage].VtxMaxEnemy.z < vtx.z)
						{
							g_aPassage[nCntPassage].VtxMaxEnemy.z = vtx.z;
						}
						pVtxBuff[nCntPassage] += sizeFvF;
					}
					//			//���_�o�b�t�@���A�����b�N
					g_pMeshPassage[nType]->UnlockVertexBuffer();
				//}
			//}
			// �ʒu�E�����̏����ݒ�
#endif
			g_aPassage[nCntPassage].pos = pos;
			g_aPassage[nCntPassage].rot = rot;
			g_aPassage[nCntPassage].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aPassage[nCntPassage].fShadow = 6;
			g_aPassage[nCntPassage].nType = nType;
			g_aPassage[nCntPassage].nActiontime = nActiontime;		// �s������
			g_aPassage[nCntPassage].nCntTime = 0;
			g_aPassage[nCntPassage].nPattan = nPattan;			// �s���p�^�[��( 0 : ���ړ� / 1 :�c�ړ�)
			g_aPassage[nCntPassage].bChange = bChange;			// �s���̕ω��̑��(�X�V�ŕω�)
			g_aPassage[nCntPassage].fSpeed = fSpeed;
			//�@�e�̃Z�b�g
			g_aPassage[nCntPassage].nIdxShadow = SetShadow(D3DXVECTOR3(g_aPassage[nCntPassage].pos.x, g_aPassage[nCntPassage].pos.y + 0.1f, g_aPassage[nCntPassage].pos.z), D3DXVECTOR3(0, 0, 0), 20.0f);
			g_aPassage[nCntPassage].bUse = true;
			break;
		}
	}
}
