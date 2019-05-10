//=============================================================================
//
// �v���C���[���� [effect.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "effect.h"
#include "Manager.h"
#include "input.h"
#include "renderer.h"
//==================================================================
// �}�N����`
//==================================================================
#define EFFECT_LIFE (30)

//==================================================================
// �ÓI�����o�ϐ��錾
//==================================================================
LPDIRECT3DTEXTURE9 CEffect::m_apTexture[2];				//���L�e�N�X�`���ւ̃|�C���^

//==================================================================
// �R���X�g���N�^&�f�X�g���N�^
//==================================================================
CEffect::CEffect(int nPriority, CScene::OBJTYPE type) : CBillboard(nPriority,type)
{
	m_nCount = 0;
	m_nLife = 1;

}
CEffect::~CEffect()
{
}

//==================================================================
// ���L�e�N�X�`���̓ǂݍ���&���
//==================================================================
HRESULT CEffect::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/effect000.jpg", &m_apTexture[0]);

	return S_OK;
}
void CEffect::Unload(void)
{
	for (int nCntTex = 0; nCntTex < 2; nCntTex++)
	{
		if (m_apTexture[nCntTex] != NULL)
		{
			m_apTexture[nCntTex]->Release();
			m_apTexture[nCntTex] = NULL;
		}
	}
}

//==================================================================
// ��������
//==================================================================
CEffect* CEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, AUTHORITY author, float fSize, D3DXCOLOR col, int nLife)
{
	CEffect* pEffect = NULL;
	pEffect = new CEffect(7,OBJTYPE_EFFECT);

	if (pEffect != NULL)
	{
		pEffect->Init(pos,move,col,fSize,nLife);	//�I�[�o�[���[�h����Init�ŏ�����
		pEffect->m_Author = author;
	}

	return pEffect;
}

//==================================================================
// ����������
//==================================================================
HRESULT CEffect::Init(void)
{
	return S_OK;
}
void CEffect::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move,D3DXCOLOR col, float fSize, int nLife)
{
	//�����_���̎擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	//�|�C���^�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();

	m_pos = pos;
	m_move = move;
	m_Col = col;
	m_nCount = 0;
	m_nLife = nLife;

	CBillboard::SetPos(pos);
	CBillboard::SetWidth(fSize);
	CBillboard::SetHeight(fSize);
	CBillboard::Init();
	CBillboard::BindTexture(m_apTexture[0]);
}

//==================================================================
// �I������
//==================================================================
void CEffect::Uninit(void)
{
	CBillboard::Uninit();
}

//==================================================================
// �X�V����
//==================================================================
void CEffect::Update(void)
{
	CBillboard::Update();
	m_nCount++;

	D3DXVECTOR3 pos = CBillboard::GetPos();
	m_pos += m_move;

	SetPos(m_pos);
	//SetCol(D3DXCOLOR(m_Col.r, m_Col.g, m_Col.b,(m_nLife - m_nCount) * (1.0f / m_nLife)));
	//if (m_nCount == m_nLife)
	//{
	//	Uninit();
	//}
}

//==================================================================
// �`�揈��
//==================================================================
void CEffect::Draw(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	pDevice->SetRenderState(D3DRS_LIGHTING,FALSE);
	// ���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	CBillboard::Draw();

	// ���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

}

void CEffect::MoveScaling(float fScaling)
{
	m_move *= fScaling;
}
void CEffect::Gravity(float fGravity)
{
	m_move.y -= fGravity;
}

void CEffect::SetParentMatrix(D3DXMATRIX* mtxParent)
{
	m_mtxParent = mtxParent;
	CBillboard::SetmtxParent(m_mtxParent);
}
