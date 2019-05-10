//=============================================================================
//
// ��󏈗� [arrow.cpp]
// Author : Meguro Mikiya
//
//=============================================================================
#include "arrow.h"
#include "input.h"
#include "shadow.h"
#include "camera.h"
#include "bullet.h"
#include "polygon.h"
#include "model.h"
#include "player.h"
#include "game.h"
#include "explosion.h"
#include "goal.h"
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPD3DXMESH g_pMeshArrow[MAX_ARROW];					//���b�V�����ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatArrow[MAX_ARROW];			//�}�e���A�����ւ̃|�C���^
LPDIRECT3DTEXTURE9	g_pTextureArrow[MAX_ARROW];		//�e�N�X�`���ւ̃|�C���^
DWORD g_nNumMatArrow = 0;							//�}�e���A�����̐�
ARROW g_aArrow[MAX_ARROW];

int ModelHandle1;
int ModelHandle2;
D3DXVECTOR3 Position1;
D3DXVECTOR3 Position2;
D3DXVECTOR3 SubVector;
float Angle;
//=============================================================================
// ����������
//=============================================================================
void InitArrow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(ARROW_NAME000,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatArrow[0],
		NULL,
		&g_nNumMatArrow,
		&g_pMeshArrow[0]);

	int nNumVtex;	//���_��
	DWORD sizeFvF;	//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff[MAX_ARROW];	//���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 vtx[MAX_ARROW];

	for (int nCntArrow = 0; nCntArrow < MAX_ARROW; nCntArrow++)
	{
		g_aArrow[nCntArrow].VtxMinArrow = D3DXVECTOR3(10000, 0, 10000);
		g_aArrow[nCntArrow].VtxMaxArrow = D3DXVECTOR3(-10000, 0, -10000);
		g_aArrow[nCntArrow].nType = 0;
		g_aArrow[nCntArrow].bUse = false;

	}

	//���_�����擾
	nNumVtex = g_pMeshArrow[0]->GetNumVertices();
	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	sizeFvF = D3DXGetFVFVertexSize(g_pMeshArrow[0]->GetFVF());

	for (int nCntArrow = 0; nCntArrow < MAX_ARROW; nCntArrow++)
	{
		//���_�@���b�N
		g_pMeshArrow[0]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff[nCntArrow]);
		for (int nCntVtx = 0; nCntVtx < nNumVtex; nCntVtx++)
		{	//���_���W�̑��
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff[nCntArrow];
			//MINVTX
			if (g_aArrow[nCntArrow].VtxMinArrow.x > vtx.x)
			{
				g_aArrow[nCntArrow].VtxMinArrow.x = vtx.x;
			}
			if (g_aArrow[nCntArrow].VtxMinArrow.y > vtx.y)
			{
				g_aArrow[nCntArrow].VtxMinArrow.y = vtx.y;
			}
			if (g_aArrow[nCntArrow].VtxMinArrow.z > vtx.z)
			{
				g_aArrow[nCntArrow].VtxMinArrow.z = vtx.z;
			}
			//MAXVTX
			if (g_aArrow[nCntArrow].VtxMaxArrow.x < vtx.x)
			{
				g_aArrow[nCntArrow].VtxMaxArrow.x = vtx.x;
			}
			if (g_aArrow[nCntArrow].VtxMaxArrow.y < vtx.y)
			{
				g_aArrow[nCntArrow].VtxMaxArrow.y = vtx.y;
			}
			if (g_aArrow[nCntArrow].VtxMaxArrow.z < vtx.z)
			{
				g_aArrow[nCntArrow].VtxMaxArrow.z = vtx.z;
			}
			//��������


			pVtxBuff[nCntArrow] += sizeFvF;
		}
		//			//���_�o�b�t�@���A�����b�N
		g_pMeshArrow[0]->UnlockVertexBuffer();
	}
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		ARROW_NAME000,
		&g_pTextureArrow[0]);

	PLAYER *pPlayer = GetPlayer();

	// �ʒu�E�����̏����ݒ�
	g_aArrow[0].pos = D3DXVECTOR3(pPlayer->pos.x, pPlayer->pos.y + 45, pPlayer->pos.z);
	g_aArrow[0].rot = D3DXVECTOR3(0, pPlayer->rot.y, 0);
	g_aArrow[0].fShadow = 12;
	g_aArrow[0].bUse = true;

}
//=============================================================================
// �I������
//=============================================================================
void UninitArrow(void)
{
	for (int nCntArrow = 0; nCntArrow < MAX_ARROW; nCntArrow++)
	{
		// ���b�V���̊J��
		if (g_pMeshArrow[nCntArrow] != NULL)
		{
			g_pMeshArrow[nCntArrow]->Release();
			g_pMeshArrow[nCntArrow] = NULL;
		}
		// �}�e���A���̊J��
		if (g_pBuffMatArrow[nCntArrow] != NULL)
		{
			g_pBuffMatArrow[nCntArrow]->Release();
			g_pBuffMatArrow[nCntArrow] = NULL;
		}
		//�e�N�X�`���̔j��
		if (g_pTextureArrow[nCntArrow] != NULL)
		{
			g_pTextureArrow[nCntArrow]->Release();
			g_pTextureArrow[nCntArrow] = NULL;
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateArrow(void)
{
	PLAYER *pPlayer = GetPlayer();
	MODEL *pModel = GetModel();
	GOAL *pGoal = GetGoal();

	D3DXVECTOR3 VecA;
	D3DXVECTOR3 VecB;
	D3DXVECTOR3 VecC;

	g_aArrow[0].pos = D3DXVECTOR3(pPlayer->pos.x, pPlayer->pos.y + 75, pPlayer->pos.z);

	Position2 = D3DXVECTOR3(50.0f, 0.0f, 0.0f);
	
	VecA = pGoal->pos - g_aArrow[0].pos;
	VecC = g_aArrow[0].pos - pPlayer->pos;
	g_aArrow[0].DiffAngle.y = (VecA.z * VecC.x) - (VecA.x * VecC.z);
			
	//�S�[���[�Ƃ̊p�x�𑪂�
	g_aArrow[0].DestAngle.y = atan2f((pGoal->pos.x - sinf(pGoal->rot.y) - g_aArrow[0].pos.x),
		(pGoal->pos.z - cosf(pGoal->rot.y) - g_aArrow[0].pos.z));
	//�v���C���[�Ƃ̋����̍���
	g_aArrow[0].DiffAngle.y = g_aArrow[0].DestAngle.y - g_aArrow[0].rot.y;

	//�p�x�̐ݒ�
	if (g_aArrow[0].DiffAngle.y > D3DX_PI)
	{
		g_aArrow[0].DiffAngle.y -= D3DX_PI* 2.0f;
	}
	if (g_aArrow[0].DiffAngle.y < -D3DX_PI)
	{
		g_aArrow[0].DiffAngle.y += D3DX_PI* 2.0f;
	}
	//�����̐ݒ�
	g_aArrow[0].rot.y += g_aArrow[0].DiffAngle.y * 1.0f;
	if (g_aArrow[0].rot.y > D3DX_PI)
	{
		g_aArrow[0].rot.y -= D3DX_PI * 2.0f;
	}
	if (g_aArrow[0].rot.y < -D3DX_PI)
	{
		g_aArrow[0].rot.y += D3DX_PI * 2.0f;
	}


}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawArrow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;						//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;							//�}�e���A���f�[�^�ւ̃|�C���^

	for (int nCntArrow = 0; nCntArrow < MAX_ARROW; nCntArrow++)
	{		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_aArrow[nCntArrow].mtxWorld);
		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aArrow[nCntArrow].rot.y, g_aArrow[nCntArrow].rot.x, g_aArrow[nCntArrow].rot.z);
		D3DXMatrixMultiply(&g_aArrow[nCntArrow].mtxWorld, &g_aArrow[nCntArrow].mtxWorld, &mtxRot);
		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_aArrow[nCntArrow].pos.x, g_aArrow[nCntArrow].pos.y, g_aArrow[nCntArrow].pos.z);
		D3DXMatrixMultiply(&g_aArrow[nCntArrow].mtxWorld, &g_aArrow[nCntArrow].mtxWorld, &mtxTrans);
		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_aArrow[nCntArrow].mtxWorld);
		// ���݂̃}�e���A�����擾
		pDevice->GetMaterial(&matDef);
		// �}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)g_pBuffMatArrow[g_aArrow[nCntArrow].nType]->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_nNumMatArrow; nCntMat++)
		{	// �}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
			// �e�N�X�`��
			pDevice->SetTexture(0, g_pTextureArrow[g_aArrow[nCntArrow].nType]);
			if (g_aArrow[nCntArrow].bUse == true)	//��󂪎g�p����Ă���
			{
				// ���(�p�[�c)�̕`��
				g_pMeshArrow[g_aArrow[nCntArrow].nType]->DrawSubset(nCntMat);
			}
		}
		// �}�e���A�����f�t�H���g�ɖ߂�
		pDevice->SetMaterial(&matDef);
	}
}

