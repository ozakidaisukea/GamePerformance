//=============================================================================
//
// �e�̏����@[bullet.cpp]
// Author : Ozaki
//
//=============================================================================
#include "bullet.h"
#include "player.h"
#include "renderer.h"
#include "main.h"
#include "manager.h"
#include "scene2D.h"
#include "input.h"
#include "explosion.h"
#include "enemy.h"
#include "score.h"
#include "effect.h"
#include "life.h"
#include "game.h"
#include "fade.h"
#include "gameover.h"
#include "tutorial.h"
#include "sound.h"
#include "logosyake.h"

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9 CBullet::m_pTexture[MAX_TEXBULLET] = {};
CExplosion*CBullet::m_pExplosion = NULL;
CScore*CBullet::m_pScore = NULL;
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBullet::CBullet():CScene2D(6)
{
	m_CountState = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CBullet::~CBullet()
{

}

//=============================================================================
// �ǂݍ���
//=============================================================================
HRESULT CBullet::Load(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = NULL;

	pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̐��� [0]
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\game\\ikura.png",
		&m_pTexture[0]);

	// �e�N�X�`���̐��� [1]
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\game\\ami.png",
		&m_pTexture[1]);

	// �e�N�X�`���̐��� [2]
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\game\\mori.png",
		&m_pTexture[2]);

	// �e�N�X�`���̐��� [3]
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\game\\turizao.png",
		&m_pTexture[3]);

	return S_OK;
}

