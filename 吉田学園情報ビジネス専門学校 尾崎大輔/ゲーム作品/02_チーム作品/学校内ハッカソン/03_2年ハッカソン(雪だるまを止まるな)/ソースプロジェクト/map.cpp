//*****************************************************************************
//
// �}�b�v�̏���[map.cpp]
// Auther:Jukiya Hayakawa
//
//*****************************************************************************
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "map.h"
#include "object.h"
#include "meshField.h"
#include "loadfilefunction.h"
#include "modelcreate.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXT_MAPSET				"MAPSET"
#define TEXT_END_MAPSET			"END_MAPSET"
#define TEXT_FILENAME_OBJECT	"FILENAME_OBJECT = "
#define TEXT_FILENAME_FIELD		"FILENAME_FIELD = "
#define TEXT_FILENAME_GAME_MAP "data\\TEXT\\MAP\\game_map.txt"
#define TEXT_FILENAME_RESULT_MAP "data\\TEXT\\MAP\\result_map.txt"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CMap::CMap()
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CMap::~CMap()
{

}

//=============================================================================
// ��������
//=============================================================================
CMap *CMap::Create(void)
{
	CMap *pMap = NULL;  // �}�b�v�|�C���^
	if (pMap == NULL)
	{//NULL�̏ꍇ
		pMap = new CMap;	//���I�m��
		if (pMap != NULL)
		{// NULL�łȂ��ꍇ
			pMap->Init();	//����������
		}
	}
	return pMap;
}

//=============================================================================
//    ����������
//=============================================================================
void CMap::Init(void)
{
	//�����_�����O�̎擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();

	// �}�b�v�����O������ǂݍ���
	FILE *pFile = NULL;   // �t�@�C���|�C���^
	if (pFile == NULL)
	{
		if (CManager::GetMode() == CManager::MODE_GAME)
		{
			pFile = fopen(TEXT_FILENAME_GAME_MAP, "r");
		}
		else if (CManager::GetMode() == CManager::MODE_RESULT)
		{
			pFile = fopen(TEXT_FILENAME_RESULT_MAP,"r");
		}
		if (pFile != NULL)
		{
			char *pStrCur;						//������̐擪�ւ̃|�C���^
			char aLine[256];					//������̓ǂݍ��ݗp
			char aStr[256];						//�����񔲂��o���p
			int	 nNumModel = 0;					//���f������
			int  nCntModel = 0;					//���f���J�E���^�[
			LPD3DXMESH pMesh = NULL;            //���b�V���̃|�C���^
			LPD3DXBUFFER pBuffMat = NULL;       //�}�e���A���̃|�C���^
			DWORD nNumMat = 0;                  //�}�e���A���̐�
			char aFileName[256] = "\0";			//���f���̃t�@�C����


			while (1)
			{
				pStrCur = CLoadFileFunction::ReadLine(pFile, &aLine[0]);
				int nNum = CLoadFileFunction::PopString(pStrCur, &aStr[0]);
				strcpy(&aStr[0], pStrCur);
				aStr[nNum - 1] = '\0';
				if (memcmp(&aStr[0], TEXT_SCRIPT, strlen(TEXT_SCRIPT)) == 0)
				{
					while (1)
					{//���f���t�@�C����ǂݍ��ނ܂ŌJ��Ԃ�
						pStrCur = CLoadFileFunction::ReadLine(pFile, &aLine[0]);
						strcpy(&aStr[0], pStrCur);	//����������o��

						if (memcmp(&aStr[0], TEXT_NUM_MODEL, strlen(TEXT_NUM_MODEL)) == 0)
						{//���f���̑����������e�L�X�g�̏ꍇ
							pStrCur += strlen(TEXT_NUM_MODEL);	//���o��
							strcpy(&aStr[0], pStrCur);

							nNumModel = atoi(&aStr[0]);	//���f���̑����ɑ��
							m_pModelCreate = CModelCreate::Create(nNumModel);
						}
						else if (memcmp(&aStr[0], TEXT_FILENAME_MODEL, strlen(TEXT_FILENAME_MODEL)) == 0)
						{// ���f���̃t�@�C���������e�L�X�g�̏ꍇ
							pStrCur += strlen(TEXT_FILENAME_MODEL);					//���o��
							strcpy(&aStr[0], pStrCur);
							int nNum = CLoadFileFunction::PopString(pStrCur, &aStr[0]);
							strcpy(&aStr[0], pStrCur);
							aStr[nNum - 1] = '\0';

							//���f���̓ǂݍ���
							D3DXLoadMeshFromX(&aStr[0],
								D3DXMESH_SYSTEMMEM,
								pDevice,
								NULL,
								&pBuffMat,
								NULL,
								&nNumMat,
								&pMesh);

							//���f�������̃��b�V���ݒu
							m_pModelCreate->SetMesh(pMesh, nCntModel);
							//���f�������̃}�e���A���ݒu
							m_pModelCreate->SetBuffMat(pBuffMat, nCntModel);
							//���f�������̃}�e���A�������ݒu
							m_pModelCreate->SetNumMat(nNumMat, nCntModel);

							//�ϐ�������
							pMesh = NULL;
							pBuffMat = NULL;
							nNumMat = 0;

							nCntModel++;  //���Z
						}
						else if (memcmp(&aStr[0], TEXT_MAPSET, strlen(TEXT_MAPSET)) == 0)
						{//�}�b�v�̐ݒu�������e�L�X�g�̏ꍇ
							while (1)
							{
								pStrCur = CLoadFileFunction::ReadLine(pFile, &aLine[0]);
								//int nNum = CLoadFileFunction::PopString(pStrCur, &aStr[0]);
								strcpy(&aStr[0], pStrCur);	//����������o��

								if (memcmp(&aStr[0], TEXT_FILENAME_FIELD, strlen(TEXT_FILENAME_FIELD)) == 0)
								{//�t�B�[���h�t�@�C�����������e�L�X�g�̏ꍇ
								}
								if (memcmp(&aStr[0], TEXT_FILENAME_OBJECT, strlen(TEXT_FILENAME_OBJECT)) == 0)
								{//�I�u�W�F�N�g�t�@�C�����������e�L�X�g�̏ꍇ
									pStrCur += strlen(TEXT_FILENAME_OBJECT);					//���o��
									strcpy(&aStr[0], pStrCur);
									int nNum = CLoadFileFunction::PopString(pStrCur, &aStr[0]);
									strcpy(&aStr[0], pStrCur);
									aStr[nNum - 1] = '\0';

									LoadObject(&aStr[0], pStrCur, &aLine[0]);
								}
								if (memcmp(&aStr[0], TEXT_END_MAPSET, strlen(TEXT_END_MAPSET)) == 0)
								{//�}�b�v�̐ݒu�I���������e�L�X�g�̏ꍇ
									break;
								}
							}
							break;
						}
					}
				}
				else if (memcmp(&aStr[0], TEXT_END_SCRIPT, strlen(TEXT_END_SCRIPT)) == 0)
				{
					break;
				}
			}
			fclose(pFile);	//�t�@�C�������
		}
	}
}

