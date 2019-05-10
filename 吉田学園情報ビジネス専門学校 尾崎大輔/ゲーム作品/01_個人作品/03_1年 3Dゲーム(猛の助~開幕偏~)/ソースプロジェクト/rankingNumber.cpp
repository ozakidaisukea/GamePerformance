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
#define RANKING_NUM			(5)

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureRankingNum = NULL;		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRankingNum = NULL;				//�e�N�X�`���̃|�C���^

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
	pDevise->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 *RANKING_NUM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRankingNum,
		NULL);

	//���[�J���ϐ�
	VERTEX_2D*pVtx;								//���_���ւ̃|�C���^

	int Ypos = 0;
	float TexUP = 0;
	float TexDOWN = 0.2;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^�̎擾
	g_pVtxBuffRankingNum->Lock(0, 0, (void**)&pVtx, 0);

	for (int RankingNum = 0; RankingNum < RANKING_NUM; RankingNum++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(400, 100 + Ypos, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(500, 100 + Ypos, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(400, 200 + Ypos, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(500, 200 + Ypos, 0.0f);

		//�e�N�X�`���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, TexUP);
		pVtx[1].tex = D3DXVECTOR2(1.0f, TexUP);
		pVtx[2].tex = D3DXVECTOR2(0.0f, TexDOWN);
		pVtx[3].tex = D3DXVECTOR2(1.0f, TexDOWN);

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

		// �P��
		if (RankingNum == 0)
		{
			pVtx[0].col = D3DCOLOR_RGBA(0, 0, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 155, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 0, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(0, 255, 155, 255);

		// �Q��
		}
		if (RankingNum == 1)
		{
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 0, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 55, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 55, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 0, 255);
		}
		// �R��
		if (RankingNum == 2)
		{
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 200, 255);
			pVtx[1].col = D3DCOLOR_RGBA(100, 150, 150, 255);
			pVtx[2].col = D3DCOLOR_RGBA(100, 150, 150, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 200, 255);
		}
		// �S��
		if (RankingNum == 3)
		{
			pVtx[0].col = D3DCOLOR_RGBA(255, 200, 100, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 100, 0, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 100, 0, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 200, 100, 255);
		}
		// �T��
		if (RankingNum == 4)
		{
			
			pVtx[0].col = D3DCOLOR_RGBA(0, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(150, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(150, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(0, 255, 255, 255);
		}

		pVtx += 4;					//���_�f�[�^�̃|�C���^��4���i�߂�
		Ypos += 100;
		TexUP += 0.2;
		TexDOWN += 0.2;
	}

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
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureRankingNum);
	for (int RankingNum = 0; RankingNum < RANKING_NUM; RankingNum++)
	{

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			0 + (4 * RankingNum),
			2);
	}
}