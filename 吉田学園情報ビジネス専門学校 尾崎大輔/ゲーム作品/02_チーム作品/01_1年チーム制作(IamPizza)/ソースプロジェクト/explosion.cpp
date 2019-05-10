//=============================================================================
//
// �������� [Explosion.cpp]
// Author : Meguro Mikiya
//
//=============================================================================
#include "explosion.h"
#include "shadow.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define EXPLOSION_TEXTURENAME	 "data\\TEXTURE\\explosion000.png"//�e�N�X�`���̃t�@�C����
#define COUNTER_ANIM_RESET		(7)								//�J�E���^�[�p
#define TEX_POS_X_INIT			(0.125f)						//�e�N�X�`�����WU�̏����ʒu
#define TEX_POS_Y_INIT			(1.0f)							//�e�N�X�`�����WV�̏����ʒu
#define TEX_LEFT				(0.0f)							//�e�N�X�`�����WU��
#define TEX_RIGHT				(0.125f)						//�e�N�X�`�����WU�E
#define TEX_TOP					(0.0f)							//�e�N�X�`�����WV��
#define TEX_BOT					(1.0f)							//�e�N�X�`�����WV��
#define MAX_EXPLOSION			(128)							//�����̍ő吔

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexExplosion(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL;	//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9	g_pTextureExplosion = NULL;		//�e�N�X�`���ւ̃|�C���^
EXPLOSION g_aExplosion[MAX_EXPLOSION];

//=============================================================================
// ����������
//=============================================================================
void InitExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice;	// �f�o�C�X�̎擾
	pDevice = GetDevice();	// �f�o�C�X�̎擾

	//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			EXPLOSION_TEXTURENAME,
			&g_pTextureExplosion);
	// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_EXPLOSION,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffExplosion,
		NULL);

	VERTEX_3D *pVtx;
	//���_�o�b�t�@�����b�N
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
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
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);		//U�����AV�������@(0.0f�`1.0f�j
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);		//U�����AV�������@(0.0f�`1.0f�j
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);		//U�����AV�������@(0.0f�`1.0f�j
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);		//U�����AV�������@(0.0f�`1.0f�j
		//���_�f�[�^�̃|�C���^��4���i�߂�
		pVtx += 4;	
	}

	for (int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		g_aExplosion[nCntExplosion].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aExplosion[nCntExplosion].fRadius = 0.0f;
		g_aExplosion[nCntExplosion].fHeght = 0.0f;
		g_aExplosion[nCntExplosion].fWidth = 0.0f;
		g_aExplosion[nCntExplosion].nCounterAnim = 0;
		g_aExplosion[nCntExplosion].nPatternAnim = 0;
		g_aExplosion[nCntExplosion].bUse = false;
		g_aExplosion[nCntExplosion].fTest = 1;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffExplosion->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void UninitExplosion(void)
{	//�e�N�X�`���̔j��
	if (g_pTextureExplosion != NULL)
	{
		g_pTextureExplosion->Release();
		g_pTextureExplosion = NULL;
	}
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffExplosion != NULL)
	{
		g_pVtxBuffExplosion->Release();
		g_pVtxBuffExplosion = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateExplosion(void)
{
	VERTEX_3D *pVtx;//���_���ւ̃|�C���^

					//���_�o�b�t�@�����b�N�����_�f�[�^�̃|�C���^���擾
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == true)
		{	// �g�p�����ꍇ
			g_aExplosion[nCntExplosion].nCounterAnim++;			// �J�E���^�[�̉��Z

			if ((g_aExplosion[nCntExplosion].nCounterAnim % 20) == 0)
			{
				g_aExplosion[nCntExplosion].nPatternAnim = (g_aExplosion[nCntExplosion].nPatternAnim + 1);

				//�e�N�X�`���ݒ�
				pVtx[nCntExplosion * 4].tex = D3DXVECTOR2((g_aExplosion[nCntExplosion].nPatternAnim * 0.1f), 0.0f);
				pVtx[nCntExplosion * 4 + 1].tex = D3DXVECTOR2((g_aExplosion[nCntExplosion].nPatternAnim * 0.1f) + 0.1f, 0.0f);
				pVtx[nCntExplosion * 4 + 2].tex = D3DXVECTOR2((g_aExplosion[nCntExplosion].nPatternAnim * 0.1f), 1.0f);
				pVtx[nCntExplosion * 4 + 3].tex = D3DXVECTOR2((g_aExplosion[nCntExplosion].nPatternAnim * 0.1f) + 0.1f, 1.0f);

				//���_�J���[
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_aExplosion[nCntExplosion].fAlpha);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_aExplosion[nCntExplosion].fAlpha);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_aExplosion[nCntExplosion].fAlpha);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_aExplosion[nCntExplosion].fAlpha);

				if (g_aExplosion[nCntExplosion].nPatternAnim > 7)
				{
					g_aExplosion[nCntExplosion].bUse = false;			//�g�p���Ă��Ȃ����
				}
			}

			g_aExplosion[nCntExplosion].pos.y += 0.3f;
		}
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffExplosion->Unlock();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX  mtxView, mtxTrans;				//�v�Z�p�}�g���b�N�X

	//�A���t�@�e�X�g(�����F��`�悵�Ȃ��悤��)
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 150);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	//Z�o�b�t�@�̐ݒ�
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	for (int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_aExplosion[nCntExplosion].mtrxWorldExplosion);
		//�r���[�}�g���b�N�X���擾
		pDevice->GetTransform(D3DTS_VIEW, &mtxView);
		//�t�s���ݒ�
		g_aExplosion[nCntExplosion].mtrxWorldExplosion._11 = mtxView._11;
		g_aExplosion[nCntExplosion].mtrxWorldExplosion._12 = mtxView._21;
		g_aExplosion[nCntExplosion].mtrxWorldExplosion._13 = mtxView._31;
		g_aExplosion[nCntExplosion].mtrxWorldExplosion._21 = mtxView._12;
		g_aExplosion[nCntExplosion].mtrxWorldExplosion._22 = mtxView._22;
		g_aExplosion[nCntExplosion].mtrxWorldExplosion._23 = mtxView._32;
		g_aExplosion[nCntExplosion].mtrxWorldExplosion._31 = mtxView._13;
		g_aExplosion[nCntExplosion].mtrxWorldExplosion._32 = mtxView._23;
		g_aExplosion[nCntExplosion].mtrxWorldExplosion._33 = mtxView._33;
		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_aExplosion[nCntExplosion].pos.x, g_aExplosion[nCntExplosion].pos.y, g_aExplosion[nCntExplosion].pos.z);
		D3DXMatrixMultiply(&g_aExplosion[nCntExplosion].mtrxWorldExplosion, &g_aExplosion[nCntExplosion].mtrxWorldExplosion, &mtxTrans);
		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_aExplosion[nCntExplosion].mtrxWorldExplosion);
		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffExplosion, 0, sizeof(VERTEX_3D));
		//���_�t�H�[�}�b�g��ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureExplosion);

		if (g_aExplosion[nCntExplosion].bUse == true)	//�������g�p����Ă���
		{
			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				0 + (4 * nCntExplosion),	//�J�n���钸�_�̃C���f�b�N�X
				2); //�`�悷��v���~�e�B�u��
		}
	}
	//�����_�[�X�e�[�g�̐ݒ�����ɖ߂�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	//Z�o�b�t�@���f�t�H���g�̐ݒ�ɖ߂�
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	//�����_�[�X�e�C�g�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexExplosion(LPDIRECT3DDEVICE9 pDevice)
{
	// ���_�o�b�t�@�𐶐�


	// ���_���̐ݒ�

}

