//=============================================================================
//
// �e���� [item.cpp]
// Author : ozaki
//
//=============================================================================
#include "item.h"
#include "Game.h"
#include "Score.h"
#include "Time.h"
#include "player.h"
#include "sound.h"
#include "player.h"
#include "Explosion.h"
#include "block.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_ITEM			(100)		// �A�C�e���̍ő吔
#define MAX_WIDTH			(30)
#define MAX_HEIGHT			(50)
#define MAX_ADD				(10)
#define ITEM_TYPE			(3)			// �A�C�e���̎��
#define ITEM_Number			(200)
#define MAX_BLOCK			(100)
//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureItem[ITEM_TYPE] = {};	    // �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItem = NULL;				// ���_�o�b�t�@�ւ̃|�C���^
Item g_aItem[MAX_ITEM];										// �A�C�e���̏��
int pItem;
int nItem = 0;
//Player g_Player;
int g_nNumCoin;

//=============================================================================
// �A�C�e���̏���������
//=============================================================================
void InitItem(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D*pVtx;												//���_���ւ̃|�C���^
	int nCntitem;
	//�f���@�C�X���擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,							// �R�C��
		"data\\TEXTURE\\coin000.png",
		&g_pTextureItem[0]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\1.png",									//�@�L�m�R
		&g_pTextureItem[1]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\2.png",									//�@�r�b�O�L�m�R
		&g_pTextureItem[2]);


	// �A�C�e���̏��̏�����
	for (nCntitem = 0; nCntitem < MAX_ITEM; nCntitem++)
	{
		g_aItem[nCntitem].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		/*g_aItem[nCntitem].col = D3DXVECTOR3(1.0f, 1.0f, 1.0f, 1.0f);*/
		g_aItem[nCntitem].bUse = false;
		g_nNumCoin = 0;
	}

	// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ITEM,
		D3DUSAGE_WRITEONLY,
		FVF_VRETEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffItem,
		NULL);

	////���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^�̎擾
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntitem = 0; nCntitem < MAX_ITEM; nCntitem++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aItem[nCntitem].pos.x - MAX_WIDTH, g_aItem[nCntitem].pos.y - MAX_HEIGHT, g_aItem[nCntitem].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_aItem[nCntitem].pos.x + MAX_WIDTH, g_aItem[nCntitem].pos.y - MAX_HEIGHT, g_aItem[nCntitem].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_aItem[nCntitem].pos.x - MAX_WIDTH, g_aItem[nCntitem].pos.y + MAX_HEIGHT, g_aItem[nCntitem].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_aItem[nCntitem].pos.x + MAX_WIDTH, g_aItem[nCntitem].pos.y + MAX_HEIGHT, g_aItem[nCntitem].pos.z);

		//�e�N�X�`���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.25f, 1.0f);

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
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffItem->Unlock();

	nItem = 0;
}

//=============================================================================
// �A�C�e���̏I������
//=============================================================================
void UninitItem(void)
{
	for (int nCnt = 0; nCnt != ITEM_TYPE; nCnt++)
	{
		// �e�N�X�`���̊J��
		if (g_pTextureItem[nCnt] != NULL)
		{
			g_pTextureItem[nCnt]->Release();
			g_pTextureItem[nCnt] = NULL;
		}
		// ���_�o�b�t�@�̊J��
		if (g_pVtxBuffItem != NULL)
		{
			g_pVtxBuffItem->Release();
			g_pVtxBuffItem = NULL;
		}
	}
}

