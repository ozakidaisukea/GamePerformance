//=============================================================================
//
// �|���S������ [Bullet.cpp]
// Author : Ozaki
//
//=============================================================================
#include "bullet.h"
//#include "shadow.h"
#include "Explosion.h"
#include "effect.h"
#include "model.h"
#include "Score.h"
#include "sound.h"
#include "Fade.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_FOER		(4)
#define BILLTEXTURENAME		"data\\TEXTURE\\bullet000.png"	// �e�N�X�`����
#define BULLET_MOVE		(20)
//#define MAX_SHADOW		(256)
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexBullet(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;		// ���_�o�b�t�@�̃|�C���^
LPDIRECT3DTEXTURE9		g_pTextureBullet = NULL;		// �e�N�X�`���ւ̃|�C���^
BULLET					g_aBullet[MAX_BULLET];

D3DXVECTOR3				aPos[4];
D3DXVECTOR3				VecA;
D3DXVECTOR3				VecB;
D3DXVECTOR3				VecC;
D3DXVECTOR3				BulletVtxMax;
D3DXVECTOR3				BulletVtxMin;

int						takumi;

//=============================================================================
// ����������
//=============================================================================
void InitBullet(void)
{
	//LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;	// �f�o�C�X�ւ̃|�C���^
	pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, BILLTEXTURENAME, &g_pTextureBullet);
	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(-10.0f, 15.0f, 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].nLife = 0;
		g_aBullet[nCntBullet].bUse = false;
	}

	// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MAX_FOER * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL);

	VERTEX_3D* pVtx; //���_���̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-2.0, 2.0, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(2.0, 2.0, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-2.0, 0.0, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(2.0, 0.0, 0.0f);

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
	g_pVtxBuffBullet->Unlock();

	//g_nIdxShadow2 = SetShadow(g_aBullet[MAX_BULLET].pos, g_aBullet[MAX_BULLET].move);

	aPos[0] = D3DXVECTOR3(-1000, 0, 1000);
	aPos[1] = D3DXVECTOR3(1000, 0, 1000);
	aPos[2] = D3DXVECTOR3(1000, 0, -1000);
	aPos[3] = D3DXVECTOR3(-1000, 0, -1000);

	BulletVtxMax = D3DXVECTOR3(2.0f, 2.0f, 1.0f);
	BulletVtxMin = D3DXVECTOR3(-2.0f, -2.0f, 0.0f);

	takumi = 0;
}

