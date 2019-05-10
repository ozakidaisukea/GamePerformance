//=============================================================================
//
// ���f������ [Player3.cpp]
// Author : Ozaki
//
//=============================================================================
#include "Player3.h"
#include "Input.h"
#include "camera.h"
#include "shadow.h"
#include "bullet.h"
#include "Explosion.h"
#include "effect.h"
#include "particle.h"
#include "model.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MOVE_PLAYER3	(0.5f)
#define MOVE_BULLET		(8.0f)
#define MAX_PLAYER3		(2)
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9  g_pVtxBuffPlayer3 = NULL;	// ���_�o�b�t�@�̃|�C���^
LPD3DXMESH				 g_pMeshPlayer3 = NULL;		// ���b�V�����ւ̃|�C���^
LPD3DXBUFFER			 g_BuffMatPlayer3 = NULL;	// �}�e���A�����ւ̃|�C���^
D3DXVECTOR3				 g_vtxMinplayer3, g_vtxMaxplayer3;
DWORD					 g_nNumMatPlayer3 = 0;		// �}�e���A�����̐�
D3DXMATRIX				 g_mtxWorldPlayer3;			// ���[���h�}�g���b�N�X
Player3					 g_Player3;					// �v���C���[
int						 g_nIdxShadow3;
//D3DXVECTOR3				 aPos[4];
//D3DXVECTOR3				 VecA;
//D3DXVECTOR3				 VecB;
//D3DXVECTOR3			 	 VecC;
//=============================================================================
// ����������
//=============================================================================
void InitPlayer3(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	MODE Mode = GetMode();

	switch (Mode)
	{
	case MODE_TITLE:
	{
		g_Player3.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	}
	break;
	case MODE_GAME:
	{
		g_Player3.pos = D3DXVECTOR3(0.0f, 0.0f, 800.0f);
	}
	break;

	}

	g_Player3.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player3.posold = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player3.bDisp = true;
	g_Player3.nCounterState = 0;
	g_Player3.nLife = 10;
	g_Player3.aModel[2];

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("data\\MODEL\\saku.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Player3.aModel[0].pBuffMat,
		NULL,
		&g_Player3.aModel[0].nNumMat,
		&g_Player3.aModel[0].pMesh);

	D3DXLoadMeshFromX("data\\MODEL\\saku.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Player3.aModel[1].pBuffMat,
		NULL,
		&g_Player3.aModel[1].nNumMat,
		&g_Player3.aModel[1].pMesh);

	// �ʒu�E�����̏����ݒ�

	//g_nIdxShadow22 = SetShadow(g_Player3.pos, g_Player3.rot);

	g_Player3.aModel[0].nIdxModelParent = -1;
	g_Player3.aModel[0].pos = D3DXVECTOR3(100.0f, 0.0f, 0.0f);

	g_Player3.aModel[1].nIdxModelParent = 0;
	g_Player3.aModel[1].pos = D3DXVECTOR3(-100.0f, 0.0f, 0.0f);

	int						 nNumVtx;					// ���_��

	DWORD					 sizeFVF;					// ���_�t�H�[�}�b�g�̐ݒ�
	BYTE					 *pVtxBuff;					// ���_�o�b�n�ւ̃|�C���^���擾

	nNumVtx = g_Player3.aModel[0].pMesh->GetNumVertices();

	sizeFVF = D3DXGetFVFVertexSize(g_Player3.aModel[0].pMesh->GetFVF());

	g_vtxMinplayer3 = D3DXVECTOR3(10000.0f, 10000.0f, 10000.0f);
	g_vtxMaxplayer3 = D3DXVECTOR3(-10000.0f, -10000.0f, -10000.0f);

	// ���_�o�b�t�@�����b�N���A
	g_Player3.aModel[0].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	// ���_���W�̑��

		if (g_vtxMaxplayer3.x < vtx.x)
		{
			g_vtxMaxplayer3.x = vtx.x;
		}
		if (g_vtxMaxplayer3.y < vtx.y)
		{
			g_vtxMaxplayer3.y = vtx.y;
		}
		if (g_vtxMaxplayer3.z < vtx.z)
		{
			g_vtxMaxplayer3.z = vtx.z;
		}

		// min
		if (g_vtxMaxplayer3.x > vtx.x)
		{
			g_vtxMaxplayer3.x = vtx.x;
		}
		if (g_vtxMaxplayer3.y > vtx.y)
		{
			g_vtxMaxplayer3.y = vtx.y;
		}
		if (g_vtxMaxplayer3.z > vtx.z)
		{
			g_vtxMaxplayer3.z = vtx.z;
		}


		pVtxBuff += sizeFVF;							// �T�C�Y���|�C���^��i�߂�

	}
	// ���_�o�b�t�@���A�����b�N����
	g_Player3.aModel[0].pMesh->UnlockVertexBuffer();

}

