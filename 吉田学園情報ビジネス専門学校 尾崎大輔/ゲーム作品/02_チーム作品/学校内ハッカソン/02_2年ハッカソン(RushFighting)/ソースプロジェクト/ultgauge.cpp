//=============================================================================
//
// �K�E�Q�[�W���� [ultgauge.cpp]
// Author : Jukiya Hayakawa
//
//=============================================================================
#include "ultgauge.h"
#include "main.h"
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_GAUGE		"data/TEXTURE/ULT_GAUGE.png"		// �ǂݍ��ރe�N�X�`���t�@�C����
#define ULTGAUGE_HEIGHT		(13)								// �Q�[�W�̍���

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexUltGauge(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureUltGauge = NULL;				// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffUltGauge = NULL;				// ���_�o�b�t�@�ւ̃|�C���^
UltGauge				g_aUltGauge[MAX_ULTGAUGE] = {};			// �Q�[�W�̏��
int						g_aCountCol[MAX_ULTGAUGE] = {};			// �F�̏��

//=============================================================================
// ����������
//=============================================================================
void InitUltGauge(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	float fUltGaugePos = 0;		//�Q�[�W�̈ʒu

								// �l�̏�����
	for (int nCntUltGauge = 0; nCntUltGauge < MAX_ULTGAUGE; nCntUltGauge++)
	{//�Q�[�W�̐������J��Ԃ�
		g_aUltGauge[nCntUltGauge].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - 140 + fUltGaugePos, 100, 0.0f);	//�ʒu�̏�����
		g_aUltGauge[nCntUltGauge].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);									//�F�̏�����
		g_aUltGauge[nCntUltGauge].fWidth = 0.0f;															//���̏�����
		g_aUltGauge[nCntUltGauge].fHeight = ULTGAUGE_HEIGHT;															//�����̏�����
		g_aUltGauge[nCntUltGauge].nType = nCntUltGauge;														//�^�C�v
		g_aUltGauge[nCntUltGauge].state = ULTGAUGE_NOMAL;														//��Ԃ̏�����
		fUltGaugePos += 280.0f;
	}

	// ���_���̐ݒ�
	MakeVertexUltGauge(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitUltGauge(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureUltGauge != NULL)
	{
		g_pTextureUltGauge->Release();
		g_pTextureUltGauge = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffUltGauge != NULL)
	{
		g_pVtxBuffUltGauge->Release();
		g_pVtxBuffUltGauge = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateUltGauge(void)
{
	for (int nCntUltGauge = 0; nCntUltGauge < MAX_ULTGAUGE; nCntUltGauge++)
	{//�Q�[�W�̐������J��Ԃ�
		switch (g_aUltGauge[nCntUltGauge].state)
		{
		case ULTGAUGE_NOMAL:	//�ʏ��Ԃ̏ꍇ
			g_aUltGauge[nCntUltGauge].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		//���F�̑��
			break;
		case ULTGAUGE_READY:	//�g�p�\���
			g_aCountCol[nCntUltGauge]++;											//�J�E���g
			if (g_aCountCol[nCntUltGauge] % 4 == 0)
			{// ��莞�Ԃ��������ꍇ
				if (g_aUltGauge[nCntUltGauge].col.b == 0.0f)
				{// �Ԃ̏ꍇ
					g_aUltGauge[nCntUltGauge].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				}
				else
				{// ���̏ꍇ
					g_aUltGauge[nCntUltGauge].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				}
			}
			break;
		case ULTGAUGE_USE:		//�g�p��Ԃ̏ꍇ
			g_aUltGauge[nCntUltGauge].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);		//�ԐF�ɂ���

			if (g_aUltGauge[nCntUltGauge].fWidth >= 0)
			{//�����O�ȏ�̏ꍇ
				//���Z����
				g_aUltGauge[nCntUltGauge].fWidth -= 1.0f;
			}
			else if (g_aUltGauge[nCntUltGauge].fWidth <= 0)
			{//�����O�ȉ��̏ꍇ
				//���̌Œ�
				g_aUltGauge[nCntUltGauge].fWidth = 0;
				//�ʏ��Ԃɂ���
				g_aUltGauge[nCntUltGauge].state = ULTGAUGE_NOMAL;
			}
			break;
		}
	}
	VERTEX_2D *pVtx;   // ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffUltGauge->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntUltGauge = 0; nCntUltGauge < MAX_ULTGAUGE; nCntUltGauge++)
	{//�Q�[�W�̐������J��Ԃ�
		switch (nCntUltGauge)
		{
		case 0:	//�v���C���[�O�̏ꍇ
			// ���_���W
			pVtx[0].pos = D3DXVECTOR3(g_aUltGauge[nCntUltGauge].pos.x - g_aUltGauge[nCntUltGauge].fWidth, g_aUltGauge[nCntUltGauge].pos.y - g_aUltGauge[nCntUltGauge].fHeight, g_aUltGauge[nCntUltGauge].pos.z);
			pVtx[1].pos = D3DXVECTOR3(g_aUltGauge[nCntUltGauge].pos.x, g_aUltGauge[nCntUltGauge].pos.y - g_aUltGauge[nCntUltGauge].fHeight, g_aUltGauge[nCntUltGauge].pos.z);
			pVtx[2].pos = D3DXVECTOR3(g_aUltGauge[nCntUltGauge].pos.x - g_aUltGauge[nCntUltGauge].fWidth, g_aUltGauge[nCntUltGauge].pos.y + g_aUltGauge[nCntUltGauge].fHeight, g_aUltGauge[nCntUltGauge].pos.z);
			pVtx[3].pos = D3DXVECTOR3(g_aUltGauge[nCntUltGauge].pos.x, g_aUltGauge[nCntUltGauge].pos.y + g_aUltGauge[nCntUltGauge].fHeight, g_aUltGauge[nCntUltGauge].pos.z);
			break;
		case 1:	//�v���C���[�P�̏ꍇ
			// ���_���W
			pVtx[0].pos = D3DXVECTOR3(g_aUltGauge[nCntUltGauge].pos.x, g_aUltGauge[nCntUltGauge].pos.y - g_aUltGauge[nCntUltGauge].fHeight, g_aUltGauge[nCntUltGauge].pos.z);
			pVtx[1].pos = D3DXVECTOR3(g_aUltGauge[nCntUltGauge].pos.x + g_aUltGauge[nCntUltGauge].fWidth, g_aUltGauge[nCntUltGauge].pos.y - g_aUltGauge[nCntUltGauge].fHeight, g_aUltGauge[nCntUltGauge].pos.z);
			pVtx[2].pos = D3DXVECTOR3(g_aUltGauge[nCntUltGauge].pos.x, g_aUltGauge[nCntUltGauge].pos.y + g_aUltGauge[nCntUltGauge].fHeight, g_aUltGauge[nCntUltGauge].pos.z);
			pVtx[3].pos = D3DXVECTOR3(g_aUltGauge[nCntUltGauge].pos.x + g_aUltGauge[nCntUltGauge].fWidth, g_aUltGauge[nCntUltGauge].pos.y + g_aUltGauge[nCntUltGauge].fHeight, g_aUltGauge[nCntUltGauge].pos.z);
			break;
		}
		// ���_�J���[
		pVtx[0].col = g_aUltGauge[nCntUltGauge].col;
		pVtx[1].col = g_aUltGauge[nCntUltGauge].col;
		pVtx[2].col = g_aUltGauge[nCntUltGauge].col;
		pVtx[3].col = g_aUltGauge[nCntUltGauge].col;

		pVtx += 4;
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffUltGauge->Unlock();

}
//=============================================================================
// �^�C�g�����
//=============================================================================
void DrawUltGauge(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffUltGauge, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureUltGauge);

	for (int nCntUltGauge = 0; nCntUltGauge < MAX_ULTGAUGE; nCntUltGauge++)
	{
		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntUltGauge, 2);
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexUltGauge(LPDIRECT3DDEVICE9 pDevice)
{
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_GAUGE,
		&g_pTextureUltGauge);

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ULTGAUGE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffUltGauge,
		NULL);

	VERTEX_2D *pVtx;   // ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffUltGauge->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntUltGauge = 0; nCntUltGauge < MAX_ULTGAUGE; nCntUltGauge++)
	{
		switch (nCntUltGauge)
		{
		case 0:
			// ���_���W
			pVtx[0].pos = D3DXVECTOR3(g_aUltGauge[nCntUltGauge].pos.x - g_aUltGauge[nCntUltGauge].fWidth, g_aUltGauge[nCntUltGauge].pos.y - g_aUltGauge[nCntUltGauge].fHeight, g_aUltGauge[nCntUltGauge].pos.z);
			pVtx[1].pos = D3DXVECTOR3(g_aUltGauge[nCntUltGauge].pos.x, g_aUltGauge[nCntUltGauge].pos.y - g_aUltGauge[nCntUltGauge].fHeight, g_aUltGauge[nCntUltGauge].pos.z);
			pVtx[2].pos = D3DXVECTOR3(g_aUltGauge[nCntUltGauge].pos.x - g_aUltGauge[nCntUltGauge].fWidth, g_aUltGauge[nCntUltGauge].pos.y + g_aUltGauge[nCntUltGauge].fHeight, g_aUltGauge[nCntUltGauge].pos.z);
			pVtx[3].pos = D3DXVECTOR3(g_aUltGauge[nCntUltGauge].pos.x, g_aUltGauge[nCntUltGauge].pos.y + g_aUltGauge[nCntUltGauge].fHeight, g_aUltGauge[nCntUltGauge].pos.z);

			// �e�N�X�`�����W
			pVtx[0].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.0f, 1.0f);
			break;
		case 1:
			// ���_���W
			pVtx[0].pos = D3DXVECTOR3(g_aUltGauge[nCntUltGauge].pos.x, g_aUltGauge[nCntUltGauge].pos.y - g_aUltGauge[nCntUltGauge].fHeight, g_aUltGauge[nCntUltGauge].pos.z);
			pVtx[1].pos = D3DXVECTOR3(g_aUltGauge[nCntUltGauge].pos.x + g_aUltGauge[nCntUltGauge].fWidth, g_aUltGauge[nCntUltGauge].pos.y - g_aUltGauge[nCntUltGauge].fHeight, g_aUltGauge[nCntUltGauge].pos.z);
			pVtx[2].pos = D3DXVECTOR3(g_aUltGauge[nCntUltGauge].pos.x, g_aUltGauge[nCntUltGauge].pos.y + g_aUltGauge[nCntUltGauge].fHeight, g_aUltGauge[nCntUltGauge].pos.z);
			pVtx[3].pos = D3DXVECTOR3(g_aUltGauge[nCntUltGauge].pos.x + g_aUltGauge[nCntUltGauge].fWidth, g_aUltGauge[nCntUltGauge].pos.y + g_aUltGauge[nCntUltGauge].fHeight, g_aUltGauge[nCntUltGauge].pos.z);

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
		pVtx[0].col = g_aUltGauge[nCntUltGauge].col;
		pVtx[1].col = g_aUltGauge[nCntUltGauge].col;
		pVtx[2].col = g_aUltGauge[nCntUltGauge].col;
		pVtx[3].col = g_aUltGauge[nCntUltGauge].col;

		pVtx += 4;
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffUltGauge->Unlock();
}

//=============================================================================
// �K�E�Q�[�W�̐ݒu����
//=============================================================================
void SetUltGauge(float fWidth, int nType)
{
	VERTEX_2D *pVtx;   // ���_���ւ̃|�C���^

	g_aUltGauge[nType].fWidth += fWidth;	//���̉��Z����

	if (g_aUltGauge[nType].fWidth >= ULTGAUGE_WIDTH)
	{//�Q�[�W���ő�l�܂ŒB�����ꍇ
		g_aUltGauge[nType].fWidth = ULTGAUGE_WIDTH;	//�Q�[�W���Œ肳����
		g_aUltGauge[nType].state = ULTGAUGE_READY;		//�g�p�\��Ԃɂ���
	}

	// ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffUltGauge->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntUltGauge = 0; nCntUltGauge < MAX_ULTGAUGE; nCntUltGauge++)
	{//�Q�[�W�̐������J��Ԃ�
		switch (nCntUltGauge)
		{
		case 0:	//�v���C���[�O�̏ꍇ
			// ���_���W
			pVtx[0].pos = D3DXVECTOR3(g_aUltGauge[nCntUltGauge].pos.x - g_aUltGauge[nCntUltGauge].fWidth, g_aUltGauge[nCntUltGauge].pos.y - g_aUltGauge[nCntUltGauge].fHeight, g_aUltGauge[nCntUltGauge].pos.z);
			pVtx[1].pos = D3DXVECTOR3(g_aUltGauge[nCntUltGauge].pos.x, g_aUltGauge[nCntUltGauge].pos.y - g_aUltGauge[nCntUltGauge].fHeight, g_aUltGauge[nCntUltGauge].pos.z);
			pVtx[2].pos = D3DXVECTOR3(g_aUltGauge[nCntUltGauge].pos.x - g_aUltGauge[nCntUltGauge].fWidth, g_aUltGauge[nCntUltGauge].pos.y + g_aUltGauge[nCntUltGauge].fHeight, g_aUltGauge[nCntUltGauge].pos.z);
			pVtx[3].pos = D3DXVECTOR3(g_aUltGauge[nCntUltGauge].pos.x, g_aUltGauge[nCntUltGauge].pos.y + g_aUltGauge[nCntUltGauge].fHeight, g_aUltGauge[nCntUltGauge].pos.z);
			break;
		case 1:	//�v���C���[�P�̏ꍇ
			// ���_���W
			pVtx[0].pos = D3DXVECTOR3(g_aUltGauge[nCntUltGauge].pos.x, g_aUltGauge[nCntUltGauge].pos.y - g_aUltGauge[nCntUltGauge].fHeight, g_aUltGauge[nCntUltGauge].pos.z);
			pVtx[1].pos = D3DXVECTOR3(g_aUltGauge[nCntUltGauge].pos.x + g_aUltGauge[nCntUltGauge].fWidth, g_aUltGauge[nCntUltGauge].pos.y - g_aUltGauge[nCntUltGauge].fHeight, g_aUltGauge[nCntUltGauge].pos.z);
			pVtx[2].pos = D3DXVECTOR3(g_aUltGauge[nCntUltGauge].pos.x, g_aUltGauge[nCntUltGauge].pos.y + g_aUltGauge[nCntUltGauge].fHeight, g_aUltGauge[nCntUltGauge].pos.z);
			pVtx[3].pos = D3DXVECTOR3(g_aUltGauge[nCntUltGauge].pos.x + g_aUltGauge[nCntUltGauge].fWidth, g_aUltGauge[nCntUltGauge].pos.y + g_aUltGauge[nCntUltGauge].fHeight, g_aUltGauge[nCntUltGauge].pos.z);
			break;
		}
		pVtx += 4;
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffUltGauge->Unlock();
}

//=============================================================================
// �K�E�Q�[�W�g�p����
//=============================================================================
void UseUltGauge(int nType)
{
	if (g_aUltGauge[nType].state == ULTGAUGE_READY)
	{//�g�p�\��Ԃ̏ꍇ
		//�g�p��Ԃɂ���
		g_aUltGauge[nType].state = ULTGAUGE_USE;
	}
}

//=============================================================================
// �K�E�Q�[�W�擾����
//=============================================================================
ULTGAUGE_STATE GetUltGaugeState(int nType)
{
	return g_aUltGauge[nType].state;
}
float GetUltGaugeWidth(int nType)
{
	return g_aUltGauge[nType].fWidth;
}
void SetUltGaugeState(ULTGAUGE_STATE state, int nType)
{
	g_aUltGauge[nType].state = state;
}