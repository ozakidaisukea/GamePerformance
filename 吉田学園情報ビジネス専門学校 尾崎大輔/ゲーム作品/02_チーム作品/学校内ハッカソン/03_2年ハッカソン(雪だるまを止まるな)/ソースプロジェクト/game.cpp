//=============================================================================
//
// �Q�[������ [manager.cpp]
// Author : Jukiya Hayakawa
//
//=============================================================================
#include "game.h"
#include "scene.h"
#include "scene2D.h"
#include "renderer.h"
#include "input.h"
#include "manager.h"
#include "player.h"
#include "meshfield.h"
#include "debugproc.h"
#include "fade.h"
#include "object.h"
#include "map.h"
#include "pause.h"
#include "camera.h"
#include "field.h"
#include "objBillboard.h"
#include "number.h"
#include "score.h"
#include "UI.h"
#include "effect.h"
//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
CPlayer		*CGame::m_pPlayer = NULL;				//�v���C���[�̃|�C���^���
CMeshField	*CGame::m_pMeshField = NULL;			//���b�V���t�B�[���h�̃|�C���^���
CMap		*CGame::m_pMap = NULL;					//�}�b�v�̃|�C���^���
CScore		*CGame::m_pScore = NULL;
CObjBillboard *CGame::m_p3Dporigon = NULL;
CItemBillboard *CGame::m_p3DItem = NULL;

//=============================================================================
// �}�N����`
//=============================================================================


//=============================================================================
// �Q�[���̃R���X�g���N�^
//=============================================================================
CGame::CGame()
{

}

//=============================================================================
// �Q�[���̃f�X�g���N�^
//=============================================================================
CGame::~CGame()
{
	m_pPlayer = NULL;		//�v���C���[��������
	m_pMeshField = NULL;	//���b�V���t�B�[���h��������
	m_pMap = NULL;			//�}�b�v��������
}

//=============================================================================
// �Q�[���̃f�X�g���N�^
//=============================================================================
CGame *CGame::Create()
{
	CGame *pGame = NULL;	//�Q�[���̃|�C���^
	if (pGame == NULL)
	{
		pGame = new CGame;	//���I�m��
		if (pGame != NULL)
		{
			pGame->Init();	//����������
		}
	}
	return pGame;
}

