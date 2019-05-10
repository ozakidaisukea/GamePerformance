//=============================================================================
//
// �e���� [Dokan.cpp]
// Author : ozaki
//
//=============================================================================
#include "dokan.h"
#include "main.h"
#include "Player.h"
#include "Input.h"
#include "sound.h"
#include "item.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_Dokan		(100)		// �u���b�N�̍ő吔
#define MAX_MIKY		(50)		// �u���b�N�̑傫��
#define X_Y				(13)		// �����萔
#define Dokan_TYPEs		(1)			// �u���b�N�̎��
//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureDokan = {};		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffDokan = NULL;					// ���_�o�b�t�@�ւ̃|�C���^
Dokan g_aDokan;										// �u���b�N�̏��

//=============================================================================
// ����������
//=============================================================================
void InitDokan(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D*pVtx;										//���_���ւ̃|�C���^

	//�f���@�C�X���擾
	pDevice = GetDevice();

	// �e�̏��̏�����
		g_aDokan.pos = D3DXVECTOR3(680.0f, 600.0f, 0.0f);
		g_aDokan.fwidth = 10.0f;
		g_aDokan.fheight = 10.0f;
		g_aDokan.move = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		g_aDokan.bUse = false;
		g_aDokan.nCntItem = 0;

	// �u���b�N�̓ǂݍ���

	// �y�� [2]
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\dokan.png",
		&g_pTextureDokan);

	// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_Dokan,
		D3DUSAGE_WRITEONLY,
		FVF_VRETEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffDokan,
		NULL);

	////���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^�̎擾
	g_pVtxBuffDokan->Lock(0, 0, (void**)&pVtx, 0);


	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_aDokan.pos.x, g_aDokan.pos.y, g_aDokan.pos.z);
	pVtx[1].pos = D3DXVECTOR3(g_aDokan.pos.x + g_aDokan.fwidth, g_aDokan.pos.y, g_aDokan.pos.z);
	pVtx[2].pos = D3DXVECTOR3(g_aDokan.pos.x, g_aDokan.pos.y + g_aDokan.fheight, g_aDokan.pos.z);
	pVtx[3].pos = D3DXVECTOR3(g_aDokan.pos.x + g_aDokan.fwidth, g_aDokan.pos.y + g_aDokan.fheight, g_aDokan.pos.z);

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
	
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffDokan->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void UninitDokan(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureDokan != NULL)
	{
			g_pTextureDokan->Release();
			g_pTextureDokan = NULL;
	}
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffDokan != NULL)
	{
		g_pVtxBuffDokan->Release();
		g_pVtxBuffDokan = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateDokan(void)
{

	D3DXVECTOR3 move;
	VERTEX_2D*pVtx;										//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^�̎擾
	g_pVtxBuffDokan->Lock(0, 0, (void**)&pVtx, 0);
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffDokan->Unlock();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawDokan(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffDokan, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VRETEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureDokan);

	// �|���S���̕`��

	//�|���S���̔j��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);
	}
//=============================================================================
// �u���b�N�̐ݒ菈��
//=============================================================================
void SetDokan(D3DXVECTOR3 pos, float fwidth, float fheigth,Dokan_TYPE type)
{
	
	VERTEX_2D*pVtx;													//���_���ւ̃|�C���^

	g_pVtxBuffDokan->Lock(0, 0, (void**)&pVtx, 0);

		if (g_aDokan.bUse == false)						//�u���b�N���g�p����Ă���
		{
			g_aDokan.pos = pos;
			g_aDokan.fwidth = fwidth;
			g_aDokan.fheight = fheigth;
			switch (g_aDokan.type)
			{
				// �y��
			case DokanType_Dokan:
				g_aDokan.nType = 1;
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				break;
			}
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aDokan.pos.x, g_aDokan.pos.y, g_aDokan.pos.z);
			pVtx[1].pos = D3DXVECTOR3(g_aDokan.pos.x + g_aDokan.fwidth, g_aDokan.pos.y, g_aDokan.pos.z);
			pVtx[2].pos = D3DXVECTOR3(g_aDokan.pos.x, g_aDokan.pos.y + g_aDokan.fheight, g_aDokan.pos.z);
			pVtx[3].pos = D3DXVECTOR3(g_aDokan.pos.x + g_aDokan.fwidth, g_aDokan.pos.y + g_aDokan.fheight, g_aDokan.pos.z);

			g_aDokan.bUse = true;
			//break;
		}
		pVtx += 4;

	g_pVtxBuffDokan->Unlock();
}

