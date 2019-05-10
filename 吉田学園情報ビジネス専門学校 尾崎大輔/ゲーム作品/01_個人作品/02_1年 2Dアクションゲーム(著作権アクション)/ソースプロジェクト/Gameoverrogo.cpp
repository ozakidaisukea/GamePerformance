//=============================================================================
//
// �w�i�̏��� [Gameoverrogo.cpp]
// Author : Ozaki
//
//=============================================================================
#include "main.h"
#include "Gameoverrogo.h"
#include "Fade.h"
#include "sound.h"
#include "Input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define BG_WIDTH	(SCREEN_WIDTH)
#define BG_HEIGHT	(70)

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureGameoverRogo = NULL;				//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGameoverRogo = NULL;		//�e�N�X�`���̃|�C���^
int		GameOvertimer;
//=============================================================================
// ����������(�|���S��)
//=============================================================================
void InitGameoverRogo(void)
{
	LPDIRECT3DDEVICE9 pDevise;						//�f�o�C�X�̃|�C���^
													//�f�o�C�X�̎擾
	pDevise = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevise,
		"data\\TEXTURE\\result_logo001.png",
		&g_pTextureGameoverRogo);

	//���_�o�b�t�@�̐���
	pDevise->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VRETEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffGameoverRogo,
		NULL);

	//���[�J���ϐ�
	VERTEX_2D*pVtx;								//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^�̎擾
	g_pVtxBuffGameoverRogo->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

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
	g_pVtxBuffGameoverRogo->Unlock();
}

//=============================================================================
// �I������(�|���S��)
//=============================================================================
void UninitGameoverRogo(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureGameoverRogo != NULL)
	{
		g_pTextureGameoverRogo->Release();
		g_pTextureGameoverRogo = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffGameoverRogo != NULL)
	{
		g_pVtxBuffGameoverRogo->Release();
		g_pVtxBuffGameoverRogo = NULL;
	}
}

//=============================================================================
// �X�V����(�|���S��)
//=============================================================================
void UpdateGameoverRogo(void)
{
	FADE Fade;
	Fade = GetFade();
	GameOvertimer++;

	if (Fade == FADE_NONE)
	{
		if (GetKeyboardTrigger(DIK_RETURN) == true && Fade == FADE_NONE)
		{
			SetFade(MODE_RANKING);
			PlaySound(SOUND_LABEL_SE_DECIDE);

		}
		if (GameOvertimer >= 700)
		{
			SetFade(MODE_RANKING);
		}

	}

}

//=============================================================================
// �`�揈��(�|���S��)
//=============================================================================
void DrawGameoverRogo(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f���@�C�X���擾
	pDevice = GetDevice();


	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffGameoverRogo, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VRETEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureGameoverRogo);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);
} 