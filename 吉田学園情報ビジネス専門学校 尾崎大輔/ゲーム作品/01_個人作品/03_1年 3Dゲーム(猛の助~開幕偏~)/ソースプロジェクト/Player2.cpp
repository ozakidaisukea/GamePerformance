//=============================================================================
//
// ���f������ [Player2.cpp]
// Author : Ozaki
//
//=============================================================================
#include "Player2.h"
#include "Input.h"
#include "camera.h"
#include "shadow.h"
#include "bullet.h"
#include "Explosion.h"
#include "effect.h"
#include "particle.h"
#include "model.h"
#include "sound.h"
#include "Fade.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MOVE_PLAYER2	(0.5f)
#define MOVE_BULLET		(8.0f)
#define MAX_PLAYER2		(2)
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9  g_pVtxBuffPlayer2 = NULL;	// ���_�o�b�t�@�̃|�C���^
LPD3DXMESH				 g_pMeshPlayer2 = NULL;		// ���b�V�����ւ̃|�C���^
LPD3DXBUFFER			 g_BuffMatPlayer2 = NULL;	// �}�e���A�����ւ̃|�C���^
D3DXVECTOR3				 g_vtxMinplayer2, g_vtxMaxplayer2;
DWORD					 g_nNumMatPlayer2 = 0;		// �}�e���A�����̐�
D3DXMATRIX				 g_mtxWorldPlayer2;			// ���[���h�}�g���b�N�X
Player2					 g_Player2;					// �v���C���[
int						 g_nIdxShadow22;
int						 g_nNumBoss;
//D3DXVECTOR3				 aPos[4];
//D3DXVECTOR3				 VecA;
//D3DXVECTOR3				 VecB;
//D3DXVECTOR3			 	 VecC;

D3DXVECTOR3				Player2VtxMax;
D3DXVECTOR3				Player2VtxMin;

//=============================================================================
// ����������
//=============================================================================
void InitPlayer2(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	MODE Mode = GetMode();

	switch (Mode)
	{
	case MODE_TITLE:
	{
		g_Player2.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	}
	break;
	case MODE_GAME:
	{
		g_Player2.pos = D3DXVECTOR3(0.0f, 0.0f, 800.0f);
	}
	break;

	}

	g_Player2.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player2.posold = D3DXVECTOR3(0.0f, 0.0f, 800.0f);
	g_Player2.bUse = true;
	g_Player2.nCounterState = 0;
	g_Player2.nLife = 1;
	g_Player2.aModel[2];

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("data\\MODEL\\Institute.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Player2.aModel[0].pBuffMat,
		NULL,
		&g_Player2.aModel[0].nNumMat,
		&g_Player2.aModel[0].pMesh);

	D3DXLoadMeshFromX("data\\MODEL\\hakasez.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Player2.aModel[1].pBuffMat,
		NULL,
		&g_Player2.aModel[1].nNumMat,
		&g_Player2.aModel[1].pMesh);

	// �ʒu�E�����̏����ݒ�

	//g_nIdxShadow22 = SetShadow(g_Player2.pos, g_Player2.rot);

	g_Player2.aModel[0].nIdxModelParent = -1;
	g_Player2.aModel[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	g_Player2.aModel[1].nIdxModelParent = 0;
	g_Player2.aModel[1].pos = D3DXVECTOR3(0.0f, 0.0f, -50.0f);

	int						 nNumVtx;					// ���_��

	DWORD					 sizeFVF;					// ���_�t�H�[�}�b�g�̐ݒ�
	BYTE					 *pVtxBuff;					// ���_�o�b�n�ւ̃|�C���^���擾

	nNumVtx = g_Player2.aModel[0].pMesh->GetNumVertices();

	sizeFVF = D3DXGetFVFVertexSize(g_Player2.aModel[0].pMesh->GetFVF());

	g_vtxMinplayer2 = D3DXVECTOR3(10000.0f, 10000.0f, 10000.0f);
	g_vtxMaxplayer2 = D3DXVECTOR3(-10000.0f, -10000.0f, -10000.0f);

	// ���_�o�b�t�@�����b�N���A
	g_Player2.aModel[0].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	// ���_���W�̑��

		if (g_vtxMaxplayer2.x < vtx.x)
		{
			g_vtxMaxplayer2.x = vtx.x;
		}
		if (g_vtxMaxplayer2.y < vtx.y)
		{
			g_vtxMaxplayer2.y = vtx.y;
		}
		if (g_vtxMaxplayer2.z < vtx.z)
		{
			g_vtxMaxplayer2.z = vtx.z;
		}

		// min
		if (g_vtxMinplayer2.x > vtx.x)
		{
			g_vtxMinplayer2.x = vtx.x;
		}
		if (g_vtxMinplayer2.y > vtx.y)
		{
			g_vtxMinplayer2.y = vtx.y;
		}
		if (g_vtxMinplayer2.z > vtx.z)
		{
			g_vtxMinplayer2.z = vtx.z;
		}


		pVtxBuff += sizeFVF;							// �T�C�Y���|�C���^��i�߂�

	}
	// ���_�o�b�t�@���A�����b�N����
	g_Player2.aModel[0].pMesh->UnlockVertexBuffer();


	Player2VtxMax = D3DXVECTOR3(2.0f, 2.0f, 1.0f);
	Player2VtxMin = D3DXVECTOR3(-2.0f, -2.0f, 0.0f);

}

