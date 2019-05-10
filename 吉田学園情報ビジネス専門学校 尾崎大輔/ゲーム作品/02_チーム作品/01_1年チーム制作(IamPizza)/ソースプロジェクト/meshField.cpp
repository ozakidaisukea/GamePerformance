//=============================================================================
//
// ���b�V���t�B�[���h���� [meshfield.cpp]
// Author : Meguro Mikiya
//
//=============================================================================
#include "meshField.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexMeshfield(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshfield = NULL;		//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9			g_pTextureMeshfield = NULL;	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshField = NULL;		//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posMeshfield;								//�ʒu
D3DXVECTOR3 g_rotMeshfield;								//����
D3DXMATRIX	g_mtrxWorldMeshfield;						//���[���h�}�g���b�N�X
int g_nNumVertexMeshField;								//���_��
int g_nNumIndexMeshField;								//�C���f�b�N�X��
int g_nNumPolygonMeshField;								//�|���S����
//=============================================================================
// ����������
//=============================================================================
void InitMeshField(void)
{
	LPDIRECT3DDEVICE9 pDevice;	// �f�o�C�X�̎擾
	pDevice = GetDevice();	// �f�o�C�X�̎擾

	int nCntXvtx = 0;
	int nCntZvtx = 0;
	int nCntVtx = 0;
	float fPos_X = 0;
	float fPos_Z = 0;
	float fXpos = -X_POSSIZE;
	float fZpos = Z_POSSIZE;
	//int nIdxX = 0;
	//int nIdxY = 0;
	int nCntIdx = 0;

	g_nNumVertexMeshField = (X_FIELD_SIZE + 1) * (Z_FIELD_SIZE + 1);
	g_nNumIndexMeshField = ((X_FIELD_SIZE + 1) * (Z_FIELD_SIZE + 1) + ((Z_FIELD_SIZE - 1) * 2) + (X_FIELD_SIZE + 1) * (Z_FIELD_SIZE - 1));

	//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			MESHFIELD_TEXTURENAME,
			&g_pTextureMeshfield);
			// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) *  g_nNumVertexMeshField,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshfield,
		NULL);

	pDevice->CreateIndexBuffer(sizeof(WORD) * g_nNumIndexMeshField,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,	//2byte�̃f�[�^
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshField,
		NULL);


	VERTEX_3D *pVtx;
	//���_�o�b�t�@�����b�N
	g_pVtxBuffMeshfield->Lock(0, 0, (void**)&pVtx, 0);
	
	//���W�𒆐S�ɂ���
	fPos_X = (fXpos * X_FIELD_SIZE) / 2;
	fPos_Z = (fZpos * Z_FIELD_SIZE) / 2;

	for (nCntZvtx = 0; nCntZvtx < Z_FIELD_SIZE + 1; nCntZvtx++)
	{
		for (nCntXvtx = 0; nCntXvtx < X_FIELD_SIZE + 1; nCntXvtx++)
		{
			//���_���̐ݒ�
			pVtx[(nCntZvtx + nCntXvtx) + nCntVtx].pos = D3DXVECTOR3(fPos_X + (nCntXvtx * X_POSSIZE), 0.0f, fPos_Z -(nCntZvtx * Z_POSSIZE) );
			//�@���̐ݒ�
			pVtx[(nCntZvtx + nCntXvtx) + nCntVtx].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			//���_�J���[
			pVtx[(nCntZvtx + nCntXvtx )+ nCntVtx].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			//�e�N�X�`�����W
			pVtx[(nCntZvtx + nCntXvtx )+ nCntVtx].tex = D3DXVECTOR2(0 + (nCntXvtx * 0.5f), 0 + (nCntZvtx * 0.5f));
		}
		//���_���̒l��ێ�
		nCntVtx += X_FIELD_SIZE;	
	}

	//���_�o�b�t�@���A�����b�N����

	g_pVtxBuffMeshfield->Unlock();
	
	//�C���f�b�N�X�f�[�^�ւ̃|�C���^
	WORD *pIdx;
	//�C���f�b�N�X�o�b�t�@�����b�N
	g_pIdxBuffMeshField->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCntIdxZ = 0; nCntIdxZ < Z_FIELD_SIZE; nCntIdxZ++)
	{
		for (int nCntIdxX = 0; nCntIdxX < X_FIELD_SIZE + 1;nCntIdxX++,nCntIdx++)
		{
			pIdx[0] = nCntIdx + X_FIELD_SIZE + 1;
			pIdx[1] = nCntIdx;
			//pIdx��2�����炷
			pIdx += 2;
			if (nCntIdxZ < Z_FIELD_SIZE && nCntIdxX == X_FIELD_SIZE)
			{
				pIdx[0] = nCntIdx;
				pIdx[1] = nCntIdx + (X_FIELD_SIZE + 1) + 1;
				//pIdx��2�����炷
				pIdx += 2;
			}
		}
	}

	//�C���f�b�N�X(�r��)

	//for (int nCnt = 0; nCnt < g_nNumIndexMeshField ; nCnt++)
	//{
	//	if (nCnt < X_FIELD_SIZE + 1)
	//	{
	//		pIdx[0 + (nCnt * 2)] = X_FIELD_SIZE + 1 + nCnt;
	//		pIdx[1 + (nCnt * 2)] = (X_FIELD_SIZE + 1 + nCnt) - (X_FIELD_SIZE + 1);
	//	}
	//	else if (nCnt > X_FIELD_SIZE + 1)
	//	{
	//		pIdx[0 + (nCnt * 2)] = (X_FIELD_SIZE  + 1)* 2 + nIdxX;
	//		pIdx[1 + (nCnt * 2)] = X_FIELD_SIZE  + 1 + nIdxX;
	//		nIdxX++;
	//	}
	//	if (nCnt == X_FIELD_SIZE)
	//	{
	//		nCnt++;
	//		pIdx[0 + (nCnt * 2)] = X_FIELD_SIZE;
	//		pIdx[1 + (nCnt * 2)] = X_FIELD_SIZE + (X_FIELD_SIZE * X_FIELD_SIZE);
	//		nIdxY = 1;
	//	}
	//}
	//pIdx[0] = 3;
	//pIdx[1] = 0;
	//pIdx[2] = 4;
	//pIdx[3] = 1;
	//pIdx[4] = 5;
	//pIdx[5] = 2;
	//pIdx[6] = 2;
	//pIdx[7] = 6;
	//pIdx[8] = 6;
	//pIdx[9] = 3;
	//pIdx[10] = 7;
	//pIdx[11] = 4;
	//pIdx[12] = 8;
	//pIdx[13] = 5;
	//�C���f�b�N�X�o�b�t�@�����b�N����

	g_pIdxBuffMeshField->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void UninitMeshField(void)
{	//�e�N�X�`���̔j��
	if (g_pTextureMeshfield != NULL)
	{
		g_pTextureMeshfield->Release();
		g_pTextureMeshfield = NULL;
	}
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffMeshfield != NULL)
	{
		g_pVtxBuffMeshfield->Release();
		g_pVtxBuffMeshfield = NULL;
	}
	// �C���f�b�N�X�o�b�t�@�̊J��
	if (g_pIdxBuffMeshField != NULL)
	{
		g_pIdxBuffMeshField->Release();
		g_pIdxBuffMeshField = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateMeshField(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawMeshField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtrxWorldMeshfield);
	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotMeshfield.y, g_rotMeshfield.x, g_rotMeshfield.z);
	D3DXMatrixMultiply(&g_mtrxWorldMeshfield, &g_mtrxWorldMeshfield, &mtxRot);
	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_posMeshfield.x, g_posMeshfield.y, g_posMeshfield.z);
	D3DXMatrixMultiply(&g_mtrxWorldMeshfield, &g_mtrxWorldMeshfield, &mtxTrans);
	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtrxWorldMeshfield);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffMeshfield, 0, sizeof(VERTEX_3D));
	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(g_pIdxBuffMeshField);
	//���_�t�H�[�}�b�g��ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureMeshfield);

	//// �|���S���̕`��
	//pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
	//	0,	//�J�n���钸�_�̃C���f�b�N�X
	//	g_nNumVertexMeshField - 2); //�`�悷��v���~�e�B�u��
	
	//�|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, g_nNumVertexMeshField, 0, g_nNumIndexMeshField - 2);
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexMeshfield(LPDIRECT3DDEVICE9 pDevice)
{
	// ���_�o�b�t�@�𐶐�


	// ���_���̐ݒ�

}

