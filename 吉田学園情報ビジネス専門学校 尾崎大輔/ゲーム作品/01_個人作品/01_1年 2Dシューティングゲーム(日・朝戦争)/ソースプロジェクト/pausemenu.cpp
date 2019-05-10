//=============================================================================
//
// �|�[�Y���j���[���� [pauseselect.cpp]
// Author : Mikiya Meguro
//
//=============================================================================
#include "input.h"
#include "fade.h"
#include "pausemenu.h"
#include "sound.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_CONTINUE		"data/TEXTURE/pause000.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_RETRY			"data/TEXTURE/pause001.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_QUIT			"data/TEXTURE/pause002.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define POLYGON_POS_X			(200)						//���_���WX�̈ړ���
#define POLYGON_POS_Y			(50)						//���_���WY�̈ړ���
#define TEX_POS_X_INIT			(1.0f)						//�e�N�X�`�����WU�̏����ʒu
#define TEX_POS_Y_INIT			(1.0f)						//�e�N�X�`�����WV�̏����ʒu
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
D3DXVECTOR3				g_PauseMenuPos(0.0f, 0.0f, 0.0f);
SELECTMODE				g_SelectMode = SELECTMODE_NONE;
int						nSelect = 0;
					
//=============================================================================
// ����������
//=============================================================================
void InitPauseSelect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	float fMenuPosY = 0;
	nSelect = 0;

	g_SelectMode = SELECTMODE_NONE;

	g_aPauseMenu[0].pos = D3DXVECTOR3(650.0f, 200.0f + (fMenuPosY), 0.0f);;
	g_aPauseMenu[0].col = D3DXCOLOR(0.0f, 0.5f, 1.0f, 1.0f);
	g_aPauseMenu[0].select = SELECTTYPE_SELECT;
	fMenuPosY += 150;
	for (int nCnt = 1; nCnt < MAX_PAUSEMENU; nCnt++)
	{
		g_aPauseMenu[nCnt].pos = D3DXVECTOR3(650.0f, 200.0f + (fMenuPosY), 0.0f);;
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


	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPauseSelect->Lock(0, 0, (void**)&pVtx, 0);

	if (GetKeyboardTrigger(DIK_DOWN) == true)
	{
		g_aPauseMenu[nSelect].select = SELECTTYPE_NONE;
		nSelect = (nSelect + 1) % 3;
		g_aPauseMenu[nSelect].select = SELECTTYPE_SELECT;
	}
	if (GetKeyboardTrigger(DIK_UP) == true)
	{
		g_aPauseMenu[nSelect].select = SELECTTYPE_NONE;
		nSelect = (nSelect + 2) % 3;
		g_aPauseMenu[nSelect].select = SELECTTYPE_SELECT;
	}

	for (int nCnt = 0; nCnt < MAX_PAUSEMENU; nCnt++)
	{
		if (g_aPauseMenu[nCnt].select == SELECTTYPE_SELECT)
		{//�I�𒆂̐F	
			g_aPauseMenu[nCnt].col = D3DXCOLOR(0.0f, 0.5f, 1.0f, 1.0f);
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




	//�G���^�[�L�[
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		if (nSelect == 0)
		{
			g_SelectMode = SELECTMODE_CONTINE;
		}
		else if (nSelect == 1)
		{
			g_SelectMode = SELECTMODE_RETRY;
		}
		else if (nSelect == 2)
		{
			g_SelectMode = SELECTMODE_QUIT;
		}

		switch (g_SelectMode)
		{
		case SELECTMODE_CONTINE:
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
			//g_SelectMode = SELECTMODE_NONE;
			//PlaySound(SOUND_LABEL_SE_DECIDE);
			
			break;
		}
		}
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
	pDevice->SetFVF(FVF_VRETEX_2D);

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
		FVF_VRETEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPauseSelect,
		NULL);

	//���_����ݒ�
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPauseSelect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCnt = 0; nCnt < MAX_PAUSEMENU; nCnt++)
	{
		//���_���W
		pVtx[0].pos = D3DXVECTOR3(g_aPauseMenu[nCnt].pos.x - POLYGON_POS_X, g_aPauseMenu[nCnt].pos.y - POLYGON_POS_Y, g_aPauseMenu[nCnt].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_aPauseMenu[nCnt].pos.x + POLYGON_POS_X, g_aPauseMenu[nCnt].pos.y - POLYGON_POS_Y, g_aPauseMenu[nCnt].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_aPauseMenu[nCnt].pos.x - POLYGON_POS_X, g_aPauseMenu[nCnt].pos.y + POLYGON_POS_Y, g_aPauseMenu[nCnt].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_aPauseMenu[nCnt].pos.x + POLYGON_POS_X, g_aPauseMenu[nCnt].pos.y + POLYGON_POS_Y, g_aPauseMenu[nCnt].pos.z);

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
		pVtx[0].col = g_aPauseMenu[nSelect].col;
		pVtx[1].col = g_aPauseMenu[nSelect].col;
		pVtx[2].col = g_aPauseMenu[nSelect].col;
		pVtx[3].col = g_aPauseMenu[nSelect].col;

		pVtx += 4;	//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPauseSelect->Unlock();
}

//=============================================================================
// �G�̐ݒ�
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
		pVtx[0].pos = D3DXVECTOR3(g_aPauseMenu[nCnt].pos.x - POLYGON_POS_X, g_aPauseMenu[nCnt].pos.y - POLYGON_POS_Y, g_aPauseMenu[nCnt].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_aPauseMenu[nCnt].pos.x + POLYGON_POS_X, g_aPauseMenu[nCnt].pos.y - POLYGON_POS_Y, g_aPauseMenu[nCnt].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_aPauseMenu[nCnt].pos.x - POLYGON_POS_X, g_aPauseMenu[nCnt].pos.y + POLYGON_POS_Y, g_aPauseMenu[nCnt].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_aPauseMenu[nCnt].pos.x + POLYGON_POS_X, g_aPauseMenu[nCnt].pos.y + POLYGON_POS_Y, g_aPauseMenu[nCnt].pos.z);
		g_aPauseMenu[nCnt].pos = pos;

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