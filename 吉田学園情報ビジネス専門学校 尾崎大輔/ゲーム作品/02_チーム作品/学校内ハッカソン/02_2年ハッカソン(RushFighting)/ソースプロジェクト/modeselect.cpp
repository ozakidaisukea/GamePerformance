//=============================================================================
//
// ���[�h�Z���N�g�̏��� [modeselect.cpp]
// Author : Niwa Hodaka
//
//=============================================================================
#include "modeselect.h"
#include "fade.h"
#include "input.h"
#include "sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_NAME1        "data/TEXTURE/gamestart.png" // �ǂݍ��ރe�N�X�`���t�@�C����(GAMESTART)
#define TEXTURE_NAME2        "data/TEXTURE/tutorial.png"  // �ǂݍ��ރe�N�X�`���t�@�C����(TUTORIAL)
#define TEXTURE_NAME3        "data/TEXTURE/ranking.png"   // �ǂݍ��ރe�N�X�`���t�@�C����(RANKING)
#define TEXTURE_NAME4        "data/TEXTURE/title.png"     // �ǂݍ��ރe�N�X�`���t�@�C����(TITLE)
#define MODESELECT_POS_X    (470)                         // ���[�h���ڂ̍���w���W
#define MODESELECT_POS_Y    (170)                         // ���[�h���ڍ���x���W
#define MODESELECT_WIDTH    (800)                         // ���[�h���ڂ̕�
#define MODESELECT_HEIGHT   (230)                         // ���[�h���ڂ̍���

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexModeSelect(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureModeSelect[MODESTART_MAX] = {};  // �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffModeSelect = NULL;               // ���_�o�b�t�@�ւ̃|�C���^
MODESELECT              g_aModeSelect[MODESTART_MAX];              // ���[�h����
float                   g_Modecol;                                 // �F�̕ω��Ɏg�p
int                     g_ModeSelect;                              // �I���Ɏg�p

//=============================================================================
// ����������
//=============================================================================
void InitModeSelect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_aModeSelect[0].col = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);  // �F��������
	g_aModeSelect[0].state = MODESTATE_SELECT;                 // �X�^�[�g��MODESTART_GAME����

	// �l�̏�����
	for (int nCntModeSelect = 1; nCntModeSelect < MODESTART_MAX; nCntModeSelect++)
	{// ���ڂ̐������J��Ԃ�
		g_aModeSelect[nCntModeSelect].col = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);  // �F��������
		g_aModeSelect[nCntModeSelect].state = MODESTATE_NONE;                   // �I������Ă��Ȃ���Ԃɂ���
	}
	g_Modecol = 0.01f;    // �F�̕ω���������
	g_ModeSelect = 0;     // �I������Ă���ԍ���MODESTART_GAME��

	// ���_���̐ݒ�
	MakeVertexModeSelect(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitModeSelect(void)
{
	// �e�N�X�`���̊J��
	for (int nCntModeSelect = 0; nCntModeSelect < MODESTART_MAX; nCntModeSelect++)
	{// �ǂݍ��񂾃e�N�X�`���̐������J��Ԃ�
		if (g_pTextureModeSelect[nCntModeSelect] != NULL)
		{
			g_pTextureModeSelect[nCntModeSelect]->Release();
			g_pTextureModeSelect[nCntModeSelect] = NULL;
		}
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffModeSelect != NULL)
	{
		g_pVtxBuffModeSelect->Release();
		g_pVtxBuffModeSelect = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateModeSelect(void)
{
	// �I�����ڈړ�����
	if (GetJoyPadTrigger(DIJS_BUTTON_18) == TRUE || GetKeyboardTrigger(DIK_W) == true)
	{// ������̓��͂����ꂽ
		g_aModeSelect[g_ModeSelect].state = MODESTATE_NONE;
		g_aModeSelect[(g_ModeSelect + (MODESTART_MAX - 1)) % MODESTART_MAX].state = MODESTATE_SELECT;
		g_ModeSelect = (g_ModeSelect + (MODESTART_MAX - 1)) % MODESTART_MAX;
	}
	if (GetJoyPadTrigger(DIJS_BUTTON_19) == TRUE || GetKeyboardTrigger(DIK_S) == true)
	{// �������̓��͂����ꂽ
		g_aModeSelect[g_ModeSelect].state = MODESTATE_NONE;
		g_aModeSelect[(g_ModeSelect + 1) % MODESTART_MAX].state = MODESTATE_SELECT;
		g_ModeSelect = (g_ModeSelect + 1) % MODESTART_MAX;
	}

	VERTEX_2D *pVtx;   // ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffModeSelect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntModeSelect = 0; nCntModeSelect < MODESTART_MAX; nCntModeSelect++)
	{// ���ڂ̐������J��Ԃ�
		if (g_aModeSelect[nCntModeSelect].state == MODESTATE_SELECT)
		{// �I������Ă�����
			g_aModeSelect[nCntModeSelect].col.r += g_Modecol;   // �_�ł�����
			g_aModeSelect[nCntModeSelect].col.g += g_Modecol;   // �_�ł�����
			g_aModeSelect[nCntModeSelect].col.b += g_Modecol;   // �_�ł�����

			if (g_aModeSelect[nCntModeSelect].col.r < 0.2f || g_aModeSelect[nCntModeSelect].col.r >= 1.0f)
			{// �F������̒l�ɒB����
				g_Modecol *= -1;  // �F�̕ω��𔽓]
			}
		}
		else if (g_aModeSelect[nCntModeSelect].state == MODESTATE_NONE)
		{// �I������Ă��Ȃ�������
			g_aModeSelect[nCntModeSelect].col.r = 0.2f;   // �F���Œ�
			g_aModeSelect[nCntModeSelect].col.g = 0.2f;   // �F���Œ�
			g_aModeSelect[nCntModeSelect].col.b = 0.2f;   // �F���Œ�
		}
		// ���_�J���[�̍X�V
		pVtx[0].col = g_aModeSelect[nCntModeSelect].col;
		pVtx[1].col = g_aModeSelect[nCntModeSelect].col;
		pVtx[2].col = g_aModeSelect[nCntModeSelect].col;
		pVtx[3].col = g_aModeSelect[nCntModeSelect].col;

		pVtx += 4;  // �|�C���^��i�߂�
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffModeSelect->Unlock();

	// ��ʑJ��
	if (GetJoyPadTrigger(DIJS_BUTTON_2) == TRUE || GetKeyboardTrigger(DIK_RETURN) == true)
	{// ����{�^���������ꂽ
		FADE fade;
		fade = GetFade();

		if (fade == FADE_NONE)
		{// �t�F�[�h��ԂłȂ�
			switch (g_ModeSelect)
			{
			case MODESTART_GAME:
				SetFade(MODE_GAME);      // �Q�[����ʂֈڍs
				break;
			case MODESTART_TUTORIAL:
				SetFade(MODE_TUTORIAL);  // �`���[�g���A����ʂֈڍs
				break;
			case MODESTART_RANKING:
				SetFade(MODE_RANKING);   // �����L���O��ʂֈڍs
				break;
			case MODESTART_TITLE:
				SetFade(MODE_TITLE);     // �^�C�g����ʂֈڍs
				break;
			}
		}
	}
}
//=============================================================================
// �^�C�g�����
//=============================================================================
void DrawModeSelect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffModeSelect, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntModeSelect = 0; nCntModeSelect < MODESTART_MAX; nCntModeSelect++)
	{// ���ڂ̐������J��Ԃ�
	    // �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureModeSelect[nCntModeSelect]);

		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntModeSelect * 4, NUM_POLYGON);
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexModeSelect(LPDIRECT3DDEVICE9 pDevice)
{
	// �e�N�X�`���̓ǂݍ���(GAMESTART)
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_NAME1,
		&g_pTextureModeSelect[0]);

	// �e�N�X�`���̓ǂݍ���(TUTORIAL)
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_NAME2,
		&g_pTextureModeSelect[1]);

	// �e�N�X�`���̓ǂݍ���(RANKING)
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_NAME3,
		&g_pTextureModeSelect[2]);

	// �e�N�X�`���̓ǂݍ���(TITLE
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_NAME4,
		&g_pTextureModeSelect[3]);

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MODESTART_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffModeSelect,
		NULL);

	VERTEX_2D *pVtx;   // ���_���ւ̃|�C���^

    // ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffModeSelect->Lock(0, 0, (void**)&pVtx, 0);

	float Pos = 0.0f;  // ���W�����炷�̂Ɏg�p

	for (int nCntModeSelect = 0; nCntModeSelect < MODESTART_MAX; nCntModeSelect++)
	{// ���ڂ̐������J��Ԃ�
	    // ���_���W
		pVtx[0].pos = D3DXVECTOR3(MODESELECT_POS_X, MODESELECT_POS_Y + Pos, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(MODESELECT_WIDTH, MODESELECT_POS_Y + Pos, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(MODESELECT_POS_X, MODESELECT_HEIGHT + Pos, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(MODESELECT_WIDTH, MODESELECT_HEIGHT + Pos, 0.0f);

		// ���_�e�N�X�`��
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// ���_�J���[
		pVtx[0].col = g_aModeSelect[nCntModeSelect].col;
		pVtx[1].col = g_aModeSelect[nCntModeSelect].col;
		pVtx[2].col = g_aModeSelect[nCntModeSelect].col;
		pVtx[3].col = g_aModeSelect[nCntModeSelect].col;

		// �e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;   // �|�C���^��i�߂�
		Pos += 110;  // ���W�����炷
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffModeSelect->Unlock();
}