//=============================================================================
// �����̐ݒ菈��
//=============================================================================
void SetExplosion(D3DXVECTOR3 pos, D3DXCOLOR col, float fHeght, float fWidth)
{
	int nCntExplosion;

	VERTEX_3D *pVtx;//���_���ւ̃|�C���^
	//���_�o�b�t�@�����b�N�����_�f�[�^�̃|�C���^���擾
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == false)	//�e���g�p����Ă��Ȃ�
		{
			g_aExplosion[nCntExplosion].pos = pos;
			//���_���W
			pVtx[0].pos = D3DXVECTOR3(-fWidth, fHeght, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(fWidth, fHeght, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-fWidth, -fHeght, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(fWidth, -fHeght, 0.0f);

			//���_�J���[
			pVtx[0].col = col;
			pVtx[1].col = col;
			pVtx[2].col = col;
			pVtx[3].col = col;

			g_aExplosion[nCntExplosion].col = col;

			g_aExplosion[nCntExplosion].nCounterAnim = 0;
			g_aExplosion[nCntExplosion].nPatternAnim = 0;
			g_aExplosion[nCntExplosion].fTest = 1;

			g_aExplosion[nCntExplosion].bUse = true;
			break;
		}
		pVtx += 4;	//���_�f�[�^�̃|�C���^��4���i�߂�	
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffExplosion->Unlock();
}
