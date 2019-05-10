//=============================================================================
//
// �̗̓Q�[�W���� [lifegauge.cpp]
// Author : Jukiya Hayakawa
//
//=============================================================================
#include "Rush.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_RUSH		"data/TEXTURE/ultlogo.png"		// �ǂݍ��ރe�N�X�`���t�@�C����

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexRushGauge(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureRush = NULL;				// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRush = NULL;				// ���_�o�b�t�@�ւ̃|�C���^
bool g_bRushDisp = false;
//=============================================================================
// ����������
//=============================================================================
void InitRush(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_���̐ݒ�
	MakeVertexRushGauge(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitRush(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureRush != NULL)
	{
		g_pTextureRush->Release();
		g_pTextureRush = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffRush != NULL)
	{
		g_pVtxBuffRush->Release();
		g_pVtxBuffRush = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateRush(void)
{

}
//=============================================================================
// �^�C�g�����
//=============================================================================
void DrawRush(void)
{
	if (g_bRushDisp == true)
	{
		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
		pDevice->SetStreamSource(0, g_pVtxBuffRush, 0, sizeof(VERTEX_2D));

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureRush);

			// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexRushGauge(LPDIRECT3DDEVICE9 pDevice)
{
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_RUSH,
		&g_pTextureRush);

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRush,
		NULL);

	VERTEX_2D *pVtx;   // ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffRush->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W
	pVtx[0].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - 200.0f, 400.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 + 200.0f, 400.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - 200.0f, 600.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 + 200.0f, 600.0f, 0.0f);

	// ���_�e�N�X�`��
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// �e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffRush->Unlock();
}

void SetRush(bool b)
{
	g_bRushDisp = b;
}