//=============================================================================
//
// �e ���� [Shadow.cpp]
// Author : Meguro Mikiya
//
//=============================================================================
#include "shadow.h"
#include "camera.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define Shadow_TEXTURENAME		 "data\\TEXTURE\\shadow000.jpg"	//�e�N�X�`���̃t�@�C����
#define TEX_POS_X_INIT			(1.0f)							//�e�N�X�`�����WU�̏����ʒu
#define TEX_POS_Y_INIT			(1.0f)							//�e�N�X�`�����WV�̏����ʒu
#define TEX_LEFT				(0.0f)							//�e�N�X�`�����WU��
#define TEX_RIGHT				(1.0f)							//�e�N�X�`�����WU�E
#define TEX_TOP					(0.0f)							//�e�N�X�`�����WV��
#define TEX_BOT					(1.0f)							//�e�N�X�`�����WV��
#define MAX_SHADOW				(600)							//�e�̍ő吔

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexShadow(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffShadow = NULL;		//���_�o�b�t�@�ւ̃|�C���^
SHADOW		g_aShadow[MAX_SHADOW];						//�e
LPDIRECT3DTEXTURE9		g_pTextureShadow = NULL;	//�e�N�X�`���ւ̃|�C���^
//=============================================================================
// ����������
//=============================================================================
void InitShadow(void)
{
	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		g_aShadow[nCntShadow].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aShadow[nCntShadow].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aShadow[nCntShadow].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aShadow[nCntShadow].fRadius = 0.0f;
		g_aShadow[nCntShadow].bUse = false;
	}

	LPDIRECT3DDEVICE9 pDevice;	// �f�o�C�X�̎擾
	pDevice = GetDevice();	// �f�o�C�X�̎擾

	//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			Shadow_TEXTURENAME,
			&g_pTextureShadow);
	// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_SHADOW,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffShadow,
		NULL);

	
	VERTEX_3D *pVtx;
	//���_�o�b�t�@�����b�N
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		//���_���W
		pVtx[0].pos = D3DXVECTOR3(-g_aShadow[nCntShadow].fRadius, 0, g_aShadow[nCntShadow].fRadius);
		pVtx[1].pos = D3DXVECTOR3(g_aShadow[nCntShadow].fRadius, 0, g_aShadow[nCntShadow].fRadius);
		pVtx[2].pos = D3DXVECTOR3(-g_aShadow[nCntShadow].fRadius, 0, -g_aShadow[nCntShadow].fRadius);
		pVtx[3].pos = D3DXVECTOR3(g_aShadow[nCntShadow].fRadius, 0, -g_aShadow[nCntShadow].fRadius);

		//�@���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		//���_�J���[
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(TEX_LEFT, TEX_TOP);
		pVtx[1].tex = D3DXVECTOR2(TEX_RIGHT, TEX_TOP);
		pVtx[2].tex = D3DXVECTOR2(TEX_LEFT, TEX_BOT);
		pVtx[3].tex = D3DXVECTOR2(TEX_RIGHT, TEX_BOT);
		
		pVtx += 4;	//���_�f�[�^�̃|�C���^��4���i�߂�
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffShadow->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void UninitShadow(void)
{	//�e�N�X�`���̔j��
	if (g_pTextureShadow != NULL)
	{
		g_pTextureShadow->Release();
		g_pTextureShadow = NULL;
	}
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffShadow != NULL)
	{
		g_pVtxBuffShadow->Release();
		g_pVtxBuffShadow = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateShadow(void)
{
	Camera *pCamera;
	pCamera = GetCamera();

	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		//�J�����Ƃ̋��������߂�
		double length = pow((g_aShadow[nCntShadow].pos.x - pCamera->posV.x)*(g_aShadow[nCntShadow].pos.x - pCamera->posV.x)
			+ (g_aShadow[nCntShadow].pos.z - pCamera->posV.z)*(g_aShadow[nCntShadow].pos.z - pCamera->posV.z), 0.5);

		//float�^�ɕϊ�
		g_aShadow[nCntShadow].fLength = (float)length;
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX  mtxRot[MAX_SHADOW],  mtxTrans[MAX_SHADOW];				//�v�Z�p�}�g���b�N�X

	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	
	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (g_aShadow[nCntShadow].fLength < 2200)
		{//�e�ƃv���C���[�̋����ŕ`�悷�邩���߂�
		// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aShadow[nCntShadow].mtrxWorld);
			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot[nCntShadow], g_aShadow[nCntShadow].rot.y, g_aShadow[nCntShadow].rot.x, g_aShadow[nCntShadow].rot.z);
			D3DXMatrixMultiply(&g_aShadow[nCntShadow].mtrxWorld, &g_aShadow[nCntShadow].mtrxWorld, &mtxRot[nCntShadow]);
			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans[nCntShadow], g_aShadow[nCntShadow].pos.x, g_aShadow[nCntShadow].pos.y, g_aShadow[nCntShadow].pos.z);
			D3DXMatrixMultiply(&g_aShadow[nCntShadow].mtrxWorld, &g_aShadow[nCntShadow].mtrxWorld, &mtxTrans[nCntShadow]);
			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aShadow[nCntShadow].mtrxWorld);
			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffShadow, 0, sizeof(VERTEX_3D));
			//���_�t�H�[�}�b�g��ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureShadow);
			if (g_aShadow[nCntShadow].bUse == true)	//�e���g�p����Ă���
			{
				// �|���S���̕`��
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
					0 + (4 * nCntShadow),	//�J�n���钸�_�̃C���f�b�N�X
					2); //�`�悷��v���~�e�B�u��
			}
		}
	}
	//�����_�[�X�e�C�g�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//=============================================================================
