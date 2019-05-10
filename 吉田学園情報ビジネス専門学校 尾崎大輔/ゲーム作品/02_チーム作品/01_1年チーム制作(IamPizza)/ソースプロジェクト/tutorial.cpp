//=============================================================================
// 
// �`���[�g���A���̏��� [tutorial.cpp]
// Author : Mikiya Meguro
//
//=============================================================================
#include "tutorial.h"
#include "input.h"
#include "fade.h"
#include "sound.h"
#include "pressenter.h"
#include "inputx.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TUTORIAL_TEXTURENAME000		"data\\TEXTURE\\Tutorial000.jpg"	//�e�N�X�`���̃t�@�C����
#define TUTORIAL_TEXTURENAME001		"data\\TEXTURE\\Tutorial001.jpg"	//�e�N�X�`���̃t�@�C����
#define TUTORIAL_TEXTURENAME002		"data\\TEXTURE\\Tutorial002.jpg"	//�e�N�X�`���̃t�@�C����
#define TUTORIAL_X				(0)							//������WX
#define TUTORIAL_Y				(0)							//������WY	
#define TUTORIAL_WIDTH			(SCREEN_WIDTH)				//�����`�̉������W
#define TUTORIAL_HEIGHT			(SCREEN_HEIGHT)				//�����`�̏c�����W
#define MAX_TEXTURE				(3)
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureTutorial[MAX_TEXTURE] = {};		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTutorial = NULL;					//���_�o�b�t�@�ւ̃|�C���^
JoyState g_JoyStateTutorial;
TUTORIAL g_Tutorial;
//*****************************************************************************
// ������
//*****************************************************************************
void InitTutorial(void)
{	//���[�J���ϐ�
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	g_JoyStateTutorial.nJoypadState = INPUT_JOYSTATE_NOTPUSH;
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		TUTORIAL_TEXTURENAME000,
		&g_pTextureTutorial[0]);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		TUTORIAL_TEXTURENAME001,
		&g_pTextureTutorial[1]);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		TUTORIAL_TEXTURENAME002,
		&g_pTextureTutorial[2]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTutorial,
		NULL);

	//���_�o�b�t�@�����b�N�����_�f�[�^�̃|�C���^���擾
	g_pVtxBuffTutorial->Lock(0, 0, (void**)&pVtx, 0);
	//���_���W
	pVtx[0].pos = D3DXVECTOR3(TUTORIAL_X, TUTORIAL_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(TUTORIAL_WIDTH, TUTORIAL_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(TUTORIAL_X, TUTORIAL_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(TUTORIAL_WIDTH, TUTORIAL_HEIGHT, 0.0f);
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
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTutorial->Unlock();
	//������
	g_Tutorial.bUse = true;
	g_Tutorial.nType = 0;

	//�v���X�G���^�[
	InitPressEnter();
	SetPressEnter(D3DXVECTOR3(SCREEN_WIDTH / 2, 420.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 200.0f, 50.0f);

}
//=============================================================================
// �I������
//=============================================================================
void UninitTutorial(void)
{	//�e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < MAX_TEXTURE; nCnt++)
	{
		if (g_pTextureTutorial[nCnt] != NULL)
		{
			g_pTextureTutorial[nCnt]->Release();
			g_pTextureTutorial[nCnt] = NULL;
		}
	}
	//���_�o�b�t�@�̔j���̔j��
	if (g_pVtxBuffTutorial != NULL)
	{
		g_pVtxBuffTutorial->Release();
		g_pVtxBuffTutorial = NULL;
	}

	UninitPressEnter();
}
//=============================================================================
// �X�V����
//=============================================================================
void UpdateTutorial(void)
{
	FADE fade;
	fade = GetFade();
	JoyState pJoyState = GetJoystate();
	XINPUT_STATE state;
	XInputGetState(0, &state);

	//�G���^�[�L�[ ��ɐi��
	if (GetKeyboardTrigger(DIK_RETURN) == true && fade == FADE_NONE || GetKeyboardTrigger(DIK_RIGHT) == true && fade == FADE_NONE
		//|| (state.Gamepad.wButtons & XINPUT_GAMEPAD_B  && pJoyState.bConnectionJoypad == true) && fade == FADE_NONE
		|| (state.Gamepad.wButtons & XINPUT_GAMEPAD_A  && pJoyState.bConnectionJoypad == true) && fade == FADE_NONE 
		|| (state.Gamepad.wButtons & XINPUT_GAMEPAD_Y  && pJoyState.bConnectionJoypad == true)
		|| (state.Gamepad.wButtons & XINPUT_GAMEPAD_X  && pJoyState.bConnectionJoypad == true))
	{
		if (g_JoyStateTutorial.nJoypadState == INPUT_JOYSTATE_NOTPUSH)
		{
			//�G���^�[�L�[
			if (GetKeyboardTrigger(DIK_RETURN) == true || GetKeyboardTrigger(DIK_RIGHT) == true 
				//|| (state.Gamepad.wButtons & XINPUT_GAMEPAD_B  && pJoyState.bConnectionJoypad == true) 
				|| (state.Gamepad.wButtons & XINPUT_GAMEPAD_A  && pJoyState.bConnectionJoypad == true)
				|| (state.Gamepad.wButtons & XINPUT_GAMEPAD_X  && pJoyState.bConnectionJoypad == true) 
				|| (state.Gamepad.wButtons & XINPUT_GAMEPAD_Y  && pJoyState.bConnectionJoypad == true))
			{
				
				if (g_Tutorial.nType < MAX_TEXTURE - 1)
				{
					g_Tutorial.nType++;
				}
				else
				{
					PlaySound(SOUND_LABEL_SE_KLAXON1);
					SetFade(MODE_GAME);
				}
			}
		}

		g_JoyStateTutorial.nJoypadState = INPUT_JOYSTATE_PUSH;
	}
	//�O�ɖ߂�
	if (GetKeyboardTrigger(DIK_LEFT) == true && fade == FADE_NONE 
		|| (state.Gamepad.wButtons & XINPUT_GAMEPAD_B  && pJoyState.bConnectionJoypad == true) && fade == FADE_NONE)
	{
		if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_B  && pJoyState.bConnectionJoypad == true) || GetKeyboardTrigger(DIK_LEFT) == true)
		{
			
				if (g_Tutorial.nType > 0)
				{
					g_Tutorial.nType--;
				}
			
		}
		g_JoyStateTutorial.nJoypadState = INPUT_JOYSTATE_PUSH;
	}
	UpdatePressEnter();

	//�W���C�p�b�h�̏�ԍX�V
	if (g_JoyStateTutorial.nJoypadState == INPUT_JOYSTATE_PUSH)
	{
		g_JoyStateTutorial.nJoypadState = INPUT_JOYSTATE_NONE;
	}
	else if (g_JoyStateTutorial.nJoypadState == INPUT_JOYSTATE_NONE)
	{
		g_JoyStateTutorial.nJoypadState = INPUT_JOYSTATE_NOTPUSH;
	}
}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawTutorial(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X���擾����
	pDevice = GetDevice();
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTutorial, 0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g��ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureTutorial[g_Tutorial.nType]);
	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,	//�J�n���钸�_�̃C���f�b�N�X
		2); //�`�悷��v���~�e�B�u��

	//DrawPressEnter();
}