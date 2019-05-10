//=============================================================================
//
// �^�C������ [timer.cpp]
// Author : Jukiya Hayakawa
//
//=============================================================================
#include "game.h"
#include "result.h"
#include "timer.h"
#include "fade.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define	TEXTURE_TIMER		"data/TEXTURE/number003.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define TEXTURE_SIZE        (30)                            // �e�N�X�`���̃T�C�Y
#define MAX_TIMERNUMBER     (3)                             // �X�R�A�̌���
#define MAX_TIMER			(999)							// �^�C�}�[�̍ő�l
//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void MakeVertexTimer(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureTimer = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTimer = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3             g_TimerPos;                 // ���_���W
TIMERSTATE              g_TimerState;               // �^�C�}�[�̏��
int                     g_TexturePosTimer;          // �e�N�X�`��X���W
int                     g_nTimer;                   // �^�C�}�[
int                     g_nCounterTimer;            // �^�C�}�[�����炷�^�C�~���O
bool					g_bStopTimer;				//�^�C�}�[���~�߂�

//=============================================================================
// ����������
//=============================================================================
void InitTimer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_nTimer = MAX_TIMER;							// �^�C�}�[�̏�����
	g_bStopTimer = false;							// �~�܂��Ă��Ȃ���Ԃɂ���
	g_TimerPos = D3DXVECTOR3(SCREEN_WIDTH / 2 + 50, 50.0f, 0.0f);		// ���W�̏�����

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		TEXTURE_TIMER,		                        // �t�@�C���̖��O
		&g_pTextureTimer);	                        // �e�N�X�`���ւ̃|�C���^

	// ���_���̍쐬
	MakeVertexTimer(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitTimer(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureTimer != NULL)
	{
		g_pTextureTimer->Release();
		g_pTextureTimer = NULL;
	}

	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffTimer != NULL)
	{
		g_pVtxBuffTimer->Release();
		g_pVtxBuffTimer = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateTimer(void)
{
	//�t�F�[�h�̎擾
	FADE fade;
	fade = GetFade();

	if (g_bStopTimer == TIMERSTATE_COUNT)
	{// �^�C�}�[��i�߂��Ԃ�������
		int time = 1;
		g_nCounterTimer++;
		if (g_nCounterTimer % 60 == 0)
		{// ��b�Ԃ�������
			g_nTimer--;
			if (g_nTimer >= 0)
			{
				VERTEX_2D *pVtx;

				// ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
				g_pVtxBuffTimer->Lock(0, 0, (void**)&pVtx, 0);

				for (int nCntTimer = 0; nCntTimer < MAX_TIMERNUMBER; nCntTimer++)
				{// �^�C�}�[�̌��������J��Ԃ�
					g_TexturePosTimer = g_nTimer % (time * 10) / time;

					// �e�N�X�`�����W�̐ݒ�
					pVtx[0].tex = D3DXVECTOR2(0.0f + (g_TexturePosTimer * 0.1f), 0.0f);
					pVtx[1].tex = D3DXVECTOR2(0.1f + (g_TexturePosTimer * 0.1f), 0.0f);
					pVtx[2].tex = D3DXVECTOR2(0.0f + (g_TexturePosTimer * 0.1f), 1.0f);
					pVtx[3].tex = D3DXVECTOR2(0.1f + (g_TexturePosTimer * 0.1f), 1.0f);

					time *= 10;
					pVtx += 4;
				}

				// ���_�o�b�t�@���A�����b�N����
				g_pVtxBuffTimer->Unlock();
			}
			if (g_nTimer <= 30)
			{
				VERTEX_2D *pVtx;

				// ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
				g_pVtxBuffTimer->Lock(0, 0, (void**)&pVtx, 0);
				for (int nCntTimer = 0; nCntTimer < MAX_TIMERNUMBER; nCntTimer++)
				{// �^�C�}�[�̌��������J��Ԃ�
					// ���_�J���[
					pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
					pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
					pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
					pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

					pVtx += 4;
				}
				// ���_�o�b�t�@���A�����b�N����
				g_pVtxBuffTimer->Unlock();
			}
			else if (g_nTimer < 0 && fade == FADE_NONE)
			{// �^�C�}�[��0�ɂȂ�����
				SetGameState(GAMESTATE_END);
			}
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawTimer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTimer, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureTimer);

	// �|���S���̕`��
	for (int nCntScore = 0; nCntScore < MAX_TIMERNUMBER; nCntScore++)
	{// �\������^�C�}�[�̌��������J��Ԃ�
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			nCntScore * 4,
			2);
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexTimer(LPDIRECT3DDEVICE9 pDevice)
{
	int time = 1;

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TIMERNUMBER,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTimer,
		NULL);

	// ���_�o�b�t�@�𐶐�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffTimer->Lock(0, 0, (void**)&pVtx, 0);

	// ���_����ݒ�
	for (int nCntTimer = 0; nCntTimer < MAX_TIMERNUMBER; nCntTimer++)
	{// �^�C�}�[�̌��������J��Ԃ�
		g_TexturePosTimer = g_nTimer % (time * 10) / time;

		// ���_���W
		pVtx[0].pos = D3DXVECTOR3(g_TimerPos.x - TEXTURE_SIZE, g_TimerPos.y - TEXTURE_SIZE, g_TimerPos.z);
		pVtx[1].pos = D3DXVECTOR3(g_TimerPos.x + TEXTURE_SIZE, g_TimerPos.y - TEXTURE_SIZE, g_TimerPos.z);
		pVtx[2].pos = D3DXVECTOR3(g_TimerPos.x - TEXTURE_SIZE, g_TimerPos.y + TEXTURE_SIZE, g_TimerPos.z);
		pVtx[3].pos = D3DXVECTOR3(g_TimerPos.x + TEXTURE_SIZE, g_TimerPos.y + TEXTURE_SIZE, g_TimerPos.z);


		// ���_�e�N�X�`��
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// ���_�J���[
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f + (g_TexturePosTimer * 0.1f), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + (g_TexturePosTimer * 0.1f), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (g_TexturePosTimer * 0.1f), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + (g_TexturePosTimer * 0.1f), 1.0f);

		pVtx += 4;
		g_TimerPos.x -= 50;
		time *= 10;
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTimer->Unlock();
}

//=============================================================================
// �^�C�}�[�̎擾
//=============================================================================
void StopTimerState(void)
{
	g_bStopTimer = TIMERSTATE_NONE_COUNT;
}