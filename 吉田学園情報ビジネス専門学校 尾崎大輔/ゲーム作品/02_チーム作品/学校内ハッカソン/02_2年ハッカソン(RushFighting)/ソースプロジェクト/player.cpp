//=============================================================================
//
// �v���C���[���� [player.cpp]
// Author : Hodaka Niwa
//
//=============================================================================
#include "player.h"
#include "input.h"
#include "camera.h"
#include "shadow.h"
#include "effect.h"
#include "lifegauge.h"
#include "ultgauge.h"
#include "game.h"
#include "result.h"
#include "sound.h"
#include "Rush.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MODEL_FILENAME   "MODEL_FILENAME"
#define NUM_MODEL        "NUM_MODEL"
#define CHARACTERSET     "CHARACTERSET"
#define MOVE             "MOVE"
#define JUMP             "JUMP"
#define INDEX            "INDEX"
#define PARENT           "PARENT"
#define POS              "POS"
#define ROT              "ROT"
#define PARTSSET         "PARTSSET"
#define END_PARTSSET     "END_PARTSSET"
#define END_CHARACTERSET "END_CHARACTERSET"
#define MOTIONSET        "MOTIONSET"
#define LOOP             "LOOP"
#define NUM_KEY          "NUM_KEY"
#define KEYSET           "KEYSET"
#define FRAME            "FRAME"
#define KEY              "KEY"
#define END_KEY          "END_KEY"
#define END_KEYSET       "END_KEYSET"
#define END_MOTIONSET    "END_MOTIONSET"


#define PLAYER_INERTIA_NORMAL (0.3f)     // �ʏ펞�̊���
#define PLAYER_INERTIA_JUMP   (0.012f)   // �W�����v���̊���
#define GRAVITY_POWER         (-0.4f)    // �d��
#define PlAYER_MAX_LIFE       (460)      // �̗�

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void PlayerOperation(int nCntPlayer);          // �v���C���[�̑��쏈��
void PlayerTransition(int nCntPlayer);         // �v���C���[�̑J�ڏ���
void PlayerAction(int nCntPlayer);             // �v���C���[���A�N�V������Ԃ̏���
void PlayerStateMent(int nCntPlayer);          // �v���C���[�̏�ԑJ�ڏ���
void PlayerMotion(int nCntPlayer);             // ���[�V��������
void PlayerMotionBlend(int nCntPlayer);        // ���[�V�����u�����h����
void PlayerMotionAdvance(int nCntPlayer);      // ���[�V�����i�s����
void SwitchKey(int nCntPlayer);                // �L�[�t���[���̐؂�ւ�����
void SwitchMotion(int nCntPlayer);             // ���[�V�����؂�ւ�����

bool CollisionAttack(int nCntPlayer, D3DXVECTOR3 pos, float fRadius);
void CollisionPlayer(int nCntPlayer);
void PlayerAttack(int nCntPlayer);
void PlayerDamage(int nCntPlayer, int nDamage);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
Player  g_Player[MAX_PLAYER];                 // �v���C���[���
int     g_nNumModel[MAX_PLAYER];              // ���̃v���C���[�̃��f����

