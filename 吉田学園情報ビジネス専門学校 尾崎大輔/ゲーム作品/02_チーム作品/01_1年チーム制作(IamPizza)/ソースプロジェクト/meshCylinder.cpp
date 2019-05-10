//=============================================================================
//
// ���b�V���V�����_�[���� [meshCylinder.cpp]
// Author : Meguro Mikiya
//
//=============================================================================
#include "meshCylinder.h"
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexMeshCylinder(LPDIRECT3DDEVICE9 pDevice);
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshCylinder = NULL;		//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_pTextureMeshCylinder = NULL;		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshCylinder = NULL;		//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posMeshCylinder;								//�ʒu
D3DXVECTOR3 g_rotMeshCylinder;								//����
D3DXMATRIX	g_mtrxWorldMeshCylinder;						//���[���h�}�g���b�N�X
int g_nNumVertexMeshCylinder;								//���_��
int g_nNumIndexMeshCylinder;								//�C���f�b�N�X��
int g_nNumPolygonMeshCylinder;								//�|���S����
//=============================================================================
// ����������
//=============================================================================
void InitMeshCylinder(void)
{
	LPDIRECT3DDEVICE9 pDevice;	// �f�o�C�X�̎擾
	pDevice = GetDevice();	// �f�o�C�X�̎擾

	int nCntH = 0;
	int nCntV = 0;
	int nCntVtx = 0;
	float fPos_X = 0;
	float fPos_Y = 0;
	float fXpos = -X_CYLINDERPOSSIZE;
	float fYpos = Y_CYLINDERPOSSIZE;
	int nCntIdx = 0;
	float fCylinder = 0.0f;
	int  nCylinder = 0;

	g_nNumVertexMeshCylinder = (X_CYLINDERSIZE + 1) * (Y_CYLINDERSIZE + 1);
	g_nNumIndexMeshCylinder = ((X_CYLINDERSIZE + 1) * (Y_CYLINDERSIZE + 1) + ((Y_CYLINDERSIZE - 1) * 2) + (X_CYLINDERSIZE + 1) * (Y_CYLINDERSIZE - 1));
	/*g_nNumPolygonMeshCylinder = ((X_CYLINDERSIZE * 2) * 2) + (Y_CYLINDERPOSSIZE * 2);*/
	//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			MESHCYLINDER_TEXTURENAME,
			&g_pTextureMeshCylinder);
			// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) *  g_nNumVertexMeshCylinder,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshCylinder,
		NULL);

	pDevice->CreateIndexBuffer(sizeof(WORD) * g_nNumIndexMeshCylinder,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,	//2byte�̃f�[�^
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshCylinder,
		NULL);


	VERTEX_3D *pVtx;
	//���_�o�b�t�@�����b�N
	g_pVtxBuffMeshCylinder->Lock(0, 0, (void**)&pVtx, 0);
	
	//���W�𒆐S�ɂ���
	fPos_X = (fXpos * X_CYLINDERSIZE) / 2;
	fPos_Y = (fYpos * Y_CYLINDERSIZE) / 2;

	for (nCntV = 0; nCntV < Y_CYLINDERSIZE + 1; nCntV++)
	{
		for (nCntH = 0; nCntH < X_CYLINDERSIZE + 1; nCntH++)
		{

			//���_���̐ݒ�
			pVtx[(nCntV + nCntH) + nCntVtx].pos.x = sinf(-fCylinder * D3DX_PI) * fXpos;
			pVtx[(nCntV + nCntH) + nCntVtx].pos.y = 20.0f - nCylinder;
			pVtx[(nCntV + nCntH) + nCntVtx].pos.z = cosf(fCylinder * D3DX_PI) * fXpos;

			//�@���̐ݒ�
			pVtx[(nCntV + nCntH) + nCntVtx].nor = D3DXVECTOR3(sinf(fCylinder), cosf(fCylinder), sinf(fCylinder));
			D3DXVec3Normalize(&pVtx[(nCntV + nCntH) + nCntVtx].nor, &pVtx[(nCntV + nCntH) + nCntVtx].nor);
			//���_�J���[
			pVtx[(nCntV + nCntH) + nCntVtx].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//�e�N�X�`�����W
			pVtx[(nCntV + nCntH) + nCntVtx].tex = D3DXVECTOR2(0 + (nCntH * 0.5f), 0 + (nCntV * 0.5f));

			//�p�x1������
			if (fCylinder >= 1.0f)
			{
				fCylinder = -1.0f;
			}
			//X�̕�����/2��1������
			fCylinder += 1.0f / (X_CYLINDERSIZE / 2);

		}
		//���_���̒l��ێ�
		nCntVtx += X_CYLINDERSIZE;
		nCylinder += 20;
		fCylinder = 0.0f;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffMeshCylinder->Unlock();
	
	//�C���f�b�N�X�f�[�^�ւ̃|�C���^
	WORD *pIdx;
	//�C���f�b�N�X�o�b�t�@�����b�N
	g_pIdxBuffMeshCylinder->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCntIdxZ = 0; nCntIdxZ < Y_CYLINDERSIZE; nCntIdxZ++)
	{
		for (int nCntIdxX = 0; nCntIdxX < X_CYLINDERSIZE + 1;nCntIdxX++,nCntIdx++)
		{
			pIdx[0] = nCntIdx + X_CYLINDERSIZE + 1;
			pIdx[1] = nCntIdx;
			//pIdx��2�����炷
			pIdx += 2;
			if (nCntIdxZ < Y_CYLINDERSIZE && nCntIdxX == X_CYLINDERSIZE)
			{
				pIdx[0] = nCntIdx;
				pIdx[1] = nCntIdx + (X_CYLINDERSIZE + 1) + 1;
				//pIdx��2�����炷
				pIdx += 2;
			}
		}
	}

	//�C���f�b�N�X(�r��)

	//for (int nCnt = 0; nCnt < g_nNumIndexMeshCylinder ; nCnt++)
	//{
	//	if (nCnt < X_CYLINDERSIZE + 1)
	//	{
	//		pIdx[0 + (nCnt * 2)] = X_CYLINDERSIZE + 1 + nCnt;
	//		pIdx[1 + (nCnt * 2)] = (X_CYLINDERSIZE + 1 + nCnt) - (X_CYLINDERSIZE + 1);
	//	}
	//	else if (nCnt > X_CYLINDERSIZE + 1)
	//	{
	//		pIdx[0 + (nCnt * 2)] = (X_CYLINDERSIZE  + 1)* 2 + nIdxX;
	//		pIdx[1 + (nCnt * 2)] = X_CYLINDERSIZE  + 1 + nIdxX;
	//		nIdxX++;
	//	}
	//	if (nCnt == X_CYLINDERSIZE)
	//	{
	//		nCnt++;
	//		pIdx[0 + (nCnt * 2)] = X_CYLINDERSIZE;
	//		pIdx[1 + (nCnt * 2)] = X_CYLINDERSIZE + (X_CYLINDERSIZE * X_CYLINDERSIZE);
	//		nIdxY = 1;
	//	}
	//}

	//�C���f�b�N�X�o�b�t�@�����b�N����
	g_pIdxBuffMeshCylinder->Unlock();

	g_posMeshCylinder = D3DXVECTOR3(100.0f,20.0f,0.0f);
}

