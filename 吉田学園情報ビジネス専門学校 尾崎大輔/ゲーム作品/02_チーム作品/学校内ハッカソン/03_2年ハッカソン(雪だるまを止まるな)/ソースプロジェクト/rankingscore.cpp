//=============================================================================
//
// �����L���O�X�R�A�̏��� [rankingrankingscore.cpp]
// Author : Jukiya Hayakawa
//
//=============================================================================
#include "rankingscore.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "bullet.h"
#include "number.h"
#include "score.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
int CRankingScore::m_aRankingScore[MAX_RANKINGSCORE] = {};

//=============================================================================
// �}�N����`
//=============================================================================

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================

//=============================================================================
// �����L���O�X�R�A�̃R���X�g���N�^
//=============================================================================
CRankingScore::CRankingScore() : CScene(6,OBJTYPE_NONE)
{
}
//=============================================================================
// �����L���O�X�R�A�̃f�X�g���N�^
//=============================================================================
CRankingScore::~CRankingScore()
{

}

//=============================================================================
//�����L���O�X�R�A�̐���
//=============================================================================
CRankingScore *CRankingScore::Create(D3DXVECTOR3 pos, float fWight, float fHeight)
{
	CRankingScore *pRankingScore = NULL;
	if (pRankingScore == NULL)
	{
		pRankingScore = new CRankingScore;		//�V�[���̓��I�m��
		pRankingScore->m_pos = pos;				//�ʒu�̑��
		pRankingScore->m_fWight = fWight;		//���̑��
		pRankingScore->m_fHeight = fHeight;		//�����̑��
		pRankingScore->Init();					//����������
		//pNumber->BindTexture(m_pTexture);
	}
	return pRankingScore;					//�l��Ԃ�
}

//=============================================================================
// �����L���O�X�R�A�̏���������
//=============================================================================
HRESULT CRankingScore::Init(void)
{
	for (int nCntRanking = 0; nCntRanking < MAX_RANKINGSCORE; nCntRanking++)
	{
		//�����̐���
		m_apScore[nCntRanking] = CScore::Create(D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z), m_fWight, m_fHeight);
		m_apScore[nCntRanking]->AddScore(CManager::GetGameScore(nCntRanking));
		m_pos.y += 105.0f;
	}
	m_nCountCol = 0;
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	return S_OK;
}

//=============================================================================
// �����L���O�X�R�A�̏I������
//=============================================================================
void CRankingScore::Uninit(void)
{
	for (int nCntRanking = 0; nCntRanking < MAX_RANKINGSCORE; nCntRanking++)
	{
		//�I������
		m_apScore[nCntRanking]->Uninit();

		//NULL�ɂ���
		m_apScore[nCntRanking] = NULL;
	}
	Release();
	//CScene::ReleaseAll();
}

//=============================================================================
// �����L���O�X�R�A�̍X�V����
//=============================================================================
void CRankingScore::Update(void)
{
	CManager *pManager = NULL;
	int nUpdateScore = pManager->GetUpdateScore();
	if (nUpdateScore >= 0 && nUpdateScore <= 4)
	{
		m_nCountCol++;
		if (m_nCountCol % 4 == 0)
		{// ��莞�Ԃ��������ꍇ
			if (m_col.b == 0.0f)
			{// �Ԃ̏ꍇ
				m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			}
			else
			{// ���̏ꍇ
				m_col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			}
		}
		m_apScore[nUpdateScore]->SetCol(m_col);
	}
}

//=============================================================================
// �����L���O�X�R�A�̕`�揈��
//=============================================================================
void CRankingScore::Draw(void)
{
}