//=============================================================================
// ����������
//=============================================================================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	FILE  *pFile;           // �e�L�X�g�t�@�C���ւ̃|�C���^
	char  str0[128];        // ����Ȃ�����
	char  xFileName[64];    // x�t�@�C���̖��O
	D3DXVECTOR3 OffsetPos;  // �e���f������̋���
	D3DXVECTOR3 OffsetRot;  // �e���f������̌���
	float fJump;            // �W�����v��
	float fMovement;        // �ړ���
	int   nIdxParent;       // �e���f��
	int   nCntModel = 0;    // ���f����ǂݍ��񂾐��𐔂���ϐ�
	int   nCntParts = 0;    // ���f���̃p�[�c����ǂݍ��񂾉񐔂𐔂���ϐ�
	int   nCntPlayer = 0;   // �v���C���[�̐�
	int   nCntMotion = 0;   // ���[�V�����̔ԍ�
	int   nCntKey = 0;      // �L�[�t���[���̔ԍ��𐔂���ϐ�
	int   nPlaybackKey;     // �t���[����
	int   nCntKeyModel = 0; // ���f���̐����̃L�[�t���[���𐔂���ϐ�
	int   bLoop;            // ���[�V���������[�v���邩���Ȃ���
	int   nNumKey = 0;      // �L�[�t���[���̐�
	D3DXVECTOR3 posAdd;     // ��̈ʒu�ɉ�����l
	D3DXVECTOR3 DestAngle;  // �ړI�̌���

	//-------------------
	//  �v���C���[1�l��
	//-------------------
	// �t�@�C���I�[�v��
	pFile = fopen("data/TEXT/motion_00.txt", "r");

	if (pFile != NULL)
	{// �t�@�C�����J����
		while (fscanf(pFile, "%s", &str0[0]) != EOF)
		{// �e�L�X�g�t�@�C���̖��[�܂ŕ���������s���󔒂�����܂œǂݎ��
			if (strcmp(&str0[0], NUM_MODEL) == 0)
			{// ���f���̐���������Ă�����
				fscanf(pFile, "%s %d", &str0[0], &g_nNumModel[nCntPlayer]);
			}
			if (strcmp(&str0[0], MODEL_FILENAME) == 0)
			{// x�t�@�C���̊g���q��������Ă�����
				if (fscanf(pFile, "%s %s", &str0[0], &xFileName[0]) == 2)
				{// ���f���̃t�@�C������ǂݎ������
				    // x�t�@�C���̓ǂݍ���
					D3DXLoadMeshFromX(&xFileName[0],
						D3DXMESH_SYSTEMMEM,
						pDevice,
						NULL,
						&g_Player[nCntPlayer].aModel[nCntModel].pBuffMat,
						NULL,
						&g_Player[nCntPlayer].aModel[nCntModel].nNumMat,
						&g_Player[nCntPlayer].aModel[nCntModel].pMesh);

					// �}�e���A����񂩂�e�N�X�`���������o��
					D3DXMATERIAL* pMat = (D3DXMATERIAL*)g_Player[nCntPlayer].aModel[nCntModel].pBuffMat->GetBufferPointer();
					D3DMATERIAL9* pMatBuff = new D3DMATERIAL9[g_Player[nCntPlayer].aModel[nCntModel].nNumMat];
					g_Player[nCntPlayer].aModel[nCntModel].pTexture = new LPDIRECT3DTEXTURE9[g_Player[nCntPlayer].aModel[nCntModel].nNumMat];

					for (DWORD nCntMat = 0; nCntMat < g_Player[nCntPlayer].aModel[nCntModel].nNumMat; nCntMat++)
					{// ���_���̐������J��Ԃ�
					 // �}�e���A������ǂݍ���
						pMatBuff[nCntMat] = pMat[nCntMat].MatD3D;

						// ����������������
						pMatBuff[nCntMat].Ambient = pMatBuff[nCntMat].Diffuse;

						// �e�N�X�`������������
						g_Player[nCntPlayer].aModel[nCntModel].pTexture[nCntMat] = NULL;

						// �e�N�X�`���̏���ǂݍ���
						if (pMat[nCntMat].pTextureFilename != NULL &&
							lstrlen(pMat[nCntMat].pTextureFilename) > 0)
						{// �e�N�X�`���̃t�@�C����������
							D3DXCreateTextureFromFile(pDevice,
								pMat[nCntMat].pTextureFilename,
								&g_Player[nCntPlayer].aModel[nCntModel].pTexture[nCntMat]);
						}

					}
				}
				nCntModel++;  // ��ނ��ς��̂Ői�߂Ă���
			}
			if (strcmp(&str0[0], CHARACTERSET) == 0)
			{// �L�����N�^�[��񂪏�����Ă�����
				while (strcmp(&str0[0], END_CHARACTERSET) != 0)
				{// �L�����N�^�[��񂪏I���܂œǂݎ��
					if (strcmp(&str0[0], MOVE) == 0)
					{// �ړ��͂�������Ă�����
						if (fscanf(pFile, "%s %f", &str0[0], &fMovement) == 2)
						{// �ړ��͂�ǂݎ������
							g_Player[nCntPlayer].fMovement = fMovement;
						}
					}
					if (strcmp(&str0[0], JUMP) == 0)
					{// �W�����v�͂�������Ă�����
						if (fscanf(pFile, "%s %f", &str0[0], &fJump) == 2)
						{// �W�����v�͂�ǂݎ������
							g_Player[nCntPlayer].fJumpPower = fJump;
						}
					}

					if (strcmp(&str0[0], PARTSSET) == 0)
					{// ���f���̃p�[�c��񂪏�����Ă�����
						int nCntSet = 0;
						int nCntPartsNum = 0;
						while (strcmp(&str0[0], END_PARTSSET) != 0)
						{// ���f���̃p�[�c��񂪏I���܂œǂݎ��
							if (strcmp(&str0[0], INDEX) == 0)
							{// �p�[�c�ԍ���ǂݎ��
								fscanf(pFile, "%s %d", &str0[0], &nCntPartsNum);
							}
							else if (strcmp(&str0[0], PARENT) == 0)
							{// �e���f���̔ԍ���ǂݎ��
								if (fscanf(pFile, "%s %d", &str0[0], &nIdxParent) == 2)
								{// �e���f���̔ԍ���ǂݎ��
									g_Player[nCntPlayer].aModel[nCntPartsNum].nIdxModelParent = nIdxParent;
								}
							}
							else if (strcmp(&str0[0], POS) == 0)
							{// �e���f������̋�����ǂݎ��
								if (fscanf(pFile, "%s %f %f %f", &str0[0], &OffsetPos.x, &OffsetPos.y, &OffsetPos.z) == 4)
								{// ���W����ǂݎ������
									g_Player[nCntPlayer].aModel[nCntPartsNum].pos = OffsetPos;
								}
							}
							else if (strcmp(&str0[0], ROT) == 0)
							{// �e���f������̌�����ǂݎ��
								if (fscanf(pFile, "%s %f %f %f", &str0[0], &OffsetRot.x, &OffsetRot.y, &OffsetRot.z) == 4)
								{// ��������ǂݎ������
									g_Player[nCntPlayer].aModel[nCntPartsNum].rot = OffsetRot;
								}
							}
							fscanf(pFile, "%s", &str0[0]); // �t�@�C����ǂݐi�߂�
							nCntSet++;                     // �Z�b�g�����񐔂𑝂₷
						}
					}
					fscanf(pFile, "%s", &str0[0]); // �t�@�C����ǂݐi�߂�
				}
			}
			if (strcmp(&str0[0], MOTIONSET) == 0)
			{// ���[�V������񂪏�����Ă�����
				nCntKey = 0;    // �L�[�t���[���̃|�C���^���W��߂�
				while (strcmp(&str0[0], END_MOTIONSET) != 0)
				{// ���[�V������񂪏I���܂œǂݎ��
					if (strcmp(&str0[0], LOOP) == 0)
					{// ���[�v���邩���Ȃ�����ǂݎ��
						if (fscanf(pFile, "%s %d", &str0[0], &bLoop) == 2)
						{// ���[�v���邩���Ȃ�����ǂݎ�ꂽ
							if (bLoop == 1)
							{
								g_Player[nCntPlayer].aMotion[nCntMotion].bLoop = true;
							}
							else
							{
								g_Player[nCntPlayer].aMotion[nCntMotion].bLoop = false;
							}
						}
					}
					else if (strcmp(&str0[0], NUM_KEY) == 0)
					{// �L�[�t���[������ǂݎ��
						if (fscanf(pFile, "%s %d", &str0[0], &nNumKey) == 2)
						{// �L�[�t���[������ǂݎ�ꂽ
							g_Player[nCntPlayer].aMotion[nCntMotion].nNumKey = nNumKey;
						}
					}
					else if (strcmp(&str0[0], KEYSET) == 0)
					{// �L�[�t���[����񂪏�����Ă�����
						nCntKeyModel = 0;
						while (strcmp(&str0[0], FRAME) != 0)
						{// �L�[�t���[������񂪏I���܂œǂݎ��
							fscanf(pFile, "%s", &str0[0]); // �t�@�C����ǂݐi�߂�
						}
						if (fscanf(pFile, "%s %d", &str0[0], &nPlaybackKey) == 2)
						{// �L�[�t���[������ǂݎ�ꂽ
							g_Player[nCntPlayer].aMotion[nCntMotion].Key[nCntKey].nPlayBackKey = nPlaybackKey;
						}
						while (strcmp(&str0[0], END_KEYSET) != 0)
						{// �L�[�t���[����񂪏I���܂œǂݎ��
							if (strcmp(&str0[0], KEY) == 0)
							{// �L�[�t���[���̖ړI�̈ʒu��񂪏�����Ă�����
								while (strcmp(&str0[0], END_KEY) != 0)
								{// �L�[�t���[���̖ړI�̈ʒu��񂪏I���܂œǂݎ��
									if (strcmp(&str0[0], POS) == 0)
									{// ���W����ǂݎ��
										if (fscanf(pFile, "%s %f %f %f", &str0[0], &posAdd.x, &posAdd.y, &posAdd.z) == 4)
										{// ���W����ǂݎ������
											g_Player[nCntPlayer].aMotion[nCntMotion].Key[nCntKey].posAdd[nCntKeyModel] = posAdd;
										}
									}
									else if (strcmp(&str0[0], ROT) == 0)
									{// ��������ǂݎ��
										if (fscanf(pFile, "%s %f %f %f", &str0[0], &DestAngle.x, &DestAngle.y, &DestAngle.z) == 4)
										{// ��������ǂݎ������
											g_Player[nCntPlayer].aMotion[nCntMotion].Key[nCntKey].DestAngle[nCntKeyModel] = DestAngle;
										}
									}
									fscanf(pFile, "%s", &str0[0]); // �t�@�C����ǂݐi�߂�
								}
								if (nCntKeyModel < MAX_MODEL - 1)
								{// ���f�����Ƃ̃L�[�t���[�����p�ӂł��鐔�܂ł��|�C���^���i��łȂ�
									nCntKeyModel++;
								}
							}
							fscanf(pFile, "%s", &str0[0]); // �t�@�C����ǂݐi�߂�
						}
						if (nCntKey < MAX_MODEL - 1)
						{// �L�[�t���[�����p�ӂł��鐔�܂ł��|�C���^���i��łȂ�
							nCntKey++;
						}
					}
					fscanf(pFile, "%s", &str0[0]); // �t�@�C����ǂݐi�߂�
				}
				if (nCntMotion < MAX_MOTION - 1)
				{// ���[�V�������p�ӂł��鐔�܂ł��|�C���^���i��łȂ�
					nCntMotion++;   // ���[�V�����ԍ������炷
				}
			}
		}
		// �t�@�C������đ��̃v���O�������炢�����悤�ɂ���
		fclose(pFile);
	}



	// ���l������������
	nCntModel = 0;    // ���f����ǂݍ��񂾐��𐔂���ϐ�
	nCntParts = 0;    // ���f���̃p�[�c����ǂݍ��񂾉񐔂𐔂���ϐ�
	nCntMotion = 0;   // ���[�V�����̔ԍ�
	nCntKey = 0;      // �L�[�t���[���̔ԍ��𐔂���ϐ�
	nPlaybackKey;     // �t���[����
	nCntKeyModel = 0; // ���f���̐����̃L�[�t���[���𐔂���ϐ�
	bLoop;            // ���[�V���������[�v���邩���Ȃ���
	nNumKey = 0;      // �L�[�t���[���̐�
	nCntModel = 0;    // ���f����


	nCntPlayer++;     // �v���C���[�̐l���𑝂₷

	//-------------------
	//  �v���C���[2�l��
	//-------------------
	// �t�@�C���I�[�v��
	pFile = fopen("data/TEXT/motion_01.txt", "r");

	if (pFile != NULL)
	{// �t�@�C�����J����
		while (fscanf(pFile, "%s", &str0[0]) != EOF)
		{// �e�L�X�g�t�@�C���̖��[�܂ŕ���������s���󔒂�����܂œǂݎ��
			if (strcmp(&str0[0], NUM_MODEL) == 0)
			{// ���f���̐���������Ă�����
				fscanf(pFile, "%s %d", &str0[0], &g_nNumModel[nCntPlayer]);
			}
			if (strcmp(&str0[0], MODEL_FILENAME) == 0)
			{// x�t�@�C���̊g���q��������Ă�����
				if (fscanf(pFile, "%s %s", &str0[0], &xFileName[0]) == 2)
				{// ���f���̃t�@�C������ǂݎ������
				 // x�t�@�C���̓ǂݍ���
					D3DXLoadMeshFromX(&xFileName[0],
						D3DXMESH_SYSTEMMEM,
						pDevice,
						NULL,
						&g_Player[nCntPlayer].aModel[nCntModel].pBuffMat,
						NULL,
						&g_Player[nCntPlayer].aModel[nCntModel].nNumMat,
						&g_Player[nCntPlayer].aModel[nCntModel].pMesh);

					// �}�e���A����񂩂�e�N�X�`���������o��
					D3DXMATERIAL* pMat = (D3DXMATERIAL*)g_Player[nCntPlayer].aModel[nCntModel].pBuffMat->GetBufferPointer();
					D3DMATERIAL9* pMatBuff = new D3DMATERIAL9[g_Player[nCntPlayer].aModel[nCntModel].nNumMat];
					g_Player[nCntPlayer].aModel[nCntModel].pTexture = new LPDIRECT3DTEXTURE9[g_Player[nCntPlayer].aModel[nCntModel].nNumMat];

					for (DWORD nCntMat = 0; nCntMat < g_Player[nCntPlayer].aModel[nCntModel].nNumMat; nCntMat++)
					{// ���_���̐������J��Ԃ�
					 // �}�e���A������ǂݍ���
						pMatBuff[nCntMat] = pMat[nCntMat].MatD3D;

						// ����������������
						pMatBuff[nCntMat].Ambient = pMatBuff[nCntMat].Diffuse;

						// �e�N�X�`������������
						g_Player[nCntPlayer].aModel[nCntModel].pTexture[nCntMat] = NULL;

						// �e�N�X�`���̏���ǂݍ���
						if (pMat[nCntMat].pTextureFilename != NULL &&
							lstrlen(pMat[nCntMat].pTextureFilename) > 0)
						{// �e�N�X�`���̃t�@�C����������
							D3DXCreateTextureFromFile(pDevice,
								pMat[nCntMat].pTextureFilename,
								&g_Player[nCntPlayer].aModel[nCntModel].pTexture[nCntMat]);
						}

					}
				}
				nCntModel++;  // ��ނ��ς��̂Ői�߂Ă���
			}
			if (strcmp(&str0[0], CHARACTERSET) == 0)
			{// �L�����N�^�[��񂪏�����Ă�����
				while (strcmp(&str0[0], END_CHARACTERSET) != 0)
				{// �L�����N�^�[��񂪏I���܂œǂݎ��
					if (strcmp(&str0[0], MOVE) == 0)
					{// �ړ��͂�������Ă�����
						if (fscanf(pFile, "%s %f", &str0[0], &fMovement) == 2)
						{// �ړ��͂�ǂݎ������
							g_Player[nCntPlayer].fMovement = fMovement;
						}
					}
					if (strcmp(&str0[0], JUMP) == 0)
					{// �W�����v�͂�������Ă�����
						if (fscanf(pFile, "%s %f", &str0[0], &fJump) == 2)
						{// �W�����v�͂�ǂݎ������
							g_Player[nCntPlayer].fJumpPower = fJump;
						}
					}

					if (strcmp(&str0[0], PARTSSET) == 0)
					{// ���f���̃p�[�c��񂪏�����Ă�����
						int nCntSet = 0;
						int nCntPartsNum = 0;
						while (strcmp(&str0[0], END_PARTSSET) != 0)
						{// ���f���̃p�[�c��񂪏I���܂œǂݎ��
							if (strcmp(&str0[0], INDEX) == 0)
							{// �p�[�c�ԍ���ǂݎ��
								fscanf(pFile, "%s %d", &str0[0], &nCntPartsNum);
							}
							else if (strcmp(&str0[0], PARENT) == 0)
							{// �e���f���̔ԍ���ǂݎ��
								if (fscanf(pFile, "%s %d", &str0[0], &nIdxParent) == 2)
								{// �e���f���̔ԍ���ǂݎ��
									g_Player[nCntPlayer].aModel[nCntPartsNum].nIdxModelParent = nIdxParent;
								}
							}
							else if (strcmp(&str0[0], POS) == 0)
							{// �e���f������̋�����ǂݎ��
								if (fscanf(pFile, "%s %f %f %f", &str0[0], &OffsetPos.x, &OffsetPos.y, &OffsetPos.z) == 4)
								{// ���W����ǂݎ������
									g_Player[nCntPlayer].aModel[nCntPartsNum].pos = OffsetPos;
								}
							}
							else if (strcmp(&str0[0], ROT) == 0)
							{// �e���f������̌�����ǂݎ��
								if (fscanf(pFile, "%s %f %f %f", &str0[0], &OffsetRot.x, &OffsetRot.y, &OffsetRot.z) == 4)
								{// ��������ǂݎ������
									g_Player[nCntPlayer].aModel[nCntPartsNum].rot = OffsetRot;
								}
							}
							fscanf(pFile, "%s", &str0[0]); // �t�@�C����ǂݐi�߂�
							nCntSet++;                     // �Z�b�g�����񐔂𑝂₷
						}
					}
					fscanf(pFile, "%s", &str0[0]); // �t�@�C����ǂݐi�߂�
				}
			}
			if (strcmp(&str0[0], MOTIONSET) == 0)
			{// ���[�V������񂪏�����Ă�����
				nCntKey = 0;    // �L�[�t���[���̃|�C���^���W��߂�
				while (strcmp(&str0[0], END_MOTIONSET) != 0)
				{// ���[�V������񂪏I���܂œǂݎ��
					if (strcmp(&str0[0], LOOP) == 0)
					{// ���[�v���邩���Ȃ�����ǂݎ��
						if (fscanf(pFile, "%s %d", &str0[0], &bLoop) == 2)
						{// ���[�v���邩���Ȃ�����ǂݎ�ꂽ
							if (bLoop == 1)
							{
								g_Player[nCntPlayer].aMotion[nCntMotion].bLoop = true;
							}
							else
							{
								g_Player[nCntPlayer].aMotion[nCntMotion].bLoop = false;
							}
						}
					}
					else if (strcmp(&str0[0], NUM_KEY) == 0)
					{// �L�[�t���[������ǂݎ��
						if (fscanf(pFile, "%s %d", &str0[0], &nNumKey) == 2)
						{// �L�[�t���[������ǂݎ�ꂽ
							g_Player[nCntPlayer].aMotion[nCntMotion].nNumKey = nNumKey;
						}
					}
					else if (strcmp(&str0[0], KEYSET) == 0)
					{// �L�[�t���[����񂪏�����Ă�����
						nCntKeyModel = 0;
						while (strcmp(&str0[0], FRAME) != 0)
						{// �L�[�t���[������񂪏I���܂œǂݎ��
							fscanf(pFile, "%s", &str0[0]); // �t�@�C����ǂݐi�߂�
						}
						if (fscanf(pFile, "%s %d", &str0[0], &nPlaybackKey) == 2)
						{// �L�[�t���[������ǂݎ�ꂽ
							g_Player[nCntPlayer].aMotion[nCntMotion].Key[nCntKey].nPlayBackKey = nPlaybackKey;
						}
						while (strcmp(&str0[0], END_KEYSET) != 0)
						{// �L�[�t���[����񂪏I���܂œǂݎ��
							if (strcmp(&str0[0], KEY) == 0)
							{// �L�[�t���[���̖ړI�̈ʒu��񂪏�����Ă�����
								while (strcmp(&str0[0], END_KEY) != 0)
								{// �L�[�t���[���̖ړI�̈ʒu��񂪏I���܂œǂݎ��
									if (strcmp(&str0[0], POS) == 0)
									{// ���W����ǂݎ��
										if (fscanf(pFile, "%s %f %f %f", &str0[0], &posAdd.x, &posAdd.y, &posAdd.z) == 4)
										{// ���W����ǂݎ������
											g_Player[nCntPlayer].aMotion[nCntMotion].Key[nCntKey].posAdd[nCntKeyModel] = posAdd;
										}
									}
									else if (strcmp(&str0[0], ROT) == 0)
									{// ��������ǂݎ��
										if (fscanf(pFile, "%s %f %f %f", &str0[0], &DestAngle.x, &DestAngle.y, &DestAngle.z) == 4)
										{// ��������ǂݎ������
											g_Player[nCntPlayer].aMotion[nCntMotion].Key[nCntKey].DestAngle[nCntKeyModel] = DestAngle;
										}
									}
									fscanf(pFile, "%s", &str0[0]); // �t�@�C����ǂݐi�߂�
								}
								if (nCntKeyModel < MAX_MODEL - 1)
								{// ���f�����Ƃ̃L�[�t���[�����p�ӂł��鐔�܂ł��|�C���^���i��łȂ�
									nCntKeyModel++;
								}
							}
							fscanf(pFile, "%s", &str0[0]); // �t�@�C����ǂݐi�߂�
						}
						if (nCntKey < MAX_MODEL - 1)
						{// �L�[�t���[�����p�ӂł��鐔�܂ł��|�C���^���i��łȂ�
							nCntKey++;
						}
					}
					fscanf(pFile, "%s", &str0[0]); // �t�@�C����ǂݐi�߂�
				}
				if (nCntMotion < MAX_MOTION - 1)
				{// ���[�V�������p�ӂł��鐔�܂ł��|�C���^���i��łȂ�
					nCntMotion++;   // ���[�V�����ԍ������炷
				}
			}
		}
		// �t�@�C������đ��̃v���O�������炢�����悤�ɂ���
		fclose(pFile);
	}




	for (nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{// �v���C���[�̐������J��Ԃ�
		g_Player[nCntPlayer].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);           // �ړ��ʂ�������
		g_Player[nCntPlayer].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);            // ���݂̌�����������
		g_Player[nCntPlayer].DiffAngle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);      // ������������
		g_Player[nCntPlayer].state = PLAYERSTATE_NORMAL;                     // �ʏ�̏�Ԃ�
		g_Player[nCntPlayer].radius = D3DXVECTOR3(11.5f, 30.0f, 11.5f);      // �����蔻������͈͂�������
		g_Player[nCntPlayer].ShadowCol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.35f); // �e�̐F��ݒ�
		g_Player[nCntPlayer].ShadowWidth = 15;                               // �e�̕���ݒ�
		g_Player[nCntPlayer].ShadowDepth = 15;                               // �e�̉��s��ݒ�
		g_Player[nCntPlayer].bJump = false;                                  // �W�����v���Ă��Ȃ���Ԃ�
		g_Player[nCntPlayer].bWeakAction = false;                            // ��U�����Ă��Ȃ���Ԃ�
		g_Player[nCntPlayer].bStorongAction = false;                         // ���U�����Ă��Ȃ���Ԃ�
		g_Player[nCntPlayer].bHit = false;                                   // �U�����q�b�g���Ă��Ȃ���Ԃ�
		g_Player[nCntPlayer].bControll = true;                               // �ړ��ł����Ԃ�
		g_Player[nCntPlayer].nLife = PlAYER_MAX_LIFE;                        // �̗�
		g_Player[nCntPlayer].wAttackNumber = WEAK_ATTACK_NUMBER_0;           // ��U���̔ԍ�
		g_Player[nCntPlayer].mState = MOTIONSTATE_NORMAL;                    // ���[�V�����̏�Ԃ͒ʏ�̏�Ԃ�

		for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
		{// ���f���̃p�[�c�����J��Ԃ�
			g_Player[nCntPlayer].aModel[nCntModel].posStd = g_Player[nCntPlayer].aModel[nCntModel].pos;
			g_Player[nCntPlayer].aModel[nCntModel].rot = g_Player[nCntPlayer].aMotion[g_Player[nCntPlayer].state].Key[g_Player[nCntPlayer].nKey].DestAngle[nCntModel];
		}

		// �e�̔ԍ���ݒ�
		g_Player[nCntPlayer].nIdxShadow = SetShadow(D3DXVECTOR3(g_Player[nCntPlayer].pos.x, 1.0f, g_Player[nCntPlayer].pos.z), g_Player[nCntPlayer].rot, g_Player[nCntPlayer].ShadowCol, g_Player[nCntPlayer].ShadowWidth, g_Player[nCntPlayer].ShadowDepth);

		// ���[�V�����J�ڏ���
		SwitchMotion(nCntPlayer);
	}

	g_Player[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);            // ���݂̈ʒu��������
	g_Player[0].posold = D3DXVECTOR3(0.0f, 0.0f, 0.0f);         // ���݂̈ʒu��������
	g_Player[0].rot = D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 0.0f);  // ���݂̈ʒu��������
	g_Player[0].DestAngle = D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 0.0f);      // �ړI�̌�����������

	g_Player[1].pos = D3DXVECTOR3(200.0f, 0.0f, 0.0f);     // ���݂̈ʒu��������
	g_Player[1].posold = D3DXVECTOR3(200.0f, 0.0f, 0.0f);  // ���݂̈ʒu��������
	g_Player[1].rot = D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f);  // ���݂̈ʒu��������
	g_Player[1].DestAngle = D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f);      // �ړI�̌�����������
}

