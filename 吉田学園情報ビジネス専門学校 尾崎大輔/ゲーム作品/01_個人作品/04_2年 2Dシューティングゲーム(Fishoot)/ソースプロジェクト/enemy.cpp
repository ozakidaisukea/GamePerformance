//=============================================================================
//
// �G�̏���[enemy.cpp]
// Author : Ozaki
//
//=============================================================================
#include "enemy.h"
#include "main.h"
#include "scene.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "scene2D.h"
#include "bullet.h"
#include "life.h"
#include "score.h"
#include "explosion.h"
#include "game.h"
#include "fade.h"
#include "player.h"
#include "tutorial.h"
#include "sound.h"

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9 CEnemy::m_pTexture[MAX_ENEMY] = {};
int				   CEnemy::m_nCounterEnemyState = NULL;
int				   CEnemy::m_enemyall = 0;
CSound			  *CEnemy::m_pSound = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CEnemy::CEnemy():CScene2D(3)
{
	m_enemyall++;
	m_CountState = 0;
	state = ENEMYSTATE_NORMAL;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CEnemy::~CEnemy()
{

}

//=============================================================================
// ���[�h
//=============================================================================
HRESULT CEnemy::Load(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = NULL;

	pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̐���[0]
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\game\\tori.png",
		&m_pTexture[0]);

	// �e�N�X�`���̐���[1]
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\game\\baiku.png",
		&m_pTexture[1]);

	// �e�N�X�`���̐���[2]
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\game\\moutaboard.png",
		&m_pTexture[2]);

	// �e�N�X�`���̐���[3]
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\game\\gyosen.png",
		&m_pTexture[3]);

	// �e�N�X�`���̐���[4]
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\game\\utyusen1.png",
		&m_pTexture[4]);

	return S_OK;
}

//=============================================================================
// �A�����[�h
//=============================================================================
void CEnemy::Unload(void)
{
	for (int nCnt = 0; nCnt < MAX_ENEMY; nCnt++)
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
HRESULT CEnemy::Init(D3DXVECTOR3 pos, float widtgh, float height, D3DXVECTOR3 move, int life, ENEMY_TYPE type)
{

	CScene2D::Init(pos,widtgh,height);

	m_widtgh = widtgh;
	m_height = height;
	m_move = move;
	m_nLife = life;
	m_Type = type;
	m_nCounterEnemyState = 0;

	SetObjtType(CScene::OBJTYPE_ENEMY);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CEnemy::Uninit(void)
{
	m_enemyall--;
	CScene2D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CEnemy::Update(void)
{
	D3DXVECTOR3 pos;

	pos = GetPosition();

	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = NULL;

	pDevice = CManager::GetRenderer()->GetDevice();

	CInputKeyboard *InputKeyboard;
	InputKeyboard = CManager::GetInputKeyboard();

	m_bullettime++;


	if (pos.x >= 700)
	{
		// �ړ���
		m_move.x -= 0.01f;

		pos += m_move;
	}

	// �e�̐���
	if (m_bullettime == 120)
	{
		D3DXVECTOR3 Playerpos = CPlayer::GetPlayerPos();
		D3DXVECTOR3	movebullet = D3DXVECTOR3(0,0,0);
		D3DXVECTOR3 Bulletpos;
		float fAngle;

		Bulletpos.x = Playerpos.x - pos.x;
		Bulletpos.y = Playerpos.y - pos.y;

		fAngle = atan2f(Bulletpos.x, Bulletpos.y);

		movebullet.x += sinf(fAngle) * MAX_BULLETSPEED;
		movebullet.y += cosf(fAngle) * MAX_BULLETSPEED;

		CBullet::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), D3DXVECTOR3(movebullet.x,movebullet.y,movebullet.z), 80.0f,80.0f, CBullet::BULLETTYPE_AMI);

		m_bullettime = 0;
	}

	switch (state)
	{
	case ENEMYSTATE_NORMAL:

		CScene2D::SetColor(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));

		m_CountState = 0;
		break;

	case ENEMYSTATE_DEATH:

		break;

	case ENEMYSTATE_DAMAGE:

		m_CountState--;

		CScene2D::SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

		if (m_CountState <= 10)
		{
			state = ENEMYSTATE_NORMAL;
		}
		break;
	}

	 //���̐ݒ�
	if (pos.x >= 800)
	{
		if (CEnemy::ENEMY_TORI == m_Type)
		{
			if (pos.y <= 200)
			{
				m_move.y += 0.01f;

				pos += m_move;

			}
			else if (pos.y >= 200)
			{
				m_move.y *= -0.5f;

				pos += m_move;
			}
		}
	}

	// �|�W�V�����̐ݒ�
	SetPosition(pos, m_rot, m_position, m_flength);
}

