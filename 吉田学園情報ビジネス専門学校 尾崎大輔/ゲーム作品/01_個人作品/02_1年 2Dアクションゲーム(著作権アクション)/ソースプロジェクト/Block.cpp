//=============================================================================
//
// �e���� [block.cpp]
// Author : ozaki
//
//=============================================================================
#include "block.h"
#include "main.h"
#include "Player.h"
#include "Input.h"
#include "sound.h"
#include "item.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_BLOCK		(50)		// �u���b�N�̍ő吔
#define MAX_MIKY		(50)		// �u���b�N�̑傫��
#define X_Y				(9)			// �����萔
#define BLOCK_TYPEs		(9)			// �u���b�N�̎��

//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureBlock[BLOCK_TYPEs] = {};		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBlock = NULL;			// ���_�o�b�t�@�ւ̃|�C���^
Block g_aBlock[MAX_BLOCK];								// �u���b�N�̏��

//=============================================================================
// ����������
//=============================================================================
void InitBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D*pVtx;										//���_���ւ̃|�C���^
	int nCntBlock = 0;

	//�f���@�C�X���擾
	pDevice = GetDevice();

	// �e�̏��̏�����
	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		g_aBlock[nCntBlock].pos = D3DXVECTOR3(700.0f, 450.0f, 0.0f);
		g_aBlock[nCntBlock].fwidth = 10.0f;
		g_aBlock[nCntBlock].fheight = 10.0f;
		g_aBlock[nCntBlock].move = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		g_aBlock[nCntBlock].bUse = false;
		g_aBlock[nCntBlock].nCntItem = 0;
	}
	// �u���b�N�̓ǂݍ���

	// �m�[�}�� [1]
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\bulock.png",
		&g_pTextureBlock[0]);

	// �y�� [2]
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\dokan.png",
		&g_pTextureBlock[1]);

	// �x���g�R���x�A�[ [3]
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\block005.jpg",
		&g_pTextureBlock[2]);

	// �X�� [4]
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\iceblock.png",
		&g_pTextureBlock[3]);

	// �H�u���b�N1 [5]
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\block200.jpg",
		&g_pTextureBlock[4]);

	// �H�u���b�N2 [6]
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\block200.jpg",
		&g_pTextureBlock[5]);

	// �ړ��� [7]
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\move.png",
		&g_pTextureBlock[6]);

	// �W�����v�� [8]
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Jun.png",
		&g_pTextureBlock[7]);

	// �΃u���b�N [9]
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\isi.png",
		&g_pTextureBlock[8]);

	// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BLOCK,
		D3DUSAGE_WRITEONLY,
		FVF_VRETEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBlock,
		NULL);

	////���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^�̎擾
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y, g_aBlock[nCntBlock].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fwidth ,g_aBlock[nCntBlock].pos.y, g_aBlock[nCntBlock].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fheight, g_aBlock[nCntBlock].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fwidth, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fheight, g_aBlock[nCntBlock].pos.z);

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


		pVtx += 4;				//���_�f�[�^�̃|�C���^��4���i�߂�
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffBlock->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void UninitBlock(void)
{
	for (int nCnt = 0; nCnt < BLOCK_TYPEs; nCnt++)
	{
		// �e�N�X�`���̊J��
		if (g_pTextureBlock[nCnt] != NULL)
		{
			g_pTextureBlock[nCnt]->Release();
			g_pTextureBlock[nCnt] = NULL;
		}
	}
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffBlock != NULL)
	{
		g_pVtxBuffBlock->Release();
		g_pVtxBuffBlock = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBlock(void)
{
	int nCntBlock;
	D3DXVECTOR3 move;
	VERTEX_2D*pVtx;										//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^�̎擾
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		switch (g_aBlock[nCntBlock].nType)
		{
		case 0:		// �ʏ�u���b�N
			break;
		case 1:		// �y�ǃu���b�N
			break;
		case 2:		// �X��
			break;
		case 3:		// �x���g�R���x��
			break;
		case 4:		// �H�u���b�N
			break;
		case 5:		//�H�u���b�N
			break;
		case 6:		// �ړ���
			g_aBlock[nCntBlock].pos.x += g_aBlock[nCntBlock].move.x;
			if (g_aBlock[nCntBlock].pos.x >= 1000)
			{
				g_aBlock[nCntBlock].move *= -1;

			}
			else if (g_aBlock[nCntBlock].pos.x <= 900)
			{
				g_aBlock[nCntBlock].move *= -1;
			}
			break;
		case 7:		// �W�����v��
			break;
		case 8:		// �΃u���b�N
			break;
		}
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y, g_aBlock[nCntBlock].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fwidth, g_aBlock[nCntBlock].pos.y, g_aBlock[nCntBlock].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fheight, g_aBlock[nCntBlock].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fwidth, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fheight, g_aBlock[nCntBlock].pos.z);
		pVtx += 4;				//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffBlock->Unlock();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBlock;

	//�f���@�C�X���擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffBlock, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VRETEX_2D);

	// �|���S���̕`��
	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureBlock[g_aBlock[nCntBlock].type]);

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				0 + (4 * nCntBlock),
				2);
		}
	}
}
//=============================================================================
// �u���b�N�̐ݒ菈��
//=============================================================================
void SetBlock(D3DXVECTOR3 pos,float fwidth,float fheigth, BLOCK_TYPE type)
{
	int nCntBlock;
	VERTEX_2D*pVtx;													//���_���ւ̃|�C���^

	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == false)						//�u���b�N���g�p����Ă���
		{
			g_aBlock[nCntBlock].pos = pos;
			g_aBlock[nCntBlock].fwidth = fwidth;
			g_aBlock[nCntBlock].fheight = fheigth;
			g_aBlock[nCntBlock].type = type;
			switch (g_aBlock[nCntBlock].type)
			{
			// �m�[�}��
			case BlockType_Normal:
				g_aBlock[nCntBlock].nType = 0;
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				break;

			// �y��
			case BlockType_Dokan:
				g_aBlock[nCntBlock].nType = 1;
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				break;

				// �x���g�R���x�A�[
			case BlockType_Beltconveyor:
				g_aBlock[nCntBlock].nType = 2;
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				break;

			// �X��
			case BlockType_Ice:
				g_aBlock[nCntBlock].nType = 3;
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				break;

			// �H�u���b�N1
			case BlockType_Question1:
				g_aBlock[nCntBlock].nType = 4;
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				break;

				// �H�u���b�N2
			case BlockType_Question2:
				g_aBlock[nCntBlock].nType = 5;
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				break;

			// �ړ���
			case BlockType_Move:
				g_aBlock[nCntBlock].nType = 6;
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				break;

			// �W�����v��
			case BlockType_Junp:
				g_aBlock[nCntBlock].nType = 7;
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				break;

			// �΃u���b�N
			case BlockType_Isi:
				g_aBlock[nCntBlock].nType = 8;
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				break;
			}
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y, g_aBlock[nCntBlock].pos.z);
			pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fwidth, g_aBlock[nCntBlock].pos.y, g_aBlock[nCntBlock].pos.z);
			pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fheight, g_aBlock[nCntBlock].pos.z);
			pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fwidth, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fheight, g_aBlock[nCntBlock].pos.z);

			g_aBlock[nCntBlock].bUse = true;
			break;
		}
		pVtx += 4;
	}
		g_pVtxBuffBlock->Unlock();
}

