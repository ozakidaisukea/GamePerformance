//=============================================================================
// ���ƍ쐬
// �w�i�̏��� [pause.cpp]
// Author : Mikiya Meguro
//
//=============================================================================
#include "main.h"
#include "pause.h"
#include "input.h"
#include "pauseselect.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define BG_TEXTURENAME		"data\\TEXTURE\\Building\\2.png"	//�e�N�X�`���̃t�@�C����
#define POS_X				(400)							//������WX
#define POS_Y				(100)							//������WY	
#define BG_WIDTH			(900)				//�����`�̉������W
#define BG_HEIGHT			(600)				//�����`�̏c�����W
#define COUNTER_ANIM_RESET	(200)						//�A�j���[�V�������Z�b�g�J�E���g
#define TEX_POS_X_INIT		(1.0f)						//�e�N�X�`�����WU�̏����ʒu
#define TEX_POS_Y_INIT		(0.005f)					//�e�N�X�`�����WV�̏����ʒu
#define TEX_LEFT			(0.0f)						//�e�N�X�`�����WU��
#define TEX_RIGHT			(1.0f)						//�e�N�X�`�����WU�E
#define TEX_TOP				(0.0f)						//�e�N�X�`�����WV��
#define TEX_BOT				(1.0f)						//�e�N�X�`�����WV��

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTexturePause = NULL;		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPause = NULL;	//���_�o�b�t�@�ւ̃|�C���^
bool bDraw;
//*****************************************************************************
// �|���S��
//*****************************************************************************
void InitPause(void)
{	//���[�J���ϐ�
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		BG_TEXTURENAME,
		&g_pTexturePause);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPause,
		NULL);

	//���_�o�b�t�@�����b�N�����_�f�[�^�̃|�C���^���擾
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);
	//���_���W
	pVtx[0].pos = D3DXVECTOR3(POS_X, POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(BG_WIDTH, POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(POS_X, BG_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(BG_WIDTH, BG_HEIGHT, 0.0f);
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
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPause->Unlock();

	InitPauseSelect();

	bDraw = true;
}
//=============================================================================
// �I������
//=============================================================================
void UninitPause(void)
{	//�e�N�X�`���̔j��
	if (g_pTexturePause != NULL)
	{
		g_pTexturePause->Release();
		g_pTexturePause = NULL;
	}
	//���_�o�b�t�@�̔j���̔j��
	if (g_pVtxBuffPause != NULL)
	{
		g_pVtxBuffPause->Release();
		g_pVtxBuffPause = NULL;
	}

	UninitPauseSelect();
}
//=============================================================================
// �X�V����
//=============================================================================
void UpdatePause(void)
{
	if (GetKeyboardTrigger(DIK_O) == true)
	{
		bDraw = bDraw ? false : true;
	}
	UpdatePauseSelect();
}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawPause(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X���擾����
	pDevice = GetDevice();
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPause, 0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g��ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturePause);
	if (bDraw == true)
	{
		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			0,	//�J�n���钸�_�̃C���f�b�N�X
			2); //�`�悷��v���~�e�B�u��
		DrawPauseSelect();
	}
}