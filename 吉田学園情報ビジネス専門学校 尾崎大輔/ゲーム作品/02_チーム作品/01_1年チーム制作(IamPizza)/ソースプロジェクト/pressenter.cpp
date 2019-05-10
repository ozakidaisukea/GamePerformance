//=============================================================================
// ���ƍ쐬
// �w�i�̏��� [pressenter.cpp]
// Author : Mikiya Meguro
//
//=============================================================================
#include "main.h"
#include "pressenter.h"
#include "input.h"
#include "Player.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define ENTER_TEXTURENAME		"data\\TEXTURE\\enter.png"	//�e�N�X�`���̃t�@�C����
#define ENTER_X					(450)						//������WX
#define ENTER_Y					(650)						//������WY	
#define ENTER_WIDTH				(800)						//�����`�̉������W
#define ENTER_HEIGHT			(710)						//�����`�̏c�����W
#define TEX_ENTER_X_INIT		(1.0f)						//�e�N�X�`�����WU�̏����ʒu
#define TEX_ENTER_Y_INIT		(0.005f)					//�e�N�X�`�����WV�̏����ʒu
#define TEX_LEFT				(0.0f)						//�e�N�X�`�����WU��
#define TEX_RIGHT				(1.0f)						//�e�N�X�`�����WU�E
#define TEX_TOP					(0.0f)						//�e�N�X�`�����WV��
#define TEX_BOT					(1.0f)						//�e�N�X�`�����WV��
#define MAX_PRESSENTER			(1)
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTexturePressEnter = NULL;	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPressEnter = NULL;	//���_�o�b�t�@�ւ̃|�C���^
PRESSENTER	g_PressEnter[MAX_PRESSENTER];
//*****************************************************************************
// �|���S��
//*****************************************************************************
void InitPressEnter(void)
{	//���[�J���ϐ�
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	for (int nCntPressEnter = 0; nCntPressEnter < MAX_PRESSENTER; nCntPressEnter++)
	{
		g_PressEnter[nCntPressEnter].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_PressEnter[nCntPressEnter].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_PressEnter[nCntPressEnter].PressEnterCnt = 0;
		g_PressEnter[nCntPressEnter].PressEnterChange = 0;
		g_PressEnter[nCntPressEnter].bUse = false;
		g_PressEnter[nCntPressEnter].bDraw = false;
	}

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		ENTER_TEXTURENAME,
		&g_pTexturePressEnter);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPressEnter,
		NULL);

	//���_�o�b�t�@�����b�N�����_�f�[�^�̃|�C���^���擾
	g_pVtxBuffPressEnter->Lock(0, 0, (void**)&pVtx, 0);
	//���_���W
	pVtx[0].pos = D3DXVECTOR3(ENTER_X, ENTER_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(ENTER_WIDTH, ENTER_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(ENTER_X, ENTER_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(ENTER_WIDTH, ENTER_HEIGHT, 0.0f);
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
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPressEnter->Unlock();
	//���l������
	//g_PressEnterCnt = 0;
	//g_PressEnterChange = 0;
}
//=============================================================================
// �I������
//=============================================================================
void UninitPressEnter(void)
{	//�e�N�X�`���̔j��
	if (g_pTexturePressEnter != NULL)
	{
		g_pTexturePressEnter->Release();
		g_pTexturePressEnter = NULL;
	}
	//���_�o�b�t�@�̔j���̔j��
	if (g_pVtxBuffPressEnter != NULL)
	{
		g_pVtxBuffPressEnter->Release();
		g_pVtxBuffPressEnter = NULL;
	}
}
//=============================================================================
// �X�V����
//=============================================================================
void UpdatePressEnter(void)
{
	
	VERTEX_2D *pVtx;			//���_���ւ̃|�C���^
	//���_�o�b�t�@�����b�N�����_�f�[�^�̃|�C���^���擾
	g_pVtxBuffPressEnter->Lock(0, 0, (void**)&pVtx, 0);
	
	for (int nCntPressEnter = 0; nCntPressEnter < MAX_PRESSENTER; nCntPressEnter++)
	{
		g_PressEnter[nCntPressEnter].PressEnterCnt++;

		if (g_PressEnter[nCntPressEnter].PressEnterCnt >= 30)
		{
			if (g_PressEnter[nCntPressEnter].PressEnterChange == 0)
			{
				g_PressEnter[nCntPressEnter].PressEnterChange = 1;
			}
			else if (g_PressEnter[nCntPressEnter].PressEnterChange == 1)
			{
				g_PressEnter[nCntPressEnter].PressEnterChange = 0;
			}
			//���_�J���[
			pVtx[0].col = D3DXCOLOR(g_PressEnter[nCntPressEnter].col.r, g_PressEnter[nCntPressEnter].col.g, g_PressEnter[nCntPressEnter].col.b, g_PressEnter[nCntPressEnter].PressEnterChange);
			pVtx[1].col = D3DXCOLOR(g_PressEnter[nCntPressEnter].col.r, g_PressEnter[nCntPressEnter].col.g, g_PressEnter[nCntPressEnter].col.b, g_PressEnter[nCntPressEnter].PressEnterChange);
			pVtx[2].col = D3DXCOLOR(g_PressEnter[nCntPressEnter].col.r, g_PressEnter[nCntPressEnter].col.g, g_PressEnter[nCntPressEnter].col.b, g_PressEnter[nCntPressEnter].PressEnterChange);
			pVtx[3].col = D3DXCOLOR(g_PressEnter[nCntPressEnter].col.r, g_PressEnter[nCntPressEnter].col.g, g_PressEnter[nCntPressEnter].col.b, g_PressEnter[nCntPressEnter].PressEnterChange);

			g_PressEnter[nCntPressEnter].PressEnterCnt = 0;
		}
		//���_���W
		pVtx[0].pos = D3DXVECTOR3(g_PressEnter[nCntPressEnter].pos.x - g_PressEnter[nCntPressEnter].fWIdth, g_PressEnter[nCntPressEnter].pos.y - g_PressEnter[nCntPressEnter].fHeight, g_PressEnter[nCntPressEnter].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_PressEnter[nCntPressEnter].pos.x + g_PressEnter[nCntPressEnter].fWIdth, g_PressEnter[nCntPressEnter].pos.y - g_PressEnter[nCntPressEnter].fHeight, g_PressEnter[nCntPressEnter].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_PressEnter[nCntPressEnter].pos.x - g_PressEnter[nCntPressEnter].fWIdth, g_PressEnter[nCntPressEnter].pos.y + g_PressEnter[nCntPressEnter].fHeight, g_PressEnter[nCntPressEnter].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_PressEnter[nCntPressEnter].pos.x + g_PressEnter[nCntPressEnter].fWIdth, g_PressEnter[nCntPressEnter].pos.y + g_PressEnter[nCntPressEnter].fHeight, g_PressEnter[nCntPressEnter].pos.z);
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPressEnter->Unlock();
}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawPressEnter(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X���擾����
	pDevice = GetDevice();

	//�A���t�@�e�X�g(�����F��`�悵�Ȃ��悤��)
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 150);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPressEnter, 0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g��ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturePressEnter);
	
	for (int nCntPressEnter = 0; nCntPressEnter < MAX_PRESSENTER; nCntPressEnter++)
	{
		if (g_PressEnter[nCntPressEnter].bDraw == true)
		{
			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				0,	//�J�n���钸�_�̃C���f�b�N�X
				2); //�`�悷��v���~�e�B�u��
		}
	}
	//�����_�[�X�e�[�g�̐ݒ�����ɖ߂�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

}
//=============================================================================
// �v���X�G���^�[�̐ݒ菈��
//=============================================================================
void SetPressEnter(D3DXVECTOR3 pos, D3DXCOLOR col, float fWIdth, float fHeight)
{
	int nCntPressEnter;

	VERTEX_2D *pVtx;//���_���ւ̃|�C���^
					//���_�o�b�t�@�����b�N�����_�f�[�^�̃|�C���^���擾
	g_pVtxBuffPressEnter->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntPressEnter = 0; nCntPressEnter < MAX_PRESSENTER; nCntPressEnter++)
	{
		if (g_PressEnter[nCntPressEnter].bUse == false)	//�A�C�e�����g�p����Ă��Ȃ�
		{

			g_PressEnter[nCntPressEnter].pos = pos;
			g_PressEnter[nCntPressEnter].fWIdth = fWIdth;
			g_PressEnter[nCntPressEnter].fHeight = fHeight;

			//���_���W
			pVtx[0].pos = D3DXVECTOR3(g_PressEnter[nCntPressEnter].pos.x - g_PressEnter[nCntPressEnter].fWIdth, g_PressEnter[nCntPressEnter].pos.y - g_PressEnter[nCntPressEnter].fHeight, g_PressEnter[nCntPressEnter].pos.z);
			pVtx[1].pos = D3DXVECTOR3(g_PressEnter[nCntPressEnter].pos.x + g_PressEnter[nCntPressEnter].fWIdth, g_PressEnter[nCntPressEnter].pos.y - g_PressEnter[nCntPressEnter].fHeight, g_PressEnter[nCntPressEnter].pos.z);
			pVtx[2].pos = D3DXVECTOR3(g_PressEnter[nCntPressEnter].pos.x - g_PressEnter[nCntPressEnter].fWIdth, g_PressEnter[nCntPressEnter].pos.y + g_PressEnter[nCntPressEnter].fHeight, g_PressEnter[nCntPressEnter].pos.z);
			pVtx[3].pos = D3DXVECTOR3(g_PressEnter[nCntPressEnter].pos.x + g_PressEnter[nCntPressEnter].fWIdth, g_PressEnter[nCntPressEnter].pos.y + g_PressEnter[nCntPressEnter].fHeight, g_PressEnter[nCntPressEnter].pos.z);

			g_PressEnter[nCntPressEnter].col = col;

			//���_�J���[
			pVtx[0].col = col;
			pVtx[1].col = col;
			pVtx[2].col = col;
			pVtx[3].col = col;
			g_PressEnter[nCntPressEnter].bDraw = true;
			g_PressEnter[nCntPressEnter].bUse = true;
			break;
		}
		pVtx += 4;	//���_�f�[�^�̃|�C���^��4���i�߂�	
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPressEnter->Unlock();
}
//=============================================================================
// �v���X�G���^�[�̎擾
//=============================================================================
PRESSENTER *GetPressEnter(void)
{
	return &g_PressEnter[0];
}