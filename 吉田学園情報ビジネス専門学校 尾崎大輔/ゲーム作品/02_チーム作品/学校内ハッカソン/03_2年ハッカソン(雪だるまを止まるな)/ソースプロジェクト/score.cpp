//=============================================================================
//
// �X�R�A�̏��� [score.cpp]
// Author : Jukiya Hayakawa
//
//=============================================================================
#include "score.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "bullet.h"
#include "number.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
int CScore::m_nScore = 0;

//=============================================================================
// �}�N����`
//=============================================================================

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================

//=============================================================================
// �X�R�A�̃R���X�g���N�^
//=============================================================================
CScore::CScore() : CScene(6,OBJTYPE_NONE)
{
}
//=============================================================================
// �X�R�A�̃f�X�g���N�^
//=============================================================================
CScore::~CScore()
{

}

//=============================================================================
//�X�R�A�̐���
//=============================================================================
CScore *CScore::Create(D3DXVECTOR3 pos, float fWight, float fHeight)
{
	CScore *pScore = NULL;
	if (pScore == NULL)
	{
		pScore = new CScore;		//�V�[���̓��I�m��
		pScore->m_pos = pos;		//�ʒu�̐ݒu
		pScore->m_fWight = fWight;	//���̐ݒu
		pScore->m_fHeight = fHeight;//�����̐ݒu
		pScore->Init();				//����������
	}
	return pScore;					//�l��Ԃ�
}

//=============================================================================
// �X�R�A�̏���������
//=============================================================================
HRESULT CScore::Init(void)
{
	for (int nCntNumber = 0; nCntNumber < SCORE_DIGIT; nCntNumber++)
	{
		m_apNumber[nCntNumber] = NULL;
	}

	for (int nCntNumber = 0; nCntNumber < SCORE_DIGIT; nCntNumber++)
	{
		if (m_apNumber[nCntNumber] == NULL)
		{
			//�����̓��I�m��
			//m_apNumber[nCntNumber] = new CNumber;

			CManager::MODE mode = CManager::GetMode();
			if (mode == CManager::MODE_GAME)
			{
				//�����̐���
				m_apNumber[nCntNumber] = CNumber::Create(D3DXVECTOR3(m_pos.x - (45 * nCntNumber), m_pos.y, m_pos.z), m_fWight, m_fHeight);
			}
			else if (mode == CManager::MODE_RANKING)
			{
				//�����̐���
				m_apNumber[nCntNumber] = CNumber::Create(D3DXVECTOR3(m_pos.x - (90 * nCntNumber), m_pos.y, m_pos.z), m_fWight, m_fHeight);
			}
			m_nScore = 0;
		}
	}
	return S_OK;
}

//=============================================================================
// �X�R�A�̏I������
//=============================================================================
void CScore::Uninit(void)
{
	//�X�R�A�̏I������
	for (int nCntNumber = 0; nCntNumber < SCORE_DIGIT; nCntNumber++)
	{
		if (m_apNumber[nCntNumber] != NULL)
		{
			//�I������
			m_apNumber[nCntNumber]->Uninit();
			//�������̊J��
			delete m_apNumber[nCntNumber];
			//NULL�ɂ���
			m_apNumber[nCntNumber] = NULL;
		}
	}
	Release();
}

//=============================================================================
// �X�R�A�̍X�V����
//=============================================================================
void CScore::Update(void)
{

}

//=============================================================================
// �X�R�A�̕`�揈��
//=============================================================================
void CScore::Draw(void)
{
	for (int nCntScore = 0; nCntScore < SCORE_DIGIT; nCntScore++)
	{
		//�����̕`�揈��
		m_apNumber[nCntScore]->Draw();
	}
}

//=============================================================================
// �X�R�A�̐ݒu����
//=============================================================================
void CScore::SetScore(int nScore)
{
	//�X�R�A�̉��Z
	m_nScore += nScore;
}

//=============================================================================
// �X�R�A�̉��Z
//=============================================================================
void CScore::AddScore(int nValue)
{
	int nAnswer = 1;
	int nScore;

	m_nScore += nValue;

	for (int nCntNumber = 0; nCntNumber < SCORE_DIGIT; nCntNumber++)
	{
		nScore = m_nScore % (nAnswer * 10) / nAnswer;
		//�����̐ݒu
		m_apNumber[nCntNumber]->SetNumber(nScore);
		nAnswer *= 10;
	}
}


//=============================================================================
// �X�R�A�̎擾
//=============================================================================
int CScore::GetScore(void)
{
	//�l��Ԃ�
	return m_nScore;
}

//=============================================================================
// �X�R�A�̎擾
//=============================================================================
void CScore::SetCol(D3DXCOLOR col)
{
	for (int nCntNumber = 0; nCntNumber < SCORE_DIGIT; nCntNumber++)
	{
		m_apNumber[nCntNumber]->SetCol(col);
	}
}