//=============================================================================
//
// �Q�[������ [game.cpp]
// Author : Ozaki
//
//=============================================================================
#include "game.h"			// �Q�[��
#include "manager.h"		// �}�l�[�W���[
#include "main.h"			// ���C��
#include "renderer.h"		// �����_���[
#include "scene.h"			// �V�[��
#include "scene2D.h"		// �V�[��2D
#include "scene3D.h"		// �V�[��3D
#include "input.h"			// ����
#include "enemyr.h"			// �G
#include "bullet.h"			// �e
#include "sound.h"			// �T�E���h
#include "title.h"			// �^�C�g��
#include "fade.h"			// �t�F�[�h
#include "camera.h"			// �J����
#include "light.h"			// ���C�g
#include "meshfield.h"		// ���b�V���t�B�[���h
#include "wall.h"			// ���b�V���E�H�[��
#include "debugproc.h"		// �f�o�b�N�\��
#include "objectbg.h"		// �I�u�W�F�N�g�w�i
#include "starterh.h"		// �X�^�[�^�[
#include "horse.h"			// ���̔n
#include "gate.h"			// �Q�[�g
#include "owner.h"			// �n��(player)
#include "union.h"			// �n�ƃW���b�L�[
#include "logo.h"
#include "gauge.h"

#include "player.h"			// �v���C���[
#include "jockey.h"			// �W���b�L�[
#include "horse2.h"			// �n�Q
#include "horse3.h"
#include "horse4.h"
#include "horse5.h"
#include "horse6.h"
#include "horse7.h"
#include "horse8.h"
#include "horse9.h"
#include "horse10.h"
#include "jockey2.h"
#include "jockey3.h"
#include "jockey4.h"
#include "jockey5.h"
#include "jockey6.h"
#include "jockey7.h"
#include "jockey8.h"
#include "jockey9.h"
#include "jockey10.h"

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
CEnemy*CGame::m_pEnemy = NULL;
CCamera*CGame::m_pCamera = NULL;
CLight*CGame::m_pLight = NULL;
CMeshFiled*CGame::m_pMeshField = NULL;
CWall*CGame::m_pWall = NULL;
CObjectBG*CGame::m_pObjectbg = NULL;
CStarter*CGame::m_pStarter = NULL;
CHorse*CGame::m_pHorse = NULL;
CGate*CGame::m_pGate = NULL;

CPlayer*CGame::m_pPlayer = NULL;
CHorse2*CGame::m_pHorse2 = NULL;
CHorse3*CGame::m_pHorse3 = NULL;
CHorse4*CGame::m_pHorse4 = NULL;
CHorse5*CGame::m_pHorse5 = NULL;
CHorse6*CGame::m_pHorse6 = NULL;
CHorse7*CGame::m_pHorse7 = NULL;
CHorse8*CGame::m_pHorse8 = NULL;
CHorse9*CGame::m_pHorse9 = NULL;
CHorse10*CGame::m_pHorse10 = NULL;
CJockey*CGame::m_pJockey = NULL;
CJockey2*CGame::m_pJockey2 = NULL;
CJockey3*CGame::m_pJockey3 = NULL;
CJockey4*CGame::m_pJockey4 = NULL;
CJockey5*CGame::m_pJockey5 = NULL;
CJockey6*CGame::m_pJockey6 = NULL;
CJockey7*CGame::m_pJockey7 = NULL;
CJockey8*CGame::m_pJockey8 = NULL;
CJockey9*CGame::m_pJockey9 = NULL;
CJockey10*CGame::m_pJockey10 = NULL;
COwner*CGame::m_pOwner = NULL;
CUnion*CGame::m_pUnion = NULL;
CScene3D*CGame::m_pScene3D = NULL;
CGauge*CGame::m_pGauge = NULL;

CGame::STATE CGame::m_State = CGame::STATE_NONE;

