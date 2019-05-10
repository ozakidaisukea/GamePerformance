//=============================================================================
//
// �|���S������ [Bullet.cpp]
// Author : Meguro Mikiya
//
//=============================================================================
#include "bullet.h"
#include "shadow.h"
#include "model.h"
#include "explosion.h"
#include "effect.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define BULLET_TEXTURENAME		 "data\\TEXTURE\\bullet000.png"			//�e�N�X�`���̃t�@�C����
#define TEX_POS_X_INIT			(1.0f)									//�e�N�X�`�����WU�̏����ʒu
#define TEX_POS_Y_INIT			(1.0f)									//�e�N�X�`�����WV�̏����ʒu
#define TEX_LEFT				(0.0f)									//�e�N�X�`�����WU��
#define TEX_RIGHT				(1.0f)									//�e�N�X�`�����WU�E
#define TEX_TOP					(0.0f)									//�e�N�X�`�����WV��
#define TEX_BOT					(1.0f)									//�e�N�X�`�����WV��
#define MAX_BULLET				(100)									//�e�̍ő吔
#define EFFECT_COLOR_PLAYER		(D3DXCOLOR (0.3f, 0.8f, 0.8f, 1.0f))	//���@�̒e�̃G�t�F�N�g�J���[
#define EFFECT_RADIUS_PLAYER	(10.0f)									//�G�t�F�N�g�̔��a
#define EFFECT_LIFE_PLAYER		(10)									//�G�t�F�N�g�̃��C�t


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexBullet(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;	//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9	g_pTextureBullet = NULL;		//�e�N�X�`���ւ̃|�C���^
BULLET g_aBullet[MAX_BULLET];

//=============================================================================
// ����������
//=============================================================================
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;	// �f�o�C�X�̎擾
	pDevice = GetDevice();	// �f�o�C�X�̎擾

	//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			BULLET_TEXTURENAME,
			&g_pTextureBullet);
	// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL);

	VERTEX_3D *pVtx;
	//���_�o�b�t�@�����b�N
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		//���_���W
		pVtx[0].pos = D3DXVECTOR3(-10.0f, 10.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(10.0f, 10.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-10.0f, -10.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(10.0f, -10.0f, 0.0f);

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

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].fRadius = 0.0f;
		g_aBullet[nCntBullet].fHeght = 0.0f;
		g_aBullet[nCntBullet].fWidth = 0.0f;
		g_aBullet[nCntBullet].nLife = 200;
		g_aBullet[nCntBullet].bUse = false;
		g_aBullet[nCntBullet].VtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].VtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBullet->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void UninitBullet(void)
{	//�e�N�X�`���̔j��
	if (g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBullet(void)
{
	VERTEX_3D *pVtx;//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N�����_�f�[�^�̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)	//�e���g�p����Ă���
		{
			g_aBullet[nCntBullet].posold = g_aBullet[nCntBullet].pos;
			g_aBullet[nCntBullet].pos.x += g_aBullet[nCntBullet].move.x;
			g_aBullet[nCntBullet].pos.y += g_aBullet[nCntBullet].move.y;
			g_aBullet[nCntBullet].pos.z += g_aBullet[nCntBullet].move.z;
			//�G�t�F�N�g�`��
			SetEffect(g_aBullet[nCntBullet].pos, EFFECT_COLOR_PLAYER, EFFECT_RADIUS_PLAYER, EFFECT_LIFE_PLAYER);

			g_aBullet[nCntBullet].nLife--;

			//�e�̃��C�t���s�����������
			if (g_aBullet[nCntBullet].nLife <= 0)
			{
				g_aBullet[nCntBullet].bUse = false;
				DeleteShadow(g_aBullet[nCntBullet].nIdxShadow);
				SetExplosion(g_aBullet[nCntBullet].pos, D3DXCOLOR(1.0f, 0.7f, 0.1f, 1.0f), 15.0f, 15.0f);
			}
			//�u���b�N�Ƃ̓����蔻��
			if (CollisionModel(&g_aBullet[nCntBullet].pos, &g_aBullet[nCntBullet].posold, &g_aBullet[nCntBullet].move, g_aBullet[nCntBullet].VtxMax, g_aBullet[nCntBullet].VtxMin) == true)
			{
				g_aBullet[nCntBullet].bUse = false;
				DeleteShadow(g_aBullet[nCntBullet].nIdxShadow);
				SetExplosion(g_aBullet[nCntBullet].pos, D3DXCOLOR(1.0f, 0.1f, 0.1f, 1.0f), 15.0f, 15.0f);

			}
			//�ǂƂ̓����蔻��
			if (FIELD_SIZE < g_aBullet[nCntBullet].pos.x)
			{
				g_aBullet[nCntBullet].bUse = false;
				DeleteShadow(g_aBullet[nCntBullet].nIdxShadow);
				SetExplosion(g_aBullet[nCntBullet].pos, D3DXCOLOR(1.0f, 0.7f, 0.1f, 1.0f), 15.0f, 15.0f);

			}
			if (-FIELD_SIZE > g_aBullet[nCntBullet].pos.x)
			{
				g_aBullet[nCntBullet].bUse = false;
				DeleteShadow(g_aBullet[nCntBullet].nIdxShadow);
				SetExplosion(g_aBullet[nCntBullet].pos, D3DXCOLOR(1.0f, 0.7f, 0.1f, 1.0f), 15.0f, 15.0f);

			}
			if (FIELD_SIZE < g_aBullet[nCntBullet].pos.z)
			{
				g_aBullet[nCntBullet].bUse = false;
				DeleteShadow(g_aBullet[nCntBullet].nIdxShadow);
				SetExplosion(g_aBullet[nCntBullet].pos, D3DXCOLOR(1.0f, 0.7f, 0.1f, 1.0f), 15.0f, 15.0f);

			}
			if (-FIELD_SIZE > g_aBullet[nCntBullet].pos.z)
			{
				g_aBullet[nCntBullet].bUse = false;
				DeleteShadow(g_aBullet[nCntBullet].nIdxShadow);
				SetExplosion(g_aBullet[nCntBullet].pos, D3DXCOLOR(1.0f, 0.7f, 0.1f, 1.0f), 15.0f, 15.0f);

			}

			SetPositionShadow(g_aBullet[nCntBullet].nIdxShadow,
				D3DXVECTOR3(g_aBullet[nCntBullet].pos.x, 0, g_aBullet[nCntBullet].pos.z), 5);
		}
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBullet->Unlock();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX  mtxView, mtxTrans;				//�v�Z�p�}�g���b�N�X
	
	//�A���t�@�e�X�g(�����F��`�悵�Ȃ��悤��)
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	//Z�o�b�t�@�̐ݒ�
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_aBullet[nCntBullet].mtrxWorldBullet);
		//�r���[�}�g���b�N�X���擾
		pDevice->GetTransform(D3DTS_VIEW, &mtxView);
		//�t�s���ݒ�
		g_aBullet[nCntBullet].mtrxWorldBullet._11 = mtxView._11;
		g_aBullet[nCntBullet].mtrxWorldBullet._12 = mtxView._21;
		g_aBullet[nCntBullet].mtrxWorldBullet._13 = mtxView._31;
		g_aBullet[nCntBullet].mtrxWorldBullet._21 = mtxView._12;
		g_aBullet[nCntBullet].mtrxWorldBullet._22 = mtxView._22;
		g_aBullet[nCntBullet].mtrxWorldBullet._23 = mtxView._32;
		g_aBullet[nCntBullet].mtrxWorldBullet._31 = mtxView._13;
		g_aBullet[nCntBullet].mtrxWorldBullet._32 = mtxView._23;
		g_aBullet[nCntBullet].mtrxWorldBullet._33 = mtxView._33;
		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_aBullet[nCntBullet].pos.x, g_aBullet[nCntBullet].pos.y, g_aBullet[nCntBullet].pos.z);
		D3DXMatrixMultiply(&g_aBullet[nCntBullet].mtrxWorldBullet, &g_aBullet[nCntBullet].mtrxWorldBullet, &mtxTrans);
		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_aBullet[nCntBullet].mtrxWorldBullet);
		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_3D));
		//���_�t�H�[�}�b�g��ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureBullet);

		if (g_aBullet[nCntBullet].bUse == true)	//�e���g�p����Ă���
		{
			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				0 + (4 * nCntBullet),	//�J�n���钸�_�̃C���f�b�N�X
				2); //�`�悷��v���~�e�B�u��
		}
	}
	//�����_�[�X�e�[�g�̐ݒ�����ɖ߂�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	//Z�o�b�t�@���f�t�H���g�̐ݒ�ɖ߂�
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexBullet(LPDIRECT3DDEVICE9 pDevice)
{
	// ���_�o�b�t�@�𐶐�


	// ���_���̐ݒ�

}