//*****************************************************************************
//���|�C���^����
//*****************************************************************************
ARROW *GetArrow(void)
{
	return &g_aArrow[0];
}
//=============================================================================
// �ݒ菈��
//=============================================================================
void SetArrow(D3DXVECTOR3 pos, int nType)
{

	int nNumVtex;	//���_��
	DWORD sizeFvF[MAX_ARROW];	//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff[MAX_ARROW];	//���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 vtx[MAX_ARROW];

	//���_�����擾
	nNumVtex = g_pMeshArrow[nType]->GetNumVertices();
	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	sizeFvF[nType] = D3DXGetFVFVertexSize(g_pMeshArrow[nType]->GetFVF());

	for (int nCntArrow = 0; nCntArrow < MAX_ARROW; nCntArrow++)
	{
		//if (g_aArrow[nCntArrow].bUse == false)
		//{
			//���_�@���b�N
			g_pMeshArrow[nType]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff[nType]);
			for (int nCntVtx = 0; nCntVtx < nNumVtex; nCntVtx++)
			{	//���_���W�̑��
				vtx[nCntArrow] = *(D3DXVECTOR3*)pVtxBuff[nType];
				if (g_aArrow[nCntArrow].VtxMinArrow.x > vtx[nCntArrow].x)
				{
					g_aArrow[nCntArrow].VtxMinArrow.x = vtx[nCntArrow].x;
				}
				if (g_aArrow[nCntArrow].VtxMinArrow.y > vtx[nCntArrow].y)
				{
					g_aArrow[nCntArrow].VtxMinArrow.y = vtx[nCntArrow].y;
				}
				if (g_aArrow[nCntArrow].VtxMinArrow.z > vtx[nCntArrow].z)
				{
					g_aArrow[nCntArrow].VtxMinArrow.z = vtx[nCntArrow].z;
				}

				if (g_aArrow[nCntArrow].VtxMaxArrow.x < vtx[nCntArrow].x)
				{
					g_aArrow[nCntArrow].VtxMaxArrow.x = vtx[nCntArrow].x;
				}
				if (g_aArrow[nCntArrow].VtxMaxArrow.y < vtx[nCntArrow].y)
				{
					g_aArrow[nCntArrow].VtxMaxArrow.y = vtx[nCntArrow].y;
				}
				if (g_aArrow[nCntArrow].VtxMaxArrow.z < vtx[nCntArrow].z)
				{
					g_aArrow[nCntArrow].VtxMaxArrow.z = vtx[nCntArrow].z;
				}
				pVtxBuff[nCntArrow] += sizeFvF[nType];
			}
			//���_�o�b�t�@���A�����b�N
			g_pMeshArrow[nType]->UnlockVertexBuffer();
		//	break;
		//}
	}

	for (int nCntArrow = 0; nCntArrow < MAX_ARROW; nCntArrow++)
	{
		if (g_aArrow[nCntArrow].bUse == false)
		{
			// �ʒu�E�����̏����ݒ�
			g_aArrow[nCntArrow].pos = pos;
			g_aArrow[nCntArrow].rot = D3DXVECTOR3(0, 0, 0);
			g_aArrow[nCntArrow].fShadow = 12;
			g_aArrow[nCntArrow].nType = nType;
			//�@�e�̃Z�b�g
			g_aArrow[nCntArrow].nIdxShadow = SetShadow(g_aArrow[nCntArrow].pos, D3DXVECTOR3(0, 0, 0), 20.0f);
			g_aArrow[nCntArrow].bUse = true;
			break;
		}
	}

}