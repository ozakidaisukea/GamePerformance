//=============================================================================
// 
// ���U���g�̏��� [fadelogo.cpp]
// Author : Mikiya Meguro
//
//=============================================================================
#include "fadelogo.h"
#include "input.h"
#include "fade.h"
#include "inputx.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TITLE_TEXTURENAME		"data\\TEXTURE\\NowLoading.png"	//�e�N�X�`���̃t�@�C����
#define RESULT_POS_X				(0)							//������WX
#define RESULT_POS_Y				(0)							//������WY	
#define RESULT_WIDTH			(SCREEN_WIDTH)				//�����`�̉������W
#define RESULT_HEIGHT			(SCREEN_HEIGHT)				//�����`�̏c�����W

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureFadeLogo = NULL;		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFadeLogo = NULL;	//���_�o�b�t�@�ւ̃|�C���^
D3DXCOLOR				g_colorFadeLogo;			// �t�F�[�h�F
//*****************************************************************************
// ������
//*****************************************************************************
void InitFadeLogo(void)
{	//���[�J���ϐ�	
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	pDevice = GetDevice();
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		TITLE_TEXTURENAME,
		&g_pTextureFadeLogo);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffFadeLogo,
		NULL);

	//���_�o�b�t�@�����b�N�����_�f�[�^�̃|�C���^���擾
	g_pVtxBuffFadeLogo->Lock(0, 0, (void**)&pVtx, 0);
	//���_���W
	pVtx[0].pos = D3DXVECTOR3(RESULT_POS_X, RESULT_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(RESULT_WIDTH, RESULT_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(RESULT_POS_X, RESULT_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(RESULT_WIDTH, RESULT_HEIGHT, 0.0f);
	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	//���_
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//���_�J���[
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffFadeLogo->Unlock();
}
//=============================================================================
// �I������
//=============================================================================
void UninitFadeLogo(void)
{	//�e�N�X�`���̔j��
	if (g_pTextureFadeLogo != NULL)
	{
		g_pTextureFadeLogo->Release();
		g_pTextureFadeLogo = NULL;
	}
	//���_�o�b�t�@�̔j���̔j��
	if (g_pVtxBuffFadeLogo != NULL)
	{
		g_pVtxBuffFadeLogo->Release();
		g_pVtxBuffFadeLogo = NULL;
	}
}
//=============================================================================
// �X�V����
//=============================================================================
void UpdateFadeLogo(void)
{
	FADE fade = GetFade();
	if (fade != FADE_NONE)
	{//�������ĂȂ����
		if (fade == FADE_IN)
		{//�t�F�[�h�C��/
			g_colorFadeLogo.a -= 0.02f;	//��ʂ𓧖��ɂ��Ă���
			if (g_colorFadeLogo.a <= 0.0f)
			{
				g_colorFadeLogo.a = 0.0f;	//�l�����Ȃ����ď�����
				fade = FADE_NONE;	//�������ĂȂ����
			}
		}
		else if (fade == FADE_OUT)
		{//�t�F�[�h�A�E�g���
			g_colorFadeLogo.r = 1.0f;
			g_colorFadeLogo.g = 1.0f;
			g_colorFadeLogo.b = 1.0f;
			g_colorFadeLogo.a += 0.02f;		//��ʂ�s������
			if (g_colorFadeLogo.a >= 1.0f)
			{
				g_colorFadeLogo.a = 1.0f;	//�l�����Ȃ����ď�����
			}
		}
		VERTEX_2D *pVtx;								//���_���ւ̃|�C���^	
		g_pVtxBuffFadeLogo->Lock(0, 0, (void**)&pVtx, 0);	//���_�o�b�t�@�����b�N�����_�f�[�^�̃|�C���^���擾	
		//���_�J���[
		pVtx[0].col = g_colorFadeLogo;
		pVtx[1].col = g_colorFadeLogo;
		pVtx[2].col = g_colorFadeLogo;
		pVtx[3].col = g_colorFadeLogo;
		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffFadeLogo->Unlock();
	}
}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawFadeLogo(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X���擾����
	pDevice = GetDevice();
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffFadeLogo, 0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g��ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureFadeLogo);
	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,	//�J�n���钸�_�̃C���f�b�N�X
		2); //�`�悷��v���~�e�B�u��
}