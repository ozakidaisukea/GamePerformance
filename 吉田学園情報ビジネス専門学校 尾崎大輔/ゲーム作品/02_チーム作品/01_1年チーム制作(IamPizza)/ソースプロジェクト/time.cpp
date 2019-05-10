//=============================================================================
//
// �^�C������ [time.cpp]
// Author : Mikiya Meguro
//
//=============================================================================
#include "time.h"
#include "game.h"
#include "tutorial.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_SCORE		"data/TEXTURE/number001.png"		// �ǂݍ��ރe�N�X�`���t�@�C����
#define TIME_POS_X				(20)							//���_���WX�̈ړ���
#define TIME_POS_Y				(20)							//���_���WY�̈ړ���
#define TEX_LEFT				(0.0f)							//�e�N�X�`�����WU��
#define TEX_RIGHT				(1.0f)							//�e�N�X�`�����WU�E
#define TEX_TOP					(0.0f)							//�e�N�X�`�����WV��
#define TEX_BOT					(1.0f)							//�e�N�X�`�����WV��
#define MAX_TIME				(3)								//�^�C���̌���
#define TIME_NUM				(180)							//�^�C��
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexTime(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureTime = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTime = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
TIME					g_Time;
//=============================================================================
// ����������
//=============================================================================
void InitTime(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	

	// �^�C���̏�����
	g_Time.nTime = TIME_NUM;
	g_Time.bTimerStop = true;
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
								TEXTURE_SCORE,		// �t�@�C���̖��O
								&g_pTextureTime);	// �e�N�X�`���ւ̃|�C���^

	// ���_���̍쐬
	MakeVertexTime(pDevice);
	
}