//=============================================================================
// �I������
//=============================================================================
void UninitPlayer(void)
{
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{// �v���C���[�̐������J��Ԃ�
		for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
		{// ���f���̃p�[�c�������J��Ԃ�
		    // ���b�V���̔j��
			if (g_Player[nCntPlayer].aModel[nCntModel].pMesh != NULL)
			{
				g_Player[nCntPlayer].aModel[nCntModel].pMesh->Release();
				g_Player[nCntPlayer].aModel[nCntModel].pMesh = NULL;
			}

			// �}�e���A���̔j��
			if (g_Player[nCntPlayer].aModel[nCntModel].pBuffMat != NULL)
			{
				g_Player[nCntPlayer].aModel[nCntModel].pBuffMat->Release();
				g_Player[nCntPlayer].aModel[nCntModel].pBuffMat = NULL;
			}

			// �e�N�X�`���̔j��
			for (DWORD nCntMat = 0; nCntMat < g_Player[nCntPlayer].aModel[nCntModel].nNumMat; nCntMat++)
			{
				if (g_Player[nCntPlayer].aModel[nCntModel].pTexture[nCntMat] != NULL)
				{
					g_Player[nCntPlayer].aModel[nCntModel].pTexture[nCntMat]->Release();
					g_Player[nCntPlayer].aModel[nCntModel].pTexture[nCntMat] = NULL;
				}
			}
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePlayer(void)
{
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{// �v���C���[�̐������J��Ԃ�
		g_Player[nCntPlayer].posold = g_Player[nCntPlayer].pos;

		if (g_Player[nCntPlayer].bWeakAction != true && g_Player[nCntPlayer].bStorongAction != true && g_Player[nCntPlayer].bControll == true && g_Player[nCntPlayer].bUltimate != true)
		{// �������Ԃł���
			// �ړ�����
			PlayerOperation(nCntPlayer);
		}

		// ����ł���v���C���[�̑J�ڏ���
		if (g_Player[nCntPlayer].bControll == true)
		{// �v���C���[������ł����Ԃł���
			PlayerTransition(nCntPlayer);
		}

		// �v���C���[�̏�ԊǗ�����
		PlayerStateMent(nCntPlayer);

		// �v���C���[�̃A�N�V��������
		PlayerAction(nCntPlayer);

		if (g_Player[nCntPlayer].mState == MOTIONSTATE_NORMAL)
		{// �ʏ�̃��[�V������Ԃ�������
		    // ���[�V��������
			PlayerMotion(nCntPlayer);
		}
		else if (g_Player[nCntPlayer].mState == MOTIONSTATE_SWITCH)
		{// ���[�V�����؂�ւ���Ԃ�������
		    // ���[�V�����u�����h����
			PlayerMotionBlend(nCntPlayer);
		}

		if (g_Player[nCntPlayer].mState == MOTIONSTATE_NORMAL)
		{// �L�[�t���[����i�߂��Ԃ�������
			// ���[�V�����i�s����
			PlayerMotionAdvance(nCntPlayer);
		}

		// �ǂ̓����蔻��
		CollisionPlayer(nCntPlayer);

		// �v���C���[�̍U������
		PlayerAttack(nCntPlayer);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans, mtxParent;     // �v�Z�p�}�g���b�N�X
	D3DXVECTOR3 vecRot, vecTrans;               // �v�Z�p���f���̌���,���W
	D3DMATERIAL9 matDef;                        // ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;                         // �}�e���A���f�[�^�ւ̃|�C���^
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{// �v���C���[�̐������J��Ԃ�
	   // ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_Player[nCntPlayer].mtxWorld);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player[nCntPlayer].rot.y, g_Player[nCntPlayer].rot.x, g_Player[nCntPlayer].rot.z);
		D3DXMatrixMultiply(&g_Player[nCntPlayer].mtxWorld, &g_Player[nCntPlayer].mtxWorld, &mtxRot);

		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_Player[nCntPlayer].pos.x, g_Player[nCntPlayer].pos.y, g_Player[nCntPlayer].pos.z);
		D3DXMatrixMultiply(&g_Player[nCntPlayer].mtxWorld, &g_Player[nCntPlayer].mtxWorld, &mtxTrans);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_Player[nCntPlayer].mtxWorld);

		for (int nCntModel = 0; nCntModel < g_nNumModel[nCntPlayer]; nCntModel++)
		{// ���f���̃p�[�c�������J��Ԃ�
			if (g_Player[nCntPlayer].aModel[nCntModel].nIdxModelParent == -1)
			{// �e�����Ȃ�
				mtxParent = g_Player[nCntPlayer].mtxWorld;     // �v���C���[�̃}�g���b�N�X�������炤
			}
			else
			{// �e������
				mtxParent = g_Player[nCntPlayer].aModel[g_Player[nCntPlayer].aModel[nCntModel].nIdxModelParent].mtxWorld;   // �e���f���̃}�g���b�N�X�������炤
			}
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Player[nCntPlayer].aModel[nCntModel].mtxWorld);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player[nCntPlayer].aModel[nCntModel].rot.y, g_Player[nCntPlayer].aModel[nCntModel].rot.x, g_Player[nCntPlayer].aModel[nCntModel].rot.z);
			D3DXMatrixMultiply(&g_Player[nCntPlayer].aModel[nCntModel].mtxWorld, &g_Player[nCntPlayer].aModel[nCntModel].mtxWorld, &mtxRot);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_Player[nCntPlayer].aModel[nCntModel].pos.x, g_Player[nCntPlayer].aModel[nCntModel].pos.y, g_Player[nCntPlayer].aModel[nCntModel].pos.z);
			D3DXMatrixMultiply(&g_Player[nCntPlayer].aModel[nCntModel].mtxWorld, &g_Player[nCntPlayer].aModel[nCntModel].mtxWorld, &mtxTrans);

			// �e�̏��������ɔ��f
			D3DXMatrixMultiply(&g_Player[nCntPlayer].aModel[nCntModel].mtxWorld, &g_Player[nCntPlayer].aModel[nCntModel].mtxWorld, &mtxParent);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Player[nCntPlayer].aModel[nCntModel].mtxWorld);

			// ���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			// �}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_Player[nCntPlayer].aModel[nCntModel].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_Player[nCntPlayer].aModel[nCntModel].nNumMat; nCntMat++)
			{// �ݒ肳��Ă����}�e���A���̐������J��Ԃ�
			 // �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_Player[nCntPlayer].aModel[nCntModel].pTexture[nCntMat]);

				// ���f��(�p�[�c)�̕`��
				g_Player[nCntPlayer].aModel[nCntModel].pMesh->DrawSubset(nCntMat);
			}

			// �ۑ����Ă����}�e���A���ɖ߂�
			pDevice->SetMaterial(&matDef);
		}
	}
}
//=============================================================================
// �v���C���[�̑��쏈��
//=============================================================================
void PlayerOperation(int nCntPlayer)
{
	if (g_Player[nCntPlayer].bJump != true)
	{// �W�����v���Ă��Ȃ�
		g_Player[nCntPlayer].posold = g_Player[nCntPlayer].pos;   // �O��̈ʒu�X�V
		if (GetXInputPress(nCntPlayer, XIJS_BUTTON_3) == true)
		{// �\���L�[�E���͂����ꂽ
			g_Player[nCntPlayer].move.x += sinf(D3DX_PI * 0.5f) *  g_Player[nCntPlayer].fMovement;
			if (g_Player[nCntPlayer].bJump != true)
			{
				g_Player[nCntPlayer].DestAngle.y = -D3DX_PI * 0.5f;
			}
		}
		else if (GetXInputPress(nCntPlayer, XIJS_BUTTON_2) == true)
		{// �\���L�[�����͂����ꂽ
			g_Player[nCntPlayer].move.x -= sinf(D3DX_PI * 0.5f) *  g_Player[nCntPlayer].fMovement;
			if (g_Player[nCntPlayer].bJump != true)
			{
				g_Player[nCntPlayer].DestAngle.y = D3DX_PI * 0.5f;
			}
		}
		else if (GetXInputPress(nCntPlayer, XIJS_BUTTON_26) == true || GetXInputPress(nCntPlayer, XIJS_BUTTON_27) == true)
		{// ���A�i���O�X�e�B�b�N�̓��͂����ꂽ
			// �ړ�����
			g_Player[nCntPlayer].move.x += sinf(GetXInputLeftAxiz(nCntPlayer)) * g_Player[nCntPlayer].fMovement;
			if (g_Player[nCntPlayer].bJump != true)
			{
				if (GetXInputPress(nCntPlayer, XIJS_BUTTON_26) == true)
				{// ���ɓ|����Ă���
					g_Player[nCntPlayer].DestAngle.y = D3DX_PI * 0.5f;
				}
				if (GetXInputPress(nCntPlayer, XIJS_BUTTON_27) == true)
				{// �E�ɓ|����Ă���
					g_Player[nCntPlayer].DestAngle.y = -D3DX_PI * 0.5f;
				}
			}
		}
	}
}
//=============================================================================
// �v���C���[�̏�ԑJ�ڏ���
//=============================================================================
void PlayerTransition(int nCntPlayer)
{
	if (g_Player[nCntPlayer].bJump == false && g_Player[nCntPlayer].bWeakAction != true && g_Player[nCntPlayer].bStorongAction != true
		&& g_Player[nCntPlayer].bUltimate != true && g_Player[nCntPlayer].state != PLAYERSTATE_ULTIMATE_START)
	{// �W�����v���Ă��Ȃ����A�N�V������ԂłȂ�
		if (g_Player[nCntPlayer].move.x <= 1.0f && g_Player[nCntPlayer].move.x >= -1.0f &&
			g_Player[nCntPlayer].move.z <= 1.0f && g_Player[nCntPlayer].move.z >= -1.0f)
		{// �ړ����Ă��Ȃ�������
			if (g_Player[nCntPlayer].state != PLAYERSTATE_NORMAL)
			{// �ړ����Ă��Ȃ���Ԃ���Ȃ�������
				g_Player[nCntPlayer].state = PLAYERSTATE_NORMAL;     // �ʏ�̏�Ԃ�
				// ���[�V�����؂�ւ�����
				SwitchMotion(nCntPlayer);
			}
		}
		if (g_Player[nCntPlayer].move.x > 1.0f || g_Player[nCntPlayer].move.x < -1.0f ||
			g_Player[nCntPlayer].move.z > 1.0f || g_Player[nCntPlayer].move.z < -1.0f)
		{// �ړ����Ă�����
			if (g_Player[nCntPlayer].state != PLAYERSTATE_MOVE)
			{// �ړ����Ă����Ԃ���Ȃ�������
				g_Player[nCntPlayer].state = PLAYERSTATE_MOVE;       // �ړ����Ă����Ԃ�
				// ���[�V�����؂�ւ�����
				SwitchMotion(nCntPlayer);
			}
		}
	}

	if (g_Player[nCntPlayer].bDown == true)
	{// �v���C���[���_�E�����Ă���
		g_Player[nCntPlayer].nStateMentCounter++;
		if (g_Player[nCntPlayer].nStateMentCounter >= 30)
		{
			g_Player[nCntPlayer].nStateMentCounter = 0;
			g_Player[nCntPlayer].bDown = false;
		}
	}
}

