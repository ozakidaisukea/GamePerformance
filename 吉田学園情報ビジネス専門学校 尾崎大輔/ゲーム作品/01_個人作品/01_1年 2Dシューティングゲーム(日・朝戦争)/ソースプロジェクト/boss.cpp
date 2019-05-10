//=============================================================================
//
// �G���� [boss.cpp]
// Author : Ozaki
//
//=============================================================================
#include "enemy.h"
#include "Explosion.h"
#include <time.h>
#include "bullet.h"
#include "Player.h"
#include "Game.h"
#include "score.h"
#include "sound.h"
#include "boss.h"
#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_TYPE_BOSS		(1)						// �G�̎��
#define MAX_MIKY			(200)
//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_apTextureBoss[MAX_TYPE_BOSS] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBoss = NULL;					// ���_�o�b�t�@�ւ̃|�C���^
Boss g_aBoss[MAX_BOSS];										// �G�̏��
int g_nNumBoss;													// �G�̑���

//=============================================================================
// ����������
//=============================================================================
void InitBoss(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �G�̏��̏�����
	for (int nCntBoss = 0; nCntBoss < MAX_BOSS; nCntBoss++)
	{
		g_aBoss[nCntBoss].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBoss[nCntBoss].nType = 0;
		g_aBoss[nCntBoss].bUse = false;
		g_aBoss[nCntBoss].nCounterState = 0;
		g_aBoss[nCntBoss].nLife = 26;
		g_aBoss[nCntBoss].nCounterAnim = 0;				//�A�j���[�V�����J�E���^�[
		g_aBoss[nCntBoss].nPatternAnim = 0;				//�A�j���[�V�����p�^�[��
		g_aBoss[nCntBoss].state = BOSSSTATE_NORMAL;
	}

	// �e�N�X�`���̓ǂݍ���(1�̕�)
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\iru.png",
		&g_apTextureBoss[0]);

	// ���_���̍쐬
	VERTEX_2D *pVtx;
	int nCntBoss;

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BOSS,
		D3DUSAGE_WRITEONLY,
		FVF_VRETEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBoss,
		NULL);

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBoss->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBoss = 0; nCntBoss < MAX_BOSS; nCntBoss++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x - MAX_MIKY, g_aBoss[nCntBoss].pos.y - MAX_MIKY, g_aBoss[nCntBoss].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + MAX_MIKY, g_aBoss[nCntBoss].pos.y - MAX_MIKY, g_aBoss[nCntBoss].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x - MAX_MIKY, g_aBoss[nCntBoss].pos.y + MAX_MIKY, g_aBoss[nCntBoss].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + MAX_MIKY, g_aBoss[nCntBoss].pos.y + MAX_MIKY, g_aBoss[nCntBoss].pos.z);

		//�e�N�X�`���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);


		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);





		pVtx += 4;					//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBoss->Unlock();
	g_nNumBoss = 0;					//�G�̑������N���A
}

