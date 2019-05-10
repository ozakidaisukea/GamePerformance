//=============================================================================
//
// �p�[�e�B�N������ [Particle.cpp]
// Author : Meguro Mikiya
//
//=============================================================================
#include "particle.h"
#include "shadow.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define PARTICLE_TEXTURENAME0	 "data\\TEXTURE\\Particle000.png"	//�e�N�X�`���̃t�@�C����
#define PARTICLE_TEXTURENAME1	 "data\\TEXTURE\\effect000.jpg"	//�e�N�X�`���̃t�@�C����

#define TEX_POS_X_INIT			(1.0f)								//�e�N�X�`�����WU�̏����ʒu
#define TEX_POS_Y_INIT			(1.0f)								//�e�N�X�`�����WV�̏����ʒu
#define TEX_LEFT				(0.0f)								//�e�N�X�`�����WU��
#define TEX_RIGHT				(1.0f)								//�e�N�X�`�����WU�E
#define TEX_TOP					(0.0f)								//�e�N�X�`�����WV��
#define TEX_BOT					(1.0f)								//�e�N�X�`�����WV��
#define MAX_PARTICLE			(7200)								//�p�[�e�B�N���̍ő吔
#define MAX_TEXTURE				(2)
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexParticle(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffParticle = NULL;	//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9	g_pTextureParticle[MAX_TEXTURE] = {};		//�e�N�X�`���ւ̃|�C���^
PARTICLE g_aParticle[MAX_PARTICLE];

//=============================================================================
// ����������
//=============================================================================
void InitParticle(void)
{
	LPDIRECT3DDEVICE9 pDevice;	// �f�o�C�X�̎擾
	pDevice = GetDevice();	// �f�o�C�X�̎擾

	//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			PARTICLE_TEXTURENAME0,
			&g_pTextureParticle[0]);
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			PARTICLE_TEXTURENAME1,
			&g_pTextureParticle[1]);
	// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_PARTICLE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffParticle,
		NULL);

	VERTEX_3D *pVtx;
	//���_�o�b�t�@�����b�N
	g_pVtxBuffParticle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
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

	for (int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		g_aParticle[nCntParticle].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aParticle[nCntParticle].fRadius = 0.0f;
		g_aParticle[nCntParticle].fHeght = 0.0f;
		g_aParticle[nCntParticle].fWidth = 0.0f;
		g_aParticle[nCntParticle].bUse = false;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffParticle->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void UninitParticle(void)
{	//�e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < MAX_TEXTURE; nCnt++)
	{
		if (g_pTextureParticle[nCnt] != NULL)
		{
			g_pTextureParticle[nCnt]->Release();
			g_pTextureParticle[nCnt] = NULL;
		}
	}
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffParticle != NULL)
	{
		g_pVtxBuffParticle->Release();
		g_pVtxBuffParticle = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateParticle(void)
{
	//���_���ւ̃|�C���^
	VERTEX_3D *pVtx;
	//���_�o�b�t�@�����b�N�����_�f�[�^�̃|�C���^���擾
	g_pVtxBuffParticle->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		if (g_aParticle[nCntParticle].bUse == true)	//�p�[�e�B�N�����g�p����Ă���
		{
			g_aParticle[nCntParticle].pos += g_aParticle[nCntParticle].move;
			g_aParticle[nCntParticle].nLife -= 1;
			g_aParticle[nCntParticle].fRadius -= 0.5f;
		}
		if (g_aParticle[nCntParticle].nLife <= 0)	//�p�[�e�B�N���̃��C�t���O
		{
			g_aParticle[nCntParticle].bUse = false;
		}
		//���_���W
		pVtx[0].pos = D3DXVECTOR3(-g_aParticle[nCntParticle].fRadius,g_aParticle[nCntParticle].fRadius, 0);
		pVtx[1].pos = D3DXVECTOR3(g_aParticle[nCntParticle].fRadius,g_aParticle[nCntParticle].fRadius, 0);
		pVtx[2].pos = D3DXVECTOR3(-g_aParticle[nCntParticle].fRadius,-g_aParticle[nCntParticle].fRadius, 0);
		pVtx[3].pos = D3DXVECTOR3(g_aParticle[nCntParticle].fRadius,-g_aParticle[nCntParticle].fRadius, 0);

		pVtx += 4;	//���_�f�[�^�̃|�C���^��4���i�߂�
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffParticle->Unlock();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawParticle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX  mtxView, mtxTrans;				//�v�Z�p�}�g���b�N�X

	//�A���t�@�e�X�g(�����F��`�悵�Ȃ��悤��)
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 150);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	//Z�o�b�t�@�̐ݒ�
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	// ���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);


	for (int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_aParticle[nCntParticle].mtrxWorldParticle);
		//�r���[�}�g���b�N�X���擾
		pDevice->GetTransform(D3DTS_VIEW, &mtxView);
		//�t�s���ݒ�
		g_aParticle[nCntParticle].mtrxWorldParticle._11 = mtxView._11;
		g_aParticle[nCntParticle].mtrxWorldParticle._12 = mtxView._21;
		g_aParticle[nCntParticle].mtrxWorldParticle._13 = mtxView._31;
		g_aParticle[nCntParticle].mtrxWorldParticle._21 = mtxView._12;
		g_aParticle[nCntParticle].mtrxWorldParticle._22 = mtxView._22;
		g_aParticle[nCntParticle].mtrxWorldParticle._23 = mtxView._32;
		g_aParticle[nCntParticle].mtrxWorldParticle._31 = mtxView._13;
		g_aParticle[nCntParticle].mtrxWorldParticle._32 = mtxView._23;
		g_aParticle[nCntParticle].mtrxWorldParticle._33 = mtxView._33;
		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_aParticle[nCntParticle].pos.x, g_aParticle[nCntParticle].pos.y, g_aParticle[nCntParticle].pos.z);
		D3DXMatrixMultiply(&g_aParticle[nCntParticle].mtrxWorldParticle, &g_aParticle[nCntParticle].mtrxWorldParticle, &mtxTrans);
		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_aParticle[nCntParticle].mtrxWorldParticle);
		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffParticle, 0, sizeof(VERTEX_3D));
		//���_�t�H�[�}�b�g��ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureParticle[g_aParticle[nCntParticle].nTexType]);

		if (g_aParticle[nCntParticle].bUse == true)	//�p�[�e�B�N�����g�p����Ă���
		{
			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				0 + (4 * nCntParticle),	//�J�n���钸�_�̃C���f�b�N�X
				2); //�`�悷��v���~�e�B�u��
		}
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
void MakeVertexParticle(LPDIRECT3DDEVICE9 pDevice)
{
	// ���_�o�b�t�@�𐶐�


	// ���_���̐ݒ�

}

