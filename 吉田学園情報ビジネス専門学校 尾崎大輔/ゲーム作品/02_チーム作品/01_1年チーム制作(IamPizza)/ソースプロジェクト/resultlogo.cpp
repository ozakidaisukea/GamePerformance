//=============================================================================
// ���ƍ쐬
// �w�i�̏��� [rankingbg.cpp]
// Author : Mikiya Meguro
//
//=============================================================================
#include "main.h"
#include "resultlogo.h"
#include "input.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define BG_TEXTURENAME		"data\\TEXTURE\\result_logo000.png"//�e�N�X�`���̃t�@�C����
#define POS_X				(0)							//������WX
#define POS_Y				(0)							//������WY	
#define BG_WIDTH			(SCREEN_WIDTH)				//�����`�̉������W
#define BG_HEIGHT			(SCREEN_HEIGHT)				//�����`�̏c�����W
#define COUNTER_ANIM_RESET	(200)						//�A�j���[�V�������Z�b�g�J�E���g
#define TEX_POS_X_INIT		(1.0f)						//�e�N�X�`�����WU�̏����ʒu
#define TEX_POS_Y_INIT		(0.005f)					//�e�N�X�`�����WV�̏����ʒu
#define TEX_LEFT			(0.0f)						//�e�N�X�`�����WU��
#define TEX_RIGHT			(1.0f)						//�e�N�X�`�����WU�E
#define TEX_TOP				(0.0f)						//�e�N�X�`�����WV��
#define TEX_BOT				(1.0f)						//�e�N�X�`�����WV��
#define RESULTLOGO_POS_X	(350)						//���_���WX�̈ړ���
#define RESULTLOGO_POS_Y	(60)						//���_���WY�̈ړ���

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		 g_pTextureResultLogo = NULL;					//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9	 g_pVtxBuffResultLogo = NULL;					//���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3				 g_Resultpos;//�ʒu
D3DXVECTOR3				 g_Resultmove;//�ړ���
float					 g_fMoveResultY = 1;
//*****************************************************************************
// �|���S��
//*****************************************************************************
void InitResultLogo(void)
{	//���[�J���ϐ�
	g_Resultpos = D3DXVECTOR3(640.0f, 180.0f, 0.0f); //�ʒu
	g_Resultmove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	 //�ʒu
	g_fMoveResultY = 1;
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		BG_TEXTURENAME,
		&g_pTextureResultLogo);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResultLogo,
		NULL);

	//���_�o�b�t�@�����b�N�����_�f�[�^�̃|�C���^���擾
	g_pVtxBuffResultLogo->Lock(0, 0, (void**)&pVtx, 0);
	//���_���W
	pVtx[0].pos = D3DXVECTOR3(g_Resultpos.x - RESULTLOGO_POS_X, g_Resultpos.y - RESULTLOGO_POS_Y, g_Resultpos.z);
	pVtx[1].pos = D3DXVECTOR3(g_Resultpos.x + RESULTLOGO_POS_X, g_Resultpos.y - RESULTLOGO_POS_Y, g_Resultpos.z);
	pVtx[2].pos = D3DXVECTOR3(g_Resultpos.x - RESULTLOGO_POS_X, g_Resultpos.y + RESULTLOGO_POS_Y, g_Resultpos.z);
	pVtx[3].pos = D3DXVECTOR3(g_Resultpos.x + RESULTLOGO_POS_X, g_Resultpos.y + RESULTLOGO_POS_Y, g_Resultpos.z);
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
	g_pVtxBuffResultLogo->Unlock();
}
//=============================================================================
// �I������
//=============================================================================
void UninitResultLogo(void)
{	//�e�N�X�`���̔j��
	if (g_pTextureResultLogo != NULL)
	{
		g_pTextureResultLogo->Release();
		g_pTextureResultLogo = NULL;
	}
	//���_�o�b�t�@�̔j���̔j��
	if (g_pVtxBuffResultLogo != NULL)
	{
		g_pVtxBuffResultLogo->Release();
		g_pVtxBuffResultLogo = NULL;
	}
}
//=============================================================================
// �X�V����
//=============================================================================
void UpdateResultLogo(void)
{

	//if (g_Resultpos.y >= 220.0f)
	//{
	//	g_fMoveResultY = 0;
	//}

	////�ʒu�X�V
	//g_Resultmove.y = 2 * g_fMoveResultY;
	//g_Resultpos.y += g_Resultmove.y;

	////�ʒu�̍X�V
	//VERTEX_2D *pVtx;	//���_���ւ̃|�C���^
	////���_�o�b�t�@�����b�N�����_�f�[�^�̃|�C���^���擾
	//g_pVtxBuffResultLogo->Lock(0, 0, (void**)&pVtx, 0);
	////���_���W
	//pVtx[0].pos = D3DXVECTOR3(g_Resultpos.x - RESULTLOGO_POS_X, g_Resultpos.y - RESULTLOGO_POS_Y, g_Resultpos.z);
	//pVtx[1].pos = D3DXVECTOR3(g_Resultpos.x + RESULTLOGO_POS_X, g_Resultpos.y - RESULTLOGO_POS_Y, g_Resultpos.z);
	//pVtx[2].pos = D3DXVECTOR3(g_Resultpos.x - RESULTLOGO_POS_X, g_Resultpos.y + RESULTLOGO_POS_Y, g_Resultpos.z);
	//pVtx[3].pos = D3DXVECTOR3(g_Resultpos.x + RESULTLOGO_POS_X, g_Resultpos.y + RESULTLOGO_POS_Y, g_Resultpos.z);
	////���_�o�b�t�@���A�����b�N����
	//g_pVtxBuffResultLogo->Unlock();
}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawResultLogo(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X���擾����
	pDevice = GetDevice();
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffResultLogo, 0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g��ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureResultLogo);
	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,	//�J�n���钸�_�̃C���f�b�N�X
		2); //�`�悷��v���~�e�B�u��
}
//=============================================================================
// �^�C�g�����S�擾����
//=============================================================================
D3DXVECTOR3 *GetResultLogo(void)
{
	return &g_Resultpos;
}
//=============================================================================
// �^�C�g�����S�̃Z�b�g
//=============================================================================
void SetResultLogo(D3DXVECTOR3 nResultLogo)
{
	g_Resultpos = nResultLogo;
}