//=============================================================================
// �I������
//=============================================================================
void UninitPlayer3(void)
{

	for (int nCnt = 0; nCnt < MAX_PLAYER3; nCnt++)
	{

		// ���b�V���̊J��
		if (g_Player3.aModel[0].pMesh != NULL)
		{
			g_Player3.aModel[0].pMesh->Release();

			g_Player3.aModel[0].pMesh = NULL;
		}

	}
	// �}�e���A���̊J��
	if (g_Player3.aModel[0].pBuffMat != NULL)
	{
		g_Player3.aModel[0].pBuffMat->Release();

		g_Player3.aModel[0].pBuffMat = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePlayer3(void)
{
	MODE Mode = GetMode();

	switch (Mode)
	{
	case MODE_TITLE:
	{
		g_Player3.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	}
	break;
	case MODE_GAME:
	{


		g_Player3.pos = D3DXVECTOR3(0.0f, 0.0f, 800.0f);

		g_Player3.pos.x += g_Player3.move.x;
		g_Player3.pos.y += g_Player3.move.y;
		g_Player3.pos.z += g_Player3.move.z;

		g_Player3.move.x += (0.0f - g_Player3.move.x) *0.4f;
		g_Player3.move.y += (0.0f - g_Player3.move.y) *0.4f;
		g_Player3.move.z += (0.0f - g_Player3.move.z) *0.4f;

		//if (g_Player3.pos.x >= 950)
		//{
		//	g_Player3.pos.x = 950 - 1;
		//}
		//if (g_Player3.pos.x <= -950)
		//{
		//	g_Player3.pos.x = -950 - 1;
		//}
		//if (g_Player3.pos.z <= -950)
		//{
		//	g_Player3.pos.z = -950 - 1;
		//}
		//if (g_Player3.pos.z >= 950)
		//{
		//	g_Player3.pos.z = 950 - 1;
		//}

		if (g_Player3.pos.y < 1.0f)
		{
			g_Player3.pos.y = 1;
		}



		//SetPostionShadow(g_nIdxShadow22, D3DXVECTOR3(g_Player3.pos.x, 0, g_Player3.pos.z));

		/*SetEffect(g_Player3.pos.x, 0, g_Player3.move.x);*/
	}
	break;

	}


}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPlayer3(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX		mtxRot, mtxTrans;				// �v�Z�p�̃}�g���b�N�X
	D3DMATERIAL9	matDef;							// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL	*pMat;							// �}�e���A���f�[�^�ւ̃|�C���^
	D3DXMATRIX		mtxParent;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_Player3.mtxWorld);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player3.rot.y, g_Player3.rot.x, g_Player3.rot.z);
	D3DXMatrixMultiply(&g_Player3.mtxWorld, &g_Player3.mtxWorld, &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_Player3.pos.x, g_Player3.pos.y, g_Player3.pos.z);
	D3DXMatrixMultiply(&g_Player3.mtxWorld, &g_Player3.mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_Player3.mtxWorld);

	for (int nCnt = 0; nCnt < MAX_PLAYER3; nCnt++)
	{
		if (g_Player3.aModel[0].nIdxModelParent == -1)
		{
			mtxParent = g_Player3.mtxWorld;
		}
		else
		{
			mtxParent = g_Player3.aModel[g_Player3.aModel[nCnt].nIdxModelParent].mtxWorld;
		}

		//if (g_Player3.aModel[1].nIdxModelParent == 0)
		//{
		//	mtxParent = g_Player3.mtxWorld;
		//}
		//else
		//{
		//	mtxParent = g_Player3.aModel[1].mtxWorld;
		//}

		//=============================================================================
		// ���f���i�e�j
		//=============================================================================

		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_Player3.aModel[nCnt].mtxWorld);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player3.aModel[nCnt].rot.y, g_Player3.aModel[nCnt].rot.x, g_Player3.aModel[nCnt
		].rot.z);
		D3DXMatrixMultiply(&g_Player3.aModel[nCnt].mtxWorld, &g_Player3.aModel[nCnt].mtxWorld, &mtxRot);

		// �ړ��𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_Player3.aModel[nCnt].pos.x, g_Player3.aModel[nCnt].pos.y, g_Player3.aModel[nCnt].pos.z);
		D3DXMatrixMultiply(&g_Player3.aModel[nCnt].mtxWorld, &g_Player3.aModel[nCnt].mtxWorld, &mtxTrans);


		D3DXMatrixMultiply(&g_Player3.aModel[nCnt].mtxWorld, &g_Player3.aModel[nCnt].mtxWorld, &mtxParent);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_Player3.aModel[nCnt].mtxWorld);

		// ���݂̃}�e���A�����擾
		pDevice->GetMaterial(&matDef);

		// �}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)g_Player3.aModel[nCnt].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_Player3.aModel[nCnt].nNumMat; nCntMat++)
		{
			// �}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			pDevice->SetTexture(0, NULL);

			// ���f��(�p�[�c)�̕`��
			g_Player3.aModel[nCnt].pMesh->DrawSubset(nCntMat);

		}

		// �}�e���A�����f�t�H���g�ɖ߂�
		pDevice->SetMaterial(&matDef);
	}
}

//=============================================================================
// ���f���̎擾
//=============================================================================
Player3 *GetPlayer2(void)
{
	return &g_Player3;
}

