//=============================================================================
//
// �Ǐ��� [wall.cpp]
// Author : OZAKI
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS

#define SAVEFILFNAME "tool.txt"

#include<stdio.h>
#include<string.h>

#include "wall.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "debugproc.h"
#include "player.h"

// �O���[�o���ϐ�
float g_aHeight2[mPolygonY][mPolygonX];	// �c�̑����Ɖ��̑���

//=============================================================================
//	�R���X�g���N�^
//=============================================================================
CWall::CWall(int nPriarity = 3, OBJTYPE objtype = OBJTYPE_WALL) : CScene(3, OBJTYPE_WALL)
{
	m_pos = D3DXVECTOR3(0, 0, 0);
	m_rot = D3DXVECTOR3(0, 0, 0);
}

//=============================================================================
//	�f�X�g���N�^
//=============================================================================
CWall::~CWall()
{

}

//=============================================================================
//	���[�h
//=============================================================================
void CWall::Load(void)
{
	FILE *pFile;

	pFile = fopen("tool.bin", "rb");

	// NULL�`�F�b�N
	if (pFile != NULL)
	{
		fread(&g_aHeight2[0][0], sizeof(float), (mPolygonY * mPolygonX), pFile);
		fclose(pFile);
	}

	// ���_���̐ݒ�
	VERTEX_3D *pVtx;						// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntY = 0; nCntY < mPolygonY; nCntY++)
	{
		for (int nCnrX = 0; nCnrX < mPolygonX; nCnrX++)
		{
			// ���_Z,X��pos��y���
			pVtx->pos.y = g_aHeight2[nCntY][nCnrX];

			pVtx++;
		}
	}
	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

//=============================================================================
//	�A�����[�h
//=============================================================================
void CWall::Unload(void)
{

}

//=============================================================================
//	����������
//=============================================================================
HRESULT CWall::Init(void)
{
	//�I�u�W�F�N�g�̎�ނ̐ݒ�
	SetObjtType(CScene::OBJTYPE_WALL);

	//	�f�o�C�X�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9	pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\bg\\sora.jpg", &m_pTexture);

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
				/* (���s�@/�@2 )�@-	(���s�@/�@Y�̕������@*�@(���_�����@/ (X�̕����� + 1 )))*/
				, (m_fDepth / 2) - (m_fDepth / m_nCutY * (nCntVtx / (m_nCutX + 1))));

		// �@���̐ݒ�
		pVtx[nCntVtx].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
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
void CWall::Uninit(void)
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
	CWall::Release();
}

//=============================================================================
//	�X�V����
//=============================================================================
void CWall::Update(void)
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
	int nCntY2 = 0;
	int nCnt3 = 0;

	for (int nCntY = 0; nCntY < mPolygonY; nCntY++)
	{
		for (int nCntX = 0; nCntX < mPolygonX; nCntX++)
		{
			D3DXVECTOR3 *pPos0, *pPos1, *pPos2, *pPos3;
			D3DXVECTOR3 Vec0, Vec1, Vec2;
			D3DXVECTOR3 nor;

			// �@���̋���
			pPos0 = &pVtx[nCntY + nCntX + nCntY2].pos;
			pPos1 = &pVtx[nCntY + nCntX + nCntY2 + (mPolygonX + 1)].pos;
			pPos2 = &pVtx[nCntY + nCntX + nCntY2 + (mPolygonX + 1) + 1].pos;
			pPos3 = &pVtx[nCntY + nCntX + nCntY2 + 1].pos;

			// �x�N�g���̋���
			Vec0 = *pPos1 - *pPos0;
			Vec1 = *pPos2 - *pPos0;
			Vec2 = *pPos3 - *pPos0;

			// Vec1 Vec0
			D3DXVec3Cross(&nor, &Vec1, &Vec0);
			// ���K��
			D3DXVec3Normalize(&nor, &nor);

			// for���ɓ���������nCntY2���Q����
			aNor[((nCntY * 2) + (nCntX * 2)) + nCnt3] = nor;

			// Vec2 Vec1
			D3DXVec3Cross(&nor, &Vec2, &Vec1);
			// ���K��
			D3DXVec3Normalize(&nor, &nor);

			aNor[(nCntY * 2) + (nCntX * 2) + nCnt3 + 1] = nor;
		}
		nCntY2 += mPolygonX;
		nCnt3 += (mPolygonX * 2) - 2;
	}

	// �@���� �e���_�̖@�������߂�
	for (int nCntYY = 0; nCntYY <= mPolygonY; nCntYY++)
	{
		for (int nCntXX = 0; nCntXX <= mPolygonX; nCntXX++)
		{
			// ��[  Z��0
			if (nCntYY == 0)
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
			else if (nCntYY == mPolygonY)
			{
				// X��0
				if (nCntXX == 0)
				{
					pVtx[mPolygonX].nor = aNor[(mPolygonX * 2) * (mPolygonX - 1)];
				}
				// X��2
				else if (nCntXX == mPolygonX)
				{
					pVtx[mPolygonX].nor = (aNor[(mPolygonX * mPolygonY) * 2 - 1] + aNor[(mPolygonX * mPolygonY) * 2 - 2]) / 2;

				}
				// X��1
				else
				{
					pVtx[mPolygonX].nor = (aNor[(mPolygonX * 2) * (nCntYY - 1) + nCntXX * mPolygonX] +
						aNor[(mPolygonX * 2) * (nCntYY - 1) + nCntXX * mPolygonX - 1] +
						aNor[(mPolygonX * 2) * (nCntYY - 1) + nCntXX * mPolygonX + 1]) / 3;
				}
			}
			// ���� Z��1
			else
			{
				// X��0
				if (nCntXX == 0)
				{
					pVtx[mPolygonX].nor = ((aNor[(mPolygonX * 2) * (nCntYY - 1)]) + (aNor[(mPolygonX * 2) * nCntYY]) + (aNor[(mPolygonX * 2) * nCntYY] + 1)) / 3;
				}
				// X��2
				else if (nCntXX == mPolygonX)
				{
					pVtx[mPolygonX].nor = (aNor[((mPolygonX * nCntYY) * 2) - 1] + aNor[((mPolygonX * nCntYY) * 2) - 2] + aNor[((mPolygonX * nCntYY + 1) * 2) - 1]) / 3;
				}
				// X��1
				else
				{
					pVtx[mPolygonX].nor = (aNor[(mPolygonX * 2) * (nCntYY - 1) + (nCntXX * 2 - 1)] +
						aNor[(mPolygonX * 2) * (nCntYY - 1) + (nCntXX * 2)] +
						aNor[(mPolygonX * 2) * (nCntYY - 1) + (nCntXX * 2 + 1)] +
						aNor[(mPolygonX * 2) * nCntYY + (nCntXX * 2 - 1)] +
						aNor[(mPolygonX * 2) * nCntYY + (nCntXX * 2)] +
						aNor[(mPolygonX * 2) * nCntYY + (nCntXX * 2 + 1)]) / 6;
				}
			}
		}
	}
	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

}

