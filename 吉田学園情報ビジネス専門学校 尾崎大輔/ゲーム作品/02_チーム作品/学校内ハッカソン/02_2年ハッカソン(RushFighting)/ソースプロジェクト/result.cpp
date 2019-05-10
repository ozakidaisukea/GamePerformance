//=============================================================================
//
// ���ʉ�ʏ��� [result.cpp]
// Author : Niwa Hodaka
//
//=============================================================================
#include "result.h"
#include "fade.h"
#include "input.h"
#include "sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define RESULT_PLAYER1			"data\\TEXTURE\\result00.png"	// �Q�[���I�[�o�[�e�N�X�`��
#define RESULT_PLAYER2			"data\\TEXTURE\\result01.png"	// �Q�[���N���A�e�N�X�`��
#define RESULT_POS_X			(0)								// �w�i�̍���X���W
#define RESULT_POS_Y			(0)								// �w�i�̍���Y���W
#define RESULT_WIDTH			(SCREEN_WIDTH)					// �w�i�̕�
#define RESULT_HEIGHT			(SCREEN_HEIGHT)					// �w�i�̍���

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
RESULT g_result = RESULT_PLAYER2_WIN;								// ���ʉ�ʂ�؂�ւ���ϐ�
int    g_nCounterResult;											// �^�C�g����ʂɑJ�ڂ���^�C�~���O
LPDIRECT3DTEXTURE9  g_pTextureResult[2] = {};						// �e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;					// ���_�o�b�t�@�ւ̃|�C���^

//=============================================================================
// ����������
//=============================================================================
void InitResult(void)
{
	g_nCounterResult = 0;		// �J�E���^�[��0��

	LPDIRECT3DDEVICE9 pDevice;	// �f�o�C�X�ւ̃|�C���^

								// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		RESULT_PLAYER1,
		&g_pTextureResult[0]);
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		RESULT_PLAYER2,
		&g_pTextureResult[1]);

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,	// �m�ۂ���o�b�t�@�̃T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,			// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffResult,
		NULL);

	VERTEX_2D *pVtx;	// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntResult = 0; nCntResult < 2; nCntResult++)
	{
		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(RESULT_POS_X, RESULT_POS_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(RESULT_WIDTH, RESULT_POS_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(RESULT_POS_X, RESULT_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(RESULT_WIDTH, RESULT_HEIGHT, 0.0f);

		// rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// ���_�J���[
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}
	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffResult->Unlock();
}
//=============================================================================
// �I������
//=============================================================================
void UninitResult(void)
{
	int nCntResult;

	for (nCntResult = 0; nCntResult < 2; nCntResult++)
	{
		// �e�N�X�`���̔j��
		if (g_pTextureResult[nCntResult] != NULL)
		{
			g_pTextureResult[nCntResult]->Release();
			g_pTextureResult[nCntResult] = NULL;
		}
	}
	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffResult != NULL)
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}
}
//=============================================================================
// �X�V����
//=============================================================================
void UpdateResult(void)
{
	FADE fade;
	g_nCounterResult++;

	fade = GetFade();
	if (GetFade() == FADE_NONE)
	{// �t�F�[�h��Ԃł͂Ȃ�
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{// ��ʑJ��
			SetFade(MODE_TITLE);
		}

		for (int nCntPad = 0; nCntPad < 2; nCntPad++)
		{
			for (int nCntButton = XIJS_BUTTON_4; nCntButton < XIJS_BUTTON_16; nCntButton++)
			{// ��������{�^�����̐������J��Ԃ�
				if (GetXInputTrigger(nCntPad, (XIJS_BUTTON)nCntButton) == TRUE)
				{
					SetFade(MODE_TITLE);
				}
			}
		}
	}
}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawResult(void)
{
	LPDIRECT3DDEVICE9	pDevice;	// �f�o�C�X�ւ̃|�C���^

	// �f�o�C�X���擾����
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffResult, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureResult[g_result]);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
//=============================================================================
// �ݒ菈��
//=============================================================================
void SetResult(RESULT result)
{
	g_result = result;
}
//=============================================================================
// �擾����
//=============================================================================
RESULT GetResult(void)
{
	return g_result;
}