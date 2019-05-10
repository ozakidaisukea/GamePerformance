//=============================================================================
//
// �����̏��� [explosion.cpp]
// Author : Ozaki
//
//=============================================================================
#include "explosion.h"
#include "player.h"
#include "renderer.h"
#include "main.h"
#include "manager.h"
#include "scene2D.h"
#include "input.h"

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9 CExplosion::m_pTexture = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CExplosion::CExplosion():CScene2D(5)
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CExplosion::~CExplosion()
{

}

//=============================================================================
// ���[�h
//=============================================================================
HRESULT CExplosion::Load(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = NULL;

	pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\game\\explosion001.png",
		&m_pTexture);

	return S_OK;
}

//=============================================================================
// �A�����[�h
//=============================================================================
void CExplosion::Unload(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();

		m_pTexture = NULL;
	}
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CExplosion::Init(D3DXVECTOR3 pos, float widtgh, float height)
{
	CScene2D::Init(pos,widtgh,height);

	//m_flength = flength;
	m_widtgh = widtgh;
	m_height = height;

	CScene2D::SetTexture(TEX_U, TEX_V, 1, 8);

	SetObjtType(CScene::OBJTYPE_EXPLOSION);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CExplosion::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CExplosion::Update(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = NULL;

	pDevice = CManager::GetRenderer()->GetDevice();

	// �����̃A�j���[�V����
	m_nCounterAnim++;

	if ((m_nCounterAnim % 3)== 0)
	{
		m_nPatternAnim = (m_nPatternAnim + 1 % 8);

		CScene2D::SetTexture(TEX_U,TEX_V,m_nPatternAnim,8);

		if (m_nPatternAnim >= 7)
		{
			Uninit();
		}
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void CExplosion::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// �����̐���
//=============================================================================
CExplosion *CExplosion::Create(D3DXVECTOR3 pos, float widtgh, float height)
{
	CExplosion *pExplosion;

	pExplosion = new CExplosion;

	pExplosion->Init(pos,widtgh,height);

	// ���L�e�N�X�`�������蓖�Ă�
	pExplosion->BindTexture(m_pTexture);

	return pExplosion;
}

