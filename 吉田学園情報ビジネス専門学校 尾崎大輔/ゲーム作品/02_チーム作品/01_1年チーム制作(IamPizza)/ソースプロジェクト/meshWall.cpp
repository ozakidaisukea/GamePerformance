//=============================================================================
//
// ���b�V���E�H�[������ [MESHWALL.cpp]
// Author : Meguro Mikiya
//
//=============================================================================
#include "meshWall.h"
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexMeshWall(LPDIRECT3DDEVICE9 pDevice);
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshWall[MAX_MESHWALL] = {};		//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_pTextureMeshWall[MAX_MESHWALL] = {};		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshWall[MAX_MESHWALL] = {};		//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
//D3DXVECTOR3 g_aMashWall[nCnt].pos;								//�ʒu
//D3DXVECTOR3 g_aMashWall[nCnt].rot;								//����
//D3DXMATRIX	g_aMashWall[nCnt].mtrxWorld;						//���[���h�}�g���b�N�X
int g_nNumVertexMeshWall;								//���_��
int g_nNumIndexMeshWall;								//�C���f�b�N�X��
int g_nNumPolygonMeshWall;								//�|���S����
MESHWALL g_aMashWall[MAX_MESHWALL];
//=============================================================================
// ����������
//=============================================================================
void InitMeshWall(int nIdxMeshWall, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	LPDIRECT3DDEVICE9 pDevice;	// �f�o�C�X�̎擾
	pDevice = GetDevice();	// �f�o�C�X�̎擾

	int nCntXvtx = 0;
	int nCntZvtx = 0;
	int nCntVtx = 0;	
	int nCntIdx = 0;

	g_nNumVertexMeshWall = (X_WALLSIZE + 1) * (Y_WALLSIZE + 1);
	g_nNumIndexMeshWall = ((X_WALLSIZE + 1) * (Y_WALLSIZE + 1) + ((Y_WALLSIZE - 1) * 2) + (X_WALLSIZE + 1) * (Y_WALLSIZE - 1));

	//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			MESHWALL_TEXTURENAME,
			&g_pTextureMeshWall[nIdxMeshWall]);
	// ���_���̍쐬
		pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) *  g_nNumVertexMeshWall,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshWall[nIdxMeshWall],
		NULL);
	// �C���f�b�N�X���̍쐬
	pDevice->CreateIndexBuffer(sizeof(WORD) * g_nNumIndexMeshWall,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,	//2byte�̃f�[�^
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshWall[nIdxMeshWall],
		NULL);

	VERTEX_3D *pVtx;
	//���_�o�b�t�@�����b�N
	g_pVtxBuffMeshWall[nIdxMeshWall]->Lock(0, 0, (void**)&pVtx, 0);
	
	//���W�𒆐S�ɂ���
	//g_aMashWall[nIdxMeshWall].fPos_X = (g_aMashWall[nIdxMeshWall].fXpos * X_WALLSIZE) / 2;
	//g_aMashWall[nIdxMeshWall].fPos_Y = (g_aMashWall[nIdxMeshWall].fYpos * Y_WALLSIZE) / 2;


	for (nCntZvtx = 0; nCntZvtx < Y_WALLSIZE + 1; nCntZvtx++)
	{
		for (nCntXvtx = 0; nCntXvtx < X_WALLSIZE + 1; nCntXvtx++)
		{
			//���_���̐ݒ�
			pVtx[(nCntZvtx + nCntXvtx) + nCntVtx + g_aMashWall[nIdxMeshWall].nVtxIndex].pos = D3DXVECTOR3(g_aMashWall[nIdxMeshWall].fPos_X + (nCntXvtx * X_POSSIZE), g_aMashWall[nIdxMeshWall].fPos_Y - (nCntZvtx * Y_POSSIZE), 0.0f);
			//�@���̐ݒ�
			pVtx[(nCntZvtx + nCntXvtx) + nCntVtx + g_aMashWall[nIdxMeshWall].nVtxIndex].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			//���_�J���[
			pVtx[(nCntZvtx + nCntXvtx) + nCntVtx + g_aMashWall[nIdxMeshWall].nVtxIndex].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.7f);
			//�e�N�X�`�����W
			pVtx[(nCntZvtx + nCntXvtx) + nCntVtx + g_aMashWall[nIdxMeshWall].nVtxIndex].tex = D3DXVECTOR2(0 + (nCntXvtx * 0.5f), 0 + (nCntZvtx * 0.5f));
		}
		//���_���̒l��ێ�
		nCntVtx += X_WALLSIZE;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffMeshWall[nIdxMeshWall]->Unlock();
	
	//�C���f�b�N�X�f�[�^�ւ̃|�C���^
	WORD *pIdx;
	//�C���f�b�N�X�o�b�t�@�����b�N
	g_pIdxBuffMeshWall[nIdxMeshWall]->Lock(0, 0, (void**)&pIdx, 0);

	

