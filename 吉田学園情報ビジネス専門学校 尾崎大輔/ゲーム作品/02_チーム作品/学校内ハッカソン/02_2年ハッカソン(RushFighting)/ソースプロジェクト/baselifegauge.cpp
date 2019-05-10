//=============================================================================
//
// �̗͂̓y��̃Q�[�W���� [lifegauge.cpp]
// Author : Jukiya Hayakawa
//
//=============================================================================
#include "baselifegauge.h"
#include "lifegauge.h"
#include "main.h"
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_BASELIFEGAUGE		"data/TEXTURE/GAUGE_BASE.png"		// �ǂݍ��ރe�N�X�`���t�@�C����

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexBaseLifeGauge(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureBaseGauge = NULL;				// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBaseGauge = NULL;				// ���_�o�b�t�@�ւ̃|�C���^
LifeGauge				g_aBaseLifeGauge[MAX_LIFEGAUGE] = {};			// �Q�[�W�̏��

//=============================================================================
// ����������
//=============================================================================
void InitBaseLifeGauge(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	float fBaseGaugePos = 0;		//�Q�[�W�̈ʒu

								// �l�̏�����
	for (int nCntBaseGauge = 0; nCntBaseGauge < MAX_LIFEGAUGE; nCntBaseGauge++)
	{//�Q�[�W�̐������J��Ԃ�
		g_aBaseLifeGauge[nCntBaseGauge].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - 100.0f + fBaseGaugePos, 50.0f, 0.0f);	//�ʒu�̏�����
		g_aBaseLifeGauge[nCntBaseGauge].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);								//�F�̏�����
		g_aBaseLifeGauge[nCntBaseGauge].fWidth = LIFEGAUGE_WIDTH + 40;												//���̏�����
		g_aBaseLifeGauge[nCntBaseGauge].fHeight = LIFEGAUGE_HEIGHT + 2;												//�����̏�����
		g_aBaseLifeGauge[nCntBaseGauge].nType = nCntBaseGauge;														//�^�C�v
		fBaseGaugePos += 200.0f;
	}

	// ���_���̐ݒ�
	MakeVertexBaseLifeGauge(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitBaseLifeGauge(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureBaseGauge != NULL)
	{
		g_pTextureBaseGauge->Release();
		g_pTextureBaseGauge = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffBaseGauge != NULL)
	{
		g_pVtxBuffBaseGauge->Release();
		g_pVtxBuffBaseGauge = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBaseLifeGauge(void)
{

}
//=============================================================================
// �^�C�g�����
//=============================================================================
void DrawBaseLifeGauge(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffBaseGauge, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureBaseGauge);

	for (int nCntBaseGauge = 0; nCntBaseGauge < MAX_LIFEGAUGE; nCntBaseGauge++)
	{
		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntBaseGauge, 2);
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexBaseLifeGauge(LPDIRECT3DDEVICE9 pDevice)
{
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_BASELIFEGAUGE,
		&g_pTextureBaseGauge);

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_LIFEGAUGE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBaseGauge,
		NULL);

	VERTEX_2D *pVtx;   // ���_���ւ̃|�C���^

					   // ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBaseGauge->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBaseGauge = 0; nCntBaseGauge < MAX_LIFEGAUGE; nCntBaseGauge++)
	{
		switch (nCntBaseGauge)
		{
		case 0:
			// ���_���W
			pVtx[0].pos = D3DXVECTOR3(g_aBaseLifeGauge[nCntBaseGauge].pos.x - g_aBaseLifeGauge[nCntBaseGauge].fWidth, g_aBaseLifeGauge[nCntBaseGauge].pos.y - g_aBaseLifeGauge[nCntBaseGauge].fHeight, g_aBaseLifeGauge[nCntBaseGauge].pos.z);
			pVtx[1].pos = D3DXVECTOR3(g_aBaseLifeGauge[nCntBaseGauge].pos.x, g_aBaseLifeGauge[nCntBaseGauge].pos.y - g_aBaseLifeGauge[nCntBaseGauge].fHeight, g_aBaseLifeGauge[nCntBaseGauge].pos.z);
			pVtx[2].pos = D3DXVECTOR3(g_aBaseLifeGauge[nCntBaseGauge].pos.x - g_aBaseLifeGauge[nCntBaseGauge].fWidth, g_aBaseLifeGauge[nCntBaseGauge].pos.y + g_aBaseLifeGauge[nCntBaseGauge].fHeight, g_aBaseLifeGauge[nCntBaseGauge].pos.z);
			pVtx[3].pos = D3DXVECTOR3(g_aBaseLifeGauge[nCntBaseGauge].pos.x, g_aBaseLifeGauge[nCntBaseGauge].pos.y + g_aBaseLifeGauge[nCntBaseGauge].fHeight, g_aBaseLifeGauge[nCntBaseGauge].pos.z);

			// �e�N�X�`�����W
			pVtx[0].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.0f, 1.0f);
			break;
		case 1:
			// ���_���W
			pVtx[0].pos = D3DXVECTOR3(g_aBaseLifeGauge[nCntBaseGauge].pos.x, g_aBaseLifeGauge[nCntBaseGauge].pos.y - g_aBaseLifeGauge[nCntBaseGauge].fHeight, g_aBaseLifeGauge[nCntBaseGauge].pos.z);
			pVtx[1].pos = D3DXVECTOR3(g_aBaseLifeGauge[nCntBaseGauge].pos.x + g_aBaseLifeGauge[nCntBaseGauge].fWidth, g_aBaseLifeGauge[nCntBaseGauge].pos.y - g_aBaseLifeGauge[nCntBaseGauge].fHeight, g_aBaseLifeGauge[nCntBaseGauge].pos.z);
			pVtx[2].pos = D3DXVECTOR3(g_aBaseLifeGauge[nCntBaseGauge].pos.x, g_aBaseLifeGauge[nCntBaseGauge].pos.y + g_aBaseLifeGauge[nCntBaseGauge].fHeight, g_aBaseLifeGauge[nCntBaseGauge].pos.z);
			pVtx[3].pos = D3DXVECTOR3(g_aBaseLifeGauge[nCntBaseGauge].pos.x + g_aBaseLifeGauge[nCntBaseGauge].fWidth, g_aBaseLifeGauge[nCntBaseGauge].pos.y + g_aBaseLifeGauge[nCntBaseGauge].fHeight, g_aBaseLifeGauge[nCntBaseGauge].pos.z);

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
		pVtx[0].col = g_aBaseLifeGauge[nCntBaseGauge].col;
		pVtx[1].col = g_aBaseLifeGauge[nCntBaseGauge].col;
		pVtx[2].col = g_aBaseLifeGauge[nCntBaseGauge].col;
		pVtx[3].col = g_aBaseLifeGauge[nCntBaseGauge].col;

		pVtx += 4;
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBaseGauge->Unlock();
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void SetBaseLifeGauge(float fWidth, int nType)
{
	VERTEX_2D *pVtx;   // ���_���ւ̃|�C���^

					   // ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBaseGauge->Lock(0, 0, (void**)&pVtx, 0);

	g_aBaseLifeGauge[nType].fWidth -= fWidth;	//���̌��Z����

	for (int nCntBaseGauge = 0; nCntBaseGauge < MAX_LIFEGAUGE; nCntBaseGauge++)
	{//�Q�[�W�̐������J��Ԃ�
		switch (nCntBaseGauge)
		{
		case 0:	//�v���C���[�O�̏ꍇ
				// ���_���W
			pVtx[0].pos = D3DXVECTOR3(g_aBaseLifeGauge[nCntBaseGauge].pos.x - g_aBaseLifeGauge[nCntBaseGauge].fWidth, g_aBaseLifeGauge[nCntBaseGauge].pos.y - g_aBaseLifeGauge[nCntBaseGauge].fHeight, g_aBaseLifeGauge[nCntBaseGauge].pos.z);
			pVtx[1].pos = D3DXVECTOR3(g_aBaseLifeGauge[nCntBaseGauge].pos.x, g_aBaseLifeGauge[nCntBaseGauge].pos.y - g_aBaseLifeGauge[nCntBaseGauge].fHeight, g_aBaseLifeGauge[nCntBaseGauge].pos.z);
			pVtx[2].pos = D3DXVECTOR3(g_aBaseLifeGauge[nCntBaseGauge].pos.x - g_aBaseLifeGauge[nCntBaseGauge].fWidth, g_aBaseLifeGauge[nCntBaseGauge].pos.y + g_aBaseLifeGauge[nCntBaseGauge].fHeight, g_aBaseLifeGauge[nCntBaseGauge].pos.z);
			pVtx[3].pos = D3DXVECTOR3(g_aBaseLifeGauge[nCntBaseGauge].pos.x, g_aBaseLifeGauge[nCntBaseGauge].pos.y + g_aBaseLifeGauge[nCntBaseGauge].fHeight, g_aBaseLifeGauge[nCntBaseGauge].pos.z);
			break;
		case 1:	//�v���C���[�P�̏ꍇ
				// ���_���W
			pVtx[0].pos = D3DXVECTOR3(g_aBaseLifeGauge[nCntBaseGauge].pos.x, g_aBaseLifeGauge[nCntBaseGauge].pos.y - g_aBaseLifeGauge[nCntBaseGauge].fHeight, g_aBaseLifeGauge[nCntBaseGauge].pos.z);
			pVtx[1].pos = D3DXVECTOR3(g_aBaseLifeGauge[nCntBaseGauge].pos.x + g_aBaseLifeGauge[nCntBaseGauge].fWidth, g_aBaseLifeGauge[nCntBaseGauge].pos.y - g_aBaseLifeGauge[nCntBaseGauge].fHeight, g_aBaseLifeGauge[nCntBaseGauge].pos.z);
			pVtx[2].pos = D3DXVECTOR3(g_aBaseLifeGauge[nCntBaseGauge].pos.x, g_aBaseLifeGauge[nCntBaseGauge].pos.y + g_aBaseLifeGauge[nCntBaseGauge].fHeight, g_aBaseLifeGauge[nCntBaseGauge].pos.z);
			pVtx[3].pos = D3DXVECTOR3(g_aBaseLifeGauge[nCntBaseGauge].pos.x + g_aBaseLifeGauge[nCntBaseGauge].fWidth, g_aBaseLifeGauge[nCntBaseGauge].pos.y + g_aBaseLifeGauge[nCntBaseGauge].fHeight, g_aBaseLifeGauge[nCntBaseGauge].pos.z);
			break;
		}
		pVtx += 4;
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBaseGauge->Unlock();
}