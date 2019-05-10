//=============================================================================
//
// �X�R�A���� [score.cpp]
// Author : Ozaki
//
//=============================================================================
#include "score.h"
#include "Game.h"
#include "enemy.h"
#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_SCORE		"data/TEXTURE/number000.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define MAX_MIKY			(20)
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexScore(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureScore = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
int						g_nScore;					// �X�R�A
D3DXVECTOR3				g_posScore;
int						g_aScore;
//=============================================================================
// ����������
//=============================================================================
void InitScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �X�R�A�̏�����
	g_nScore = 0;
	g_posScore = D3DXVECTOR3(900, 50, 0.0f);

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
								TEXTURE_SCORE,		// �t�@�C���̖��O
								&g_pTextureScore);	// �e�N�X�`���ւ̃|�C���^

	// ���_���̍쐬
	MakeVertexScore(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitScore(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureScore != NULL)
	{
		g_pTextureScore->Release();
		g_pTextureScore = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffScore != NULL)
	{
		g_pVtxBuffScore->Release();
		g_pVtxBuffScore = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateScore(void)
{

}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
    pDevice->SetStreamSource(0, g_pVtxBuffScore, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VRETEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureScore);

	// �|���S���̕`��
	for (int nCntScore = 0; nCntScore < 8; nCntScore++)
	{
		//�|���S���̔j��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			4 * nCntScore,
			2);
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexScore(LPDIRECT3DDEVICE9 pDevice)
{

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 *8,
		D3DUSAGE_WRITEONLY,
		FVF_VRETEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffScore,
		NULL);

		VERTEX_2D*pVtx;


	//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^�̎擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	// ���_����ݒ�
	for (int nCnt = 0; nCnt < 8; nCnt++)
	{
		//g_aExplosion[nCntExplosion].pos.y -= 10.0f;
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_posScore.x - MAX_MIKY, g_posScore.y - MAX_MIKY, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posScore.x + MAX_MIKY, g_posScore.y - MAX_MIKY, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posScore.x - MAX_MIKY, g_posScore.y + MAX_MIKY, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posScore.x + MAX_MIKY, g_posScore.y + MAX_MIKY, 0.0f);


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

		//�e�N�X�`���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;

		g_posScore.x += 50;
	}
	//g_posScore.x = 1200;

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffScore->Unlock();

}

//=============================================================================
// �X�R�A�̉��Z
//=============================================================================
void AddScore(int nValue)
{
	VERTEX_2D*pVtx;

	int nScoreda[8];
	int nCntScoreda;

	g_nScore += nValue * 2;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^�̎擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	nScoreda[0] = g_nScore / 10000000;
	nScoreda[1] = g_nScore % 10000000 / 1000000;
	nScoreda[2] = g_nScore % 1000000 / 100000;
	nScoreda[3] = g_nScore % 100000 / 10000;
	nScoreda[4] = g_nScore % 10000 / 1000;
	nScoreda[5] = g_nScore % 1000 / 100;
	nScoreda[6] = g_nScore % 100 / 10;
	nScoreda[7] = g_nScore % 10;

	for (nCntScoreda = 0; nCntScoreda < 8; nCntScoreda++)
	{
		pVtx[0].tex = D3DXVECTOR2(0.0f + nScoreda[nCntScoreda] * 0.1f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + nScoreda[nCntScoreda] * 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + nScoreda[nCntScoreda] * 0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + nScoreda[nCntScoreda] * 0.1f, 1.0f);

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffScore->Unlock();
}

//=============================================================================
// �G�̎擾
//=============================================================================
int GetScore(void)
{
	return g_nScore;
}