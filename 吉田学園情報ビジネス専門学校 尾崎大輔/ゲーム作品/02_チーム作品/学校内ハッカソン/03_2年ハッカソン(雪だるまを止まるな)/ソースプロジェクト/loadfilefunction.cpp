//=============================================================================
//
// �t�@�C����ǂݍ��ލۂ̊֐� [loadfilefunction.cpp]
// Author : Jukiya Hayakawa
//
//=============================================================================
#include "loadfilefunction.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CLoadFileFunction::CLoadFileFunction()
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CLoadFileFunction::~CLoadFileFunction()
{

}

//=============================================================================
// �s�̓ǂݍ��ݏ���
//=============================================================================
char *CLoadFileFunction::ReadLine(FILE *pFile, char *pDst)
{
	fgets(pDst, 256, pFile);
	while (1)
	{//��񂪂Ȃ��Ȃ�܂ŌJ��Ԃ�

		if (memcmp(pDst, "#", strlen("#")) == 0)
		{//�R�����g�������s�̏ꍇ
			fgets(pDst, 256, pFile);
		}
		else if (memcmp(pDst, "\n", strlen("\n")) == 0)
		{//���s�������s�̏ꍇ
			fgets(pDst, 256, pFile);
		}
		else if (memcmp(pDst, "\t", strlen("\t")) == 0)
		{//�^�u�������s�̏ꍇ
			pDst += strlen("\t");	//���o��

			while (1)
			{
				if (memcmp(pDst, "#", 1) == 0)
				{//�R�����g�������s�̏ꍇ
					fgets(pDst, 256, pFile);
					break;
				}
				else if (memcmp(pDst, "\n", 2) == 0)
				{//���s�������s�̏ꍇ
					fgets(pDst, 256, pFile);
					break;
				}
				else if (memcmp(pDst, "\t", 2) == 0)
				{//�^�u�������s�̏ꍇ
					pDst = GetLineTop(pDst);
				}
				else if (memcmp(pDst, " ", 2) == 0)
				{//�X�y�[�X�������s�̏ꍇ
					pDst = GetLineTop(pDst);
				}
				else
				{
					break;
				}
			}
		}
		else if (memcmp(pDst, " ", 1) == 0)
		{//�X�y�[�X�������s�̏ꍇ
			while (1)
			{
				if (memcmp(pDst, "#", 1) == 0)
				{//�R�����g�������s�̏ꍇ
					fgets(pDst, 256, pFile);
					break;
				}
				else if (memcmp(pDst, "\n", 2) == 0)
				{//���s�������s�̏ꍇ
					fgets(pDst, 256, pFile);
					break;
				}
				else if (memcmp(pDst, "\t", 2) == 0)
				{//�^�u�������s�̏ꍇ
					pDst = GetLineTop(pDst);
				}
				else if (memcmp(pDst, " ", 1) == 0)
				{//�X�y�[�X�������s�̏ꍇ
					pDst = GetLineTop(pDst);
				}
				else
				{
					break;
				}
			}
		}
		else
		{
			break;
		}
	}
	return pDst;
}

//=============================================================================
// �󔒂̏���
//=============================================================================
char *CLoadFileFunction::GetLineTop(char *pScr)
{
	while (1)
	{
		if (memcmp(pScr, " ", strlen(" ")) == 0)
		{//�X�y�[�X�������s�̏ꍇ
			pScr += strlen(" ");
		}
		else if (memcmp(pScr, "\t", strlen("\t")) == 0)
		{//�^�u�������s�̏ꍇ
			pScr += strlen("\t");
		}
		else
		{
			break;
		}
	}

	return pScr;
}

//=============================================================================
// �������J�E���g����
//=============================================================================
int CLoadFileFunction::PopString(char *pScr, char *pDst)
{
	int nCount = 0;
	while (1)
	{
		nCount += 1;	//�J�E���^�[�����Z
		pScr += 1;		//���o��
		if (memcmp(pScr, " ", strlen(" ")) == 0)
		{//�X�y�[�X�������s�̏ꍇ
			pScr = "\0";	//NULL�ɂ���
			nCount += 1;	//�J�E���^�[�����Z
			break;
		}
		else if (memcmp(pScr, "\t", strlen("\t")) == 0)
		{//�X�y�[�X�������s�̏ꍇ
			pScr = "\0";	//NULL�ɂ���
			nCount += 1;	//�J�E���^�[�����Z����
			break;
		}
	}
	strcpy(pDst, pScr);
	return  nCount;
}