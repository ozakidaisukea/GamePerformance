//=============================================================================
//
// �w�i�̏��� [TitleRogo.cpp]
// Author : Ozaki
//
//=============================================================================
#include "main.h"
#include "Titlerogo.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define BG_WIDTH	(SCREEN_WIDTH)
#define BG_HEIGHT	(SCREEN_HEIGHT)

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureTitleRogo = NULL;				//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitleRogo = NULL;		//�e�N�X�`���̃|�C���^

//=============================================================================
// ����������(�|���S��)
//=============================================================================
void InitTitleRogo(void)
{
	LPDIRECT3DDEVICE9 pDevise;						//�f�o�C�X�̃|�C���^
													//�f�o�C�X�̎擾
	pDevise = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevise,
		"data\\TEXTURE\\title1�P.png",
		&g_pTextureTitleRogo);

	//���_�o�b�t�@�̐���
	pDevise->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitleRogo,
		NULL);

	//���[�J���ϐ�
	VERTEX_2D*pVtx;								//���_���ւ̃|�C���^

												//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^�̎擾
	g_pVtxBuffTitleRogo->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(300, 0, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(950, 0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(300, 600, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(950, 600, 0.0f);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffTitleRogo->Unlock();
}

//=============================================================================
// �I������(�|���S��)
//=============================================================================
void UninitTitleRogo(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureTitleRogo != NULL)
	{
		g_pTextureTitleRogo->Release();
		g_pTextureTitleRogo = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffTitleRogo != NULL)
	{
		g_pVtxBuffTitleRogo->Release();
		g_pVtxBuffTitleRogo = NULL;
	}
}

//=============================================================================
// �X�V����(�|���S��)
//=============================================================================
void UpdateTitleRogo(void)
{

	////���[�J���ϐ�
	//VERTEX_2D*pVtx;								//���_���ւ̃|�C���^

	////���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^�̎擾
	//g_pVtxBuffTitleRogo->Lock(0, 0, (void**)&pVtx, 0);

	//pVtx += 4;

	////���_�o�b�t�@���A�����b�N
	//g_pVtxBuffTitleRogo->Unlock();

}

//=============================================================================
// �`�揈��(�|���S��)
//=============================================================================
void DrawTitleRogo(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f���@�C�X���擾
	pDevice = GetDevice();


	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTitleRogo, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureTitleRogo);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);
}