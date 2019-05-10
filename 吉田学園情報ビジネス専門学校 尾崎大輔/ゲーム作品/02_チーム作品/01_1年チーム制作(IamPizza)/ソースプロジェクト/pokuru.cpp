//=============================================================================
//
// ���f������ [pokuru.cpp]
// Author : Meguro Mikiya
//
//=============================================================================
#include "pokuru.h"
#include "input.h"
#include "shadow.h"
#include "camera.h"
#include "bullet.h"
#include "polygon.h"
#include "model.h"
#include "game.h"
#include "goal.h"
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9	g_pTexturePokuru = NULL;		//�e�N�X�`���ւ̃|�C���^
POKURU g_aPokuru;
//=============================================================================
// ����������
//=============================================================================
void InitPokuru(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(POKURU_NAME,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_aPokuru.aModel[0].pBuffMat,
		NULL,
		&g_aPokuru.aModel[0].nNumMat,
		&g_aPokuru.aModel[0].pMesh);
	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(POKURU_NAME1,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_aPokuru.aModel[1].pBuffMat,
		NULL,
		&g_aPokuru.aModel[1].nNumMat,
		&g_aPokuru.aModel[1].pMesh);
	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(POKURU_NAME2,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_aPokuru.aModel[2].pBuffMat,
		NULL,
		&g_aPokuru.aModel[2].nNumMat,
		&g_aPokuru.aModel[2].pMesh);
	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(POKURU_NAME3,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_aPokuru.aModel[3].pBuffMat,
		NULL,
		&g_aPokuru.aModel[3].nNumMat,
		&g_aPokuru.aModel[3].pMesh);
	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(POKURU_NAME4,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_aPokuru.aModel[4].pBuffMat,
		NULL,
		&g_aPokuru.aModel[4].nNumMat,
		&g_aPokuru.aModel[4].pMesh);
	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(POKURU_NAME5,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_aPokuru.aModel[5].pBuffMat,
		NULL,
		&g_aPokuru.aModel[5].nNumMat,
		&g_aPokuru.aModel[5].pMesh);
	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(POKURU_NAME6,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_aPokuru.aModel[6].pBuffMat,
		NULL,
		&g_aPokuru.aModel[6].nNumMat,
		&g_aPokuru.aModel[6].pMesh);
	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(POKURU_NAME7,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_aPokuru.aModel[7].pBuffMat,
		NULL,
		&g_aPokuru.aModel[7].nNumMat,
		&g_aPokuru.aModel[7].pMesh);
	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(POKURU_NAME8,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_aPokuru.aModel[8].pBuffMat,
		NULL,
		&g_aPokuru.aModel[8].nNumMat,
		&g_aPokuru.aModel[8].pMesh);
	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(POKURU_NAME9,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_aPokuru.aModel[9].pBuffMat,
		NULL,
		&g_aPokuru.aModel[9].nNumMat,
		&g_aPokuru.aModel[9].pMesh);

	int nNumVtex;	//���_��
	DWORD sizeFvF;	//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;	//���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 vtx;

	for (int nCntPokuru = 0; nCntPokuru < POKURU_PARTS; nCntPokuru++)
	{
		//���_�����擾
		nNumVtex = g_aPokuru.aModel[nCntPokuru].pMesh->GetNumVertices();
		//���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFvF = D3DXGetFVFVertexSize(g_aPokuru.aModel[nCntPokuru].pMesh->GetFVF());

		//���_�o�b�t�@�����b�N
		g_aPokuru.aModel[nCntPokuru].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);
		for (int nCntVtx = 0; nCntVtx < nNumVtex; nCntVtx++)
		{	//���_���W�̑��

			vtx = *(D3DXVECTOR3*)pVtxBuff;

			if (g_aPokuru.VtxMin.x > vtx.x)
			{
				g_aPokuru.VtxMin.x = vtx.x;
			}
			if (g_aPokuru.VtxMin.y > vtx.y)
			{
				g_aPokuru.VtxMin.y = vtx.y;
			}
			if (g_aPokuru.VtxMin.z > vtx.z)
			{
				g_aPokuru.VtxMin.z = vtx.z;
			}

			if (g_aPokuru.VtxMax.x < vtx.x)
			{
				g_aPokuru.VtxMax.x = vtx.x;
			}
			if (g_aPokuru.VtxMax.y < vtx.y)
			{
				g_aPokuru.VtxMax.y = vtx.y;
			}
			if (g_aPokuru.VtxMax.z < vtx.z)
			{
				g_aPokuru.VtxMax.z = vtx.z;
			}

			//�T�C�Y���|�C���^��i�߂�
			pVtxBuff += sizeFvF;
		}
		//���_�o�b�t�@���A�����b�N
		g_aPokuru.aModel[nCntPokuru].pMesh->UnlockVertexBuffer();
	}

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		POKURU_NAME,
		&g_pTexturePokuru);

	GOAL *pGoal = GetGoal();

	// �ʒu�E�����̏����ݒ�
	g_aPokuru.pos = D3DXVECTOR3(pGoal->pos.x, pGoal->pos.y, pGoal->pos.z);
	g_aPokuru.rot = D3DXVECTOR3(0, D3DX_PI * 0.0f, 0);
	g_aPokuru.move = D3DXVECTOR3(0, 0, 0);
	g_aPokuru.fShadow = 1;
	g_aPokuru.fDestAngle = D3DX_PI * 1.0f;
	g_aPokuru.state = POKURUSTATE_NORMAL;
	g_aPokuru.fDiffAngle = 0;
	g_aPokuru.fHeight = 5;
	g_aPokuru.fWidth = 10;
	//���f���̃I�t�Z�b�g
	g_aPokuru.aModel[0].nIdxModelParent = -1;
	g_aPokuru.aModel[0].pos = D3DXVECTOR3(0, 30, 0);

	g_aPokuru.aModel[1].nIdxModelParent = 0;
	g_aPokuru.aModel[1].pos = D3DXVECTOR3(0, 30, 0);

	g_aPokuru.aModel[2].nIdxModelParent = 0;
	g_aPokuru.aModel[2].pos = D3DXVECTOR3(-8.5, 23.0, 0.0);
	g_aPokuru.aModel[2].rot = D3DXVECTOR3(0.0f, 0.0f, 1.4f);

	g_aPokuru.aModel[3].nIdxModelParent = 2;
	g_aPokuru.aModel[3].pos = D3DXVECTOR3(-30.0, -1.0, 0.0);

	g_aPokuru.aModel[4].nIdxModelParent = 0;
	g_aPokuru.aModel[4].pos = D3DXVECTOR3(8.5, 25.0, 0.0);
	g_aPokuru.aModel[4].rot = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

	g_aPokuru.aModel[5].nIdxModelParent = 4;
	g_aPokuru.aModel[5].pos = D3DXVECTOR3(30.0, -3.0, 0.0);

	g_aPokuru.aModel[6].nIdxModelParent = 0;
	g_aPokuru.aModel[6].pos = D3DXVECTOR3(-5.0, 0.0, 0.0);

	g_aPokuru.aModel[7].nIdxModelParent = 6;
	g_aPokuru.aModel[7].pos = D3DXVECTOR3(0.0, -25.0, 5.0);

	g_aPokuru.aModel[8].nIdxModelParent = 0;
	g_aPokuru.aModel[8].pos = D3DXVECTOR3(5.0, 0.0, 0.0);

	g_aPokuru.aModel[9].nIdxModelParent = 8;
	g_aPokuru.aModel[9].pos = D3DXVECTOR3(0.0f, -25.0f, 2.7f);

	//�@�e�̃Z�b�g
	g_aPokuru.nIdxShadow = SetShadow(D3DXVECTOR3(0, 0, 100), D3DXVECTOR3(0, 0, 0), 20.0f);
}

