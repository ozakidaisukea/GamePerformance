//=============================================================================
//
// �v���C���[�̏��� [player.cpp]
// Author : Jukiya Hayakawa
//
//=============================================================================
#include "player.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "sound.h"
#include "camera.h"
#include "debugproc.h"
#include "scene3D.h"
#include "meshfield.h"
#include "model.h"
#include "game.h"
#include "object.h"
#include "loadfilefunction.h"
#include "objBillboard.h"
#include "particle.h"

#define MOTION_TXT_NAME "data\\TEXT\\motion.txt"
#define PLAYER_APPEAR (500)
#define PLAYER_SPEED (30.0f)
#define QUATANION_ROT (0.05f)
//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
int g_nNumModel = 2;			//���f���̑���
char g_aFilenameModel[MAX_PLAYER_MODEL][256];	//

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPD3DXMESH			CPlayer::m_pMesh[MAX_PLAYER_MODEL] = {};
LPD3DXBUFFER		CPlayer::m_pBuffMat[MAX_PLAYER_MODEL] = {};
DWORD				CPlayer::m_nNumMat[MAX_PLAYER_MODEL] = {};
LPDIRECT3DTEXTURE9	CPlayer::m_pTexture = NULL;
//=============================================================================
// �v���C���[�̃R���X�g���N�^
//=============================================================================
CPlayer::CPlayer() : CScene(1,OBJTYPE_NONE)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�ʒu�̏����l
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ߋ��̈ʒu�̏����l
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�����̏����l
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�ړ��ʏ����l
	m_bJump = false;								//�W�����v���Ă��Ȃ����
	m_motionType = MOTION_NEUTRAL;					//���[�V������������
	m_nCountFrame = 0;								//�t���[������������
	m_scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	for (int nCntModel = 0; nCntModel < MAX_PLAYER_MODEL; nCntModel++)
	{//���f���̐������J��Ԃ�
		m_apModel[nCntModel] = NULL;
	}
	D3DXMatrixIdentity(&m_mtxRot);					// ���[���h�}�g���b�N�X�̏�����
	D3DXQuaternionIdentity(&m_quat);				//�N�I�[�^�j�I����������
	m_vecAxis = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�x�N�g����������
	m_fValueRot = 0.0f;								//������������
	m_state = PLAYER_STATE_START;					//�v���C���[���n�߂��Ԃɂ���
	m_bHitFlag = false;
	m_nAppearTimer = 0;

}
//=============================================================================
// �v���C���[�̃f�X�g���N�^
//=============================================================================
CPlayer::~CPlayer()
{

}

//=============================================================================
// �I�u�W�F�N�g�̃e�N�X�`���ǂݍ���
//=============================================================================
HRESULT CPlayer::Load(void)
{
	//�����_�����O�̎擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\earth000.jpg",
		&m_pTexture);

	return S_OK;
}

//=============================================================================
// �I�u�W�F�N�g�̃e�N�X�`���j��
//=============================================================================
void CPlayer::Unload(void)
{
	for (int nCntMesh = 0; nCntMesh < MAX_PLAYER_MODEL; nCntMesh++)
	{//���f���̐������J��Ԃ�
		// ���b�V���̊J��
		if (m_pMesh[nCntMesh] != NULL)
		{
			m_pMesh[nCntMesh]->Release();
			m_pMesh[nCntMesh] = NULL;
		}
	}

	for (int nCntMat = 0; nCntMat < MAX_PLAYER_MODEL; nCntMat++)
	{//���f���̐������J��Ԃ�
		// �}�e���A���̊J��
		if (m_pBuffMat[nCntMat] != NULL)
		{
			m_pBuffMat[nCntMat]->Release();
			m_pBuffMat[nCntMat] = NULL;
		}
	}
}

//=============================================================================
//�v���C���[�̐���
//=============================================================================
CPlayer *CPlayer::Create(D3DXVECTOR3 pos)
{
	CPlayer *pPlayer = NULL;					//�v���C���[�̃|�C���^
	if (pPlayer == NULL)
	{
		pPlayer = new CPlayer;					//�V�[���̓��I�m��
		pPlayer->Init();						//����������
		pPlayer->m_pos = pos;
	}
	return pPlayer;					//�l��Ԃ�
}

//=============================================================================
// �v���C���[�̏���������
//=============================================================================
HRESULT CPlayer::Init(void)
{
	SetObjType(CScene::OBJTYPE_PLAYER);
	//���[�V��������ǂݍ���
	LoadMotion();
	m_scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_VtxMax = D3DXVECTOR3(30.0f*m_scale.x, 30.0f*m_scale.y, 30.0f*m_scale.z);	//���_���W�̍ő�l������
	m_VtxMin = D3DXVECTOR3(-30.0f*m_scale.x, -30.0f*m_scale.y, -30.0f*m_scale.z);	//���_���W�̍ŏ��l������

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�ʒu�̏�����
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�����̏�����
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�ړ��ʏ����l
	m_bJump = false;								//�W�����v���Ă��Ȃ����
	m_nKey = 0;										//���݂̃L�[��������
	m_nNumKey = 2;									//�L�[�̑�����������
	m_nCountFrame = 0;								//�J�E���g�t���[����������
	return S_OK;
}

//=============================================================================
// �v���C���[�̏I������
//=============================================================================
void CPlayer::Uninit(void)
{
	for (int nCntModel = 0 ; nCntModel < MAX_PLAYER_MODEL; nCntModel++)
	{//���f���̐������J��Ԃ�
		if (m_apModel[nCntModel] != NULL)
		{
			//�I������
			m_apModel[nCntModel]->Uninit();
			delete m_apModel[nCntModel];
			m_apModel[nCntModel] = NULL;
		}
	}

	Release();
}

