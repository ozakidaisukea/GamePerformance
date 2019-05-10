//=============================================================================
//
// �G���� [enemy.cpp]
// Author : Meguro Mikiya
//
//=============================================================================
#include "enemy.h"
#include "input.h"
#include "shadow.h"
#include "camera.h"
#include "bullet.h"
#include "polygon.h"
#include "player.h"
#include "game.h"
#include "explosion.h"
#include "sound.h"
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPD3DXMESH g_pMeshEnemy[MAX_ENEMY_TYPE];						//���b�V�����ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatEnemy[MAX_ENEMY_TYPE];				//�}�e���A�����ւ̃|�C���^
LPDIRECT3DTEXTURE9	g_pTextureEnemy[MAX_ENEMY_TYPE];			//�e�N�X�`���ւ̃|�C���^
DWORD g_nNumMatEnemy[MAX_ENEMY_TYPE] = {};					//�}�e���A�����̐�
ENEMY g_aEnemy[MAX_ENEMY];
VTX g_aEnemyVtx[MAX_ENEMY_TYPE];
//=============================================================================
// ����������
//=============================================================================
void InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(ENEMY_NAME000,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatEnemy[0],
		NULL,
		&g_nNumMatEnemy[0],
		&g_pMeshEnemy[0]);

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(ENEMY_NAME001,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatEnemy[1],
		NULL,
		&g_nNumMatEnemy[1],
		&g_pMeshEnemy[1]);
	
	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(ENEMY_NAME002,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatEnemy[2],
		NULL,
		&g_nNumMatEnemy[2],
		&g_pMeshEnemy[2]);

	int nNumVtex;	//���_��
	DWORD sizeFvF;	//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff[MAX_ENEMY];	//���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 vtx[MAX_ENEMY];
	
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{//�G�̏�����
		g_aEnemy[nCntEnemy].VtxMinEnemy = D3DXVECTOR3(10000, 0, 10000);
		g_aEnemy[nCntEnemy].VtxMaxEnemy = D3DXVECTOR3(-10000, 0, -10000);
		g_aEnemy[nCntEnemy].nType = 0;
		g_aEnemy[nCntEnemy].bUse = false;

	}	
	for (int nCntTypeEnemy = 0; nCntTypeEnemy < MAX_ENEMY_TYPE; nCntTypeEnemy++)
	{//�����蔻��̏�����
		g_aEnemyVtx[nCntTypeEnemy].VtxMaxEnemy = D3DXVECTOR3(-10000, 0, -10000);
		g_aEnemyVtx[nCntTypeEnemy].VtxMinEnemy = D3DXVECTOR3(10000, 0, 10000);
	}

	for (int nCntTypeEnemy = 0; nCntTypeEnemy < MAX_ENEMY_TYPE; nCntTypeEnemy++)
	{
		//���_�����擾
		nNumVtex = g_pMeshEnemy[nCntTypeEnemy]->GetNumVertices();
		//���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFvF = D3DXGetFVFVertexSize(g_pMeshEnemy[nCntTypeEnemy]->GetFVF());
		//���_�@���b�N
		g_pMeshEnemy[nCntTypeEnemy]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff[nCntTypeEnemy]);
		for (int nCntVtx = 0; nCntVtx < nNumVtex; nCntVtx++)
		{	//���_���W�̑��
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff[nCntTypeEnemy];
			if (g_aEnemyVtx[nCntTypeEnemy].VtxMinEnemy.x > vtx.x)
			{
				g_aEnemyVtx[nCntTypeEnemy].VtxMinEnemy.x = vtx.x;
			}
			if (g_aEnemyVtx[nCntTypeEnemy].VtxMinEnemy.y > vtx.y)
			{
				g_aEnemyVtx[nCntTypeEnemy].VtxMinEnemy.y = vtx.y;
			}
			if (g_aEnemyVtx[nCntTypeEnemy].VtxMinEnemy.z > vtx.z)
			{
				g_aEnemyVtx[nCntTypeEnemy].VtxMinEnemy.z = vtx.z;
			}

			if (g_aEnemyVtx[nCntTypeEnemy].VtxMaxEnemy.x < vtx.x)
			{
				g_aEnemyVtx[nCntTypeEnemy].VtxMaxEnemy.x = vtx.x;
			}
			if (g_aEnemyVtx[nCntTypeEnemy].VtxMaxEnemy.y < vtx.y)
			{
				g_aEnemyVtx[nCntTypeEnemy].VtxMaxEnemy.y = vtx.y;
			}
			if (g_aEnemyVtx[nCntTypeEnemy].VtxMaxEnemy.z < vtx.z)
			{
				g_aEnemyVtx[nCntTypeEnemy].VtxMaxEnemy.z = vtx.z;
			}
			pVtxBuff[nCntTypeEnemy] += sizeFvF;
		}
		//			//���_�o�b�t�@���A�����b�N
		g_pMeshEnemy[nCntTypeEnemy]->UnlockVertexBuffer();
	}


	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		ENEMY_NAME000,
		&g_pTextureEnemy[0]);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		ENEMY_NAME000,
		&g_pTextureEnemy[1]);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		ENEMY_NAME000,
		&g_pTextureEnemy[2]);
}

