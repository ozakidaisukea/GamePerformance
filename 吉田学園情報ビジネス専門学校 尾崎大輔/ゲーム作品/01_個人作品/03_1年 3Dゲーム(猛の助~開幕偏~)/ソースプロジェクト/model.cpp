//=============================================================================
//
// ���f������ [model.cpp]
// Author : Meguro Mikiya
//
//=============================================================================
#include "model.h"
#include "input.h"
#include "shadow.h"
#include "camera.h"
#include "bullet.h"
#include "polygon.h"
#include "player.h"
#include "player2.h"
#include "game.h"
#include "explosion.h"
#include "Fade.h"
#include "sound.h"

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPD3DXMESH g_pMeshModel[MAX_MODEL_TYPE];						//���b�V�����ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatModel[MAX_MODEL_TYPE];				//�}�e���A�����ւ̃|�C���^
LPDIRECT3DTEXTURE9	g_pTextureModel[MAX_MODEL_TYPE];			//�e�N�X�`���ւ̃|�C���^
DWORD g_nNumMatModel[MAX_MODEL_TYPE] = {};					//�}�e���A�����̐�
MODEL g_aModel[MAX_MODEL];
D3DXMATERIAL *g_pMat;
VTX g_aModelVtx[MAX_MODEL_TYPE];

int						takumi1;

//=============================================================================
// ����������
//=============================================================================
void InitModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(MODEL_NAME000,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatModel[0],
		NULL,
		&g_nNumMatModel[0],
		&g_pMeshModel[0]);

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(MODEL_NAME001,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatModel[1],
		NULL,
		&g_nNumMatModel[1],
		&g_pMeshModel[1]);

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(MODEL_NAME002,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatModel[2],
		NULL,
		&g_nNumMatModel[2],
		&g_pMeshModel[2]);

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(MODEL_NAME003,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatModel[3],
		NULL,
		&g_nNumMatModel[3],
		&g_pMeshModel[3]);

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(MODEL_NAME004,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatModel[4],
		NULL,
		&g_nNumMatModel[4],
		&g_pMeshModel[4]);


	int nNumVtex;	//���_��
	DWORD sizeFvF;	//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff[MAX_MODEL];	//���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 vtx[MAX_MODEL];

	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		g_aModel[nCntModel].VtxMinModel = D3DXVECTOR3(10000, 0, 10000);
		g_aModel[nCntModel].VtxMaxModel = D3DXVECTOR3(-10000, 0, -10000);
		g_aModel[nCntModel].nType = 0;
		g_aModel[nCntModel].bUse = false;
		g_aModel[nCntModel].nLife = 20;
		g_aModel[nCntModel].fDistangle = 0;
		g_aModel[nCntModel].fDiftangle = 0;
		g_aModel[nCntModel].move = D3DXVECTOR3(0.0f,0.0f,0.0f);

	}
	for (int nCntTypeModel = 0; nCntTypeModel < MAX_MODEL_TYPE; nCntTypeModel++)
	{
		g_aModelVtx[nCntTypeModel].VtxMaxModel = D3DXVECTOR3(-10000, 0, -10000);
		g_aModelVtx[nCntTypeModel].VtxMinModel = D3DXVECTOR3(10000, 0, 10000);
	}

#if 0
	for (int nCntTypeModel = 0; nCntTypeModel < MAX_MODEL_TYPE; nCntTypeModel++)
	{
		//���_�����擾
		nNumVtex = g_pMeshModel[nCntTypeModel]->GetNumVertices();
		//���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFvF = D3DXGetFVFVertexSize(g_pMeshModel[nCntTypeModel]->GetFVF());
		for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
		{
			//���_�@���b�N
			g_pMeshModel[nCntTypeModel]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff[nCntModel]);
			for (int nCntVtx = 0; nCntVtx < nNumVtex; nCntVtx++)
			{	//���_���W�̑��
				D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff[nCntModel];
				if (g_aModel[nCntModel].VtxMinModel.x > vtx.x)
				{
					g_aModel[nCntModel].VtxMinModel.x = vtx.x;
				}
				if (g_aModel[nCntModel].VtxMinModel.y > vtx.y)
				{
					g_aModel[nCntModel].VtxMinModel.y = vtx.y;
				}
				if (g_aModel[nCntModel].VtxMinModel.z > vtx.z)
				{
					g_aModel[nCntModel].VtxMinModel.z = vtx.z;
				}

				if (g_aModel[nCntModel].VtxMaxModel.x < vtx.x)
				{
					g_aModel[nCntModel].VtxMaxModel.x = vtx.x;
				}
				if (g_aModel[nCntModel].VtxMaxModel.y < vtx.y)
				{
					g_aModel[nCntModel].VtxMaxModel.y = vtx.y;
				}
				if (g_aModel[nCntModel].VtxMaxModel.z < vtx.z)
				{
					g_aModel[nCntModel].VtxMaxModel.z = vtx.z;
				}
				pVtxBuff[nCntModel] += sizeFvF;
			}
			//			//���_�o�b�t�@���A�����b�N
			g_pMeshModel[nCntTypeModel]->UnlockVertexBuffer();
		}
	}

