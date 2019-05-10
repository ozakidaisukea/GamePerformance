//=============================================================================
//
// �`���[�g���A���̏��� [tutorial.cpp]
// Author : Ozaki
//
//=============================================================================
#include "main.h"
#include "tutorial.h"
#include "input.h"
#include "fade.h"
#include "sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define tutorial_WIDTH	(SCREEN_WIDTH)
#define tutorial_HEIGHT	(SCREEN_HEIGHT)

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTexturetutorial = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufftutorial = NULL;		//�e�N�X�`���̃|�C���^

//=============================================================================
// ����������(�|���S��)
//=============================================================================
void Inittutorial(void)
{
	LPDIRECT3DDEVICE9 pDevice;						//�f�o�C�X�̃|�C���^					
	pDevice = GetDevice();	//�f�o�C�X�̎擾

							//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\tutorial_bg001.jpg",
		&g_pTexturetutorial);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VRETEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBufftutorial,
		NULL);
	//���[�J���ϐ�
	VERTEX_2D*pVtx;								//���_���ւ̃|�C���^


												//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^�̎擾
	g_pVtxBufftutorial->Lock(0, 0, (void**)&pVtx, 0);

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
	g_pVtxBufftutorial->Unlock();
}

//=============================================================================
// �I������(�|���S��)
//=============================================================================
void Uninittutorial(void)
{
	//�e�N�X�`���̔j��
	if (g_pTexturetutorial != NULL)
	{
		g_pTexturetutorial->Release();
		g_pTexturetutorial = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBufftutorial != NULL)
	{
		g_pVtxBufftutorial->Release();
		g_pVtxBufftutorial = NULL;
	}
}

//=============================================================================
// �X�V����(�|���S��)
//=============================================================================
void Updatetutorial(void)
{
	FADE Fade;
	Fade = GetFade();

	if (Fade == FADE_NONE)
	{
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			SetFade(MODE_GAME);
			PlaySound(SOUND_LABEL_SE_DECIDE);
		}
	}

}

//=============================================================================
// �`�揈��(�|���S��)
//=============================================================================
void Drawtutorial(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f���@�C�X���擾
	pDevice = GetDevice();


	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBufftutorial, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VRETEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturetutorial);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);
}