//=============================================================================
// �I������
//=============================================================================
void UninitEnemy(void)
{
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY_TYPE; nCntEnemy++)
	{
		// ���b�V���̊J��
		if (g_pMeshEnemy[nCntEnemy] != NULL)
		{
			g_pMeshEnemy[nCntEnemy]->Release();
			g_pMeshEnemy[nCntEnemy] = NULL;
		}
		// �}�e���A���̊J��
		if (g_pBuffMatEnemy[nCntEnemy] != NULL)
		{
			g_pBuffMatEnemy[nCntEnemy]->Release();
			g_pBuffMatEnemy[nCntEnemy] = NULL;
		}
		//�e�N�X�`���̔j��
		if (g_pTextureEnemy[nCntEnemy] != NULL)
		{
			g_pTextureEnemy[nCntEnemy]->Release();
			g_pTextureEnemy[nCntEnemy] = NULL;
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEnemy(void)
{
	for (int nCnt = 0; nCnt < MAX_ENEMY; nCnt++)
	{
		if (g_aEnemy[nCnt].bUse == true)
		{
			if (g_aEnemy[nCnt].nType == 1)
			{
				//���f���̈ړ�	���f���̈ړ�����p�x(�G�̌��� + �p�x) * �ړ���
				g_aEnemy[nCnt].move.x -= sinf(g_aEnemy[nCnt].rot.y) * MOVE_ENEMY / 2;
				g_aEnemy[nCnt].move.z -= cosf(g_aEnemy[nCnt].rot.y) * MOVE_ENEMY / 2;
				g_aEnemy[nCnt].fDestAngle = (g_aEnemy[nCnt].rot.y + D3DX_PI * 0.0f);

				//��]�̑傫��(�������قǑ傫��)
				g_aEnemy[nCnt].rot.y += 0.015f;
			}
			else if (g_aEnemy[nCnt].nType == 0)
			{
				//g_aEnemy[nCnt].fDestAngle = (g_aEnemy[nCnt].rot.y + D3DX_PI * 0.0f);
				//g_aEnemy[nCnt].rot.y += 0.2f;

			}
			else if (g_aEnemy[nCnt].nType == 2)
			{
				//g_aEnemy[nCnt].fDestAngle = (g_aEnemy[nCnt].rot.y + D3DX_PI * 0.0f);
				//g_aEnemy[nCnt].rot.y += 0.02f;
			}

			//�����̊���
			g_aEnemy[nCnt].fDiffAngle = g_aEnemy[nCnt].fDestAngle - g_aEnemy[nCnt].rot.y;
			//�p�x�̐ݒ�
			if (g_aEnemy[nCnt].fDiffAngle > D3DX_PI)
			{
				g_aEnemy[nCnt].fDiffAngle -= D3DX_PI* 2.0f;
			}
			if (g_aEnemy[nCnt].fDiffAngle < -D3DX_PI)
			{
				g_aEnemy[nCnt].fDiffAngle += D3DX_PI* 2.0f;
			}
			g_aEnemy[nCnt].rot.y += g_aEnemy[nCnt].fDiffAngle * 0.1f;

			if (g_aEnemy[nCnt].rot.y > D3DX_PI)
			{
				g_aEnemy[nCnt].rot.y -= D3DX_PI* 2.0f;
			}
			if (g_aEnemy[nCnt].rot.y < -D3DX_PI)
			{
				g_aEnemy[nCnt].rot.y += D3DX_PI* 2.0f;
			}
			if (g_aEnemy[nCnt].rot.x > D3DX_PI)
			{
				g_aEnemy[nCnt].rot.x -= D3DX_PI* 2.0f;
			}
			if (g_aEnemy[nCnt].rot.x < -D3DX_PI)
			{
				g_aEnemy[nCnt].rot.x += D3DX_PI* 2.0f;
			}

			g_aEnemy[nCnt].pos += g_aEnemy[nCnt].move;
			//����
			g_aEnemy[nCnt].move.x += (0.0f - g_aEnemy[nCnt].move.x) * 0.05f;
			g_aEnemy[nCnt].move.z += (0.0f - g_aEnemy[nCnt].move.z) * 0.05f;
			g_aEnemy[nCnt].move.y += (0.0f - g_aEnemy[nCnt].move.y) * 0.05f;
			//���f���Ƃ̓����蔻��
			if (CollisionModel(&g_aEnemy[nCnt].pos, &g_aEnemy[nCnt].posold, &g_aEnemy[nCnt].move,
				g_aEnemyVtx[g_aEnemy[nCnt].nType].VtxMaxEnemy, g_aEnemyVtx[g_aEnemy[nCnt].nType].VtxMinEnemy) == true)
			{

			}
			SetPositionShadow(g_aEnemy[nCnt].nIdxShadow, D3DXVECTOR3(g_aEnemy[nCnt].pos.x, 0.1f, g_aEnemy[nCnt].pos.z), 15);
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;						//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;							//�}�e���A���f�[�^�ւ̃|�C���^

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)	//�G���g�p����Ă���
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aEnemy[nCntEnemy].mtxWorld);
			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aEnemy[nCntEnemy].rot.y, g_aEnemy[nCntEnemy].rot.x, g_aEnemy[nCntEnemy].rot.z);
			D3DXMatrixMultiply(&g_aEnemy[nCntEnemy].mtxWorld, &g_aEnemy[nCntEnemy].mtxWorld, &mtxRot);
			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aEnemy[nCntEnemy].pos.x, g_aEnemy[nCntEnemy].pos.y, g_aEnemy[nCntEnemy].pos.z);
			D3DXMatrixMultiply(&g_aEnemy[nCntEnemy].mtxWorld, &g_aEnemy[nCntEnemy].mtxWorld, &mtxTrans);
			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aEnemy[nCntEnemy].mtxWorld);
			// ���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			// �}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_pBuffMatEnemy[g_aEnemy[nCntEnemy].nType]->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_nNumMatEnemy[g_aEnemy[nCntEnemy].nType]; nCntMat++)
			{	// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
				// �e�N�X�`��
				pDevice->SetTexture(0, g_pTextureEnemy[0]);
				// �G(�p�[�c)�̕`��
				g_pMeshEnemy[g_aEnemy[nCntEnemy].nType]->DrawSubset(nCntMat);
			}
			// �}�e���A�����f�t�H���g�ɖ߂�
			pDevice->SetMaterial(&matDef);
		}
	}
}
//*****************************************************************************
//�G�|�C���^����
//*****************************************************************************
ENEMY *GetEnemy(void)
{
	return &g_aEnemy[0];
}
//*****************************************************************************
//�G�Ƃ̓����蔻�菈��
//*****************************************************************************
bool CollisionEnemy(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 VtxMax, D3DXVECTOR3 VtxMin)
{
	bool bLand = false;

	GAMESTATE GameState;
	GameState = GetGameState();
	PLAYER *pPlayer;
	pPlayer = GetPlayer();

	D3DXVECTOR3 VecA(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 VecB(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 VecC(0.0f, 0.0f, 0.0f);

	/*VecA = *pPosOld - *pPos;
	VecB = ;*/

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{
#if 1
			//�G��Y���̒�
			if (pPos->y + VtxMin.y < g_aEnemy[nCntEnemy].pos.y + g_aEnemyVtx[g_aEnemy[nCntEnemy].nType].VtxMaxEnemy.y
				&& pPos->y + VtxMax.y > g_aEnemy[nCntEnemy].pos.y + g_aEnemyVtx[g_aEnemy[nCntEnemy].nType].VtxMinEnemy.y)
			{
				//�G��Z���̒�
				if (pPos->z + VtxMin.z < g_aEnemy[nCntEnemy].pos.z + g_aEnemyVtx[g_aEnemy[nCntEnemy].nType].VtxMaxEnemy.z
					&& pPos->z + VtxMax.z > g_aEnemy[nCntEnemy].pos.z + g_aEnemyVtx[g_aEnemy[nCntEnemy].nType].VtxMinEnemy.z)
				{
					//�G��X���̒�
					if (pPos->x + VtxMin.x < g_aEnemy[nCntEnemy].pos.x + g_aEnemyVtx[g_aEnemy[nCntEnemy].nType].VtxMaxEnemy.x
						&& pPos->x + VtxMax.x > g_aEnemy[nCntEnemy].pos.x + g_aEnemyVtx[g_aEnemy[nCntEnemy].nType].VtxMinEnemy.x)
					{
#if 1
						//X���̓����蔻��
						if (pPosOld->x + 1 > g_aEnemy[nCntEnemy].pos.x + g_aEnemyVtx[g_aEnemy[nCntEnemy].nType].VtxMaxEnemy.x)
						{
							pPos->x = g_aEnemy[nCntEnemy].pos.x + g_aEnemyVtx[g_aEnemy[nCntEnemy].nType].VtxMaxEnemy.x + VtxMax.x;
							pPosOld->x = g_aEnemy[nCntEnemy].pos.x + g_aEnemyVtx[g_aEnemy[nCntEnemy].nType].VtxMaxEnemy.x + VtxMax.x;
							if (g_aEnemy[nCntEnemy].nType == 1)
							{//�g�Q�ɓ�������
								pMove->x = 5.0f;
							
							}

							bLand = true;
						}
						else if (pPosOld->x - 1 < g_aEnemy[nCntEnemy].pos.x + g_aEnemyVtx[g_aEnemy[nCntEnemy].nType].VtxMinEnemy.x)
						{
							pPos->x = g_aEnemy[nCntEnemy].pos.x + g_aEnemyVtx[g_aEnemy[nCntEnemy].nType].VtxMinEnemy.x + VtxMin.x;
							pPosOld->x = g_aEnemy[nCntEnemy].pos.x + g_aEnemyVtx[g_aEnemy[nCntEnemy].nType].VtxMinEnemy.x + VtxMin.x;
							if (g_aEnemy[nCntEnemy].nType == 1)
							{//�g�Q�ɓ�������
								pMove->x = -5.0f;
							
							}
							bLand = true;
						}
						//Z���̓����蔻��
						else if (pPosOld->z + 1 > g_aEnemy[nCntEnemy].pos.z + g_aEnemyVtx[g_aEnemy[nCntEnemy].nType].VtxMaxEnemy.z)
						{
							pPos->z = g_aEnemy[nCntEnemy].pos.z + g_aEnemyVtx[g_aEnemy[nCntEnemy].nType].VtxMaxEnemy.z + VtxMax.z;
							pPosOld->z = g_aEnemy[nCntEnemy].pos.z + g_aEnemyVtx[g_aEnemy[nCntEnemy].nType].VtxMaxEnemy.z + VtxMax.z;
							if (g_aEnemy[nCntEnemy].nType == 1)
							{//�g�Q�ɓ�������
								pMove->z = 10.0f;
							
							}
							bLand = true;
						}
						else if (pPosOld->z - 1 < g_aEnemy[nCntEnemy].pos.z + g_aEnemyVtx[g_aEnemy[nCntEnemy].nType].VtxMinEnemy.z)
						{						
							if (g_aEnemy[nCntEnemy].nType == 1)
							{//�g�Q�ɓ�������
								pMove->z = - 10.0f;
							
							}
							else
							{
								pPos->z = g_aEnemy[nCntEnemy].pos.z + g_aEnemyVtx[g_aEnemy[nCntEnemy].nType].VtxMinEnemy.z + VtxMin.z;
								pPosOld->z = g_aEnemy[nCntEnemy].pos.z + g_aEnemyVtx[g_aEnemy[nCntEnemy].nType].VtxMinEnemy.z + VtxMin.z;
							}
							bLand = true;
						}
						//Y���̓����蔻��
						else if (pPosOld->y >= g_aEnemy[nCntEnemy].pos.y + g_aEnemyVtx[g_aEnemy[nCntEnemy].nType].VtxMaxEnemy.y)
						{
							pPos->y = g_aEnemy[nCntEnemy].pos.y + g_aEnemyVtx[g_aEnemy[nCntEnemy].nType].VtxMaxEnemy.y;
							pPosOld->y = g_aEnemy[nCntEnemy].pos.y + g_aEnemyVtx[g_aEnemy[nCntEnemy].nType].VtxMaxEnemy.y;
							bLand = true;
						}
						else if (pPosOld->y <= g_aEnemy[nCntEnemy].pos.y + g_aEnemyVtx[g_aEnemy[nCntEnemy].nType].VtxMinEnemy.y)
						{
							pPos->y = g_aEnemy[nCntEnemy].pos.y + g_aEnemyVtx[g_aEnemy[nCntEnemy].nType].VtxMinEnemy.y;
							pPosOld->y = g_aEnemy[nCntEnemy].pos.y + g_aEnemyVtx[g_aEnemy[nCntEnemy].nType].VtxMinEnemy.y;
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
// �e�̐ݒ菈��
//=============================================================================
void SetEnemy(D3DXVECTOR3 pos, int nType)
{

	//int nNumVtex;	//���_��
	//DWORD sizeFvF[MAX_ENEMY];	//���_�t�H�[�}�b�g�̃T�C�Y
	//BYTE *pVtxBuff[MAX_ENEMY];	//���_�o�b�t�@�ւ̃|�C���^
	//D3DXVECTOR3 vtx[MAX_ENEMY];

	////���_�����擾
	//nNumVtex = g_pMeshEnemy[nType]->GetNumVertices();
	////���_�t�H�[�}�b�g�̃T�C�Y���擾
	//sizeFvF[nType] = D3DXGetFVFVertexSize(g_pMeshEnemy[nType]->GetFVF());

	//for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	//{
	//	if (g_aEnemy[nCntEnemy].bUse == false)
	//	{
	//		//���_�@���b�N
	//		g_pMeshEnemy[nType]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff[nType]);
	//		for (int nCntVtx = 0; nCntVtx < nNumVtex; nCntVtx++)
	//		{	//���_���W�̑��
	//			vtx[nCntEnemy] = *(D3DXVECTOR3*)pVtxBuff[nType];
	//			if (g_aEnemy[nCntEnemy].VtxMinEnemy.x > vtx[nCntEnemy].x)
	//			{
	//				g_aEnemy[nCntEnemy].VtxMinEnemy.x = vtx[nCntEnemy].x;
	//			}
	//			if (g_aEnemy[nCntEnemy].VtxMinEnemy.y > vtx[nCntEnemy].y)
	//			{
	//				g_aEnemy[nCntEnemy].VtxMinEnemy.y = vtx[nCntEnemy].y;
	//			}
	//			if (g_aEnemy[nCntEnemy].VtxMinEnemy.z > vtx[nCntEnemy].z)
	//			{
	//				g_aEnemy[nCntEnemy].VtxMinEnemy.z = vtx[nCntEnemy].z;
	//			}

	//			if (g_aEnemy[nCntEnemy].VtxMaxEnemy.x < vtx[nCntEnemy].x)
	//			{
	//				g_aEnemy[nCntEnemy].VtxMaxEnemy.x = vtx[nCntEnemy].x;
	//			}
	//			if (g_aEnemy[nCntEnemy].VtxMaxEnemy.y < vtx[nCntEnemy].y)
	//			{
	//				g_aEnemy[nCntEnemy].VtxMaxEnemy.y = vtx[nCntEnemy].y;
	//			}
	//			if (g_aEnemy[nCntEnemy].VtxMaxEnemy.z < vtx[nCntEnemy].z)
	//			{
	//				g_aEnemy[nCntEnemy].VtxMaxEnemy.z = vtx[nCntEnemy].z;
	//			}
	//			pVtxBuff[nCntEnemy] += sizeFvF[nType];
	//		}
	//		//���_�o�b�t�@���A�����b�N
	//		g_pMeshEnemy[nType]->UnlockVertexBuffer();
	//		break;
	//	}
	//}

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == false)
		{
			// �ʒu�E�����̏����ݒ�
			g_aEnemy[nCntEnemy].pos = pos;
			g_aEnemy[nCntEnemy].rot = D3DXVECTOR3(0, 0, 0);
			g_aEnemy[nCntEnemy].fShadow = 12;
			g_aEnemy[nCntEnemy].nType = nType;
			//�@�e�̃Z�b�g
			g_aEnemy[nCntEnemy].nIdxShadow = SetShadow(D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x, 0.1f, g_aEnemy[nCntEnemy].pos.z), D3DXVECTOR3(0, 0, 0), 30.0f);
			g_aEnemy[nCntEnemy].bUse = true;
			break;
		}
	}

}