//=============================================================================
// 
// �}�b�v�̏��� [map.cpp]
// Author : Mikiya Meguro
//
//=============================================================================
#include "Map.h"
#include "input.h"
#include "mapPlayer.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAP_TEXTURENAME		"data\\TEXTURE\\MapField001.jpg"	//�e�N�X�`���̃t�@�C����
#define POS_X				(0)							//������WX
#define POS_Y				(420)							//������WY	
#define BG_WIDTH			(300)						//�����`�̉������W
#define BG_HEIGHT			(720)						//�����`�̏c�����W

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureMap = NULL;		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMap = NULL;	//���_�o�b�t�@�ւ̃|�C���^
//*****************************************************************************
// �}�b�v
//*****************************************************************************
void InitMap(void)
{	
	//���[�J���ϐ�
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		MAP_TEXTURENAME,
		&g_pTextureMap);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMap,
		NULL);

	//���_�o�b�t�@�����b�N�����_�f�[�^�̃|�C���^���擾
	g_pVtxBuffMap->Lock(0, 0, (void**)&pVtx, 0);
	//���_���W
	pVtx[0].pos = D3DXVECTOR3(POS_X, POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(POS_X + BG_WIDTH, POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(POS_X, BG_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(POS_X + BG_WIDTH, BG_HEIGHT, 0.0f);
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
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffMap->Unlock();	

	//�}�b�v�v���C���[����������
	InitMapPlayer();
}
//=============================================================================
// �I������
//=============================================================================
void UninitMap(void)
{	//�e�N�X�`���̔j��
	if (g_pTextureMap != NULL)
	{
		g_pTextureMap->Release();
		g_pTextureMap = NULL;
	}
	//���_�o�b�t�@�̔j���̔j��
	if (g_pVtxBuffMap != NULL)
	{
		g_pVtxBuffMap->Release();
		g_pVtxBuffMap = NULL;
	}
	//�}�b�v�v���C���[�I������
	UninitMapPlayer();

}
//=============================================================================
// �X�V����
//=============================================================================
void UpdateMap(void)
{
	//�}�b�v�v���C���[����������
	UpdateMapPlayer();

}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawMap(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X���擾����
	pDevice = GetDevice();
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffMap, 0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g��ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureMap);
	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,	//�J�n���钸�_�̃C���f�b�N�X
		2); //�`�悷��v���~�e�B�u��

	//�}�b�v�v���C���[�`�揈��
	DrawMapPlayer();

}