LPDIRECT3DTEXTURE9	CGame::m_pTexture = NULL;
LPDIRECT3DVERTEXBUFFER9 CGame::m_pVtxBuff = NULL;
int CGame::m_nTimer = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CGame::CGame()
{
	m_nIndex = 0;
	m_nCounterGameState = 0;
	m_State = STATE_NONE;
	m_Gametimmer = 0;
	m_nTimer = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CGame::~CGame()
{

}

//=============================================================================
// ���[�h
//=============================================================================
HRESULT CGame::Load(void)
{
	return S_OK;
}

//=============================================================================
// �A�����[�h
//=============================================================================
void CGame::Unload(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();

		m_pTexture = NULL;
	}
}

//=============================================================================
// �Q�[���̐���
//=============================================================================
CGame *CGame::Create(void)
{
	CGame *pGame;

	pGame = new CGame;

	pGame->Init();

	return pGame;
}

//=============================================================================
// ����������
//=============================================================================
void CGame::Init(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = NULL;

	pDevice = CManager::GetRenderer()->GetDevice();

	m_pCamera = new CCamera;
	m_pLight = new CLight;

	//===================================
	// �ǂݍ��ݗ�
	//===================================

	// �J�����̏�����
	m_pCamera->Init();

	// �J�������擾
	m_pCamera->SetMode(CCamera::MODE_GAME);

	// ���C�g�̏�����
	m_pLight->Init();

	// �I�u�W�F�N�g�w�i�̓ǂݍ���
	CObjectBG::Load();

	// �X�^�[�^�[�̓ǂݍ���
	CStarter::Load();

	// �Q�[�g�̓ǂݍ���
	CGate::Load();

	// �n�̓ǂݍ���
	CHorse::Load();
	// �n�̓ǂݍ���
	CHorse2::Load();
	// �n�̓ǂݍ���
	CHorse3::Load();
	// �n�̓ǂݍ���
	CHorse4::Load();
	// �n�̓ǂݍ���
	CHorse5::Load();
	// �n�̓ǂݍ���
	CHorse6::Load();
	// �n�̓ǂݍ���
	CHorse7::Load();
	// �n�̓ǂݍ���
	CHorse8::Load();
	// �n�̓ǂݍ���
	CHorse9::Load();
	// �n�̓ǂݍ���
	CHorse10::Load();
	// �v���C���[��ǂݍ���
	CPlayer::Load();

	// �W���b�L�[�̓ǂݍ���
	CJockey::Load();
	// �W���b�L�[�̓ǂݍ���
	CJockey2::Load();
	// �W���b�L�[�̓ǂݍ���
	CJockey3::Load();
	// �W���b�L�[�̓ǂݍ���
	CJockey4::Load();
	// �W���b�L�[�̓ǂݍ���
	CJockey5::Load();
	// �W���b�L�[�̓ǂݍ���
	CJockey6::Load();
	// �W���b�L�[�̓ǂݍ���
	CJockey7::Load();
	// �W���b�L�[�̓ǂݍ���
	CJockey8::Load();
	// �W���b�L�[�̓ǂݍ���
	CJockey9::Load();
	// �W���b�L�[�̓ǂݍ���
	CJockey10::Load();

	// �I�[�i�[�̓ǂݍ���
	COwner::Load();

	// �Q�[�W�̓ǂݍ���
	CGauge::Load();

	//===================================
	// ������
	//===================================

	// �v���C���[�̐���
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, D3DX_PI, 0), CPlayer::JOCKEYTYPE_GAME);
	// �W���b�L�[�̐���
	m_pJockey = CJockey::Create(D3DXVECTOR3(0, 20, 0), D3DXVECTOR3(0, D3DX_PI, 0), CJockey::JOCKEYTYPE_GAME);
	// �n2�̐���
	m_pHorse2 = CHorse2::Create(D3DXVECTOR3(50, 0, 0), D3DXVECTOR3(0, D3DX_PI, 0), CHorse2::JOCKEYTYPE_GAME);
	// �W���b�L�[�Q�̐���
	m_pJockey2 = CJockey2::Create(D3DXVECTOR3(50, 20, 0),D3DXVECTOR3(0,D3DX_PI,0),CJockey2::JOCKEYTYPE_GAME);
	// �n3�̐���
	m_pHorse3 = CHorse3::Create(D3DXVECTOR3(-50, 0, 0), D3DXVECTOR3(0, D3DX_PI, 0), CHorse3::JOCKEYTYPE_GAME);
	// �W���b�L�[3�̐���
	m_pJockey3 = CJockey3::Create(D3DXVECTOR3(-50, 20, 0), D3DXVECTOR3(0, D3DX_PI, 0), CJockey3::JOCKEYTYPE_GAME);
	// �n4�̐���
	m_pHorse4 = CHorse4::Create(D3DXVECTOR3(-100, 0, 0), D3DXVECTOR3(0, D3DX_PI, 0), CHorse4::JOCKEYTYPE_GAME);
	// �W���b�L�[4�̐���
	m_pJockey4 = CJockey4::Create(D3DXVECTOR3(-100, 20, 0), D3DXVECTOR3(0, D3DX_PI, 0), CJockey4::JOCKEYTYPE_GAME);
	// �n5�̐���
	m_pHorse5 = CHorse5::Create(D3DXVECTOR3(-150, 0, 0), D3DXVECTOR3(0, D3DX_PI, 0), CHorse5::JOCKEYTYPE_GAME);
	// �W���b�L�[5�̐���
	m_pJockey5 = CJockey5::Create(D3DXVECTOR3(-150, 20, 0), D3DXVECTOR3(0, D3DX_PI, 0), CJockey5::JOCKEYTYPE_GAME);
	// �n6�̐���
	m_pHorse6 = CHorse6::Create(D3DXVECTOR3(-200, 0, 0), D3DXVECTOR3(0, D3DX_PI, 0), CHorse6::JOCKEYTYPE_GAME);
	// �W���b�L�[6�̐���
	m_pJockey6 = CJockey6::Create(D3DXVECTOR3(-200, 20, 0), D3DXVECTOR3(0, D3DX_PI, 0), CJockey6::JOCKEYTYPE_GAME);
	// �n7�̐���
	m_pHorse7 = CHorse7::Create(D3DXVECTOR3(-250, 0, 0), D3DXVECTOR3(0, D3DX_PI, 0), CHorse7::JOCKEYTYPE_GAME);
	// �W���b�L�[7�̐���
	m_pJockey7 = CJockey7::Create(D3DXVECTOR3(-250, 20, 0), D3DXVECTOR3(0, D3DX_PI, 0), CJockey7::JOCKEYTYPE_GAME);
	// �n8�̐���
	m_pHorse8 = CHorse8::Create(D3DXVECTOR3(-300, 0, 0), D3DXVECTOR3(0, D3DX_PI, 0), CHorse8::JOCKEYTYPE_GAME);
	// �W���b�L�[8�̐���
	m_pJockey8 = CJockey8::Create(D3DXVECTOR3(-300, 20, 0), D3DXVECTOR3(0, D3DX_PI, 0), CJockey8::JOCKEYTYPE_GAME);
	// �n9�̐���
	m_pHorse9 = CHorse9::Create(D3DXVECTOR3(-350, 0, 0), D3DXVECTOR3(0, D3DX_PI, 0), CHorse9::JOCKEYTYPE_GAME);
	// �W���b�L�[9�̐���
	m_pJockey9 = CJockey9::Create(D3DXVECTOR3(-350, 20, 0), D3DXVECTOR3(0, D3DX_PI, 0), CJockey9::JOCKEYTYPE_GAME);
	// �n10�̐���
	m_pHorse10 = CHorse10::Create(D3DXVECTOR3(-400, 0, 0), D3DXVECTOR3(0, D3DX_PI, 0), CHorse10::JOCKEYTYPE_GAME);
	// �W���b�L�[10�̐���
	m_pJockey10 = CJockey10::Create(D3DXVECTOR3(-400, 20, 0), D3DXVECTOR3(0, D3DX_PI, 0), CJockey10::JOCKEYTYPE_GAME);

	// �r���{�[�h�̐���
	CBillboard::Create(D3DXVECTOR3(0, 200, 50), D3DXVECTOR3(0, 0, 0));

	// ���b�V���t�B�[���h�̐���
	m_pMeshField = CMeshFiled::Create(D3DXVECTOR3(-300.0f, 0.0f, 1700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), X_SIZE, Z_SIZE, mPolygonX, mPolygonZ);

	// �ǂ̐���
	/*�E*/m_pWall = CWall::Create(D3DXVECTOR3(300.0f, 100.0f, 1700.0f), D3DXVECTOR3(0.0f, 0.0f, 1.5f), X_SIZE, Y_SIZE, mPolygonX, mPolygonY);
	/*��*/m_pWall = CWall::Create(D3DXVECTOR3(-900.0f, 100.0f, 1700.0f), D3DXVECTOR3(0.0f, 0.0f, -1.5f), X_SIZE, Y_SIZE, mPolygonX, mPolygonY);
	/*��*/m_pWall = CWall::Create(D3DXVECTOR3(-300.0f, 100.0f, 3600.0f), D3DXVECTOR3(-1.5f, 0.0f, 0.0f), 2000, 1200, mPolygonX, mPolygonY);
	/*�O*/m_pWall = CWall::Create(D3DXVECTOR3(-300.0f, 100.0f, 0.0f), D3DXVECTOR3(1.5f, 0.0f, 0.0f), 2000, 1200, mPolygonX, mPolygonY);
	/*�W*/m_pWall = CWall::Create(D3DXVECTOR3(-300.0f, 600.0f, 1700.0f), D3DXVECTOR3(0.0f, 0.0f, D3DX_PI), X_SIZE, Z_SIZE, mPolygonX, mPolygonZ);


	// �I�u�W�F�N�g�w�i�̐���
	// ���n��
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-800.0f, 0.0f, 500.0f), D3DXVECTOR3(0.0f, 30.0f, 0.0f), CObjectBG::MODELTYPE_BILL000);

	// �S�[���̐���
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 3000.0f),D3DXVECTOR3(0.0f,11.0f,0.0f), CObjectBG::MODELTYPE_GOAL);

	// �Q�[�W�̐���
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, -30.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 30.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 60.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 90.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 125.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 155.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 185.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 215.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 245.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 275.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 305.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 335.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 365.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 395.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 425.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 455.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 485.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 515.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 545.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 575.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 605.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 635.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 665.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 695.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 725.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 755.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 785.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 815.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 845.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 875.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 905.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 935.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 965.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 995.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 1025.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 1055.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 1085.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 1105.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 1135.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 1165.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 1195.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 1225.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 1255.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 1285.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 1315.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 1345.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 1375.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 1405.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 1435.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 1465.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 1495.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 1525.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 1555.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 1585.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 1615.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 1645.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 1675.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 1705.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 1735.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 1765.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 1795.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 1825.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 1855.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 1885.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 1915.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 1945.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 1975.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 2005.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 2035.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 2065.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 2095.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 2125.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 2155.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 2185.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 2215.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 2245.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 2275.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 2305.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 2335.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 2365.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 2395.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 2425.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 2455.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 2485.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 2515.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 2545.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 2575.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 2605.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 2635.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 2665.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 2695.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 2725.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 2755.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 2785.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 2815.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 2845.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 2875.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 2905.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 2935.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 2965.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 2995.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 3025.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 3055.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 3085.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 3115.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 3145.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 3175.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 3205.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 3235.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 3265.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 3295.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 3295.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 3295.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 3325.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 3355.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 3385.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 3415.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 3445.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(100.0f, 0.0f, 3475.0f), D3DXVECTOR3(0.0f, -11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);

	//===================����====================================================================================================================
	// �Q�[�W�̐���
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, -30.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 30.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 60.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 90.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 125.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 155.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 185.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 215.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 245.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 275.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 305.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 335.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 365.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 395.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 425.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 455.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 485.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 515.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 545.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 575.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 605.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 635.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 665.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 695.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 725.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 755.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 785.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 815.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 845.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 875.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 905.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 935.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 965.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 995.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 1025.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 1055.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 1085.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 1105.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 1135.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 1165.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 1195.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 1225.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 1255.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 1285.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 1315.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 1345.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 1375.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 1405.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 1435.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 1465.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 1495.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 1525.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 1555.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 1585.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 1615.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 1645.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 1675.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 1705.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 1735.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 1765.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 1795.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 1825.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 1855.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 1885.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 1915.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 1945.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 1975.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 2005.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 2035.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 2065.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 2095.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 2125.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 2155.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 2185.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 2215.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 2245.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 2275.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 2305.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 2335.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 2365.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 2395.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 2425.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 2455.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 2485.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 2515.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 2545.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 2575.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 2605.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 2635.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 2665.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 2695.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 2725.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 2755.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 2785.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 2815.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 2845.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 2875.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 2905.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 2935.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 2965.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 2995.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 3025.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 3055.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 3085.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 3115.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 3145.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 3175.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 3205.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 3235.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 3265.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 3295.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 3295.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 3295.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 3325.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 3355.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 3385.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 3415.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 3445.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);
	m_pObjectbg = CObjectBG::Create(D3DXVECTOR3(-500.0f, 0.0f, 3475.0f), D3DXVECTOR3(0.0f, 11.0f, 0.0f), CObjectBG::MODELTYPE_GAGE);


	// �X�^�[�^�[�̐���
	//m_pStarter = CStarter::Create(D3DXVECTOR3(0, 50, 0));

	// �Q�[�g�̐���
	//CGate::Create(D3DXVECTOR3(0, 10, 0),CGate::GATE_TYPE1);
	//CGate::Create(D3DXVECTOR3(0, 10, 0), CGate::GATE_TYPE1);

	// �I�[�i�[
	m_pOwner = COwner::Create(D3DXVECTOR3(150.0f, 0.0f, 100.0f),D3DXVECTOR3(0.0f,D3DX_PI / 2,0.0f));

	// �Q�[�W�̐���
	CGauge::Create(D3DXVECTOR3(50, 80, 0), 100.0f, 100.0f);

}