#endif
	for (int nCntTypeModel = 0; nCntTypeModel < MAX_MODEL_TYPE; nCntTypeModel++)
	{
		//���_�����擾
		nNumVtex = g_pMeshModel[nCntTypeModel]->GetNumVertices();
		//���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFvF = D3DXGetFVFVertexSize(g_pMeshModel[nCntTypeModel]->GetFVF());
		//���_�@���b�N
		g_pMeshModel[nCntTypeModel]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff[nCntTypeModel]);
		for (int nCntVtx = 0; nCntVtx < nNumVtex; nCntVtx++)
		{	//���_���W�̑��
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff[nCntTypeModel];
			if (g_aModelVtx[nCntTypeModel].VtxMinModel.x > vtx.x)
			{
				g_aModelVtx[nCntTypeModel].VtxMinModel.x = vtx.x;
			}
			if (g_aModelVtx[nCntTypeModel].VtxMinModel.y > vtx.y)
			{
				g_aModelVtx[nCntTypeModel].VtxMinModel.y = vtx.y;
			}
			if (g_aModelVtx[nCntTypeModel].VtxMinModel.z > vtx.z)
			{
				g_aModelVtx[nCntTypeModel].VtxMinModel.z = vtx.z;
			}

			if (g_aModelVtx[nCntTypeModel].VtxMaxModel.x < vtx.x)
			{
				g_aModelVtx[nCntTypeModel].VtxMaxModel.x = vtx.x;
			}
			if (g_aModelVtx[nCntTypeModel].VtxMaxModel.y < vtx.y)
			{
				g_aModelVtx[nCntTypeModel].VtxMaxModel.y = vtx.y;
			}
			if (g_aModelVtx[nCntTypeModel].VtxMaxModel.z < vtx.z)
			{
				g_aModelVtx[nCntTypeModel].VtxMaxModel.z = vtx.z;
			}
			pVtxBuff[nCntTypeModel] += sizeFvF;
		}
		//			//���_�o�b�t�@���A�����b�N
		g_pMeshModel[nCntTypeModel]->UnlockVertexBuffer();
	}


	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\exclamation000.jpg",
		&g_pTextureModel[0]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\question000.jpg",
		&g_pTextureModel[1]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		MODEL_NAME002,
		&g_pTextureModel[2]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		MODEL_NAME003,
		&g_pTextureModel[3]);

	//for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	//{
	//	for (int nCntMat = 0; nCntMat < (int)g_nNumMatModel[nCntModel]; nCntMat++)
	//	{
	//		// �}�e���A���f�[�^�ւ̃|�C���^���擾
	//		g_pMat = (D3DXMATERIAL*)g_pBuffMatModel[g_aModel[nCntModel].nType]->GetBufferPointer();
	//		{
	//			D3DXCreateTextureFromFile(pDevice,
	//				g_pMat[nCntMat].pTextureFilename,
	//				&g_pTextureModel[g_aModel[nCntModel].nType]);
	//		}
	//	}
	//}

	//float testpos = 100;
	//for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	//{
	//	// �ʒu�E�����̏����ݒ�
	//	g_aModel[nCntModel].pos = D3DXVECTOR3(testpos, 0, 0);
	//	g_aModel[nCntModel].rot = D3DXVECTOR3(0, 0, 0);
	//	g_aModel[nCntModel].fShadow = 12;
	////	g_aModel[nCntModel].fDestAngle = 0;
	//	//g_aModel
	//	//�@�e�̃Z�b�g
	//	g_aModel[nCntModel].nIdxShadow = SetShadow(g_aModel[nCntModel].pos, D3DXVECTOR3(0, 0, 0), 20.0f);

	//	testpos -= 100;
	//	g_aModel[nCntModel].bUse = true;
	//}

	takumi1 = 0;
}

