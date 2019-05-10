//=============================================================================
//
// ���b�V���t�B�[���h���� [meshField.cpp]
// Author : OZAKI
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS

#define SAVEFILFNAME "tool.txt"

#include<stdio.h>
#include<string.h>

#include "MeshField.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "debugproc.h"
#include "player.h"

// �O���[�o���ϐ�
float g_aHeight[mPolygonZ][mPolygonX];	// �c�̑����Ɖ��̑���

//=============================================================================
//	�ÓI�����o�ϐ��̏�����
//=============================================================================

//=============================================================================
//	�R���X�g���N�^
//=============================================================================
CMeshFiled::CMeshFiled(int nPriarity = 3,OBJTYPE objtype = OBJTYPE_MESHFIELD) : CScene(3, OBJTYPE_MESHFIELD)
{

}

//=============================================================================
//	�f�X�g���N�^
//=============================================================================
CMeshFiled::~CMeshFiled()
{

}


//=============================================================================
//	���[�h
//=============================================================================
void CMeshFiled::Load(void)
{
	FILE *pFile;

	pFile = fopen("tool.bin", "rb");

	// NULL�`�F�b�N
	if (pFile != NULL)
	{
		fread(&g_aHeight[0][0], sizeof(float), (mPolygonZ * mPolygonX), pFile);
		fclose(pFile);
	}

	// ���_���̐ݒ�
	VERTEX_3D *pVtx;						// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntZ = 0; nCntZ < mPolygonZ; nCntZ++)
	{
		for (int nCnrX = 0; nCnrX < mPolygonX; nCnrX++)
		{
			// ���_Z,X��pos��y���
			pVtx->pos.y = g_aHeight[nCntZ][nCnrX];

			pVtx++;
		}
	}
	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

//=============================================================================
//	�A�����[�h
//=============================================================================
void CMeshFiled::Unload(void)
{

}

//=============================================================================
//	����������
//=============================================================================
HRESULT CMeshFiled::Init(void)
{
	//�I�u�W�F�N�g�̎�ނ̐ݒ�
	SetObjtType(CScene::OBJTYPE_MESHFIELD);

	//	�f�o�C�X�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9	pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\bg\\field004.jpg", &m_pTexture);

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * m_nNumVtx
		, D3DUSAGE_WRITEONLY
		, FVF_VRETEX_3D
		, D3DPOOL_MANAGED
		, &m_pVtxBuff
		, NULL);

	// �C���f�b�N�X�o�b�t�@�𐶐�
	pDevice->CreateIndexBuffer(sizeof(WORD) *m_nNumIdx
		, D3DUSAGE_WRITEONLY
		, D3DFMT_INDEX16
		, D3DPOOL_MANAGED
		, &m_pIdxBuff
		, NULL);

	// ���_���̐ݒ�
	VERTEX_3D *pVtx;						// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntVtx = 0; nCntVtx < m_nNumVtx; nCntVtx++)
	{//	���_������

	 // ���_���W�̐ݒ�
		pVtx[nCntVtx].pos = D3DXVECTOR3
			/* (���@/�@2 )�@+�@(���@/�@X�̕������@*�@(���_�����@% (X�̕����� + 1 )))*/
			((-m_fWidth / 2) + (m_fWidth / m_nCutX * (nCntVtx % (m_nCutX + 1)))
				, 0.0f
				/* (���s�@/�@2 )�@-	(���s�@/�@Z�̕������@*�@(���_�����@/ (X�̕����� + 1 )))*/
				, (m_fDepth / 2) - (m_fDepth / m_nCutZ * (nCntVtx / (m_nCutX + 1))));

		// �@���̐ݒ�
		pVtx[nCntVtx].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	}


	for (int nCntVtx = 0; nCntVtx < m_nNumVtx; nCntVtx++)
	{//	���_������

	 // ���_�J���[�̐ݒ�
		pVtx[nCntVtx].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// �e�N�X�`�����W�̐ݒ�
		pVtx[nCntVtx].tex = D3DXVECTOR2(nCntVtx % (m_nCutX + 1) * 1.0f, nCntVtx / (m_nCutX + 1) * 1.0f);
	}

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	// �C���f�b�N�X�f�[�^�̐ݒ�
	WORD *pIdx;									// �C���f�b�N�X�f�[�^�ւ̃|�C���^

	// �C���f�b�N�X�o�b�t�@�����b�N���A�C���f�b�N�X�f�[�^�ւ̃|�C���^���擾
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	// �C���f�b�N�X�̐ݒ�
	int nNumIdx = m_nCutX + 1;					//	���b�V���̉��̕�����
	for (int nCntIdx = 0; nCntIdx < m_nNumIdx; nCntIdx += 2/*�C���f�b�N�X�̒��_2���_�����Z����*/, nNumIdx++/*for���̐��������b�V���̉��̕��������₷*/)
	{//	�C���f�b�N�X������
		if (nNumIdx % (m_nCutX + 1) == 0 && nNumIdx != m_nCutX + 1)
		{	//	���_�̃C���f�b�N�X���[�܂ł�������
			pIdx[nCntIdx] = nNumIdx - (m_nCutX + 2);	/*	���̕������@-�@(���̕����� + 2)*/
			pIdx[nCntIdx + 1] = nNumIdx;				/*	���̕����� */
														//	���_�o�b�t�@�����炷
			nCntIdx += 2;
		}
		pIdx[nCntIdx] = nNumIdx;	/*	���̕����� */
		pIdx[nCntIdx + 1] = nNumIdx - (m_nCutX + 1);	/*	���̕������@-�@(���̕����� + 2)*/
	}

	// �C���f�b�N�X�o�b�t�@���A�����b�N����
	m_pIdxBuff->Unlock();


	return S_OK;
}

