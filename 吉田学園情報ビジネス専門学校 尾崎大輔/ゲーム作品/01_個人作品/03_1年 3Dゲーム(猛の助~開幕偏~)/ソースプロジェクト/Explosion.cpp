//=============================================================================
//
// �|���S������ [Explosion.cpp]
// Author : Ozaki
//
//=============================================================================
#include "Explosion.h"
#include "shadow.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_FOER		(4)
#define BILLTEXTURENAME		"data\\TEXTURE\\explosion000.png"	// �e�N�X�`����)
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexExplosion(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9	   g_pVtxBuffExplosion = NULL;		// ���_�o�b�t�@�̃|�C���^
LPDIRECT3DTEXTURE9		   g_pTextureExplosion = NULL;		// �e�N�X�`���ւ̃|�C���^
Explosion				   g_aExplosion[MAX_EXPLOSION];

//=============================================================================
// ����������
//=============================================================================
void InitExplosion(void)
{
	//LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;	// �f�o�C�X�ւ̃|�C���^
	pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, BILLTEXTURENAME, &g_pTextureExplosion);

	// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MAX_FOER * MAX_EXPLOSION,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffExplosion,
		NULL);

	VERTEX_3D* pVtx; //���_���̃|�C���^


					 // ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-50, 10.0, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(50, 50, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-50, -50, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(10.0, -50, 0.0f);

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
		pVtx[1].tex = D3DXVECTOR2(0.125f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 0.125f);
		pVtx[3].tex = D3DXVECTOR2(0.125f, 0.125f);

		pVtx += 4;					//���_�f�[�^�̃|�C���^��4���i�߂�		

	}
	//���_�o�b�t�@���A�����b�N�h����
	g_pVtxBuffExplosion->Unlock();

	for (int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		g_aExplosion[nCntExplosion].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aExplosion[nCntExplosion].movve = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aExplosion[nCntExplosion].bUse = false;
	}
}