//=============================================================================
// �I������
//=============================================================================
void UninitPlayer2(void)
{

	for (int nCnt = 0; nCnt < MAX_PLAYER2; nCnt++)
	{

		// ���b�V���̊J��
		if (g_Player2.aModel[nCnt].pMesh != NULL)
		{
			g_Player2.aModel[nCnt].pMesh->Release();

			g_Player2.aModel[nCnt].pMesh = NULL;
		}

		// �}�e���A���̊J��
		if (g_Player2.aModel[nCnt].pBuffMat != NULL)
		{
			g_Player2.aModel[nCnt].pBuffMat->Release();

			g_Player2.aModel[nCnt].pBuffMat = NULL;
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePlayer2(void)
{
	MODE Mode = GetMode();


	MODEL *pModel;
	pModel = GetModel();


	switch (Mode)
	{
	case MODE_TITLE:
	{
		g_Player2.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	}
	break;

	case MODE_GAME:
	{
		if (g_Player2.bUse == true)
		{// ���m���g�p����Ă���
			g_Player2.posold = D3DXVECTOR3(0.0f, 0.0f, 600.0f);
			if (CollisionModel(&g_Player2.pos, &g_Player2.posold, &g_Player2.move, D3DXVECTOR3(50.0f, 20.0f, 70.0f), Player2VtxMax, Player2VtxMin, &g_Player2.pModel) == true)
			{
				SetExplosion(g_Player2.pos * 100.0f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(255, 0, 0, 0.0f));
				PlaySound(SOUND_LABEL_SE_EXPLOSION);
				FADE Fade;
				Fade = GetFade();
				if (Fade == FADE_NONE)
				{

					SetFade(MODE_GAMEOVER);
					PlaySound(SOUND_LABEL_SE_SAKEBI);
				}
				g_Player2.bUse = false;
				/*g_Player2.pModel->nLife -= 1;
				if (pModel->nLife <= 0)
				{
					SetExplosion(g_Player2.pModel->pos, g_Player2.pModel->rot, D3DXCOLOR(1.0f, 0.0f, 1.0, 0.0f));*/

					//g_Player2.pos.x += g_Player2.move.x;
					//g_Player2.pos.y += g_Player2.move.y;
					//g_Player2.pos.z += g_Player2.move.z;

					//g_Player2.move.x += (0.0f - g_Player2.move.x) *0.4f;
					//g_Player2.move.y += (0.0f - g_Player2.move.y) *0.4f;
					//g_Player2.move.z += (0.0f - g_Player2.move.z) *0.4f;

					//if (g_Player2.pos.x >= 950)
					//{
					//	g_Player2.pos.x = 950 - 1;
					//}
					//if (g_Player2.pos.x <= -950)
					//{
					//	g_Player2.pos.x = -950 - 1;
					//}
					//if (g_Player2.pos.z <= -950)
					//{
					//	g_Player2.pos.z = -950 - 1;
					//}
					//if (g_Player2.pos.z >= 950)
					//{
					//	g_Player2.pos.z = 950 - 1;
					//}

					//g_Player2.bDisp = false;
					//SetExplosion(g_Player2.pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
			}
			if (g_Player2.pos.y < 1.0f)
			{
				g_Player2.pos.y = 1;
			}


			//SetPostionShadow(g_nIdxShadow22, D3DXVECTOR3(g_Player2.pos.x, 0, g_Player2.pos.z));

			/*SetEffect(g_Player2.pos.x, 0, g_Player2.move.x);*/
		}
	}
		break;

	}


}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPlayer2(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX		mtxRot, mtxTrans;				// �v�Z�p�̃}�g���b�N�X
	D3DMATERIAL9	matDef;							// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL	*pMat;							// �}�e���A���f�[�^�ւ̃|�C���^
	D3DXMATRIX		mtxParent;

	if (g_Player2.bUse == true)
	{// ���m���g�p����Ă���
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_Player2.mtxWorld);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player2.rot.y, g_Player2.rot.x, g_Player2.rot.z);
		D3DXMatrixMultiply(&g_Player2.mtxWorld, &g_Player2.mtxWorld, &mtxRot);

		// �ړ��𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_Player2.pos.x, g_Player2.pos.y, g_Player2.pos.z);
		D3DXMatrixMultiply(&g_Player2.mtxWorld, &g_Player2.mtxWorld, &mtxTrans);


		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_Player2.mtxWorld);

		for (int nCnt = 0; nCnt < MAX_PLAYER2; nCnt++)
		{
			if (g_Player2.aModel[0].nIdxModelParent == -1)
			{
				mtxParent = g_Player2.mtxWorld;
			}
			else
			{
				mtxParent = g_Player2.aModel[g_Player2.aModel[nCnt].nIdxModelParent].mtxWorld;
			}

			//if (g_Player2.aModel[1].nIdxModelParent == 0)
			//{
			//	mtxParent = g_Player2.mtxWorld;
			//}
			//else
			//{
			//	mtxParent = g_Player2.aModel[1].mtxWorld;
			//}

			//=============================================================================
			// ���f���i�e�j
			//=============================================================================

			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Player2.aModel[nCnt].mtxWorld);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player2.aModel[nCnt].rot.y, g_Player2.aModel[nCnt].rot.x, g_Player2.aModel[nCnt
			].rot.z);
			D3DXMatrixMultiply(&g_Player2.aModel[nCnt].mtxWorld, &g_Player2.aModel[nCnt].mtxWorld, &mtxRot);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_Player2.aModel[nCnt].pos.x, g_Player2.aModel[nCnt].pos.y, g_Player2.aModel[nCnt].pos.z);
			D3DXMatrixMultiply(&g_Player2.aModel[nCnt].mtxWorld, &g_Player2.aModel[nCnt].mtxWorld, &mtxTrans);


			D3DXMatrixMultiply(&g_Player2.aModel[nCnt].mtxWorld, &g_Player2.aModel[nCnt].mtxWorld, &mtxParent);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Player2.aModel[nCnt].mtxWorld);

			// ���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			// �}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_Player2.aModel[nCnt].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_Player2.aModel[nCnt].nNumMat; nCntMat++)
			{
				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				pDevice->SetTexture(0, NULL);

				// ���f��(�p�[�c)�̕`��
				g_Player2.aModel[nCnt].pMesh->DrawSubset(nCntMat);

			}

			// �}�e���A�����f�t�H���g�ɖ߂�
			pDevice->SetMaterial(&matDef);
		}
	}
}

