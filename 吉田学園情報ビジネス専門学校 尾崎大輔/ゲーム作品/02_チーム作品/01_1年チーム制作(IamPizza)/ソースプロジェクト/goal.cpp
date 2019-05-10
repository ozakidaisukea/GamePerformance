//=============================================================================
//
// �S�[������ [goal.cpp]
// Author : Meguro Mikiya
//
//=============================================================================
#include "goal.h"
#include "input.h"
#include "shadow.h"
#include "camera.h"
#include "bullet.h"
#include "polygon.h"
#include "player.h"
#include "game.h"
#include "explosion.h"
#include "sound.h"
#include "particle.h"
#include "fade.h"
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPD3DXMESH g_pMeshGoal[MAX_GOAL];					//���b�V�����ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatGoal[MAX_GOAL];			//�}�e���A�����ւ̃|�C���^
LPDIRECT3DTEXTURE9	g_pTextureGoal[MAX_GOAL];		//�e�N�X�`���ւ̃|�C���^
DWORD g_nNumMatGoal[MAX_GOAL] = {};							//�}�e���A�����̐�
GOAL g_aGoal[MAX_GOAL];
D3DXMATERIAL *g_pMatGoal;
//=============================================================================
// ����������
//=============================================================================
void InitGoal(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(GOAL_NAME000,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatGoal[0],
		NULL,
		&g_nNumMatGoal[0],
		&g_pMeshGoal[0]);



	int nNumVtex;	//���_��
	DWORD sizeFvF;	//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff[MAX_GOAL];	//���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 vtx[MAX_GOAL];

	for (int nCntGoal = 0; nCntGoal < MAX_GOAL; nCntGoal++)
	{
		g_aGoal[nCntGoal].VtxMinGoal = D3DXVECTOR3(10000, 0, 10000);
		g_aGoal[nCntGoal].VtxMaxGoal = D3DXVECTOR3(-10000, 0, -10000);
		g_aGoal[nCntGoal].nType = 0;
		g_aGoal[nCntGoal].bUse = false;
		g_aGoal[nCntGoal].nCntGoal = 0;
		g_aGoal[nCntGoal].nGoalPattern = 0;
		g_aGoal[nCntGoal].nCounterState = 60;
		g_aGoal[nCntGoal].state = GOALSTATE_NORMAL;;
	}

	//���_�����擾
	nNumVtex = g_pMeshGoal[0]->GetNumVertices();
	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	sizeFvF = D3DXGetFVFVertexSize(g_pMeshGoal[0]->GetFVF());

	for (int nCntGoal = 0; nCntGoal < MAX_GOAL; nCntGoal++)
	{
		//���_�@���b�N
		g_pMeshGoal[0]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff[nCntGoal]);
		for (int nCntVtx = 0; nCntVtx < nNumVtex; nCntVtx++)
		{	//���_���W�̑��
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff[nCntGoal];
			if (g_aGoal[nCntGoal].VtxMinGoal.x > vtx.x)
			{
				g_aGoal[nCntGoal].VtxMinGoal.x = vtx.x;
			}
			if (g_aGoal[nCntGoal].VtxMinGoal.y > vtx.y)
			{
				g_aGoal[nCntGoal].VtxMinGoal.y = vtx.y;
			}
			if (g_aGoal[nCntGoal].VtxMinGoal.z > vtx.z)
			{
				g_aGoal[nCntGoal].VtxMinGoal.z = vtx.z;
			}

			if (g_aGoal[nCntGoal].VtxMaxGoal.x < vtx.x)
			{
				g_aGoal[nCntGoal].VtxMaxGoal.x = vtx.x;
			}
			if (g_aGoal[nCntGoal].VtxMaxGoal.y < vtx.y)
			{
				g_aGoal[nCntGoal].VtxMaxGoal.y = vtx.y;
			}
			if (g_aGoal[nCntGoal].VtxMaxGoal.z < vtx.z)
			{
				g_aGoal[nCntGoal].VtxMaxGoal.z = vtx.z;
			}
			//��������

			pVtxBuff[nCntGoal] += sizeFvF;
		}
		//			//���_�o�b�t�@���A�����b�N
		g_pMeshGoal[0]->UnlockVertexBuffer();
	}
	
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		GOAL_NAME000,
		&g_pTextureGoal[0]);

	for (int nCntGoal = 0; nCntGoal < MAX_GOAL; nCntGoal++)
	{
		for (int nCntMat = 0; nCntMat < (int)g_nNumMatGoal[nCntGoal]; nCntMat++)
		{
			// �}�e���A���f�[�^�ւ̃|�C���^���擾
			g_pMatGoal = (D3DXMATERIAL*)g_pBuffMatGoal[g_aGoal[nCntGoal].nType]->GetBufferPointer();
			{
				D3DXCreateTextureFromFile(pDevice,
					g_pMatGoal[nCntMat].pTextureFilename,
					&g_pTextureGoal[g_aGoal[nCntGoal].nType]);
			}
		}
	}
}

