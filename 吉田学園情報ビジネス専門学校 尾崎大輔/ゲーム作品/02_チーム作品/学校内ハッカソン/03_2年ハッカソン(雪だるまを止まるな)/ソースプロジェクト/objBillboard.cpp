//=============================================================================
//
// ��Q��(�r���{�[�h)���� [objBillboard.cpp]
// Author : Yuto Kodama
//
//=============================================================================
#include "objBillboard.h"
#include "manager.h"
#include "renderer.h"
#include "score.h"
#include "game.h"

//*****************************************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9 CObjBillboard::m_apTexture[CObjBillboard::TYPE_MAX] = {};

CObjBillboard::CObjBillboard()
{
}

//=============================================================================
// �R���X�g���N�^&�f�X�g���N�^
//=============================================================================
CObjBillboard::CObjBillboard(int nPriority, CScene::OBJTYPE type) : CBillboard(nPriority, type)
{

}

CObjBillboard::~CObjBillboard()
{

}

//=============================================================================
// ��������
//=============================================================================
CObjBillboard* CObjBillboard::Create(CObjBillboard::OBJ_TYPE type, D3DXVECTOR3 pos)
{
	CObjBillboard* pBillboard = NULL;

	pBillboard = new CObjBillboard(3, CScene::OBJTYPE_BILLBOARD);

	if (pBillboard != NULL)
	{
		pBillboard->SetHeight(50.0f);
		pBillboard->SetWidth(50.0f);
		pBillboard->Init(type, pos);
	}

	return pBillboard;
}

//=============================================================================
// �e�N�X�`���ǂݍ��ݏ���
//=============================================================================
HRESULT CObjBillboard::Load(void)
{
	//�����_���̎擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	//�|�C���^�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();


	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/f_tree941.png", &m_apTexture[TYPE_TREE_1]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/christmas-tree.png", &m_apTexture[TYPE_TREE_2]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/", &m_apTexture[TYPE_ROCK]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/grass.png", &m_apTexture[TYPE_GRASS]);

	return S_OK;
}

//=============================================================================
// �e�N�X�`���������
//=============================================================================
void CObjBillboard::Unload(void)
{
	//���
	for (int nCntTex = 0; nCntTex < TYPE_MAX; nCntTex++)
	{
		if (m_apTexture[nCntTex] != NULL)
		{
			m_apTexture[nCntTex]->Release();
			m_apTexture[nCntTex] = NULL;
		}
	}
}

//=============================================================================
// ����������
//=============================================================================
void CObjBillboard::Init(CObjBillboard::OBJ_TYPE type, D3DXVECTOR3 pos)
{

	//�e�N���X�̏�����
	CBillboard::Init();

	//�ϐ��ɒl������
	m_Type = type;
	m_pos = pos;

	//�e�N���X�ɒl��ݒ�
	CBillboard::SetPos(pos);
	CBillboard::BindTexture(m_apTexture[type]);
}