//=============================================================================
// �Q�[���̏���������
//=============================================================================
HRESULT CGame::Init(void)
{
	CCamera* pCamera = CManager::GetCamera();

	CUI::Load();
	CUI::CreateMode(CManager::MODE_GAME);

	//�|�[�Y�̓ǂݍ���
	CPause::Load();

	//�����̓ǂݍ���
	CNumber::Load();

	//�v���C���[�̓ǂݍ���
	CPlayer::Load();

	//�t�B�[���h�̓ǂݍ���
	CField::Load();

	//�I�u�W�F�N�g�r���{�[�h�̓ǂݍ���
	CObjBillboard::Load();

	//�A�C�e���r���{�[�g�̓ǂݍ���
	CItemBillboard::Load();

	//�G�t�F�N�g�̓ǂݍ���
	CEffect::Load();

	//�}�b�v�𐶐�
	m_pMap = CMap::Create();

	//CItemBillboard::Create(CItemBillboard::TYPE_PRESENTBOX_0, D3DXVECTOR3(0.0f, 100.0f, 200.0f),100,100);

	//�t�B�[���h�̐���
	CField::Create(D3DXVECTOR3(0.0f, 0.0f, 1500.0f), 400.0f, 3000.0f);

	//���b�V���t�B�[���h�̐���
	//CMeshField::Create(D3DXVECTOR3(0.0f,1.0f,0.0f));

	//�X�R�A�̐���
	m_pScore = CScore::Create(D3DXVECTOR3(SCREEN_WIDTH - 150.0f, 50.0f, 0.0f), 23.0f, 23.0f);

	//�v���C���[�̐���
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 10.0f, 0.0f));

	pCamera->SetTarget(m_pPlayer);

	m_p3DItem =  CItemBillboard::Create(CItemBillboard::TYPE_PRESENTBOX_0, D3DXVECTOR3(0.0f,50.0f,300));
	m_p3DItem = CItemBillboard::Create(CItemBillboard::TYPE_PRESENTBOX_0, D3DXVECTOR3(0.0f, 50.0f, 900));
	m_p3DItem = CItemBillboard::Create(CItemBillboard::TYPE_PRESENTBOX_0, D3DXVECTOR3(0.0f, 50.0f, 1500));
	m_p3DItem = CItemBillboard::Create(CItemBillboard::TYPE_PRESENTBOX_0, D3DXVECTOR3(0.0f, 50.0f, 2100));
	m_p3DItem = CItemBillboard::Create(CItemBillboard::TYPE_PRESENTBOX_0, D3DXVECTOR3(0.0f, 50.0f, 2700));
	m_p3DItem = CItemBillboard::Create(CItemBillboard::TYPE_PRESENTBOX_0, D3DXVECTOR3(0.0f, 50.0f, 3300));
	m_p3DItem = CItemBillboard::Create(CItemBillboard::TYPE_PRESENTBOX_0, D3DXVECTOR3(0.0f, 50.0f, 3900));
	m_p3DItem = CItemBillboard::Create(CItemBillboard::TYPE_PRESENTBOX_0, D3DXVECTOR3(0.0f, 50.0f, 4500));
	m_p3DItem = CItemBillboard::Create(CItemBillboard::TYPE_PRESENTBOX_0, D3DXVECTOR3(0.0f, 50.0f, 5100));


	for (int nCount = 0; nCount < 50; nCount++)
	{
		m_p3Dporigon = CObjBillboard::Create(CObjBillboard::TYPE_TREE_1, D3DXVECTOR3(100.0f, 100, (nCount*100.0f)));
	}
	for (int nCount = 0; nCount < 50; nCount++)
	{
		m_p3Dporigon = CObjBillboard::Create(CObjBillboard::TYPE_TREE_1, D3DXVECTOR3(-100.0f, 100, (nCount*100.0f)));
	}
	return S_OK;
}

//=============================================================================
// �Q�[���̏I������
//=============================================================================
void CGame::Uninit(void)
{

	//�A�C�e���r���{�[�g�̓ǂݍ���
	CItemBillboard::Unload();

	CUI::Unload();
	//�I�u�W�F�N�g�r���{�[�h�̔j��
	CObjBillboard::Unload();
	//�v���C���[�̔j��
	CPlayer::Unload();
	//�|�[�Y�̔j��
	CPause::Unload();
	//�����̔j��
	CNumber::Unload();

	//�}�b�v�̏I������
	if (m_pMap != NULL)
	{
		m_pMap->Uninit();
		delete m_pMap;
		m_pMap = NULL;
	}

	//�S�ẴI�u�W�F�N�g�J��
	CScene::ReleaseAll();
}

//=============================================================================
// �Q�[���̍X�V����
//=============================================================================
void CGame::Update(void)
{
	//�L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetKeyboard();

	//�t�F�[�h�̎擾
	CFade *pFade = CManager::GetFade();
	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true)
	{//Enter�L�[�����������ꍇ
	 //���U���g�֑J��
		//pFade->SetFade(CManager::MODE_RESULT, pFade->FADE_OUT);

	}

	if (m_pPlayer->GetState() == CPlayer::PLAYER_STATE_GOAL)
	{
		pFade->SetFade(CManager::MODE_RESULT, pFade->FADE_OUT);
	}

	//�f�o�b�O�\��
#ifdef _DEBUG
	CDebugProc::Print(1, "Game");
#endif // _DEBUG
}

//=============================================================================
// �Q�[���̕`�揈��
//=============================================================================
void CGame::Draw(void)
{
}

//=============================================================================
// �v���C���[�̎擾
//=============================================================================
CPlayer *CGame::GetPlayer(void)
{
	return m_pPlayer;				//�l��Ԃ�
}

//=============================================================================
// �X�R�A�̎擾
//=============================================================================
CScore * CGame::GetScore(void)
{
	return m_pScore;
}

//=============================================================================
// �I�u�W�F�N�g3D�̎擾
//=============================================================================
CMeshField *CGame::GetMeshField(void)
{
	return m_pMeshField;				//�l��Ԃ�
}