//=============================================================================
// �u���b�N�̓����蔻�菈��
//=============================================================================
bool CollisionBlock(D3DXVECTOR3 *pPos, D3DXVECTOR3*pPosOld, D3DXVECTOR3 *pMove,float fwigth, float fheigth)								//�ړ�
{
	int nCntBlock;

	bool bLand = false;					//���n�������ǂ���

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{

		if (g_aBlock[nCntBlock].bUse == true)
		{
			if (pPos->x + fwigth - X_Y >= g_aBlock[nCntBlock].pos.x
				&& pPos->x - fwigth + X_Y <= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fwidth)
			{
				if (pPosOld->y <= g_aBlock[nCntBlock].pos.y && pPos->y >= g_aBlock[nCntBlock].pos.y)
				{//��̓����蔻��

					// �e�u���b�N���d�l
					if (g_aBlock[nCntBlock].type == BlockType_Normal)
					{// �m�[�}���u���b�N
						pPos->y = g_aBlock[nCntBlock].pos.y;
						bLand = true;

						pMove->y = 0.0f;
					}
					if (g_aBlock[nCntBlock].type == BlockType_Beltconveyor)
					{// �x���g�R���x�A�[
						pPos->y = g_aBlock[nCntBlock].pos.y;
						bLand = true;
						pPos->x += 3.0f;
						pMove->y = 0.0f;
					}
					if (g_aBlock[nCntBlock].type == BlockType_Dokan)
					{// �y��
						pPosOld->x >= g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fwidth &&
							pPos->x + fwigth <= g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fwidth;
						{//�E�̓����蔻��
							pPosOld->x - X_Y <= g_aBlock[nCntBlock].pos.x &&
								pPos->x - fwigth - X_Y >= g_aBlock[nCntBlock].pos.x;
							{//���̓����蔻��
								pPos->y = g_aBlock[nCntBlock].pos.y;
								bLand = true;
								pMove->y = 0.0f;

							}
						}
					}
					if (g_aBlock[nCntBlock].type == BlockType_Question1)
					{// �H�u���b�N1
						//PlaySound(SOUND_LABRL_SE_COIN);
						pPos->y = g_aBlock[nCntBlock].pos.y;
						bLand = true;

						pMove->y = 0.0f;
					}
					if (g_aBlock[nCntBlock].type == BlockType_Question2)
					{// �H�u���b�N2
					 //PlaySound(SOUND_LABRL_SE_COIN);
						pPos->y = g_aBlock[nCntBlock].pos.y;
						bLand = true;

						pMove->y = 0.0f;
					}
					if (g_aBlock[nCntBlock].type == BlockType_Ice)
					{// �X��
						pPos->y = g_aBlock[nCntBlock].pos.y;
						bLand = true;

						pMove->y = 0.01f;
					}
					if (g_aBlock[nCntBlock].type == BlockType_Move)
					{// �ړ���
						pPos->x = pPos->x + g_aBlock[nCntBlock].move.x;
						pPos->y = g_aBlock[nCntBlock].pos.y;
						bLand = true;

						pMove->y = 0.0f;
					}

					if (g_aBlock[nCntBlock].type == BlockType_Junp)
					{// �W�����v��
						pPos->y = g_aBlock[nCntBlock].pos.y;
						bLand = true;
						pMove->y = -40.0f;
					}

					if (g_aBlock[nCntBlock].type == BlockType_Isi)
					{// �΃u���b�N
						pPos->y = g_aBlock[nCntBlock].pos.y;
						bLand = true;

						pMove->y = 0.0f;
					}
				}
				else if (pPosOld->y - fheigth >= g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fheight
					&& pPos->y - fheigth <= g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fheight)
				{//���̓����蔻��
					pPos->y = g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fheight + fheigth;

					pMove->y = 0.0f;
					if (g_aBlock[nCntBlock].type == BlockType_Question1)
					{// �H�u���b�N1
						if (g_aBlock[nCntBlock].nCntItem < 1)
						{
							PlaySound(SOUND_LABRL_SE_COIN);
							SetItem(g_aBlock[nCntBlock].pos + D3DXVECTOR3(g_aBlock[nCntBlock].fwidth - 33, -40, 0.0f), 50, 50, ITEMSTATE_MUSHROOMS);
							g_aBlock[nCntBlock].nCntItem++;
						}

						pPos->y = g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fheight + fheigth;

						pMove->y = 0.0f;
					}
					if (g_aBlock[nCntBlock].type == BlockType_Question2)
					{// �H�u���b�N2
						if (g_aBlock[nCntBlock].nCntItem < 1)
						{
							PlaySound(SOUND_LABRL_SE_COIN);
							SetItem(g_aBlock[nCntBlock].pos + D3DXVECTOR3(g_aBlock[nCntBlock].fwidth -35, -60, 0.0f), 100, 100, ITEMSTATE_BIGMUSHROOMS);
							g_aBlock[nCntBlock].nCntItem++;
						}

						pPos->y = g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fheight + fheigth;

						pMove->y = 0.0f;
					}
				}

				if (//�����瑫
					pPosOld->y - fheigth >= g_aBlock[nCntBlock].pos.y
					&& pPosOld->y <= g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fheight
					//������
					|| pPosOld->y - fheigth > g_aBlock[nCntBlock].pos.y
					&& pPosOld->y - fheigth < g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fheight
					// ������
					|| pPosOld->y > g_aBlock[nCntBlock].pos.y
					&& pPosOld->y < g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fheight)
				{
					if (pPosOld->x + 7 >= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fwidth &&
						pPos->x - fwigth + 7 <= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fwidth)
					{//�E�̓����蔻��
						pPos->x = g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fwidth + fwigth - 7;

						pMove->x = 0.0f;
					}
					else if (pPosOld->x - 7 <= g_aBlock[nCntBlock].pos.x &&
						pPos->x + fwigth - 7 >= g_aBlock[nCntBlock].pos.x)
					{//���̓����蔻��
						pPos->x = g_aBlock[nCntBlock].pos.x - fwigth + 7;

						pMove->x = 0.0f;
					}
				}
			}
		}
	}
	return bLand;
}

//=============================================================================
//�A�C�e���̎擾
//=============================================================================
Block *GetBlock(void)
{
	return &g_aBlock[0];
}