//=============================================================================
// �J��
//=============================================================================
void CBullet::Unload(void)
{
	for (int nCnt = 0; nCnt < MAX_TEXBULLET; nCnt++)
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
HRESULT CBullet::Init(D3DXVECTOR3 pos,D3DXVECTOR3 move, float widtgh, float height, BULLETTYPE type)
{
	CScene2D::Init(pos,widtgh,height);
	m_move = move;
	m_widtgh = widtgh;
	m_height = height;

	SetObjtType(CScene::OBJTYPE_BULLET);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CBullet::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CBullet::Update(void)
{

	D3DXVECTOR3 bulletpos;

	bulletpos = GetPosition();

	bulletpos.x += m_move.x;

	// �ړ���
	m_move.y += 0.1f;

	bulletpos.y += m_move.y;

	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();

	// �|�W�V�����̐ݒ�
	SetPosition(bulletpos, m_rot, m_position, m_fLength);

	// �e�͈̔�
	if (bulletpos.x > SCREEN_WIDTH)
	{
		Uninit();
	}

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
				if (objttpe == CScene::OBJTYPE_ENEMY && m_type == BULLETTYPE_PLAYER)
				{
					// �G�t�F�N�g�̐���
					CEffect::Create(D3DXVECTOR3(bulletpos.x, bulletpos.y, bulletpos.z), D3DXCOLOR(1.0f, 0.0f, 1.0f, 0.5f), 50.0f, 20.0f);

					// �G��pos���擾
					D3DXVECTOR3 enemypos;

					enemypos = pScene->GetPosition();

					// �X�R�A���擾
					CScore *pScore;

					//=========================================================================
					// �v���C���[�̒e�ƓG�̓����蔻��
					//=========================================================================
					if ((enemypos.x) - pScene->GetWidth() < bulletpos.x && (enemypos.x) + pScene->GetWidth() > bulletpos.x &&
						(enemypos.y) - pScene->GetHeigth() < bulletpos.y && (enemypos.y) + pScene->GetHeigth() > bulletpos.y)
					{
						// ���[�h���擾
						CManager::MODE mode;
						mode = CManager::GetMode();

						switch (mode)
						{
							//=====================================================
							// �`���[�g���A��
							//=====================================================
						case CManager::MODE_TUTORIAL:

							// �����̐���
							//CExplosion::Create(D3DXVECTOR3(bulletpos.x, bulletpos.y, 0), 150.0f, 150.0f);

							// �G���擾
							CEnemy *pEnemy;
							pEnemy = CTutorial::GetEnemy();

							CBullet::Uninit();

							if (pEnemy != NULL && pEnemy->state == CEnemy::ENEMYSTATE_NORMAL)
							{
								// �G�ւ̃_���[�W��
								pEnemy->HitEnemy(1);

								// �X�R�A�̎擾
								pScore = CTutorial::GetScore();

								// �X�R�A�̉��Z
								pScore->AddScore(100);

								break;
							}

							break;

							//=====================================================
							// �Q�[��
							//=====================================================
						case CManager::MODE_GAME:

							// �G���擾
							CEnemy *ppEnemy;

							CBullet::Uninit();

							for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
							{
								ppEnemy = CGame::GetEnemy(nCntEnemy);

								if (ppEnemy != NULL && ppEnemy->state == CEnemy::ENEMYSTATE_NORMAL)
								{
									// �G�ւ̃_���[�W��
									ppEnemy->HitEnemy(1);

									// �Q�[���̃X�R�A���擾
									pScore = CGame::GetScore();

									// �X�R�A�̉��Z
									pScore->AddScore(100);

									break;
								}

							}
							break;
							break;
						}
					}
				}

				//=========================================================================
				// �G�̒e�ƃv���C���[�Ƃ̓����蔻��
				//=========================================================================
				if (objttpe == CScene::OBJTYPE_PLAYER && m_type == BULLETTYPE_AMI)
				{
					// �v���C���[��pos���擾
					D3DXVECTOR3 playerpos;

					playerpos = pScene->GetPosition();

					// �G�̒e�ƃv���C���[�Ƃ̓����蔻��
					if ((playerpos.x) - pScene->GetWidth() + 50.0f < bulletpos.x && (playerpos.x) + pScene->GetWidth() - 50.0f > bulletpos.x &&
						(playerpos.y) - pScene->GetHeigth() + 50.0f < bulletpos.y && (playerpos.y) + pScene->GetHeigth() - 50.0f > bulletpos.y)
					{
						// ���[�h���擾
						CManager::MODE mode;
						mode = CManager::GetMode();

						// �T�E���h���擾
						CSound *pSound;
						pSound = CManager::GetSound();

						pSound->PlaySound(pSound->SOUND_LABEL_SE_DAMAGE);

						m_CountState--;

						CPlayer::PLAYERSTATE_DAMAGE;

						CScene2D::SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

						if (m_CountState <= 10)
						{
							CPlayer::PLAYERSTATE_NORMAL;
						}

						switch (mode)
						{
							//=====================================================
							// �`���[�g���A��
							//=====================================================
						case CManager::MODE_TUTORIAL:

							// ���C�t���擾
							CLife *ppLife;
							ppLife = CTutorial::GetLife();

							// ���C�t�����炷
							ppLife->CutLife(1);

							// ���C�t���O�ɂȂ�����
							if (ppLife->m_nLife <= 0)
							{
								// �V���P���S�摜 ����
								CLogosyake::Create(D3DXVECTOR3(bulletpos.x, bulletpos.y, 0), 100.0f, 150.0f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), CLogosyake::SYAKE_DEATH);

								// �v���C���[�̎擾
								CPlayer *pPlayer;
								pPlayer = CTutorial::GetPlayer();

								pPlayer->Uninit();

								// �t�F�[�h���擾
								CFade *pFade;
								pFade = CManager::GetFade();

								if (pFade->GetFade() == CFade::FADE_NONE)
								{
									pFade->SetFade(CManager::MODE_TUTORIAL);
								}
							}
							break;

							//=====================================================
							// �Q�[���ł̏���
							//=====================================================
						case CManager::MODE_GAME:

							// ���C�t���擾
							CLife *pLife = NULL;
							pLife = CGame::GetLife();

							// ���C�t�����炷
							pLife->CutLife(1);

							// ���C�t���O�ɂȂ�����
							if (pLife->m_nLife <= 0)
							{
								// �V���P���S�摜 ����
								CLogosyake::Create(D3DXVECTOR3(bulletpos.x, bulletpos.y, 0), 100.0f, 150.0f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), CLogosyake::SYAKE_DEATH);

								// �v���C���[�̎擾
								CPlayer *pPlayer;
								pPlayer = CGame::GetPlayer();

								pPlayer->Uninit();

								// �t�F�[�h���擾
								CFade *pFade;
								pFade = CManager::GetFade();

								if (pFade->GetFade() == CFade::FADE_NONE)
								{
									CGame::SetState(CGame::STATE_GAMEOVER);
								}
							}
							break;
						}
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
void CBullet::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// �e�̐���
//=============================================================================
CBullet *CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float widtgh, float height, BULLETTYPE type)
{
	CBullet *pBullet;

	pBullet = new CBullet;

	pBullet->Init(pos,move,widtgh,height,type);

	pBullet->m_type = type;

	// ���L�e�N�X�`�������蓖�Ă�
	pBullet->BindTexture(m_pTexture[type]);

	return pBullet;
}