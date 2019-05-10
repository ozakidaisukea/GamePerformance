//=============================================================================
//
// �w�i�̏��� [Pausebg.cpp]
// Author : Ozaki
//
//=============================================================================
#include "main.h"
#include "PauseBG.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define PauseBG_WIDTH	(SCREEN_WIDTH)
#define PauseBG_HEIGHT	(SCREEN_HEIGHT)

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTexturePauseBG = NULL;				//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPauseBG = NULL;			//�e�N�X�`���̃|�C���^
int g_PatrnAnimea = 0;
int g_KounterAnimea = 0;

//=============================================================================
// ����������(�|���S��)
//=============================================================================
void InitPauseBG(void)
{
	LPDIRECT3DDEVICE9 pDevise;						//�f�o�C�X�̃|�C���^
													//�f�o�C�X�̎擾
	pDevise = GetDevice();

	////�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevise,
		"data\\TEXTURE\\pause100.png",
		&g_pTexturePauseBG);

	//���_�o�b�t�@�̐���
	pDevise->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPauseBG,
		NULL);

	//���[�J���ϐ�
	VERTEX_2D*pVtx;								//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^�̎擾
	g_pVtxBuffPauseBG->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//�e�N�X�`���̐ݒ�
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
	pVtx[0].col = D3DXCOLOR(1.0f, 0, 0, 0.5);
	pVtx[1].col = D3DXCOLOR(1.0f, 0, 0, 0.5);
	pVtx[2].col = D3DXCOLOR(1.0f, 0, 0, 0.5);
	pVtx[3].col = D3DXCOLOR(1.0f, 0, 0, 0.5);

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffPauseBG->Unlock();


}

//=============================================================================
// �I������(�|���S��)
//=============================================================================
void UninitPauseBG(void)
{
	//�e�N�X�`���̔j��
	if (g_pTexturePauseBG != NULL)
	{
		g_pTexturePauseBG->Release();
		g_pTexturePauseBG = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPauseBG != NULL)
	{
		g_pVtxBuffPauseBG->Release();
		g_pVtxBuffPauseBG = NULL;
	}
}

//=============================================================================
// �X�V����(�|���S��)
//=============================================================================
void UpdatePauseBG(void)
{
	////���[�J���ϐ�
	//VERTEX_2D*pVtx;								//���_���ւ̃|�C���^
	//											//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^�̎擾
	//g_pVtxBuffPauseBG->Lock(0, 0, (void**)&pVtx, 0);

	//g_KounterAnimea++;
	//pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f - (g_KounterAnimea * 0.005f));
	//pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f - (g_KounterAnimea * 0.005f));
	//pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f - (g_KounterAnimea * 0.005f));
	//pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f - (g_KounterAnimea * 0.005f));

	//pVtx += 4;

	////���_�o�b�t�@���A�����b�N
	//g_pVtxBuffPauseBG->Unlock();


}

//=============================================================================
// �`�揈��(�|���S��)
//=============================================================================
void DrawPauseBG(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f���@�C�X���擾
	pDevice = GetDevice();


	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPauseBG, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturePauseBG);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);
}