//=============================================================================
// �I������
//=============================================================================
void CGame::Uninit(void)
{
	CPlayer::Unload();
	// �I�u�W�F�N�g�w�i�̓ǂݍ���
	CObjectBG::UnLoad();
	// �X�^�[�^�[�̓ǂݍ���
	CStarter::Unload();
	// �Q�[�g�̓ǂݍ���
	CGate::Unload();
	// �n�̓ǂݍ���
	CHorse::Unload();
	// �n2�̓ǂݍ���
	CHorse2::Unload();
	// �n3�̓ǂݍ���
	CHorse3::Unload();
	// �n4�̓ǂݍ���
	CHorse4::Unload();
	// �n5�̓ǂݍ���
	CHorse5::Unload();
	// �n6�̓ǂݍ���
	CHorse6::Unload();
	// �n7�̓ǂݍ���
	CHorse7::Unload();
	// �n8�̓ǂݍ���
	CHorse8::Unload();
	// �n9�̓ǂݍ���
	CHorse9::Unload();
	// �n10�̓ǂݍ���
	CHorse10::Unload();
	// �W���b�L�[�̓ǂݍ���
	CJockey::Unload();
	// �W���b�L�[�̓ǂݍ���
	CJockey2::Unload();
	// �W���b�L�[�̓ǂݍ���
	CJockey3::Unload();
	// �W���b�L�[�̓ǂݍ���
	CJockey4::Unload();
	// �W���b�L�[�̓ǂݍ���
	CJockey5::Unload();
	// �W���b�L�[�̓ǂݍ���
	CJockey6::Unload();
	// �W���b�L�[�̓ǂݍ���
	CJockey7::Unload();
	// �W���b�L�[�̓ǂݍ���
	CJockey8::Unload();
	// �W���b�L�[�̓ǂݍ���
	CJockey9::Unload();
	// �W���b�L�[�̓ǂݍ���
	CJockey10::Unload();
	// �I�[�i�[�̓ǂݍ���
	COwner::Unload();

	// �J������j��
	if (m_pCamera != NULL)
	{
		m_pCamera->Uninit();			// �J����������

		delete m_pCamera;
		m_pCamera = NULL;
	}

	// ���C�g��j��
	if (m_pLight != NULL)
	{
		m_pLight->Uninit();				// ���C�g������

		delete m_pLight;
		m_pLight = NULL;
	}

	// �v���C���[��NULL�`�F�b�N
	if (m_pPlayer != NULL)
	{
		m_pPlayer = NULL;
	}

	if (m_pObjectbg != NULL)
	{
		m_pObjectbg = NULL;
	}

	// ���b�V���t�B�[���h��NULL�`�F�b�N
	if (m_pMeshField != NULL)
	{
		//m_pMeshField->Uninit();
		m_pMeshField = NULL;
	}

	CScene::ReleaseAll();
}