//=============================================================================
// ���f���̎擾
//=============================================================================
Player2 *GetPlayer2(void)
{
	return &g_Player2;
}

//=============================================================================
// �v���C���[�̓����蔻��
//=============================================================================
bool CollisionPlayer2(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 radius, MODEL **pPlayer2)
{
	bool bLand = false;  // ��������ǂ���

						 /*Model1 *pPlayer = GetPlayer();*/

	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{// ��Q���̐������J��Ԃ�
		if (g_Player2.bUse == true)
		{// ��Q�����g�p����Ă���
			if (pPos->y <= g_Player2.pos.y + g_Player2.VtxMaxModel.y && pPos->y + radius.y > g_Player2.pos.y + g_Player2.VtxMinModel.y
				|| pPos->y + radius.y > g_Player2.pos.y + g_Player2.VtxMaxModel.y && pPos->y < g_Player2.pos.y + g_Player2.VtxMinModel.y
				|| pPos->y + radius.y > g_Player2.pos.y + g_Player2.VtxMaxModel.y && pPos->y < g_Player2.pos.y + g_Player2.VtxMinModel.y)
			{// ��Q����Y���W�̒��ɂ���
				if (pPos->z - radius.z <= g_Player2.pos.z + g_Player2.VtxMaxModel.z && pPos->z + radius.z >= g_Player2.pos.z + g_Player2.VtxMinModel.z)
				{// ��Q����Z���W�̒��ɂ���
					if (pPosOld->x + radius.x <= g_Player2.pos.x + g_Player2.VtxMinModel.x
						&& pPos->x + radius.x > g_Player2.pos.x + g_Player2.VtxMinModel.x)
					{// X���W�̒��ɍ����������
					 // ���˕Ԃ�
						g_Player2.move.x += pMove->x + 5;

						pPos->x = g_Player2.pos.x + g_Player2.VtxMinModel.x - radius.x;
						pMove->x = -4.0f;
						SetExplosion(g_Player2.pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(255, 255, 255,0.0f));






						bLand = true;

					}
					else if (pPosOld->x - radius.x >= g_Player2.pos.x + g_Player2.VtxMaxModel.x
						&& pPos->x - radius.x < g_Player2.pos.x + g_Player2.VtxMaxModel.x)
					{// X���W�̒��ɉE���������
					 // ���˕Ԃ�
						g_Player2.move.x += pMove->x - 5;

						pPos->x = g_Player2.pos.x + g_Player2.VtxMaxModel.x + radius.x + 0.1f;
						pMove->x = 4.0f;

						bLand = true;
					}
				}
				if (pPos->x - radius.x <= g_Player2.pos.x + g_Player2.VtxMaxModel.x && pPos->x + radius.x >= g_Player2.pos.x + g_Player2.VtxMinModel.x)
				{// ��Q����X���W�̒��ɂ���
					if (pPosOld->z + radius.z <= g_Player2.pos.z + g_Player2.VtxMinModel.z
						&& pPos->z + radius.z > g_Player2.pos.z + g_Player2.VtxMinModel.z)
					{// Z���W�̒��ɑO���������
					 // ���˕Ԃ�
						g_Player2.move.z += pMove->z + 5;

						pPos->z = g_Player2.pos.z + g_Player2.VtxMinModel.z - radius.z;
						pMove->z = -4.0f;
						SetExplosion(g_Player2.pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(255, 255, 255, 0.0f));

						bLand = true;
					}
					else if (pPosOld->z - radius.z >= g_Player2.pos.z + g_Player2.VtxMaxModel.z
						&& pPos->z - radius.z < g_Player2.pos.z + g_Player2.VtxMaxModel.z)
					{// Z���W�̒��Ɍ�납�������
					 // ���˕Ԃ�
						g_Player2.move.z += pMove->z - 5;

						pPos->z = g_Player2.pos.z + g_Player2.VtxMaxModel.z + radius.z + 0.1f;
						pMove->z = 4.0f;

						bLand = true;
					}
				}

				//if (pPos->x - radius.x < g_Player2.pos.x + g_Player2.VtxMaxModel.x - 2.0f&& pPos->x + radius.x > g_Player2.pos.x + g_Player2.VtxMinModel.x + 2.0f
				//	&& pPos->z - radius.z <= g_Player2.pos.z + g_Player2.VtxMaxModel.z - 2.0f && pPos->z + radius.z >= g_Player2.pos.z + g_Player2.VtxMinModel.z + 2.0f)
				//{// ��Q���̓����ɏ����
				//	bLand = true;  // ����������Ԃ�
				//	pPos->y = g_Player2.pos.y + g_Player2.VtxMaxModel.y;
				//	pMove->y = 0.0f;  // �ړ��ʂ��Ȃ���
				//}
			}
		}
	}

	return bLand;   // ��������ǂ�����Ԃ�
}

void HitPlayer(int nCntPlayer, int nDamage)
{

	FADE Fade;
	Fade = GetFade();

	g_Player2.nLife -= nDamage;
	if (g_Player2.nLife <= 0)
	{
		SetExplosion(g_Player2.pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		PlaySound(SOUND_LABEL_SE_SAKEBI);
		g_Player2.bUse = false;
		g_nNumBoss--;				//�G�̑��������炷
		if (g_nNumBoss <= 0)
		{
			SetFade(MODE_GAMEOVER);
		}
	}
}