//=============================================================================
//
// DirectX���^���� [player.cpp]
// Author : Ozaki
//
//=============================================================================
#include "main.h"
#include "player.h"
#include "Input.h"
#include "block.h"
#include "player.h"
#include "item.h"
#include "sound.h"
#include "dokan.h"
#include "Game.h"

//*****************************************************************************
//�}�N����`
//*****************************************************************************
#define MAX_MIKY		(40)
#define PLAYER_JNP		(600)
#define MAX_WIDTH		(30)
#define MAX_HEIGHT		(40)

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
VERTEX_2D g_aVertex[4];											//���_�����i�[����
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;						//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;				//�e�N�X�`���̃|�C���^
Player g_Player;
int nCountAnim;
int nPatternAnim;
D3DXVECTOR3 pos;
//=============================================================================
// ����������(�|���S��)
//=============================================================================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevise;									//�f�o�C�X�̃|�C���^

	//�f�o�C�X�̎擾
	pDevise = GetDevice();

	g_Player.pos = D3DXVECTOR3(950.0f, 100.0f, 0.0f);
	g_Player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.bDisp = true;
	g_Player.bJunp = false;
	g_Player.fwidth = MAX_WIDTH;
	g_Player.fheigth = MAX_HEIGHT;
	g_Player.state = PLAYER_NORMAL;
	g_Player.nCounterState = 0;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevise,
		"data\\TEXTURE\\mario2.png",
		&g_pTexturePlayer);

	//���_�o�b�t�@�̐���
	pDevise->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VRETEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPlayer,
		NULL);

	//���[�J���ϐ�
	VERTEX_2D*pVtx;														//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^�̎擾
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_Player.pos.x - g_Player.fwidth, g_Player.pos.y - g_Player.fheigth, g_Player.pos.z);
	pVtx[1].pos = D3DXVECTOR3(g_Player.pos.x + g_Player.fwidth, g_Player.pos.y - g_Player.fheigth, g_Player.pos.z);
	pVtx[2].pos = D3DXVECTOR3(g_Player.pos.x - g_Player.fwidth, g_Player.pos.y , g_Player.pos.z);
	pVtx[3].pos = D3DXVECTOR3(g_Player.pos.x + g_Player.fwidth, g_Player.pos.y , g_Player.pos.z);

	//�e�N�X�`���̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
	pVtx[3].tex = D3DXVECTOR2(0.25f, 0.5f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffPlayer->Unlock();
}

//=============================================================================
// �I������(�|���S��)
//=============================================================================
void UninitPlayer(void)
{
	//�e�N�X�`���̔j��
	if (g_pTexturePlayer != NULL)
	{
		g_pTexturePlayer->Release();
		g_pTexturePlayer = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPlayer != NULL)
	{
		g_pVtxBuffPlayer->Release();
		g_pVtxBuffPlayer = NULL;
	}
}