//=============================================================================
// �X�V����
//=============================================================================
void CGame::Update(void)
{
	// �L�[�{�[�h���擾
	CInputKeyboard *InputKeyboard;
	InputKeyboard = CManager::GetInputKeyboard();

	// �f�o�b�N���擾
	CDebugProc *m_Dubug = CRenderer::GetDebug();

	// �t�F�[�h���擾
	CFade *pFade;
	pFade = CManager::GetFade();

	m_Gametimmer++;
	m_nTimer++;

	// NULL�`�F�b�N
	if (m_pCamera != NULL)
	{
		m_pCamera->Update();			// �J�������X�V
	}

	// NULL�`�F�b�N
	if (m_pLight != NULL)
	{
		m_pLight->Update();				// ���C�g���X�V
	}

	// �f�o�b�N�\��
#ifdef _DEBUG
	m_Dubug->Print("s", "Game");

#endif // DEBUG
}

//=============================================================================
// �`�揈��
//=============================================================================
void CGame::Draw(void)
{
	// NULL�`�F�b�N
	if (m_pCamera != NULL)
	{
		m_pCamera->SetCamera();			// �J�����̐ݒ�
	}
}

//=============================================================================
// �v���C���[�̎擾
//=============================================================================
CPlayer *CGame::GetPlayer(void)
{
	return m_pPlayer;
}