//=============================================================================
// �I������
//=============================================================================
void CObjBillboard::Uninit(void)
{
	//�e�N���X�̏I������
	CBillboard::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CObjBillboard::Update(void)
{
	float fHeight = GetHeight();
	float fWidth = GetWidth();
	D3DXVECTOR3 pos = GetPos();


	SetHeight(fHeight);
	SetWidth(fWidth);

	//�e�N���X�ɐV�����l��ݒ�
	CBillboard::SetPos(m_pos);

	//�e�N���X�̍X�V����
	CBillboard::Update();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CObjBillboard::Draw(void)
{
	//�e�N���X�̕`�揈��
	CBillboard::Draw();
}


//=============================================================================
//
// �A�C�e��(�r���{�[�h)���� [ItemBillboard.cpp]
// Author : Jukiya Hayakawa
//
//=============================================================================
//*****************************************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9 CItemBillboard::m_apTexture[CItemBillboard::TYPE_MAX] = {};

//=============================================================================
// �R���X�g���N�^&�f�X�g���N�^
//=============================================================================
CItemBillboard::CItemBillboard()
{
	m_type = TYPE_PRESENTBOX_0;
}

//=============================================================================
// �R���X�g���N�^&�f�X�g���N�^
//=============================================================================
CItemBillboard::CItemBillboard(int nPriority, CScene::OBJTYPE type) : CBillboard(nPriority, type)
{

}
CItemBillboard::~CItemBillboard()
{

}

//=============================================================================
// ��������
//=============================================================================
CItemBillboard* CItemBillboard::Create(CItemBillboard::ITEM_TYPE type, D3DXVECTOR3 pos)
{
	CItemBillboard* pBillboard = NULL;

	pBillboard = new CItemBillboard(3, CScene::OBJTYPE_ITEM_BILLBOARD);


	if (pBillboard != NULL)
	{
		pBillboard->SetHeight(25.0f);
		pBillboard->SetWidth(25.0f);
		pBillboard->Init(type, pos);
	}

	return pBillboard;
}

//=============================================================================
// �e�N�X�`���ǂݍ��ݏ���
//=============================================================================
HRESULT CItemBillboard::Load(void)
{
	//�����_���̎擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	//�|�C���^�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();


	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/box.png", &m_apTexture[TYPE_PRESENTBOX_0]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/christmas-tree.png", &m_apTexture[TYPE_PRESENTBOX_1]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/", &m_apTexture[TYPE_PRESENTBOX_2]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/grass.png", &m_apTexture[TYPE_PRESENTBOX_3]);

	return S_OK;
}

//=============================================================================
// �e�N�X�`���������
//=============================================================================
void CItemBillboard::Unload(void)
{
	//�J��
	for (int nCntTex = 0; nCntTex < TYPE_MAX; nCntTex++)
	{
		if (m_apTexture[nCntTex] != NULL)
		{
			m_apTexture[nCntTex]->Release();
			m_apTexture[nCntTex] = NULL;
		}
	}
}

//=============================================================================
// ����������
//=============================================================================
void CItemBillboard::Init(CItemBillboard::ITEM_TYPE type, D3DXVECTOR3 pos)
{
	//�I�u�W�F�N�g��ނ̐ݒu����
	SetObjType(OBJTYPE_ITEM_BILLBOARD);

	//�e�N���X�̏�����
	CBillboard::Init();

	//�ϐ��ɒl������
	m_type = type;
	//�e�N���X�ɒl��ݒ�
	CBillboard::SetPos(pos);
	CBillboard::BindTexture(m_apTexture[type]);
}

//=============================================================================
// �I������
//=============================================================================
void CItemBillboard::Uninit(void)
{
	//�e�N���X�̏I������
	CBillboard::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CItemBillboard::Update(void)
{
	D3DXVECTOR3 pos = GetPos();
	float fHeight = GetHeight();
	float fWidth = GetWidth();

	SetHeight(fHeight);
	SetWidth(fWidth);
	SetPos(pos);

	//�e�N���X�̍X�V����
	CBillboard::Update();


}

//=============================================================================
// �`�揈��
//=============================================================================
void CItemBillboard::Draw(void)
{
	//�e�N���X�̕`�揈��
	CBillboard::Draw();
}

//=============================================================================
// �����蔻�菈��
//=============================================================================
void CItemBillboard::Collision(D3DXVECTOR3 pos)
{
	//�X�R�A�̎擾
	CScore *pScore = CGame::GetScore();
	//�ʒu�̎擾
	D3DXVECTOR3 ItemPos = GetPos();
	//�����̕ϐ�
	float fLength = 0.0f;

	//�����̌v�Z
	fLength = sqrtf((pos.x - ItemPos.x) * (pos.x - ItemPos.x) + (pos.z - ItemPos.z) * (pos.z - ItemPos.z));

	if (fLength >= 0.0f && fLength <= 20.0f)
	{//���͈͓̔��̏ꍇ
	 //�X�R�A���Z���ďI������
		pScore->AddScore(10000);
		Uninit();
	}
}
