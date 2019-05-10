//=============================================================================
//
// �������Ԃ̏��� [score.cpp]
// Author : Shun Yokomichi
//
//=============================================================================
#include "gauge.h"
#include "game.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_GAUGE000		"data/TEXTURE/PizzaMetre000.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define TEXTURE_GAUGE001		"data/TEXTURE/PizzaHot000.png"		// �ǂݍ��ރe�N�X�`���t�F�C����
#define TEXTURE_GAUGE002		"data/TEXTURE/PizzaCool000.png"		// �ǂݍ��ރe�N�X�`���t�F�C����
#define TEXTURE_GAUGE003		"data/TEXTURE/memory.png"			// �ǂݍ��ރe�N�X�`���t�F�C����
#define MAX_GAUGE				(4)									// �Q�[�W�̍ő吔	
#define REDUCE_GAUGE			(0.08f)								// �Q�[�W�̌����(���t���[��)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexGauge(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureGauge[MAX_GAUGE] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGauge = NULL;				// ���_�o�b�t�@�ւ̃|�C���^
float g_fGauge;												// �Q�[�W�̒l
float g_fGaugeColR;											// �Q�[�W�̐F(��)
float g_fGaugeColG;											// �Q�[�W�̐F(��)
float g_fGaugeColB;											// �Q�[�W�̐F(��)
 
