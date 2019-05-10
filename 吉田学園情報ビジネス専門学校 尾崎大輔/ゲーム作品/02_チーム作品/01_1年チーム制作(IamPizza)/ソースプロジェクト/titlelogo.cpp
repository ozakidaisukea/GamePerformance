//=============================================================================
// ���ƍ쐬
// �w�i�̏��� [titlelogo.cpp]
// Author : Mikiya Meguro
//
//=============================================================================
#include "main.h"
#include "titlelogo.h"
#include "input.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TITLELOGO_TEXTURENAME	"data\\TEXTURE\\title000.png"//�e�N�X�`���̃t�@�C����
#define TEX_LEFT				(0.0f)						//�e�N�X�`�����WU��
#define TEX_RIGHT				(1.0f)						//�e�N�X�`�����WU�E
#define TEX_TOP					(0.0f)						//�e�N�X�`�����WV��
#define TEX_BOT					(1.0f)						//�e�N�X�`�����WV��
#define TITLELOGO_POS_X			(300)						//���_���WX�̈ړ���
#define TITLELOGO_POS_Y			(100)						//���_���WY�̈ړ���

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		 g_pTextureTitleLogo = NULL;					//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9	 g_pVtxBuffTitleLogo = NULL;					//���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3				 g_Titlepos;//�ʒu
D3DXVECTOR3				 g_Titlemove;//�ړ���
float					 g_fMoveTitleY;
//*****************************************************************************
// �|���S��
//*****************************************************************************
void InitTitleLogo(void)
{	//���[�J���ϐ�
	g_Titlepos = D3DXVECTOR3(640.0f, -30.0f, 0.0f); //�ʒu
	g_Titlemove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	 //�ʒu
	g_fMoveTitleY = 1;
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		TITLELOGO_TEXTURENAME,
		&g_pTextureTitleLogo);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitleLogo,
		NULL);

	//���_�o�b�t�@�����b�N�����_�f�[�^�̃|�C���^���擾
	g_pVtxBuffTitleLogo->Lock(0, 0, (void**)&pVtx, 0);
	//���_���W
	pVtx[0].pos = D3DXVECTOR3(g_Titlepos.x - TITLELOGO_POS_X, g_Titlepos.y - TITLELOGO_POS_Y, g_Titlepos.z);
	pVtx[1].pos = D3DXVECTOR3(g_Titlepos.x + TITLELOGO_POS_X, g_Titlepos.y - TITLELOGO_POS_Y, g_Titlepos.z);
	pVtx[2].pos = D3DXVECTOR3(g_Titlepos.x - TITLELOGO_POS_X, g_Titlepos.y + TITLELOGO_POS_Y, g_Titlepos.z);
	pVtx[3].pos = D3DXVECTOR3(g_Titlepos.x + TITLELOGO_POS_X, g_Titlepos.y + TITLELOGO_POS_Y, g_Titlepos.z);
	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(TEX_LEFT, TEX_TOP);
	pVtx[1].tex = D3DXVECTOR2(TEX_RIGHT, TEX_TOP);
	pVtx[2].tex = D3DXVECTOR2(TEX_LEFT, TEX_BOT);
	pVtx[3].tex = D3DXVECTOR2(TEX_RIGHT, TEX_BOT);
	//���_
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//���_�J���[
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTitleLogo->Unlock();
}
//=============================================================================
// �I������
//=============================================================================
void UninitTitleLogo(void)
{	//�e�N�X�`���̔j��
	if (g_pTextureTitleLogo != NULL)
	{
		g_pTextureTitleLogo->Release();
		g_pTextureTitleLogo = NULL;
	}
	//���_�o�b�t�@�̔j���̔j��
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

	if (g_Titlepos.y >= 220.0f)
	{
		g_fMoveTitleY = 0;
	}

	//�ʒu�X�V
	g_Titlemove.y = 2 * g_fMoveTitleY;
	g_Titlepos.y += g_Titlemove.y;

	//�ʒu�̍X�V
	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^
	//���_�o�b�t�@�����b�N�����_�f�[�^�̃|�C���^���擾
	g_pVtxBuffTitleLogo->Lock(0, 0, (void**)&pVtx, 0);
	//���_���W
	pVtx[0].pos = D3DXVECTOR3(g_Titlepos.x - TITLELOGO_POS_X, g_Titlepos.y - TITLELOGO_POS_Y, g_Titlepos.z);
	pVtx[1].pos = D3DXVECTOR3(g_Titlepos.x + TITLELOGO_POS_X, g_Titlepos.y - TITLELOGO_POS_Y, g_Titlepos.z);
	pVtx[2].pos = D3DXVECTOR3(g_Titlepos.x - TITLELOGO_POS_X, g_Titlepos.y + TITLELOGO_POS_Y, g_Titlepos.z);
	pVtx[3].pos = D3DXVECTOR3(g_Titlepos.x + TITLELOGO_POS_X, g_Titlepos.y + TITLELOGO_POS_Y, g_Titlepos.z);
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTitleLogo->Unlock();
}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawTitleLogo(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X���擾����
	pDevice = GetDevice();

	//�A���t�@�e�X�g(�����F��`�悵�Ȃ��悤��)
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 150);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTitleLogo, 0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g��ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureTitleLogo);
	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,	//�J�n���钸�_�̃C���f�b�N�X
		2); //�`�悷��v���~�e�B�u��

	//�����_�[�X�e�[�g�̐ݒ�����ɖ߂�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}
//=============================================================================
// �^�C�g�����S�擾����
//=============================================================================
D3DXVECTOR3 *GetTitleLogo(void)
{
	return &g_Titlepos;
}
//=============================================================================
// �^�C�g�����S�̃Z�b�g
//=============================================================================
void SetTitleLogo(D3DXVECTOR3 nTitleLogo)
{
	g_Titlepos = nTitleLogo;
}