//=============================================================================
// �I������
//=============================================================================
void UninitExplosion(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffExplosion != NULL)
	{
		g_pVtxBuffExplosion->Release();
		g_pVtxBuffExplosion = NULL;
	}

	if (g_pTextureExplosion != NULL)
	{
		g_pTextureExplosion->Release();
		g_pTextureExplosion = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateExplosion(void)
{
		int nCntExplosion;
		VERTEX_3D*pVtx;		
													//���_���ւ̃|�C���^
	
		//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^�̎擾
		g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);
		for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
		{
			if (g_aExplosion[nCntExplosion].bUse == true)
			{
				g_aExplosion[nCntExplosion].nCounterAnim++;
				if ((g_aExplosion[nCntExplosion].nCounterAnim % 5) == 0)
				{
					g_aExplosion[nCntExplosion].nPatternAnim = (g_aExplosion[nCntExplosion].nPatternAnim + 1 % 8);
					//g_aExplosion[nCntExplosion].pos.y -= 10.0f;
					//���_���W�̐ݒ�
					/*pVtx[0].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - MAX_EXPLOSION, g_aExplosion[nCntExplosion].pos.y - MAX_EXPLOSION, g_aExplosion[nCntExplosion].pos.z);
					pVtx[1].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + MAX_EXPLOSION, g_aExplosion[nCntExplosion].pos.y - MAX_EXPLOSION, g_aExplosion[nCntExplosion].pos.z);
					pVtx[2].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - MAX_EXPLOSION, g_aExplosion[nCntExplosion].pos.y + MAX_EXPLOSION, g_aExplosion[nCntExplosion].pos.z);
					pVtx[3].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + MAX_EXPLOSION, g_aExplosion[nCntExplosion].pos.y + MAX_EXPLOSION, g_aExplosion[nCntExplosion].pos.z);*/
	
					//�e�N�X�`���̐ݒ�
					pVtx[0].tex.x = (0.0f + (0.125f * (g_aExplosion[nCntExplosion].nPatternAnim % 8)));
					pVtx[0].tex.y = (0.0f + 1.0f);
	
					pVtx[1].tex.x = (0.125f + (0.125f * (g_aExplosion[nCntExplosion].nPatternAnim % 8)));
					pVtx[1].tex.y = (0.0f + 1.0f);
	
					pVtx[2].tex.x = (0.0f + (0.125f * (g_aExplosion[nCntExplosion].nPatternAnim % 8)));
					pVtx[2].tex.y = (1.0f + 1.0f);
	
					pVtx[3].tex.x = (0.125f + (0.125f * (g_aExplosion[nCntExplosion].nPatternAnim % 8)));
					pVtx[3].tex.y = (1.0f + 1.0f);
	
					if (g_aExplosion[nCntExplosion].nPatternAnim >= 8)
					{
						g_aExplosion[nCntExplosion].bUse = false;
					}
				}
			}
			pVtx += 4;
		}
	
		//���_�o�b�t�@���A�����b�N
		g_pVtxBuffExplosion->Unlock();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans, mtxView;

	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 150);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);

	for (int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{

		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_aExplosion[nCntExplosion].mtxWorld);

		//
		pDevice->GetTransform(D3DTS_VIEW, &mtxView);
		g_aExplosion[nCntExplosion].mtxWorld._11 = mtxView._11;
		g_aExplosion[nCntExplosion].mtxWorld._12 = mtxView._21;
		g_aExplosion[nCntExplosion].mtxWorld._13 = mtxView._31;
		g_aExplosion[nCntExplosion].mtxWorld._21 = mtxView._12;
		g_aExplosion[nCntExplosion].mtxWorld._22 = mtxView._22;
		g_aExplosion[nCntExplosion].mtxWorld._23 = mtxView._32;
		g_aExplosion[nCntExplosion].mtxWorld._31 = mtxView._13;
		g_aExplosion[nCntExplosion].mtxWorld._32 = mtxView._23;
		g_aExplosion[nCntExplosion].mtxWorld._33 = mtxView._33;

		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_aExplosion[nCntExplosion].pos.x, g_aExplosion[nCntExplosion].pos.y, g_aExplosion[nCntExplosion].pos.z);
		D3DXMatrixMultiply(&g_aExplosion[nCntExplosion].mtxWorld, &g_aExplosion[nCntExplosion].mtxWorld, &mtxTrans);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_aExplosion[nCntExplosion].mtxWorld);

		// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffExplosion, 0, sizeof(VERTEX_3D));

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureExplosion);

	
		if (g_aExplosion[nCntExplosion].bUse == true)
		{
			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0 + (4 * nCntExplosion), 2);
		}

		// �����_�[�X�e�[�g�����ɖ߂�
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexExplosion(LPDIRECT3DDEVICE9 pDevice)
{

}
//=============================================================================
// �ǂ̐ݒ�ʒu
//=============================================================================
void SetExplosion(D3DXVECTOR3 posExplosion, D3DXVECTOR3 rotExplosion, D3DXCOLOR col)
{
	int nCntExplosion;
	VERTEX_3D*pVtx;														//���_���ւ̃|�C���^

	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == false)
		{

			g_aExplosion[nCntExplosion].pos = posExplosion;

			////���_���W�̐ݒ�
			//pVtx[0].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - MAX_EXPLOSION, g_aExplosion[nCntExplosion].pos.y - MAX_EXPLOSION, g_aExplosion[nCntExplosion].pos.z);
			//pVtx[1].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + MAX_EXPLOSION, g_aExplosion[nCntExplosion].pos.y - MAX_EXPLOSION, g_aExplosion[nCntExplosion].pos.z);
			//pVtx[2].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - MAX_EXPLOSION, g_aExplosion[nCntExplosion].pos.y + MAX_EXPLOSION, g_aExplosion[nCntExplosion].pos.z);
			//pVtx[3].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + MAX_EXPLOSION, g_aExplosion[nCntExplosion].pos.y + MAX_EXPLOSION, g_aExplosion[nCntExplosion].pos.z);

			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			g_aExplosion[nCntExplosion].pos = posExplosion;
			g_aExplosion[nCntExplosion].movve = rotExplosion;
			g_aExplosion[nCntExplosion].nCounterAnim = 0;
			g_aExplosion[nCntExplosion].nPatternAnim = 0;
			g_aExplosion[nCntExplosion].bUse = true;
			break;
		}
		pVtx += 4;
	}
	g_pVtxBuffExplosion->Unlock();
}

//=============================================================================
// �������擾
//=============================================================================
Explosion *GetExplosion(void)
{
	return &g_aExplosion[0];
}