//=============================================================================
//
// �^�C�g�����S�̏��� [titlelogo.cpp]
// Author : Jukiya Hayakawa
//
//=============================================================================
#include "titlelogo.h"
#include "main.h"
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_TITLELOGO		"data/TEXTURE/titlelogo.png"			// �ǂݍ��ރe�N�X�`���t�@�C����
#define TITLELOGO_WIDTH			(250)									// �Q�[�W�̕�
#define TITLELOGO_HEIGHT		(250)									// �Q�[�W�̍���

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexTitleLogo(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureTitleLogo = NULL;					// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitleLogo = NULL;					// ���_�o�b�t�@�ւ̃|�C���^
TitleLogo				g_titleLogo;								// �Q�[�W�̏��

//=============================================================================
// ����������
//=============================================================================
void InitTitleLogo(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_titleLogo.pos = D3DXVECTOR3(SCREEN_WIDTH / 2 , SCREEN_HEIGHT / 2 - 100 , 0.0f);	//�ʒu�̏�����
	g_titleLogo.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);												//�F�̏�����
	g_titleLogo.fWidth = TITLELOGO_WIDTH;																//���̏�����
	g_titleLogo.fHeight = TITLELOGO_HEIGHT;																//�����̏�����

	// ���_���̐ݒ�
	MakeVertexTitleLogo(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitTitleLogo(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureTitleLogo != NULL)
	{
		g_pTextureTitleLogo->Release();
		g_pTextureTitleLogo = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffTitleLogo != NULL)
	{
		g_pVtxBuffTitleLogo->Release();
		g_pVtxBuffTitleLogo = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateTitleLogo(void)
{

	//if (g_titleLogo.col.a <= 1.0f)
	//{
	//	g_titleLogo.col.a += 0.005f;		//���Z����
	//}
	//else if (g_titleLogo.col.a >= 1.0f)
	//{
	//	g_titleLogo.col.a = 1.0f;
	//}
	//VERTEX_2D *pVtx;   // ���_���ւ̃|�C���^

	//// ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	//g_pVtxBuffTitleLogo->Lock(0, 0, (void**)&pVtx, 0);

	//// ���_���W
	//pVtx[0].pos = D3DXVECTOR3(g_titleLogo.pos.x - g_titleLogo.fWidth, g_titleLogo.pos.y - g_titleLogo.fHeight, g_titleLogo.pos.z);
	//pVtx[1].pos = D3DXVECTOR3(g_titleLogo.pos.x + g_titleLogo.fWidth, g_titleLogo.pos.y - g_titleLogo.fHeight, g_titleLogo.pos.z);
	//pVtx[2].pos = D3DXVECTOR3(g_titleLogo.pos.x - g_titleLogo.fWidth, g_titleLogo.pos.y + g_titleLogo.fHeight, g_titleLogo.pos.z);
	//pVtx[3].pos = D3DXVECTOR3(g_titleLogo.pos.x + g_titleLogo.fWidth, g_titleLogo.pos.y + g_titleLogo.fHeight, g_titleLogo.pos.z);

	//// ���_�J���[
	//pVtx[0].col = g_titleLogo.col;
	//pVtx[1].col = g_titleLogo.col;
	//pVtx[2].col = g_titleLogo.col;
	//pVtx[3].col = g_titleLogo.col;

	//// ���_�o�b�t�@���A�����b�N����
	//g_pVtxBuffTitleLogo->Unlock();
}
//=============================================================================
// �^�C�g�����
//=============================================================================
void DrawTitleLogo(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffTitleLogo, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureTitleLogo);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexTitleLogo(LPDIRECT3DDEVICE9 pDevice)
{
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_TITLELOGO,
		&g_pTextureTitleLogo);

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TITlELOGO,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitleLogo,
		NULL);

	VERTEX_2D *pVtx;   // ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffTitleLogo->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W
	pVtx[0].pos = D3DXVECTOR3(g_titleLogo.pos.x - g_titleLogo.fWidth, g_titleLogo.pos.y - g_titleLogo.fHeight, g_titleLogo.pos.z);
	pVtx[1].pos = D3DXVECTOR3(g_titleLogo.pos.x + g_titleLogo.fWidth, g_titleLogo.pos.y - g_titleLogo.fHeight, g_titleLogo.pos.z);
	pVtx[2].pos = D3DXVECTOR3(g_titleLogo.pos.x - g_titleLogo.fWidth, g_titleLogo.pos.y + g_titleLogo.fHeight, g_titleLogo.pos.z);
	pVtx[3].pos = D3DXVECTOR3(g_titleLogo.pos.x + g_titleLogo.fWidth, g_titleLogo.pos.y + g_titleLogo.fHeight, g_titleLogo.pos.z);

	// �e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�e�N�X�`��
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[
	pVtx[0].col = g_titleLogo.col;
	pVtx[1].col = g_titleLogo.col;
	pVtx[2].col = g_titleLogo.col;
	pVtx[3].col = g_titleLogo.col;

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTitleLogo->Unlock();
}