//=============================================================================
// �I������
//=============================================================================
void UninitModel(void)
{
	for (int nCntModel = 0; nCntModel < MAX_MODEL_TYPE; nCntModel++)
	{
		// ���b�V���̊J��
		if (g_pMeshModel[nCntModel] != NULL)
		{
			g_pMeshModel[nCntModel]->Release();
			g_pMeshModel[nCntModel] = NULL;
		}
		// �}�e���A���̊J��
		if (g_pBuffMatModel[nCntModel] != NULL)
		{
			g_pBuffMatModel[nCntModel]->Release();
			g_pBuffMatModel[nCntModel] = NULL;
		}
		//�e�N�X�`���̔j��
		if (g_pTextureModel[nCntModel] != NULL)
		{
			g_pTextureModel[nCntModel]->Release();
			g_pTextureModel[nCntModel] = NULL;
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateModel(void)
{
	Player2 *pPlayer2;
	pPlayer2 = GetPlayer2();

	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		if (g_aModel[nCntModel].bUse == true)
		{
			g_aModel[nCntModel].fDistangle = atan2f((pPlayer2->pos.x - sinf(pPlayer2->rot.y) - g_aModel[nCntModel].pos.x),
				(pPlayer2->pos.z - cosf(pPlayer2->rot.y) - g_aModel[nCntModel].pos.z));

			g_aModel[nCntModel].fDiftangle = g_aModel[nCntModel].fDistangle - g_aModel[nCntModel].rot.y;

			if (g_aModel[nCntModel].fDiftangle > D3DX_PI)
			{
				g_aModel[nCntModel].fDiftangle -= D3DX_PI * 2.0f;
			}
			if (g_aModel[nCntModel].fDiftangle < -D3DX_PI)
			{
				g_aModel[nCntModel].fDiftangle += D3DX_PI * 2.0f;
			}

			g_aModel[nCntModel].rot.y += g_aModel[nCntModel].fDiftangle * 1.0f;

			if (g_aModel[nCntModel].rot.y > D3DX_PI)
			{
				g_aModel[nCntModel].rot.y -= D3DX_PI * 2.0f;
			}
			if (g_aModel[nCntModel].rot.y < -D3DX_PI)
			{
				g_aModel[nCntModel].rot.y += D3DX_PI * 2.0f;
			}
			g_aModel[nCntModel].move.x = sinf(g_aModel[nCntModel].rot.y) * 2.5f;
			g_aModel[nCntModel].move.z = cosf(g_aModel[nCntModel].rot.y) * 2.5f;
			g_aModel[nCntModel].pos += g_aModel[nCntModel].move;

			/*g_aModel[nCntModel].nLife--;*/

			// �e�̎���
			if (g_aModel[nCntModel].nLife <= 0)
			{
				g_aModel[nCntModel].bUse = false;
				//DeleteShadow(g_aBullet[nCntBullet].nIdxShadow);
				SetExplosion(g_aModel[nCntModel].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),D3DXCOLOR(255,255,0,0.0f));
				SetFade(MODE_RESULT);
				takumi1++;
			}

			FADE Fade;
			Fade = GetFade();

			if (takumi1 == 5)
			{
				SetFade(MODE_RESULT);
			}

			if (g_aModel[nCntModel].pos.y < 1.0f)
			{
				g_aModel[nCntModel].pos.y = 1;
			}
			//SetPostionShadow(g_nIdxShado, D3DXVECTOR3(g_aModel[nCntModel].pos.x, 0, g_aModel[nCntModel].pos.z));
		}
	}
}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;						//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;							//�}�e���A���f�[�^�ւ̃|�C���^

	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		if (g_aModel[nCntModel].bUse == true)	//���f�����g�p����Ă���
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aModel[nCntModel].mtxWorld);
			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aModel[nCntModel].rot.y, g_aModel[nCntModel].rot.x, g_aModel[nCntModel].rot.z);
			D3DXMatrixMultiply(&g_aModel[nCntModel].mtxWorld, &g_aModel[nCntModel].mtxWorld, &mtxRot);
			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aModel[nCntModel].pos.x, g_aModel[nCntModel].pos.y, g_aModel[nCntModel].pos.z);
			D3DXMatrixMultiply(&g_aModel[nCntModel].mtxWorld, &g_aModel[nCntModel].mtxWorld, &mtxTrans);
			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aModel[nCntModel].mtxWorld);
			// ���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);


			// �}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_pBuffMatModel[g_aModel[nCntModel].nType]->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_nNumMatModel[g_aModel[nCntModel].nType]; nCntMat++)
			{	// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
				// �e�N�X�`��

				pDevice->SetTexture(0, g_pTextureModel[2]);

				// ���f��(�p�[�c)�̕`��
				g_pMeshModel[g_aModel[nCntModel].nType]->DrawSubset(nCntMat);

			}
			// �}�e���A�����f�t�H���g�ɖ߂�
			pDevice->SetMaterial(&matDef);
		}
	}
}

