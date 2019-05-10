//=============================================================================
//
// �G�t�F�N�g�̏����@[effect.cpp]
// Author : Ozaki
//
//=============================================================================
#include "effect.h"
#include "renderer.h"
#include "main.h"
#include "manager.h"
#include "scene2D.h"
#include "input.h"

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9 CEffect::m_pTexture = NULL;
CExplosion*CEffect::m_pExplosion = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CEffect::CEffect():CScene2D(7)
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CEffect::~CEffect()
{

}

//=============================================================================
// ���[�h
//=============================================================================
HRESULT CEffect::Load(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = NULL;

	pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\game\\effect000.jpg",
		&m_pTexture);

	return S_OK;
}

//=============================================================================
// �A�����[�h
//=============================================================================
void CEffect::Unload(void)
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
HRESULT CEffect::Init(D3DXVECTOR3 pos, D3DXCOLOR col, float widtgh, float height)
{
	CScene2D::Init(pos, widtgh,height);
	//m_fLength = flength;
	m_widtgh = widtgh;
	m_height = height;
	m_col = col;

	SetObjtType(CScene::OBJTYPE_EFFECT);

	// �G�t�F�N�g�̕\������
	m_nLife = 40;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CEffect::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CEffect::Update(void)
{
	D3DXVECTOR3 effectpos;

	effectpos = GetPosition();


	// �F
	m_col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.5f);

	// ���C�t
	m_nLife -= 1;

	// �傫��
	m_widtgh,m_height -= 1;


	LPDIRECT3DVERTEXBUFFER9 VtxBuff;

		VtxBuff = GetVtxBG();
		//���[�J���ϐ�
		VERTEX_2D*pVtx;

		//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^�̎擾
		VtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//���_�J���[�̐ݒ�
		pVtx[0].col = m_col;
		pVtx[1].col = m_col;
		pVtx[2].col = m_col;
		pVtx[3].col = m_col;

		//���_�o�b�t�@���A�����b�N
		VtxBuff->Unlock();

	SetPosition(effectpos, m_rot, m_position, m_fLength);

	// �\�����Ԃ�0�ɂȂ�Ə���
	if (m_nLife <= 0)
	{
		Uninit();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CEffect::Draw(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = NULL;

	pDevice = CManager::GetRenderer()->GetDevice();

	// ���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	CScene2D::Draw();

	// ���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//=============================================================================
// �e�̐���
//=============================================================================
CEffect *CEffect::Create(D3DXVECTOR3 pos, D3DXCOLOR col, float widtgh, float height)
{
	CEffect *pEffect;

	pEffect = new CEffect;

	pEffect->Init(pos,col,widtgh,height);

	// ���L�e�N�X�`�������蓖�Ă�
	pEffect->BindTexture(m_pTexture);

	return pEffect;
}