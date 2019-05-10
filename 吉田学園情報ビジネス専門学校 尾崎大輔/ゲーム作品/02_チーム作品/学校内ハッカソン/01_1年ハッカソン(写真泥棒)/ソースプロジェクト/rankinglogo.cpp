//=============================================================================
//
// �����L���O���S���� [rankinglogo.cpp]
// Author : Niwa Hodaka
//
//=============================================================================
#include "rankinglogo.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_NAME      "data/TEXTURE/rankinglogo000.png"  // �ǂݍ��ރe�N�X�`���t�@�C����
#define TEXTURE_SIZEX     (460)                              // �e�N�X�`���𒣂�t���镝
#define TEXTURE_SIZEY     (70)                               // �e�N�X�`���𒣂�t���鍂��

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexRankingLogo(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureRankingLogo = NULL; // �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRankingLogo = NULL; // ���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3             g_PosRankingLogo;             // �����L���O���S���W
D3DXCOLOR				g_colorRankingLogo;		      // �����L���O���S�F

//=============================================================================
// ����������
//=============================================================================
void InitRankingLogo(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �l�̏�����
	g_PosRankingLogo = D3DXVECTOR3(SCREEN_WIDTH / 2, 80, 0.0f);
	g_colorRankingLogo = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

	// ���_���̐ݒ�
	MakeVertexRankingLogo(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitRankingLogo(void)
{
	// �e�N�X�`���̔j��
	if (g_pTextureRankingLogo != NULL)
	{
		g_pTextureRankingLogo->Release();
		g_pTextureRankingLogo = NULL;
	}


	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffRankingLogo != NULL)
	{
		g_pVtxBuffRankingLogo->Release();
		g_pVtxBuffRankingLogo = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateRankingLogo(void)
{
}
//=============================================================================
// �^�C�g�����
//=============================================================================
void DrawRankingLogo(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffRankingLogo, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureRankingLogo);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexRankingLogo(LPDIRECT3DDEVICE9 pDevice)
{
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_NAME,
		&g_pTextureRankingLogo);

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRankingLogo,
		NULL);

	VERTEX_2D *pVtx;   // ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffRankingLogo->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W
	pVtx[0].pos = D3DXVECTOR3(g_PosRankingLogo.x - TEXTURE_SIZEX, g_PosRankingLogo.y - TEXTURE_SIZEY, g_PosRankingLogo.z);
	pVtx[1].pos = D3DXVECTOR3(g_PosRankingLogo.x + TEXTURE_SIZEX, g_PosRankingLogo.y - TEXTURE_SIZEY, g_PosRankingLogo.z);
	pVtx[2].pos = D3DXVECTOR3(g_PosRankingLogo.x - TEXTURE_SIZEX, g_PosRankingLogo.y + TEXTURE_SIZEY, g_PosRankingLogo.z);
	pVtx[3].pos = D3DXVECTOR3(g_PosRankingLogo.x + TEXTURE_SIZEX, g_PosRankingLogo.y + TEXTURE_SIZEY, g_PosRankingLogo.z);

	// ���_�e�N�X�`��
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[
	pVtx[0].col = g_colorRankingLogo;
	pVtx[1].col = g_colorRankingLogo;
	pVtx[2].col = g_colorRankingLogo;
	pVtx[3].col = g_colorRankingLogo;

	// �e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffRankingLogo->Unlock();
}