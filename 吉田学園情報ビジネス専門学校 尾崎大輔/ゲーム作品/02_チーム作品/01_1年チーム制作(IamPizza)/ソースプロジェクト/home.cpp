//=============================================================================
//
// �z�[������ [home.cpp]
// Author : Meguro Mikiya
//
//=============================================================================
#include "home.h"
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
LPD3DXMESH g_pMeshHome[MAX_HOME];					//���b�V�����ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatHome[MAX_HOME];			//�}�e���A�����ւ̃|�C���^
LPDIRECT3DTEXTURE9	g_pTextureHome[MAX_HOME];		//�e�N�X�`���ւ̃|�C���^
DWORD g_nNumMatHome[MAX_HOME] = {};							//�}�e���A�����̐�
HOME g_aHome[MAX_HOME];
D3DXMATERIAL *g_pMatHome;
//=============================================================================
// ����������
//=============================================================================
void InitHome(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(HOME_NAME000,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatHome[0],
		NULL,
		&g_nNumMatHome[0],
		&g_pMeshHome[0]);



	int nNumVtex;	//���_��
	DWORD sizeFvF;	//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff[MAX_HOME];	//���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 vtx[MAX_HOME];

	for (int nCntHome = 0; nCntHome < MAX_HOME; nCntHome++)
	{
		g_aHome[nCntHome].VtxMinHome = D3DXVECTOR3(10000, 0, 10000);
		g_aHome[nCntHome].VtxMaxHome = D3DXVECTOR3(-10000, 0, -10000);
		g_aHome[nCntHome].nType = 0;
		g_aHome[nCntHome].bUse = false;
	}

	//���_�����擾
	nNumVtex = g_pMeshHome[0]->GetNumVertices();
	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	sizeFvF = D3DXGetFVFVertexSize(g_pMeshHome[0]->GetFVF());

	for (int nCntHome = 0; nCntHome < MAX_HOME; nCntHome++)
	{
		//���_�@���b�N
		g_pMeshHome[0]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff[nCntHome]);
		for (int nCntVtx = 0; nCntVtx < nNumVtex; nCntVtx++)
		{	//���_���W�̑��
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff[nCntHome];
			if (g_aHome[nCntHome].VtxMinHome.x > vtx.x)
			{
				g_aHome[nCntHome].VtxMinHome.x = vtx.x;
			}
			if (g_aHome[nCntHome].VtxMinHome.y > vtx.y)
			{
				g_aHome[nCntHome].VtxMinHome.y = vtx.y;
			}
			if (g_aHome[nCntHome].VtxMinHome.z > vtx.z)
			{
				g_aHome[nCntHome].VtxMinHome.z = vtx.z;
			}

			if (g_aHome[nCntHome].VtxMaxHome.x < vtx.x)
			{
				g_aHome[nCntHome].VtxMaxHome.x = vtx.x;
			}
			if (g_aHome[nCntHome].VtxMaxHome.y < vtx.y)
			{
				g_aHome[nCntHome].VtxMaxHome.y = vtx.y;
			}
			if (g_aHome[nCntHome].VtxMaxHome.z < vtx.z)
			{
				g_aHome[nCntHome].VtxMaxHome.z = vtx.z;
			}
			//��������

			pVtxBuff[nCntHome] += sizeFvF;
		}
		//			//���_�o�b�t�@���A�����b�N
		g_pMeshHome[0]->UnlockVertexBuffer();
	}
	
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		HOME_NAME000,
		&g_pTextureHome[0]);

	for (int nCntHome = 0; nCntHome < MAX_HOME; nCntHome++)
	{
		for (int nCntMat = 0; nCntMat < (int)g_nNumMatHome[nCntHome]; nCntMat++)
		{
			// �}�e���A���f�[�^�ւ̃|�C���^���擾
			g_pMatHome = (D3DXMATERIAL*)g_pBuffMatHome[g_aHome[nCntHome].nType]->GetBufferPointer();
			{
				D3DXCreateTextureFromFile(pDevice,
					g_pMatHome[nCntMat].pTextureFilename,
					&g_pTextureHome[g_aHome[nCntHome].nType]);
			}
		}
	}
}