//=============================================================================
// �G�̎擾
//=============================================================================
CEnemy *CGame::GetEnemy(void)
{
	return m_pEnemy;
}

//=============================================================================
// �J�����̎擾
//=============================================================================
CCamera * CGame::GetCamera(void)
{
	return m_pCamera;
}

//=============================================================================
// ���C�g�̎擾
//=============================================================================
CLight * CGame::GetLight(void)
{
	return m_pLight;
}

//=============================================================================
// ���b�V���t�B�[���h�̎擾
//=============================================================================
CMeshFiled * CGame::GetMeshFiled(void)
{
	return m_pMeshField;
}

//=============================================================================
// ���b�V���t�B�[���h�̎擾
//=============================================================================
CWall * CGame::GetWall(void)
{
	return m_pWall;
}

//=============================================================================
// �I�u�W�F�N�g�w�i�̎擾
//=============================================================================
CObjectBG * CGame::GetObjectbg(void)
{
	return m_pObjectbg;
}

//=============================================================================
// �X�^�[�^�[�̎擾
//=============================================================================
CStarter * CGame::GetStarter(void)
{
	return m_pStarter;
}

//=============================================================================
// �n�̎擾
//=============================================================================
CHorse * CGame::GetHorse(void)
{
	return m_pHorse;
}
//=============================================================================
// �n2�̎擾
//=============================================================================
CHorse2 * CGame::GetHorse2(void)
{
	return m_pHorse2;
}
//=============================================================================
// �n3�̎擾
//=============================================================================
CHorse3 * CGame::GetHorse3(void)
{
	return m_pHorse3;
}
//=============================================================================
// �n4�̎擾
//=============================================================================
CHorse4 * CGame::GetHorse4(void)
{
	return m_pHorse4;
}
//=============================================================================
// �n5�̎擾
//=============================================================================
CHorse5 * CGame::GetHorse5(void)
{
	return m_pHorse5;
}
//=============================================================================
// �n6�̎擾
//=============================================================================
CHorse6 * CGame::GetHorse6(void)
{
	return m_pHorse6;
}
//=============================================================================
// �n7�̎擾
//=============================================================================
CHorse7 * CGame::GetHorse7(void)
{
	return m_pHorse7;
}
//=============================================================================
// �n8�̎擾
//=============================================================================
CHorse8 * CGame::GetHorse8(void)
{
	return m_pHorse8;
}
//=============================================================================
// �n9�̎擾
//=============================================================================
CHorse9 * CGame::GetHorse9(void)
{
	return m_pHorse9;
}
//=============================================================================
// �n10�̎擾
//=============================================================================
CHorse10 * CGame::GetHorse10(void)
{
	return m_pHorse10;
}

