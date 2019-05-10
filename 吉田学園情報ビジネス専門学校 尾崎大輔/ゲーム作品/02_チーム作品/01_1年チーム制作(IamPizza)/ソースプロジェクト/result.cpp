//=============================================================================
// 
// ���U���g�̏��� [result.cpp]
// Author : Mikiya Meguro
//
//=============================================================================
#include "result.h"
#include "input.h"
#include "fade.h"
//#include "score.h"
//#include "time.h"
#include "resultlogo.h"
#include "inputx.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TITLE_TEXTURENAME		"data\\TEXTURE\\Gameclear.jpg"	//�e�N�X�`���̃t�@�C����
#define RESULT_POS_X				(0)							//������WX
#define RESULT_POS_Y				(0)							//������WY	
#define RESULT_WIDTH			(SCREEN_WIDTH)				//�����`�̉������W
#define RESULT_HEIGHT			(SCREEN_HEIGHT)				//�����`�̏c�����W

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureResult = NULL;		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;	//���_�o�b�t�@�ւ̃|�C���^
int g_nCounterGameClear;
JoyState g_JoyStateResult;
//*****************************************************************************
// ������
//*****************************************************************************
void InitResult(void)
{	//���[�J���ϐ�	
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;
	
	g_nCounterGameClear = 0;
	g_JoyStateResult.nJoypadState = INPUT_JOYSTATE_NOTPUSH;
	pDevice = GetDevice();
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		TITLE_TEXTURENAME,
		&g_pTextureResult);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResult,
		NULL);

	//���_�o�b�t�@�����b�N�����_�f�[�^�̃|�C���^���擾
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);
	//���_���W
	pVtx[0].pos = D3DXVECTOR3(RESULT_POS_X, RESULT_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(RESULT_WIDTH, RESULT_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(RESULT_POS_X, RESULT_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(RESULT_WIDTH, RESULT_HEIGHT, 0.0f);
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
	g_pVtxBuffResult->Unlock();
	//�J�E���g���Z�b�g
	g_nCounterGameClear = 0;

	InitResultLogo();

}
//=============================================================================
// �I������
//=============================================================================
void UninitResult(void)
{	//�e�N�X�`���̔j��
	if (g_pTextureResult != NULL)
	{
		g_pTextureResult->Release();
		g_pTextureResult = NULL;
	}
	//���_�o�b�t�@�̔j���̔j��
	if (g_pVtxBuffResult != NULL)
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}

	UninitResultLogo();
}
//=============================================================================
// �X�V����
//=============================================================================
void UpdateResult(void)
{
	JoyState pJoyState = GetJoystate();
	XINPUT_STATE state;
	XInputGetState(0, &state);

	//�G���^�[�L�[
	if (GetKeyboardTrigger(DIK_RETURN) == true || (state.Gamepad.wButtons & XINPUT_GAMEPAD_B  && pJoyState.bConnectionJoypad == true) || (state.Gamepad.wButtons & XINPUT_GAMEPAD_A  && pJoyState.bConnectionJoypad == true)
		|| (state.Gamepad.wButtons & XINPUT_GAMEPAD_X  && pJoyState.bConnectionJoypad == true) || (state.Gamepad.wButtons & XINPUT_GAMEPAD_Y  && pJoyState.bConnectionJoypad == true))
	{
		if (g_JoyStateResult.nJoypadState == INPUT_JOYSTATE_NOTPUSH)
		{
			SetFade(MODE_RANKING);
		}

		g_JoyStateResult.nJoypadState = INPUT_JOYSTATE_PUSH;
	}
	g_nCounterGameClear++;
	if (g_nCounterGameClear >= 600)
	{
		SetFade(MODE_RANKING);
	}

	//�W���C�p�b�h�̏�ԍX�V
	if (g_JoyStateResult.nJoypadState == INPUT_JOYSTATE_PUSH)
	{
		g_JoyStateResult.nJoypadState = INPUT_JOYSTATE_NONE;
	}
	else if (g_JoyStateResult.nJoypadState == INPUT_JOYSTATE_NONE)
	{
		g_JoyStateResult.nJoypadState = INPUT_JOYSTATE_NOTPUSH;
	}
	UpdateResultLogo();
}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X���擾����
	pDevice = GetDevice();
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffResult, 0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g��ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureResult);
	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,	//�J�n���钸�_�̃C���f�b�N�X
		2); //�`�悷��v���~�e�B�u��

	//DrawResultLogo();

}