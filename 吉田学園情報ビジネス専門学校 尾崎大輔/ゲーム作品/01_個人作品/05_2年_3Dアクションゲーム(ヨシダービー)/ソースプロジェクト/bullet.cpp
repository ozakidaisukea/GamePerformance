//=============================================================================
//
// bullet���� [bullet.cpp]
// Author : Ozaki
//
//=============================================================================
#include "main.h"
#include "bullet.h"
#include "scene.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "debugproc.h"
#include "scene.h"

//=============================================================================
// �ÓI�����o-�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CBullet::m_pTexture = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBullet::CBullet(int nCntPriority, OBJTYPE objtype) :CBillboard(4, CScene::OBJTYPE_BULLET)
{
	// �|���S���̈ʒu��ݒ�
	m_pos = D3DXVECTOR3(0, 0, 0.0f);

	m_nLife = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CBullet::~CBullet()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CBullet::Init(void)
{
	CBillboard::SetPosition(m_pos);

	CBillboard::Init();

	m_nLife = 100;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CBullet::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}

	// �e�N�X�`���̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	CScene::Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CBullet::Update(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = NULL;

	// �}�l�[�W���[���擾
	pDevice = CManager::GetRenderer()->GetDevice();

	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;

	pos = CBillboard::GetPosition();

	pos += m_move;

	m_nLife -= 1;

	CBillboard::SetPosition(pos);

	// �\�����Ԃ�0�ɂȂ�Ə���
	if (m_nLife <= 0)
	{
		Uninit();
	}

	// �ǂ̓����蔻��
	if (pos.x >= 150)
	{
		pos.x = 150 - 1;
		Uninit();
	}
	if (pos.x <= -150)
	{
		pos.x = -150 - 1;
		Uninit();
	}
	if (pos.z <= -150)
	{
		pos.z = -150 - 1;
		Uninit();
	}
	if (pos.z >= 150)
	{
		pos.z = 150 - 1;
		Uninit();
	}

	float fgsk[4];

	// ��
	m_VecA = m_aPos[0] - m_aPos[1];
	m_VecC = pos - m_aPos[0];
	fgsk[0] = ((m_VecA.z * m_VecC.x) - (m_VecA.x * m_VecC.z));
	if (fgsk[0] > 0)
	{
		Uninit();
	}

	// ��O
	m_VecA = m_aPos[0] - m_aPos[1];
	m_VecC = pos - m_aPos[0];
	fgsk[1] = ((m_VecA.z * m_VecC.x) - (m_VecA.x * m_VecC.z));
	if (fgsk[1] > 0)
	{
		Uninit();
	}

	// �E
	m_VecA = m_aPos[0] - m_aPos[1];
	m_VecC = pos - m_aPos[0];
	fgsk[2] = ((m_VecA.z * m_VecC.x) - (m_VecA.x * m_VecC.z));
	if (fgsk[2] > 0)
	{
		Uninit();
	}

	// ��
	m_VecA = m_aPos[0] - m_aPos[1];
	m_VecC = pos - m_aPos[0];
	fgsk[3] = ((m_VecA.z * m_VecC.x) - (m_VecA.x * m_VecC.z));
	if (fgsk[3] > 0)
	{
		Uninit();
	}

	m_VecA = m_aPos[0] - m_aPos[1];
	m_VecC = pos - m_aPos[0];
	fgsk[0] = ((m_VecA.z * m_VecC.x) - (m_VecA.x * m_VecC.z));
	if (fgsk[0] > 0)
	{
		Uninit();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CBullet::Draw(void)
{
	CBillboard::Draw();
}

//=============================================================================
// �V�[��3D�̐���
//=============================================================================
CBullet *CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	CBullet *pBullet;

	pBullet = new CBullet(5);

	pBullet->m_pos = pos;
	pBullet->m_move = move;
	pBullet->Init();


	// ���L�e�N�X�`�������蓖�Ă�
	pBullet->BindTexture(m_pTexture);

	return pBullet;
}

//=============================================================================
// ���L�e�N�X�`�������蓖�Ă�
//=============================================================================
void CBullet::BindTexture(LPDIRECT3DTEXTURE9 texture)
{
	m_pTexture = texture;
}