//=============================================================================
// �p�[�e�B�N���̐ݒ菈��
//=============================================================================
void SetParticle(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, D3DXCOLOR col, float fRadius, int nLife, PARTICLE_TYPE type)
{
	int nCntParticle;
	int nParticleTotal = 0;	//1��p�[�e�B�N���̍ő吔
	int RotRand;
	int RotRandY;
	int ColRandR;
	int ColRandG;
	int ColRandB;
	float ColR = 0;
	float ColG = 0;
	float ColB = 0;
	D3DXCOLOR(0, 0, 0, 0);

	VERTEX_3D *pVtx;//���_���ւ̃|�C���^
	//���_�o�b�t�@�����b�N�����_�f�[�^�̃|�C���^���擾
	g_pVtxBuffParticle->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		if (g_aParticle[nCntParticle].bUse == false)	//�p�[�e�B�N�����g�p����Ă��Ȃ�
		{
			g_aParticle[nCntParticle].pos = pos;
			g_aParticle[nCntParticle].fRadius = fRadius;
			g_aParticle[nCntParticle].nLife = nLife;
			g_aParticle[nCntParticle].ParticleType = type; 
			g_aParticle[nCntParticle].nTexType = 0;
			if (g_aParticle[nCntParticle].ParticleType == PARTICLE_TYPE_GOAL)
			{
				g_aParticle[nCntParticle].nTexType = 1;
			}

			RotRand = rand() % 30;
			RotRandY = rand() % 314;
			
			g_aParticle[nCntParticle].move.x += sinf(rot.y + RotRand) * move.x;
			g_aParticle[nCntParticle].move.y += tanf(rot.x + RotRandY) * move.y;
			g_aParticle[nCntParticle].move.z += cosf(rot.y + RotRand) * move.z;
			
			//if (g_aParticle[nCntParticle].move.y <= 0)
			//{
			//	g_aParticle[nCntParticle].move.y *= -1;
			//}

			ColRandR = rand() % 10;
			ColRandG = rand() % 10;
			ColRandB = rand() % 10;

			ColR += ColRandR;
			ColG += ColRandG;
			ColB += ColRandB;

			ColR = ColR / 10;
			ColG = ColG / 10;
			ColB = ColB / 10;

			D3DXCOLOR(ColR, ColG, ColB, 1.0f);

			g_aParticle[nCntParticle].col = col;

			if (type == PARTICLE_TYPE_GOAL)
			{
				//���_�J���[
				pVtx[0].col = D3DXCOLOR(ColR, ColG, ColB, 1.0f);
				pVtx[1].col = D3DXCOLOR(ColR, ColG, ColB, 1.0f);
				pVtx[2].col = D3DXCOLOR(ColR, ColG, ColB, 1.0f);
				pVtx[3].col = D3DXCOLOR(ColR, ColG, ColB, 1.0f);
			}
			if (type == PARTICLE_TYPE_PIZZA_DEATH)
			{
				//���_�J���[
				pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			}
			nParticleTotal++;
			g_aParticle[nCntParticle].bUse = true;

			//1��̃p�[�e�B�N���ő吔
			if (nParticleTotal >= 15)
			{
				nParticleTotal = 0;
				break;
			}		
		}
		pVtx += 4;	//���_�f�[�^�̃|�C���^��4���i�߂�	
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffParticle->Unlock();
}