//=============================================================================
// �u���b�N�̓����蔻�菈��
//=============================================================================
bool CollisionDokan(D3DXVECTOR3 *pPos, D3DXVECTOR3*pPosOld, D3DXVECTOR3 *pMove, float fwigth, float fheigth)								//�ړ�
{
	int nCntDokan;

	bool bLand = false;					//���n�������ǂ���
	
	Player *pPlayer;
	pPlayer = GetPlayer();

	for (nCntDokan = 0; nCntDokan < MAX_Dokan; nCntDokan++)
	{

		if (g_aDokan.bUse == true)
		{
			if (pPos->x + fwigth - X_Y >= g_aDokan.pos.x
				&& pPos->x - fwigth + X_Y <= g_aDokan.pos.x + g_aDokan.fwidth)
			{
				if (pPosOld->y <= g_aDokan.pos.y && pPos->y >= g_aDokan.pos.y)
				{//��̓����蔻��

				 // �e�u���b�N���d�l
					if (g_aDokan.type == DokanType_Dokan)
					{// �y��
						pPosOld->x >= g_aDokan.pos.x - g_aDokan.fwidth &&
							pPos->x + fwigth <= g_aDokan.pos.x - g_aDokan.fwidth;
						{//�E�̓����蔻��

							pPosOld->x - X_Y <= g_aDokan.pos.x &&
								pPos->x - fwigth - X_Y >= g_aDokan.pos.x;
							{//���̓����蔻��
								pPos->y = g_aDokan.pos.y;
								bLand = true;
								pMove->y = 0.0f;
							}
						}
					}
				}
				else if (pPosOld->y - fheigth >= g_aDokan.pos.y + 7/* + g_aDokan.fheight*/
					&& pPos->y - fheigth <= g_aDokan.pos.y + 7/*+ g_aDokan.fheight*/)
				{//���̓����蔻��

					Player *pPlayer;
					pPlayer = GetPlayer();

					pPlayer->bJunp = true;


					//pPos->y = g_aDokan.pos.y + g_aDokan.fheight + fheigth;

					pMove->y = 0.0f;

					//pPos->y = g_aDokan.pos.y + g_aDokan.fheight + fheigth;
				}
				if (//�����瑫
					pPosOld->y - fheigth >= g_aDokan.pos.y
					&& pPosOld->y <= g_aDokan.pos.y + g_aDokan.fheight
					//������
					|| pPosOld->y - fheigth > g_aDokan.pos.y
					&& pPosOld->y - fheigth < g_aDokan.pos.y + g_aDokan.fheight
					// ������
					|| pPosOld->y > g_aDokan.pos.y
					&& pPosOld->y < g_aDokan.pos.y + g_aDokan.fheight)
				{
					if (pPosOld->x + X_Y >= g_aDokan.pos.x + g_aDokan.fwidth &&
						pPos->x - fwigth + X_Y <= g_aDokan.pos.x + g_aDokan.fwidth)
					{//�E�̓����蔻��
						pPos->x = g_aDokan.pos.x + g_aDokan.fwidth + fwigth - X_Y;

						pMove->x = 0.0f;
					}
					else if (pPosOld->x - X_Y <= g_aDokan.pos.x &&
						pPos->x + fwigth - X_Y >= g_aDokan.pos.x)
					{//���̓����蔻��
						pPos->x = g_aDokan.pos.x - fwigth + X_Y;

						pMove->x = 0.0f;
					}
				}

				if (pPlayer->state == PLAYER_BIGSTATE)
				{


					if (//�����瑫
						pPosOld->y - fheigth >= g_aDokan.pos.y
						&& pPosOld->y <= g_aDokan.pos.y + g_aDokan.fheight
						//������
						|| pPosOld->y - fheigth > g_aDokan.pos.y
						&& pPosOld->y - fheigth < g_aDokan.pos.y + g_aDokan.fheight
						// ������
						|| pPosOld->y > g_aDokan.pos.y
						&& pPosOld->y < g_aDokan.pos.y + g_aDokan.fheight)
					{
						if (pPosOld->x + 7 >= g_aDokan.pos.x + g_aDokan.fwidth &&
							pPos->x - fwigth + 7 <= g_aDokan.pos.x + g_aDokan.fwidth)
						{//�E�̓����蔻��
							pPos->x = g_aDokan.pos.x + g_aDokan.fwidth + fwigth - 7;

							pMove->x = 0.0f;
						}
						else if (pPosOld->x - 7 <= g_aDokan.pos.x &&
							pPos->x + fwigth - 7 >= g_aDokan.pos.x)
						{//���̓����蔻��
							pPos->x = g_aDokan.pos.x - fwigth + 7;

							pMove->x = 0.0f;
						}

					}
				}
			}
		}
	}
	return bLand;
}