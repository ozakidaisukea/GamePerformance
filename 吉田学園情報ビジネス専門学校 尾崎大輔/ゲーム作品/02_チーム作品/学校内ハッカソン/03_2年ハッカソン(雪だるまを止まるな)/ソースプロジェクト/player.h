//=============================================================================
//
// �v���C���[�̏��� [player.h]
// Author : Jukiya Hayakawa
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
#include "scene.h"

#define MAX_PLAYER_MODEL (1)
#define MAX_PLAYER_PARTS (1)
#define MAX_MOTION		 (10)
#define MAX_KEY			 (10)

//�O���錾
class CModel;
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CPlayer : public CScene
{
public:	//�N������A�N�Z�X�\
	//*************************************************************************
	// �\���̒�`
	//*************************************************************************
	typedef struct
	{
		float fPosX;
		float fPosY;
		float fPosZ;
		float fRotX;
		float fRotY;
		float fRotZ;
	}KEY;

	typedef struct
	{
		int nFrame;
		KEY aKey[MAX_PLAYER_MODEL];
	}KEY_INFO;

	typedef struct
	{
		bool bLoop;
		int nNumKey;
		KEY_INFO aKeyInfo[MAX_KEY];
	}MOTION_INFO;

	typedef enum
	{
		MOTION_NEUTRAL = 0,		//�j���[�g�������[�V����
		MOTION_MOVE,			//�ړ����[�V����
		MOTION_PANCH,			//�p���`���[�V����
		MOTION_JUMP,			//�W�����v���[�V����
		MOTION_LANDING,			//���n���[�V����
		MOTION_MAX,
	}MOTION_TYPE;

	typedef enum
	{
		PLAYER_STATE_START = 0,
		PLAYER_STATE_GOAL,
		PLAYER_STATE_MAX,
	}PLAYER_STATE;

	//�����o�֐�
	CPlayer();
	~CPlayer();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void UpdateMotion(void);
	void LoadMotion(void);
	void SetMotion(MOTION_TYPE type);
	bool GetJump(void);
	D3DXVECTOR3 GetPosition(void) { return m_pos; };
	D3DXVECTOR3 SetScale(D3DXVECTOR3 scale);
	PLAYER_STATE GetState(void);

	//�ÓI�����o�֐�
	static CPlayer *Create(D3DXVECTOR3 pos);
	static HRESULT Load(void);
	static void Unload(void);

private:	//�����������A�N�Z�X�\
	//�����o�֐�
	void Move(void);
	void Collision(void);

	//�����o�ϐ�
	D3DXVECTOR3 m_pos;											//�ʒu
	D3DXVECTOR3 m_posOld;										//�ߋ��̈ʒu
	D3DXVECTOR3 m_rot;											//����
	D3DXVECTOR3	m_move;											//�ړ���
	D3DXMATRIX	m_mtxWorld;										//���[���h�}�g���b�N�X
	D3DXVECTOR3	m_VtxMin;						//�ŏ��l
	D3DXVECTOR3	m_VtxMax;						//�ő�l
	bool		m_bJump;										//�W�����v���Ă��邩�ǂ���
	int			m_nNumKey;										//�L�[�̑���
	KEY_INFO	*m_pKeyInfo;									//�L�[���̃|�C���^
	int			m_nKey;											//���݂̃L�[No.
	int			m_nCountFrame;									//�t���[���J�E���^�[
	int			m_nNumParts;									//�p�[�c�̑���
	int			m_nIndexParent[MAX_PLAYER_PARTS];				//�v���C���[�̃p�[�c�ԍ�
	KEY			m_aKeyOffset[MAX_PLAYER_PARTS];					//�v���C���[�̃I�t�Z�b�g
	MOTION_INFO	m_apMotionInfo[MAX_KEY];						//���[�V�����̏��
	MOTION_TYPE	m_motionType;									//���[�V�����̎��
	D3DXVECTOR3	 m_scale;										//�傫��
	int m_OldMotion;											//�ߋ��̃��[�V����
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;						// ���_�o�b�t�@�ւ̃|�C���^
	CModel						*m_apModel[MAX_PLAYER_MODEL];	//���f���̃|�C���^
	D3DXMATRIX	m_mtxRot;										//��]�}�g���b�N�X�i�ۑ��p�j
	D3DXQUATERNION	m_quat;										//�N�H�[�^�j�I��
	D3DXVECTOR3	m_vecAxis;										//��]��
	float		m_fValueRot;									//��]�p�i��]�ʁj
	PLAYER_STATE m_state;										//�v���C���[�̏��
	bool		m_bHitFlag;										//�I�u�W�F�N�g�̎�O�Ƀq�b�g������
	int			m_nAppearTimer;									//���G���ԃ^�C�}�[

	//�ÓI�����o�ϐ�
	static LPDIRECT3DTEXTURE9	m_pTexture;								// �e�N�X�`���ւ̃|�C���^

	//�ÓI�����o�ϐ�
	static LPD3DXMESH			m_pMesh[MAX_PLAYER_MODEL];		//���b�V�����ւ̃|�C���^
	static LPD3DXBUFFER			m_pBuffMat[MAX_PLAYER_MODEL];	//�}�e���A�����ւ̃|�C���^
	static DWORD				m_nNumMat[MAX_PLAYER_MODEL];	//�}�e���A�����̐�
};
#endif