//=============================================================================
//	�I������
//=============================================================================
void CMeshFiled::Uninit(void)
{
	//�e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}

	//���_�o�b�t�@�̊J��
	if (m_pVtxBuff != NULL)
	{//	���_�o�b�t�@���g���Ă�����
		m_pVtxBuff->Release();
		// ��ɂ���
		m_pVtxBuff = NULL;
	}

	//�C���f�b�N�X�o�b�t�@�̊J��
	if (m_pIdxBuff != NULL)
	{//	�C���f�b�N�X�o�b�t�@���g���Ă�����
		m_pIdxBuff->Release();

		// �C���f�b�N�X����ɂ���
		m_pIdxBuff = NULL;
	}
	//�������g�̔j��
	CMeshFiled::Release();
}

//=============================================================================
//	�X�V����
//=============================================================================
void CMeshFiled::Update(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = NULL;

	// �}�l�[�W���[���擾
	pDevice = CManager::GetRenderer()->GetDevice();

	// �L�[�{�[�h���擾
	CInputKeyboard *InputKeyboard;
	InputKeyboard = CManager::GetInputKeyboard();

	// �f�o�b�N�\�����擾
	CDebugProc *m_Dubug = CRenderer::GetDebug();

	//���[�J���ϐ�
	VERTEX_3D*pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^�̎擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���[�J���ϐ�
	D3DXVECTOR3 aNor[MAX_NOR];
	int nCntZ2 = 0;
	int nCnt3 = 0;

	for (int nCntZ = 0; nCntZ < mPolygonZ; nCntZ++)
	{
		for (int nCntX = 0; nCntX < mPolygonX; nCntX++)
		{
			D3DXVECTOR3 *pPos0, *pPos1, *pPos2, *pPos3;
			D3DXVECTOR3 Vec0, Vec1, Vec2;
			D3DXVECTOR3 nor;

			// �@���̋���
			pPos0 = &pVtx[nCntZ + nCntX + nCntZ2].pos;
			pPos1 = &pVtx[nCntZ + nCntX + nCntZ2 + (mPolygonX + 1)].pos;
			pPos2 = &pVtx[nCntZ + nCntX + nCntZ2 + (mPolygonX + 1) + 1].pos;
			pPos3 = &pVtx[nCntZ + nCntX + nCntZ2 + 1].pos;

			// �x�N�g���̋���
			Vec0 = *pPos1 - *pPos0;
			Vec1 = *pPos2 - *pPos0;
			Vec2 = *pPos3 - *pPos0;

			// Vec1 Vec0
			D3DXVec3Cross(&nor, &Vec1, &Vec0);
			// ���K��
			D3DXVec3Normalize(&nor, &nor);

			// for���ɓ���������nCntZ2���Q����
			aNor[((nCntZ * 2) + (nCntX * 2)) + nCnt3] = nor;

			// Vec2 Vec1
			D3DXVec3Cross(&nor, &Vec2, &Vec1);
			// ���K��
			D3DXVec3Normalize(&nor, &nor);

			aNor[(nCntZ * 2) + (nCntX * 2) + nCnt3 + 1] = nor;
		}
		nCntZ2 += mPolygonX;
		nCnt3 += (mPolygonX * 2) - 2;
	}

	// �@���� �e���_�̖@�������߂�
	for (int nCntZZ = 0; nCntZZ <= mPolygonZ; nCntZZ++)
	{
		for (int nCntXX = 0; nCntXX <= mPolygonX; nCntXX++)
		{
			// ��[  Z��0
			if (nCntZZ == 0)
			{
				// ���� X��0
				if (nCntXX == 0)
				{
					pVtx[0].nor = (aNor[0] + aNor[1]) / 2;
				}
				// �E�� X��2
				else if (nCntXX == mPolygonX)
				{
					pVtx[mPolygonX].nor = aNor[mPolygonX * 2 - 1];
				}
				// ���� X��1
				else
				{
					pVtx[mPolygonX].nor = (aNor[nCntXX * mPolygonX] + aNor[nCntXX * mPolygonX - 1] + aNor[nCntXX * mPolygonX + 1]) / 3;
				}
			}
			// ���[  Z��3
			else if (nCntZZ == mPolygonZ)
			{
				// X��0
				if (nCntXX == 0)
				{
					pVtx[mPolygonX].nor = aNor[(mPolygonX * 2) * (mPolygonX - 1)];
				}
				// X��2
				else if (nCntXX == mPolygonX)
				{
					pVtx[mPolygonX].nor = (aNor[(mPolygonX * mPolygonZ) * 2 - 1] + aNor[(mPolygonX * mPolygonZ) * 2 - 2]) / 2;

				}
				// X��1
				else
				{
					pVtx[mPolygonX].nor = (aNor[(mPolygonX * 2) * (nCntZZ - 1) + nCntXX * mPolygonX] +
						aNor[(mPolygonX * 2) * (nCntZZ - 1) + nCntXX * mPolygonX - 1] +
						aNor[(mPolygonX * 2) * (nCntZZ - 1) + nCntXX * mPolygonX + 1]) / 3;
				}
			}
			// ���� Z��1
			else
			{
				// X��0
				if (nCntXX == 0)
				{
					pVtx[mPolygonX].nor = ((aNor[(mPolygonX * 2) * (nCntZZ - 1)]) + (aNor[(mPolygonX * 2) * nCntZZ]) + (aNor[(mPolygonX * 2) * nCntZZ] + 1)) / 3;
				}
				// X��2
				else if (nCntXX == mPolygonX)
				{
					pVtx[mPolygonX].nor = (aNor[((mPolygonX * nCntZZ) * 2) - 1] + aNor[((mPolygonX * nCntZZ) * 2) - 2] + aNor[((mPolygonX * nCntZZ + 1) * 2) - 1]) / 3;
				}
				// X��1
				else
				{
					pVtx[mPolygonX].nor = (aNor[(mPolygonX * 2) * (nCntZZ - 1) + (nCntXX * 2 - 1)] +
						aNor[(mPolygonX * 2) * (nCntZZ - 1) + (nCntXX * 2)] +
						aNor[(mPolygonX * 2) * (nCntZZ - 1) + (nCntXX * 2 + 1)] +
						aNor[(mPolygonX * 2) * nCntZZ + (nCntXX * 2 - 1)] +
						aNor[(mPolygonX * 2) * nCntZZ + (nCntXX * 2)] +
						aNor[(mPolygonX * 2) * nCntZZ + (nCntXX * 2 + 1)]) / 6;
				}
			}
		}
	}
	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

#ifdef _DEBUG

	//m_Dubug->Print("ssfsfsf", "\n[ pVtx[0]�@���O ] ", "X", pVtx[0].nor.x, "Y", pVtx[0].nor.y, "Z", pVtx[0].nor.z);
	//m_Dubug->Print("ssfsfsf", "\n[ pVtx[1]�@���P ] ", "X", pVtx[1].nor.x, "Y", pVtx[1].nor.y, "Z", pVtx[1].nor.z);
	//m_Dubug->Print("ssfsfsf", "\n[ pVtx[2]�@���Q ] ", "X", pVtx[2].nor.x, "Y", pVtx[2].nor.y, "Z", pVtx[2].nor.z);
	//m_Dubug->Print("ssfsfsf", "\n[ pVtx[3]�@���R ] ", "X", pVtx[3].nor.x, "Y", pVtx[3].nor.y, "Z", pVtx[3].nor.z);
	//m_Dubug->Print("ssfsfsf", "\n[ pVtx[4]�@���S ] ", "X", pVtx[4].nor.x, "Y", pVtx[4].nor.y, "Z", pVtx[4].nor.z);
	//m_Dubug->Print("ssfsfsf", "\n[ pVtx[5]�@���T ] ", "X", pVtx[5].nor.x, "Y", pVtx[5].nor.y, "Z", pVtx[5].nor.z);
	//m_Dubug->Print("ssfsfsf", "\n[ pVtx[6]�@���U ] ", "X", pVtx[6].nor.x, "Y", pVtx[6].nor.y, "Z", pVtx[6].nor.z);
	//m_Dubug->Print("ssfsfsf", "\n[ pVtx[7]�@���V ] ", "X", pVtx[7].nor.x, "Y", pVtx[7].nor.y, "Z", pVtx[7].nor.z);
	//m_Dubug->Print("ssfsfsf", "\n[ pVtx[8]�@���W ] ", "X", pVtx[8].nor.x, "Y", pVtx[8].nor.y, "Z", pVtx[8].nor.z);
	//m_Dubug->Print("s", "\n");
	//m_Dubug->Print("ssfsfsf", "\n[ pVtx�̈ʒu ] ", "X", pVtx->pos.x, "Y", pVtx->pos.y, "Z", pVtx->pos.z);
#endif
}

//=============================================================================
//	�X�V����
//=============================================================================
void CMeshFiled::Draw(void)
{
	//	�f�o�C�X�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;				// �v�Z�p�}�g���b�N�X

												// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxworld);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxworld, &m_mtxworld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxworld, &m_mtxworld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxworld);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(m_pIdxBuff);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VRETEX_3D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	// �|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_nNumVtx, 0, m_nNumPolygon);
}

//=============================================================================
//�|���S���̐�������
//=============================================================================
CMeshFiled *CMeshFiled::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fDepth, int nCutX, int nCutZ)
{
	CMeshFiled *pSmeshFiled = {};

	if (pSmeshFiled == NULL)
	{//	3D�|���S���̐���
		pSmeshFiled = new CMeshFiled;
		if (pSmeshFiled != NULL)
		{//	3D�|���S�����������ꂽ��
		 // �|���S���̏���������
			pSmeshFiled->m_pos = pos;		//	�ʒu
			pSmeshFiled->m_rot = rot;		//	��]
			pSmeshFiled->m_fWidth = fWidth;	//	��
			pSmeshFiled->m_fDepth = fDepth;	//	���s
			pSmeshFiled->m_nCutX = nCutX;	//	���̕�����
			pSmeshFiled->m_nCutZ = nCutZ;	//	���s�̕�����
			pSmeshFiled->m_nNumVtx = (nCutX + 1) *(nCutZ + 1);					//	�C���f�b�N�X�p�̒��_���̌v�Z
			pSmeshFiled->m_nNumPolygon = nCutX * nCutZ * 2 + (nCutZ - 1) * 4;	//	�|���S�����̃|���S�����̌v�Z
			pSmeshFiled->m_nNumIdx = pSmeshFiled->m_nNumPolygon + 2;			//	�C���f�b�N�X�p�̃|���S�����̌v�Z
			pSmeshFiled->Init();
		}
	}
	return pSmeshFiled;
}

