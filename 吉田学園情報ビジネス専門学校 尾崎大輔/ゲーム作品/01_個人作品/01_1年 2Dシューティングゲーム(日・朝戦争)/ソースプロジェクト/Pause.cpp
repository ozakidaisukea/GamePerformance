//=============================================================================
//
// �w�i�̏��� [Pause.cpp]
// Author : Ozaki
//
//=============================================================================
#include "main.h"
#include "Pause.h"
#include "PauseBG.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define Pause_WIDTH		(SCREEN_WIDTH)
#define Pause_HEIGHT	(SCREEN_HEIGHT)


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
//VERTEX_2D g_aVertex[4];							//���_�����i�[����
LPDIRECT3DTEXTURE9 g_pTexturePause = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPause = NULL;		//�e�N�X�`���̃|�C���^

//=============================================================================
// ����������(�|���S��)
//=============================================================================
void InitPause(void)
{
	LPDIRECT3DDEVICE9 pDevise;						//�f�o�C�X�̃|�C���^
													//�f�o�C�X�̎擾
	pDevise = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevise,
		"data\\TEXTURE\\pause100.png",
		&g_pTexturePause);

	//���_�o�b�t�@�̐���
	pDevise->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VRETEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPause,
		NULL);
	//���[�J���ϐ�
	VERTEX_2D*pVtx;								//���_���ւ̃|�C���^
												//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^�̎擾
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);
	 
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
	pVtx[0].col = D3DCOLOR_RGBA(0, 0, 0, 150);
	pVtx[1].col = D3DCOLOR_RGBA(0, 0, 0, 150);
	pVtx[2].col = D3DCOLOR_RGBA(0, 0, 0, 150);
	pVtx[3].col = D3DCOLOR_RGBA(0, 0, 0, 150);

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffPause->Unlock();


	InitPauseBG();
	//InitPausecont();
}

//=============================================================================
// �I������(�|���S��)
//=============================================================================
void UninitPause(void)
{
	//�e�N�X�`���̔j��
	if (g_pTexturePause != NULL)
	{
		g_pTexturePause->Release();
		g_pTexturePause = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPause != NULL)
	{
		g_pVtxBuffPause->Release();
		g_pVtxBuffPause = NULL;
	}
	UninitPauseBG();
	//UninitPausemenu();
}

//=============================================================================
// �X�V����(�|���S��)
//=============================================================================
void UpdatePause(void)
{
	//���[�J���ϐ�
	//VERTEX_2D*pVtx;								//���_���ւ̃|�C���^
	//											���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^�̎擾
	//g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	//
	//pVtx += 4;

	//���_�o�b�t�@���A�����b�N
	//g_pVtxBuffPause->Unlock();
	UpdatePauseBG();
	//UpdatePausecont();
}

//=============================================================================
// �`�揈��(�|���S��)
//=============================================================================
void DrawPause(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f���@�C�X���擾
	pDevice = GetDevice();


	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPause, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VRETEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturePause);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);
	DrawPauseBG();
	//DrawPausecont();
}