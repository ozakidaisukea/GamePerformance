//=============================================================================
//
// �e�̏��� [shadoe.cpp]
// Author : Ozaki
//
//=============================================================================
#include "shadow.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_FOER		(4)
#define ENTER_TEXTURENAME		"data\\TEXTURE\\shadow000.jpg"	// �e�N�X�`����
#define MAX_SHADOW		(100)
//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;			// �ʒu
	D3DXVECTOR3	rot;			// ����
	D3DXMATRIX	mtxWorld;		//
	D3DXCOLOR	col;			// �F
	float		fRadius;		// ���a(�傫��)
	bool		bUse;			// �g�p���Ă��邩�ǂ���
}SHADOW;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexShadow(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffShadow = NULL;		// ���_�o�b�t�@�̃|�C���^
LPDIRECT3DTEXTURE9		g_pTextureShadow = NULL;		// �e�N�X�`���ւ̃|�C���^
//D3DXVECTOR3				g_posShadow;					// �ʒu
//D3DXVECTOR3				g_rotShadow;					// ����
//D3DXMATRIX				g_aShadow[nCntShadow].mtxWorld;				// ���[���h�}�g���b�N�X
SHADOW					g_aShadow[MAX_SHADOW];
//=============================================================================
// ����������
//=============================================================================
void InitShadow(void)
{
	//LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;	// �f�o�C�X�ւ̃|�C���^
	pDevice = GetDevice();

	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		g_aShadow[nCntShadow].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aShadow[nCntShadow].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aShadow[nCntShadow].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, ENTER_TEXTURENAME, &g_pTextureShadow);

	// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MAX_FOER * MAX_SHADOW,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffShadow,
		NULL);
	VERTEX_3D* pVtx;			//���_���̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-12.5, 0.0, 12.5);
		pVtx[1].pos = D3DXVECTOR3(12.5, 0.0, 12.5);
		pVtx[2].pos = D3DXVECTOR3(-12.5, 0.0, -12.5);
		pVtx[3].pos = D3DXVECTOR3(12.5, 0.0, -12.5);

		// �@�����
		pVtx[0].nor = D3DXVECTOR3(0, 1, 0);
		pVtx[1].nor = D3DXVECTOR3(0, 1, 0);
		pVtx[2].nor = D3DXVECTOR3(0, 1, 0);
		pVtx[3].nor = D3DXVECTOR3(0, 1, 0);

		// ���_�J���[
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;					//���_�f�[�^�̃|�C���^��4���i�߂�

	}

	//���_�o�b�t�@���A�����b�N�h����
	g_pVtxBuffShadow->Unlock();

}

//=============================================================================
// �I������
//=============================================================================
void UninitShadow(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffShadow != NULL)
	{
		g_pVtxBuffShadow->Release();
		g_pVtxBuffShadow = NULL;
	}

	if (g_pTextureShadow != NULL)
	{
		g_pTextureShadow->Release();
		g_pTextureShadow = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateShadow(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot[MAX_SHADOW], mtxTrans[MAX_SHADOW];

	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);


	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{

		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_aShadow[nCntShadow].mtxWorld);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot[nCntShadow], g_aShadow[nCntShadow].rot.y, g_aShadow[nCntShadow].rot.x, g_aShadow[nCntShadow].rot.z);
		D3DXMatrixMultiply(&g_aShadow[nCntShadow].mtxWorld, &g_aShadow[nCntShadow].mtxWorld, &mtxRot[nCntShadow]);

		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans[nCntShadow], g_aShadow[nCntShadow].pos.x, g_aShadow[nCntShadow].pos.y, g_aShadow[nCntShadow].pos.z);
		D3DXMatrixMultiply(&g_aShadow[nCntShadow].mtxWorld, &g_aShadow[nCntShadow].mtxWorld, &mtxTrans[nCntShadow]);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_aShadow[nCntShadow].mtxWorld);

		// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffShadow, 0, sizeof(VERTEX_3D));

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);
		if (g_aShadow[nCntShadow].bUse == true)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureShadow);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0 + (4 * nCntShadow), 2);
		}
	}
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexShadow(LPDIRECT3DDEVICE9 pDevice)
{
}

//=============================================================================
// �e�̐ݒ�
//=============================================================================
int SetShadow(D3DXVECTOR3 pos,D3DXVECTOR3 rot)
{
	int nCntShadow;
	VERTEX_3D*pVtx;					//���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (g_aShadow[nCntShadow].bUse == false)
		{
			g_aShadow[nCntShadow].pos = pos;
			g_aShadow[nCntShadow].rot = rot;

			// ���_���W�̐ݒ�
			/*pVtx[0].pos = D3DXVECTOR3(-12.5, 0.0, 12.5);
			pVtx[1].pos = D3DXVECTOR3(12.5, 0.0, 12.5);
			pVtx[2].pos = D3DXVECTOR3(-12.5, 0.0, -12.5);
			pVtx[3].pos = D3DXVECTOR3(12.5, 0.0, -12.5);*/

			g_aShadow[nCntShadow].bUse = true;
			break;
		}
		pVtx += 4;					//���_�f�[�^�̃|�C���^��4���i�߂�
	}
	return nCntShadow;				// �g�p���Ă���e�̔ԍ�(�C���f�b�N�X)��Ԃ�

	//���_�o�b�t�@���A�����b�N�h����
	g_pVtxBuffShadow->Unlock();
}
//=============================================================================
// �e�̈ʒu��ݒ�
//=============================================================================
void SetPostionShadow(int nIdxShadow, D3DXVECTOR3 pos)
{
	g_aShadow[nIdxShadow].pos = pos;
}
//=============================================================================
// �e�̍폜
//=============================================================================
void DeleteShadow(int nIdxShadow)
{
	g_aShadow[nIdxShadow].bUse = false;
}