//=============================================================================
// �I������
//=============================================================================
void UninitHome(void)
{
	for (int nCntHome = 0; nCntHome < MAX_HOME; nCntHome++)
	{
		// ���b�V���̊J��
		if (g_pMeshHome[nCntHome] != NULL)
		{
			g_pMeshHome[nCntHome]->Release();
			g_pMeshHome[nCntHome] = NULL;
		}
		// �}�e���A���̊J��
		if (g_pBuffMatHome[nCntHome] != NULL)
		{
			g_pBuffMatHome[nCntHome]->Release();
			g_pBuffMatHome[nCntHome] = NULL;
		}
		//�e�N�X�`���̔j��
		if (g_pTextureHome[nCntHome] != NULL)
		{
			g_pTextureHome[nCntHome]->Release();
			g_pTextureHome[nCntHome] = NULL;
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateHome(void)
{
	
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawHome(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;						//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;							//�}�e���A���f�[�^�ւ̃|�C���^

	for (int nCntHome = 0; nCntHome < MAX_HOME; nCntHome++)
	{		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_aHome[nCntHome].mtxWorld);
		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aHome[nCntHome].rot.y, g_aHome[nCntHome].rot.x, g_aHome[nCntHome].rot.z);
		D3DXMatrixMultiply(&g_aHome[nCntHome].mtxWorld, &g_aHome[nCntHome].mtxWorld, &mtxRot);
		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_aHome[nCntHome].pos.x, g_aHome[nCntHome].pos.y, g_aHome[nCntHome].pos.z);
		D3DXMatrixMultiply(&g_aHome[nCntHome].mtxWorld, &g_aHome[nCntHome].mtxWorld, &mtxTrans);
		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_aHome[nCntHome].mtxWorld);
		// ���݂̃}�e���A�����擾
		pDevice->GetMaterial(&matDef);
		
		
		// �}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)g_pBuffMatHome[g_aHome[nCntHome].nType]->GetBufferPointer();
 
		for (int nCntMat = 0; nCntMat < (int)g_nNumMatHome[nCntHome]; nCntMat++)
		{	// �}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
			// �e�N�X�`��
			pDevice->SetTexture(0, g_pTextureHome[g_aHome[nCntHome].nType]);		  
		 	if (g_aHome[nCntHome].bUse == true)	//�z�[�����g�p����Ă���
			{	// �z�[��(�p�[�c)�̕`��
				g_pMeshHome[g_aHome[nCntHome].nType]->DrawSubset(nCntMat);
			}
		}
		// �}�e���A�����f�t�H���g�ɖ߂�
		pDevice->SetMaterial(&matDef);
	}
}