//=============================================================================
// �v���C���[�̏�ԑJ�ڏ���
//=============================================================================
void PlayerStateMent(int nCntPlayer)
{
	// �d�͂����Z����
	g_Player[nCntPlayer].move.y += GRAVITY_POWER;

	// �ʒu���ړ�
	g_Player[nCntPlayer].pos.x += g_Player[nCntPlayer].move.x;
	g_Player[nCntPlayer].pos.y += g_Player[nCntPlayer].move.y;
	g_Player[nCntPlayer].pos.z += g_Player[nCntPlayer].move.z;

	// �p�x�̏C��
	g_Player[nCntPlayer].DiffAngle.y = g_Player[nCntPlayer].DestAngle.y - g_Player[nCntPlayer].rot.y;   // ���݂̌����ƖړI�̌����̍������v�Z

	if (g_Player[nCntPlayer].DiffAngle.y > D3DX_PI)
	{// ������D3DX_PI�𒴂���
		g_Player[nCntPlayer].DiffAngle.y -= D3DX_PI * 2.0f;
	}
	if (g_Player[nCntPlayer].DiffAngle.y < -D3DX_PI)
	{// ������-D3DX_PI�𒴂���
		g_Player[nCntPlayer].DiffAngle.y += D3DX_PI * 2.0f;
	}

	g_Player[nCntPlayer].rot.y += g_Player[nCntPlayer].DiffAngle.y * 0.1f;

	if (g_Player[nCntPlayer].rot.y > D3DX_PI)
	{// ���݂̌�����D3DX_PI�𒴂���
		g_Player[nCntPlayer].rot.y -= D3DX_PI * 2.0f;
	}
	if (g_Player[nCntPlayer].rot.y < -D3DX_PI)
	{// ���݂̌�����-D3DX_PI�𒴂���
		g_Player[nCntPlayer].rot.y += D3DX_PI * 2.0f;
	}

	// �e�̈ʒu�X�V
	SetPositionShadow(g_Player[nCntPlayer].nIdxShadow, D3DXVECTOR3(g_Player[nCntPlayer].pos.x, 1.0f, g_Player[nCntPlayer].pos.z));

	// �e�̐F�X�V
	SetColShadow(g_Player[nCntPlayer].nIdxShadow, g_Player[nCntPlayer].ShadowCol);

	// �e�̑傫���X�V
	SetSizeShadow(g_Player[nCntPlayer].nIdxShadow, g_Player[nCntPlayer].ShadowWidth, g_Player[nCntPlayer].ShadowDepth);

	if (g_Player[nCntPlayer].pos.y < 0.0f)
	{// ���n����
		g_Player[nCntPlayer].pos.y = 0.0f;         // �ʒu��߂�
		g_Player[nCntPlayer].move.y = 0.0f;        // �d�͂�����
		g_Player[nCntPlayer].ShadowWidth = 15;     // �e�̕���߂�
		g_Player[nCntPlayer].ShadowDepth = 15;     // �e�̉��s��߂�
		g_Player[nCntPlayer].ShadowCol.a = 0.15f;  // �e�̓����x��߂�
		if (g_Player[nCntPlayer].state == PLAYERSTATE_JUMP)
		{// �W�����v��Ԃ�������
			if (g_Player[nCntPlayer].bJump == true)
			{// �W�����v���Ă���
				if (g_Player[nCntPlayer].move.x <= 1.0f && g_Player[nCntPlayer].move.x >= -1.0f &&
					g_Player[nCntPlayer].move.z <= 1.0f && g_Player[nCntPlayer].move.z >= -1.0f)
				{// �ړ����Ă��Ȃ�������
					g_Player[nCntPlayer].state = PLAYERSTATE_NORMAL;        // ���n��Ԃ�
																			// ���[�V�����؂�ւ�����
					SwitchMotion(nCntPlayer);
					g_Player[nCntPlayer].move.x = 0.0f;   // �ړ��𖳎�����
					g_Player[nCntPlayer].move.z = 0.0f;   // �ړ��𖳎�����

				}
				else if (g_Player[nCntPlayer].move.x > 1.0f || g_Player[nCntPlayer].move.x < -1.0f ||
					g_Player[nCntPlayer].move.z > 1.0f || g_Player[nCntPlayer].move.z < -1.0f)
				{// �ړ����Ă�����
					g_Player[nCntPlayer].state = PLAYERSTATE_MOVE;           // �ړ����Ă����Ԃ�
																			 // ���[�V�����؂�ւ�����
					SwitchMotion(nCntPlayer);
				}
			}
			PlaySound(SOUND_LABEL_SE_LANDING);
		}
		else if (g_Player[nCntPlayer].state == PLAYERSTATE_DAMAGE_FLY)
		{// ������я�Ԃ�������
			g_Player[nCntPlayer].state = PLAYERSTATE_DAMAGE_DOWN;
			SwitchMotion(nCntPlayer);
			PlaySound(SOUND_LABEL_SE_DOWN);
			g_Player[nCntPlayer].move.x = 0.0f;
		}
		g_Player[nCntPlayer].bJump = false;      // �W�����v���Ă��Ȃ������
	}

	// �����𓭂�����
	if (g_Player[nCntPlayer].bJump == false)
	{// �W�����v���Ă��Ȃ�������
		g_Player[nCntPlayer].move.x += (0.0f - g_Player[nCntPlayer].move.x) * PLAYER_INERTIA_NORMAL;
		g_Player[nCntPlayer].move.z += (0.0f - g_Player[nCntPlayer].move.z) * PLAYER_INERTIA_NORMAL;
	}
	else if (g_Player[nCntPlayer].bJump == true)
	{// �W�����v���Ă�����
		g_Player[nCntPlayer].move.x += (0.0f - g_Player[nCntPlayer].move.x) * PLAYER_INERTIA_JUMP;
		g_Player[nCntPlayer].move.z += (0.0f - g_Player[nCntPlayer].move.z) * PLAYER_INERTIA_JUMP;
	}

	if (g_Player[nCntPlayer].bJump == true)
	{// �W�����v���Ă�����
		if (g_Player[nCntPlayer].move.y > 0.0f)
		{// �󒆂ɏオ���Ă���
			g_Player[nCntPlayer].ShadowWidth -= 0.3f;
			g_Player[nCntPlayer].ShadowDepth -= 0.3f;
			g_Player[nCntPlayer].ShadowCol.a -= 0.006f;
		}
		else if (g_Player[nCntPlayer].move.y < 0.0f)
		{// �n��ɗ����Ă���
			g_Player[nCntPlayer].ShadowWidth += 0.3f;
			g_Player[nCntPlayer].ShadowDepth += 0.3f;
			g_Player[nCntPlayer].ShadowCol.a += 0.006f;
		}
	}
}