//=============================================================================
// �v���C���[�̍X�V����
//=============================================================================
void CPlayer::Update(void)
{
	//���݂̈ʒu�����ߋ��̈ʒu�ɑ��
	m_posOld = m_pos;

	//���݂̃��[�V�������ߋ��̃��[�V�������ɑ��
	m_OldMotion = m_motionType;

	//�ړ�����
	Move();

	//�����蔻�菈��
	Collision();

	//���[�V�����̍X�V����
	//UpdateMotion();

	//�L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetKeyboard();

#ifdef _DEBUG
	CDebugProc::Print(1, "�v���C���[�̈ʒu  : x[%.1f],y[%.1f],z[%.1f]\n", m_pos.x, m_pos.y, m_pos.z);
	CDebugProc::Print(1, "�v���C���[�̈ړ���  : %f",m_move.y);

#endif
}

//=============================================================================
// �v���C���[�̕`�揈��
//=============================================================================
void CPlayer::Draw(void)
{
	//�����_�����O�̎擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans,mtxScale;					//�v�Z�p�}�g���b�N�X

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//
	D3DXQuaternionRotationAxis(&m_quat, &m_vecAxis, m_fValueRot);

	//
	D3DXMatrixRotationQuaternion(&mtxRot, &m_quat);

	// ��]�𔽉f
	D3DXMatrixMultiply(&mtxRot, &m_mtxRot, &mtxRot);

	//�ۑ�
	m_mtxRot = mtxRot;

	//
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &m_mtxRot);

	//// ��]�𔽉f
	//D3DXMatrixRotationYawPitchRoll(&mtxRot,
	//	m_rot.y, m_rot.x, m_rot.z);

	//D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �傫���̔��f
	D3DXMatrixScaling(&mtxScale,
		m_scale.x, m_scale.y, m_scale.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScale);


	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	D3DXMATRIX	mtxShadow;		//�V���h�E�}�g���b�N�X
	D3DXPLANE	planeField;		//���ʏ��
	D3DXVECTOR4 vecLight;		//���C�g���
	D3DXVECTOR3	pos, normal;	//�ʒu�A�@��

								//���Z�����̐ݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP,
		D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND,
		D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND,
		D3DBLEND_ONE);

	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//�V���h�E�}�g���b�N�X��������
	D3DXMatrixIdentity(&mtxShadow);

	//���C�g�̐ݒ�
	vecLight = D3DXVECTOR4(0.25f, 0.87f, -0.44f, 0.0f);

	//�ʒu�̐ݒ�
	pos = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//�@���̐ݒ�
	normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//�ʒu�Ɩ@�����畽�ʂ��쐬����
	D3DXPlaneFromPointNormal(&planeField, &pos, &normal);

	//���ʂ̎ˉe
	D3DXMatrixShadow(&mtxShadow, &vecLight, &planeField);

	//���[���h�}�g���b�N�X�Ɗ|�����킹��
	D3DXMatrixMultiply(&mtxShadow, &m_mtxWorld, &mtxShadow);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxShadow);

	for (int nCntModel = 0; nCntModel < MAX_PLAYER_MODEL; nCntModel++)
	{//���f���̐������J��Ԃ�
	 //�e�N�X�`������
		pDevice->SetTexture(0, NULL);
		// ���f��(�p�[�c)�̕`��
		m_pMesh[nCntModel]->DrawSubset(0);
		//�`�揈��
		//m_apModel[nCntModel]->Draw();
	}

	//���̐ݒ�ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP,
		D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND,
		D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND,
		D3DBLEND_INVSRCALPHA);
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	for (int nCntModel = 0; nCntModel < MAX_PLAYER_MODEL; nCntModel++)
	{
		//���f���̕`��
		m_apModel[nCntModel]->Draw();
	}
}