//=============================================================================
// �e�̐ݒ菈��
//=============================================================================
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fHeght, float fWidth)
{
	int nCntBullet;
	VERTEX_3D *pVtx;//���_���ւ̃|�C���^
					//���_�o�b�t�@�����b�N�����_�f�[�^�̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == false)	//�e���g�p����Ă��Ȃ�
		{
			g_aBullet[nCntBullet].pos = pos;
			g_aBullet[nCntBullet].move = move;
			g_aBullet[nCntBullet].fHeght= fHeght;
			g_aBullet[nCntBullet].fWidth = fWidth;
			//���_���W
			pVtx[0].pos = D3DXVECTOR3(-g_aBullet[nCntBullet].fWidth, g_aBullet[nCntBullet].fHeght, 0);
			pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].fWidth, g_aBullet[nCntBullet].fHeght, 0);
			pVtx[2].pos = D3DXVECTOR3(-g_aBullet[nCntBullet].fWidth, -g_aBullet[nCntBullet].fHeght, 0);
			pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].fWidth, -g_aBullet[nCntBullet].fHeght, 0);
			//�@�e�̃Z�b�g
			g_aBullet[nCntBullet].nIdxShadow = SetShadow(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0),
				5);
			g_aBullet[nCntBullet].nLife = 100;
			g_aBullet[nCntBullet].bUse = true;
			g_aBullet[nCntBullet].bShadowUse = true;
			g_aBullet[nCntBullet].VtxMax = D3DXVECTOR3(fWidth, 0, 10);
			g_aBullet[nCntBullet].VtxMin = D3DXVECTOR3(-fWidth, 0, -10);
			break;
		}
		pVtx += 4;	//���_�f�[�^�̃|�C���^��4���i�߂�	
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBullet->Unlock();
}