//=============================================================================
//    �I������
//=============================================================================
void CMap::Uninit(void)
{
	//���f�������̏I������
	if (m_pModelCreate != NULL)
	{
		m_pModelCreate->Uninit();
		delete m_pModelCreate;
		m_pModelCreate = NULL;
	}
}

//=============================================================================
// �z�u���ǂݍ��ݏ���
//=============================================================================
void CMap::LoadObject(char *pObjectFileName, char *pStrCur, char *pLine)
{
	FILE *pFile = NULL;  // �t�@�C���|�C���^
	if (pFile == NULL)
	{//NULL�̏ꍇ
		pFile = fopen(pObjectFileName, "r");
		if (pFile != NULL)
		{//NULL�łȂ��ꍇ
			char aStr[256];						//�����񔲂��o���p
			CObject *pObject = NULL;                                        // �z�u���N���X�ւ̃|�C���^
			int nObjectType = 0;                                            // �z�u���̃��f���ԍ�
			D3DXVECTOR3 ObjectPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);          // �z�u���̍��W
			D3DXVECTOR3 ObjectRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);          // �z�u���̌���
			D3DXVECTOR3 ObjectSize = D3DXVECTOR3(1.0f, 1.0f, 1.0f);			// �z�u���̑傫��
			bool bObjectHit = false;										// �z�u���̓����锻��

			pStrCur = CLoadFileFunction::ReadLine(pFile, pLine);
			int nNum = CLoadFileFunction::PopString(pStrCur, &aStr[0]);
			strcpy(&aStr[0], pStrCur);
			aStr[nNum - 1] = '\0';

			if (memcmp(&aStr[0], TEXT_SCRIPT, strlen(TEXT_SCRIPT)) == 0)
			{
				while (1)
				{
					pStrCur = CLoadFileFunction::ReadLine(pFile, pLine);	// �L���ȕ������������
					strcpy(&aStr[0], pStrCur);								//����������o��

					if (memcmp(&aStr[0], TEXT_MODELSET, strlen(TEXT_MODELSET)) == 0)
					{//���f���̐ݒu�������e�L�X�g�̏ꍇ
						while (1)
						{
							pStrCur = CLoadFileFunction::ReadLine(pFile, pLine);	// �L���ȕ������������
							strcpy(&aStr[0], pStrCur);								//����������o��

							if (memcmp(&aStr[0], TEXT_TYPE, strlen(TEXT_TYPE)) == 0)
							{// ��ނ������e�L�X�g�̏ꍇ
								pStrCur += strlen(TEXT_TYPE);
								pStrCur = CLoadFileFunction::GetLineTop(pStrCur);
								strcpy(&aStr[0], pStrCur);							//����������o��
								nObjectType = atoi(&aStr[0]);
							}
							else if (memcmp(pStrCur, TEXT_POS, strlen(TEXT_POS)) == 0)
							{// �ʒu�������e�L�X�g�̏ꍇ
								int nWord = 0;
								pStrCur += strlen(TEXT_POS);
								strcpy(&aStr[0], pStrCur);			//����������o��
								ObjectPos.x = (float)atof(&aStr[0]);

								nWord = CLoadFileFunction::PopString(pStrCur, &aStr[0]);
								pStrCur += nWord;
								strcpy(&aStr[0], pStrCur);			//����������o��
								ObjectPos.y = (float)atof(&aStr[0]);

								nWord = CLoadFileFunction::PopString(pStrCur, &aStr[0]);
								pStrCur += nWord;
								strcpy(&aStr[0], pStrCur);			//����������o��
								ObjectPos.z = (float)atof(&aStr[0]);

							}
							else if (memcmp(pStrCur, TEXT_ROT, strlen(TEXT_ROT)) == 0)
							{// �����������e�L�X�g�̏ꍇ
								int nWord = 0;
								pStrCur += strlen(TEXT_ROT);
								strcpy(&aStr[0], pStrCur);			//����������o��
								ObjectRot.x = (float)atof(&aStr[0]);

								nWord = CLoadFileFunction::PopString(pStrCur, &aStr[0]);
								pStrCur += nWord;
								strcpy(&aStr[0], pStrCur);			//����������o��
								ObjectRot.y = (float)atof(&aStr[0]);

								nWord = CLoadFileFunction::PopString(pStrCur, &aStr[0]);
								pStrCur += nWord;
								strcpy(&aStr[0], pStrCur);			//����������o��
								ObjectRot.z = (float)atof(&aStr[0]);
							}
							else if (memcmp(pStrCur, TEXT_SIZE, strlen(TEXT_SIZE)) == 0)
							{// �傫���������e�L�X�g�̏ꍇ
								int nWord = 0;
								pStrCur += strlen(TEXT_SIZE);
								strcpy(&aStr[0], pStrCur);			//����������o��
								ObjectSize.x = (float)atof(&aStr[0]);

								nWord = CLoadFileFunction::PopString(pStrCur, &aStr[0]);
								pStrCur += nWord;
								strcpy(&aStr[0], pStrCur);			//����������o��
								ObjectSize.y = (float)atof(&aStr[0]);

								nWord = CLoadFileFunction::PopString(pStrCur, &aStr[0]);
								pStrCur += nWord;
								strcpy(&aStr[0], pStrCur);			//����������o��
								ObjectSize.z = (float)atof(&aStr[0]);
							}
							else if (memcmp(&aStr[0], TEXT_HIT, strlen(TEXT_HIT)) == 0)
							{// ��ނ������e�L�X�g�̏ꍇ
								pStrCur += strlen(TEXT_HIT);
								pStrCur = CLoadFileFunction::GetLineTop(pStrCur);
								strcpy(&aStr[0], pStrCur);							//����������o��
								int nHit = atoi(&aStr[0]);							//�����i�[
								switch (nHit)
								{
								case 0:	//0�̏ꍇ�����蔻��Ȃ�
									bObjectHit = false;
									break;
								case 1:	//1�̏ꍇ�����蔻�肠��
									bObjectHit = true;
									break;
								}
							}
							else if (memcmp(pStrCur, TEXT_END_MODELSET, strlen(TEXT_END_MODELSET)) == 0)
							{// �z�u�ǂݍ��ݏI���������e�L�X�g�̏ꍇ
								pObject = CObject::Create(ObjectPos, ObjectRot,ObjectSize,bObjectHit);
								if (pObject != NULL)
								{
									pObject->BindX(m_pModelCreate->GetMesh(nObjectType), m_pModelCreate->GetBuffMat(nObjectType), m_pModelCreate->GetNumMat(nObjectType));
									pObject->SetVtxMin(m_pModelCreate->GetVtxMin(nObjectType));
									pObject->SetVtxMax(m_pModelCreate->GetVtxMax(nObjectType));
								}
								break;  // ���[�v�I��
							}

						}
					}
					else if (memcmp(pStrCur, TEXT_END_SCRIPT, strlen(TEXT_END_SCRIPT)) == 0)
					{
						break;  // ���[�v�I��
					}
				}
			}
			// �t�@�C�������
			fclose(pFile);
		}
	}
}
