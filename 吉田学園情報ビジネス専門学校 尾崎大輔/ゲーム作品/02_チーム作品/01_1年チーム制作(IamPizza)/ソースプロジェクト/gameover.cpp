//=============================================================================
// 
// �Q�[���I�[�o�[�̏��� [gameover.cpp]
// Author : Mikiya Meguro
//
//=============================================================================
#include "gameover.h"
#include "input.h"
#include "fade.h"
#include "gameoverlogo.h"
#include "player.h"
#include "inputx.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define GAMEOVER_TEXTURENAME		"data\\TEXTURE\\gameover000.jpg"	// �e�N�X�`���̃t�@�C����
#define GAMEOVER_TEXTURENAME001		"data\\TEXTURE\\gameover001.jpg"	// �e�N�X�`���̃t�@�C����
#define GAMEOVER_TEXTURENAME002		"data\\TEXTURE\\gameover002.png"	// �e�N�X�`���̃t�@�C����
#define POS_X						(0)								//������WX
#define POS_Y						(0)								//������WY	
#define BG_WIDTH					(SCREEN_WIDTH)					//�����`�̉������W
#define BG_HEIGHT					(SCREEN_HEIGHT)					//�����`�̏c�����W

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTexturegameover = NULL;		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffgameover = NULL;	//���_�o�b�t�@�ւ̃|�C���^
int g_nCntGameOver;
JoyState g_JoyStateGameOver;
//*****************************************************************************
// ������
//*****************************************************************************
void InitGameOver(void)
{	//���[�J���ϐ�
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	PLAYER *pPlayer = GetPlayer();
	g_JoyStateGameOver.nJoypadState = INPUT_JOYSTATE_NOTPUSH;
	if (pPlayer->state == PLAYERSTATE_EAT)
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			GAMEOVER_TEXTURENAME,
			&g_pTexturegameover);
	}
	else if (pPlayer->state == PLAYERSTATE_GAUGEZERO)
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			GAMEOVER_TEXTURENAME001,
			&g_pTexturegameover);
	}
	else
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			GAMEOVER_TEXTURENAME002,
			&g_pTexturegameover);
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffgameover,
		NULL);

	//���_�o�b�t�@�����b�N�����_�f�[�^�̃|�C���^���擾
	g_pVtxBuffgameover->Lock(0, 0, (void**)&pVtx, 0);
	//���_���W
	pVtx[0].pos = D3DXVECTOR3(POS_X, POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(BG_WIDTH, POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(POS_X, BG_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(BG_WIDTH, BG_HEIGHT, 0.0f);
	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	//���_
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//���_�J���[
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffgameover->Unlock();
	//�J�E���g���Z�b�g
	g_nCntGameOver = 0;

	InitGameoverLogo();
}
//=============================================================================
// �I������
//=============================================================================
void UninitGameOver(void)
{	//�e�N�X�`���̔j��
	if (g_pTexturegameover != NULL)
	{
		g_pTexturegameover->Release();
		g_pTexturegameover = NULL;
	}
	//���_�o�b�t�@�̔j���̔j��
	if (g_pVtxBuffgameover != NULL)
	{
		g_pVtxBuffgameover->Release();
		g_pVtxBuffgameover = NULL;
	}

	UninitGameoverLogo();
}
//=============================================================================
// �X�V����
//=============================================================================
void UpdateGameOver(void)
{
	JoyState pJoyState = GetJoystate();
	XINPUT_STATE state;
	XInputGetState(0, &state);

	//�G���^�[�L�[
	if (GetKeyboardTrigger(DIK_RETURN) == true || (state.Gamepad.wButtons & XINPUT_GAMEPAD_B  && pJoyState.bConnectionJoypad == true) || (state.Gamepad.wButtons & XINPUT_GAMEPAD_A  && pJoyState.bConnectionJoypad == true)
		|| (state.Gamepad.wButtons & XINPUT_GAMEPAD_X  && pJoyState.bConnectionJoypad == true) || (state.Gamepad.wButtons & XINPUT_GAMEPAD_Y  && pJoyState.bConnectionJoypad == true))
	{
		if (g_JoyStateGameOver.nJoypadState == INPUT_JOYSTATE_NOTPUSH)
		{
			SetFade(MODE_TITLE);
		}

		g_JoyStateGameOver.nJoypadState = INPUT_JOYSTATE_PUSH;
	}
	g_nCntGameOver++;
	if (g_nCntGameOver >= 600)
	{
		SetFade(MODE_TITLE);
	}

	//�W���C�p�b�h�̏�ԍX�V
	if (g_JoyStateGameOver.nJoypadState == INPUT_JOYSTATE_PUSH)
	{
		g_JoyStateGameOver.nJoypadState = INPUT_JOYSTATE_NONE;
	}
	else if (g_JoyStateGameOver.nJoypadState == INPUT_JOYSTATE_NONE)
	{
		g_JoyStateGameOver.nJoypadState = INPUT_JOYSTATE_NOTPUSH;
	}
}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawGameOver(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X���擾����
	pDevice = GetDevice();
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffgameover, 0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g��ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturegameover);
	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,	//�J�n���钸�_�̃C���f�b�N�X
		2); //�`�悷��v���~�e�B�u��

	DrawGameoverLogo();
}