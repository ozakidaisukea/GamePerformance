//=============================================================================
//
// �^�C�g���̏��� [Title.cpp]
// Author : Ozaki
//
//=============================================================================
#include "main.h"
#include "Title.h"
#include "input.h"
#include "sound.h"
#include "Fade.h"
#include "camera.h"
#include "light.h"
#include "wall.h"
#include "polygon.h"
#include "tutorial.h"
#include "Titlerogo.h"
#include "Player2.h"
#include "shadow.h"
#include "Player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define Title_WIDTH		(500)
#define Title_HEIGHT	(500)


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
//VERTEX_2D g_aVertex[4];							//���_�����i�[����
LPDIRECT3DTEXTURE9 g_pTextureTitle = NULL;				//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;		//�e�N�X�`���̃|�C���^

int titletimer;
//=============================================================================
// ����������(�|���S��)
//=============================================================================
void InitTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;						//�f�o�C�X�̃|�C���^
	pDevice = GetDevice();	//�f�o�C�X�̎擾
	titletimer = 0;

	//���[�J���ϐ�
	VERTEX_2D*pVtx;								//���_���ւ̃|�C���^

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\sensou.jpg",
		&g_pTextureTitle);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL);

	//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^�̎擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(Title_WIDTH, 0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0, Title_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(Title_WIDTH, Title_HEIGHT, 0.0f);

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
	g_pVtxBuffTitle->Unlock();

	// �J�����̏���������
	InitCamera();
	// ���C�g�̏���������
	InitLight();

	InitTitleRogo();

	InitWall();

	InitPlayer2();

	InitShadow();

	// �t�B�[���h�̏�����
	InitPolygon();

	// ���b�V���E�H�[���̏�����
	SetWall(D3DXVECTOR3(0.0f, 0.0f, -1000.0f), D3DXVECTOR3(0.0f, D3DX_PI*1.0f, 0.0f));	 // ��O
	SetWall(D3DXVECTOR3(0.0f, 0.0f, 1000.0f), D3DXVECTOR3(0.0f, -D3DX_PI*0.0f, 0.0f));	 // ��
	SetWall(D3DXVECTOR3(-1000.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI*-0.5f, 0.0f));	 // ��
	SetWall(D3DXVECTOR3(1000.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f));	 // �E


}

//=============================================================================
// �I������(�|���S��)
//=============================================================================
void UninitTitle(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureTitle != NULL)
	{
		g_pTextureTitle->Release();
		g_pTextureTitle = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}

	UninitCamera();

	UninitPolygon();

	UninitWall();

	UninitTitleRogo();

	UninitLight();

	UninitPlayer2();

	UninitShadow();

}

//=============================================================================
// �X�V����(�|���S��)
//=============================================================================
void UpdateTitle(void)
{
	FADE Fade;
	Fade = GetFade();
	titletimer++;

	if (Fade == FADE_NONE)
	{
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			SetFade(MODE_TUTORIAL);

			PlaySound(SOUND_LABEL_SE_USHI);
		}
		if (titletimer >= 300)
		{
			SetFade(MODE_RANKING);
		}

	}

	UpdatePlayer2();

	UpdateCamera();

	UpdatePolygon();

	UpdateWall();

	UpdateTitleRogo();

	UpdateLight();

	UpdateShadow();
}

//=============================================================================
// �`�揈��(�|���S��)
//=============================================================================
void DrawTitle(void)
{
	//LPDIRECT3DDEVICE9 pDevice;

	////�f���@�C�X���擾
	//pDevice = GetDevice();

	////���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	//pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	////���_�t�H�[�}�b�g�̐ݒ�
	//pDevice->SetFVF(FVF_VERTEX_2D);

	////�e�N�X�`���̐ݒ�
	//pDevice->SetTexture(0, g_pTextureTitle);

	////�|���S���̕`��
	//pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
	//	0,
	//	2);

	SetCamera();

	DrawPlayer2();

	DrawPolygon();

	DrawWall();

	DrawTitleRogo();

	DrawShadow();
}