//=============================================================================
// �I������
//=============================================================================
void UninitBullet(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}

	if (g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBullet(void)
{
	int nCntBullet;

	VERTEX_3D*pVtx;	//���_���ւ̃|�C���^

	MODEL *pModel;
	pModel = GetModel();

	FADE Fade;
	Fade = GetFade();

	//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^�̎擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{
			g_aBullet[nCntBullet].posold = g_aBullet[nCntBullet].pos;

			g_aBullet[nCntBullet].pos += g_aBullet[nCntBullet].move;
			//SetPostionShadow(g_aBullet[nCntBullet].nIdxShadow, D3DXVECTOR3(g_aBullet[nCntBullet].pos.x, 0, g_aBullet[nCntBullet].pos.z));

			g_aBullet[nCntBullet].nLife--;

			// �e�̎���
			if (g_aBullet[nCntBullet].nLife <= 0)
			{
				g_aBullet[nCntBullet].bUse = false;
				//DeleteShadow(g_aBullet[nCntBullet].nIdxShadow);
				SetExplosion(g_aBullet[nCntBullet].pos, D3DXVECTOR3(0.0f,0.0f,0.0f),D3DXCOLOR(1.0f, 0.0f, 0.0f,1.0f));
			}

			if (pModel->bUse == true)
			{
				pModel->pos.x < g_aBullet[nCntBullet].pos.x && pModel->pos.x > g_aBullet[nCntBullet].pos.x
					&& pModel->pos.z < g_aBullet[nCntBullet].pos.z && pModel->pos.z > g_aBullet[nCntBullet].pos.z;
			}

			if (CollisionModel(&g_aBullet[nCntBullet].pos, &g_aBullet[nCntBullet].posold, &g_aBullet[nCntBullet].move,D3DXVECTOR3(10.0f, 10.0f, 10.0f), BulletVtxMax,BulletVtxMin,&g_aBullet[nCntBullet].pModel) == true)
			{
				g_aBullet[nCntBullet].bUse = false;
				SetExplosion(g_aBullet[nCntBullet].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
				AddScore(100);

				g_aBullet[nCntBullet].pModel->nLife -= 1;
						if (g_aBullet[nCntBullet].pModel->nLife <= 0)
						{
							SetExplosion(g_aBullet[nCntBullet].pModel->pos, g_aBullet[nCntBullet].pModel->rot,D3DXCOLOR(1.0f,0.0f,1.0,0.0f));
							PlaySound(SOUND_LABEL_SE_EXPLOSION);
							g_aBullet[nCntBullet].pModel->bUse = false;
							//AddScore(10000);
							//SetGameState(GAMESTATE_END);
							//SetFade(MODE_RESULT);
 							takumi++;
						}

						if (takumi == 4)
						{
							SetFade(MODE_RESULT);
						}
			}

			// �ǂ̓����蔻��
		/*	if (g_aBullet[nCntBullet].pos.x >= 1000)
			{
				g_aBullet[nCntBullet].pos.x = 1000 - 1;
				g_aBullet[nCntBullet].bUse = false;
				DeleteShadow(g_aBullet[nCntBullet].nIdxShadow);
				SetExplosion(g_aBullet[nCntBullet].pos, D3DXVECTOR3(1.0f, 0.0f, 0.0f));

			}
			if (g_aBullet[nCntBullet].pos.x <= -1000)
			{
				g_aBullet[nCntBullet].pos.x = -1000 - 1;
				g_aBullet[nCntBullet].bUse = false;
				DeleteShadow(g_aBullet[nCntBullet].nIdxShadow);
				SetExplosion(g_aBullet[nCntBullet].pos, D3DXVECTOR3(1.0f, 0.0f, 0.0f));
			}
			if (g_aBullet[nCntBullet].pos.z <= -1000)
			{
				g_aBullet[nCntBullet].pos.z = -1000 - 1;
				g_aBullet[nCntBullet].bUse = false;
				DeleteShadow(g_aBullet[nCntBullet].nIdxShadow);
				SetExplosion(g_aBullet[nCntBullet].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			}
			if (g_aBullet[nCntBullet].pos.z >= 1000)
			{
				g_aBullet[nCntBullet].pos.z = 1000 - 1;
				g_aBullet[nCntBullet].bUse = false;
				DeleteShadow(g_aBullet[nCntBullet].nIdxShadow);
				SetExplosion(g_aBullet[nCntBullet].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			}*/
			float fgsk[4];

			// ��
			VecA = aPos[0] - aPos[1];
			VecC = g_aBullet[nCntBullet].pos - aPos[0];
			fgsk[0] = ((VecA.z * VecC.x) - (VecA.x * VecC.z));
			if (fgsk[0] > 0)
			{
				g_aBullet[nCntBullet].bUse = false;
				//DeleteShadow(g_aBullet[nCntBullet].nIdxShadow);
				SetExplosion(g_aBullet[nCntBullet].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
			}

			// ��O
			VecA = aPos[0] - aPos[1];
			VecC = g_aBullet[nCntBullet].pos - aPos[0];
			fgsk[1] = ((VecA.z * VecC.x) - (VecA.x * VecC.z));
			if (fgsk[1] > 0)
			{
				g_aBullet[nCntBullet].bUse = false;
				//DeleteShadow(g_aBullet[nCntBullet].nIdxShadow);
				SetExplosion(g_aBullet[nCntBullet].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
			}

			// �E
			VecA = aPos[0] - aPos[1];
			VecC = g_aBullet[nCntBullet].pos - aPos[0];
			fgsk[2] = ((VecA.z * VecC.x) - (VecA.x * VecC.z));
			if (fgsk[2] > 0)
			{
				g_aBullet[nCntBullet].bUse = false;
				//DeleteShadow(g_aBullet[nCntBullet].nIdxShadow);
				SetExplosion(g_aBullet[nCntBullet].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
			}

			// ��
			VecA = aPos[0] - aPos[1];
			VecC = g_aBullet[nCntBullet].pos - aPos[0];
			fgsk[3] = ((VecA.z * VecC.x) - (VecA.x * VecC.z));
			if (fgsk[3] > 0)
			{
				g_aBullet[nCntBullet].bUse = false;
				//DeleteShadow(g_aBullet[nCntBullet].nIdxShadow);
				SetExplosion(g_aBullet[nCntBullet].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
			}

			VecA = aPos[0] - aPos[1];
			VecC = g_aBullet[nCntBullet].pos - aPos[0];
			fgsk[0] = ((VecA.z * VecC.x) - (VecA.x * VecC.z));
			if (fgsk[0] > 0)
			{
				g_aBullet[nCntBullet].bUse = false;
			//	DeleteShadow(g_aBullet[nCntBullet].nIdxShadow);
				SetExplosion(g_aBullet[nCntBullet].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
			}
			SetEffect(g_aBullet[nCntBullet].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, 0);
		}

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffBullet->Unlock();


}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans, mtxView;
	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{

		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_aBullet[nCntBullet].mtxWorld);

		//
		pDevice->GetTransform(D3DTS_VIEW, &mtxView);
		g_aBullet[nCntBullet].mtxWorld._11 = mtxView._11;
		g_aBullet[nCntBullet].mtxWorld._12 = mtxView._21;
		g_aBullet[nCntBullet].mtxWorld._13 = mtxView._31;
		g_aBullet[nCntBullet].mtxWorld._21 = mtxView._12;
		g_aBullet[nCntBullet].mtxWorld._22 = mtxView._22;
		g_aBullet[nCntBullet].mtxWorld._23 = mtxView._32;
		g_aBullet[nCntBullet].mtxWorld._31 = mtxView._13;
		g_aBullet[nCntBullet].mtxWorld._32 = mtxView._23;
		g_aBullet[nCntBullet].mtxWorld._33 = mtxView._33;

		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_aBullet[nCntBullet].pos.x, g_aBullet[nCntBullet].pos.y, g_aBullet[nCntBullet].pos.z);
		D3DXMatrixMultiply(&g_aBullet[nCntBullet].mtxWorld, &g_aBullet[nCntBullet].mtxWorld, &mtxTrans);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_aBullet[nCntBullet].mtxWorld);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureBullet);

		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

		if (g_aBullet[nCntBullet].bUse == true)
		{
			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0 + (4 * nCntBullet), 2);
		}

		// �����_�[�X�e�[�g�����ɖ߂�
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	}
}
//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexBullet(LPDIRECT3DDEVICE9 pDevice)
{

}
//=============================================================================
// �ǂ̐ݒ�ʒu
//=============================================================================
void SetBullet(D3DXVECTOR3 posbullet, D3DXVECTOR3 rotbullet, D3DXVECTOR3 movebullet )
{
	int nCntBullet;


	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == false)
		{
			g_aBullet[nCntBullet].pos = posbullet;
			g_aBullet[nCntBullet].move = movebullet;
 		//	g_aBullet[nCntBullet].nIdxShadow = SetShadow(g_aBullet[nCntBullet].pos, D3DXVECTOR3(0.0,0.0,0.0f));
			g_aBullet[nCntBullet].nLife = 100;
			g_aBullet[nCntBullet].bUse = true;
			break;
		}
	}
}