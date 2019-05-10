//=============================================================================
// ���ƍ쐬
// �w�i�̏��� [Resultrogo.cpp]
// Author : Ozaki
//
//=============================================================================
#include "main.h"
#include "Resultrogo.h"
#include "input.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define ResultrogoLOGO_TEXTURENAME	"data\\TEXTURE\\zyozyo.png"//�e�N�X�`���̃t�@�C����
#define TEX_LEFT				(0.0f)						//�e�N�X�`�����WU��
#define TEX_RIGHT				(1.0f)						//�e�N�X�`�����WU�E
#define TEX_TOP					(0.0f)						//�e�N�X�`�����WV��
#define TEX_BOT					(1.0f)						//�e�N�X�`�����WV��
#define ResultrogoLOGO_POS_X	(300)						//���_���WX�̈ړ���
#define ResultrogoLOGO_POS_Y	(100)						//���_���WY�̈ړ���

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		 g_pTextureResultrogo = NULL;					//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9	 g_pVtxBuffResultrogo = NULL;					//���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3				 g_Resultrogopos;//�ʒu
D3DXVECTOR3				 g_Resultrogomove;//�ړ���
float					 g_fMoveResultrogoY;
//*****************************************************************************
// �|���S��
//*****************************************************************************
void InitResultrogo(void)
{	//���[�J���ϐ�
	g_Resultrogopos = D3DXVECTOR3(1000.0f, -30.0f, 0.0f); //�ʒu
	g_Resultrogomove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	  //�ʒu
	g_fMoveResultrogoY = 1;
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		ResultrogoLOGO_TEXTURENAME,
		&g_pTextureResultrogo);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResultrogo,
		NULL);

	//���_�o�b�t�@�����b�N�����_�f�[�^�̃|�C���^���擾
	g_pVtxBuffResultrogo->Lock(0, 0, (void**)&pVtx, 0);
	//���_���W
	pVtx[0].pos = D3DXVECTOR3(g_Resultrogopos.x - ResultrogoLOGO_POS_X, g_Resultrogopos.y - ResultrogoLOGO_POS_Y, g_Resultrogopos.z);
	pVtx[1].pos = D3DXVECTOR3(g_Resultrogopos.x + ResultrogoLOGO_POS_X, g_Resultrogopos.y - ResultrogoLOGO_POS_Y, g_Resultrogopos.z);
	pVtx[2].pos = D3DXVECTOR3(g_Resultrogopos.x - ResultrogoLOGO_POS_X, g_Resultrogopos.y + ResultrogoLOGO_POS_Y, g_Resultrogopos.z);
	pVtx[3].pos = D3DXVECTOR3(g_Resultrogopos.x + ResultrogoLOGO_POS_X, g_Resultrogopos.y + ResultrogoLOGO_POS_Y, g_Resultrogopos.z);
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
	g_pVtxBuffResultrogo->Unlock();
}
//=============================================================================
// �I������
//=============================================================================
void UninitResultrogo(void)
{	//�e�N�X�`���̔j��
	if (g_pTextureResultrogo != NULL)
	{
		g_pTextureResultrogo->Release();
		g_pTextureResultrogo = NULL;
	}
	//���_�o�b�t�@�̔j���̔j��
	if (g_pVtxBuffResultrogo != NULL)
	{
		g_pVtxBuffResultrogo->Release();
		g_pVtxBuffResultrogo = NULL;
	}
}
//=============================================================================
// �X�V����
//=============================================================================
void UpdateResultrogo(void)
{

	if (g_Resultrogopos.y >= SCREEN_HEIGHT - 48)
	{
		g_fMoveResultrogoY = 0;
	}

	//�ʒu�X�V
	g_Resultrogomove.y = 5 * g_fMoveResultrogoY;
	g_Resultrogopos.y += g_Resultrogomove.y;

	//�ʒu�̍X�V
	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^
	//���_�o�b�t�@�����b�N�����_�f�[�^�̃|�C���^���擾
	g_pVtxBuffResultrogo->Lock(0, 0, (void**)&pVtx, 0);
	//���_���W
	pVtx[0].pos = D3DXVECTOR3(g_Resultrogopos.x - ResultrogoLOGO_POS_X, g_Resultrogopos.y - ResultrogoLOGO_POS_Y, g_Resultrogopos.z);
	pVtx[1].pos = D3DXVECTOR3(g_Resultrogopos.x + ResultrogoLOGO_POS_X, g_Resultrogopos.y - ResultrogoLOGO_POS_Y, g_Resultrogopos.z);
	pVtx[2].pos = D3DXVECTOR3(g_Resultrogopos.x - ResultrogoLOGO_POS_X, g_Resultrogopos.y + ResultrogoLOGO_POS_Y, g_Resultrogopos.z);
	pVtx[3].pos = D3DXVECTOR3(g_Resultrogopos.x + ResultrogoLOGO_POS_X, g_Resultrogopos.y + ResultrogoLOGO_POS_Y, g_Resultrogopos.z);
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffResultrogo->Unlock();
}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawResultrogo(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X���擾����
	pDevice = GetDevice();

	//�A���t�@�e�X�g(�����F��`�悵�Ȃ��悤��)
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 150);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffResultrogo, 0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g��ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureResultrogo);
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
D3DXVECTOR3 *GetResultrogo(void)
{
	return &g_Resultrogopos;
}
//=============================================================================
// �^�C�g�����S�̃Z�b�g
//=============================================================================
void SetResultrogo(D3DXVECTOR3 nResultrogoLogo)
{
	g_Resultrogopos = nResultrogoLogo;
}