//=============================================================================
//
// �w�i�̏��� [RankingNum.cpp]
// Author : Ozaki
//
//=============================================================================
#include "main.h"
#include "rankingNumber.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define RankingNum_WIDTH	(SCREEN_WIDTH)
#define RankingNum_HEIGHT	(SCREEN_HEIGHT)


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureRankingNum = NULL;				//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRankingNum = NULL;		//�e�N�X�`���̃|�C���^

//=============================================================================
// ����������(�|���S��)
//=============================================================================
void InitRankingNum(void)
{
	LPDIRECT3DDEVICE9 pDevise;						//�f�o�C�X�̃|�C���^
													
	//�f�o�C�X�̎擾
	pDevise = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevise,
		"data\\TEXTURE\\ranking_rank.png",
		&g_pTextureRankingNum);

	//���_�o�b�t�@�̐���
	pDevise->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VRETEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRankingNum,
		NULL);

	//���[�J���ϐ�
	VERTEX_2D*pVtx;								//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^�̎擾
	g_pVtxBuffRankingNum->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(400, 300, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(500, 300, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(400, 400, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(500, 400, 0.0f);

	//�e�N�X�`���̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.2f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.2f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(0, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(0, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(0, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(0, 255, 255, 255);

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffRankingNum->Unlock();
}

//=============================================================================
// �I������(�|���S��)
//=============================================================================
void UninitRankingNum(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureRankingNum != NULL)
	{
		g_pTextureRankingNum->Release();
		g_pTextureRankingNum = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffRankingNum != NULL)
	{
		g_pVtxBuffRankingNum->Release();
		g_pVtxBuffRankingNum = NULL;
	}
}

//=============================================================================
// �X�V����(�|���S��)
//=============================================================================
void UpdateRankingNum(void)
{

}

//=============================================================================
// �`�揈��(�|���S��)
//=============================================================================
void DrawRankingNum(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f���@�C�X���擾
	pDevice = GetDevice();


	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffRankingNum, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VRETEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureRankingNum);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);
}