//=============================================================================
//
// �p�[�e�B�N���̏��� [effect.cpp]
// Author : Jukiya Hayakawa
//
//=============================================================================
#include "particle2D.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"


//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CParticle2D::m_pTexture = NULL;

//=============================================================================
// �}�N����`
//=============================================================================
#define	TEXTURE_PARTICLE			"data\\TEXTURE\\UI\\minmapplayer.png"		// �~�j�}�b�v�̃v���C���[

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================

//=============================================================================
// �I�u�W�F�N�g�̃R���X�g���N�^
//=============================================================================
CParticle2D::CParticle2D() : CScene2D(1)
{
	m_nLife = 0;								//�̗͂̏����l
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړ��ʂ̏����l
}
//=============================================================================
// �I�u�W�F�N�g�̃f�X�g���N�^
//=============================================================================
CParticle2D::~CParticle2D()
{

}

//=============================================================================
//�I�u�W�F�N�g�̐���
//=============================================================================
CParticle2D *CParticle2D::Create(D3DXVECTOR3 pos,D3DXVECTOR3 move, D3DXCOLOR col,float fLength)
{
	CParticle2D *pParticle = NULL;

	if (pParticle == NULL)
	{
		pParticle = new CParticle2D;				//�V�[���̓��I�m��
		pParticle->SetPos(pos);					//�ʒu�̑��
		pParticle->SetLength(fLength);			//�g��̑��
		pParticle->m_move = move;
		pParticle->Init();						//����������
		pParticle->SetCol(col);					//�F�̑��
		pParticle->BindTexture(m_pTexture);		//�e�N�X�`��
	}
	return pParticle;							//�l��Ԃ�
}

//=============================================================================
// �I�u�W�F�N�g�̃e�N�X�`���ǂݍ���
//=============================================================================
HRESULT CParticle2D::Load(void)
{
	//�����_�����O�̎擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_PARTICLE,
		&m_pTexture);

	return S_OK;
}

//=============================================================================
// �I�u�W�F�N�g�̃e�N�X�`���j��
//=============================================================================
void CParticle2D::Unload(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}
//=============================================================================
// �I�u�W�F�N�g�̏���������
//=============================================================================
HRESULT CParticle2D::Init(void)
{
	//CScene2D�̏���������
	CScene2D::Init();
	return S_OK;
}

//=============================================================================
// �I�u�W�F�N�g�̏I������
//=============================================================================
void CParticle2D::Uninit(void)
{
	//CScene2D�̏I������
	CScene2D::Uninit();
}

//=============================================================================
// �I�u�W�F�N�g�̍X�V����
//=============================================================================
void CParticle2D::Update(void)
{
	D3DXVECTOR3	pos;		//�ʒu
	D3DXCOLOR	col;		//�F
	float		length;		//�g��

	//�ʒu�̎擾
	pos = GetPos();
	//�F�̎擾
	col = GetCol();
	//�g��̎擾
	length = GetfLength();

	//���Z����
	length--;				//�g�吔�����炷
	col.r -= 0.0005f;		//�F�����炷
	col.g -= 0.0005f;		//�F�����炷
	col.b -= 0.0005f;		//�F�����炷
	col.a -= 0.0005f;		//�����x�����炷

	pos += m_move;
	//�ʒu�̐ݒu
	SetPos(pos);
	//�g��̐ݒu
	SetLength(length);
	//�ʒu�̐ݒu
	SetVtxLenghtPos(pos);
	//�F�̐ݒu
	SetCol(col);

	if (length <= 0.0f)
	{//���܂��͍�����0�ȉ��ɂȂ����ꍇ
	 //�I������
		Uninit();
	}

	//CScene2D�̍X�V����
	CScene2D::Update();
}

//=============================================================================
// �I�u�W�F�N�g�̕`�揈��
//=============================================================================
void CParticle2D::Draw(void)
{
	//�����_�����O�̎擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();

	// ���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//CScene2D�̕`�揈��
	CScene2D::Draw();

	// ���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}