//=============================================================================
// �I������
//=============================================================================
void UninitTime(void)
{
	// �e�N�X�`���̊J��
		if (g_pTextureTime != NULL)
		{
			g_pTextureTime->Release();
			g_pTextureTime = NULL;
		}
	
	// ���_�o�b�t�@�̊J��
		if (g_pVtxBuffTime != NULL)
		{
			g_pVtxBuffTime->Release();
			g_pVtxBuffTime = NULL;
		}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateTime(void)
{

	// ���_���̍쐬
	VERTEX_2D *pVtx;

	//�Q�[���X�e�C�g�̎擾
	GAMESTATE GameState;
	GameState = GetGameState();

	int nCntTime;
	int nPosMove = 0;
	int nAnswer = 0;
	int nTime = 1;
	g_Time.TimePos.x = 680;
	g_Time.TimePos.y = 52.0f;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	if (g_Time.bTimerStop == true)
	{
		g_Time.nTimeCounter++;
		if (g_Time.nTimeCounter >= 60)
		{
			g_Time.nTimeCounter = 0;
			g_Time.nTime -= 1;
		}
	}
	else if (g_Time.bTimerStop == false)
	{
	/*	g_nTimeCounter++;
		if (g_nTimeCounter >= 70)
		{*/
			//SetGameState(GAMESTATE_END);
		//	g_nTimeCounter = 0;
		//}
	}



	if (g_Time.nTime >= 0)
	{
		for (nCntTime = 0; nCntTime < MAX_TIME; nCntTime++)
		{

			nAnswer = g_Time.nTime % (nTime * 10) / nTime;

			//���_���W
			pVtx[0].pos = D3DXVECTOR3(g_Time.TimePos.x - TIME_POS_X, g_Time.TimePos.y - TIME_POS_Y, g_Time.TimePos.z);
			pVtx[1].pos = D3DXVECTOR3(g_Time.TimePos.x + TIME_POS_X, g_Time.TimePos.y - TIME_POS_Y, g_Time.TimePos.z);
			pVtx[2].pos = D3DXVECTOR3(g_Time.TimePos.x - TIME_POS_X, g_Time.TimePos.y + TIME_POS_Y, g_Time.TimePos.z);
			pVtx[3].pos = D3DXVECTOR3(g_Time.TimePos.x + TIME_POS_X, g_Time.TimePos.y + TIME_POS_Y, g_Time.TimePos.z);

			//�e�N�X�`�����W
			pVtx[0].tex = D3DXVECTOR2(0.0f + (nAnswer * 0.1f), 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f + (nAnswer * 0.1f), 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f + (nAnswer * 0.1f), 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f + (nAnswer * 0.1f), 1.0f);

			//���_
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			//���_�J���[
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
			
			if (g_Time.nTime <= 10)
			{
				//���_�J���[
				pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			}

			pVtx += 4;	//���_�f�[�^�̃|�C���^��4���i�߂�
			nTime *= 10;
			g_Time.TimePos.x -= 40;
		}		
	}
	if (g_Time.nTime == 0)
	{
		if (GameState != GAMESTATE_GAMEOVER)
		{
			SetGameState(GAMESTATE_GAMEOVER);
		}
		//g_nTime = 60;
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTime->Unlock();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawTime(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCntScore;

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
    pDevice->SetStreamSource(0, g_pVtxBuffTime, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureTime);

	// �|���S���̕`��

	for (nCntScore = 0; nCntScore < MAX_TIME; nCntScore++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			0 + (4 * nCntScore),	//�J�n���钸�_�̃C���f�b�N�X
			2); //�`�悷��v���~�e�B�u��
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexTime(LPDIRECT3DDEVICE9 pDevice)
{	
	// ���_���̍쐬
	VERTEX_2D *pVtx;
	int nCntScore;
	int nPosMove = 0;
	g_Time.TimePos.x = SCREEN_WIDTH / 2;
	g_Time.TimePos.y = 52.0f;

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TIME,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTime,
		NULL);

	//���_����ݒ�
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntScore = 0; nCntScore  < MAX_TIME; nCntScore++)
	{
	//���_���W
			pVtx[0].pos = D3DXVECTOR3(g_Time.TimePos.x - TIME_POS_X, g_Time.TimePos.y - TIME_POS_Y, g_Time.TimePos.z);
			pVtx[1].pos = D3DXVECTOR3(g_Time.TimePos.x + TIME_POS_X, g_Time.TimePos.y - TIME_POS_Y, g_Time.TimePos.z);
			pVtx[2].pos = D3DXVECTOR3(g_Time.TimePos.x - TIME_POS_X, g_Time.TimePos.y + TIME_POS_Y, g_Time.TimePos.z);
			pVtx[3].pos = D3DXVECTOR3(g_Time.TimePos.x + TIME_POS_X, g_Time.TimePos.y + TIME_POS_Y, g_Time.TimePos.z);
		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		//���_
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);

		pVtx += 4;	//���_�f�[�^�̃|�C���^��4���i�߂�
		g_Time.TimePos.x -= 40;
	}
	 //���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTime->Unlock();
}

//=============================================================================
// �^�C���̉��Z
//=============================================================================
void AddTime(int nValue)
{
	// ���_���̍쐬
	VERTEX_2D *pVtx;
	int nCntTime;
	int nPosMove = 0;
	int nAnswer = 0;
	int nTime = 1;
	g_Time.TimePos.x = SCREEN_WIDTH / 2;
	g_Time.TimePos.y = 60.0f;

	g_Time.nTime += nValue;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntTime = 0; nCntTime < MAX_TIME; nCntTime++)
	{
		nAnswer = g_Time.nTime % (nTime * 10) / nTime;

		//���_���W
		pVtx[0].pos = D3DXVECTOR3(g_Time.TimePos.x - TIME_POS_X, g_Time.TimePos.y - TIME_POS_Y, g_Time.TimePos.z);
		pVtx[1].pos = D3DXVECTOR3(g_Time.TimePos.x + TIME_POS_X, g_Time.TimePos.y - TIME_POS_Y, g_Time.TimePos.z);
		pVtx[2].pos = D3DXVECTOR3(g_Time.TimePos.x - TIME_POS_X, g_Time.TimePos.y + TIME_POS_Y, g_Time.TimePos.z);
		pVtx[3].pos = D3DXVECTOR3(g_Time.TimePos.x + TIME_POS_X, g_Time.TimePos.y + TIME_POS_Y, g_Time.TimePos.z);
		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f + (nAnswer * 0.1f), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + (nAnswer * 0.1f), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (nAnswer * 0.1f), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + (nAnswer * 0.1f), 1.0f);

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

		pVtx += 4;	//���_�f�[�^�̃|�C���^��4���i�߂�
		nTime *= 10;
		g_Time.TimePos.x -= 40;
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTime->Unlock();
}
//=============================================================================
// �^�C���̎擾
//=============================================================================
TIME *GetTime(void)
{
	return &g_Time;
}