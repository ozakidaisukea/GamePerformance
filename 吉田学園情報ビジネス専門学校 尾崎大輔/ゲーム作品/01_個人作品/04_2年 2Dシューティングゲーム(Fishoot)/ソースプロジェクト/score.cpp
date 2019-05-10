//=============================================================================
//
// �X�R�A���� [score.cpp]
// Author : Ozaki
//
//=============================================================================
#include "score.h"
#include "scene.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CScore::CScore()
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CScore::~CScore()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CScore::Init(D3DXVECTOR3 pos, float widtgh, float height)
{
	for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		// �i���o�[�𐶐�
		m_apNumber[nCnt] = CNumber::Create(D3DXVECTOR3(pos.x + (40 * nCnt),pos.y,pos.z ), widtgh,height);

		m_mScore = 0;
	}
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CScore::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		m_apNumber[nCnt]->Uninit();

		delete	m_apNumber[nCnt];
		m_apNumber[nCnt] = NULL;
	}
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CScore::Update(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void CScore::Draw(void)
{
	for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		if (m_apNumber[nCnt] != NULL)
		{
			m_apNumber[nCnt]->Draw();
		}
	}
}

//=============================================================================
// �X�R�A�̐���
//=============================================================================
CScore*CScore::Create(D3DXVECTOR3 pos, float widtgh, float height)
{
	CScore *pScore;

	pScore = new CScore;

	pScore->Init(pos, widtgh,height);

	return pScore;
}

//=============================================================================
// �X�R�A�̐ݒu
//=============================================================================
void CScore::SetScore(int nScore)
{
	m_mScore = nScore;
}

//=============================================================================
// �X�R�A�̎擾
//=============================================================================
int CScore::GetScore(void)
{
	return m_mScore;
}

//=============================================================================
// �X�R�A�̉��Z
//=============================================================================
void CScore::AddScore(int nValue)
{
	m_mScore += nValue;

	//m_apNumber[0]->SetNumber(m_mScore / 10000000);
	//m_apNumber[1]->SetNumber(m_mScore % 10000000 / 1000000);
	//m_apNumber[2]->SetNumber(m_mScore % 1000000 / 100000);
	//m_apNumber[3]->SetNumber(m_mScore % 100000 / 10000);
	//m_apNumber[4]->SetNumber(m_mScore % 10000 / 1000);
	//m_apNumber[5]->SetNumber(m_mScore % 1000 / 100);
	//m_apNumber[6]->SetNumber(m_mScore % 100 / 10);
	//m_apNumber[7]->SetNumber(m_mScore % 10);


	m_apNumber[0]->SetNumber(m_mScore % 10000000);
	m_apNumber[1]->SetNumber(m_mScore % 1000000 / 100000);
	m_apNumber[2]->SetNumber(m_mScore % 100000 / 10000);
	m_apNumber[3]->SetNumber(m_mScore % 10000 / 1000);
	m_apNumber[4]->SetNumber(m_mScore % 1000 / 100);
	m_apNumber[5]->SetNumber(m_mScore % 100 / 10);
	m_apNumber[6]->SetNumber(m_mScore % 10);
}