//=============================================================================
// �v���C���[�̃��[�V�����X�V����
//=============================================================================
void CPlayer::UpdateMotion(void)
{
	KEY *pKey, *pKeyNext;		// �L�[�̏��
	float fRateMotion;			// ���Βl
	float fDiffMotion;			// ����
	D3DXVECTOR3 pos;			// �ʒu
	D3DXVECTOR3 rot;			// ����

	/*if (m_apMotionInfo[m_motionType].nNumKey <= m_nKey)
	{
		m_nKey = 0;
		m_nCountFrame = 0;
	}*/

	if (m_OldMotion != m_motionType)
	{//�O��̃��[�V�������Ⴄ�ꍇ
		m_nKey = 0;			//���݂̃L�[��������
		m_nCountFrame = 0;	//�J�E���g�t���[����������
	}
	for (int nCntModel = 0; nCntModel < g_nNumModel; nCntModel++)
	{//���f���̐������J��Ԃ�
		if (m_apModel[nCntModel] != NULL)
		{//���f��������ꍇ
			pKey = &m_apMotionInfo[m_motionType].aKeyInfo[m_nKey].aKey[nCntModel];
			pKeyNext = &m_apMotionInfo[m_motionType].aKeyInfo[(m_nKey + 1) % /*2*/m_apMotionInfo[m_motionType].nNumKey].aKey[nCntModel];

			//�ʒu���WX
			fRateMotion = (float)(m_nCountFrame) / (float)m_apMotionInfo[m_motionType].aKeyInfo[m_nKey].nFrame;	// ���Βl�̎擾
			fDiffMotion = pKeyNext->fPosX - pKey->fPosX;														// �����̎擾
			pos.x = m_apModel[nCntModel]->GetPos().x +  pKey->fPosX + (fDiffMotion * fRateMotion);

			//�ʒu���WY
			fDiffMotion = pKeyNext->fPosY - pKey->fPosY;								// �����̎擾
			pos.y = m_apModel[nCntModel]->GetPos().y + pKey->fPosY + (fDiffMotion * fRateMotion);

			//�ʒu���WZ
			fDiffMotion = pKeyNext->fPosZ - pKey->fPosZ;								// �����̎擾
			pos.z = m_apModel[nCntModel]->GetPos().z + pKey->fPosZ + (fDiffMotion * fRateMotion);

			//�������WX
			fDiffMotion = pKeyNext->fRotX - pKey->fRotX;								// �����̎擾
			rot.x = pKey->fRotX + (fDiffMotion * fRateMotion);

			//�������WY
			fDiffMotion = pKeyNext->fRotY - pKey->fRotY;								// �����̎擾
			rot.y = pKey->fRotY + (fDiffMotion * fRateMotion);

			//�������WZ
			fDiffMotion = pKeyNext->fRotZ - pKey->fRotZ;								// �����̎擾
			rot.z = pKey->fRotZ + (fDiffMotion * fRateMotion);

			//�ʒu�̐ݒu����
			//m_apModel[nCntModel]->SetPos(pos);
			//�����̐ݒu����
			m_apModel[nCntModel]->SetRot(rot);

		}
	}

		if (m_nKey <= m_apMotionInfo[m_motionType].nNumKey - 1)
		{//���݂̃L�[���Ώۂ̃L�[�̑�����菬�����ꍇ�J�E���g�t���[�������Z
			m_nCountFrame++;
		}
		if (m_nCountFrame >= m_apMotionInfo[m_motionType].aKeyInfo[m_nKey].nFrame)
		{//���݂̃t���[�������Ώۂ̃L�[�t���[�����ȏ�̏ꍇ
			//m_nKey = (m_nKey + (m_apMotionInfo[m_motionType].nNumKey - 1)) % m_apMotionInfo[m_motionType].nNumKey;
			//���݂̃L�[�̐؂�ւ�
			m_nKey = (m_nKey + 1) % m_apMotionInfo[m_motionType].nNumKey;
			if (m_nKey == m_apMotionInfo[m_motionType].nNumKey - 1 && m_apMotionInfo[m_motionType].bLoop == false)
			{//���݂̃L�[���Ώۂ̃L�[�����ɒB�������[�v���Ȃ��ꍇ

				if (m_motionType == MOTION_JUMP && m_bJump == true)
				{//
					//m_nKey = m_apMotionInfo[m_motionType].nNumKey - 1;
				}

			}
			//�J�E���g�t���[����������
			m_nCountFrame = 0;
		}
#if 0
	switch (m_apMotionInfo[m_motionType].bLoop)
	{
	case true:
		m_nCountFrame++;	//�J�E���g�t���[���̉��Z

		if (m_nCountFrame >= m_apMotionInfo[m_motionType].aKeyInfo[m_nKey].nFrame)
		{//���݂̃t���[�������Ώۂ̃L�[�t���[�����ȏ�̏ꍇ
			if (m_nKey == m_apMotionInfo[m_motionType].nNumKey - 1)
			{//���݂̃L�[���Ώۂ̃L�[�������ɒB�����ꍇ�O�Ԗڂ̃L�[�ԍ��ɖ߂�

				m_nKey = 0;
				//m_nKey = m_apMotionInfo[m_motionType].nNumKey - 1;
			}
			else
			{//�L�[�̉��Z
				m_nKey++;
			}
			//�J�E���g�t���[��������
			m_nCountFrame = 0;
		}
		break;
	case false:
		if (m_nKey <= m_apMotionInfo[m_motionType].nNumKey - 1)
		{//���݂̃L�[���Ώۂ̃L�[�̑�����菬�����ꍇ�J�E���g�t���[�������Z
			m_nCountFrame++;
		}
		if (m_nCountFrame >= m_apMotionInfo[m_motionType].aKeyInfo[m_nKey].nFrame)
		{//���݂̃t���[�������Ώۂ̃L�[�t���[�����ȏ�̏ꍇ
			if (m_apMotionInfo[m_motionType].nNumKey - 1 > m_nKey)
			{//���݂̃L�[���Ώۂ̃L�[�̑�����菬�����ꍇ�L�[�����Z
				m_nKey++;

				m_nCountFrame = 0;
			}
			else
			{
				//�R�}���h�̎擾
				CCommand *pCommand;
				pCommand = CGame::GetCommad();
				//�j���[�g�����ɐ؂�ւ�
				m_motionType = MOTION_NEUTRAL;
				//�R�}���h�����s���Ă��Ȃ���Ԃɂ���
				pCommand->SetCommandState(pCommand->COMMAND_NONE);
				m_nCountFrame = 0;

			}
		}
		break;
	}
#endif
#ifdef _DEBUG
	for (int nCntRot = 0; nCntRot < MAX_PLAYER_MODEL; nCntRot++)
	{//�p�[�c�̐������J��Ԃ�
		//�ʒu�ƌ�����\��
		//CDebugProc::Print(1, "Pos[%d]  : x[%.1f],y[%.1f],z[%.1f]\n", nCntRot, m_apModel[nCntRot]->GetPos().x, m_apModel[nCntRot]->GetPos().y, m_apModel[nCntRot]->GetPos().z);
		//CDebugProc::Print(1, "Rot[%d]  : x[%.1f],y[%.1f],z[%.1f]\n", nCntRot, m_apModel[nCntRot]->GetRot().x, m_apModel[nCntRot]->GetRot().y, m_apModel[nCntRot]->GetRot().z);

	}
	CDebugProc::Print(1, "�v���C���[�ړ�[W,A,S,D]\n");
	CDebugProc::Print(1, "Key[%d / %d]\n",m_nKey,m_apMotionInfo[m_motionType].nNumKey);
	CDebugProc::Print(1, "Frame[%d / %d]\n",m_nCountFrame, m_apMotionInfo[m_motionType].aKeyInfo[m_nKey].nFrame);
	CDebugProc::Print(1, "���[�V����[%d]\n", m_motionType);
#endif
}
//=============================================================================
// �v���C���[�̈ړ�����
//=============================================================================
void CPlayer::Move(void)
{
	//�L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetKeyboard();

	//�W���C�p�b�h�̎擾
	CInputJoypad *pInputJoypad;
	pInputJoypad = CManager::GetJoypad();

	//�J�����̎擾
	CCamera *pCamera;
	pCamera = CManager::GetCamera();
	//�J�����̌����擾
	D3DXVECTOR3 cameraRot = pCamera->GetRot();

	//�T�E���h�̎擾
	CSound *pSound;
	pSound = CManager::GetSound();

	//�O�̃t���[���œ������Ă�����
	if (m_bHitFlag == true)
	{
		//CParticle::Create(m_pos, m_rot, 50, CParticle::PARTICLE_TYPE1);
		pSound->PlaySound(CSound::SOUND_LABEL_SE_DAMAGE);

		m_nAppearTimer = PLAYER_APPEAR;
		m_pos.z -= 100.0f;
		m_bHitFlag = false;
	}

	if (m_state == PLAYER_STATE_START)
	{//�v���C���[���������Ԃ̏ꍇ
		//��ɑO�i
		m_vecAxis = D3DXVECTOR3(1.0f, 0.0f, 0.0f);			//���̐ݒ�
		m_fValueRot = D3DX_PI * QUATANION_ROT;				//��]��
		float fAngle = (2 * D3DX_PI * PLAYER_SPEED);		//�~��
		m_pos.z += (m_fValueRot / (2 * D3DX_PI)) * fAngle;	//�ʒu���Z

		//if (pInputKeyboard->GetPress(DIK_W) == true)
		//{
		//	m_vecAxis = D3DXVECTOR3(1.0f, 0.0f, 0.0f);			//���̐ݒ�
		//	m_fValueRot = D3DX_PI * QUATANION_ROT;				//��]��
		//	float fAngle = (2 * D3DX_PI * PLAYER_SPEED);		//�~��
		//	m_pos.z += (m_fValueRot / (2 * D3DX_PI)) * fAngle;	//�ʒu���Z
		//}
		if (pInputKeyboard->GetPress(DIK_A) == true
			||pInputJoypad->GetPress(CInputJoypad::DIJS_BUTTON_LSTICK_LEFT) == true)
		{//���ړ�
			m_vecAxis = D3DXVECTOR3(0.0f, 0.0f, 1.0f);			//���̐ݒ�
			m_fValueRot = D3DX_PI * QUATANION_ROT;				//��]��
			float fAngle = (2 * D3DX_PI * PLAYER_SPEED);		//�~��
			m_pos.x -= (m_fValueRot / (2 * D3DX_PI)) * fAngle;	//�ʒu���Z
		}
		else if (pInputKeyboard->GetPress(DIK_D) == true
			|| pInputJoypad->GetPress(CInputJoypad::DIJS_BUTTON_LSTICK_RIGHT) == true)
		{//�E�ړ�
			m_vecAxis = D3DXVECTOR3(0.0f, 0.0f, -1.0f);			//���̐ݒ�
			m_fValueRot = D3DX_PI * QUATANION_ROT;				//��]��
			float fAngle = (2 * D3DX_PI * PLAYER_SPEED);		//�~��
			m_pos.x += (m_fValueRot / (2 * D3DX_PI)) * fAngle;	//�ʒu���Z
		}

		//if (pInputKeyboard->GetTrigger(DIK_J) == true
		//	|| pInputJoypad->GetTrigger(CInputJoypad::DIJS_BUTTON_LB) == true)
		//{//�v���C���[�k��
		//	if (m_scale.x > 0.5f && m_scale.y > 0.5f && m_scale.z > 0.5f)
		//	{//�傫����0.5���傫���ꍇ
		//		pSound->PlaySound(CSound::SOUND_LABEL_SE_SYUKUSYOU);

		//		m_scale = D3DXVECTOR3(m_scale.x - 0.5f, m_scale.y - 0.5f, m_scale.z - 0.5f);
		//	}
		//}
		//if (pInputKeyboard->GetTrigger(DIK_K) == true
		//	|| pInputJoypad->GetTrigger(CInputJoypad::DIJS_BUTTON_RB) == true)
		//{//�v���C���[�g��
		//	if (m_scale.x < 2.0f && m_scale.y < 2.0f && m_scale.z < 2.0f)
		//	{//�傫����2.0��菬�����ꍇ
		//		pSound->PlaySound(CSound::SOUND_LABEL_SE_KAKUDAI);

		//		m_scale = D3DXVECTOR3(m_scale.x + 0.5f, m_scale.y + 0.5f, m_scale.z + 0.5f);
		//	}
		//}
	}
	CDebugProc::Print(1, "�傫�� x:%f y:%f z:%f\n", m_scale.x, m_scale.y, m_scale.z);

	if (m_bJump == false)
	{//�W�����v���Ă��Ȃ��ꍇ
		//�ړ��ʏ�����
		m_move.y = 0.0f;
		if (pInputKeyboard->GetTrigger(DIK_SPACE) == true
			|| pInputJoypad->GetPress(CInputJoypad::DIJS_BUTTON_A) == true)
		{//Space�L�[�������ꂽ�ꍇ
			pSound->PlaySound(CSound::SOUND_LABEL_SE_JUMP);

			//�W�����v���[�V�����ɐ؂�ւ�
			m_motionType = MOTION_JUMP;
			//���݂̃L�[��������
			m_nKey = 0;
			//�ړ��ʂ����Z
			m_move.y -= (cosf(D3DX_PI * 1.0f) * 8.0f);				//�W�����v���Ă����Ԃɂ���
			m_bJump = true;
		}
	}

	if (m_pos.x <= -75.0f)
	{
		m_pos.x = -75.0f;
	}
	else if (m_pos.x >= 80.0f)
	{
		m_pos.x = 80.0f;
	}
	if (m_pos.z >= 5900.0f)
	{//�v���C���[���S�[���n�_�ɓ��B�����ꍇ
		m_pos.z = 5900.0f;			//�ʒu�Œ�
		m_state = PLAYER_STATE_GOAL;//�S�[��������Ԃɂ���
		m_fValueRot = 0.0f;			//������
	}
	//�d��
	m_move.y -= cosf(D3DX_PI * 0) * 0.5f;

	//�ړ����Z����
	m_pos.y += m_move.y;

}

