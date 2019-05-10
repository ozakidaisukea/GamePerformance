//=============================================================================
//
// �u���[�̏��� [gauge.cpp]
// Author : Meguro Mikiya
//
//=============================================================================
#include "blur.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_GAUGE000		"data/TEXTURE/�W��1.jpg"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define TEXTURE_GAUGE001		"data/TEXTURE/�W��2.jpg"		// �ǂݍ��ރe�N�X�`���t�F�C����
#define TEXTURE_GAUGE002		"data/TEXTURE/�W��2.jpg"		// �ǂݍ��ރe�N�X�`���t�F�C����
#define TEXTURE_GAUGE003		"data/TEXTURE/�W��2.jpg"			// �ǂݍ��ރe�N�X�`���t�F�C����
#define MAX_GAUGE				(3)									// �Q�[�W�̍ő吔	
#define REDUCE_GAUGE			(0.12f)								// �Q�[�W�̌����(���t���[��)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexBlur(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureBlur[MAX_GAUGE] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBlur = NULL;				// ���_�o�b�t�@�ւ̃|�C���^
int nCouter;
float fAlpha1;
float fAlpha2;
float fAlpha3;
//=============================================================================
// ����������
//=============================================================================
void InitBlur(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_GAUGE000, &g_pTextureBlur[0]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_GAUGE001, &g_pTextureBlur[1]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_GAUGE002, &g_pTextureBlur[2]);
	//D3DXCreateTextureFromFile(pDevice, TEXTURE_GAUGE003, &g_pTextureBlur[3]);

	// ���_���̍쐬
	MakeVertexBlur(pDevice);

	fAlpha1 = 0;
	fAlpha2 = 0;
	fAlpha3 = 0;
}

//=============================================================================
// �I������
//=============================================================================
void UninitBlur(void)
{
	for (int nCntBlur = 0; nCntBlur < MAX_GAUGE; nCntBlur++)
	{
		// �e�N�X�`���̊J��
		if (g_pTextureBlur[nCntBlur] != NULL)
		{
			g_pTextureBlur[nCntBlur]->Release();
			g_pTextureBlur[nCntBlur] = NULL;
		}
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffBlur != NULL)
	{
		g_pVtxBuffBlur->Release();
		g_pVtxBuffBlur = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBlur(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBlur(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBlur, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �|���S���̕`��
	for (int nCntBlur = 0; nCntBlur < MAX_GAUGE; nCntBlur++)
	{// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureBlur[nCntBlur]);
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBlur * 4, 2);
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexBlur(LPDIRECT3DDEVICE9 pDevice)
{

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_GAUGE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBlur,
		NULL);

	// ���_���̍쐬
	VERTEX_2D*pVtx;			//���_���ւ̃|�C���^

							//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBlur->Lock(0, 0, (void**)&pVtx, 0);
	
	for (int nCntGauge = 0; nCntGauge < MAX_GAUGE; nCntGauge++)
	{
		if (nCntGauge == 0)
		{	// �Q�[�W
			//���_���W
			pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_WIDTH, 0.0f);

			//���_�J���[�ݒ�
			pVtx[0].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.7f);
			pVtx[1].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.7f);
			pVtx[2].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.7f);
			pVtx[3].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.7f);
		}
		else if (nCntGauge == 1)
		{	// �d�r
			//���_���W
			pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_WIDTH, 0.0f);

			//���_�J���[�ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);
		}
		else if (nCntGauge == 2)
		{	// �o�b�e���[������
			//���_���W
			pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_WIDTH, 0.0f);

			//���_�J���[�ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}

		//1.0f�ŌŒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//�e�N�X�`���ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;	//���_�f�[�^�̃|�C���^���S���i�߂�
	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffBlur->Unlock();
}