//=============================================================================
// �X�V����(�|���S��)
//=============================================================================
void UpdatePlayer(void)
{
	g_Player.posold = g_Player.pos;

	VERTEX_2D*pVtx;							//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A�e�N�X�`�����W���X�V
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//���ړ�
	if (GetKeyboardPress(DIK_A) == true)
	{
		//PlaySound(SOUND_LABRL_SE_running);
		g_Player.DirectionMove0 = 1;
		g_Player.move.x += sinf(-D3DX_PI / 2) *1.0f;
		g_Player.move.y += -cosf(D3DX_PI / 2) *1.0f;
	}
	//�E�ړ�
	else if (GetKeyboardPress(DIK_D) == true)
	{
		//PlaySound(SOUND_LABRL_SE_running);
		g_Player.DirectionMove0 = 0;
		g_Player.move.x += sinf(D3DX_PI / 2) *1.0f;
		g_Player.move.y += cosf(D3DX_PI / 2) *1.0f;

	}

	//�C�ӂ̃L�[(SPACE�L�[)�������ꂽ���ǂ���
	if (GetKeyboardTrigger(DIK_SPACE) == true)
	{
		if (g_Player.bJunp == false)
		{
			PlaySound(SOUND_LABRL_SE_junp);
			g_Player.move.y = -20;

			g_Player.bJunp = true;
		}
	}

	if (g_Player.bJunp == false)
	{// �W�����v���Ă��Ȃ���
		if (g_Player.move.x > 2 || g_Player.move.x < -2)
		{// �ړ����Ă���Ƃ�
			g_Player.nCounterAnim++;

			if ((g_Player.nCounterAnim % 5) == 0)
			{
				if(g_Player.nPatternAnim == 2)
				{
					g_Player.nPatternAnim = 1;
				}
				else if(g_Player.nPatternAnim == 1)
				{
					g_Player.nPatternAnim = 2;
				}
				else
				{
					g_Player.nPatternAnim = 1;
				}

				//�e�N�X�`���̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(g_Player.nPatternAnim * 0.25f, 0.0f + (g_Player.DirectionMove0 * 0.5f));
				pVtx[1].tex = D3DXVECTOR2(g_Player.nPatternAnim * 0.25f + 0.25f, 0.0f + (g_Player.DirectionMove0 * 0.5f));
				pVtx[2].tex = D3DXVECTOR2(g_Player.nPatternAnim * 0.25f, 0.5f + (g_Player.DirectionMove0 * 0.5f));
				pVtx[3].tex = D3DXVECTOR2(g_Player.nPatternAnim * 0.25f + 0.25f, 0.5f + (g_Player.DirectionMove0 * 0.5f));

				//�p�^�[���A�j���[�V����
				nPatternAnim++;
			}
		}
		else
		{// �ړ����Ă��Ȃ��Ƃ�
			if (g_Player.nPatternAnim != 0)
			{
				g_Player.nCounterAnim++;

				if ((g_Player.nCounterAnim % 2) == 0)
				{
					g_Player.nPatternAnim = 0;

					//�e�N�X�`���̐ݒ�
					pVtx[0].tex = D3DXVECTOR2(g_Player.nPatternAnim * 0.25f, 0.0f + (g_Player.DirectionMove0 * 0.5f));
					pVtx[1].tex = D3DXVECTOR2(g_Player.nPatternAnim * 0.25f + 0.25f, 0.0f + (g_Player.DirectionMove0 * 0.5f));
					pVtx[2].tex = D3DXVECTOR2(g_Player.nPatternAnim * 0.25f, 0.5f + (g_Player.DirectionMove0 * 0.5f));
					pVtx[3].tex = D3DXVECTOR2(g_Player.nPatternAnim * 0.25f + 0.25f, 0.5f + (g_Player.DirectionMove0 * 0.5f));
				}
			}

		}

	}
	else
	{// �W�����v���Ă���Ƃ�
		if (g_Player.nPatternAnim != 3)
		{
			g_Player.nCounterAnim++;

			if ((g_Player.nCounterAnim % 10) == 0)
			{
				g_Player.nPatternAnim = 3;

				//�e�N�X�`���̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(g_Player.nPatternAnim * 0.25f, 0.0f + (g_Player.DirectionMove0 * 0.5f));
				pVtx[1].tex = D3DXVECTOR2(g_Player.nPatternAnim * 0.25f + 0.25f, 0.0f + (g_Player.DirectionMove0 * 0.5f));
				pVtx[2].tex = D3DXVECTOR2(g_Player.nPatternAnim * 0.25f, 0.5f + (g_Player.DirectionMove0 * 0.5f));
				pVtx[3].tex = D3DXVECTOR2(g_Player.nPatternAnim * 0.25f + 0.25f, 0.5f + (g_Player.DirectionMove0 * 0.5f));
			}
		}
	}
	g_Player.move.x += (0.0f - g_Player.move.x) *0.1f;
	g_Player.move.y += 1.0f;

	g_Player.pos.x += g_Player.move.x;
	g_Player.pos.y += g_Player.move.y;

	if (g_Player.pos.x < 0)
	{
		g_Player.pos.x = SCREEN_WIDTH;
		g_Player.posold.x = g_Player.pos.x;
	}

	if (g_Player.pos.x > SCREEN_WIDTH)
	{
		g_Player.pos.x = 0;
		g_Player.posold.x = g_Player.pos.x;
	}
	if (g_Player.pos.y >= SCREEN_HEIGHT)
	{
		GAMESTATE GameState;
		GameState = GetGameState();
		if (GameState != GAMESTATE_GAMEOVER)
		{
			//SetGameState(GAMESTATE_END);
			SetGameState(GAMESTATE_GAMEOVER);
			PlaySound(SOUND_LABEL_SE_MARIO_DETH);
			StopSound(SOUND_LABEL_SE_MARIO_DETH);
		}

	}

	if (CollisionBlock(&g_Player.pos, &g_Player.posold, &g_Player.move, g_Player.fwidth, g_Player.fheigth) == true || CollisionDokan(&g_Player.pos, &g_Player.posold, &g_Player.move, g_Player.fwidth, g_Player.fheigth) == true)
	{
		g_Player.bJunp = false;
	}
	else
	{
		g_Player.bJunp = true;
	}

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_Player.pos.x - g_Player.fwidth, g_Player.pos.y - g_Player.fheigth, g_Player.pos.z);
	pVtx[1].pos = D3DXVECTOR3(g_Player.pos.x + g_Player.fwidth, g_Player.pos.y - g_Player.fheigth, g_Player.pos.z);
	pVtx[2].pos = D3DXVECTOR3(g_Player.pos.x - g_Player.fwidth, g_Player.pos.y, g_Player.pos.z);
	pVtx[3].pos = D3DXVECTOR3(g_Player.pos.x + g_Player.fwidth, g_Player.pos.y, g_Player.pos.z);

	//�e�N�X�`���̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(g_Player.nPatternAnim * 0.25f, 0.0f + (g_Player.DirectionMove0 * 0.5f));
	pVtx[1].tex = D3DXVECTOR2(g_Player.nPatternAnim * 0.25f + 0.25f, 0.0f + (g_Player.DirectionMove0 * 0.5f));
	pVtx[2].tex = D3DXVECTOR2(g_Player.nPatternAnim * 0.25f, 0.5f + (g_Player.DirectionMove0 * 0.5f));
	pVtx[3].tex = D3DXVECTOR2(g_Player.nPatternAnim * 0.25f + 0.25f, 0.5f + (g_Player.DirectionMove0 * 0.5f));

	CollisionItem(&g_Player.pos, &g_Player.move, g_Player.fwidth, g_Player.fheigth);

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffPlayer->Unlock();
}

//=============================================================================
// �`�揈��(�|���S��)
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f���@�C�X���擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPlayer, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VRETEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturePlayer);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);
}
//=============================================================================
// �v���C���[���擾
//=============================================================================
Player *GetPlayer(void)
{
	return &g_Player;
}