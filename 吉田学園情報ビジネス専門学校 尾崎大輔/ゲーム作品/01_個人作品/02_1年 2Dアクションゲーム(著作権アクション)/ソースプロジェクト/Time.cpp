//=============================================================================
//
// �X�R�A���� [Time.cpp]
// Author : Ozaki
//
//=============================================================================
#include "Time.h"
#include "main.h"
#include "Game.h"
#include "Gameover.h"
#include "sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_TIME		"data/TEXTURE/number000.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define MAX_MIKY			(20)							// ���Ԃ̑傫��

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexTime(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureTime = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTime = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
int						g_nTime;					// �X�R�A
int                     g_nTimeCnt;
D3DXVECTOR3				g_posTime;
bool  bTimer;
//=============================================================================
// ����������
//=============================================================================
void InitTime(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �X�R�A�̏�����
	g_nTime = 20;
	g_posTime = D3DXVECTOR3(600, 70, 0.0f);
	bTimer = true;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		TEXTURE_TIME,								// �t�@�C���̖��O
		&g_pTextureTime);							// �e�N�X�`���ւ̃|�C���^

													// ���_���̍쐬
	MakeVertexTime(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitTime(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureTime != NULL)
	{
		g_pTextureTime->Release();
		g_pTextureTime = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffTime != NULL)
	{
		g_pVtxBuffTime->Release();
		g_pVtxBuffTime = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateTime(void)
{
	VERTEX_2D*pVtx;

	int nTimeda[3];
	int nCntTimeda;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^�̎擾
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	if (bTimer == true)
	{
		g_nTimeCnt++;
		if (g_nTimeCnt >= 60)
		{
			g_nTimeCnt = 0;
			g_nTime -= 1;
			if (g_nTime >= 0)
			{
				nTimeda[0] = g_nTime % 1000 / 100;
				nTimeda[1] = g_nTime % 100 / 10;
				nTimeda[2] = g_nTime % 10;

				for (nCntTimeda = 0; nCntTimeda < 3; nCntTimeda++)
				{
					pVtx[0].tex = D3DXVECTOR2(0.0f + nTimeda[nCntTimeda] * 0.1f, 0.0f);
					pVtx[1].tex = D3DXVECTOR2(0.1f + nTimeda[nCntTimeda] * 0.1f, 0.0f);
					pVtx[2].tex = D3DXVECTOR2(0.0f + nTimeda[nCntTimeda] * 0.1f, 1.0f);
					pVtx[3].tex = D3DXVECTOR2(0.1f + nTimeda[nCntTimeda] * 0.1f, 1.0f);

					pVtx += 4;
				}
			}
		}
		else if (g_nTime <= 0)
		{
			GAMESTATE state;
			state = GetGameState();
			if (state == GAMESTATE_NORMAL)
			{
				StopSound(SOUND_LABEL_BGM006);
				PlaySound(SOUND_LABEL_SE_MARIO_DETH);
				SetGameState(GAMESTATE_GAMEOVER);
			}
		}
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffTime->Unlock();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawTime(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTime, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VRETEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureTime);

	// �|���S���̕`��
	for (int nCntTime = 0; nCntTime < 3; nCntTime++)
	{
		//�|���S���̔j��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			4 * nCntTime,
			2);
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexTime(LPDIRECT3DDEVICE9 pDevice)
{
	int nTimeda[3];
	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 3,
		D3DUSAGE_WRITEONLY,
		FVF_VRETEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTime,
		NULL);

	VERTEX_2D*pVtx;


	//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^�̎擾
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	nTimeda[0] = g_nTime % 1000 / 100;
	nTimeda[1] = g_nTime % 100 / 10;
	nTimeda[2] = g_nTime % 10;

	// ���_����ݒ�
	for (int nCnt = 0; nCnt < 3; nCnt++)
	{

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_posTime.x - MAX_MIKY, g_posTime.y - MAX_MIKY, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posTime.x + MAX_MIKY, g_posTime.y - MAX_MIKY, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posTime.x - MAX_MIKY, g_posTime.y + MAX_MIKY, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posTime.x + MAX_MIKY, g_posTime.y + MAX_MIKY, 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 0,  0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);

		//�e�N�X�`���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f + nTimeda[nCnt] * 0.1f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + nTimeda[nCnt] * 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + nTimeda[nCnt] * 0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + nTimeda[nCnt] * 0.1f, 1.0f);

		pVtx += 4;

		g_posTime.x += 50;
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffTime->Unlock();

}

//=============================================================================
// ���Ԃ̉��Z
//=============================================================================
void AddTime(int nValue)
{
	VERTEX_2D*pVtx;

	int nTimeda[8];
	int nCntTimeda;

	g_nTime += nValue;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^�̎擾
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	nTimeda[0] = g_nTime / 10000000;
	nTimeda[1] = g_nTime % 10000000 / 1000000;
	nTimeda[2] = g_nTime % 1000000 / 100000;
	nTimeda[3] = g_nTime % 100000 / 10000;
	nTimeda[4] = g_nTime % 10000 / 1000;
	nTimeda[5] = g_nTime % 1000 / 100;
	nTimeda[6] = g_nTime % 100 / 10;
	nTimeda[7] = g_nTime % 10;

	for (nCntTimeda = 0; nCntTimeda < 8; nCntTimeda++)
	{
		pVtx[0].tex = D3DXVECTOR2(0.0f + nTimeda[nCntTimeda] * 0.1f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + nTimeda[nCntTimeda] * 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + nTimeda[nCntTimeda] * 0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + nTimeda[nCntTimeda] * 0.1f, 1.0f);

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffTime->Unlock();
}

//=============================================================================
// ���Ԃ̎擾
//=============================================================================
bool *GetTime(void)
{
	return &bTimer;
}

void StopTimer(void)
{
	bTimer = false;
}