//=============================================================================
// 
// �}�b�v�v���C���[�v���C���[�̏��� [mapplayer.cpp]
// Author : Mikiya Meguro
//
//=============================================================================
#include "mapplayer.h"
#include "input.h"
#include "player.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAPPLAYER_TEXTURENAME		"data\\TEXTURE\\�ۂ�����.png"	//�e�N�X�`���̃t�@�C����
#define POS_X				(150)						//������WX
#define POS_Y				(80)						//������WY	
#define MAPPLAYER_WIDTH		(30)						//�����`�̉������W
#define MAPPLAYER_HEIGHT	(30)						//�����`�̏c�����W
#define MINIMAP				(150)
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureMapPlayer = NULL;		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMapPlayer = NULL;	//���_�o�b�t�@�ւ̃|�C���^
MAPPLAYER	g_MapPlayer;
//*****************************************************************************
// �}�b�v�v���C���[
//*****************************************************************************
void InitMapPlayer(void)
{	
	//���[�J���ϐ�
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	PLAYER *pPlayer = GetPlayer();
	D3DXVECTOR3 mapPlayer = pPlayer->pos / 10;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		MAPPLAYER_TEXTURENAME,
		&g_pTextureMapPlayer);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMapPlayer,
		NULL);

	//���_�o�b�t�@�����b�N�����_�f�[�^�̃|�C���^���擾
	g_pVtxBuffMapPlayer->Lock(0, 0, (void**)&pVtx, 0);
	//���_���W
	pVtx[0].pos = D3DXVECTOR3(mapPlayer.x /*+ MAPPLAYER_WIDTH*/, mapPlayer.z, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(mapPlayer.x /*+ MAPPLAYER_WIDTH*/ + MAPPLAYER_WIDTH, mapPlayer.z, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(mapPlayer.x /*+ MAPPLAYER_WIDTH*/, mapPlayer.z + MAPPLAYER_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(mapPlayer.x /*+ MAPPLAYER_WIDTH*/ + MAPPLAYER_WIDTH, mapPlayer.z + MAPPLAYER_HEIGHT, 0.0f);
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
	g_pVtxBuffMapPlayer->Unlock();	

	g_MapPlayer.nMapBorder = 1;
	g_MapPlayer.move = D3DXVECTOR3(0.0f,0.0f,0.0f);
	g_MapPlayer.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_MapPlayer.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MapPlayer.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}
//=============================================================================
// �I������
//=============================================================================
void UninitMapPlayer(void)
{	//�e�N�X�`���̔j��
	if (g_pTextureMapPlayer != NULL)
	{
		g_pTextureMapPlayer->Release();
		g_pTextureMapPlayer = NULL;
	}
	//���_�o�b�t�@�̔j���̔j��
	if (g_pVtxBuffMapPlayer != NULL)
	{
		g_pVtxBuffMapPlayer->Release();
		g_pVtxBuffMapPlayer = NULL;
	}
}
//=============================================================================
// �X�V����
//=============================================================================
void UpdateMapPlayer(void)
{
	PLAYER *pPlayer = GetPlayer();

	D3DXVECTOR3 mapPlayer = pPlayer->pos / 20;
	//�}�b�v�̈ʒu������
	mapPlayer.z -= 420;

	//�t�B�[���h�̑傫���̔���
	if (MINIMAP - MAPPLAYER_WIDTH / 2 <= mapPlayer.x )
	{
		g_MapPlayer.nMapBorder += 1;
		mapPlayer.x += (-MINIMAP + MAPPLAYER_WIDTH / 2) * 2;
	}
	if (-MINIMAP + MAPPLAYER_WIDTH / 2 >= mapPlayer.x)
	{
		g_MapPlayer.nMapBorder -= 1;
		mapPlayer.x += (MINIMAP + MAPPLAYER_WIDTH / 2) * 2;
	}
	//if (-MINIMAP + MAPPLAYER_HEIGHT / 2 >= mapPlayer.z)
	//{
	//	mapPlayer.z = -MINIMAP + MAPPLAYER_HEIGHT / 2;
	//}
	//if (MINIMAP - MAPPLAYER_HEIGHT / 2 <= mapPlayer.z)
	//{
	//	mapPlayer.z = MINIMAP - MAPPLAYER_HEIGHT / 2;
	//}

	VERTEX_2D *pVtx;//���_���ւ̃|�C���^
	
	//���_�o�b�t�@�����b�N�����_�f�[�^�̃|�C���^���擾
	g_pVtxBuffMapPlayer->Lock(0, 0, (void**)&pVtx, 0);
	
	////���_���W
	//pVtx[0].pos = D3DXVECTOR3(POS_X + mapPlayer.x, POS_Y - mapPlayer.z, 0.0f);
	//pVtx[1].pos = D3DXVECTOR3(POS_X + MAPPLAYER_WIDTH + mapPlayer.x, POS_Y - mapPlayer.z, 0.0f);
	//pVtx[2].pos = D3DXVECTOR3(POS_X + mapPlayer.x, MAPPLAYER_HEIGHT - mapPlayer.z, 0.0f);
	//pVtx[3].pos = D3DXVECTOR3(POS_X + MAPPLAYER_WIDTH + mapPlayer.x, MAPPLAYER_HEIGHT - mapPlayer.z, 0.0f);
	//���_���W
	pVtx[0].pos = D3DXVECTOR3(mapPlayer.x - MAPPLAYER_WIDTH + 150, -mapPlayer.z - MAPPLAYER_HEIGHT + 150, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(mapPlayer.x + MAPPLAYER_WIDTH + 150, -mapPlayer.z - MAPPLAYER_HEIGHT + 150, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(mapPlayer.x - MAPPLAYER_WIDTH + 150, -mapPlayer.z + MAPPLAYER_HEIGHT + 150, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(mapPlayer.x + MAPPLAYER_WIDTH + 150, -mapPlayer.z + MAPPLAYER_HEIGHT + 150, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffMapPlayer->Unlock();
}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawMapPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X���擾����
	pDevice = GetDevice();
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffMapPlayer, 0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g��ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureMapPlayer);
	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,	//�J�n���钸�_�̃C���f�b�N�X
		2); //�`�悷��v���~�e�B�u��
}
