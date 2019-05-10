//=============================================================================
//
// �����L���O���� [ranking.cpp]
// Author : Ozaki
//
//=============================================================================
#include "score.h"
#include "Game.h"
#include "main.h"
#include "fade.h"
#include "input.h"
#include "sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_Ranking		"data/TEXTURE/Number000.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define MAX_MIKY			(20)
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexRanking(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureRanking = NULL;			// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRanking = NULL;			// ���_�o�b�t�@�ւ̃|�C���^
int						g_nRanking;							// �X�R�A
D3DXVECTOR3				g_posRanking;
int						nScore;
int						rankingtimer;
//=============================================================================
// ����������
//=============================================================================
void InitRanking(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �X�R�A�̏�����
	rankingtimer = 0;

	//�v���C���[�̎擾
	g_nRanking = 0;
	g_posRanking = D3DXVECTOR3(600, 350, 0.0f);

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
		TEXTURE_Ranking,									// �t�@�C���̖��O
		&g_pTextureRanking);								// �e�N�X�`���ւ̃|�C���^

															// ���_���̍쐬
	MakeVertexRanking(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitRanking(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureRanking != NULL)
	{
		g_pTextureRanking->Release();
		g_pTextureRanking = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffRanking != NULL)
	{
		g_pVtxBuffRanking->Release();
		g_pVtxBuffRanking = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateRanking(void)
{
	FADE Fade;
	Fade = GetFade();
	rankingtimer++;


	if (Fade == FADE_NONE)
	{
		if (GetKeyboardTrigger(DIK_RETURN) == true && Fade == FADE_NONE)
		{
			SetFade(MODE_TITLE);
			PlaySound(SOUND_LABEL_SE_DECIDE);

		}
		if (rankingtimer == 700)
		{
			SetFade(MODE_TITLE);
			rankingtimer = 0;
			
		}

	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawRanking(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffRanking, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VRETEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureRanking);

	// �|���S���̕`��
	for (int nCntRanking = 0; nCntRanking < 8; nCntRanking++)
	{
		//�|���S���̔j��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			4 * nCntRanking,
			2);
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexRanking(LPDIRECT3DDEVICE9 pDevice)
{

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 8,
		D3DUSAGE_WRITEONLY,
		FVF_VRETEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRanking,
		NULL);

	VERTEX_2D*pVtx;
	int nRankingda[8];

	//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^�̎擾
	g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);
	nRankingda[0] = g_nRanking / 10000000;
	nRankingda[1] = g_nRanking % 10000000 / 1000000;
	nRankingda[2] = g_nRanking % 1000000 / 100000;
	nRankingda[3] = g_nRanking % 100000 / 10000;
	nRankingda[4] = g_nRanking % 10000 / 1000;
	nRankingda[5] = g_nRanking % 1000 / 100;
	nRankingda[6] = g_nRanking % 100 / 10;
	nRankingda[7] = g_nRanking % 10;

	// ���_����ݒ�
	for (int nCnt = 0; nCnt < 8; nCnt++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_posRanking.x - MAX_MIKY, g_posRanking.y - MAX_MIKY, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posRanking.x + MAX_MIKY, g_posRanking.y - MAX_MIKY, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posRanking.x - MAX_MIKY, g_posRanking.y + MAX_MIKY, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posRanking.x + MAX_MIKY, g_posRanking.y + MAX_MIKY, 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(0, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(0, 255, 0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);

		pVtx[0].tex = D3DXVECTOR2(0.0f + nRankingda[nCnt] * 0.1f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + nRankingda[nCnt] * 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + nRankingda[nCnt] * 0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + nRankingda[nCnt] * 0.1f, 1.0f);

		pVtx += 4;

		g_posRanking.x += 50;
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffRanking->Unlock();
}

//=============================================================================
// �����L���O�̉��Z
//=============================================================================
void AddRanking(int nValue)
{
	VERTEX_2D*pVtx;

	int nRankingda[8];
	int nCntRankingda;

	g_nRanking = nValue;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^�̎擾
	g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);

	nRankingda[0] = g_nRanking / 10000000;
	nRankingda[1] = g_nRanking % 10000000 / 1000000;
	nRankingda[2] = g_nRanking % 1000000 / 100000;
	nRankingda[3] = g_nRanking % 100000 / 10000;
	nRankingda[4] = g_nRanking % 10000 / 1000;
	nRankingda[5] = g_nRanking % 1000 / 100;
	nRankingda[6] = g_nRanking % 100 / 10;
	nRankingda[7] = g_nRanking % 10;

	for (nCntRankingda = 0; nCntRankingda < 8; nCntRankingda++)
	{
		pVtx[0].tex = D3DXVECTOR2(0.0f + nRankingda[nCntRankingda] * 0.1f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + nRankingda[nCntRankingda] * 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + nRankingda[nCntRankingda] * 0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + nRankingda[nCntRankingda] * 0.1f, 1.0f);

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffRanking->Unlock();
}