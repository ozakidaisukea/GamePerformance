//=============================================================================
//
// �w�i�̏��� [bg.cpp]
// Author : Ozaki
//
//=============================================================================
#include "main.h"
#include "bg.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define BG_WIDTH	(SCREEN_WIDTH)
#define BG_HEIGHT	(SCREEN_HEIGHT)
#define PATTERN_X (0.00005f * g_PatrnAnime)

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTexturebg = NULL;				//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffbg = NULL;		//�e�N�X�`���̃|�C���^
int g_PatrnAnime;
int g_KounterAnime = 0;
//=============================================================================
// ����������(�|���S��)
//=============================================================================
void Initbg(void)
{
	LPDIRECT3DDEVICE9 pDevise;						//�f�o�C�X�̃|�C���^
													//�f�o�C�X�̎擾
	pDevise = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevise,
		"data\\TEXTURE\\sky000.jpg",
		&g_pTexturebg);

	//���_�o�b�t�@�̐���
	pDevise->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VRETEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffbg,
		NULL);

	//���[�J���ϐ�
	VERTEX_2D*pVtx;								//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^�̎擾
	g_pVtxBuffbg->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(PATTERN_X + 0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(PATTERN_X + 0.25f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(PATTERN_X + 0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(PATTERN_X + 0.25f, 1.0f);

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
	g_pVtxBuffbg->Unlock();
}

//=============================================================================
// �I������(�|���S��)
//=============================================================================
void Uninitbg(void)
{
	//�e�N�X�`���̔j��
	if (g_pTexturebg != NULL)
	{
		g_pTexturebg->Release();
		g_pTexturebg = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffbg != NULL)
	{
		g_pVtxBuffbg->Release();
		g_pVtxBuffbg = NULL;
	}
}

//=============================================================================
// �X�V����(�|���S��)
//=============================================================================
void Updatebg(void)
{
	g_PatrnAnime++;

	//���[�J���ϐ�
	VERTEX_2D*pVtx;								//���_���ւ̃|�C���^
												//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^�̎擾
	g_pVtxBuffbg->Lock(0, 0, (void**)&pVtx, 0);

	g_KounterAnime++;
	pVtx[0].tex.x = PATTERN_X + 0.0f;
	pVtx[1].tex.x = PATTERN_X + 0.25f;
	pVtx[2].tex.x = PATTERN_X + 0.0f;
	pVtx[3].tex.x = PATTERN_X + 0.25;

	pVtx += 4;

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffbg->Unlock();

}

//=============================================================================
// �`�揈��(�|���S��)
//=============================================================================
void Drawbg(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f���@�C�X���擾
	pDevice = GetDevice();


	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffbg, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VRETEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturebg);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);
}