#if 0
	for (int nCntIdxZ = 0; nCntIdxZ < Y_WALLSIZE; nCntIdxZ++)
	{
		for (int nCntIdxX = 0; nCntIdxX < X_WALLSIZE + 1; nCntIdxX++, nCntIdx++)
		{
			pIdx[0] = nCntIdx + X_WALLSIZE + 1;
			pIdx[1] = nCntIdx;
			//pIdx��2�����炷
			pIdx += 2;
			if (nCntIdxZ < Y_WALLSIZE && nCntIdxX == X_WALLSIZE)
			{
				pIdx[0] = nCntIdx;
				pIdx[1] = nCntIdx + (X_WALLSIZE + 1) + 1;
				//pIdx��2�����炷
				pIdx += 2;
			}
		}
	}
#endif

	//�C���f�b�N�X(InitOnly)
#if 1	
	for (int nCntIdxZ = 0; nCntIdxZ < Y_WALLSIZE; nCntIdxZ++)
	{
		for (int nCntIdxX = 0; nCntIdxX < X_WALLSIZE + 1; nCntIdxX++, nCntIdx++)
		{
			pIdx[0 + g_aMashWall[nIdxMeshWall].nIdxIndex] = nCntIdx + X_WALLSIZE + 1;
			pIdx[1 + g_aMashWall[nIdxMeshWall].nIdxIndex] = nCntIdx;
			//pIdx��2�����炷
			pIdx += 2;
			if (nCntIdxZ < Y_WALLSIZE && nCntIdxX == X_WALLSIZE)
			{
				pIdx[0 + g_aMashWall[nIdxMeshWall].nIdxIndex] = nCntIdx;
				pIdx[1 + g_aMashWall[nIdxMeshWall].nIdxIndex] = nCntIdx + (X_WALLSIZE + 1) + 1;
				//pIdx��2�����炷
				pIdx += 2;
			}
		}
	}
#endif
	//�C���f�b�N�X�o�b�t�@���A�����b�N
	g_pIdxBuffMeshWall[nIdxMeshWall]->Unlock();

	g_aMashWall[nIdxMeshWall].pos = pos;
	g_aMashWall[nIdxMeshWall].rot = rot;
	g_aMashWall[nIdxMeshWall].bUse = true;
}

//=============================================================================
// �I������
//=============================================================================
void UninitMeshWall(void)
{	//�e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < MAX_MESHWALL; nCnt++)
	{
		if (g_pTextureMeshWall[nCnt] != NULL)
		{
			g_pTextureMeshWall[nCnt]->Release();
			g_pTextureMeshWall[nCnt] = NULL;
		}
		// ���_�o�b�t�@�̊J��
		if (g_pVtxBuffMeshWall[nCnt] != NULL)
		{
			g_pVtxBuffMeshWall[nCnt]->Release();
			g_pVtxBuffMeshWall[nCnt] = NULL;
		}
		// �C���f�b�N�X�o�b�t�@�̊J��
		if (g_pIdxBuffMeshWall[nCnt] != NULL)
		{
			g_pIdxBuffMeshWall[nCnt]->Release();
			g_pIdxBuffMeshWall[nCnt] = NULL;
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateMeshWall(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawMeshWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X

	for (int nCnt= 0; nCnt < MAX_MESHWALL; nCnt++)
	{
	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_aMashWall[nCnt].mtrxWorld); 
	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aMashWall[nCnt].rot.y, g_aMashWall[nCnt].rot.x, g_aMashWall[nCnt].rot.z);
	D3DXMatrixMultiply(&g_aMashWall[nCnt].mtrxWorld, &g_aMashWall[nCnt].mtrxWorld, &mtxRot);
	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_aMashWall[nCnt].pos.x, g_aMashWall[nCnt].pos.y, g_aMashWall[nCnt].pos.z);
	D3DXMatrixMultiply(&g_aMashWall[nCnt].mtrxWorld, &g_aMashWall[nCnt].mtrxWorld, &mtxTrans);
	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_aMashWall[nCnt].mtrxWorld);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffMeshWall[nCnt], 0, sizeof(VERTEX_3D));
	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(g_pIdxBuffMeshWall[nCnt]);
	//���_�t�H�[�}�b�g��ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureMeshWall[nCnt]);

	//�|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0 , g_nNumVertexMeshWall, 0, g_nNumIndexMeshWall - 2);
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexMeshWall(LPDIRECT3DDEVICE9 pDevice)
{
	// ���_�o�b�t�@�𐶐�


	// ���_���̐ݒ�
}