// �e�̐ݒ菈��
//=============================================================================
int SetShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius)
{
	int nCntShadow;
	VERTEX_3D *pVtx;//���_���ւ̃|�C���^
	//���_�o�b�t�@�����b�N�����_�f�[�^�̃|�C���^���擾
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (g_aShadow[nCntShadow].bUse == false)	//�e���g�p����Ă��Ȃ�
		{
			g_aShadow[nCntShadow].pos = pos;
			g_aShadow[nCntShadow].rot = rot;
			g_aShadow[nCntShadow].fRadius = fRadius;
			//���_���W
			pVtx[0].pos = D3DXVECTOR3(-g_aShadow[nCntShadow].fRadius, 0, g_aShadow[nCntShadow].fRadius);
			pVtx[1].pos = D3DXVECTOR3(g_aShadow[nCntShadow].fRadius, 0, g_aShadow[nCntShadow].fRadius);
			pVtx[2].pos = D3DXVECTOR3(-g_aShadow[nCntShadow].fRadius, 0, -g_aShadow[nCntShadow].fRadius);
			pVtx[3].pos = D3DXVECTOR3(g_aShadow[nCntShadow].fRadius, 0, -g_aShadow[nCntShadow].fRadius);
			
			g_aShadow[nCntShadow].bUse = true;
			break;
		}
		pVtx += 4;	//���_�f�[�^�̃|�C���^��4���i�߂�	
	}
	return nCntShadow;
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffShadow->Unlock();
}

//=============================================================================
// �e�̈ʒu�ݒ�
//=============================================================================
void SetPositionShadow(int nIdxShadow, D3DXVECTOR3 pos, float fRadius)
{
	g_aShadow[nIdxShadow].pos = pos;
	g_aShadow[nIdxShadow].fRadius = fRadius;

	VERTEX_3D *pVtx;//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N�����_�f�[�^�̃|�C���^���擾
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);
	//���_�f�[�^�̃|�C���^���C���f�b�N�X���i�߂�
	pVtx += 4 * nIdxShadow;

	//���_���W
	pVtx[0].pos = D3DXVECTOR3(-g_aShadow[nIdxShadow].fRadius, 0, g_aShadow[nIdxShadow].fRadius);
	pVtx[1].pos = D3DXVECTOR3(g_aShadow[nIdxShadow].fRadius, 0, g_aShadow[nIdxShadow].fRadius);
	pVtx[2].pos = D3DXVECTOR3(-g_aShadow[nIdxShadow].fRadius, 0, -g_aShadow[nIdxShadow].fRadius);
	pVtx[3].pos = D3DXVECTOR3(g_aShadow[nIdxShadow].fRadius, 0, -g_aShadow[nIdxShadow].fRadius);

//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffShadow->Unlock();
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexShadow(LPDIRECT3DDEVICE9 pDevice)
{
	// ���_�o�b�t�@�𐶐�


	// ���_���̐ݒ�

}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void DeleteShadow(int nIdxShadow)
{
	g_aShadow[nIdxShadow].bUse = false;
}
