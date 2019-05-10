//=============================================================================
//
// �w�i�̏��� [Gameover.cpp]
// Author : Ozaki
//
//=============================================================================
#include "main.h"
#include "BG.h"
#include "Gameover.h"
#include "fade.h"
#include "input.h"
#include "sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define GAMEOVER_WIDTH	(SCREEN_WIDTH)
#define GAMEOVER_HEIGHT	(SCREEN_HEIGHT)


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
//VERTEX_2D g_aVertex[4];							//���_�����i�[����
LPDIRECT3DTEXTURE9 g_pTextureGAMEOVER = NULL;				//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGAMEOVER = NULL;		//�e�N�X�`���̃|�C���^
int Gameovertimer;
//=============================================================================
// ����������(�|���S��)
//=============================================================================
void InitGameover(void)
{
	LPDIRECT3DDEVICE9 pDevise;						//�f�o�C�X�̃|�C���^
													//�f�o�C�X�̎擾
	pDevise = GetDevice();

	Gameovertimer = 0;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevise,
		"data\\TEXTURE\\gameover.jpg",
		&g_pTextureGAMEOVER);

	//���_�o�b�t�@�̐���
	pDevise->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VRETEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffGAMEOVER,
		NULL);
	//���[�J���ϐ�
	VERTEX_2D*pVtx;								//���_���ւ̃|�C���^
												//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^�̎擾
	g_pVtxBuffGAMEOVER->Lock(0, 0, (void**)&pVtx, 0);

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
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffGAMEOVER->Unlock();
}

//=============================================================================
// �I������(�|���S��)
//=============================================================================
void UninitGameover(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureGAMEOVER != NULL)
	{
		g_pTextureGAMEOVER->Release();
		g_pTextureGAMEOVER = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffGAMEOVER != NULL)
	{
		g_pVtxBuffGAMEOVER->Release();
		g_pVtxBuffGAMEOVER = NULL;
	}
}

//=============================================================================
// �X�V����(�|���S��)
//=============================================================================
void UpdateGameover(void)
{
	FADE Fade;
	Fade = GetFade();
	Gameovertimer++;

	if (Fade == FADE_NONE)
	{
		if (GetKeyboardTrigger(DIK_RETURN) == true && Fade == FADE_NONE)
		{
			SetFade(MODE_RANKING);
			PlaySound(SOUND_LABEL_SE_DECIDE);
		}
		if (Gameovertimer == 700)
		{
			SetFade(MODE_TITLE);
			Gameovertimer = 0;

		}
	}
}

//=============================================================================
// �`�揈��(�|���S��)
//=============================================================================
void DrawGameover(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f���@�C�X���擾
	pDevice = GetDevice();


	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffGAMEOVER, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VRETEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureGAMEOVER);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);
}