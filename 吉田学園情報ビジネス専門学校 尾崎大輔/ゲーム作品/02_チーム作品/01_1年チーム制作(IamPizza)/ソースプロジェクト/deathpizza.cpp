//=============================================================================
//
// �f�X�s�U���� [deathpizza.cpp]
// Author : Meguro Mikiya
//
//=============================================================================
#include "deathpizza.h"
#include "shadow.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define EFFECT_TEXTURENAME	 "data\\TEXTURE\\DEATHPIZZA000.png"	//�e�N�X�`���̃t�@�C����
#define TEX_POS_X_INIT			(1.0f)							//�e�N�X�`�����WU�̏����ʒu
#define TEX_POS_Y_INIT			(1.0f)							//�e�N�X�`�����WV�̏����ʒu
#define TEX_LEFT				(0.0f)							//�e�N�X�`�����WU��
#define TEX_RIGHT				(1.0f)							//�e�N�X�`�����WU�E
#define TEX_TOP					(0.0f)							//�e�N�X�`�����WV��
#define TEX_BOT					(1.0f)							//�e�N�X�`�����WV��
#define MAX_EFFECT				(128)							//�G�t�F�N�g�̍ő吔

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexDeathPizza(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffDeathPizza = NULL;	//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9	g_pTextureDeathPizza = NULL;		//�e�N�X�`���ւ̃|�C���^
DEATHPIZZA g_aDeathPizza[MAX_EFFECT];

//=============================================================================
// ����������
//=============================================================================
void InitDeathPizza(void)
{
	LPDIRECT3DDEVICE9 pDevice;	// �f�o�C�X�̎擾
	pDevice = GetDevice();	// �f�o�C�X�̎擾

	//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			EFFECT_TEXTURENAME,
			&g_pTextureDeathPizza);
	// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_EFFECT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffDeathPizza,
		NULL);

	VERTEX_3D *pVtx;
	//���_�o�b�t�@�����b�N
	g_pVtxBuffDeathPizza->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntDeathPizza = 0; nCntDeathPizza < MAX_EFFECT; nCntDeathPizza++)
	{
		//���_���W
		pVtx[0].pos = D3DXVECTOR3(-20.0f, 20.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(20.0f, 20.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-20.0f, -20.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(20.0f, -20.0f, 0.0f);

		//�@���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		//���_�J���[
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(TEX_LEFT, TEX_TOP);
		pVtx[1].tex = D3DXVECTOR2(TEX_RIGHT, TEX_TOP);
		pVtx[2].tex = D3DXVECTOR2(TEX_LEFT, TEX_BOT);
		pVtx[3].tex = D3DXVECTOR2(TEX_RIGHT, TEX_BOT);
		//���_�f�[�^�̃|�C���^��4���i�߂�
		pVtx += 4;	
	}

	for (int nCntDeathPizza = 0; nCntDeathPizza < MAX_EFFECT; nCntDeathPizza++)
	{
		g_aDeathPizza[nCntDeathPizza].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aDeathPizza[nCntDeathPizza].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aDeathPizza[nCntDeathPizza].fRadius = 0.0f;
		g_aDeathPizza[nCntDeathPizza].fHeght = 0.0f;
		g_aDeathPizza[nCntDeathPizza].fWidth = 0.0f;
		g_aDeathPizza[nCntDeathPizza].bUse = false;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffDeathPizza->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void UninitDeathPizza(void)
{	//�e�N�X�`���̔j��
	if (g_pTextureDeathPizza != NULL)
	{
		g_pTextureDeathPizza->Release();
		g_pTextureDeathPizza = NULL;
	}
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffDeathPizza != NULL)
	{
		g_pVtxBuffDeathPizza->Release();
		g_pVtxBuffDeathPizza = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateDeathPizza(void)
{
	//���_���ւ̃|�C���^
	VERTEX_3D *pVtx;
	//���_�o�b�t�@�����b�N�����_�f�[�^�̃|�C���^���擾
	g_pVtxBuffDeathPizza->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntDeathPizza = 0; nCntDeathPizza < MAX_EFFECT; nCntDeathPizza++)
	{
		if (g_aDeathPizza[nCntDeathPizza].bUse == true)	//�G�t�F�N�g���g�p����Ă���
		{
			g_aDeathPizza[nCntDeathPizza].pos += g_aDeathPizza[nCntDeathPizza].move;
			//g_aDeathPizza[nCntDeathPizza].nLife -= 1;
			//g_aDeathPizza[nCntDeathPizza].fRadius -= 0.5f;
			g_aDeathPizza[nCntDeathPizza].col.a -= 0.01f;

			if (/*g_aDeathPizza[nCntDeathPizza].nLife <= 0 || */g_aDeathPizza[nCntDeathPizza].col.a <= 0.1f)	//�G�t�F�N�g�̃��C�t���O
			{
				g_aDeathPizza[nCntDeathPizza].bUse = false;
			}
			//���_���W
			pVtx[0].pos = D3DXVECTOR3(-g_aDeathPizza[nCntDeathPizza].fRadius, g_aDeathPizza[nCntDeathPizza].fRadius, 0);
			pVtx[1].pos = D3DXVECTOR3(g_aDeathPizza[nCntDeathPizza].fRadius, g_aDeathPizza[nCntDeathPizza].fRadius, 0);
			pVtx[2].pos = D3DXVECTOR3(-g_aDeathPizza[nCntDeathPizza].fRadius, -g_aDeathPizza[nCntDeathPizza].fRadius, 0);
			pVtx[3].pos = D3DXVECTOR3(g_aDeathPizza[nCntDeathPizza].fRadius, -g_aDeathPizza[nCntDeathPizza].fRadius, 0);

			//���_�J���[
			pVtx[0].col = D3DXCOLOR(g_aDeathPizza[nCntDeathPizza].col.r, g_aDeathPizza[nCntDeathPizza].col.g, g_aDeathPizza[nCntDeathPizza].col.b, g_aDeathPizza[nCntDeathPizza].col.a);
			pVtx[1].col = D3DXCOLOR(g_aDeathPizza[nCntDeathPizza].col.r, g_aDeathPizza[nCntDeathPizza].col.g, g_aDeathPizza[nCntDeathPizza].col.b, g_aDeathPizza[nCntDeathPizza].col.a);
			pVtx[2].col = D3DXCOLOR(g_aDeathPizza[nCntDeathPizza].col.r, g_aDeathPizza[nCntDeathPizza].col.g, g_aDeathPizza[nCntDeathPizza].col.b, g_aDeathPizza[nCntDeathPizza].col.a);
			pVtx[3].col = D3DXCOLOR(g_aDeathPizza[nCntDeathPizza].col.r, g_aDeathPizza[nCntDeathPizza].col.g, g_aDeathPizza[nCntDeathPizza].col.b, g_aDeathPizza[nCntDeathPizza].col.a);

			pVtx += 4;	//���_�f�[�^�̃|�C���^��4���i�߂�
		}
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffDeathPizza->Unlock();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawDeathPizza(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX  mtxView, mtxTrans;				//�v�Z�p�}�g���b�N�X

	//�A���t�@�e�X�g(�����F��`�悵�Ȃ��悤��)
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 150);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	//Z�o�b�t�@�̐ݒ�
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	// ���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);


	for (int nCntDeathPizza = 0; nCntDeathPizza < MAX_EFFECT; nCntDeathPizza++)
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_aDeathPizza[nCntDeathPizza].mtrxWorldDeathPizza);
		//�r���[�}�g���b�N�X���擾
		pDevice->GetTransform(D3DTS_VIEW, &mtxView);
		//�t�s���ݒ�
		g_aDeathPizza[nCntDeathPizza].mtrxWorldDeathPizza._11 = mtxView._11;
		g_aDeathPizza[nCntDeathPizza].mtrxWorldDeathPizza._12 = mtxView._21;
		g_aDeathPizza[nCntDeathPizza].mtrxWorldDeathPizza._13 = mtxView._31;
		g_aDeathPizza[nCntDeathPizza].mtrxWorldDeathPizza._21 = mtxView._12;
		g_aDeathPizza[nCntDeathPizza].mtrxWorldDeathPizza._22 = mtxView._22;
		g_aDeathPizza[nCntDeathPizza].mtrxWorldDeathPizza._23 = mtxView._32;
		g_aDeathPizza[nCntDeathPizza].mtrxWorldDeathPizza._31 = mtxView._13;
		g_aDeathPizza[nCntDeathPizza].mtrxWorldDeathPizza._32 = mtxView._23;
		g_aDeathPizza[nCntDeathPizza].mtrxWorldDeathPizza._33 = mtxView._33;
		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_aDeathPizza[nCntDeathPizza].pos.x, g_aDeathPizza[nCntDeathPizza].pos.y, g_aDeathPizza[nCntDeathPizza].pos.z);
		D3DXMatrixMultiply(&g_aDeathPizza[nCntDeathPizza].mtrxWorldDeathPizza, &g_aDeathPizza[nCntDeathPizza].mtrxWorldDeathPizza, &mtxTrans);
		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_aDeathPizza[nCntDeathPizza].mtrxWorldDeathPizza);
		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffDeathPizza, 0, sizeof(VERTEX_3D));
		//���_�t�H�[�}�b�g��ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureDeathPizza);

		if (g_aDeathPizza[nCntDeathPizza].bUse == true)	//�G�t�F�N�g���g�p����Ă���
		{
			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				0 + (4 * nCntDeathPizza),	//�J�n���钸�_�̃C���f�b�N�X
				2); //�`�悷��v���~�e�B�u��
		}

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, NULL);
	}
	//�����_�[�X�e�[�g�̐ݒ�����ɖ߂�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	//Z�o�b�t�@���f�t�H���g�̐ݒ�ɖ߂�
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	// ���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexDeathPizza(LPDIRECT3DDEVICE9 pDevice)
{
	// ���_�o�b�t�@�𐶐�


	// ���_���̐ݒ�

}

//=============================================================================
// �G�t�F�N�g�̐ݒ菈��
//=============================================================================
void SetDeathPizza(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fRadius, int nLife)
{
	int nCntDeathPizza;

	VERTEX_3D *pVtx;//���_���ւ̃|�C���^
	//���_�o�b�t�@�����b�N�����_�f�[�^�̃|�C���^���擾
	g_pVtxBuffDeathPizza->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntDeathPizza = 0; nCntDeathPizza < MAX_EFFECT; nCntDeathPizza++)
	{
		if (g_aDeathPizza[nCntDeathPizza].bUse == false)	//�G�t�F�N�g���g�p����Ă��Ȃ�
		{
			g_aDeathPizza[nCntDeathPizza].pos = pos;
			g_aDeathPizza[nCntDeathPizza].move = move;
			g_aDeathPizza[nCntDeathPizza].fRadius = fRadius;
			g_aDeathPizza[nCntDeathPizza].nLife = nLife;
			g_aDeathPizza[nCntDeathPizza].col = col;
			g_aDeathPizza[nCntDeathPizza].bUse = true;
			break;
		}
		pVtx += 4;	//���_�f�[�^�̃|�C���^��4���i�߂�	
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffDeathPizza->Unlock();
}