//=============================================================================
// �v���C���[���A�N�V������Ԃ̎��̏���
//=============================================================================
void PlayerAction(int nCntPlayer)
{
	if (g_Player[nCntPlayer].bControll == true)
	{// ����ł����Ԃł���
		if (GetKeyboardTrigger(DIK_SPACE) == true || GetXInputTrigger(nCntPlayer, XIJS_BUTTON_24) == true || GetXInputTrigger(nCntPlayer, XIJS_BUTTON_0) == true)
		{// �W�����v�{�^���������ꂽ
			if (g_Player[nCntPlayer].bJump == false)
			{// �W�����v���Ă��Ȃ�
				g_Player[nCntPlayer].move.y += g_Player[nCntPlayer].fJumpPower;   // �㏸������
				g_Player[nCntPlayer].move.x = 0.0f;
				if (GetXInputTrigger(nCntPlayer, XIJS_BUTTON_0) == true)
				{// �\���L�[����͂�����Ă���
					if (GetXInputTrigger(nCntPlayer, XIJS_BUTTON_2) == true)
					{// �\���L�[�����͂�����Ă���
						g_Player[nCntPlayer].move.x = sinf((D3DX_PI * -0.5f)) * 5.0f;
					}
					else if (GetXInputTrigger(nCntPlayer, XIJS_BUTTON_3) == true)
					{// �\���L�[�E���͂�����Ă���
						g_Player[nCntPlayer].move.x = sinf((D3DX_PI * 0.5f)) * 5.0f;
					}
				}

				if (GetXInputTrigger(nCntPlayer, XIJS_BUTTON_24) == true)
				{// ���X�e�B�b�N����͂�����Ă���
					if (GetXInputThumbLX(nCntPlayer) <= -3000.0f)
					{// ���X�e�B�b�N���ɓ|����Ă�
						g_Player[nCntPlayer].move.x = sinf((D3DX_PI * -0.5f)) * 5.0f;
					}
					else if (GetXInputThumbLX(nCntPlayer) >= 3000.0f)
					{// ���X�e�B�b�N�E�ɓ|����Ă�
						g_Player[nCntPlayer].move.x = sinf((D3DX_PI * 0.5f)) * 5.0f;
					}
				}

				PlaySound(SOUND_LABEL_SE_JUMP);
				g_Player[nCntPlayer].bJump = true;                                // �W�����v������Ԃ�
				g_Player[nCntPlayer].state = PLAYERSTATE_JUMP;                    // �W�����v��Ԃ�
				// ���[�V�����؂�ւ�����
				SwitchMotion(nCntPlayer);

				// �ʒu���ړ�
				g_Player[nCntPlayer].pos.x += g_Player[nCntPlayer].move.x;
				g_Player[nCntPlayer].pos.y += g_Player[nCntPlayer].move.y;
				g_Player[nCntPlayer].pos.z += g_Player[nCntPlayer].move.z;
			}
		}

		if (GetKeyboardTrigger(DIK_RETURN) == true || GetXInputTrigger(nCntPlayer, XIJS_BUTTON_11) == true)
		{// ��U���{�^���������ꂽ
			if (g_Player[nCntPlayer].bStorongAction != true && g_Player[nCntPlayer].bUltimate != true)
			{// ���U�������Ă��Ȃ�
				if (g_Player[nCntPlayer].wAttackNumber < WEAK_ATTACK_NUMBER_MAX)
				{// ��U���̔h�����I����Ă��Ȃ�
					if (g_Player[nCntPlayer].wAttackNumber == WEAK_ATTACK_NUMBER_0)
					{// �ŏ��̍U���Ȃ��
						g_Player[nCntPlayer].state = (PLAYERSTATE)(g_Player[nCntPlayer].wAttackNumber + 2);
						g_Player[nCntPlayer].wAttackNumber++;
						SwitchMotion(nCntPlayer);
					}
					else
					{// ����ȊO�̍U��
						g_Player[nCntPlayer].state = (PLAYERSTATE)(g_Player[nCntPlayer].wAttackNumber + 2);
						g_Player[nCntPlayer].wAttackNumber++;
						SwitchMotion(nCntPlayer);
					}
					g_Player[nCntPlayer].bWeakAction = true;   // ��U�����Ă����Ԃ�
					g_Player[nCntPlayer].bHit = false;         // �U�����q�b�g���Ă��Ȃ������
					PlaySound(SOUND_LABEL_SE_WEAKPUNCH);
				}
			}
		}

		if (GetKeyboardTrigger(DIK_RETURN) == true || GetXInputTrigger(nCntPlayer, XIJS_BUTTON_10) == true)
		{// ���U���{�^���������ꂽ
			if (g_Player[nCntPlayer].bWeakAction != true && g_Player[nCntPlayer].bUltimate != true)
			{// ��U�������Ă��Ȃ�
				if (g_Player[nCntPlayer].bStorongAction != true)
				{// ���U�������Ă��Ȃ�
					g_Player[nCntPlayer].state = PLAYERSTATE_STORONG_ATTACK;
					SwitchMotion(nCntPlayer);
					g_Player[nCntPlayer].bStorongAction = true;
					g_Player[nCntPlayer].bHit = false;         // �U�����q�b�g���Ă��Ȃ������
					PlaySound(SOUND_LABEL_SE_STORONGPUNCH);
				}
			}
		}

		if (GetXInputTrigger(nCntPlayer, XIJS_BUTTON_13) == true)
		{// �K�E�U���{�^���������ꂽ
			if (GetUltGaugeWidth(nCntPlayer) >= ULTGAUGE_WIDTH)
			{// �K�E�Q�[�W�����^���ł���
			    // �K�E�Q�[�W�����^���ł���
				g_Player[nCntPlayer].state = PLAYERSTATE_ULTIMATE_START;
				SwitchMotion(nCntPlayer);
				g_Player[nCntPlayer].bHit = false;         // �U�����q�b�g���Ă��Ȃ������
			}
		}
	}
}