//=============================================================================
// �v���C���[�̓����蔻�菈��
//=============================================================================
void CPlayer::Collision(void)
{
	// �z�u���ƒn�ʂւ̃|�C���^�擾����
	CScene *pScene = NULL;               // �I�u�W�F�N�g�̃|�C���^
	CScene *pSceneNext = NULL;           // ���̃I�u�W�F�N�g�̃|�C���^
	CObject *pObject = NULL;             // �z�u���̃|�C���^
	CMeshField *pMeshField = NULL;		// ���b�V���t�B�[���h�̃|�C���^
	CItemBillboard *pItemBillboard = NULL;	//�r���{�[�h�̃|�C���^

	for (int nCntPriority = 0; nCntPriority < NUM_PRIORITY; nCntPriority++)
	{// �D�揇�ʂ̐������J��Ԃ�
		pScene = CScene::GetTop(nCntPriority);
		while (pScene != NULL)
		{// NULL�ɂȂ�܂ŌJ��Ԃ�
			pSceneNext = pScene->GetNext();
			if (pScene->GetObjType() == OBJTYPE_OBJECT)
			{// �z�u���̏ꍇ
					pObject = (CObject*)pScene;
				if (pObject != NULL)
				{// �z�u�����擾�ł���
					if (m_nAppearTimer <= 0)
					{
						if (pObject->Collision(&m_pos, &m_posOld, &m_move,
							&(D3DXVECTOR3(m_VtxMin.x * m_scale.x, m_VtxMin.y * m_scale.y, m_VtxMin.z * m_scale.z)),
							&(D3DXVECTOR3(m_VtxMax.x * m_scale.x, m_VtxMax.y * m_scale.y, m_VtxMax.z * m_scale.z)),
							&m_bHitFlag) == true)
						{// �z�u���̏�ɏ���Ă���
							m_bJump = false;
						}
					}
					else
					{
						m_nAppearTimer--;
					}
				}
			}
			else if (pScene->GetObjType() == OBJTYPE_MESHFIELD)
			{//���b�V���t�B�[���h�̏ꍇ
				//pMeshField = (CMeshField*)pScene;

				////�t�B�[���h�̈ʒu���
				//float fMeshHeight = pMeshField->GetHeight(m_pos);

				//if (m_bJump == false)
				//{//�W�����v���Ă��Ȃ��ꍇ
				// 	if (m_pos.y <= fMeshHeight + (10.0f * m_scale.y))
				//	{//�v���C���[�����b�V���t�B�[���h���Ⴂ�ʒu�̏ꍇ
				//		m_move.y = 0.0f;								//y���̈ړ��ʂ�0�ɂ���
				//		m_pos.y = fMeshHeight + (10.0f * m_scale.y);							//���b�V���t�B�[���h�Ɠ��������ɂ���
				//		m_bJump = false;								//�W�����v���Ă��Ȃ���Ԃɂ���
				//	}
				//}
				//else
				//{//�W�����v���Ă���ꍇ
				//	if (m_pos.y <= fMeshHeight + (10.0f * m_scale.y))
				//	{// �v���C���[��y���W���n�ʂ����Ⴂ�Ƃ�
				//	 // �W�����v���Ă��Ȃ���Ԃɂ���
				//		m_bJump = false;
				//	}
				//}
			}
			else if (pScene->GetObjType() == OBJTYPE_ITEM_BILLBOARD)
			{
				pItemBillboard = (CItemBillboard*)pScene;
				pItemBillboard->Collision(m_pos);

			}
			// ���̃I�u�W�F�N�g�ւ̃|�C���^���擾
			pScene = pSceneNext;
		}
	}
	if (m_pos.y <= 0.0f + (10.0f * m_scale.y))
	{
		m_move.y = 0.0f;								//y���̈ړ��ʂ�0�ɂ���
		m_pos.y = 0.0f + (10.0f * m_scale.y);			//���b�V���t�B�[���h�Ɠ��������ɂ���
		m_bJump = false;								//�W�����v���Ă��Ȃ���Ԃɂ���
	}
}