//=============================================================================
// �A�C�e���̍X�V����
//=============================================================================
void UpdateItem(void)
{
	int nCntitem;
	VERTEX_2D*pVtx;
	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^�̎擾
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntitem = 0; nCntitem < MAX_ITEM; nCntitem++)
	{
		if (g_aItem[nCntitem].bUse == true)
		{
			if (g_aItem[nCntitem].type == ITEMSTATE_COIN)
			{
				g_aItem[nCntitem].nCounterAnim++;
				if ((g_aItem[nCntitem].nCounterAnim % 10) == 0)
				{
					g_aItem[nCntitem].nPatternAnim = (g_aItem[nCntitem].nPatternAnim + 1 % 8);

					//���_���W�̐ݒ�
					pVtx[0].pos = D3DXVECTOR3(g_aItem[nCntitem].pos.x - g_aItem[nCntitem].fwidth, g_aItem[nCntitem].pos.y - g_aItem[nCntitem].fheigth, g_aItem[nCntitem].pos.z);
					pVtx[1].pos = D3DXVECTOR3(g_aItem[nCntitem].pos.x + g_aItem[nCntitem].fwidth, g_aItem[nCntitem].pos.y - g_aItem[nCntitem].fheigth, g_aItem[nCntitem].pos.z);
					pVtx[2].pos = D3DXVECTOR3(g_aItem[nCntitem].pos.x - g_aItem[nCntitem].fwidth, g_aItem[nCntitem].pos.y + g_aItem[nCntitem].fheigth, g_aItem[nCntitem].pos.z);
					pVtx[3].pos = D3DXVECTOR3(g_aItem[nCntitem].pos.x + g_aItem[nCntitem].fwidth, g_aItem[nCntitem].pos.y + g_aItem[nCntitem].fheigth, g_aItem[nCntitem].pos.z);

					//�e�N�X�`���̐ݒ�
					pVtx[0].tex.x = (0.0f + (0.25f * (g_aItem[nCntitem].nPatternAnim % 8)));
					pVtx[0].tex.y = (0.0f + 1.0f);

					pVtx[1].tex.x = (0.25f + (0.25f * (g_aItem[nCntitem].nPatternAnim % 8)));
					pVtx[1].tex.y = (0.0f + 1.0f);

					pVtx[2].tex.x = (0.0f + (0.25f * (g_aItem[nCntitem].nPatternAnim % 8)));
					pVtx[2].tex.y = (1.0f + 1.0f);

					pVtx[3].tex.x = (0.25f + (0.25f * (g_aItem[nCntitem].nPatternAnim % 8)));
					pVtx[3].tex.y = (1.0f + 1.0f);

					//if (g_aItem[nCntitem].nPatternAnim >= 8)
					//{
					//	g_aItem[nCntitem].bUse = false;
					//}
				}
			}
		}
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffItem->Unlock();

}

//=============================================================================
// �A�C�e���̕`�揈��
//=============================================================================
void DrawItem(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntItem;

	//�f���@�C�X���擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffItem, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VRETEX_2D);

	// �|���S���̕`��
	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse == true)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureItem[g_aItem[nCntItem].type]);

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				0 + (4 * nCntItem),
				2);
		}
	}
}