//*****************************************************************************
//�z�[���|�C���^����
//*****************************************************************************
HOME *GetHome(void)
{
	return &g_aHome[0];
}
//*****************************************************************************
//�z�[���Ƃ̓����蔻�菈��
//*****************************************************************************
bool CollisionHome(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 VtxMax, D3DXVECTOR3 VtxMin/*, HOME **pHome*/)
{
	bool bLand = false;

	GAMESTATE GameState;
	GameState = GetGameState();

	for (int nCntHome = 0; nCntHome < MAX_HOME; nCntHome++)
	{
		if (g_aHome[nCntHome].bUse == true)
		{
#if 1
			//�z�[����Y���̒�
			if (pPos->y < g_aHome[nCntHome].pos.y + g_aHome[nCntHome].VtxMaxHome.y
				&& pPos->y > g_aHome[nCntHome].pos.y + g_aHome[nCntHome].VtxMinHome.y)
			{
				//�z�[����Z���̒�
				if (pPos->z + VtxMin.z < g_aHome[nCntHome].pos.z + g_aHome[nCntHome].VtxMaxHome.z
					&& pPos->z + VtxMax.z > g_aHome[nCntHome].pos.z + g_aHome[nCntHome].VtxMinHome.z)
				{
					//�z�[����X���̒�
					if (pPos->x + VtxMin.x < g_aHome[nCntHome].pos.x + g_aHome[nCntHome].VtxMaxHome.x
						&& pPos->x + VtxMax.x > g_aHome[nCntHome].pos.x + g_aHome[nCntHome].VtxMinHome.x)
					{

						//X���̓����蔻��
						if (pPosOld->x + 1 > g_aHome[nCntHome].pos.x + g_aHome[nCntHome].VtxMaxHome.x)
						{
							bLand = true;
						}
						else if (pPosOld->x - 1 < g_aHome[nCntHome].pos.x + g_aHome[nCntHome].VtxMinHome.x)
						{
							bLand = true;
						}
						//Z���̓����蔻��
						if (pPosOld->z + 1 > g_aHome[nCntHome].pos.z + g_aHome[nCntHome].VtxMaxHome.z)
						{
							bLand = true;
						}
						else if (pPosOld->z - 1 < g_aHome[nCntHome].pos.z + g_aHome[nCntHome].VtxMinHome.z)
						{
							bLand = true;
						}
						//Y���̓����蔻��
						if (pPosOld->y >= g_aHome[nCntHome].pos.y + g_aHome[nCntHome].VtxMaxHome.y)
						{
						}
						else if (pPosOld->y <= g_aHome[nCntHome].pos.y + g_aHome[nCntHome].VtxMinHome.y)
						{
						}
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
void SetHome(D3DXVECTOR3 pos, int nType)
{

	int nNumVtex;	//���_��
	DWORD sizeFvF[MAX_HOME];	//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff[MAX_HOME];	//���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 vtx[MAX_HOME];

	//���_�����擾
	nNumVtex = g_pMeshHome[nType]->GetNumVertices();
	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	sizeFvF[nType] = D3DXGetFVFVertexSize(g_pMeshHome[nType]->GetFVF());

	for (int nCntHome = 0; nCntHome < MAX_HOME; nCntHome++)
	{
		//if (g_aHome[nCntHome].bUse == false)
		//{
			//���_�@���b�N
			g_pMeshHome[nType]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff[nType]);
			for (int nCntVtx = 0; nCntVtx < nNumVtex; nCntVtx++)
			{	//���_���W�̑��
				vtx[nCntHome] = *(D3DXVECTOR3*)pVtxBuff[nType];
				if (g_aHome[nCntHome].VtxMinHome.x > vtx[nCntHome].x)
				{
					g_aHome[nCntHome].VtxMinHome.x = vtx[nCntHome].x;
				}
				if (g_aHome[nCntHome].VtxMinHome.y > vtx[nCntHome].y)
				{
					g_aHome[nCntHome].VtxMinHome.y = vtx[nCntHome].y;
				}
				if (g_aHome[nCntHome].VtxMinHome.z > vtx[nCntHome].z)
				{
					g_aHome[nCntHome].VtxMinHome.z = vtx[nCntHome].z;
				}

				if (g_aHome[nCntHome].VtxMaxHome.x < vtx[nCntHome].x)
				{
					g_aHome[nCntHome].VtxMaxHome.x = vtx[nCntHome].x;
				}
				if (g_aHome[nCntHome].VtxMaxHome.y < vtx[nCntHome].y)
				{
					g_aHome[nCntHome].VtxMaxHome.y = vtx[nCntHome].y;
				}
				if (g_aHome[nCntHome].VtxMaxHome.z < vtx[nCntHome].z)
				{
					g_aHome[nCntHome].VtxMaxHome.z = vtx[nCntHome].z;
				}
				pVtxBuff[nCntHome] += sizeFvF[nType];
			}
			//���_�o�b�t�@���A�����b�N
			g_pMeshHome[nType]->UnlockVertexBuffer();
		//	break;
		//}
	}

	for (int nCntHome = 0; nCntHome < MAX_HOME; nCntHome++)
	{
		if (g_aHome[nCntHome].bUse == false)
		{
			// �ʒu�E�����̏����ݒ�
			g_aHome[nCntHome].pos = pos;
			g_aHome[nCntHome].rot = D3DXVECTOR3(0, 0, 0);
			g_aHome[nCntHome].fShadow = 12;
			g_aHome[nCntHome].nType = nType;
			//�@�e�̃Z�b�g
			//g_aHome[nCntHome].nIdxShadow = SetShadow(g_aHome[nCntHome].pos, D3DXVECTOR3(0, 0, 0), 20.0f);
			g_aHome[nCntHome].bUse = true;
			break;
		}
	}

}
