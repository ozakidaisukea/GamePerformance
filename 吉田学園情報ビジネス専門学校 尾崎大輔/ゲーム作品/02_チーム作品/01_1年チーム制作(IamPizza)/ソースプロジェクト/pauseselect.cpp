//=============================================================================
//
// �|�[�Y���j���[���� [pauseselect.cpp]
// Author : Mikiya Meguro
//
//=============================================================================
#include "input.h"
#include "fade.h"
#include "pauseselect.h" 
#include "Player.h"
#include "tutorial.h"
#include "sound.h"
#include "inputx.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_CONTINUE		"data/TEXTURE/pause000.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_RETRY			"data/TEXTURE/pause001.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_QUIT			"data/TEXTURE/pause002.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define PAUSESELECT_POS_X			(200)						//���_���WX�̈ړ���
#define PAUSESELECT_POS_Y			(50)						//���_���WY�̈ړ���
//#define TEX_PS_X_INIT			(1.0f)						//�e�N�X�`�����WU�̏����ʒu
//#define TEX_PS_Y_INIT			(1.0f)						//�e�N�X�`�����WV�̏����ʒu
#define TEX_LEFT				(0.0f)						//�e�N�X�`�����WU��
#define TEX_RIGHT				(1.0f)						//�e�N�X�`�����WU�E
#define TEX_TOP					(0.0f)						//�e�N�X�`�����WV��
#define TEX_BOT					(1.0f)						//�e�N�X�`�����WV��
#define MAX_PAUSEMENU			(3)							//�����L���O�̐�

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexPauseSelect(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTexturePauseSelect[MAX_PAUSEMENU] = {};		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPauseSelect = NULL;					// ���_�o�b�t�@�ւ̃|�C���^
PAUSESELECT				g_aPauseMenu[MAX_PAUSEMENU];					// �|�[�Y���j���[
D3DXVECTOR3				g_PauseMenuPos;
SELECTMODE				g_SelectMode = SELECTMODE_NONE;
int						g_nSelect;
JoyState g_JoyStatePause;
//=============================================================================
// ����������
//=============================================================================
void InitPauseSelect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	g_JoyStatePause.nJoypadState = INPUT_JOYSTATE_NOTPUSH;
	float fMenuPosY = 0;
	g_nSelect = 0;
	g_PauseMenuPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_SelectMode = SELECTMODE_NONE;

	g_aPauseMenu[0].pos = D3DXVECTOR3(650.0f, 200.0f + (fMenuPosY), 0.0f);
	g_aPauseMenu[0].col = D3DXCOLOR(0.0f, 0.5f, 1.0f, 1.0f);
	g_aPauseMenu[0].select = SELECTTYPE_SELECT;
	fMenuPosY += 150;
	for (int nCnt = 1; nCnt < MAX_PAUSEMENU; nCnt++)
	{
		g_aPauseMenu[nCnt].pos = D3DXVECTOR3(650.0f, 200.0f + (fMenuPosY), 0.0f);
		g_aPauseMenu[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aPauseMenu[nCnt].select = SELECTTYPE_NONE;
		fMenuPosY += 150;
	}

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,			// �f�o�C�X�ւ̃|�C���^
		TEXTURE_CONTINUE,						// �t�@�C���̖��O
		&g_pTexturePauseSelect[0]);				// �e�N�X�`���ւ̃|�C���^

											
	D3DXCreateTextureFromFile(pDevice,			// �f�o�C�X�ւ̃|�C���^
		TEXTURE_RETRY,							// �t�@�C���̖��O
		&g_pTexturePauseSelect[1]);				// �e�N�X�`���ւ̃|�C���^
											
	D3DXCreateTextureFromFile(pDevice,			// �f�o�C�X�ւ̃|�C���^
		TEXTURE_QUIT,							// �t�@�C���̖��O
		&g_pTexturePauseSelect[2]);				// �e�N�X�`���ւ̃|�C���^

	// ���_���̍쐬
	MakeVertexPauseSelect(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitPauseSelect(void)
{
	for (int nCnt = 0; nCnt < MAX_PAUSEMENU; nCnt++)
	{// �e�N�X�`���̊J��
		if (g_pTexturePauseSelect[nCnt] != NULL)
		{
			g_pTexturePauseSelect[nCnt]->Release();
			g_pTexturePauseSelect[nCnt] = NULL;
		}
	}
		// ���_�o�b�t�@�̊J��
		if (g_pVtxBuffPauseSelect != NULL)
		{
			g_pVtxBuffPauseSelect->Release();
			g_pVtxBuffPauseSelect = NULL;
		}
	
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePauseSelect(void)
{
	// ���_���̍쐬
	VERTEX_2D *pVtx;
	FADE fade;
	fade = GetFade();
	JoyState pJoyState = GetJoystate();
	XINPUT_STATE state;
	XInputGetState(0, &state);
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPauseSelect->Lock(0, 0, (void**)&pVtx, 0);

	if (GetKeyboardTrigger(DIK_DOWN) == true && fade == FADE_NONE || (state.Gamepad.sThumbLY <= -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && pJoyState.bConnectionJoypad == true) && fade == FADE_NONE)
	{
		if (g_JoyStatePause.nJoypadState == INPUT_JOYSTATE_NOTPUSH)
		{
			PlaySound(SOUND_LABEL_SE_SELECT);
			g_aPauseMenu[g_nSelect].select = SELECTTYPE_NONE;
			g_nSelect = (g_nSelect + 1) % 3;
			g_aPauseMenu[g_nSelect].select = SELECTTYPE_SELECT;
		}

		g_JoyStatePause.nJoypadState = INPUT_JOYSTATE_PUSH;
	}
	if (GetKeyboardTrigger(DIK_UP) == true && fade == FADE_NONE || (state.Gamepad.sThumbLY >= XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && pJoyState.bConnectionJoypad == true) && fade == FADE_NONE)
	{
		if (g_JoyStatePause.nJoypadState == INPUT_JOYSTATE_NOTPUSH)
		{
			PlaySound(SOUND_LABEL_SE_SELECT);
			g_aPauseMenu[g_nSelect].select = SELECTTYPE_NONE;
			g_nSelect = (g_nSelect + 2) % 3;
			g_aPauseMenu[g_nSelect].select = SELECTTYPE_SELECT;
		}

		g_JoyStatePause.nJoypadState = INPUT_JOYSTATE_PUSH;
	}
	if (GetKeyboardTrigger(DIK_S) == true && fade == FADE_NONE || (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN  && pJoyState.bConnectionJoypad == true) && fade == FADE_NONE)
	{
		if (g_JoyStatePause.nJoypadState == INPUT_JOYSTATE_NOTPUSH)
		{
			PlaySound(SOUND_LABEL_SE_SELECT);
			g_aPauseMenu[g_nSelect].select = SELECTTYPE_NONE;
			g_nSelect = (g_nSelect + 1) % 3;
			g_aPauseMenu[g_nSelect].select = SELECTTYPE_SELECT;
		}
		g_JoyStatePause.nJoypadState = INPUT_JOYSTATE_PUSH;
	}
	if (GetKeyboardTrigger(DIK_W) == true && fade == FADE_NONE || (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP  && pJoyState.bConnectionJoypad == true) && fade == FADE_NONE)
	{
		if (g_JoyStatePause.nJoypadState == INPUT_JOYSTATE_NOTPUSH)
		{
			PlaySound(SOUND_LABEL_SE_SELECT);
			g_aPauseMenu[g_nSelect].select = SELECTTYPE_NONE;
			g_nSelect = (g_nSelect + 2) % 3;
			g_aPauseMenu[g_nSelect].select = SELECTTYPE_SELECT;
		}
		g_JoyStatePause.nJoypadState = INPUT_JOYSTATE_PUSH;
	}


	//�G���^�[�L�[
	if (GetKeyboardTrigger(DIK_RETURN) == true && fade == FADE_NONE || (state.Gamepad.wButtons & XINPUT_GAMEPAD_B  && pJoyState.bConnectionJoypad == true) && fade == FADE_NONE)
	{
		if (g_JoyStatePause.nJoypadState == INPUT_JOYSTATE_NOTPUSH)
		{
			if (g_nSelect == 0)
			{
				PlaySound(SOUND_LABEL_SE_CANCEL);
				g_SelectMode = SELECTMODE_CONTINUE;
			}
			else if (g_nSelect == 1)
			{
				PlaySound(SOUND_LABEL_SE_DECIDE);
				g_SelectMode = SELECTMODE_RETRY;
			}
			else if (g_nSelect == 2)
			{
				PlaySound(SOUND_LABEL_SE_DECIDE);
				g_SelectMode = SELECTMODE_QUIT;
			}
		}

		g_JoyStatePause.nJoypadState = INPUT_JOYSTATE_PUSH;

		switch (g_SelectMode)
		{
		case SELECTMODE_CONTINUE:
		{
			break;
		}
		case SELECTMODE_RETRY:
		{
			SetFade(MODE_GAME);
			break;
		}
		case SELECTMODE_QUIT:
		{
			SetFade(MODE_TITLE);
			break;
		}
		}
	}

	if (GetKeyboardTrigger(DIK_P) == true || (state.Gamepad.wButtons & XINPUT_GAMEPAD_A  && pJoyState.bConnectionJoypad == true) && fade == FADE_NONE)
	{
		if (g_JoyStatePause.nJoypadState == INPUT_JOYSTATE_NOTPUSH)
		{
			g_nSelect = 0;
			g_aPauseMenu[g_nSelect].select = SELECTTYPE_SELECT;
			g_aPauseMenu[1].select = SELECTTYPE_NONE;
			g_aPauseMenu[2].select = SELECTTYPE_NONE;
		}

		g_JoyStatePause.nJoypadState = INPUT_JOYSTATE_PUSH;
	}

	for (int nCnt = 0; nCnt < MAX_PAUSEMENU; nCnt++)
	{
		if (g_aPauseMenu[nCnt].select == SELECTTYPE_SELECT)
		{//�I�𒆂̐F	
			g_aPauseMenu[nCnt].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		}
		else
		{//���I���̐F
			g_aPauseMenu[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
		//���_�J���[
		pVtx[0].col = g_aPauseMenu[nCnt].col;
		pVtx[1].col = g_aPauseMenu[nCnt].col;
		pVtx[2].col = g_aPauseMenu[nCnt].col;
		pVtx[3].col = g_aPauseMenu[nCnt].col;
		pVtx += 4;
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPauseSelect->Unlock();

	//�W���C�p�b�h�̏�ԍX�V
	if (g_JoyStatePause.nJoypadState == INPUT_JOYSTATE_PUSH)
	{
		g_JoyStatePause.nJoypadState = INPUT_JOYSTATE_NONE;
	}
	else if (g_JoyStatePause.nJoypadState == INPUT_JOYSTATE_NONE)
	{
		g_JoyStatePause.nJoypadState = INPUT_JOYSTATE_NOTPUSH;
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPauseSelect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCnt;

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPauseSelect, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCnt = 0; nCnt < MAX_PAUSEMENU; nCnt++)
	{
		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTexturePauseSelect[nCnt]);

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			0 + (4 * nCnt),	//�J�n���钸�_�̃C���f�b�N�X
			2); //�`�悷��v���~�e�B�u��
	}
	
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexPauseSelect(LPDIRECT3DDEVICE9 pDevice)
{
	// ���_���̍쐬
	VERTEX_2D *pVtx;
	int nCnt;

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_PAUSEMENU,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPauseSelect,
		NULL);

	//���_����ݒ�
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPauseSelect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCnt = 0; nCnt < MAX_PAUSEMENU; nCnt++)
	{
		//���_���W
		pVtx[0].pos = D3DXVECTOR3(g_aPauseMenu[nCnt].pos.x - PAUSESELECT_POS_X, g_aPauseMenu[nCnt].pos.y - PAUSESELECT_POS_Y, g_aPauseMenu[nCnt].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_aPauseMenu[nCnt].pos.x + PAUSESELECT_POS_X, g_aPauseMenu[nCnt].pos.y - PAUSESELECT_POS_Y, g_aPauseMenu[nCnt].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_aPauseMenu[nCnt].pos.x - PAUSESELECT_POS_X, g_aPauseMenu[nCnt].pos.y + PAUSESELECT_POS_Y, g_aPauseMenu[nCnt].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_aPauseMenu[nCnt].pos.x + PAUSESELECT_POS_X, g_aPauseMenu[nCnt].pos.y + PAUSESELECT_POS_Y, g_aPauseMenu[nCnt].pos.z);
		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(TEX_LEFT, TEX_TOP);
		pVtx[1].tex = D3DXVECTOR2(TEX_RIGHT, TEX_TOP);
		pVtx[2].tex = D3DXVECTOR2(TEX_LEFT, TEX_BOT);
		pVtx[3].tex = D3DXVECTOR2(TEX_RIGHT, TEX_BOT);
		//���_
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		//���_�J���[
		pVtx[0].col = g_aPauseMenu[g_nSelect].col;
		pVtx[1].col = g_aPauseMenu[g_nSelect].col;
		pVtx[2].col = g_aPauseMenu[g_nSelect].col;
		pVtx[3].col = g_aPauseMenu[g_nSelect].col;

		pVtx += 4;	//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPauseSelect->Unlock();
}

//=============================================================================
// �|�[�Y�̐ݒ�
//=============================================================================
void SetPauseSelect(D3DXVECTOR3 pos, D3DXCOLOR col)
{
	int nCnt;
	float fMenuPosY = 0;
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^
					//���_����ݒ�
					//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPauseSelect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCnt = 0; nCnt < MAX_PAUSEMENU; nCnt++)
	{
		//���_���W
		pVtx[0].pos = D3DXVECTOR3(g_aPauseMenu[nCnt].pos.x - PAUSESELECT_POS_X, g_aPauseMenu[nCnt].pos.y - PAUSESELECT_POS_Y, g_aPauseMenu[nCnt].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_aPauseMenu[nCnt].pos.x + PAUSESELECT_POS_X, g_aPauseMenu[nCnt].pos.y - PAUSESELECT_POS_Y, g_aPauseMenu[nCnt].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_aPauseMenu[nCnt].pos.x - PAUSESELECT_POS_X, g_aPauseMenu[nCnt].pos.y + PAUSESELECT_POS_Y, g_aPauseMenu[nCnt].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_aPauseMenu[nCnt].pos.x + PAUSESELECT_POS_X, g_aPauseMenu[nCnt].pos.y + PAUSESELECT_POS_Y, g_aPauseMenu[nCnt].pos.z);
		g_aPauseMenu[nCnt].pos = pos;
		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(TEX_LEFT, TEX_TOP);
		pVtx[1].tex = D3DXVECTOR2(TEX_RIGHT, TEX_TOP);
		pVtx[2].tex = D3DXVECTOR2(TEX_LEFT, TEX_BOT);
		pVtx[3].tex = D3DXVECTOR2(TEX_RIGHT, TEX_BOT);
		//���_
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		g_aPauseMenu[nCnt].col = col;
	
		fMenuPosY += 100;

		pVtx += 4;	//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPauseSelect->Unlock();
}

//=============================================================================
// �Z���N�g���[�h�̎擾
//=============================================================================
SELECTMODE *GetPauseMode(void)
{
	return &g_SelectMode;
}