//*****************************************************************************
//���f���|�C���^����
//*****************************************************************************
MODEL *GetModel(void)
{
	return &g_aModel[0];
}
//*****************************************************************************
//���f���Ƃ̓����蔻�菈��
//*****************************************************************************
bool CollisionModel(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 radius,D3DXVECTOR3 VtxMax, D3DXVECTOR3 VtxMin ,MODEL **pModel)
{
	//bool bLand = false;  // ��������ǂ���

	//Player *pPlayer = GetPlayer();

	//D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//D3DXMATRIX mtxMax, mtxMin, mtxRot, mtxTrans;


	//for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	//{// ��Q���̐������J��Ԃ�
	//	if (g_aModel[nCntModel].bUse == true)
	//	{// ��Q�����g�p����Ă���

	//		//[MAX]

	//		// ���[���h�}�g���b�N�X�̏�����
	//		D3DXMatrixIdentity(&mtxMax);
	//		// ��]�𔽉f
	//		D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	//		D3DXMatrixMultiply(&mtxMax, &mtxMax, &mtxRot);
	//		// �ʒu�𔽉f
	//		D3DXMatrixTranslation(&mtxTrans, g_aModel[nCntModel].VtxMaxModel.x, g_aModel[nCntModel].VtxMaxModel.y, g_aModel[nCntModel].VtxMaxModel.z);
	//		D3DXMatrixMultiply(&mtxMax, &mtxMax, &mtxTrans);

	//		D3DXMatrixMultiply(&mtxMax, &mtxMax, &g_aModel[nCntModel].mtxWorld);

	//		//[MIN]
	//		// ���[���h�}�g���b�N�X�̏�����
	//		D3DXMatrixIdentity(&mtxMin);
	//		// ��]�𔽉f
	//		D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	//		D3DXMatrixMultiply(&mtxMin, &mtxMin, &mtxRot);
	//		// �ʒu�𔽉f
	//		D3DXMatrixTranslation(&mtxTrans, g_aModel[nCntModel].VtxMinModel.x, g_aModel[nCntModel].VtxMinModel.y, g_aModel[nCntModel].VtxMinModel.z);
	//		D3DXMatrixMultiply(&mtxMin, &mtxMin, &mtxTrans);

	//		D3DXMatrixMultiply(&mtxMin, &mtxMin, &g_aModel[nCntModel].mtxWorld);


	//		//if (pPos->y <= mtxMax._42 && pPos->y + radius.y > mtxMin._42
	//		//	|| pPos->y + radius.y > mtxMax._42 && pPos->y < mtxMin._42
	//		//	|| pPos->y + radius.y > mtxMax._42 && pPos->y < mtxMin._42)
	//		//{// ��Q����Y���W�̒��ɂ���
	//			if (pPos->z - radius.z <= mtxMax._43 && pPos->z + radius.z >= mtxMin._43)
	//			{// ��Q����Z���W�̒��ɂ���
	//				if (pPosOld->x + radius.x <= mtxMin._41
	//					&& pPos->x + radius.x > mtxMin._41)
	//				{// X���W�̒��ɍ����������
	//				 // ���˕Ԃ�
	//					//g_aModel[nCntModel].move.x += pMove->x + 5;
	//					pPos->x = mtxMax._41 - radius.x;
	//					pMove->x = 0.0f;
	//					*pModel = &g_aModel[nCntModel];
	//				}
	//				else if (pPosOld->x - radius.x >= mtxMax._41
	//					&& pPos->x - radius.x <  mtxMax._41)
	//				{// X���W�̒��ɉE���������
	//				 // ���˕Ԃ�
	//					//g_aModel[nCntModel].move.x += pMove->x - 5;

	//					pPos->x = mtxMax._41 + radius.x + 0.1f;
	//					pMove->x = 0.0f;
	//					*pModel = &g_aModel[nCntModel];
	//				}
	//			}
	//			if (pPos->x - radius.x <= mtxMax._41 && pPos->x + radius.x >=  mtxMin._41)
	//			{// ��Q����X���W�̒��ɂ���
	//				if (pPosOld->z + radius.z <= mtxMin._43
	//					&& pPos->z + radius.z > mtxMin._43)
	//				{// Z���W�̒��ɑO���������
	//				 // ���˕Ԃ�
	//					//g_aModel[nCntModel].move.z += pMove->z + 5;
	//					SetExplosion(g_aModel[nCntModel].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(255, 255, 255, 0.0f));
	//					g_aModel[nCntModel].bUse = false;
	//					pPos->z = mtxMax._43 - radius.z;
	//					pMove->z = 0.0f;
	//					*pModel = &g_aModel[nCntModel];
	//					bLand = true;
	//					FADE Fade;
	//					Fade = GetFade();
	//					if (Fade == FADE_NONE)
	//					{

	//						SetFade(MODE_RESULT);
	//						PlaySound(SOUND_LABEL_SE_SAKEBI);
	//					}
	//				}
	//				else if (pPosOld->z - radius.z >= mtxMax._43
	//					&& pPos->z - radius.z < mtxMax._43)
	//				{// Z���W�̒��Ɍ�납�������
	//				 // ���˕Ԃ�
	//					//g_aModel[nCntModel].move.z += pMove->z - 5;

	//					pPos->z = mtxMax._43 + radius.z + 0.1f;
	//					pMove->z = 0.0f;
	//					*pModel = &g_aModel[nCntModel];
	//				}
	//			}

	//			//if (pPos->x - radius.x < g_aModel[nCntModel].pos.x + g_aModel[nCntModel].VtxMaxModel.x - 2.0f&& pPos->x + radius.x > g_aModel[nCntModel].pos.x + g_aModel[nCntModel].VtxMinModel.x + 2.0f
	//			//	&& pPos->z - radius.z <= g_aModel[nCntModel].pos.z + g_aModel[nCntModel].VtxMaxModel.z - 2.0f && pPos->z + radius.z >= g_aModel[nCntModel].pos.z + g_aModel[nCntModel].VtxMinModel.z + 2.0f)
	//			//{// ��Q���̓����ɏ����
	//			//	bLand = true;  // ����������Ԃ�
	//			//	pPos->y = g_aModel[nCntModel].pos.y + g_aModel[nCntModel].VtxMaxModel.y;
	//			//	pMove->y = 0.0f;  // �ړ��ʂ��Ȃ���
	//			//}
	//

	//		//pPos->x + fwigth - X_Y >= g_aBlock[nCntBlock].pos.x
	//		//	&& pPos->x - fwigth + X_Y <= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fwidth)


	//		// X
	//		//if (pPos->x - radius.x >= mtxMin._41 && pPos->x + radius.x >= mtxMin._41)
	//		//{
	//		//	if (pPosOld->x -radius.x <= mtxMax._41 && pPosOld->x + radius.x <= mtxMax._41)
	//		//	{

	//		//	}
	//		//}


	//		//if (pPos->y <= mtxMax._42 && pPos->y + radius.y > mtxMin._42
	//		//	|| pPos->y + radius.y > mtxMax._42 && pPos->y < mtxMin._42
	//		//	|| pPos->y + radius.y > mtxMax._42 && pPos->y < mtxMin._42)
	//		//{
	//		//	if (pPos->x <= mtxMax._41 && pPos->x + radius.x > mtxMin._41
	//		//		|| pPos->x + radius.x > mtxMax._41 && pPos->x < mtxMin._41
	//		//		|| pPos->x + radius.x > mtxMax._41 && pPos->x < mtxMin._41)
	//		//	{
	//		//		if (pPos->z > mtxMin._43 && pPosOld->z < mtxMin._43)
	//		//		{
	//		//			bLand = true;  // ����������Ԃ�
	//		//			pPos->z = mtxMin._43;  // �ړ��ʂ��Ȃ���
	//		//			pMove->z = 0.0f;  // �ړ��ʂ��Ȃ���
	//		//		}
	//		//	}
	//		//}
	//	}
	//}

	//return bLand;   // ��������ǂ�����Ԃ�

bool bLand = false;  // ��������ǂ���

Player *pPlayer = GetPlayer();

for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
{// ��Q���̐������J��Ԃ�
	if (g_aModel[nCntModel].bUse == true)
	{// ��Q�����g�p����Ă���
		if (pPos->y <= g_aModel[nCntModel].pos.y + g_aModel[nCntModel].VtxMaxModel.y && pPos->y + radius.y > g_aModel[nCntModel].pos.y + g_aModel[nCntModel].VtxMinModel.y
			|| pPos->y + radius.y > g_aModel[nCntModel].pos.y + g_aModel[nCntModel].VtxMaxModel.y && pPos->y < g_aModel[nCntModel].pos.y + g_aModel[nCntModel].VtxMinModel.y
			|| pPos->y + radius.y > g_aModel[nCntModel].pos.y + g_aModel[nCntModel].VtxMaxModel.y && pPos->y < g_aModel[nCntModel].pos.y + g_aModel[nCntModel].VtxMinModel.y)
		{// ��Q����Y���W�̒��ɂ���
			if (pPos->z - radius.z <= g_aModel[nCntModel].pos.z + g_aModel[nCntModel].VtxMaxModel.z && pPos->z + radius.z >= g_aModel[nCntModel].pos.z + g_aModel[nCntModel].VtxMinModel.z)
			{// ��Q����Z���W�̒��ɂ���
				if (pPosOld->x + radius.x <= g_aModel[nCntModel].pos.x + g_aModel[nCntModel].VtxMinModel.x
					&& pPos->x + radius.x > g_aModel[nCntModel].pos.x + g_aModel[nCntModel].VtxMinModel.x)
				{// X���W�̒��ɍ����������
				 // ���˕Ԃ�
					//g_aModel[nCntModel].move.x += pMove->x + 5;

					pPos->x = g_aModel[nCntModel].pos.x + g_aModel[nCntModel].VtxMinModel.x - radius.x;
					pMove->x = 0.0f;
					*pModel = &g_aModel[nCntModel];
					bLand = true;
				}
				else if (pPosOld->x - radius.x >= g_aModel[nCntModel].pos.x + g_aModel[nCntModel].VtxMaxModel.x
					&& pPos->x - radius.x < g_aModel[nCntModel].pos.x + g_aModel[nCntModel].VtxMaxModel.x)
				{// X���W�̒��ɉE���������
				 // ���˕Ԃ�
					//g_aModel[nCntModel].move.x += pMove->x - 5;

					pPos->x = g_aModel[nCntModel].pos.x + g_aModel[nCntModel].VtxMaxModel.x + radius.x + 0.1f;
					pMove->x = 0.0f;
					*pModel = &g_aModel[nCntModel];
					bLand = true;
				}
			}
			if (pPos->x - radius.x <= g_aModel[nCntModel].pos.x + g_aModel[nCntModel].VtxMaxModel.x && pPos->x + radius.x >= g_aModel[nCntModel].pos.x + g_aModel[nCntModel].VtxMinModel.x)
			{// ��Q����X���W�̒��ɂ���
				if (pPosOld->z + radius.z <= g_aModel[nCntModel].pos.z + g_aModel[nCntModel].VtxMinModel.z
					&& pPos->z + radius.z > g_aModel[nCntModel].pos.z + g_aModel[nCntModel].VtxMinModel.z)
				{// Z���W�̒��ɑO���������
				 // ���˕Ԃ�
					//g_aModel[nCntModel].move.z += pMove->z + 5;

					pPos->z = g_aModel[nCntModel].pos.z + g_aModel[nCntModel].VtxMinModel.z - radius.z;
					pMove->z = 0.0f;
					*pModel = &g_aModel[nCntModel];
					bLand = true;

				}
				else if (pPosOld->z - radius.z >= g_aModel[nCntModel].pos.z + g_aModel[nCntModel].VtxMaxModel.z
					&& pPos->z - radius.z < g_aModel[nCntModel].pos.z + g_aModel[nCntModel].VtxMaxModel.z)
				{// Z���W�̒��Ɍ�납�������
				 // ���˕Ԃ�
				//	g_aModel[nCntModel].move.z += pMove->z - 5;
					pPos->z = g_aModel[nCntModel].pos.z + g_aModel[nCntModel].VtxMinModel.z - radius.z;
					pMove->z = 0.0f;
					*pModel = &g_aModel[nCntModel];
					g_aModel[nCntModel].bUse = false;
				}
			}

			//if (pPos->x - radius.x < g_aModel[nCntModel].pos.x + g_aModel[nCntModel].VtxMaxModel.x - 2.0f&& pPos->x + radius.x > g_aModel[nCntModel].pos.x + g_aModel[nCntModel].VtxMinModel.x + 2.0f
			//	&& pPos->z - radius.z <= g_aModel[nCntModel].pos.z + g_aModel[nCntModel].VtxMaxModel.z - 2.0f && pPos->z + radius.z >= g_aModel[nCntModel].pos.z + g_aModel[nCntModel].VtxMinModel.z + 2.0f)
			//{// ��Q���̓����ɏ����
			//	bLand = true;  // ����������Ԃ�
			//	pPos->y = g_aModel[nCntModel].pos.y + g_aModel[nCntModel].VtxMaxModel.y;
			//	pMove->y = 0.0f;  // �ړ��ʂ��Ȃ���
			//}
		}
	}
}

return bLand;   // ��������ǂ�����Ԃ�
}


