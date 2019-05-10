//=============================================================================
//
// ���C�t���� [life.cpp]
// Author : Ozaki
//
//=============================================================================
#include "life.h"
#include "renderer.h"
#include "manager.h"
#include "scene.h"
#include "scene2D.h"
#include "lifescene2D.h"
#include "player.h"

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9 CLife::m_pTexture = NULL;

//=============================================================================
// ���[�h
//=============================================================================
HRESULT CLife::Load(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = NULL;

	pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\game\\fishlife.png",
		&m_pTexture);

	return S_OK;
}

//=============================================================================
// �A�����[�h
//=============================================================================
void CLife::Unload(void)
{
		// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();

		m_pTexture = NULL;
	}
}

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CLife::CLife()
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CLife::~CLife()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CLife::Init(D3DXVECTOR3 pos, float widtgh, float height)
{
	SetObjtType(CScene2D::OBJTYPE_LIFE);

	m_nLife = MAX_LIFE;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CLife::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_LIFE; nCnt++)
	{
		if (m_apScene2D[nCnt] != NULL)
		{
			m_apScene2D[nCnt]->Uninit();

			delete m_apScene2D[nCnt];
			m_apScene2D[nCnt] = NULL;
		}
	}
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CLife::Update(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void CLife::Draw(void)
{
	for (int nCnt = 0; nCnt < m_nLife; nCnt++)
	{
		m_apScene2D[nCnt]->Draw();
	}
}

//=============================================================================
// ���C�t�����炷����
//=============================================================================
void CLife::CutLife(int nLife)
{
	if (CPlayer::GetState() != CPlayer::PLAYERSTATE_ULTIMATE)
	{
		m_nLife -= nLife;
	}
}


//=============================================================================
// ���C�t�̐���
//=============================================================================
CLife *CLife::Create(D3DXVECTOR3 pos, float widtgh, float height)
{
	CLife *pLife;

	pLife = new CLife;

	for (int nCnt = 0; nCnt < MAX_LIFE; nCnt++)
	{
		pLife->m_apScene2D[nCnt] = new CLIfeScene2D;

		pLife->m_apScene2D[nCnt]->BindTexture(m_pTexture);

		pLife->m_apScene2D[nCnt]->Init(D3DXVECTOR3(pos.x + (50 * nCnt), pos.y, pos.z), widtgh,height);
	}
	pLife->Init(pos, widtgh,height);

	return pLife;
}

//=============================================================================
// ���C�t���擾
//=============================================================================
int CLife::GetLife(int nLife)
{
	return m_nLife;
}

