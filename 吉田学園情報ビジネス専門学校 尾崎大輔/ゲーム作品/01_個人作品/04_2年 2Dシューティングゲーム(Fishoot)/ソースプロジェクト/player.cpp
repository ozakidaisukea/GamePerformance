//=============================================================================
//
// �v���C���[ [player.cpp]
// Author : Ozaki
//
//=============================================================================
#include "player.h"
#include "main.h"
#include "scene.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "scene2D.h"
#include "bullet.h"
#include "effect.h"
#include "enemy.h"
#include "game.h"
#include "gauge.h"
#include "tutorial.h"
#include "explosion.h"
#include "sound.h"
#include "joypad.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define PLAYER_SPEED	(3.5f)

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9 CPlayer::m_pTexture = NULL;
D3DXVECTOR3		   CPlayer::m_pos = D3DXVECTOR3(0,0,0);
CSound*CPlayer::m_pSound = NULL;						// �T�E���h
CPlayer::PLAYERSTATE CPlayer::state = {};
CBullet*CPlayer::m_pBullet = NULL;
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CPlayer::CPlayer():CScene2D(2)
{
	m_effecttimer = 0;
	m_bullettime = 0;
	m_nLife = 0;
	state = PLAYERSTATE_NORMAL;
	m_posold = D3DXVECTOR3(0, 0, 0);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pBullet = 0;
	m_ultimatetimer = 0;
	m_CountState = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CPlayer::~CPlayer()
{

}

//=============================================================================
// ���[�h
//=============================================================================
HRESULT CPlayer::Load(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = NULL;

	pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\game\\syake.png",
		&m_pTexture);

	return S_OK;
}