//=============================================================================
// �ݒ菈��
//=============================================================================
void SetModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType)
{
	int nNumVtex;	//���_��
	DWORD sizeFvF;	//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff[MAX_MODEL];	//���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 vtx[MAX_MODEL];

	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		if (g_aModel[nCntModel].bUse == false)
		{


			//for (int nCntTypeModel = 0; nCntTypeModel < MAX_MODEL_TYPE; nCntTypeModel++)
			//{
			//���_�����擾
			nNumVtex = g_pMeshModel[nType]->GetNumVertices();
			//���_�t�H�[�}�b�g�̃T�C�Y���擾
			sizeFvF = D3DXGetFVFVertexSize(g_pMeshModel[nType]->GetFVF());
			//	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
			//{
			//���_�@���b�N
			g_pMeshModel[nType]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff[nType]);
			for (int nCntVtx = 0; nCntVtx < nNumVtex; nCntVtx++)
			{	//���_���W�̑��
				D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff[nType];
				if (g_aModel[nCntModel].VtxMinModel.x > vtx.x)
				{
					g_aModel[nCntModel].VtxMinModel.x = vtx.x;
				}
				if (g_aModel[nCntModel].VtxMinModel.y > vtx.y)
				{
					g_aModel[nCntModel].VtxMinModel.y = vtx.y;
				}
				if (g_aModel[nCntModel].VtxMinModel.z > vtx.z)
				{
					g_aModel[nCntModel].VtxMinModel.z = vtx.z;
				}

				if (g_aModel[nCntModel].VtxMaxModel.x < vtx.x)
				{
					g_aModel[nCntModel].VtxMaxModel.x = vtx.x;
				}
				if (g_aModel[nCntModel].VtxMaxModel.y < vtx.y)
				{
					g_aModel[nCntModel].VtxMaxModel.y = vtx.y;
				}
				if (g_aModel[nCntModel].VtxMaxModel.z < vtx.z)
				{
					g_aModel[nCntModel].VtxMaxModel.z = vtx.z;
				}
				pVtxBuff[nCntModel] += sizeFvF;
			}
			//			//���_�o�b�t�@���A�����b�N
			g_pMeshModel[nType]->UnlockVertexBuffer();
			//}
			//}
			// �ʒu�E�����̏����ݒ�

			g_aModel[nCntModel].pos = pos;
			g_aModel[nCntModel].rot = D3DXVECTOR3(0, 0, 0);
			g_aModel[nCntModel].fShadow = 12;
			g_aModel[nCntModel].nType = nType;
			//�@�e�̃Z�b�g
			g_aModel[nCntModel].nIdxShadow = SetShadow(g_aModel[nCntModel].pos, D3DXVECTOR3(0, 0, 0));
			g_aModel[nCntModel].bUse = true;
			break;
		}
	}
}
