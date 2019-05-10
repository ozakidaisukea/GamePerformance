//=============================================================================
//
// �|���S������ [billboard.cpp]
// Author : Ozaki
//
//=============================================================================
#include "billboard.h"
#include "shadow.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_FOER		(4)
#define BILLTEXTURENAME		"data\\TEXTURE\\bullet000.png"	// �e�N�X�`����

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexBillboard(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9	   g_pVtxBuffBillboard = NULL;		// ���_�o�b�t�@�̃|�C���^
LPDIRECT3DTEXTURE9		   g_pTextureBillboard = NULL;		// �e�N�X�`���ւ̃|�C���^
Billboard				   g_aBillboard[MAX_BILLBOARD];
int						   g_nIdxShadow;

//=============================================================================
// ����������
//=============================================================================
void InitBillboard(void)
{
	//LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;	// �f�o�C�X�ւ̃|�C���^
	pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, BILLTEXTURENAME, &g_pTextureBillboard);

	// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MAX_FOER * MAX_BILLBOARD,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBillboard,
		NULL);

	VERTEX_3D* pVtx; //���_���̃|�C���^


					 // ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
	{
		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-15.0, 20.0, -0);
		pVtx[1].pos = D3DXVECTOR3(15.0, 20.0, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-15.0, -0, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(15.0, -0, 0.0f);

		// �@�����
		pVtx[0].nor = D3DXVECTOR3(0, 0, -1);
		pVtx[1].nor = D3DXVECTOR3(0, 0, -1);
		pVtx[2].nor = D3DXVECTOR3(0, 0, -1);
		pVtx[3].nor = D3DXVECTOR3(0, 0, -1);

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
	g_pVtxBuffBillboard->Unlock();

	for (int nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
	{
		g_aBillboard[nCntBillboard].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBillboard[nCntBillboard].movve = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBillboard[nCntBillboard].bUse = false;
	}
	g_nIdxShadow = SetShadow(g_aBillboard[0].pos, g_aBillboard[0].rot);
}

//=============================================================================
// �I������
//=============================================================================
void UninitBillboard(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffBillboard != NULL)
	{
		g_pVtxBuffBillboard->Release();
		g_pVtxBuffBillboard = NULL;
	}

	if (g_pTextureBillboard != NULL)
	{
		g_pTextureBillboard->Release();
		g_pTextureBillboard = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBillboard(void)
{
	/*SetPostionShadow(g_nIdxShadow, D3DXVECTOR3(g_aBillboard[0].pos.x, 0,
		g_aBillboard[0].pos.z));*/
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBillboard(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans, mtxView;


	for (int nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
	{

		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_aBillboard[nCntBillboard].mtxWorld);

		//
		pDevice->GetTransform(D3DTS_VIEW, &mtxView);
		g_aBillboard[nCntBillboard].mtxWorld._11 = mtxView._11;
		g_aBillboard[nCntBillboard].mtxWorld._12 = mtxView._21;
		g_aBillboard[nCntBillboard].mtxWorld._13 = mtxView._31;
		g_aBillboard[nCntBillboard].mtxWorld._21 = mtxView._12;
		g_aBillboard[nCntBillboard].mtxWorld._22 = mtxView._22;
		g_aBillboard[nCntBillboard].mtxWorld._23 = mtxView._32;
		g_aBillboard[nCntBillboard].mtxWorld._31 = mtxView._13;
		g_aBillboard[nCntBillboard].mtxWorld._32 = mtxView._23;
		g_aBillboard[nCntBillboard].mtxWorld._33 = mtxView._33;

		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_aBillboard[nCntBillboard].pos.x, g_aBillboard[nCntBillboard].pos.y, g_aBillboard[nCntBillboard].pos.z);
		D3DXMatrixMultiply(&g_aBillboard[nCntBillboard].mtxWorld, &g_aBillboard[nCntBillboard].mtxWorld, &mtxTrans);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_aBillboard[nCntBillboard].mtxWorld);

		// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffBillboard, 0, sizeof(VERTEX_3D));

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureBillboard);

		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

		if (g_aBillboard[nCntBillboard].bUse == true)
		{
			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0 + (4 * nCntBillboard), 2);
		}

		// �����_�[�X�e�[�g�����ɖ߂�
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexBillboard(LPDIRECT3DDEVICE9 pDevice)
{

}
//=============================================================================
// �ǂ̐ݒ�ʒu
//=============================================================================
void SetBillboard(D3DXVECTOR3 posBillboard, D3DXVECTOR3 rotBillboard)
{
	int nCntBillboard;

	for (nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
	{
		if (g_aBillboard[nCntBillboard].bUse == false)
		{
			g_aBillboard[nCntBillboard].pos = posBillboard;
			g_aBillboard[nCntBillboard].movve = rotBillboard;
			g_aBillboard[nCntBillboard].bUse = true;
			break;
		}
	}
}