//=============================================================================
// �A�����[�h
//=============================================================================
void CPlayer::Unload(void)
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
HRESULT CPlayer::Init(D3DXVECTOR3 pos, float widtgh, float height)
{
	CScene2D::Init(pos,widtgh,height);

	m_widtgh = widtgh;

	m_height = height;

	SetObjtType(CScene::OBJTYPE_PLAYER);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CPlayer::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CPlayer::Update(void)
{
	D3DXVECTOR3 posold;
	D3DXVECTOR3 Enemypos[MAX_ENEMY] = {};
	D3DXVECTOR3	moveplayer = D3DXVECTOR3(0, 0, 0);
	D3DXVECTOR3 move = m_move;
	D3DXVECTOR3 TargetPos;
	D3DXVECTOR3 lengthpos;
	int			nCntEnemy = 0;
	float fAngle;

	m_pos = GetPosition();
	m_bullettime++;
	m_effecttimer++;

	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = NULL;

	pDevice = CManager::GetRenderer()->GetDevice();

	// �L�[�{�[�h���擾
	CInputKeyboard *InputKeyboard;
	InputKeyboard = CManager::GetInputKeyboard();

	// �L�[�{�[�h���擾
	CInputjoypad *InputJoypad;
	InputJoypad = CManager::GetInputJoypad();

	// �T�E���h���擾
	CSound *pSound;
	pSound = CManager::GetSound();

	//====================================================
	// �L�[�{�[�h
	//====================================================

	// ��ړ�[W�L�[��]
	if (InputKeyboard->GetPress(DIK_W) == true)
	{
		m_pos.y -= PLAYER_SPEED;
	}

	// ���ړ�[S�L�[��]
	if (InputKeyboard->GetPress(DIK_S) == true)
	{
		m_pos.y += PLAYER_SPEED;
	}

	// ���ړ�[A�L�[ ��]
	if (InputKeyboard->GetPress(DIK_A) == true)
	{
		m_pos.x -= PLAYER_SPEED;
	}

	// �E�ړ�[D�L�[ ��]
	if (InputKeyboard->GetPress(DIK_D) == true)
	{
		m_pos.x += PLAYER_SPEED;
	}

	//======================================================================
	// ���X�e�B�b�N
	//======================================================================

	// ��ړ�
	if (InputJoypad->GetPress(CInputjoypad::DIJS_STICK_LEFT_UP) == true)
	{
		m_pos.y -= PLAYER_SPEED;
	}

	// ���ړ�
	if (InputJoypad->GetPress(CInputjoypad::DIJS_STICK_LEFT_DOWN) == true)
	{
		m_pos.y += PLAYER_SPEED;

	}

	// ���ړ�
	if (InputJoypad->GetPress(CInputjoypad::DIJS_STICK_LEFT_LEFT) == true)
	{
		m_pos.x -= PLAYER_SPEED;
	}

	// �E�ړ�
	if (InputJoypad->GetPress(CInputjoypad::DIJS_STICK_LEFT_RIGTH) == true)
	{
		m_pos.x += PLAYER_SPEED;

	}

	//======================================================================
	// �\���L�[
	//======================================================================

	if (InputJoypad->GetPress(CInputjoypad::DIJS_STICK_POV_UP) == true || InputJoypad->GetPress(CInputjoypad::DIJS_STICK_POV_DOWN) == true
		|| InputJoypad->GetPress(CInputjoypad::DIJS_STICK_POV_LEFT) == true || InputJoypad->GetPress(CInputjoypad::DIJS_STICK_POV_RIGTH) == true)
	{
		m_pos.x += sinf(InputJoypad->GetRadiom()) * PLAYER_SPEED;
		m_pos.y -= cosf(InputJoypad->GetRadiom()) * PLAYER_SPEED;
	}

	// �e[SPACE�L�[]
	if (InputKeyboard->GetTrigger(DIK_SPACE) == true || InputJoypad->GetTrigger(CInputjoypad::DIJS_BOTTON_A) == true
		|| InputJoypad->GetTrigger(CInputjoypad::DIJS_BOTTON_RT) == true)
	{
		if (m_bool == false)
		{
			// �e�̐���
			CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z), D3DXVECTOR3(PLAYER_SPEED, -10.0f, move.z), 50.0f, 50.0f, CBullet::BULLETTYPE_PLAYER);

			pSound->PlaySound(pSound->SOUND_LABEL_SE_SHOT);

			m_bool = true;
		}
	}

	if (m_bool == true)
	{
		m_bullettime++;
		if (m_bullettime >= 120)
		{
			m_bool = false;

			pSound->StopSound(pSound->SOUND_LABEL_SE_SHOT);
			m_bullettime = 0;
		}
	}

	if (CGauge::m_fGauge >= 250.0f)
	{
		 // �K�E�Z
		if (InputKeyboard->GetPress(DIK_Q) == true && InputKeyboard->GetPress(DIK_E) == true ||
			InputJoypad->GetPress(CInputjoypad::DIJS_BOTTON_LB) == true && InputJoypad->GetPress(CInputjoypad::DIJS_BOTTON_RB) == true)
		{
			// �v���C���[���K�E�Z��
			state = PLAYERSTATE_ULTIMATE;

			pSound->PlaySound(pSound->SOUND_LABEL_SE_SUPERDRY);

			CGauge::AddGauge(-250.0f);
		}
	}

	switch (state)
	{

		// �v���C���[���K�E�Z��ł�
	case PLAYERSTATE_ULTIMATE:

		// �G�t�F�N�g�̐���
		CEffect::Create(D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), 100.0f, 100.0f);

		// �I�u�W�F�N�g�^�C�v���擾
		for (int nCntPriority = 0; nCntPriority < MAX_PRIORITY1; nCntPriority++)
		{
			for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
			{
				CScene2D *pScene;
				pScene = (CScene2D*)CScene::GetSCene(nCntScene, nCntPriority);

				if (pScene != NULL)
				{
					CScene::OBJTYPE objttpe;

					objttpe = pScene->GetObjtType();

					// �G�̓����蔻��
					if (objttpe == CScene::OBJTYPE_ENEMY)
					{
						Enemypos[0] = pScene->GetPosition();
						// �v���C���[�ʒu�ƓG�̈ʒu�̓����蔻��
						if ((Enemypos[0].x) - pScene->GetWidth() < m_pos.x && (Enemypos[0].x) + pScene->GetWidth() > m_pos.x &&
							(Enemypos[0].y) - pScene->GetHeigth() < m_pos.y && (Enemypos[0].y) + pScene->GetHeigth() > m_pos.y)
						{
							// ���[�h���擾
							CManager::MODE mode;
							mode = CManager::GetMode();

							switch (mode)
							{

								//======================
								// �`���[�g���A��
								//======================
							case CManager::MODE_TUTORIAL:

								// �G���擾
								CEnemy *ppEnemy;
								ppEnemy = CTutorial::GetEnemy();

								if (ppEnemy != NULL)
								{
									// �G�ւ̃_���[�W
									ppEnemy->HitEnemy(20);

									// �v���C���[�����ɂ����ʒu�ɖ߂�
									m_pos = D3DXVECTOR3(300, 600, 0);

									state = PLAYERSTATE_NORMAL;

									pSound->StopSound(pSound->SOUND_LABEL_SE_SUPERDRY);

								}
								break;

								//======================
								// �Q�[��
								//======================
							case CManager::MODE_GAME:

								// �G���擾
								CEnemy *pEnemy;
								pEnemy = CGame::GetEnemy(CManager::GetGame()->GetNumEnemy());

								if (pEnemy != NULL)
								{
									// �G�ւ̃_���[�W
									pEnemy->HitEnemy(20);

									// �v���C���[�����ɂ����ʒu�ɖ߂�
									m_pos = D3DXVECTOR3(300, 600, 0);

									state = PLAYERSTATE_NORMAL;

									pSound->StopSound(pSound->SOUND_LABEL_SE_SUPERDRY);
									break;
								}
							}
							m_bullettime = 0;
						}
					}
				}
			}
		}

		// �����̖ړI�n��G�̖ړI�n�Ɉڍs
		TargetPos.x = Enemypos[0].x - m_pos.x;
		TargetPos.y = Enemypos[0].y - m_pos.y;

		fAngle = atan2f(TargetPos.x, TargetPos.y);

		moveplayer.x += sinf(fAngle) * 15;
		moveplayer.y += cosf(fAngle) * 15;

		m_pos.x += moveplayer.x;
		m_pos.y += moveplayer.y;

		// �G�t�F�N�g�̎���
		if (m_effecttimer == 60)
		{
			// ���ʎ��ɂȂ�
			state = PLAYERSTATE_NORMAL;

			// �v���C���[�����ɂ����ʒu�ɖ߂�
			m_pos = m_posold;

			m_effecttimer = 0;
		}
		break;

		// �v���C���[���ʏ펞
	case PLAYERSTATE_NORMAL:

		// �v���C���[�ʒu
		m_posold = m_pos;

		CScene2D::SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		m_CountState = 0;

		// �v���C���[�̈ړ���
		if (m_pos.x <= 160)
		{
			// ��
			m_pos.x = 160;
		}

		else if (m_pos.x >= 1230)
		{
			// �E
			m_pos.x = 1230;
		}

		// �c�̐���
		if (m_pos.y >= 700)
		{
			m_pos.y = 700;
		}
		else if (m_pos.y <= 450)
		{
			m_pos.y = 450;
		}
		break;

		// �v���C���[�̃_���[�W���
	case PLAYERSTATE_DAMAGE:

		m_CountState--;

		CScene2D::SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

		if (m_CountState <= 10)
		{
			state = PLAYERSTATE_NORMAL;
		}
		break;

	}
	SetPosition(m_pos, m_rot, m_position, m_flength);
}

//=============================================================================
// �`�揈��
//=============================================================================
void CPlayer::Draw(void)
{
	CScene2D::Draw();
}


//=============================================================================
// �v���C���[�̃X�e�[�g���擾
//=============================================================================
CPlayer::PLAYERSTATE CPlayer::GetState(void)
{
	return state;
}


//=============================================================================
// �v���C���[�̈ʒu���擾
//=============================================================================
D3DXVECTOR3 CPlayer::GetPlayerPos(void)
{
	return m_pos;
}

//=============================================================================
// �v���C���[�̐���
//=============================================================================
CPlayer *CPlayer::Create(D3DXVECTOR3 pos, float widtgh, float height)
{
	CPlayer *pPlayer;

	pPlayer = new CPlayer;

	pPlayer->Init(pos,widtgh,height);

	pPlayer->m_widtgh = widtgh;

	pPlayer->m_height = height;

	// ���L�e�N�X�`�������蓖�Ă�
	pPlayer->BindTexture(m_pTexture);

	return pPlayer;
}