//=============================================================================
// �A�C�e���̐ݒ菈��
//=============================================================================
void SetItem(D3DXVECTOR3 pos, float fwidth, float fheigth, ITEMTYPE type)
{
	int nCntItem;
	VERTEX_2D*pVtx;									//���_���ւ̃|�C���^

	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse == false)		//�A�C�e�����g�p����Ă���
		{
			g_aItem[nCntItem].pos = pos;
			g_aItem[nCntItem].fwidth = fwidth;
			g_aItem[nCntItem].fheigth = fheigth;
			g_aItem[nCntItem].type = type;

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - g_aItem[nCntItem].fwidth, g_aItem[nCntItem].pos.y - g_aItem[nCntItem].fheigth, g_aItem[nCntItem].pos.z);
			pVtx[1].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + g_aItem[nCntItem].fwidth, g_aItem[nCntItem].pos.y - g_aItem[nCntItem].fheigth, g_aItem[nCntItem].pos.z);
			pVtx[2].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - g_aItem[nCntItem].fwidth, g_aItem[nCntItem].pos.y + g_aItem[nCntItem].fheigth, g_aItem[nCntItem].pos.z);
			pVtx[3].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + g_aItem[nCntItem].fwidth, g_aItem[nCntItem].pos.y + g_aItem[nCntItem].fheigth, g_aItem[nCntItem].pos.z);

			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			switch (g_aItem[nCntItem].type)
			{
				// �R�C��
			case ITEMSTATE_COIN:
				g_aItem[nCntItem].nType = 0;
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				//�e�N�X�`���̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.25f, 1.0f);
				g_nNumCoin++;
				break;

				// �L�m�R
			case ITEMSTATE_MUSHROOMS:
				g_aItem[nCntItem].nType = 1;
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				//�e�N�X�`���̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
				break;

				// �r�b�O�L�m�R
			case ITEMSTATE_BIGMUSHROOMS:
				g_aItem[nCntItem].nType = 1;
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

				//�e�N�X�`���̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
				break;
			}

			g_aItem[nCntItem].nCounterAnim = 0;
			g_aItem[nCntItem].nPatternAnim = 0;
			g_aItem[nCntItem].bUse = true;
			nItem++;
			break;
		}
		pVtx += 4;
	}
	g_pVtxBuffItem->Unlock();
}

//=============================================================================
//�A�C�e���̎擾
//=============================================================================
Item *GetItem(void)
{
	return &g_aItem[0];
}

//=============================================================================
//�A�C�e�������蔻��
//=============================================================================
void CollisionItem(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pMove, float fwidth, float fheigth)
{
	bool bLand = false;					//���n�������ǂ���
	int nCntItem;
	Item *pItem;
	pItem = GetItem();

	Block *pBlock;
	pBlock = GetBlock();

	Player *pPlayer;
	pPlayer = GetPlayer();
	pPlayer->posold = pPlayer->pos;
	//���[�J���ϐ�
	VERTEX_2D*pVtx;														//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^�̎擾
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++, pItem++)
	{
		//�A�C�e���Əd�Ȃ�����
		if (pItem->bUse == true)					//�A�C�e�����g�p����Ă���
		{
			if (pItem->pos.x - MAX_WIDTH - MAX_ADD < pPos->x&& pItem->pos.x + MAX_WIDTH + MAX_ADD > pPos->x
				&& pItem->pos.y - MAX_HEIGHT + MAX_ADD < pPos->y && pItem->pos.y + MAX_HEIGHT + MAX_ADD > pPos->y)

			{
				if (pItem->type == ITEMSTATE_COIN)
				{
					SetExplosion(D3DXVECTOR3(g_aItem[nCntItem].pos.x, g_aItem[nCntItem].pos.y, g_aItem[nCntItem].pos.z), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),30);
					PlaySound(SOUND_LABRL_SE_COIN);
					g_nNumCoin--;
					//�A�C�e��������
					pItem->bUse = false;
				}
				else if (pItem->type == ITEMSTATE_MUSHROOMS)
				{
					PlaySound(SOUND_LABRL_SE_nomu);

					pPlayer->fheigth += 80;
					pPlayer->fwidth += 20;
					//�A�C�e��������
					pItem->bUse = false;

					pPlayer->state = PLAYER_BIGSTATE;


				}
				else if (pItem->type == ITEMSTATE_BIGMUSHROOMS)
				{
					PlaySound(SOUND_LABRL_SE_nomu);

					pPlayer->fheigth += 220;
					pPlayer->fwidth += 100;
					//�A�C�e��������
					pItem->bUse = false;

					for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++, pBlock++)
					{

						pBlock->bUse = false;
					}
				}

				//�X�R�A���Z
				AddScore(10000);

				if (g_nNumCoin == 0)
				{
					bool *pTimer;
					pTimer = GetTime();

					GAMESTATE GameState;
					GameState = GetGameState();


					if (GameState != GAMESTATE_END)
					{
						StopTimer();
						SetGameState(GAMESTATE_END);

					}
				}
			}
		}
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffItem->Unlock();
}