//=============================================================================
// �v���C���[�̃��[�V����
//=============================================================================
void PlayerMotion(int nCntPlayer)
{
	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{// ���f���̃p�[�c�����J��Ԃ�
	    // ���݂̈ʒu�X�V
		g_Player[nCntPlayer].aModel[nCntModel].pos.x += g_Player[nCntPlayer].aModel[nCntModel].posDiff.x / g_Player[nCntPlayer].aMotion[g_Player[nCntPlayer].state].Key[g_Player[nCntPlayer].nKey].nPlayBackKey;
		g_Player[nCntPlayer].aModel[nCntModel].pos.y += g_Player[nCntPlayer].aModel[nCntModel].posDiff.y / g_Player[nCntPlayer].aMotion[g_Player[nCntPlayer].state].Key[g_Player[nCntPlayer].nKey].nPlayBackKey;
		g_Player[nCntPlayer].aModel[nCntModel].pos.z += g_Player[nCntPlayer].aModel[nCntModel].posDiff.z / g_Player[nCntPlayer].aMotion[g_Player[nCntPlayer].state].Key[g_Player[nCntPlayer].nKey].nPlayBackKey;

		g_Player[nCntPlayer].aModel[nCntModel].rot.x += g_Player[nCntPlayer].aModel[nCntModel].DiffAngle.x / g_Player[nCntPlayer].aMotion[g_Player[nCntPlayer].state].Key[g_Player[nCntPlayer].nKey].nPlayBackKey;

		if (g_Player[nCntPlayer].aModel[nCntModel].rot.x > D3DX_PI)
		{// ���݂̌�����D3DX_PI�𒴂���
			g_Player[nCntPlayer].aModel[nCntModel].rot.x -= D3DX_PI * 2.0f;
		}
		if (g_Player[nCntPlayer].aModel[nCntModel].rot.x < -D3DX_PI)
		{// ���݂̌�����-D3DX_PI�𒴂���
			g_Player[nCntPlayer].aModel[nCntModel].rot.x += D3DX_PI * 2.0f;
		}

		g_Player[nCntPlayer].aModel[nCntModel].rot.y += g_Player[nCntPlayer].aModel[nCntModel].DiffAngle.y / g_Player[nCntPlayer].aMotion[g_Player[nCntPlayer].state].Key[g_Player[nCntPlayer].nKey].nPlayBackKey;

		if (g_Player[nCntPlayer].aModel[nCntModel].rot.y > D3DX_PI)
		{// ���݂̌�����D3DX_PI�𒴂���
			g_Player[nCntPlayer].aModel[nCntModel].rot.y -= D3DX_PI * 2.0f;
		}
		if (g_Player[nCntPlayer].aModel[nCntModel].rot.y < -D3DX_PI)
		{// ���݂̌�����-D3DX_PI�𒴂���
			g_Player[nCntPlayer].aModel[nCntModel].rot.y += D3DX_PI * 2.0f;
		}

		g_Player[nCntPlayer].aModel[nCntModel].rot.z += g_Player[nCntPlayer].aModel[nCntModel].DiffAngle.z / g_Player[nCntPlayer].aMotion[g_Player[nCntPlayer].state].Key[g_Player[nCntPlayer].nKey].nPlayBackKey;

		if (g_Player[nCntPlayer].aModel[nCntModel].rot.z > D3DX_PI)
		{// ���݂̌�����D3DX_PI�𒴂���
			g_Player[nCntPlayer].aModel[nCntModel].rot.z -= D3DX_PI * 2.0f;
		}
		if (g_Player[nCntPlayer].aModel[nCntModel].rot.z < -D3DX_PI)
		{// ���݂̌�����-D3DX_PI�𒴂���
			g_Player[nCntPlayer].aModel[nCntModel].rot.z += D3DX_PI * 2.0f;
		}
	}
}
//=============================================================================
// �v���C���[�̃��[�V�����u�����h����
//=============================================================================
void PlayerMotionBlend(int nCntPlayer)
{
	// �u�����h�J�E���^�[��i�߂�
	g_Player[nCntPlayer].nBlendCounter++;
	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{// ���f���̃p�[�c�����J��Ԃ�
	    // ���݂̈ʒu�X�V
		g_Player[nCntPlayer].aModel[nCntModel].pos.x += g_Player[nCntPlayer].aModel[nCntModel].posDiff.x / (g_Player[nCntPlayer].aMotion[g_Player[nCntPlayer].state].Key[g_Player[nCntPlayer].nKey].nPlayBackKey * 0.3f);
		g_Player[nCntPlayer].aModel[nCntModel].pos.y += g_Player[nCntPlayer].aModel[nCntModel].posDiff.y / (g_Player[nCntPlayer].aMotion[g_Player[nCntPlayer].state].Key[g_Player[nCntPlayer].nKey].nPlayBackKey * 0.3f);
		g_Player[nCntPlayer].aModel[nCntModel].pos.z += g_Player[nCntPlayer].aModel[nCntModel].posDiff.z / (g_Player[nCntPlayer].aMotion[g_Player[nCntPlayer].state].Key[g_Player[nCntPlayer].nKey].nPlayBackKey * 0.3f);

		g_Player[nCntPlayer].aModel[nCntModel].rot.x += g_Player[nCntPlayer].aModel[nCntModel].DiffAngle.x / (g_Player[nCntPlayer].aMotion[g_Player[nCntPlayer].state].Key[g_Player[nCntPlayer].nKey].nPlayBackKey * 0.3f);

		if (g_Player[nCntPlayer].aModel[nCntModel].rot.x > D3DX_PI)
		{// ���݂̌�����D3DX_PI�𒴂���
			g_Player[nCntPlayer].aModel[nCntModel].rot.x -= D3DX_PI * 2.0f;
		}
		if (g_Player[nCntPlayer].aModel[nCntModel].rot.x < -D3DX_PI)
		{// ���݂̌�����-D3DX_PI�𒴂���
			g_Player[nCntPlayer].aModel[nCntModel].rot.x += D3DX_PI * 2.0f;
		}
		g_Player[nCntPlayer].aModel[nCntModel].rot.y += g_Player[nCntPlayer].aModel[nCntModel].DiffAngle.y / (g_Player[nCntPlayer].aMotion[g_Player[nCntPlayer].state].Key[g_Player[nCntPlayer].nKey].nPlayBackKey * 0.3f);

		if (g_Player[nCntPlayer].aModel[nCntModel].rot.y > D3DX_PI)
		{// ���݂̌�����D3DX_PI�𒴂���
			g_Player[nCntPlayer].aModel[nCntModel].rot.y -= D3DX_PI * 2.0f;
		}
		if (g_Player[nCntPlayer].aModel[nCntModel].rot.y < -D3DX_PI)
		{// ���݂̌�����-D3DX_PI�𒴂���
			g_Player[nCntPlayer].aModel[nCntModel].rot.y += D3DX_PI * 2.0f;
		}

		g_Player[nCntPlayer].aModel[nCntModel].rot.z += g_Player[nCntPlayer].aModel[nCntModel].DiffAngle.z / (g_Player[nCntPlayer].aMotion[g_Player[nCntPlayer].state].Key[g_Player[nCntPlayer].nKey].nPlayBackKey * 0.3f);

		if (g_Player[nCntPlayer].aModel[nCntModel].rot.z > D3DX_PI)
		{// ���݂̌�����D3DX_PI�𒴂���
			g_Player[nCntPlayer].aModel[nCntModel].rot.z -= D3DX_PI * 2.0f;
		}
		if (g_Player[nCntPlayer].aModel[nCntModel].rot.z < -D3DX_PI)
		{// ���݂̌�����-D3DX_PI�𒴂���
			g_Player[nCntPlayer].aModel[nCntModel].rot.z += D3DX_PI * 2.0f;
		}
	}

	if (g_Player[nCntPlayer].nBlendCounter >= g_Player[nCntPlayer].aMotion[g_Player[nCntPlayer].state].Key[g_Player[nCntPlayer].nKey].nPlayBackKey * 0.3f)
	{// �u�����h�J�E���^�[������̒l��
		g_Player[nCntPlayer].nBlendCounter = 0;            // �u�����h�J�E���^�[��������
		if (g_Player[nCntPlayer].aMotion[g_Player[nCntPlayer].state].nNumKey >= 2)
		{// �L�[�t���[����2�ȏ゠������
			g_Player[nCntPlayer].mState = MOTIONSTATE_NORMAL;  // ���[�V�����̏�Ԃ�ʏ�̏�Ԃ�
			g_Player[nCntPlayer].nKey++;                       // �L�[�t���[����i�߂�
												   // �L�[�t���[���؂�ւ�����
			SwitchKey(nCntPlayer);
		}
		else
		{// �L�[�t���[��������ȏ�Ȃ�
			g_Player[nCntPlayer].mState = MOTIONSTATE_STOP;    // ���[�V�����̏�Ԃ����[�V�������Ȃ���Ԃ�
		}
	}
}
//=============================================================================
// ���[�V�����i�s����
//=============================================================================
void PlayerMotionAdvance(int nCntPlayer)
{
	g_Player[nCntPlayer].nMotionCounter++;   // ���[�V�����J�E���^�[��i�߂�
	if (g_Player[nCntPlayer].nMotionCounter >= g_Player[nCntPlayer].aMotion[g_Player[nCntPlayer].state].Key[g_Player[nCntPlayer].nKey].nPlayBackKey)
	{// �Đ��t���[�����ɒB����
		if (g_Player[nCntPlayer].nKey == g_Player[nCntPlayer].aMotion[g_Player[nCntPlayer].state].nNumKey - 1)
		{// ���݂̃L�[�t���[���������̃��[�V�����̃L�[�t���[���̑�����������
			if (g_Player[nCntPlayer].aMotion[g_Player[nCntPlayer].state].bLoop == true)
			{// ���[�v���锻�肾������
				g_Player[nCntPlayer].nKey = 0;             // ���݂̃L�[�t���[�������ɖ߂�
				// �L�[�t���[���؂�ւ�����
				SwitchKey(nCntPlayer);
			}
			else
			{// ���[�v���Ȃ����肾������
				if (g_Player[nCntPlayer].bWeakAction == true || g_Player[nCntPlayer].bStorongAction == true)
				{// �A�N�V������Ԃ�������
					g_Player[nCntPlayer].state = PLAYERSTATE_NORMAL;  // �ʏ��Ԃ�

					// ���[�V�����؂�ւ�����
					SwitchMotion(nCntPlayer);
				}
				else if (g_Player[nCntPlayer].state == PLAYERSTATE_DAMAGE)
				{// �_���[�W��Ԃ�������
					if (g_Player[(nCntPlayer + 1) % MAX_PLAYER].bUltimate == false)
					{
						g_Player[nCntPlayer].state = PLAYERSTATE_NORMAL;
						// ���[�V�����؂�ւ�����
						SwitchMotion(nCntPlayer);
						g_Player[nCntPlayer].bControll = true;
					}
					else if(g_Player[(nCntPlayer + 1) % MAX_PLAYER].bUltimate == true)
					{
						g_Player[nCntPlayer].state = PLAYERSTATE_DAMAGE;
						// ���[�V�����؂�ւ�����
						SwitchMotion(nCntPlayer);
					}
				}
				else if (g_Player[nCntPlayer].state == PLAYERSTATE_DAMAGE_DOWN)
				{// �_�E����Ԃ�������
					if (g_Player[nCntPlayer].nLife >= 0)
					{// �̗͂��܂�����
						g_Player[nCntPlayer].state = PLAYERSTATE_DAMAGE_GETUP;
						// ���[�V�����؂�ւ�����
						SwitchMotion(nCntPlayer);
					}
				}
				else if (g_Player[nCntPlayer].state == PLAYERSTATE_DAMAGE_GETUP)
				{// �N���オ���Ԃ�������
					g_Player[nCntPlayer].state = PLAYERSTATE_NORMAL;
					// ���[�V�����؂�ւ�����
					SwitchMotion(nCntPlayer);
					g_Player[nCntPlayer].bControll = true;
				}
				else
				{// ����ȊO�̃��[�V�����Ȃ��
					g_Player[nCntPlayer].mState = MOTIONSTATE_STOP;
				}
			}
		}
		else
		{
			g_Player[nCntPlayer].nKey++;         // ���݂̃L�[�t���[����i�߂�

			// �L�[�t���[���؂�ւ�����
			SwitchKey(nCntPlayer);
		}
		g_Player[nCntPlayer].nMotionCounter = 0;   // �J�E���^�[��߂�
	}
}
//=============================================================================
// �L�[�t���[���؂�ւ�����
//=============================================================================
void SwitchKey(int nCntPlayer)
{
	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{// ���f���̃p�[�c�����J��Ԃ�
	 // �ڕW�̍��W�ݒ�
		g_Player[nCntPlayer].aModel[nCntModel].posDiff.x = g_Player[nCntPlayer].aModel[nCntModel].posStd.x - (g_Player[nCntPlayer].aModel[nCntModel].pos.x - g_Player[nCntPlayer].aMotion[g_Player[nCntPlayer].state].Key[g_Player[nCntPlayer].nKey].posAdd[nCntModel].x);
		g_Player[nCntPlayer].aModel[nCntModel].posDiff.y = g_Player[nCntPlayer].aModel[nCntModel].posStd.y - (g_Player[nCntPlayer].aModel[nCntModel].pos.y - g_Player[nCntPlayer].aMotion[g_Player[nCntPlayer].state].Key[g_Player[nCntPlayer].nKey].posAdd[nCntModel].y);
		g_Player[nCntPlayer].aModel[nCntModel].posDiff.z = g_Player[nCntPlayer].aModel[nCntModel].posStd.z - (g_Player[nCntPlayer].aModel[nCntModel].pos.z - g_Player[nCntPlayer].aMotion[g_Player[nCntPlayer].state].Key[g_Player[nCntPlayer].nKey].posAdd[nCntModel].z);

		// �p�x�̍����̏C��
		g_Player[nCntPlayer].aModel[nCntModel].DiffAngle.x = g_Player[nCntPlayer].aMotion[g_Player[nCntPlayer].state].Key[g_Player[nCntPlayer].nKey].DestAngle[nCntModel].x - g_Player[nCntPlayer].aModel[nCntModel].rot.x;   // ���݂̌����ƖړI�̌����̍������v�Z

		if (g_Player[nCntPlayer].aModel[nCntModel].DiffAngle.x > D3DX_PI)
		{// ������D3DX_PI�𒴂���
			g_Player[nCntPlayer].aModel[nCntModel].DiffAngle.x -= D3DX_PI * 2.0f;
		}
		if (g_Player[nCntPlayer].aModel[nCntModel].DiffAngle.x < -D3DX_PI)
		{// ������-D3DX_PI�𒴂���
			g_Player[nCntPlayer].aModel[nCntModel].DiffAngle.x += D3DX_PI * 2.0f;
		}
		// �p�x�̍����̏C��
		g_Player[nCntPlayer].aModel[nCntModel].DiffAngle.y = g_Player[nCntPlayer].aMotion[g_Player[nCntPlayer].state].Key[g_Player[nCntPlayer].nKey].DestAngle[nCntModel].y - g_Player[nCntPlayer].aModel[nCntModel].rot.y;   // ���݂̌����ƖړI�̌����̍������v�Z

		if (g_Player[nCntPlayer].aModel[nCntModel].DiffAngle.y > D3DX_PI)
		{// ������D3DX_PI�𒴂���
			g_Player[nCntPlayer].aModel[nCntModel].DiffAngle.y -= D3DX_PI * 2.0f;
		}
		if (g_Player[nCntPlayer].aModel[nCntModel].DiffAngle.y < -D3DX_PI)
		{// ������-D3DX_PI�𒴂���
			g_Player[nCntPlayer].aModel[nCntModel].DiffAngle.y += D3DX_PI * 2.0f;
		}

		// �p�x�̍����̏C��
		g_Player[nCntPlayer].aModel[nCntModel].DiffAngle.z = g_Player[nCntPlayer].aMotion[g_Player[nCntPlayer].state].Key[g_Player[nCntPlayer].nKey].DestAngle[nCntModel].z - g_Player[nCntPlayer].aModel[nCntModel].rot.z;   // ���݂̌����ƖړI�̌����̍������v�Z

		if (g_Player[nCntPlayer].aModel[nCntModel].DiffAngle.z > D3DX_PI)
		{// ������D3DX_PI�𒴂���
			g_Player[nCntPlayer].aModel[nCntModel].DiffAngle.z -= D3DX_PI * 2.0f;
		}
		if (g_Player[nCntPlayer].aModel[nCntModel].DiffAngle.z < -D3DX_PI)
		{// ������-D3DX_PI�𒴂���
			g_Player[nCntPlayer].aModel[nCntModel].DiffAngle.z += D3DX_PI * 2.0f;
		}
	}
}

