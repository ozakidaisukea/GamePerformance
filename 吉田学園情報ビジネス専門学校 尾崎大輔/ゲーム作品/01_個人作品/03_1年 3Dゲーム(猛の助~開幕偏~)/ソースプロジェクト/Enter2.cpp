//=============================================================================
//
// �G���^�[���� [enter2.cpp]
// Author : Ozaki
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "Enter2.h"
#include "fade.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define ENTER_TEXTURENAME		"data\\TEXTURE\\press_enter.png"	// �e�N�X�`����
#define	ENTER_SIZE0				(30)								// �|�[�Y�Z���N�g�̑傫��
#define	ENTER_SIZE1				(120)								// �|�[�Y�Z���N�g�̑傫��

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureEnter2 = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnter2 = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
ENTER2 g_Enter2;
int	g_nCntEnter2 = 0;
float g_fEnterTimer2 = 0.0f;

//=============================================================================
// �^�C�g������������
//=============================================================================
void InitEnter2(void)
{
	LPDIRECT3DDEVICE9 pDevice;	// �f�o�C�X�ւ̃|�C���^

								// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �G���^�[�̏��̏�����
	g_Enter2.pos = D3DXVECTOR3(200, SCREEN_HEIGHT / 2, 0.0f);
	g_Enter2.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, ENTER_TEXTURENAME, &g_pTextureEnter2);

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,	// �m�ۂ���o�b�t�@�̃T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,			// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffEnter2,
		NULL);

	VERTEX_2D *pVtx;	// ���_���ւ̃|�C���^

						// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffEnter2->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_Enter2.pos.x - ENTER_SIZE1, g_Enter2.pos.y - ENTER_SIZE0, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Enter2.pos.x + ENTER_SIZE1, g_Enter2.pos.y - ENTER_SIZE0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Enter2.pos.x - ENTER_SIZE1, g_Enter2.pos.y + ENTER_SIZE0, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Enter2.pos.x + ENTER_SIZE1, g_Enter2.pos.y + ENTER_SIZE0, 0.0f);

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffEnter2->Unlock();
}

//=============================================================================
// �^�C�g���I������
//=============================================================================
void UninitEnter2(void)
{
	// �e�N�X�`���̔j��
	if (g_pTextureEnter2 != NULL)
	{
		g_pTextureEnter2->Release();
		g_pTextureEnter2 = NULL;
	}

	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffEnter2 != NULL)
	{
		g_pVtxBuffEnter2->Release();
		g_pVtxBuffEnter2 = NULL;
	}
}

//=============================================================================
// �^�C�g���X�V����
//=============================================================================
void UpdateEnter2(void)
{
	g_nCntEnter2++;
	if (g_nCntEnter2 >= 10)
	{
		if (g_fEnterTimer2 == 1)
		{
			g_fEnterTimer2 = 0.0f;
		}
		else if (g_fEnterTimer2 == 0)
		{
			g_fEnterTimer2 = 1.0f;
		}

		VERTEX_2D *pVtx;	// ���_���ւ̃|�C���^

							// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		g_pVtxBuffEnter2->Lock(0, 0, (void**)&pVtx, 0);


		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, g_fEnterTimer2);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, g_fEnterTimer2);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, g_fEnterTimer2);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, g_fEnterTimer2);

		g_nCntEnter2 = 0;
	}

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffEnter2->Unlock();
}

//=============================================================================
// �^�C�g���`�揈��
//=============================================================================
void DrawEnter2(void)
{
	LPDIRECT3DDEVICE9	pDevice;	// �f�o�C�X�ւ̃|�C���^

									// �f�o�C�X���擾����
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffEnter2, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureEnter2);

	// �^�C�g���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}