//=============================================================================
// �I������
//=============================================================================
void UninitGoal(void)
{
	for (int nCntGoal = 0; nCntGoal < MAX_GOAL; nCntGoal++)
	{
		// ���b�V���̊J��
		if (g_pMeshGoal[nCntGoal] != NULL)
		{
			g_pMeshGoal[nCntGoal]->Release();
			g_pMeshGoal[nCntGoal] = NULL;
		}
		// �}�e���A���̊J��
		if (g_pBuffMatGoal[nCntGoal] != NULL)
		{
			g_pBuffMatGoal[nCntGoal]->Release();
			g_pBuffMatGoal[nCntGoal] = NULL;
		}
		//�e�N�X�`���̔j��
		if (g_pTextureGoal[nCntGoal] != NULL)
		{
			g_pTextureGoal[nCntGoal]->Release();
			g_pTextureGoal[nCntGoal] = NULL;
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateGoal(void)
{
	Camera *pCamera;
	pCamera = GetCamera();
	//�J�����Ƃ̋��������߂�
	double length = pow((g_aGoal[0].pos.x - pCamera->posV.x)*(g_aGoal[0].pos.x - pCamera->posV.x)
		+ (g_aGoal[0].pos.z - pCamera->posV.z)*(g_aGoal[0].pos.z - pCamera->posV.z), 0.5);

	//float�^�ɕϊ�
	g_aGoal[0].fLength = (float)length;

	if(g_aGoal[0].nGoalPattern == 0)
	{
		g_aGoal[0].pos = D3DXVECTOR3(8230, 0, -500);
	}
	else if (g_aGoal[0].nGoalPattern == 1)
	{
		g_aGoal[0].pos = D3DXVECTOR3(2400, 0, 7200);
	}
	else if (g_aGoal[0].nGoalPattern == 2)
	{
		g_aGoal[0].pos = D3DXVECTOR3(6300, 0, 5560);
	}
	else if (g_aGoal[0].nGoalPattern == 3)
	{
		g_aGoal[0].pos = D3DXVECTOR3(550, 0, -480);
	}
	
	if (g_aGoal[0].state == GOALSTATE_CHECKPOINT)
	{
		g_aGoal[0].nCounterState++;
		if(g_aGoal[0].nCounterState > 60)
		{
			g_aGoal[0].nCounterState = 0;
			g_aGoal[0].state = GOALSTATE_NORMAL;
		}
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawGoal(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;						//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;							//�}�e���A���f�[�^�ւ̃|�C���^

	for (int nCntGoal = 0; nCntGoal < MAX_GOAL; nCntGoal++)
	{		// ���[���h�}�g���b�N�X�̏�����
		if (g_aGoal[0].fLength < 2200)
		{//�S�[���ƃv���C���[�̋����ŕ`�悷�邩���߂�
			D3DXMatrixIdentity(&g_aGoal[nCntGoal].mtxWorld);
			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aGoal[nCntGoal].rot.y, g_aGoal[nCntGoal].rot.x, g_aGoal[nCntGoal].rot.z);
			D3DXMatrixMultiply(&g_aGoal[nCntGoal].mtxWorld, &g_aGoal[nCntGoal].mtxWorld, &mtxRot);
			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aGoal[nCntGoal].pos.x, g_aGoal[nCntGoal].pos.y, g_aGoal[nCntGoal].pos.z);
			D3DXMatrixMultiply(&g_aGoal[nCntGoal].mtxWorld, &g_aGoal[nCntGoal].mtxWorld, &mtxTrans);
			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aGoal[nCntGoal].mtxWorld);
			// ���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);


			// �}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_pBuffMatGoal[g_aGoal[nCntGoal].nType]->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_nNumMatGoal[nCntGoal]; nCntMat++)
			{	// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
				// �e�N�X�`��
				pDevice->SetTexture(0, g_pTextureGoal[g_aGoal[nCntGoal].nType]);
				if (g_aGoal[nCntGoal].bUse == true)	//�S�[�����g�p����Ă���
				{	// �S�[��(�p�[�c)�̕`��
					g_pMeshGoal[g_aGoal[nCntGoal].nType]->DrawSubset(nCntMat);
				}
			}
			// �}�e���A�����f�t�H���g�ɖ߂�
			pDevice->SetMaterial(&matDef);
		}
	}
}

//*****************************************************************************
//�S�[���|�C���^����
//*****************************************************************************
GOAL *GetGoal(void)
{
	return &g_aGoal[0];
}
//*****************************************************************************
//�S�[���Ƃ̓����蔻�菈��
//*****************************************************************************
bool CollisionGoal(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 VtxMax, D3DXVECTOR3 VtxMin/*, GOAL **pGoal*/)
{
	bool bLand = false;

	GAMESTATE GameState;
	GameState = GetGameState();
	FADE fade = GetFade();

	for (int nCntGoal = 0; nCntGoal < MAX_GOAL; nCntGoal++)
	{
		if (g_aGoal[nCntGoal].bUse == true)
		{
#if 1
			//�S�[����Y���̒�
			if (pPos->y < g_aGoal[nCntGoal].pos.y + g_aGoal[nCntGoal].VtxMaxGoal.y
				&& pPos->y > g_aGoal[nCntGoal].pos.y + g_aGoal[nCntGoal].VtxMinGoal.y)
			{
				//�S�[����Z���̒�
				if (pPos->z + VtxMin.z < g_aGoal[nCntGoal].pos.z + g_aGoal[nCntGoal].VtxMaxGoal.z
					&& pPos->z + VtxMax.z > g_aGoal[nCntGoal].pos.z + g_aGoal[nCntGoal].VtxMinGoal.z)
				{
					//�S�[����X���̒�
					if (pPos->x + VtxMin.x < g_aGoal[nCntGoal].pos.x + g_aGoal[nCntGoal].VtxMaxGoal.x
						&& pPos->x + VtxMax.x > g_aGoal[nCntGoal].pos.x + g_aGoal[nCntGoal].VtxMinGoal.x)
					{

						//X���̓����蔻��
						if (pPosOld->x + 1 > g_aGoal[nCntGoal].pos.x + g_aGoal[nCntGoal].VtxMaxGoal.x)
						{
							//if (g_aGoal[0].nGoalPattern == 0)
							//{
							//	g_aGoal[0].nGoalPattern = 1;
							//}
							//if (g_aGoal[0].nGoalPattern == 1)
							//{
							//	g_aGoal[0].nGoalPattern = 2;
							//}
							if (GameState != GAMESTATE_GAMECLEAR && g_aGoal[0].state == GOALSTATE_NORMAL || fade == FADE_NONE && g_aGoal[0].state == GOALSTATE_NORMAL)
							{
								if(GameState != GAMESTATE_GAMECLEAR && g_aGoal[0].nGoalPattern == 3)
								{
									SetGameState(GAMESTATE_GAMECLEAR);
									PlaySound(SOUND_LABEL_SE_CHIME1);
								}
								g_aGoal[0].state = GOALSTATE_CHECKPOINT;
								PlaySound(SOUND_LABEL_SE_CHIME1);
								SetParticle(D3DXVECTOR3(g_aGoal[nCntGoal].pos.x, g_aGoal[nCntGoal].pos.y + 50, g_aGoal[nCntGoal].pos.z)
									, D3DXVECTOR3(0.8f, 0.2f, 0.8f), D3DXVECTOR3(0, 0, 0), D3DXCOLOR(0, 0, 0, 0), 20, 30, PARTICLE_TYPE_GOAL);
							}
							bLand = true;
						}
						else if (pPosOld->x - 1 < g_aGoal[nCntGoal].pos.x + g_aGoal[nCntGoal].VtxMinGoal.x)
						{
							if (GameState != GAMESTATE_GAMECLEAR && g_aGoal[0].state == GOALSTATE_NORMAL || fade == FADE_NONE && g_aGoal[0].state == GOALSTATE_NORMAL)
							{
								if (GameState != GAMESTATE_GAMECLEAR && g_aGoal[0].nGoalPattern == 3)
								{
									SetGameState(GAMESTATE_GAMECLEAR);
									PlaySound(SOUND_LABEL_SE_CHIME1);
								}
								g_aGoal[0].state = GOALSTATE_CHECKPOINT;
								PlaySound(SOUND_LABEL_SE_CHIME1);
								SetParticle(D3DXVECTOR3(g_aGoal[nCntGoal].pos.x, g_aGoal[nCntGoal].pos.y + 50, g_aGoal[nCntGoal].pos.z)
									, D3DXVECTOR3(0.8f, 0.2f, 0.8f), D3DXVECTOR3(0, 0, 0), D3DXCOLOR(0, 0, 0, 0), 20, 30, PARTICLE_TYPE_GOAL);
							}
							bLand = true;
						}
						//Z���̓����蔻��
						if (pPosOld->z + 1 > g_aGoal[nCntGoal].pos.z + g_aGoal[nCntGoal].VtxMaxGoal.z)
						{
							if (GameState != GAMESTATE_GAMECLEAR && g_aGoal[0].state == GOALSTATE_NORMAL || fade == FADE_NONE && g_aGoal[0].state == GOALSTATE_NORMAL)
							{
								if (GameState != GAMESTATE_GAMECLEAR && g_aGoal[0].nGoalPattern == 3)
								{
									SetGameState(GAMESTATE_GAMECLEAR);
									PlaySound(SOUND_LABEL_SE_CHIME1);
								}
								g_aGoal[0].state = GOALSTATE_CHECKPOINT;
								PlaySound(SOUND_LABEL_SE_CHIME1);
								SetParticle(D3DXVECTOR3(g_aGoal[nCntGoal].pos.x, g_aGoal[nCntGoal].pos.y + 50, g_aGoal[nCntGoal].pos.z)
									, D3DXVECTOR3(0.8f, 0.2f, 0.8f), D3DXVECTOR3(0, 0, 0), D3DXCOLOR(0, 0, 0, 0), 20, 30, PARTICLE_TYPE_GOAL);

							}
							bLand = true;
						}
						else if (pPosOld->z - 1 < g_aGoal[nCntGoal].pos.z + g_aGoal[nCntGoal].VtxMinGoal.z)
						{
							if (GameState != GAMESTATE_GAMECLEAR && g_aGoal[0].state == GOALSTATE_NORMAL || fade == FADE_NONE && g_aGoal[0].state == GOALSTATE_NORMAL)
							{
								if (GameState != GAMESTATE_GAMECLEAR && g_aGoal[0].nGoalPattern == 3)
								{
									SetGameState(GAMESTATE_GAMECLEAR);
									PlaySound(SOUND_LABEL_SE_CHIME1);
								}
								g_aGoal[0].state = GOALSTATE_CHECKPOINT;
								PlaySound(SOUND_LABEL_SE_CHIME1);
								SetParticle(D3DXVECTOR3(g_aGoal[nCntGoal].pos.x, g_aGoal[nCntGoal].pos.y + 50, g_aGoal[nCntGoal].pos.z)
									, D3DXVECTOR3(0.8f, 0.2f, 0.8f), D3DXVECTOR3(0, 0, 0), D3DXCOLOR(0, 0, 0, 0), 20, 30, PARTICLE_TYPE_GOAL);
							}
							bLand = true;
						}
						//Y���̓����蔻��
						if (pPosOld->y >= g_aGoal[nCntGoal].pos.y + g_aGoal[nCntGoal].VtxMaxGoal.y)
						{
						}
						else if (pPosOld->y <= g_aGoal[nCntGoal].pos.y + g_aGoal[nCntGoal].VtxMinGoal.y)
						{
						}
					}
				}
			}
#endif
		}
	}
	
	return bLand;
}


//=============================================================================
// �ݒ菈��
//=============================================================================
void SetGoal(D3DXVECTOR3 pos, int nType)
{

	int nNumVtex;	//���_��
	DWORD sizeFvF[MAX_GOAL];	//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff[MAX_GOAL];	//���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 vtx[MAX_GOAL];

	//���_�����擾
	nNumVtex = g_pMeshGoal[nType]->GetNumVertices();
	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	sizeFvF[nType] = D3DXGetFVFVertexSize(g_pMeshGoal[nType]->GetFVF());

	for (int nCntGoal = 0; nCntGoal < MAX_GOAL; nCntGoal++)
	{
		//if (g_aGoal[nCntGoal].bUse == false)
		//{
			//���_�@���b�N
			g_pMeshGoal[nType]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff[nType]);
			for (int nCntVtx = 0; nCntVtx < nNumVtex; nCntVtx++)
			{	//���_���W�̑��
				vtx[nCntGoal] = *(D3DXVECTOR3*)pVtxBuff[nType];
				if (g_aGoal[nCntGoal].VtxMinGoal.x > vtx[nCntGoal].x)
				{
					g_aGoal[nCntGoal].VtxMinGoal.x = vtx[nCntGoal].x;
				}
				if (g_aGoal[nCntGoal].VtxMinGoal.y > vtx[nCntGoal].y)
				{
					g_aGoal[nCntGoal].VtxMinGoal.y = vtx[nCntGoal].y;
				}
				if (g_aGoal[nCntGoal].VtxMinGoal.z > vtx[nCntGoal].z)
				{
					g_aGoal[nCntGoal].VtxMinGoal.z = vtx[nCntGoal].z;
				}

				if (g_aGoal[nCntGoal].VtxMaxGoal.x < vtx[nCntGoal].x)
				{
					g_aGoal[nCntGoal].VtxMaxGoal.x = vtx[nCntGoal].x;
				}
				if (g_aGoal[nCntGoal].VtxMaxGoal.y < vtx[nCntGoal].y)
				{
					g_aGoal[nCntGoal].VtxMaxGoal.y = vtx[nCntGoal].y;
				}
				if (g_aGoal[nCntGoal].VtxMaxGoal.z < vtx[nCntGoal].z)
				{
					g_aGoal[nCntGoal].VtxMaxGoal.z = vtx[nCntGoal].z;
				}
				pVtxBuff[nCntGoal] += sizeFvF[nType];
			}
			//���_�o�b�t�@���A�����b�N
			g_pMeshGoal[nType]->UnlockVertexBuffer();
		//	break;
		//}
	}

	for (int nCntGoal = 0; nCntGoal < MAX_GOAL; nCntGoal++)
	{
		if (g_aGoal[nCntGoal].bUse == false)
		{
			// �ʒu�E�����̏����ݒ�
			g_aGoal[nCntGoal].pos = pos;
			g_aGoal[nCntGoal].rot = D3DXVECTOR3(0, 0, 0);
			g_aGoal[nCntGoal].fShadow = 12;
			g_aGoal[nCntGoal].nType = nType;
			//�@�e�̃Z�b�g
			//g_aGoal[nCntGoal].nIdxShadow = SetShadow(g_aGoal[nCntGoal].pos, D3DXVECTOR3(0, 0, 0), 20.0f);
			g_aGoal[nCntGoal].bUse = true;
			break;
		}
	}

}