//=============================================================================
// ���[�V�����؂�ւ�����
//=============================================================================
void SwitchMotion(int nCntPlayer)
{
	g_Player[nCntPlayer].nMotionCounter = 0;          // ���[�V�����J�E���^�[�����Z�b�g
	g_Player[nCntPlayer].nKey = 0;                    // ���݂̃L�[�t���[�������Z�b�g
	g_Player[nCntPlayer].mState = MOTIONSTATE_SWITCH; // ���[�V�����؂�ւ���Ԃ�
	if (g_Player[nCntPlayer].state != PLAYERSTATE_STORONG_ATTACK
		&& g_Player[nCntPlayer].state != PLAYERSTATE_WEAK_ATTACK_0
		&& g_Player[nCntPlayer].state != PLAYERSTATE_WEAK_ATTACK_1
		&& g_Player[nCntPlayer].state != PLAYERSTATE_WEAK_ATTACK_2
		&& g_Player[nCntPlayer].state != PLAYERSTATE_ULTIMATE
		&& g_Player[nCntPlayer].state != PLAYERSTATE_ULTIMATE_START)
	{// �U���̃A�N�V�����ł͂Ȃ�
		if (g_Player[nCntPlayer].bWeakAction == true)
		{
			g_Player[nCntPlayer].bWeakAction = false;
			g_Player[nCntPlayer].wAttackNumber = 0;
		}
		if (g_Player[nCntPlayer].bStorongAction == true)
		{
			g_Player[nCntPlayer].bStorongAction = false;
		}
		if (g_Player[nCntPlayer].bUltimate == true)
		{
			g_Player[nCntPlayer].bUltimate = false;
		}
	}

	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{// ���f���̃p�[�c�����J��Ԃ�
	 // �ڕW�̍��W�ݒ�
		g_Player[nCntPlayer].aModel[nCntModel].posDiff.x = g_Player[nCntPlayer].aModel[nCntModel].posStd.x - (g_Player[nCntPlayer].aModel[nCntModel].pos.x - g_Player[nCntPlayer].aMotion[g_Player[nCntPlayer].state].Key[g_Player[nCntPlayer].nKey].posAdd[nCntModel].x);
		g_Player[nCntPlayer].aModel[nCntModel].posDiff.y = g_Player[nCntPlayer].aModel[nCntModel].posStd.y - (g_Player[nCntPlayer].aModel[nCntModel].pos.y - g_Player[nCntPlayer].aMotion[g_Player[nCntPlayer].state].Key[g_Player[nCntPlayer].nKey].posAdd[nCntModel].y);
		g_Player[nCntPlayer].aModel[nCntModel].posDiff.z = g_Player[nCntPlayer].aModel[nCntModel].posStd.z - (g_Player[nCntPlayer].aModel[nCntModel].pos.z - g_Player[nCntPlayer].aMotion[g_Player[nCntPlayer].state].Key[g_Player[nCntPlayer].nKey].posAdd[nCntModel].z);

		// �p�x�̍����̏C��
		g_Player[nCntPlayer].aModel[nCntModel].DiffAngle.x = g_Player[nCntPlayer].aMotion[g_Player[nCntPlayer].state].Key[g_Player[nCntPlayer].nKey].DestAngle[nCntModel].x - g_Player[nCntPlayer].aModel[nCntModel].rot.x;   // ���݂̌����ƖړI�̌����̍������v�Z

		if (g_Player[nCntPlayer].aModel[nCntModel].DiffAngle.x > D3DX_PI)
		{// ������D3DX_PI�𒴂���
			g_Player[nCntPlayer].aModel[nCntModel].DiffAngle.x -= D3DX_PI * 2.0f;
		}
		if (g_Player[nCntPlayer].aModel[nCntModel].DiffAngle.x < -D3DX_PI)
		{// ������-D3DX_PI�𒴂���
			g_Player[nCntPlayer].aModel[nCntModel].DiffAngle.x += D3DX_PI * 2.0f;
		}
		// �p�x�̍����̏C��
		g_Player[nCntPlayer].aModel[nCntModel].DiffAngle.y = g_Player[nCntPlayer].aMotion[g_Player[nCntPlayer].state].Key[g_Player[nCntPlayer].nKey].DestAngle[nCntModel].y - g_Player[nCntPlayer].aModel[nCntModel].rot.y;   // ���݂̌����ƖړI�̌����̍������v�Z

		if (g_Player[nCntPlayer].aModel[nCntModel].DiffAngle.y > D3DX_PI)
		{// ������D3DX_PI�𒴂���
			g_Player[nCntPlayer].aModel[nCntModel].DiffAngle.y -= D3DX_PI * 2.0f;
		}
		if (g_Player[nCntPlayer].aModel[nCntModel].DiffAngle.y < -D3DX_PI)
		{// ������-D3DX_PI�𒴂���
			g_Player[nCntPlayer].aModel[nCntModel].DiffAngle.y += D3DX_PI * 2.0f;
		}

		// �p�x�̍����̏C��
		g_Player[nCntPlayer].aModel[nCntModel].DiffAngle.z = g_Player[nCntPlayer].aMotion[g_Player[nCntPlayer].state].Key[g_Player[nCntPlayer].nKey].DestAngle[nCntModel].z - g_Player[nCntPlayer].aModel[nCntModel].rot.z;   // ���݂̌����ƖړI�̌����̍������v�Z

		if (g_Player[nCntPlayer].aModel[nCntModel].DiffAngle.z > D3DX_PI)
		{// ������D3DX_PI�𒴂���
			g_Player[nCntPlayer].aModel[nCntModel].DiffAngle.z -= D3DX_PI * 2.0f;
		}
		if (g_Player[nCntPlayer].aModel[nCntModel].DiffAngle.z < -D3DX_PI)
		{// ������-D3DX_PI�𒴂���
			g_Player[nCntPlayer].aModel[nCntModel].DiffAngle.z += D3DX_PI * 2.0f;
		}
	}
}
//=============================================================================
// �v���C���[�̎擾
//=============================================================================
Player *GetPlayer(int nCntPlayer)
{
	return &g_Player[nCntPlayer];
}

