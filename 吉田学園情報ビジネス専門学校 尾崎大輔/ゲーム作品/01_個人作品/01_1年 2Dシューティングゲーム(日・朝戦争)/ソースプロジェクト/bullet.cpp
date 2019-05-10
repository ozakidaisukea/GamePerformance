//=============================================================================
//
// �e���� [bullet.cpp]
// Author : ozaki
//
//=============================================================================
#include "bullet.h"
#include "Explosion.h"
#include "enemy.h"
#include "Player.h"
#include "effect.h"
#include "sound.h"
#include "boss.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_BULLET		(256)		// �e�̍ő吔
#define MAX_MIKY		(50)		// �e�̑傫��

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;				//�ʒu
	D3DXVECTOR3 move;				//�ړ���
	BULLETTYPE type;				//�e�̎��
	int bullettex;					//�e�N�X�`���̎��
	int nLife;						//����
	bool bUse;						//�g�p���Ă��邩
}Bullet;

//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureBullet[2] = { NULL };	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
Bullet g_aBullet[MAX_BULLET];							// �e�̏��

//=============================================================================
// ����������
//=============================================================================
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D*pVtx;														//���_���ւ̃|�C���^
	int nCntBullet;

	//�f���@�C�X���擾
	pDevice = GetDevice();

	// �e�̏��̏�����
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].nLife = 30;
		g_aBullet[nCntBullet].bUse = false;
	}
	// �e�N�X�`���̓ǂݍ���[1�G]
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\12.png",
		&g_pTextureBullet[0]);

	// �e�N�X�`���̓ǂݍ���[2�v���C���[]
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\abe1.png",
		&g_pTextureBullet[1]);

	// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VRETEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL);

	////���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^�̎擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - MAX_MIKY, g_aBullet[nCntBullet].pos.y - MAX_MIKY, g_aBullet[nCntBullet].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + MAX_MIKY, g_aBullet[nCntBullet].pos.y - MAX_MIKY, g_aBullet[nCntBullet].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - MAX_MIKY, g_aBullet[nCntBullet].pos.y + MAX_MIKY, g_aBullet[nCntBullet].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + MAX_MIKY, g_aBullet[nCntBullet].pos.y + MAX_MIKY, g_aBullet[nCntBullet].pos.z);

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
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);


		pVtx += 4;					//���_�f�[�^�̃|�C���^��4���i�߂�
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffBullet->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void UninitBullet(void)
{
	for (int nCnt = 0;nCnt < 2;nCnt++)
	{
		// �e�N�X�`���̊J��
		if (g_pTextureBullet[nCnt] != NULL)
		{
			g_pTextureBullet[nCnt]->Release();
			g_pTextureBullet[nCnt] = NULL;
		}
	}
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBullet(void)
{
	int nCntBullet;

	VERTEX_2D*pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^�̎擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{
			g_aBullet[nCntBullet].pos.y -= g_aBullet[nCntBullet].move.y;
			g_aBullet[nCntBullet].pos.x -= g_aBullet[nCntBullet].move.x;

			g_aBullet[nCntBullet].nLife--;

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - MAX_MIKY, g_aBullet[nCntBullet].pos.y - MAX_MIKY, g_aBullet[nCntBullet].pos.z);
			pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + MAX_MIKY, g_aBullet[nCntBullet].pos.y - MAX_MIKY, g_aBullet[nCntBullet].pos.z);
			pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - MAX_MIKY, g_aBullet[nCntBullet].pos.y + MAX_MIKY, g_aBullet[nCntBullet].pos.z);
			pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + MAX_MIKY, g_aBullet[nCntBullet].pos.y + MAX_MIKY, g_aBullet[nCntBullet].pos.z);

			//�e�N�X�`���̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			//��莞�Ԍo��
			g_aBullet[nCntBullet].nLife;
			if (g_aBullet[nCntBullet].nLife <= 0)
			{
				SetExplosion(g_aBullet[nCntBullet].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				g_aBullet[nCntBullet].bUse = false;
			}
			if (g_aBullet[nCntBullet].pos.y < 0)
			{
				g_aBullet[nCntBullet].bUse = false;
			}

			if (g_aBullet[nCntBullet].type == BULLETTYPE_ENEMY)
			{
				Player *pPlayer;

				//�v���C���[�̎擾
				pPlayer = GetPlayer();

				if (pPlayer->bDisp == true)
				{
					if (pPlayer->pos.x - 50 < g_aBullet[nCntBullet].pos.x && pPlayer->pos.x + 50 > g_aBullet[nCntBullet].pos.x
						&& pPlayer->pos.y - 50 < g_aBullet[nCntBullet].pos.y && pPlayer->pos.y + 50 > g_aBullet[nCntBullet].pos.y)
					{
						HitPlayer(1);
						g_aBullet[nCntBullet].bUse = false;		//�g�p���ĂȂ���ԂɂȂ�
						PlaySound(SOUND_LABEL_SE_HUMAN1);
					}
				}
			}
			else if (g_aBullet[nCntBullet].type == BULLETTYPE_PLAYER)
			{
				int nCntEnemy;
				Enemy *pEnemy;
				Boss  *pBoss;

				//�G�̎擾
				pEnemy = GetEnemy();

				pBoss = GetBoss();

				for (nCntEnemy = 0; nCntEnemy < MAX_BULLET; nCntEnemy++, pEnemy++)
				{
					if (pEnemy->bUse == true)					//�G���g�p����Ă���
					{
						if (pEnemy->pos.x - 50 < g_aBullet[nCntBullet].pos.x && pEnemy->pos.x + 50 > g_aBullet[nCntBullet].pos.x
							&& pEnemy->pos.y - 50 < g_aBullet[nCntBullet].pos.y && pEnemy->pos.y + 50 > g_aBullet[nCntBullet].pos.y)
						{
							HitEnemy(nCntEnemy, 1);
							g_aBullet[nCntBullet].bUse = false;		//�g�p���ĂȂ���ԂɂȂ�

						}
					}
				}
				if (pBoss->bUse == true)				//�G���g�p����Ă���
				{
					if (pBoss->pos.x - 200 < g_aBullet[nCntBullet].pos.x && pBoss->pos.x + 200 > g_aBullet[nCntBullet].pos.x
						&& pBoss->pos.y - 200 < g_aBullet[nCntBullet].pos.y && pBoss->pos.y + 200 > g_aBullet[nCntBullet].pos.y)
					{
						HitBoss(0, 1);
						g_aBullet[nCntBullet].bUse = false;		//�g�p���ĂȂ���ԂɂȂ�
					}
				}

				SetEffect(g_aBullet[nCntBullet].pos, D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), 50.0f, 50);
			}
		}
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffBullet->Unlock();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBullet;

	//�f���@�C�X���擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VRETEX_2D);


		// �|���S���̕`��
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{
			if (g_aBullet[nCntBullet].type == BULLETTYPE_PLAYER)
			{
				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTextureBullet[1]);

				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
					0 + (4 * nCntBullet),
					2);
			}
			else if (g_aBullet[nCntBullet].type == BULLETTYPE_ENEMY)
			{
				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTextureBullet[0]);

				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
					0 + (4 * nCntBullet),
					2);
			}
		}
	}
}

//=============================================================================
// �e�̐ݒ菈��
//=============================================================================
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move,BULLETTYPE type)
{
	int nCntBullet;
	VERTEX_2D*pVtx;														//���_���ւ̃|�C���^

	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == false)		//�e���g�p����Ă���
		{
			g_aBullet[nCntBullet].pos = pos;
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - MAX_MIKY, g_aBullet[nCntBullet].pos.y - MAX_MIKY, g_aBullet[nCntBullet].pos.z);
			pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + MAX_MIKY, g_aBullet[nCntBullet].pos.y - MAX_MIKY, g_aBullet[nCntBullet].pos.z);
			pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - MAX_MIKY, g_aBullet[nCntBullet].pos.y + MAX_MIKY, g_aBullet[nCntBullet].pos.z);
			pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + MAX_MIKY, g_aBullet[nCntBullet].pos.y + MAX_MIKY, g_aBullet[nCntBullet].pos.z);
			g_aBullet[nCntBullet].move = move;
			g_aBullet[nCntBullet].nLife = 380;
			g_aBullet[nCntBullet].bUse = true;
			g_aBullet[nCntBullet].type = type;

			break;
		}
		pVtx += 4;
	}
	g_pVtxBuffBullet->Unlock();
}