//=============================================================================
// �v���C���[�̃��[�V�����ǂݍ���
//=============================================================================
void CPlayer::LoadMotion(void)
{
	//�����_�����O�̎擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();

	FILE *pFile;	//�t�@�C���̃|�C���^

	pFile = fopen(MOTION_TXT_NAME, "r");	//�e�L�X�g�ǂݍ���
	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ
		char *pStrCur;						//������̐擪�ւ̃|�C���^
		char aLine[256];					//������̓ǂݍ��ݗp
		char aStr[256];						//�����񔲂��o���p
		int nIdx;

		while (1)
		{//���f���t�@�C����ǂݍ��ނ܂ŌJ��Ԃ�
			pStrCur = CLoadFileFunction::ReadLine(pFile, &aLine[0]);
			int nNum = CLoadFileFunction::PopString(pStrCur, &aStr[0]);
			strcpy(&aStr[0], pStrCur);
			aStr[nNum - 1] = '\0';
			if (memcmp(&aStr[0], TEXT_SCRIPT, strlen(TEXT_SCRIPT)) == 0)
			{
				//************************************************************************
				// ���f���̑���&�t�@�C���̓ǂݍ���
				//************************************************************************
				while (1)
				{//���f���t�@�C����ǂݍ��ނ܂ŌJ��Ԃ�
					pStrCur = CLoadFileFunction::ReadLine(pFile, &aLine[0]);
					strcpy(&aStr[0], pStrCur);				//����������o��

					if (memcmp(&aStr[0], TEXT_NUM_MODEL, strlen(TEXT_NUM_MODEL)) == 0)
					{//�e�L�X�g�����f���̑����������s�̏ꍇ
						pStrCur += strlen(TEXT_NUM_MODEL);	//���o��
						strcpy(&aStr[0], pStrCur);

						g_nNumModel = atoi(&aStr[0]);	//���f���̑����ɑ��


						for (int nCntModel = 0; nCntModel < g_nNumModel; nCntModel++)
						{
							while (1)
							{
								pStrCur = CLoadFileFunction::ReadLine(pFile, &aLine[0]);
								strcpy(&aStr[0], pStrCur);				//����������o��
								if (memcmp(&aStr[0], TEXT_FILENAME_MODEL, strlen(TEXT_FILENAME_MODEL)) == 0)
								{//�e�L�X�g�����f���̖��O�������s�̏ꍇ
									pStrCur += strlen(TEXT_FILENAME_MODEL);					//���o��
									strcpy(&aStr[0], pStrCur);
									int nNum = CLoadFileFunction::PopString(pStrCur, &aStr[0]);
									strcpy(&aStr[0], pStrCur);
									aStr[nNum - 1] = '\0';

									strcpy(&g_aFilenameModel[nCntModel][0], aStr);	//���f���̖��O���擾

																					// X�t�@�C���̓ǂݍ���
									D3DXLoadMeshFromX(&g_aFilenameModel[nCntModel][0],
										D3DXMESH_SYSTEMMEM,
										pDevice,
										NULL,
										&m_pBuffMat[nCntModel],
										NULL,
										&m_nNumMat[nCntModel],
										&m_pMesh[nCntModel]);

									break;
								}
							}
						}
						break;		//�����o��
					}
				}

				while (1)
				{//���f���̏���ǂݎ��܂ŌJ��Ԃ�
					pStrCur = CLoadFileFunction::ReadLine(pFile, &aLine[0]);
					strcpy(&aStr[0], pStrCur);				//����������o��

					//************************************************************************
					// ���f���̏��ǂݍ���
					//************************************************************************
					if (memcmp(&aStr[0], TEXT_CHARASET, strlen(TEXT_CHARASET)) == 0)
					{//�e�L�X�g�����f���ݒu�������s�̏ꍇ
						while (1)
						{
							pStrCur = CLoadFileFunction::ReadLine(pFile, pStrCur);
							strcpy(&aStr[0], pStrCur);				//����������o��
							if (memcmp(&aStr[0], TEXT_NUM_PARTS, strlen(TEXT_NUM_PARTS)) == 0)
							{
								pStrCur += strlen(TEXT_NUM_PARTS);
								pStrCur = CLoadFileFunction::GetLineTop(pStrCur);
								strcpy(&aStr[0], pStrCur);			//����������o��
								m_nNumParts = atoi(&aStr[0]);

								for (int nCntParts = 0; nCntParts < m_nNumParts; nCntParts++)
								{
									pStrCur = CLoadFileFunction::ReadLine(pFile, &aLine[0]);
									strcpy(&aStr[0], pStrCur);				//����������o��

									while (1)
									{
										if (memcmp(&aStr[0], TEXT_PARTSSET, strlen(TEXT_PARTSSET)) == 0)
										{//�p�[�c���̐ݒu�������s�̏ꍇ
											while (1)
											{
												pStrCur = CLoadFileFunction::ReadLine(pFile, &aLine[0]);
												strcpy(&aStr[0], pStrCur);				//����������o��

												if (memcmp(&aStr[0], TEXT_INDEX, strlen(TEXT_INDEX)) == 0)
												{//�e�L�X�g���C���f�b�N�X�������s�̏ꍇ
													pStrCur += strlen(TEXT_INDEX);
													pStrCur = CLoadFileFunction::GetLineTop(pStrCur);
													strcpy(&aStr[0], pStrCur);			//����������o��
													nIdx = atoi(&aStr[0]);
													m_nIndexParent[nIdx];
												}
												else if (memcmp(&aStr[0], TEXT_PARENT, strlen(TEXT_PARENT)) == 0)
												{//�e�L�X�g���e�q�֌W�������s�̏ꍇ
													pStrCur += strlen(TEXT_PARENT);
													pStrCur = CLoadFileFunction::GetLineTop(pStrCur);
													strcpy(&aStr[0], pStrCur);			//����������o��
													m_nIndexParent[nIdx] = atoi(&aStr[0]);
												}
												else if (memcmp(&aStr[0], TEXT_POS, strlen(TEXT_POS)) == 0)
												{//�e�L�X�g���ʒu�������s�̏ꍇ
													int nWord = 0;
													pStrCur += strlen(TEXT_POS);
													//nWord = PopString(pStrCur, &aStr[0]);
													//pStrCur += nWord;
													strcpy(&aStr[0], pStrCur);			//����������o��
													m_aKeyOffset[nCntParts].fPosX = (float)atof(&aStr[0]);

													nWord = CLoadFileFunction::PopString(pStrCur, &aStr[0]);
													pStrCur += nWord;
													strcpy(&aStr[0], pStrCur);			//����������o��
													m_aKeyOffset[nCntParts].fPosY = (float)atof(&aStr[0]);

													nWord = CLoadFileFunction::PopString(pStrCur, &aStr[0]);
													pStrCur += nWord;
													strcpy(&aStr[0], pStrCur);			//����������o��
													m_aKeyOffset[nCntParts].fPosZ = (float)atof(&aStr[0]);
												}
												else if (memcmp(&aStr[0], TEXT_ROT, strlen(TEXT_ROT)) == 0)
												{//�e�L�X�g���ʒu�������s�̏ꍇ
													int nWord = 0;
													pStrCur += strlen(TEXT_ROT);
													//nWord = PopString(pStrCur, &aStr[0]);
													//pStrCur += nWord;
													strcpy(&aStr[0], pStrCur);			//����������o��
													m_aKeyOffset[nCntParts].fRotX = (float)atof(&aStr[0]);

													nWord = CLoadFileFunction::PopString(pStrCur, &aStr[0]);
													pStrCur += nWord;
													strcpy(&aStr[0], pStrCur);			//����������o��
													m_aKeyOffset[nCntParts].fRotY = (float)atof(&aStr[0]);

													nWord = CLoadFileFunction::PopString(pStrCur, &aStr[0]);
													pStrCur += nWord;
													strcpy(&aStr[0], pStrCur);			//����������o��
													m_aKeyOffset[nCntParts].fRotZ = (float)atof(&aStr[0]);
												}
												else if (memcmp(&aStr[0], TEXT_END_PARTSSET, strlen(TEXT_END_PARTSSET)) == 0)
												{//�e�L�X�g���p�[�c�̐ݒu�I���������s�̏ꍇ
													if (m_nIndexParent[nCntParts] == -1)
													{
														m_apModel[nIdx] = CModel::Create(D3DXVECTOR3(m_pos.x + m_aKeyOffset[nIdx].fPosX, m_pos.y + m_aKeyOffset[nIdx].fPosY, m_pos.z + m_aKeyOffset[nIdx].fPosZ));
														m_apModel[nIdx]->BindX(m_pMesh[nIdx], m_pBuffMat[nIdx], m_nNumMat[nIdx]);
														m_apModel[nIdx]->BindTexture(m_pTexture);
														m_apModel[nIdx]->SetParent(NULL);
													}
													else if (m_nIndexParent[nCntParts] > -1)
													{
														m_apModel[nIdx] = CModel::Create(D3DXVECTOR3(m_pos.x + m_aKeyOffset[nIdx].fPosX, m_pos.y + m_aKeyOffset[nIdx].fPosY, m_pos.z + m_aKeyOffset[nIdx].fPosZ));
														m_apModel[nIdx]->BindX(m_pMesh[nIdx], m_pBuffMat[nIdx], m_nNumMat[nIdx]);
														m_apModel[nIdx]->SetParent(m_apModel[m_nIndexParent[nIdx]]);
													}

													break;
												}
											}
											break;
										}
									}
								}
							}
							else if (memcmp(&aStr[0], TEXT_END_CHARASET, strlen(TEXT_END_CHARASET)) == 0)
							{//�e�L�X�g�����f���̐ݒu�I���������s�̏ꍇ
								break;
							}
						}
						break;
					}
				}

				//************************************************************************
				// ���[�V�����̓ǂݍ���
				//************************************************************************
				for (int nCntMotion = 0; nCntMotion < MAX_MOTION; nCntMotion++)
				{
					pStrCur = CLoadFileFunction::ReadLine(pFile, &aLine[0]);
					strcpy(&aStr[0], pStrCur);				//����������o��
					if (memcmp(&aStr[0], TEXT_MOTIONSET, strlen(TEXT_MOTIONSET)) == 0)
					{//���[�V�����̐ݒu�������s�̏ꍇ
						while (1)
						{
							pStrCur = CLoadFileFunction::ReadLine(pFile, pStrCur);				//�s�̓ǂݍ���
							strcpy(&aStr[0], pStrCur);						//����������o��
							if (memcmp(&aStr[0], TEXT_LOOP, strlen(TEXT_LOOP)) == 0)
							{//���[�v�������s�̏ꍇ
								pStrCur += strlen(TEXT_LOOP);				//���o��
								pStrCur = CLoadFileFunction::GetLineTop(pStrCur);				//�󔒏���
								int nNum = CLoadFileFunction::PopString(pStrCur, &aStr[0]);	//�������̃J�E���g
								strcpy(&aStr[0], pStrCur);
								aStr[nNum - 1] = '\0';

								if (atoi(&aStr[0]) == 0)
								{//�O���L������Ă����ꍇ���[�v���Ȃ�
									m_apMotionInfo[nCntMotion].bLoop = false;
								}
								else if (atoi(&aStr[0]) == 1)
								{//�P���L������Ă����ꍇ���[�v����
									m_apMotionInfo[nCntMotion].bLoop = true;
								}
							}
							else if (memcmp(&aStr[0], TEXT_NUM_KEY, strlen(TEXT_NUM_KEY)) == 0)
							{//�L�[�̑����������s�̏ꍇ
								pStrCur += strlen(TEXT_NUM_KEY);			//���o��
								pStrCur = CLoadFileFunction::GetLineTop(pStrCur);				//�󔒏���
								strcpy(&aStr[0], pStrCur);					//����������o��

								m_apMotionInfo[nCntMotion].nNumKey = atoi(&aStr[0]);//�L�[�̑�������

								for (int nCntKey = 0; nCntKey < m_apMotionInfo[nCntMotion].nNumKey; nCntKey++)
								{//�L�[�̑������J��Ԃ�
									while (1)
									{
										pStrCur = CLoadFileFunction::ReadLine(pFile, &aLine[0]);	//�s�̓ǂݍ���
										strcpy(&aStr[0], pStrCur);				//����������o��
										if (memcmp(&aStr[0], TEXT_KEYSET, strlen(TEXT_KEYSET)) == 0)
										{//�L�[�̐ݒu�J�n�������s�̏ꍇ
											for (int nCntModel = 0; nCntModel < g_nNumModel; nCntModel++)
											{
												while (1)
												{
													pStrCur = CLoadFileFunction::ReadLine(pFile, &aLine[0]);
													strcpy(&aStr[0], pStrCur);				//����������o��

													if (memcmp(&aStr[0], TEXT_FRAME, strlen(TEXT_FRAME)) == 0)
													{//�t���[�����������s�̏ꍇ
														pStrCur += strlen(TEXT_FRAME);		//���o��
														pStrCur = CLoadFileFunction::GetLineTop(pStrCur);		//�s�̓ǂݍ���
														strcpy(&aStr[0], pStrCur);			//����������o��
														m_apMotionInfo[nCntMotion].aKeyInfo[nCntKey].nFrame = atoi(&aStr[0]);	//�t���[���̑��
													}
													else if (memcmp(&aStr[0], TEXT_KEY, strlen(TEXT_KEY)) == 0)
													{//�L�[�̊J�n�������s�̏ꍇ

														while (1)
														{
															pStrCur = CLoadFileFunction::ReadLine(pFile, &aLine[0]);	//�s�̓ǂݍ���
															strcpy(&aStr[0], pStrCur);				//����������o��

															if (memcmp(&aStr[0], TEXT_POS, strlen(TEXT_POS)) == 0)
															{//�ʒu�̏��������s�̏ꍇ
																int nWord = 0;
																pStrCur += strlen(TEXT_POS);	//���o��

																strcpy(&aStr[0], pStrCur);			//����������o��
																m_apMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntModel].fPosX = (float)atof(&aStr[0]);	//X���W�̑��

																nWord = CLoadFileFunction::PopString(pStrCur, &aStr[0]);	//�������J�E���g
																pStrCur += nWord;						//�J�E���g���ꂽ�����o��
																strcpy(&aStr[0], pStrCur);				//����������o��
																m_apMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntModel].fPosY = (float)atof(&aStr[0]);	//Y���W�̑��

																nWord = CLoadFileFunction::PopString(pStrCur, &aStr[0]);	//�������J�E���g
																pStrCur += nWord;						//�J�E���g���ꂽ�����o��
																strcpy(&aStr[0], pStrCur);				//����������o��
																m_apMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntModel].fPosZ = (float)atof(&aStr[0]);	//Z���W�̑��
															}
															else if (memcmp(&aStr[0], TEXT_ROT, strlen(TEXT_ROT)) == 0)
															{//�����̏��������s�̏ꍇ
																int nWord = 0;
																pStrCur += strlen(TEXT_ROT);		//���o��

																strcpy(&aStr[0], pStrCur);			//����������o��
																m_apMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntModel].fRotX = (float)atof(&aStr[0]);	//X���W�̑��

																nWord = CLoadFileFunction::PopString(pStrCur, &aStr[0]);	//�������J�E���g
																pStrCur += nWord;						//�J�E���g���ꂽ�����o��
																strcpy(&aStr[0], pStrCur);				//����������o��
																m_apMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntModel].fRotY = (float)atof(&aStr[0]);	//Y���W�̑��

																nWord = CLoadFileFunction::PopString(pStrCur, &aStr[0]);	//�������J�E���g
																pStrCur += nWord;						//�J�E���g���ꂽ�����o��
																strcpy(&aStr[0], pStrCur);				//����������o��
																m_apMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntModel].fRotZ = (float)atof(&aStr[0]);	//Z���W�̑��
															}
															else if (memcmp(&aStr[0], TEXT_END_KEY, strlen(TEXT_END_KEY)) == 0)
															{//�L�[�̏I���������s�̏ꍇ
																break;
															}
														}
														break;
													}

												}
											}
										}
										else if (memcmp(&aStr[0], TEXT_END_KEYSET, strlen(TEXT_END_KEYSET)) == 0)
										{//�L�[�̐ݒu�I���������s�̏ꍇ
											break;
										}
									}
								}
							}
							else if (memcmp(&aStr[0], TEXT_END_MOTIONSET, strlen(TEXT_END_MOTIONSET)) == 0)
							{//���[�V�����̐ݒu�I���������s�̏ꍇ
								break;
							}
						}
					}
				}
			}
			else if (memcmp(&aStr[0], TEXT_END_SCRIPT, strlen(TEXT_END_SCRIPT)) == 0)
			{
				break;
			}
		}
	}
	fclose(pFile);	//�t�@�C�������
}

//=============================================================================
// ���[�V�����̐ݒu����
//=============================================================================
void CPlayer::SetMotion(MOTION_TYPE type)
{
	m_motionType = type;
}

//=============================================================================
//�@�W�����v�����Ă��邩���擾
//=============================================================================
bool CPlayer::GetJump(void)
{
	return m_bJump;
}

//=============================================================================
//�@�W�����v�����Ă��邩���擾
//=============================================================================
CPlayer::PLAYER_STATE CPlayer::GetState(void)
{
	return m_state;
}