//=============================================================================
//	�X�V����
//=============================================================================
void CWall::Draw(void)
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
CWall *CWall::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fDepth, int nCutX, int nCutY)
{
	CWall *pSmeshFiled = {};

	if (pSmeshFiled == NULL)
	{//	3D�|���S���̐���
		pSmeshFiled = new CWall;
		if (pSmeshFiled != NULL)
		{//	3D�|���S�����������ꂽ��
		 // �|���S���̏���������
			pSmeshFiled->m_pos = pos;		//	�ʒu
			pSmeshFiled->m_rot = rot;		//	��]
			pSmeshFiled->m_fWidth = fWidth;	//	��
			pSmeshFiled->m_fDepth = fDepth;	//	���s
			pSmeshFiled->m_nCutX = nCutX;	//	���̕�����
			pSmeshFiled->m_nCutY = nCutY;	//	���s�̕�����
			pSmeshFiled->m_nNumVtx = (nCutX + 1) *(nCutY + 1);					//	�C���f�b�N�X�p�̒��_���̌v�Z
			pSmeshFiled->m_nNumPolygon = nCutX * nCutY * 2 + (nCutY - 1) * 4;	//	�|���S�����̃|���S�����̌v�Z
			pSmeshFiled->m_nNumIdx = pSmeshFiled->m_nNumPolygon + 2;			//	�C���f�b�N�X�p�̃|���S�����̌v�Z
			pSmeshFiled->Init();
		}
	}
	return pSmeshFiled;
}

//=============================================================================
//	���ʃe�N�X�`�������蓖�Ă�
//=============================================================================
void CWall::BindTexture(LPDIRECT3DTEXTURE9		pTexture)
{
	m_pTexture = pTexture;
}

//=============================================================================
//	�n�ʂ̍����̎擾
//=============================================================================
void CWall::SetHigth(D3DXVECTOR3 pos, float fValue, float fRange)
{
	//	CPlayer::GetPlayerpos;

	// ���_���̐ݒ�
	VERTEX_3D *pVtx;						// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntY = 0; nCntY < mPolygonY + 1; nCntY++)
	{
		for (int nCnrX = 0; nCnrX < mPolygonX + 1; nCnrX++)
		{
			float fLength = sqrtf((pos.x - pVtx->pos.x) * (pos.x - pVtx->pos.x)
				+ (pos.y - pVtx->pos.y) * (pos.y - pVtx->pos.y));

			// �Ώۂ̒��_�͈͓�
			if (fLength < fRange)
			{
				float fHeight = cosf((D3DX_PI * 0.5f) * (fLength / fRange))* fValue;

				pVtx->pos.y += fHeight;

			}

			pVtx++;
		}
	}

	// �f�o�b�N�\�����擾
	CDebugProc *m_Dubug = CRenderer::GetDebug();

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

//=============================================================================
//	�Z�[�u
//=============================================================================
void CWall::Save(void)
{
	FILE *pFile;

	// ���_���̐ݒ�
	VERTEX_3D *pVtx;						// ���_���ւ̃|�C���^

											// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntY = 0; nCntY < mPolygonY; nCntY++)
	{
		for (int nCnrX = 0; nCnrX < mPolygonX; nCnrX++)
		{
			// ���_Z,X��pos��y���
			g_aHeight2[nCntY][nCnrX] = pVtx->pos.y;

			pVtx++;
		}
	}
	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

	pFile = fopen("tool.bin", "wb");

	if (pFile != NULL)
	{

		fwrite(&g_aHeight2[0][0], sizeof(float), (mPolygonY * mPolygonX), pFile);
		fclose(pFile);
	}


}