//=============================================================================
//	���ʃe�N�X�`�������蓖�Ă�
//=============================================================================
void CMeshFiled::BindTexture(LPDIRECT3DTEXTURE9		pTexture)
{
	m_pTexture = pTexture;
}

//=============================================================================
//	�n�ʂ̍����̎擾
//=============================================================================
void CMeshFiled::SetHigth(D3DXVECTOR3 pos, float fValue, float fRange)
{
	//// ���_���̐ݒ�
	//VERTEX_3D *pVtx;						// ���_���ւ̃|�C���^

	//// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	//m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//for (int nCntZ = 0; nCntZ < mPolygonZ + 1; nCntZ++)
	//{
	//	for (int nCnrX = 0; nCnrX < mPolygonX + 1; nCnrX++)
	//	{
	//		float fLength = sqrt((pos.x - pVtx->pos.x) * (pos.x - pVtx->pos.x)
	//			+ (pos.z - pVtx->pos.z) * (pos.z - pVtx->pos.z));

	//		// �Ώۂ̒��_�͈͓�
	//		if (fLength < fRange)
	//		{
	//			float fHeight = cosf((D3DX_PI * 0.5f) * (fLength / fRange))* fValue;

	//			pVtx->pos.y += fHeight;

	//		}

	//		pVtx++;
	//	}
	//}

	//// �f�o�b�N�\�����擾
	//CDebugProc *m_Dubug = CRenderer::GetDebug();

	////���_�o�b�t�@���A�����b�N
	//m_pVtxBuff->Unlock();
}

//=============================================================================
//	�Z�[�u
//=============================================================================
void CMeshFiled::Save(void)
{
	FILE *pFile;

	// ���_���̐ݒ�
	VERTEX_3D *pVtx;						// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntZ = 0; nCntZ < mPolygonZ; nCntZ++)
	{
		for (int nCnrX = 0; nCnrX < mPolygonX; nCnrX++)
		{
			// ���_Z,X��pos��y���
			g_aHeight[nCntZ][nCnrX] = pVtx->pos.y;

			pVtx++;
		}
	}
//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

	pFile = fopen("tool.bin", "wb");

	if (pFile != NULL)
	{

		fwrite(&g_aHeight[0][0], sizeof(float), (mPolygonZ * mPolygonX), pFile);
		fclose(pFile);
	}


}