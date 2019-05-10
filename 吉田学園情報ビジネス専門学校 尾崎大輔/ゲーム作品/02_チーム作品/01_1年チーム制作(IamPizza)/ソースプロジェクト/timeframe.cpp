//=============================================================================
// 
// �^�C���t���[���̏��� [TimeFrame.cpp]
// Author : Mikiya Meguro
//
//=============================================================================
#include "main.h"
#include "timeframe.h"
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TIME_TEXTURENAME	"data\\TEXTURE\\frame_timer.png"	//�e�N�X�`���̃t�@�C����
#define TF_X				(540)								//������WX
#define TF_Y				(5)									//������WY	
#define TF_WIDTH			(740)								//�����`�̉������W
#define TF_HEIGHT			(80)								//�����`�̏c�����W
#define TEX_LEFT			(0.0f)								//�e�N�X�`�����WU��
#define TEX_RIGHT			(1.0f)								//�e�N�X�`�����WU�E
#define TEX_TOP				(0.0f)								//�e�N�X�`�����WV��
#define TEX_BOT				(1.0f)								//�e�N�X�`�����WV��

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureTimeFrame = NULL;		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTimeFrame = NULL;	//���_�o�b�t�@�ւ̃|�C���^
//*****************************************************************************
// ������
//*****************************************************************************
void InitTimeFrame(void)
{	//���[�J���ϐ�
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		TIME_TEXTURENAME,
		&g_pTextureTimeFrame);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTimeFrame,
		NULL);

	//���_�o�b�t�@�����b�N�����_�f�[�^�̃|�C���^���擾
	g_pVtxBuffTimeFrame->Lock(0, 0, (void**)&pVtx, 0);
	//���_���W
	pVtx[0].pos = D3DXVECTOR3(TF_X, TF_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(TF_WIDTH, TF_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(TF_X, TF_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(TF_WIDTH, TF_HEIGHT, 0.0f);
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
	g_pVtxBuffTimeFrame->Unlock();
}
//=============================================================================
// �I������
//=============================================================================
void UninitTimeFrame(void)
{	//�e�N�X�`���̔j��
	if (g_pTextureTimeFrame != NULL)
	{
		g_pTextureTimeFrame->Release();
		g_pTextureTimeFrame = NULL;
	}
	//���_�o�b�t�@�̔j���̔j��
	if (g_pVtxBuffTimeFrame != NULL)
	{
		g_pVtxBuffTimeFrame->Release();
		g_pVtxBuffTimeFrame = NULL;
	}
}
//=============================================================================
// �X�V����
//=============================================================================
void UpdateTimeFrame(void)
{
}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawTimeFrame(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X���擾����
	pDevice = GetDevice();
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTimeFrame, 0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g��ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureTimeFrame);
	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,	//�J�n���钸�_�̃C���f�b�N�X
		2); //�`�悷��v���~�e�B�u��
}