//=============================================================================
// �I������
//=============================================================================
void UninitBoss(void)
{
	int nCntTex;

	// �e�N�X�`���̊J��
	for (nCntTex = 0; nCntTex < MAX_TYPE_BOSS; nCntTex++)
	{
		if (g_apTextureBoss[nCntTex] != NULL)
		{
			g_apTextureBoss[nCntTex]->Release();
			g_apTextureBoss[nCntTex] = NULL;
		}
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffBoss != NULL)
	{
		g_pVtxBuffBoss->Release();
		g_pVtxBuffBoss = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBoss(void)
{
	int nCntBoss;

	for (nCntBoss = 0; nCntBoss < MAX_BOSS; nCntBoss++)
	{
		if (g_aBoss[nCntBoss].bUse == true)		//�G���g�p����Ă���
		{

			g_aBoss[nCntBoss].nCounterAnim++;
			if ((g_aBoss[nCntBoss].nCounterAnim % 5) == 0)
			{
				g_aBoss[nCntBoss].nPatternAnim = (g_aBoss[nCntBoss].nPatternAnim + 1 % 8);
				//g_aExplosion[nCntExplosion].pos.y -= 10.0f;

				// ���_���̍쐬
				VERTEX_2D *pVtx;

				g_pVtxBuffBoss->Lock(0, 0, (void**)&pVtx, 0);
				pVtx += nCntBoss * 4;

				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x - MAX_MIKY, g_aBoss[nCntBoss].pos.y - MAX_MIKY, g_aBoss[nCntBoss].pos.z);
				pVtx[1].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + MAX_MIKY, g_aBoss[nCntBoss].pos.y - MAX_MIKY, g_aBoss[nCntBoss].pos.z);
				pVtx[2].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x - MAX_MIKY, g_aBoss[nCntBoss].pos.y + MAX_MIKY, g_aBoss[nCntBoss].pos.z);
				pVtx[3].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + MAX_MIKY, g_aBoss[nCntBoss].pos.y + MAX_MIKY, g_aBoss[nCntBoss].pos.z);

				//�e�N�X�`���̐ݒ�
				pVtx[0].tex.x = (0.0f + (0.5f * (g_aBoss[nCntBoss].nPatternAnim % 8)));
				pVtx[0].tex.y = (0.0f + 1.0f);

				pVtx[1].tex.x = (0.5f + (0.5f * (g_aBoss[nCntBoss].nPatternAnim % 8)));
				pVtx[1].tex.y = (0.0f + 1.0f);

				pVtx[2].tex.x = (0.0f + (0.5f * (g_aBoss[nCntBoss].nPatternAnim % 8)));
				pVtx[2].tex.y = (1.0f + 1.0f);

				pVtx[3].tex.x = (0.5f + (0.5f * (g_aBoss[nCntBoss].nPatternAnim % 8)));
				pVtx[3].tex.y = (1.0f + 1.0f);

				if (g_aBoss[nCntBoss].nPatternAnim >= 8)
				{
					g_aBoss[nCntBoss].nPatternAnim = false;
				}
				g_pVtxBuffBoss->Unlock();
			}

			switch (g_aBoss[nCntBoss].state)
			{
			case BOSSSTATE_NORMAL:
				if (rand() % 5 == 0)
				{
					float Kakudo;
					float Idoux;
					float Idouy;
					Player *pPlayer;

					//�v���C���[�̎擾
					pPlayer = GetPlayer();
					//�v���C���[�Ƃ̋���
					Idoux = g_aBoss[nCntBoss].pos.x - pPlayer->pos.x;
					Idouy = g_aBoss[nCntBoss].pos.y - pPlayer->pos.y;

					Kakudo = atan2f(Idoux, Idouy);

					D3DXVECTOR3 movepos(0.0f, 0.0f, 0.0f);

					movepos.x = sinf(Kakudo) * 10.0f;
					movepos.y = cosf(Kakudo) * 10.0f;


					D3DXVECTOR3 Setpos(g_aBoss[nCntBoss].pos.x, g_aBoss[nCntBoss].pos.y + 60, 0.0f);
					SetBullet(Setpos, movepos, BULLETTYPE_ENEMY);
				}
				break;

			case BOSSSTATE_DAMAGE:
				g_aBoss[nCntBoss].nCounterState--;
				if (g_aBoss[nCntBoss].nCounterState <= 0)
				{
					g_aBoss[nCntBoss].state = BOSSSTATE_NORMAL;

					// ���_���̍쐬
					VERTEX_2D *pVtx;

					g_pVtxBuffBoss->Lock(0, 0, (void**)&pVtx, 0);
					pVtx += nCntBoss * 4;

					//���_�J���[�̐ݒ�
					pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

					g_pVtxBuffBoss->Unlock();
				}
				break;
			}
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBoss(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffBoss, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VRETEX_2D);

	// �|���S���̕`��
	for (int nCntBoss = 0; nCntBoss < MAX_ENEMY; nCntBoss++)
	{
		if (g_aBoss[nCntBoss].bUse == true)
		{
			//�e�N�X�`���̔j��
			pDevice->SetTexture(0, g_apTextureBoss[g_aBoss[nCntBoss].nType]);

			//�|���S���̔j��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				0 + (4 * nCntBoss),
				2);
		}
	}
}

//=============================================================================
// �G�̐ݒ�
//=============================================================================
void SetBoss(D3DXVECTOR3 pos, int nType)
{
	int nCntBoss;


	// ���_���̍쐬
	VERTEX_2D *pVtx;

	g_pVtxBuffBoss->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBoss = 0; nCntBoss < MAX_BOSS; nCntBoss++)
	{
		if (g_aBoss[nCntBoss].bUse == false)		//�e���g�p����Ă���
		{
			g_aBoss[nCntBoss].pos = pos;
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x - MAX_MIKY, g_aBoss[nCntBoss].pos.y - MAX_MIKY, g_aBoss[nCntBoss].pos.z);
			pVtx[1].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + MAX_MIKY, g_aBoss[nCntBoss].pos.y - MAX_MIKY, g_aBoss[nCntBoss].pos.z);
			pVtx[2].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x - MAX_MIKY, g_aBoss[nCntBoss].pos.y + MAX_MIKY, g_aBoss[nCntBoss].pos.z);
			pVtx[3].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + MAX_MIKY, g_aBoss[nCntBoss].pos.y + MAX_MIKY, g_aBoss[nCntBoss].pos.z);

			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			g_aBoss[nCntBoss].nCounterState = 0;
			g_aBoss[nCntBoss].nLife = 26;
			g_aBoss[nCntBoss].state = BOSSSTATE_NORMAL;

			g_aBoss[nCntBoss].nType = nType;
			g_aBoss[nCntBoss].bUse = true;
			g_nNumBoss++;		//�G�̑��������Z����

			break;
		}
		pVtx += 4;
	}
	g_pVtxBuffBoss->Unlock();
}

//=============================================================================
// �G�̎擾
//=============================================================================
Boss*GetBoss(void)
{
	return &g_aBoss[0];
}
//=============================================================================
//�G�̃_���[�W����
//=============================================================================
void HitBoss(int nCntBoss, int nDamage)
{
	g_aBoss[nCntBoss].nLife -= nDamage;
	if (g_aBoss[nCntBoss].nLife <= 0)
	{
		SetExplosion(g_aBoss[nCntBoss].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.1f));
		PlaySound(SOUND_LABEL_SE_EXPLOSION);
		g_aBoss[nCntBoss].bUse = false;
		AddScore(10000);
		g_nNumBoss--;				//�G�̑��������炷
		if (g_nNumBoss <= 0)
		{
			SetGameState(GAMESTATE_END);
		}
	}
	else
	{
		g_aBoss[nCntBoss].state = BOSSSTATE_DAMAGE;
		g_aBoss[nCntBoss].nCounterState = 5;

		// ���_���̍쐬
		VERTEX_2D *pVtx;

		g_pVtxBuffBoss->Lock(0, 0, (void**)&pVtx, 0);
		pVtx += nCntBoss * 4;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

		g_pVtxBuffBoss->Unlock();
	}
}