//=============================================================================
// �I������
//=============================================================================
void UninitMeshCylinder(void)
{	//�e�N�X�`���̔j��
	if (g_pTextureMeshCylinder != NULL)
	{
		g_pTextureMeshCylinder->Release();
		g_pTextureMeshCylinder = NULL;
	}
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffMeshCylinder != NULL)
	{
		g_pVtxBuffMeshCylinder->Release();
		g_pVtxBuffMeshCylinder = NULL;
	}
	// �C���f�b�N�X�o�b�t�@�̊J��
	if (g_pIdxBuffMeshCylinder != NULL)
	{
		g_pIdxBuffMeshCylinder->Release();
		g_pIdxBuffMeshCylinder = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateMeshCylinder(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawMeshCylinder(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtrxWorldMeshCylinder);
	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotMeshCylinder.y, g_rotMeshCylinder.x, g_rotMeshCylinder.z);
	D3DXMatrixMultiply(&g_mtrxWorldMeshCylinder, &g_mtrxWorldMeshCylinder, &mtxRot);
	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_posMeshCylinder.x, g_posMeshCylinder.y, g_posMeshCylinder.z);
	D3DXMatrixMultiply(&g_mtrxWorldMeshCylinder, &g_mtrxWorldMeshCylinder, &mtxTrans);
	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtrxWorldMeshCylinder);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffMeshCylinder, 0, sizeof(VERTEX_3D));
	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(g_pIdxBuffMeshCylinder);
	//���_�t�H�[�}�b�g��ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureMeshCylinder);

	//// �|���S���̕`��
	//pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
	//	0,	//�J�n���钸�_�̃C���f�b�N�X
	//	g_nNumVertexMeshCylinder - 2); //�`�悷��v���~�e�B�u��
	
	//�|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, g_nNumVertexMeshCylinder, 0, g_nNumIndexMeshCylinder - 2);
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexMeshCylinder(LPDIRECT3DDEVICE9 pDevice)
{
	// ���_�o�b�t�@�𐶐�


	// ���_���̐ݒ�

}

