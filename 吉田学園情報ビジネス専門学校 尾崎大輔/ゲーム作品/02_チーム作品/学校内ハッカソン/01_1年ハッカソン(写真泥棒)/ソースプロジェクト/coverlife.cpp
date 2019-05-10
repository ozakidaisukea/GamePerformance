//=============================================================================
//
// �̗͂̃J�o�[���� [coverlife.cpp]
// Author : Jukiya Hayakawa
//
//=============================================================================
#include "coverlife.h"
#include "lifegauge.h"
#include "main.h"
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_COVERLIFE		"data/TEXTURE/GAUGE_COVER.png"		// �ǂݍ��ރe�N�X�`���t�@�C����

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexCoverLife(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureCoverLife = NULL;				// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffCoverLife = NULL;				// ���_�o�b�t�@�ւ̃|�C���^
LifeGauge				g_aCoverLife[MAX_LIFEGAUGE] = {};			// �Q�[�W�̏��

//=============================================================================
// ����������
//=============================================================================
void InitCoverLife(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	float fCoverLifePos = 0;		//�Q�[�W�̈ʒu

									// �l�̏�����
	for (int nCntCoverLife = 0; nCntCoverLife < MAX_LIFEGAUGE; nCntCoverLife++)
	{//�Q�[�W�̐������J��Ԃ�
		g_aCoverLife[nCntCoverLife].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - 125.0f + fCoverLifePos, 50.0f, 0.0f);	//�ʒu�̏�����
		g_aCoverLife[nCntCoverLife].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);								//�F�̏�����
		g_aCoverLife[nCntCoverLife].fWidth = LIFEGAUGE_WIDTH + 30.0f;												//���̏�����
		g_aCoverLife[nCntCoverLife].fHeight = 40;												//�����̏�����
		g_aCoverLife[nCntCoverLife].nType = nCntCoverLife;														//�^�C�v
		fCoverLifePos += 250.0f;
	}

	// ���_���̐ݒ�
	MakeVertexCoverLife(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitCoverLife(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureCoverLife != NULL)
	{
		g_pTextureCoverLife->Release();
		g_pTextureCoverLife = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffCoverLife != NULL)
	{
		g_pVtxBuffCoverLife->Release();
		g_pVtxBuffCoverLife = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateCoverLife(void)
{

}
//=============================================================================
// �^�C�g�����
//=============================================================================
void DrawCoverLife(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffCoverLife, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureCoverLife);

	for (int nCntCoverLife = 0; nCntCoverLife < MAX_LIFEGAUGE; nCntCoverLife++)
	{
		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntCoverLife, 2);
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexCoverLife(LPDIRECT3DDEVICE9 pDevice)
{
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_COVERLIFE,
		&g_pTextureCoverLife);

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_LIFEGAUGE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffCoverLife,
		NULL);

	VERTEX_2D *pVtx;   // ���_���ւ̃|�C���^

					   // ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffCoverLife->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntCoverLife = 0; nCntCoverLife < MAX_LIFEGAUGE; nCntCoverLife++)
	{
		switch (nCntCoverLife)
		{
		case 0:
			// ���_���W
			pVtx[0].pos = D3DXVECTOR3(g_aCoverLife[nCntCoverLife].pos.x - g_aCoverLife[nCntCoverLife].fWidth, g_aCoverLife[nCntCoverLife].pos.y - g_aCoverLife[nCntCoverLife].fHeight, g_aCoverLife[nCntCoverLife].pos.z);
			pVtx[1].pos = D3DXVECTOR3(g_aCoverLife[nCntCoverLife].pos.x, g_aCoverLife[nCntCoverLife].pos.y - g_aCoverLife[nCntCoverLife].fHeight, g_aCoverLife[nCntCoverLife].pos.z);
			pVtx[2].pos = D3DXVECTOR3(g_aCoverLife[nCntCoverLife].pos.x - g_aCoverLife[nCntCoverLife].fWidth, g_aCoverLife[nCntCoverLife].pos.y + g_aCoverLife[nCntCoverLife].fHeight, g_aCoverLife[nCntCoverLife].pos.z);
			pVtx[3].pos = D3DXVECTOR3(g_aCoverLife[nCntCoverLife].pos.x, g_aCoverLife[nCntCoverLife].pos.y + g_aCoverLife[nCntCoverLife].fHeight, g_aCoverLife[nCntCoverLife].pos.z);

			// �e�N�X�`�����W
			pVtx[0].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.0f, 1.0f);
			break;
		case 1:
			// ���_���W
			pVtx[0].pos = D3DXVECTOR3(g_aCoverLife[nCntCoverLife].pos.x, g_aCoverLife[nCntCoverLife].pos.y - g_aCoverLife[nCntCoverLife].fHeight, g_aCoverLife[nCntCoverLife].pos.z);
			pVtx[1].pos = D3DXVECTOR3(g_aCoverLife[nCntCoverLife].pos.x + g_aCoverLife[nCntCoverLife].fWidth, g_aCoverLife[nCntCoverLife].pos.y - g_aCoverLife[nCntCoverLife].fHeight, g_aCoverLife[nCntCoverLife].pos.z);
			pVtx[2].pos = D3DXVECTOR3(g_aCoverLife[nCntCoverLife].pos.x, g_aCoverLife[nCntCoverLife].pos.y + g_aCoverLife[nCntCoverLife].fHeight, g_aCoverLife[nCntCoverLife].pos.z);
			pVtx[3].pos = D3DXVECTOR3(g_aCoverLife[nCntCoverLife].pos.x + g_aCoverLife[nCntCoverLife].fWidth, g_aCoverLife[nCntCoverLife].pos.y + g_aCoverLife[nCntCoverLife].fHeight, g_aCoverLife[nCntCoverLife].pos.z);

			// �e�N�X�`�����W
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
			break;
		}
		// ���_�e�N�X�`��
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// ���_�J���[
		pVtx[0].col = g_aCoverLife[nCntCoverLife].col;
		pVtx[1].col = g_aCoverLife[nCntCoverLife].col;
		pVtx[2].col = g_aCoverLife[nCntCoverLife].col;
		pVtx[3].col = g_aCoverLife[nCntCoverLife].col;

		pVtx += 4;
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffCoverLife->Unlock();
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void SetCoverLife(float fWidth, int nType)
{
	VERTEX_2D *pVtx;   // ���_���ւ̃|�C���^

					   // ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffCoverLife->Lock(0, 0, (void**)&pVtx, 0);

	g_aCoverLife[nType].fWidth -= fWidth;	//���̌��Z����

	for (int nCntCoverLife = 0; nCntCoverLife < MAX_LIFEGAUGE; nCntCoverLife++)
	{//�Q�[�W�̐������J��Ԃ�
		switch (nCntCoverLife)
		{
		case 0:	//�v���C���[�O�̏ꍇ
				// ���_���W
			pVtx[0].pos = D3DXVECTOR3(g_aCoverLife[nCntCoverLife].pos.x - g_aCoverLife[nCntCoverLife].fWidth, g_aCoverLife[nCntCoverLife].pos.y - g_aCoverLife[nCntCoverLife].fHeight, g_aCoverLife[nCntCoverLife].pos.z);
			pVtx[1].pos = D3DXVECTOR3(g_aCoverLife[nCntCoverLife].pos.x, g_aCoverLife[nCntCoverLife].pos.y - g_aCoverLife[nCntCoverLife].fHeight, g_aCoverLife[nCntCoverLife].pos.z);
			pVtx[2].pos = D3DXVECTOR3(g_aCoverLife[nCntCoverLife].pos.x - g_aCoverLife[nCntCoverLife].fWidth, g_aCoverLife[nCntCoverLife].pos.y + g_aCoverLife[nCntCoverLife].fHeight, g_aCoverLife[nCntCoverLife].pos.z);
			pVtx[3].pos = D3DXVECTOR3(g_aCoverLife[nCntCoverLife].pos.x, g_aCoverLife[nCntCoverLife].pos.y + g_aCoverLife[nCntCoverLife].fHeight, g_aCoverLife[nCntCoverLife].pos.z);
			break;
		case 1:	//�v���C���[�P�̏ꍇ
				// ���_���W
			pVtx[0].pos = D3DXVECTOR3(g_aCoverLife[nCntCoverLife].pos.x, g_aCoverLife[nCntCoverLife].pos.y - g_aCoverLife[nCntCoverLife].fHeight, g_aCoverLife[nCntCoverLife].pos.z);
			pVtx[1].pos = D3DXVECTOR3(g_aCoverLife[nCntCoverLife].pos.x + g_aCoverLife[nCntCoverLife].fWidth, g_aCoverLife[nCntCoverLife].pos.y - g_aCoverLife[nCntCoverLife].fHeight, g_aCoverLife[nCntCoverLife].pos.z);
			pVtx[2].pos = D3DXVECTOR3(g_aCoverLife[nCntCoverLife].pos.x, g_aCoverLife[nCntCoverLife].pos.y + g_aCoverLife[nCntCoverLife].fHeight, g_aCoverLife[nCntCoverLife].pos.z);
			pVtx[3].pos = D3DXVECTOR3(g_aCoverLife[nCntCoverLife].pos.x + g_aCoverLife[nCntCoverLife].fWidth, g_aCoverLife[nCntCoverLife].pos.y + g_aCoverLife[nCntCoverLife].fHeight, g_aCoverLife[nCntCoverLife].pos.z);
			break;
		}
		pVtx += 4;
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffCoverLife->Unlock();
}