//=============================================================================
// �I������
//=============================================================================
void UninitPokuru(void)
{
	for (int nCntPokuru = 0; nCntPokuru < POKURU_PARTS; nCntPokuru++)
	{
		// ���b�V���̊J��
		if (g_aPokuru.aModel[nCntPokuru].pMesh != NULL)
		{
			g_aPokuru.aModel[nCntPokuru].pMesh->Release();
			g_aPokuru.aModel[nCntPokuru].pMesh = NULL;
		}
		// �}�e���A���̊J��
		if (g_aPokuru.aModel[nCntPokuru].pBuffMat != NULL)
		{
			g_aPokuru.aModel[nCntPokuru].pBuffMat->Release();
			g_aPokuru.aModel[nCntPokuru].pBuffMat = NULL;
		}
	}
	//�e�N�X�`���̔j��
	if (g_pTexturePokuru != NULL)
	{
		g_pTexturePokuru->Release();
		g_pTexturePokuru = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePokuru(void)
{
	Camera *pCamera = GetCamera();
	GOAL *pGoal = GetGoal();

	// �ʒu�E�����̏����ݒ�
	g_aPokuru.pos = D3DXVECTOR3(pGoal->pos.x, pGoal->pos.y, pGoal->pos.z + 70);

	//�J�����Ƃ̋��������߂�
	double length = pow((g_aPokuru.pos.x - pCamera->posV.x)*(g_aPokuru.pos.x - pCamera->posV.x)
		+ (g_aPokuru.pos.z - pCamera->posV.z)*(g_aPokuru.pos.z - pCamera->posV.z), 0.5);

	//float�^�ɕϊ�
	g_aPokuru.fLength = (float)length;

	//�Q�[���X�e�C�g�̎擾
	GAMESTATE GameState;
	GameState = GetGameState();

	if (0 >= g_aPokuru.pos.y)
	{
		g_aPokuru.pos.y = 0 + 0.1f;
		g_aPokuru.move.y = 0;
	}

	//���f���Ƃ̓����蔻��
	if (CollisionModel(&g_aPokuru.pos, &g_aPokuru.posold, &g_aPokuru.move, g_aPokuru.VtxMax, g_aPokuru.VtxMin) == true)
	{//���f���ɒ��n�����Ƃ�

	}

	SetPositionShadow(g_aPokuru.nIdxShadow, D3DXVECTOR3(g_aPokuru.pos.x, 0, g_aPokuru.pos.z), 15);
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPokuru(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X

	D3DMATERIAL9 matDef;						//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;							//�}�e���A���f�[�^�ւ̃|�C���^
	D3DXMATRIX mtxParent;
	if (g_aPokuru.fLength < 2200)
	{//���f���ƃv���C���[�̋����ŕ`�悷�邩���߂�
	// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_aPokuru.mtxWorld);
		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aPokuru.rot.y, g_aPokuru.rot.x, g_aPokuru.rot.z);
		D3DXMatrixMultiply(&g_aPokuru.mtxWorld, &g_aPokuru.mtxWorld, &mtxRot);
		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_aPokuru.pos.x, g_aPokuru.pos.y, g_aPokuru.pos.z);
		D3DXMatrixMultiply(&g_aPokuru.mtxWorld, &g_aPokuru.mtxWorld, &mtxTrans);
		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_aPokuru.mtxWorld);

		for (int nCntPokuru = 0; nCntPokuru < POKURU_PARTS; nCntPokuru++)
		{
			if (g_aPokuru.aModel[nCntPokuru].nIdxModelParent == -1)
			{
				mtxParent = g_aPokuru.mtxWorld;
			}
			else
			{
				mtxParent = g_aPokuru.aModel[g_aPokuru.aModel[nCntPokuru].nIdxModelParent].mtxWorld;
			}

			// �q���f��
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aPokuru.aModel[nCntPokuru].mtxWorld);
			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aPokuru.aModel[nCntPokuru].rot.y, g_aPokuru.aModel[nCntPokuru].rot.x, g_aPokuru.aModel[nCntPokuru].rot.z);
			D3DXMatrixMultiply(&g_aPokuru.aModel[nCntPokuru].mtxWorld, &g_aPokuru.aModel[nCntPokuru].mtxWorld, &mtxRot);
			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aPokuru.aModel[nCntPokuru].pos.x, g_aPokuru.aModel[nCntPokuru].pos.y, g_aPokuru.aModel[nCntPokuru].pos.z);
			D3DXMatrixMultiply(&g_aPokuru.aModel[nCntPokuru].mtxWorld, &g_aPokuru.aModel[nCntPokuru].mtxWorld, &mtxTrans);
			//�e�̏�������
			D3DXMatrixMultiply(&g_aPokuru.aModel[nCntPokuru].mtxWorld, &g_aPokuru.aModel[nCntPokuru].mtxWorld, &mtxParent);
			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aPokuru.aModel[nCntPokuru].mtxWorld);

			// ���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);
			// �}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_aPokuru.aModel[nCntPokuru].pBuffMat->GetBufferPointer();
			for (int nCntMat = 0; nCntMat < (int)g_aPokuru.aModel[nCntPokuru].nNumMat; nCntMat++)
			{
				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
				// �e�N�X�`��
				pDevice->SetTexture(0, g_pTexturePokuru);
				// ���f��(�p�[�c)�̕`��
				g_aPokuru.aModel[nCntPokuru].pMesh->DrawSubset(nCntMat);
			}
			// �}�e���A�����f�t�H���g�ɖ߂�
			pDevice->SetMaterial(&matDef);
		}
	}
}

//*****************************************************************************
//�v���C���[�|�C���^����
//*****************************************************************************
POKURU *GetPokuru(void)
{
	return &g_aPokuru;
}