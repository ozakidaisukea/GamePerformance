//=============================================================================
//
// DirectX���^���� [player.cpp]
// Author : Ozaki
//
//=============================================================================
#include "main.h"
#include "player.h"
#include "input.h"
#include "bullet.h"
#include "enemy.h"
#include "Player.h"
#include "Explosion.h"
#include "Game.h"
#include "sound.h"

//*****************************************************************************
//�}�N����`
//*****************************************************************************
#define MAX_MIKY		(50)

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
VERTEX_2D g_aVertex[4];													//���_�����i�[����
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;								//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;						//�e�N�X�`���̃|�C���^
int g_nCountAnim;														//�A�j���[�V�����J�E���^�[
int g_nPatternAnim;														//�A�j���[�V�����p�^�[��
Player g_Player;

//=============================================================================
// ����������(�|���S��)
//=============================================================================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevise;											//�f�o�C�X�̃|�C���^

	//�f�o�C�X�̎擾
	pDevise = GetDevice();

	g_Player.pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 1.1, 0.0f);
	g_Player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.bDisp = true;

	g_Player.nCounterState = 0;
	g_Player.nLife = 100;
	g_Player.state = PLAYERSTATE_NORMAL;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevise,
						      "data\\TEXTURE\\23.png",
							  &g_pTexturePlayer);

	////�e�N�X�`���A�j���[�V����
	//g_nCountAnim = 0;													//�J�E���^�[������������
	//g_nPatternAnim = 0;												//�p�^�[��������������

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
	pVtx[0].pos = D3DXVECTOR3(g_Player.pos.x - MAX_MIKY, g_Player.pos.y - MAX_MIKY, g_Player.pos.z);
	pVtx[1].pos = D3DXVECTOR3(g_Player.pos.x + MAX_MIKY, g_Player.pos.y - MAX_MIKY, g_Player.pos.z);
	pVtx[2].pos = D3DXVECTOR3(g_Player.pos.x - MAX_MIKY, g_Player.pos.y + MAX_MIKY, g_Player.pos.z);
	pVtx[3].pos = D3DXVECTOR3(g_Player.pos.x + MAX_MIKY, g_Player.pos.y + MAX_MIKY, g_Player.pos.z);

	//�e�N�X�`���̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f,0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f,0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f,1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f,1.0f);

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
	if (g_pVtxBuffPlayer  != NULL)
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
	//if (g_Player.pos.x = 0)
	//{
	//	g_Player.move.x = 0;
	//}

	switch (g_Player.state)
	{
	case PLAYERSTATE_NORMAL:
		break;

	case PLAYERSTATE_DAMAGE:
		g_Player.nCounterState--;
		if (g_Player.nCounterState <= 0)
		{
			g_Player.state = PLAYERSTATE_NORMAL;

			VERTEX_2D *pVtx;
			g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//���_�o�b�t�@���A�����b�N
			g_pVtxBuffPlayer->Unlock();
		}
		break;

	case PLAYERSTATE_DEATH:
		g_Player.nCounterState--;
		if (g_Player.nCounterState <= 0)
		{
			g_Player.state = PLAYERSTATE_NORMAL;
			SetGameState(GAMESTATE_GAMEOVER);
		}
		return;
		break;
	}

	if (g_Player.bDisp == true)
	{
		VERTEX_2D*pVtx;														//���_���ւ̃|�C���^																//���_�o�b�t�@�����b�N���A�e�N�X�`�����W���X�V
		g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);
		if (GetKeyboardPress(DIK_A) == true)
		{
			if (GetKeyboardPress(DIK_W) == true)
			{//����ړ�
				g_Player.move.x += -sinf(D3DX_PI / 4 * 1) *1.0f;
				g_Player.move.y += -cosf(D3DX_PI / 4 * 1) *1.0f;
			}
			else if (GetKeyboardPress(DIK_S) == true)
			{//�����ړ�
				g_Player.move.x += -sinf(D3DX_PI / 4 * 3) *1.0f;
				g_Player.move.y += -cosf(D3DX_PI / 4 * 3) *1.0f;
			}
			else
			{// ���ړ�
				g_Player.move.x += -sinf(D3DX_PI / 2) *1.0f;
				g_Player.move.y += -cosf(D3DX_PI / 2) *1.0f;
			}

		}
		else if (GetKeyboardPress(DIK_D) == true)
		{
			if (GetKeyboardPress(DIK_W) == true)
			{//�E��ړ�
				g_Player.move.x += sinf(D3DX_PI / 4 * 3) *1.0f;
				g_Player.move.y += cosf(D3DX_PI / 4 * 3) *1.0f;
			}
			else if (GetKeyboardPress(DIK_S) == true)
			{//�E���ړ�
				g_Player.move.x += sinf(D3DX_PI / 4 * 1) *1.0f;
				g_Player.move.y += cosf(D3DX_PI / 4 * 1) *1.0f;
			}
			else
			{// �E�ړ�
				g_Player.move.x += sinf(D3DX_PI / 2) *1.0f;
				g_Player.move.y += cosf(D3DX_PI / 2) *1.0f;
			}

		}
		//�C�ӂ̃L�[(S�L�[)�������ꂽ���ǂ���
		else if (GetKeyboardPress(DIK_S) == true)
		{
			g_Player.move.x += -sinf(D3DX_PI) *1.0f;
			g_Player.move.y += -cosf(D3DX_PI) *1.0f;
		}
		//�C�ӂ̃L�[(W�L�[)�������ꂽ���ǂ���
		else if (GetKeyboardPress(DIK_W) == true)
		{
			g_Player.move.x += sinf(D3DX_PI) *1.0f;
			g_Player.move.y += cosf(D3DX_PI) *1.0f;
		}
		//�C�ӂ̃L�[(SPACE�L�[)�������ꂽ���ǂ���
		if (GetKeyboardTrigger(DIK_SPACE) == true)
		{
			PlaySound(SOUND_LABEL_SE_ABE);
			SetBullet(g_Player.pos, D3DXVECTOR3(0.0f, 10.0f, 0.0f), BULLETTYPE_PLAYER);
		}

		g_Player.pos.x += g_Player.move.x;
		g_Player.pos.y += g_Player.move.y;

		g_Player.move.x += (0.0f - g_Player.move.x) *0.1f;
		g_Player.move.y += (0.0f - g_Player.move.y) *0.1f;

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_Player.pos.x - MAX_MIKY, g_Player.pos.y - MAX_MIKY, g_Player.pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_Player.pos.x + MAX_MIKY, g_Player.pos.y - MAX_MIKY, g_Player.pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_Player.pos.x - MAX_MIKY, g_Player.pos.y + MAX_MIKY, g_Player.pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_Player.pos.x + MAX_MIKY, g_Player.pos.y + MAX_MIKY, g_Player.pos.z);

		//���_�o�b�t�@���A�����b�N
		g_pVtxBuffPlayer->Unlock();

		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			PlaySound(SOUND_LABEL_SE_DECIDE);
			SetMode(MODE_RESULT);
		}
	}

}

//=============================================================================
// �`�揈��(�|���S��)
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f���@�C�X���擾
	pDevice = GetDevice();

	if (g_Player.bDisp == true)
	{
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

}
//=============================================================================
//�v���C���[�̃|�C���^�[�̎擾
//=============================================================================
Player *GetPlayer(void)
{
		return &g_Player;
}

//=============================================================================
//�G�̒e
//=============================================================================
void HitPlayer(int nDamage)
{
	g_Player.nLife -= nDamage;
	if (g_Player.nLife <= 0)
	{
		if (g_Player.bDisp == true)
		{
			SetExplosion(g_Player.pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.1f));
			g_Player.bDisp = false;
			g_Player.state = PLAYERSTATE_DEATH;
			PlaySound(SOUND_LABEL_SE_HUMAN2);
			g_Player.nCounterState = 10;
		}
	}
	else
	{
		g_Player.state = PLAYERSTATE_DAMAGE;
		g_Player.nCounterState = 5;

		// ���_���̍쐬
		VERTEX_2D *pVtx;

		g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

		g_pVtxBuffPlayer->Unlock();
	}
}