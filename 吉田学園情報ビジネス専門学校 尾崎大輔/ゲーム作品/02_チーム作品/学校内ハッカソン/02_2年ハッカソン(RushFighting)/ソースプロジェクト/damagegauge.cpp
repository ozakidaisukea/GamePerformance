//=============================================================================
//
// �_���[�W�Q�[�W���� [damagegauge.cpp]
// Author : Jukiya Hayakawa
//
//=============================================================================
#include "damagegauge.h"
#include "lifegauge.h"
#include "main.h"
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_DAMAGEGAUGE		"data/TEXTURE/DAMAGE_GAUGE.png"		// �ǂݍ��ރe�N�X�`���t�@�C����

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexDamageGauge(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureDamageGauge = NULL;				// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffDamageGauge = NULL;				// ���_�o�b�t�@�ւ̃|�C���^
DamageGauge				g_aDamageGauge[MAX_DAMAGEGAUGE] = {};			// �Q�[�W�̏��
float					g_aCutWidth[MAX_DAMAGEGAUGE] = {};
//=============================================================================
// ����������
//=============================================================================
void InitDamageGauge(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	float fGaugePos = 0;		//�Q�[�W�̈ʒu

								// �l�̏�����
	for (int nCntGauge = 0; nCntGauge < MAX_DAMAGEGAUGE; nCntGauge++)
	{//�Q�[�W�̐������J��Ԃ�
		g_aDamageGauge[nCntGauge].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - 152 + fGaugePos, 50.0f, 0.0f);	//�ʒu�̏�����
		g_aDamageGauge[nCntGauge].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);						//�F�̏�����
		g_aDamageGauge[nCntGauge].fWidth = LIFEGAUGE_WIDTH;											//���̏�����
		g_aDamageGauge[nCntGauge].fHeight = LIFEGAUGE_HEIGHT;											//�����̏�����
		g_aDamageGauge[nCntGauge].nType = nCntGauge;												//�^�C�v
		fGaugePos += 305;
	}

	// ���_���̐ݒ�
	MakeVertexDamageGauge(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitDamageGauge(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureDamageGauge != NULL)
	{
		g_pTextureDamageGauge->Release();
		g_pTextureDamageGauge = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffDamageGauge != NULL)
	{
		g_pVtxBuffDamageGauge->Release();
		g_pVtxBuffDamageGauge = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateDamageGauge(void)
{
	for (int nCntDamageGauge = 0; nCntDamageGauge < MAX_DAMAGEGAUGE; nCntDamageGauge++)
	{//�Q�[�W�̐������J��Ԃ�
		switch (g_aDamageGauge[nCntDamageGauge].state)
		{
		case STATE_NOMAL:		//�ʏ��Ԃ̏ꍇ
			break;
		case STATE_MINUS:		//���Z��Ԃ̏ꍇ
			g_aDamageGauge[nCntDamageGauge].fWidth -= 0.5f;	//���Z����
			if (g_aDamageGauge[nCntDamageGauge].fWidth <= g_aCutWidth[nCntDamageGauge])
			{//������v�����ꍇ
				g_aDamageGauge[nCntDamageGauge].fWidth = g_aCutWidth[nCntDamageGauge];	//���̌Œ�
			}
			break;
		}
	}
		VERTEX_2D *pVtx;   // ���_���ւ̃|�C���^

		// ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
		g_pVtxBuffDamageGauge->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCntGauge = 0; nCntGauge < MAX_DAMAGEGAUGE; nCntGauge++)
		{//�Q�[�W�̐������J��Ԃ�
			switch (nCntGauge)
			{
			case 0:	//�v���C���[�O�̏ꍇ
					// ���_���W
				pVtx[0].pos = D3DXVECTOR3(g_aDamageGauge[nCntGauge].pos.x - g_aDamageGauge[nCntGauge].fWidth, g_aDamageGauge[nCntGauge].pos.y - g_aDamageGauge[nCntGauge].fHeight, g_aDamageGauge[nCntGauge].pos.z);
				pVtx[1].pos = D3DXVECTOR3(g_aDamageGauge[nCntGauge].pos.x, g_aDamageGauge[nCntGauge].pos.y - g_aDamageGauge[nCntGauge].fHeight, g_aDamageGauge[nCntGauge].pos.z);
				pVtx[2].pos = D3DXVECTOR3(g_aDamageGauge[nCntGauge].pos.x - g_aDamageGauge[nCntGauge].fWidth, g_aDamageGauge[nCntGauge].pos.y + g_aDamageGauge[nCntGauge].fHeight, g_aDamageGauge[nCntGauge].pos.z);
				pVtx[3].pos = D3DXVECTOR3(g_aDamageGauge[nCntGauge].pos.x, g_aDamageGauge[nCntGauge].pos.y + g_aDamageGauge[nCntGauge].fHeight, g_aDamageGauge[nCntGauge].pos.z);
				break;
			case 1:	//�v���C���[�P�̏ꍇ
					// ���_���W
				pVtx[0].pos = D3DXVECTOR3(g_aDamageGauge[nCntGauge].pos.x, g_aDamageGauge[nCntGauge].pos.y - g_aDamageGauge[nCntGauge].fHeight, g_aDamageGauge[nCntGauge].pos.z);
				pVtx[1].pos = D3DXVECTOR3(g_aDamageGauge[nCntGauge].pos.x + g_aDamageGauge[nCntGauge].fWidth, g_aDamageGauge[nCntGauge].pos.y - g_aDamageGauge[nCntGauge].fHeight, g_aDamageGauge[nCntGauge].pos.z);
				pVtx[2].pos = D3DXVECTOR3(g_aDamageGauge[nCntGauge].pos.x, g_aDamageGauge[nCntGauge].pos.y + g_aDamageGauge[nCntGauge].fHeight, g_aDamageGauge[nCntGauge].pos.z);
				pVtx[3].pos = D3DXVECTOR3(g_aDamageGauge[nCntGauge].pos.x + g_aDamageGauge[nCntGauge].fWidth, g_aDamageGauge[nCntGauge].pos.y + g_aDamageGauge[nCntGauge].fHeight, g_aDamageGauge[nCntGauge].pos.z);
				break;
			}
			pVtx += 4;
		}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffDamageGauge->Unlock();
}
//=============================================================================
// �^�C�g�����
//=============================================================================
void DrawDamageGauge(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffDamageGauge, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureDamageGauge);

	for (int nCntGauge = 0; nCntGauge < MAX_DAMAGEGAUGE; nCntGauge++)
	{
		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntGauge, 2);
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexDamageGauge(LPDIRECT3DDEVICE9 pDevice)
{
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_DAMAGEGAUGE,
		&g_pTextureDamageGauge);

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_DAMAGEGAUGE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffDamageGauge,
		NULL);

	VERTEX_2D *pVtx;   // ���_���ւ̃|�C���^

					   // ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffDamageGauge->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntGauge = 0; nCntGauge < MAX_DAMAGEGAUGE; nCntGauge++)
	{
		switch (nCntGauge)
		{
		case 0:
			// ���_���W
			pVtx[0].pos = D3DXVECTOR3(g_aDamageGauge[nCntGauge].pos.x - g_aDamageGauge[nCntGauge].fWidth, g_aDamageGauge[nCntGauge].pos.y - g_aDamageGauge[nCntGauge].fHeight, g_aDamageGauge[nCntGauge].pos.z);
			pVtx[1].pos = D3DXVECTOR3(g_aDamageGauge[nCntGauge].pos.x, g_aDamageGauge[nCntGauge].pos.y - g_aDamageGauge[nCntGauge].fHeight, g_aDamageGauge[nCntGauge].pos.z);
			pVtx[2].pos = D3DXVECTOR3(g_aDamageGauge[nCntGauge].pos.x - g_aDamageGauge[nCntGauge].fWidth, g_aDamageGauge[nCntGauge].pos.y + g_aDamageGauge[nCntGauge].fHeight, g_aDamageGauge[nCntGauge].pos.z);
			pVtx[3].pos = D3DXVECTOR3(g_aDamageGauge[nCntGauge].pos.x, g_aDamageGauge[nCntGauge].pos.y + g_aDamageGauge[nCntGauge].fHeight, g_aDamageGauge[nCntGauge].pos.z);

			// �e�N�X�`�����W
			pVtx[0].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.0f, 1.0f);
			break;
		case 1:
			// ���_���W
			pVtx[0].pos = D3DXVECTOR3(g_aDamageGauge[nCntGauge].pos.x, g_aDamageGauge[nCntGauge].pos.y - g_aDamageGauge[nCntGauge].fHeight, g_aDamageGauge[nCntGauge].pos.z);
			pVtx[1].pos = D3DXVECTOR3(g_aDamageGauge[nCntGauge].pos.x + g_aDamageGauge[nCntGauge].fWidth, g_aDamageGauge[nCntGauge].pos.y - g_aDamageGauge[nCntGauge].fHeight, g_aDamageGauge[nCntGauge].pos.z);
			pVtx[2].pos = D3DXVECTOR3(g_aDamageGauge[nCntGauge].pos.x, g_aDamageGauge[nCntGauge].pos.y + g_aDamageGauge[nCntGauge].fHeight, g_aDamageGauge[nCntGauge].pos.z);
			pVtx[3].pos = D3DXVECTOR3(g_aDamageGauge[nCntGauge].pos.x + g_aDamageGauge[nCntGauge].fWidth, g_aDamageGauge[nCntGauge].pos.y + g_aDamageGauge[nCntGauge].fHeight, g_aDamageGauge[nCntGauge].pos.z);

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
		pVtx[0].col = g_aDamageGauge[nCntGauge].col;
		pVtx[1].col = g_aDamageGauge[nCntGauge].col;
		pVtx[2].col = g_aDamageGauge[nCntGauge].col;
		pVtx[3].col = g_aDamageGauge[nCntGauge].col;

		pVtx += 4;
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffDamageGauge->Unlock();
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void SetDamageGaugeState(DAMAGE_STATE state, int nType,float fWidth)
{
	g_aDamageGauge[nType].state = state;
	g_aCutWidth[nType] = fWidth;
}