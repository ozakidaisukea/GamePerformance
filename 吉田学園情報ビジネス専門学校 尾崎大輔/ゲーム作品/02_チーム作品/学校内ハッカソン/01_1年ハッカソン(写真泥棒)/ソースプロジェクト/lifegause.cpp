//=============================================================================
//
// �̗̓Q�[�W���� [lifegauge.cpp]
// Author : Jukiya Hayakawa
//
//=============================================================================
#include "lifegauge.h"
#include "main.h"
#include "input.h"
#include "damagegauge.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_LIFEGAUGE		"data/TEXTURE/LIFE_GAUGE.png"		// �ǂݍ��ރe�N�X�`���t�@�C����

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexLifeGauge(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureGauge = NULL;				// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGauge = NULL;				// ���_�o�b�t�@�ւ̃|�C���^
LifeGauge				g_aLifeGauge[MAX_LIFEGAUGE] = {};			// �Q�[�W�̏��

//=============================================================================
// ����������
//=============================================================================
void InitLifeGauge(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	float fGaugePos = 0;		//�Q�[�W�̈ʒu

	// �l�̏�����
	for (int nCntGauge = 0 ; nCntGauge < MAX_LIFEGAUGE; nCntGauge++)
	{//�Q�[�W�̐������J��Ԃ�
		g_aLifeGauge[nCntGauge].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - 152 + fGaugePos, 50.0f, 0.0f);	//�ʒu�̏�����
		g_aLifeGauge[nCntGauge].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);						//�F�̏�����
		g_aLifeGauge[nCntGauge].fWidth = LIFEGAUGE_WIDTH;											//���̏�����
		g_aLifeGauge[nCntGauge].fHeight = LIFEGAUGE_HEIGHT;											//�����̏�����
		g_aLifeGauge[nCntGauge].nType = nCntGauge;												//�^�C�v
		fGaugePos += 305;
	}

	// ���_���̐ݒ�
	MakeVertexLifeGauge(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitLifeGauge(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureGauge != NULL)
	{
		g_pTextureGauge->Release();
		g_pTextureGauge = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffGauge != NULL)
	{
		g_pVtxBuffGauge->Release();
		g_pVtxBuffGauge = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateLifeGauge(void)
{

}
//=============================================================================
// �^�C�g�����
//=============================================================================
void DrawLifeGauge(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffGauge, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureGauge);

	for (int nCntGauge = 0; nCntGauge < MAX_LIFEGAUGE; nCntGauge++)
	{
		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntGauge, 2);
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexLifeGauge(LPDIRECT3DDEVICE9 pDevice)
{
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_LIFEGAUGE,
		&g_pTextureGauge);

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_LIFEGAUGE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffGauge,
		NULL);

	VERTEX_2D *pVtx;   // ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffGauge->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntGauge = 0; nCntGauge < MAX_LIFEGAUGE; nCntGauge++)
	{
		switch (nCntGauge)
		{
		case 0:
			// ���_���W
			pVtx[0].pos = D3DXVECTOR3(g_aLifeGauge[nCntGauge].pos.x - g_aLifeGauge[nCntGauge].fWidth, g_aLifeGauge[nCntGauge].pos.y - g_aLifeGauge[nCntGauge].fHeight, g_aLifeGauge[nCntGauge].pos.z);
			pVtx[1].pos = D3DXVECTOR3(g_aLifeGauge[nCntGauge].pos.x, g_aLifeGauge[nCntGauge].pos.y - g_aLifeGauge[nCntGauge].fHeight, g_aLifeGauge[nCntGauge].pos.z);
			pVtx[2].pos = D3DXVECTOR3(g_aLifeGauge[nCntGauge].pos.x - g_aLifeGauge[nCntGauge].fWidth, g_aLifeGauge[nCntGauge].pos.y + g_aLifeGauge[nCntGauge].fHeight, g_aLifeGauge[nCntGauge].pos.z);
			pVtx[3].pos = D3DXVECTOR3(g_aLifeGauge[nCntGauge].pos.x, g_aLifeGauge[nCntGauge].pos.y + g_aLifeGauge[nCntGauge].fHeight, g_aLifeGauge[nCntGauge].pos.z);

			// �e�N�X�`�����W
			pVtx[0].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.0f, 1.0f);
			break;
		case 1:
			// ���_���W
			pVtx[0].pos = D3DXVECTOR3(g_aLifeGauge[nCntGauge].pos.x, g_aLifeGauge[nCntGauge].pos.y - g_aLifeGauge[nCntGauge].fHeight, g_aLifeGauge[nCntGauge].pos.z);
			pVtx[1].pos = D3DXVECTOR3(g_aLifeGauge[nCntGauge].pos.x + g_aLifeGauge[nCntGauge].fWidth, g_aLifeGauge[nCntGauge].pos.y - g_aLifeGauge[nCntGauge].fHeight, g_aLifeGauge[nCntGauge].pos.z);
			pVtx[2].pos = D3DXVECTOR3(g_aLifeGauge[nCntGauge].pos.x, g_aLifeGauge[nCntGauge].pos.y + g_aLifeGauge[nCntGauge].fHeight, g_aLifeGauge[nCntGauge].pos.z);
			pVtx[3].pos = D3DXVECTOR3(g_aLifeGauge[nCntGauge].pos.x + g_aLifeGauge[nCntGauge].fWidth, g_aLifeGauge[nCntGauge].pos.y + g_aLifeGauge[nCntGauge].fHeight, g_aLifeGauge[nCntGauge].pos.z);

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
		pVtx[0].col = g_aLifeGauge[nCntGauge].col;
		pVtx[1].col = g_aLifeGauge[nCntGauge].col;
		pVtx[2].col = g_aLifeGauge[nCntGauge].col;
		pVtx[3].col = g_aLifeGauge[nCntGauge].col;

		pVtx += 4;
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffGauge->Unlock();
}

//=============================================================================
// �̗̓Q�[�W�̐ݒu����
//=============================================================================
void SetLifeGauge(float fWidth, int nType)
{
	VERTEX_2D *pVtx;   // ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffGauge->Lock(0, 0, (void**)&pVtx, 0);

	g_aLifeGauge[nType].fWidth -= fWidth;	//���̌��Z����

	for (int nCntGauge = 0; nCntGauge < MAX_LIFEGAUGE; nCntGauge++)
	{//�Q�[�W�̐������J��Ԃ�
		switch (nCntGauge)
		{
		case 0:	//�v���C���[�O�̏ꍇ
			// ���_���W
			pVtx[0].pos = D3DXVECTOR3(g_aLifeGauge[nCntGauge].pos.x - g_aLifeGauge[nCntGauge].fWidth, g_aLifeGauge[nCntGauge].pos.y - g_aLifeGauge[nCntGauge].fHeight, g_aLifeGauge[nCntGauge].pos.z);
			pVtx[1].pos = D3DXVECTOR3(g_aLifeGauge[nCntGauge].pos.x, g_aLifeGauge[nCntGauge].pos.y - g_aLifeGauge[nCntGauge].fHeight, g_aLifeGauge[nCntGauge].pos.z);
			pVtx[2].pos = D3DXVECTOR3(g_aLifeGauge[nCntGauge].pos.x - g_aLifeGauge[nCntGauge].fWidth, g_aLifeGauge[nCntGauge].pos.y + g_aLifeGauge[nCntGauge].fHeight, g_aLifeGauge[nCntGauge].pos.z);
			pVtx[3].pos = D3DXVECTOR3(g_aLifeGauge[nCntGauge].pos.x, g_aLifeGauge[nCntGauge].pos.y + g_aLifeGauge[nCntGauge].fHeight, g_aLifeGauge[nCntGauge].pos.z);
			break;
		case 1:	//�v���C���[�P�̏ꍇ
			// ���_���W
			pVtx[0].pos = D3DXVECTOR3(g_aLifeGauge[nCntGauge].pos.x, g_aLifeGauge[nCntGauge].pos.y - g_aLifeGauge[nCntGauge].fHeight, g_aLifeGauge[nCntGauge].pos.z);
			pVtx[1].pos = D3DXVECTOR3(g_aLifeGauge[nCntGauge].pos.x + g_aLifeGauge[nCntGauge].fWidth, g_aLifeGauge[nCntGauge].pos.y - g_aLifeGauge[nCntGauge].fHeight, g_aLifeGauge[nCntGauge].pos.z);
			pVtx[2].pos = D3DXVECTOR3(g_aLifeGauge[nCntGauge].pos.x, g_aLifeGauge[nCntGauge].pos.y + g_aLifeGauge[nCntGauge].fHeight, g_aLifeGauge[nCntGauge].pos.z);
			pVtx[3].pos = D3DXVECTOR3(g_aLifeGauge[nCntGauge].pos.x + g_aLifeGauge[nCntGauge].fWidth, g_aLifeGauge[nCntGauge].pos.y + g_aLifeGauge[nCntGauge].fHeight, g_aLifeGauge[nCntGauge].pos.z);
			break;
		}
		SetDamageGaugeState(STATE_MINUS, nCntGauge, g_aLifeGauge[nCntGauge].fWidth);
		pVtx += 4;
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffGauge->Unlock();
}