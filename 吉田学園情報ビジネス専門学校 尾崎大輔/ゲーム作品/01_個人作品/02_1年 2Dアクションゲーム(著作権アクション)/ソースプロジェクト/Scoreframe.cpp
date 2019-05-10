//=============================================================================
//
// �X�R�A���� [scoreframe.cpp]
// Author : Ozaki
//
//=============================================================================
#include "scoreframe.h"
#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_SCORE		"data/TEXTURE/frame_score.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define MAX_MIKY			(70)

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureScoreFrame = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScoreFrame = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
int						g_nScoreFrame;						// �X�R�A
D3DXVECTOR3				g_posScoreFrame;
int						g_aScoreFrame;
//=============================================================================
// ����������
//=============================================================================
void InitScoreFrame(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �X�R�A�̏�����
	g_nScoreFrame = 0;
	g_posScoreFrame = D3DXVECTOR3(1070, 75, 0.0f);

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		TEXTURE_SCORE,		// �t�@�C���̖��O
		&g_pTextureScoreFrame);	// �e�N�X�`���ւ̃|�C���^
								//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VRETEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffScoreFrame,
		NULL);

	//���[�J���ϐ�
	VERTEX_2D*pVtx;								//���_���ւ̃|�C���^

	
	//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^�̎擾
	g_pVtxBuffScoreFrame->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_posScoreFrame.x - MAX_MIKY * 3, g_posScoreFrame.y - MAX_MIKY , g_posScoreFrame.z);
	pVtx[1].pos = D3DXVECTOR3(g_posScoreFrame.x + MAX_MIKY * 3, g_posScoreFrame.y - MAX_MIKY , g_posScoreFrame.z);
	pVtx[2].pos = D3DXVECTOR3(g_posScoreFrame.x - MAX_MIKY * 3, g_posScoreFrame.y + MAX_MIKY / 2, g_posScoreFrame.z);
	pVtx[3].pos = D3DXVECTOR3(g_posScoreFrame.x + MAX_MIKY * 3, g_posScoreFrame.y + MAX_MIKY / 2, g_posScoreFrame.z);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2( 0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2( 1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2( 0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2( 1.0f, 1.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 0, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 0, 255);
	pVtx[2].col = D3DCOLOR_RGBA(0, 255, 0, 255);
	pVtx[3].col = D3DCOLOR_RGBA(0, 255, 255, 255);

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffScoreFrame->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void UninitScoreFrame(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureScoreFrame != NULL)
	{
		g_pTextureScoreFrame->Release();
		g_pTextureScoreFrame = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffScoreFrame != NULL)
	{
		g_pVtxBuffScoreFrame->Release();
		g_pVtxBuffScoreFrame = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateScoreFrame(void)
{

}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawScoreFrame(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffScoreFrame, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VRETEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureScoreFrame);

	// �|���S���̕`��

		//�|���S���̔j��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			0,
			2);	
}