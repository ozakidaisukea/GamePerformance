//=============================================================================
//
// �A�C�e���̏��� [item.cpp]
// Author : Ozaki
//
//=============================================================================
#include "item.h"
#include "player.h"
#include "renderer.h"
#include "main.h"
#include "manager.h"
#include "scene2D.h"
#include "input.h"
#include "gauge.h"
#include "sound.h"
#include "score.h"
#include "game.h"

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9 CItem::m_pTexture[MAX_ITEM] = {};
CScore*CItem::m_apScore = NULL;
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CItem::CItem() :CScene2D(3)
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CItem::~CItem()
{

}

//=============================================================================
// ���[�h
//=============================================================================
HRESULT CItem::Load(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = NULL;

	pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̐���0
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\game\\item0.png",
		&m_pTexture[0]);

	// �e�N�X�`���̐���1
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\game\\item0_high.png",
		&m_pTexture[1]);

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\game\\item1.png",
		&m_pTexture[2]);

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\game\\item1_high.png",
		&m_pTexture[3]);

	return S_OK;
}

//=============================================================================
// �A�����[�h
//=============================================================================
void CItem::Unload(void)
{
	for (int nCnt = 0; nCnt < MAX_ITEM; nCnt++)
	{
		// �e�N�X�`���̔j��
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();

			m_pTexture[nCnt] = NULL;
		}
	}
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CItem::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, float widtgh, float height, ITEM_TYPE type)
{
	CScene2D::Init(pos, widtgh,height);
	m_move = move;
	m_widtgh = widtgh;
	m_height = height;

	SetObjtType(CScene::OBJTYPE_ITEM);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CItem::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CItem::Update(void)
{
	D3DXVECTOR3 Itempos;
	D3DXVECTOR3 Itemposold;

	Itempos = GetPosition();

	Itempos.y += m_move.y;

	// �ړ���
	m_move.x -= 0.01f;

	Itempos.x += m_move.x;

	// �|�W�V�����̐ݒ�
	SetPosition(Itempos, m_rot, m_pos, m_flength);

	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = NULL;

	pDevice = CManager::GetRenderer()->GetDevice();

	// �T�E���h���擾
	CSound *pSound;
	pSound = CManager::GetSound();

	// �I�u�W�F�N�g�^�C�v���擾
	for (int nCntPriority = 0; nCntPriority < MAX_PRIORITY1; nCntPriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
		{
			CScene2D *pScene;
			pScene = (CScene2D*)CScene::GetSCene(nCntScene,nCntPriority);

			// NULL�`�F�b�N
			if (pScene != NULL)
			{
				CScene::OBJTYPE objttype;

				objttype = pScene->GetObjtType();

				if (objttype == CScene::OBJTYPE_PLAYER)
				{
					// �v���C���[��pos���擾
					D3DXVECTOR3 playerpos;

					playerpos = pScene->GetPosition();

					if (Itempos.x < 0)
					{
						Itempos.x = SCREEN_WIDTH;
						Itemposold.x = Itempos.x;
					}

					if (Itempos.x > SCREEN_WIDTH)
					{
						Itempos.x = 0;
						Itemposold.x = Itempos.x;
					}

					// �A�C�e���ƃv���C���[�̓����蔻��
					if (Itempos.x - pScene->GetWidth() < playerpos.x && Itempos.x + pScene->GetWidth() > playerpos.x &&
						Itempos.y - pScene->GetHeigth() < playerpos.y && Itempos.y + pScene->GetHeigth() > playerpos.y)
					{
						CGauge::AddGauge(20);

						pSound->PlaySound(pSound->SOUND_LABEL_SE_SOSYAKU);

						Uninit();

					}
				}
			}
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CItem::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// �����̐���
//=============================================================================
CItem *CItem::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float widtgh, float height, ITEM_TYPE type)
{
	CItem *pItem;

	pItem = new CItem;

	pItem->Init(pos, move, widtgh,height,type);

	pItem->m_type = type;

	// ���L�e�N�X�`�������蓖�Ă�
	pItem->BindTexture(m_pTexture[type]);

	return pItem;
}