//=============================================================================
// �`�揈��
//=============================================================================
void CEnemy::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// �G�̐���
//=============================================================================
CEnemy *CEnemy::Create(D3DXVECTOR3 pos, float widtgh, float height, D3DXVECTOR3 move,int life, ENEMY_TYPE type)
{
	CEnemy *pEnemy;

	pEnemy = new CEnemy;

	pEnemy->Init(pos, widtgh,height, move,life, type);

	// ���L�e�N�X�`�������蓖�Ă�
	pEnemy->BindTexture(m_pTexture[type]);

	return pEnemy;
}

//=============================================================================
//�G�̃_���[�W����
//=============================================================================
void CEnemy::HitEnemy(int nDamage)
{
	m_nLife -= nDamage;

	D3DXVECTOR3 enemypos;

	enemypos = GetPosition();

	// �T�E���h���擾
	CSound *pSound;
	pSound = CManager::GetSound();

	pSound->PlaySound(pSound->SOUND_LABEL_SE_DAMAGE);

	state = ENEMYSTATE_DAMAGE;


	// �G�̃��C�t���O�ɂȂ�����
	if (m_nLife <= 0)
	{
		m_CountState = 15;

		// �����̐���
		CExplosion::Create(D3DXVECTOR3(enemypos.x, enemypos.y, 0), 300.0f, 300.0f);

		m_nCounterEnemyState++;

		// ���[�h���擾
		CManager::MODE mode;
		mode = CManager::GetMode();

		// �X�R�A���擾
		CScore *pScore;

		switch (mode)
		{
		case CManager::MODE_TUTORIAL:

			// �X�R�A�̎擾
			pScore = CTutorial::GetScore();

			pSound->PlaySound(pSound->SOUND_LABEL_SE_EXPLOSION);

			// �X�R�A���Z
			pScore->AddScore(1000);
			break;

		case CManager::MODE_GAME:

			// �X�R�A�̎擾
			pScore = CGame::GetScore();

			pSound->PlaySound(pSound->SOUND_LABEL_SE_EXPLOSION);

			// �X�R�A���Z
			pScore->AddScore(1000);
			break;
		}

		if (CManager::GetMode() == CManager::MODE_GAME)
		{
			CGame *pGame = CManager::GetGame();
			if (pGame != NULL)
			{
				pGame->SetNumEnemyAll(pGame->GetNumEnemyAll() - 1);
				if (pGame->GetNumEnemyAll() <= 0)
				{
					pGame->SetState(CGame::STATE_RESULT);
				}
				else
				{
					pGame->SetEnemy();
				}
			}
		}
		Uninit();
	}
}

//// ��]
//if (m_rot > D3DX_PI)
//{
//	m_rot -= D3DX_PI * 2;
//}
//if (m_rot < -D3DX_PI)
//{
//	m_rot += D3DX_PI * 2;
//}

//// �g��
//if (m_position > 200)
//{
//	m_Addposition *= -1;
//}
//// �k��
//if (m_position < -200)
//{
//	m_Addposition *= -1;
//}