//=============================================================================
// ����������
//=============================================================================
void InitGauge(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �Q�[�W�̏�����
	g_fGauge = 320.0f;
	g_fGaugeColR = 1.0f;
	g_fGaugeColG = 0.0f;
	g_fGaugeColB = 0.0f;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_GAUGE000, &g_pTextureGauge[0]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_GAUGE001, &g_pTextureGauge[1]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_GAUGE002, &g_pTextureGauge[2]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_GAUGE003, &g_pTextureGauge[3]);

	// ���_���̍쐬
	MakeVertexGauge(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitGauge(void)
{
	for (int nCntGauge = 0; nCntGauge < MAX_GAUGE; nCntGauge++)
	{
		// �e�N�X�`���̊J��
		if (g_pTextureGauge[nCntGauge] != NULL)
		{
			g_pTextureGauge[nCntGauge]->Release();
			g_pTextureGauge[nCntGauge] = NULL;
		}
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
void UpdateGauge(void)
{
	// ���_���̍쐬
	VERTEX_2D*pVtx;			//���_���ւ̃|�C���^
	PLAYER *pPlayer = GetPlayer();

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffGauge->Lock(0, 0, (void**)&pVtx, 0);
	
	if(g_fGauge >= 320.0f && g_fGauge <= 580.0f)
	{
		g_fGauge += REDUCE_GAUGE;

		pVtx[0].pos = D3DXVECTOR3(1170.0f, g_fGauge, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(1200.0f, g_fGauge, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(1170.0f, 580.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(1200.0f, 580.0f, 0.0f);
	}

	// �F�̕ω�(�Q�[�W)
	if (g_fGauge >= 320.0f && g_fGauge <= 381.9f)
	{
		// �Q�[�W(�ԐF)
		pVtx[0].col = D3DXCOLOR(g_fGaugeColR, 0.0f, 0.0f, 0.8f);
		pVtx[1].col = D3DXCOLOR(g_fGaugeColR, 0.0f, 0.0f, 0.8f);
		pVtx[2].col = D3DXCOLOR(g_fGaugeColR, 0.0f, 0.0f, 0.8f);
		pVtx[3].col = D3DXCOLOR(g_fGaugeColR, 0.0f, 0.0f, 0.8f);
	}
	else if (g_fGauge >= 381.9f && g_fGauge <= 444.9f)
	{
		// �Q�[�W(�I�����W�F)
		g_fGaugeColG += 0.004f;

		if (g_fGaugeColG >= 0.5f)
		{
			g_fGaugeColG = 0.5f;
		}

		pVtx[0].col = D3DXCOLOR(g_fGaugeColR, g_fGaugeColG, 0.0f, 0.8f);
		pVtx[1].col = D3DXCOLOR(g_fGaugeColR, g_fGaugeColG, 0.0f, 0.8f);
		pVtx[2].col = D3DXCOLOR(g_fGaugeColR, g_fGaugeColG, 0.0f, 0.8f);
		pVtx[3].col = D3DXCOLOR(g_fGaugeColR, g_fGaugeColG, 0.0f, 0.8f);
	}
	else if (g_fGauge >= 444.9f && g_fGauge <= 512.9f)
	{	// �Q�[�W(���F)
		g_fGaugeColB += 0.008f;
		g_fGaugeColR -= 0.008f;
		g_fGaugeColG += 0.002f;

		if (g_fGaugeColB >= 0.8f)
		{
			g_fGaugeColB = 0.8f;
		}
		if (g_fGaugeColG >= 0.5f)
		{
			g_fGaugeColG = 0.5f;
		}
		if (g_fGaugeColR <= 0.3f)
		{
			g_fGaugeColR = 0.0f;
		}

		pVtx[0].col = D3DXCOLOR(g_fGaugeColR, g_fGaugeColG, g_fGaugeColB, 0.8f);
		pVtx[1].col = D3DXCOLOR(g_fGaugeColR, g_fGaugeColG, g_fGaugeColB, 0.8f);
		pVtx[2].col = D3DXCOLOR(g_fGaugeColR, g_fGaugeColG, g_fGaugeColB, 0.8f);
		pVtx[3].col = D3DXCOLOR(g_fGaugeColR, g_fGaugeColG, g_fGaugeColB, 0.8f);
	}
	else
	{	// �Q�[�W(�F)
		g_fGaugeColB += 0.008f;
		g_fGaugeColR -= 0.008f;
		g_fGaugeColG -= 0.002f;

		if (g_fGaugeColB >= 1.0f)
		{
			g_fGaugeColB = 1.0f;
		}
		if (g_fGaugeColG <= 0.0f)
		{
			g_fGaugeColG = 0.0f;
		}
		if (g_fGaugeColR <= 0.0f)
		{
			g_fGaugeColR = 0.0f;
		}

		pVtx[0].col = D3DXCOLOR(g_fGaugeColR, g_fGaugeColG, g_fGaugeColB, 0.8f);
		pVtx[1].col = D3DXCOLOR(g_fGaugeColR, g_fGaugeColG, g_fGaugeColB, 0.8f);
		pVtx[2].col = D3DXCOLOR(g_fGaugeColR, g_fGaugeColG, g_fGaugeColB, 0.8f);
		pVtx[3].col = D3DXCOLOR(g_fGaugeColR, g_fGaugeColG, g_fGaugeColB, 0.8f);
	}

	if (g_fGauge >= 580.0f)
	{	// Pizza���[�h�̃Q�[�W�����ꂽ�ꍇ(GAMEOVER)
		SetGameState(GAMESTATE_GAMEOVER);
		pPlayer->state = PLAYERSTATE_GAUGEZERO;
		pPlayer->PizzaMode = PLAYERPIZZA_HUMAN;
		SetGaugeState(false);
	}

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffGauge->Unlock();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawGaugee(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffGauge, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �|���S���̕`��
	for (int nCntGauge = 0; nCntGauge < MAX_GAUGE; nCntGauge++)
	{// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureGauge[nCntGauge]);
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntGauge * 4, 2);
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexGauge(LPDIRECT3DDEVICE9 pDevice)
{

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_GAUGE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffGauge,
		NULL);

	// ���_���̍쐬
	VERTEX_2D*pVtx;			//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffGauge->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntGauge = 0; nCntGauge < MAX_GAUGE; nCntGauge++)
	{
		if (nCntGauge == 0)
		{	// �Q�[�W
			//���_�ݒ�
			pVtx[0].pos = D3DXVECTOR3(1170.0f, g_fGauge, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(1200.0f, g_fGauge, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(1170.0f, 580.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(1200.0f, 580.0f, 0.0f);

			//���_�J���[�ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.8f);
			pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.8f);
			pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.8f);
			pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.8f);
		}
		else if(nCntGauge == 1)
		{	// HotPizza
			//���_�ݒ�
			pVtx[0].pos = D3DXVECTOR3(1153.0f, 250.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(1220.0f, 250.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(1153.0f, 300.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(1220.0f, 300.0f, 0.0f);
			//���_�J���[�ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
		else if (nCntGauge == 2)
		{	// CoolPizza
			//���_�ݒ�
			pVtx[0].pos = D3DXVECTOR3(1153.0f, 600.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(1220.0f, 600.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(1153.0f, 650.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(1220.0f, 650.0f, 0.0f);

			//���_�J���[�ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
		else
		{	// ������
			//���_�ݒ�
			pVtx[0].pos = D3DXVECTOR3(1170.0f, 319.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(1201.0f, 319.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(1170.0f, 582.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(1201.0f, 582.0f, 0.0f);

			//���_�J���[�ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}

		//1.0f�ŌŒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		
		//�e�N�X�`���ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		

		pVtx += 4;	//���_�f�[�^�̃|�C���^���S���i�߂�
	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffGauge->Unlock();
}