//=============================================================================
// �v���C���[���m�̍U�����菈��
//=============================================================================
void PlayerAttack(int nCntPlayer)
{
	if (g_Player[nCntPlayer].bWeakAction == true)
	{// ��U�������Ă���
		SetEffect(D3DXVECTOR3(g_Player[nCntPlayer].aModel[5].mtxWorld._41, g_Player[nCntPlayer].aModel[5].mtxWorld._42, g_Player[nCntPlayer].aModel[5].mtxWorld._43), D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f), 10.0f, 10);
		SetEffect(D3DXVECTOR3(g_Player[nCntPlayer].aModel[5].mtxWorld._41, g_Player[nCntPlayer].aModel[5].mtxWorld._42, g_Player[nCntPlayer].aModel[5].mtxWorld._43), D3DXCOLOR(1.0f, 0.0f, 0.2f, 1.0f), 15.0f, 10);
	}
	else if (g_Player[nCntPlayer].bStorongAction == true)
	{// ���U�������Ă���
		if (g_Player[nCntPlayer].aMotion[g_Player[nCntPlayer].state].nNumKey >= 3)
		{// �����蔻��J�n�^�C�~���O�ɂȂ���
			SetEffect(D3DXVECTOR3(g_Player[nCntPlayer].aModel[11].mtxWorld._41, g_Player[nCntPlayer].aModel[11].mtxWorld._42, g_Player[nCntPlayer].aModel[11].mtxWorld._43), D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f), 13.0f, 10);
			SetEffect(D3DXVECTOR3(g_Player[nCntPlayer].aModel[11].mtxWorld._41, g_Player[nCntPlayer].aModel[11].mtxWorld._42, g_Player[nCntPlayer].aModel[11].mtxWorld._43), D3DXCOLOR(1.0f, 0.0f, 0.2f, 1.0f), 18.0f, 10);
		}
	}
	else if (g_Player[nCntPlayer].bUltimate == true)
	{// �K�E�U�������Ă���
		SetEffect(D3DXVECTOR3(g_Player[nCntPlayer].aModel[5].mtxWorld._41, g_Player[nCntPlayer].aModel[5].mtxWorld._42, g_Player[nCntPlayer].aModel[5].mtxWorld._43), D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f), 10.0f, 10);
		SetEffect(D3DXVECTOR3(g_Player[nCntPlayer].aModel[5].mtxWorld._41, g_Player[nCntPlayer].aModel[5].mtxWorld._42, g_Player[nCntPlayer].aModel[5].mtxWorld._43), D3DXCOLOR(1.0f, 0.0f, 0.2f, 1.0f), 15.0f, 10);
		SetEffect(D3DXVECTOR3(g_Player[nCntPlayer].aModel[8].mtxWorld._41, g_Player[nCntPlayer].aModel[8].mtxWorld._42, g_Player[nCntPlayer].aModel[8].mtxWorld._43), D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f), 13.0f, 10);
		SetEffect(D3DXVECTOR3(g_Player[nCntPlayer].aModel[8].mtxWorld._41, g_Player[nCntPlayer].aModel[8].mtxWorld._42, g_Player[nCntPlayer].aModel[8].mtxWorld._43), D3DXCOLOR(1.0f, 0.0f, 0.2f, 1.0f), 18.0f, 10);

		if (GetXInputTrigger(nCntPlayer, XIJS_BUTTON_11) == true)
		{// B�{�^����������Ă���
			PlayerDamage((nCntPlayer + 1) % MAX_PLAYER, 5);
		}

		if (GetUltGaugeState(nCntPlayer) == ULTGAUGE_NOMAL)
		{// �K�E�Q�[�W����ɂȂ���
		   // �U�����̏�Ԃ�߂�
			g_Player[nCntPlayer].state = PLAYERSTATE_NORMAL;
			SwitchMotion(nCntPlayer);

			g_Player[(nCntPlayer + 1) % MAX_PLAYER].bHit = false;

			// �h�q�����Ԃ���΂�
			g_Player[(nCntPlayer + 1) % MAX_PLAYER].state = PLAYERSTATE_DAMAGE_FLY;
			SwitchMotion((nCntPlayer + 1) % MAX_PLAYER);
			g_Player[(nCntPlayer + 1) % MAX_PLAYER].move.x -= sinf(g_Player[nCntPlayer].rot.y) * 20.0f;
			g_Player[(nCntPlayer + 1) % MAX_PLAYER].move.y += 7.0f;
			g_Player[(nCntPlayer + 1) % MAX_PLAYER].bDown = true;

			SetRush(false);
		}
	}

	if (g_Player[(nCntPlayer + 1) % MAX_PLAYER].bDown == false)
	{// �v���C���[���_�E�����Ă��Ȃ�
		if (g_Player[nCntPlayer].bHit == false)
		{// �U�����q�b�g���Ă��Ȃ�
			if (g_Player[nCntPlayer].bWeakAction == true)
			{// ��U�������Ă���
				D3DXVECTOR3 ColPos = D3DXVECTOR3(g_Player[nCntPlayer].aModel[5].mtxWorld._41, g_Player[nCntPlayer].aModel[5].mtxWorld._42, g_Player[nCntPlayer].aModel[5].mtxWorld._43);
				if (g_Player[nCntPlayer].aMotion[g_Player[nCntPlayer].state].nNumKey >= 1)
				{// �����蔻��J�n�^�C�~���O�ɂȂ���
					CollisionAttack((nCntPlayer + 1) % MAX_PLAYER, ColPos, 15.0f);
				}
			}

			if (g_Player[nCntPlayer].bStorongAction == true)
			{// ��U�������Ă���
				if (g_Player[nCntPlayer].aMotion[g_Player[nCntPlayer].state].nNumKey >= 3)
				{// �����蔻��J�n�^�C�~���O�ɂȂ���
					CollisionAttack((nCntPlayer + 1) % MAX_PLAYER, D3DXVECTOR3(g_Player[nCntPlayer].aModel[11].mtxWorld._41, g_Player[nCntPlayer].aModel[11].mtxWorld._42, g_Player[nCntPlayer].aModel[11].mtxWorld._43), 15.0f);
				}
			}
			if (g_Player[nCntPlayer].state == PLAYERSTATE_ULTIMATE_START)
			{// �K�E�Z�J�n��Ԃ�������
				D3DXVECTOR3 ColPos = D3DXVECTOR3(g_Player[nCntPlayer].aModel[5].mtxWorld._41, g_Player[nCntPlayer].aModel[5].mtxWorld._42, g_Player[nCntPlayer].aModel[5].mtxWorld._43);
				if (g_Player[nCntPlayer].aMotion[g_Player[nCntPlayer].state].nNumKey >= 1)
				{// �����蔻��J�n�^�C�~���O�ɂȂ���
					if (CollisionAttack((nCntPlayer + 1) % MAX_PLAYER, ColPos, 15.0f) == true)
					{// �q�b�g����
						g_Player[nCntPlayer].state = PLAYERSTATE_ULTIMATE;
						SwitchMotion(nCntPlayer);
						g_Player[nCntPlayer].bUltimate = true;
						SetUltGaugeState(ULTGAUGE_USE, nCntPlayer);

						g_Player[(nCntPlayer + 1) % MAX_PLAYER].state = PLAYERSTATE_DAMAGE;
						SwitchMotion((nCntPlayer + 1) % MAX_PLAYER);
					}
				}
			}
		}
	}
}

//=============================================================================
// �v���C���[���m�̓����蔻�菈��
//=============================================================================
bool CollisionAttack(int nCntPlayer, D3DXVECTOR3 pos, float fRadius)
{
	bool bCol = false;  // �����������ǂ���
	if (pos.y - fRadius < g_Player[nCntPlayer].pos.y + 70.0f
		&& pos.y + fRadius > g_Player[nCntPlayer].pos.y)
	{// ���킪�G��Y���W�̒��ɂ���
		if (pos.x - fRadius < g_Player[nCntPlayer].pos.x + 20.0f
			&& pos.x + fRadius >  g_Player[nCntPlayer].pos.x - 20.0f)
		{// �U�����������h�q����X���W�̒��ɂ���
			int nDamage = 0;
			if (g_Player[(nCntPlayer + 1) % MAX_PLAYER].bWeakAction == true)
			{// ��U����������
				nDamage = 10;
				SetUltGauge(30.0f, (nCntPlayer + 1) % MAX_PLAYER);
			}
			if (g_Player[(nCntPlayer + 1) % MAX_PLAYER].bStorongAction == true)
			{// ���U����������
				nDamage = 20;
				SetUltGauge(50.0f, (nCntPlayer + 1) % MAX_PLAYER);
			}
			if (g_Player[(nCntPlayer + 1) % MAX_PLAYER].state == PLAYERSTATE_ULTIMATE_START)
			{// ���U����������
				nDamage = 5;
				g_Player[(nCntPlayer + 1) % MAX_PLAYER].bUltimate = true;
				SetRush(true);
			}
			// �_���[�W����
			PlayerDamage(nCntPlayer, nDamage);
			g_Player[(nCntPlayer + 1) % MAX_PLAYER].bHit = true;  // �U�����q�b�g���������
			bCol = true;  // ������������ɂ���
		}
	}

	return bCol;
}

//=============================================================================
// �v���C���[�̃_���[�W����
//=============================================================================
void PlayerDamage(int nCntPlayer, int nDamage)
{
	// �̗͂����炷
	g_Player[nCntPlayer].nLife -= nDamage;
	g_Player[nCntPlayer].bControll = false;

	// �̗̓Q�[�W�����炷
	SetLifeGauge((float)nDamage, nCntPlayer);

	if (g_Player[nCntPlayer].nLife <= 0)
	{// �̗͂�0�ɂȂ���
		g_Player[nCntPlayer].move.x -= sinf(g_Player[(nCntPlayer + 1) % MAX_PLAYER].rot.y) * 20.0f;
		g_Player[nCntPlayer].move.y += 7.0f;
		g_Player[nCntPlayer].bDown = true;

		g_Player[nCntPlayer].state = PLAYERSTATE_DAMAGE_FLY;
		SwitchMotion(nCntPlayer);
		if (GetGameState() != GAMESTATE_END)
		{// �Q�[���I����ԂłȂ�
			SetGameState(GAMESTATE_END);
			RESULT result = (RESULT)((nCntPlayer + 1) % MAX_PLAYER);
			SetResult(result);
		}
	}
	else
	{// �̗͂��c���Ă���
		if (g_Player[(nCntPlayer + 1) % MAX_PLAYER].bUltimate == false)
		{// �K�E��Ԃł͂Ȃ�
			if (g_Player[(nCntPlayer + 1) % MAX_PLAYER].state == PLAYERSTATE_WEAK_ATTACK_2 || g_Player[(nCntPlayer + 1) % MAX_PLAYER].state == PLAYERSTATE_STORONG_ATTACK)
			{// ���U������U����3���ڂ��q�b�g����
				g_Player[nCntPlayer].move.x -= sinf(g_Player[(nCntPlayer + 1) % MAX_PLAYER].rot.y) * 20.0f;
				g_Player[nCntPlayer].move.y += 7.0f;
				g_Player[nCntPlayer].bDown = true;

				g_Player[nCntPlayer].state = PLAYERSTATE_DAMAGE_FLY;
				SwitchMotion(nCntPlayer);
				PlaySound(SOUND_LABEL_SE_DAMAGE);
			}
			else
			{// ����ȊO�̍U�����q�b�g����
				g_Player[nCntPlayer].move.x -= sinf(g_Player[(nCntPlayer + 1) % MAX_PLAYER].rot.y) * 2.0f;

				g_Player[nCntPlayer].state = PLAYERSTATE_DAMAGE;
				SwitchMotion(nCntPlayer);

				PlaySound(SOUND_LABEL_SE_DAMAGE);
			}
		}
	}
}

//=============================================================================
// �v���C���[�̏�ԑJ�ڏ���
//=============================================================================
void CollisionPlayer(int nCntPlayer)
{
	if (g_Player[nCntPlayer].pos.x >= 850.0f)
	{
		g_Player[nCntPlayer].pos.x = 850.0f;
	}
	if (g_Player[nCntPlayer].pos.x <= -850.0f)
	{
		g_Player[nCntPlayer].pos.x = -850.0f;
	}

	if (g_Player[nCntPlayer].pos.y <= g_Player[(nCntPlayer + 1) % MAX_PLAYER].pos.y + 100.0f)
	{
		if (g_Player[nCntPlayer].posold.x >= g_Player[(nCntPlayer + 1) % MAX_PLAYER].pos.x + 30.0f && g_Player[nCntPlayer].pos.x < g_Player[(nCntPlayer + 1) % MAX_PLAYER].pos.x + 30.0f)
		{
			g_Player[nCntPlayer].pos.x = g_Player[(nCntPlayer + 1) % MAX_PLAYER].pos.x + 30.0f;
		}
		if (g_Player[nCntPlayer].posold.x <= g_Player[(nCntPlayer + 1) % MAX_PLAYER].pos.x - 30.0f && g_Player[nCntPlayer].pos.x > g_Player[(nCntPlayer + 1) % MAX_PLAYER].pos.x - 30.0f)
		{
			g_Player[nCntPlayer].pos.x = g_Player[(nCntPlayer + 1) % MAX_PLAYER].pos.x - 30.0f;
		}
	}
}