//=============================================================================
// �Q�[�g�̎擾
//=============================================================================
CGate * CGame::GetGate(void)
{
	return m_pGate;
}

//=============================================================================
// �W���b�L�[1�̎擾
//=============================================================================
CJockey * CGame::GetJockey(void)
{
	return m_pJockey;
}
//=============================================================================
// �W���b�L�[2�̎擾
//=============================================================================
CJockey2 * CGame::GetJockey2(void)
{
	return m_pJockey2;
}
//=============================================================================
// �W���b�L�[3�̎擾
//=============================================================================
CJockey3 * CGame::GetJockey3(void)
{
	return m_pJockey3;
}
//=============================================================================
// �W���b�L�[4�̎擾
//=============================================================================
CJockey4 * CGame::GetJockey4(void)
{
	return m_pJockey4;
}
//=============================================================================
// �W���b�L�[5�̎擾
//=============================================================================
CJockey5 * CGame::GetJockey5(void)
{
	return m_pJockey5;
}
//=============================================================================
// �W���b�L�[6�̎擾
//=============================================================================
CJockey6 * CGame::GetJockey6(void)
{
	return m_pJockey6;
}
//=============================================================================
// �W���b�L�[7�̎擾
//=============================================================================
CJockey7 * CGame::GetJocke7(void)
{
	return m_pJockey7;
}

//=============================================================================
// �W���b�L�[8�̎擾
//=============================================================================
CJockey8 * CGame::GetJocke8(void)
{
	return m_pJockey8;
}

//=============================================================================
// �W���b�L�[9�̎擾
//=============================================================================
CJockey9 * CGame::GetJockey9(void)
{
	return m_pJockey9;
}

//=============================================================================
// �W���b�L�[10�̎擾
//=============================================================================
CJockey10 * CGame::GetJockey10(void)
{
	return m_pJockey10;
}

//=============================================================================
// �I�[�i�[�̎擾
//=============================================================================
COwner * CGame::GetOwner(void)
{
	return m_pOwner;
}

//=============================================================================
// ���̂̎擾
//=============================================================================
CUnion * CGame::GetUnion(void)
{
	return m_pUnion;
}

//=============================================================================
// 3D�I�u�W�F�N�g�̎擾
//=============================================================================
CScene3D * CGame::GetScene3D(void)
{
	return m_pScene3D;
}

//=============================================================================
// �Q�[�W�̎擾
//=============================================================================
CGauge * CGame::GetGauge(void)
{
	return m_pGauge;
}

//=============================================================================
// �^�C���擾
//=============================================================================
int CGame::GetTime(void)
{
	return m_nTimer;
}
