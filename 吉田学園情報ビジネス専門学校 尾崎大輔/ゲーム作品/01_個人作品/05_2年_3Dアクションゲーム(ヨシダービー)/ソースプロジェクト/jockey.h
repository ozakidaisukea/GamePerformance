//=============================================================================
//
// �W���b�L�[ ���� [jockey.h]
// Author : Ozaki
//
//=============================================================================
#ifndef _JOCKEY_H_
#define _JOCKEY_H_

#include "main.h"
#include "scene.h"
#include "sceneX.h"

#include<stdio.h>
#include<string.h>

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define FIELD_MAX_SIZE			(FIELD_SIZE - 10)
#define MAX_MODEL_TYPE			(5)								//���f����ނ̍ő吔
#define MOVE_PLAYER				(0.005f)
#define MOVE_PLAYER1			(0.01f)
#define NUM_PLAYER_MODEL		(11)
#define MAX_ROT					(1.0f)
#define MAX_PARTS				(30)
#define MAX_MOTION				(30)

//*****************************************************************************
// �N���X�錾
//*****************************************************************************
class CModel;
class CScene3D;
class CMeshOrbit;

class CJockey : public CScene
{
public:

	//================
	// �L�[�v�f
	//================
	typedef struct
	{
		float fPosX;
		float fPosY;
		float fPosZ;

		float fRotX;
		float fRotY;
		float fRotZ;
	}KEY;

	//================
	// �L�[���
	//================
	typedef struct
	{
		int nFrame;
		KEY aKey[MAX_PARTS];
	}KEY_INFO;

	//================
	// ���[�V�������
	//================
	typedef struct
	{
		bool		bLoop;
		int			nNumKey;
		KEY_INFO	aKeyInfo[NUM_PLAYER_MODEL];
	}MOTION_INFO;

	typedef enum
	{
		JOCKEYSTATE_NONE = 0,		//�������
		JOCKEYSTATE_NORMAL,			//�ʏ�
		JOCKEYSTATE_MAX,			//�ő吔
	}JOCKEYSTATE;

	typedef enum
	{
		JOCKEYTYPE_NONE = 0,		//�������
		JOCKEYTYPE_TITLE,			//�ʏ�
		JOCKEYTYPE_GAME,			//�ʏ�
		JOCKEYTYPE_RESULT,
		JOCKEYTYOE_MAX,				//�ő吔
	}JOCKEYTYPE;

	static HRESULT Load(void);	// �ǂݍ���
	static void Unload(void);	// �J��

	CJockey(int nPriority = 1, OBJTYPE objtype = OBJTYPE_PLAYER);
	~CJockey();

	HRESULT Init(void);									// ����������
	void	Uninit(void);								// �I������
	void	Update(void);								// �X�V����
	void	Draw(void);									// �`�揈��
	static CJockey *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, JOCKEYTYPE type);			// ��������
	D3DXVECTOR3 GetPlayerpos(D3DXVECTOR3 pos);			// �ʒu�擾
	D3DXVECTOR3 Getpos(void);							// �ʒu�擾
	D3DXVECTOR3 Getrot(void);							// �ʒu�擾
	D3DXVECTOR3 Getmove(void);							// �ʒu�擾


	static void	FileLoad(void);							// �t�@�C���ǂݍ���
	void UpdateMotion(void);							// ���[�V�����̍X�V�֐�

	static char	*ReadLine(FILE *pFile, char *pDest);	// 1�s��(256������)�̓ǂݍ���
	static char *GetLineTop(char *pSrc);				// ������̐擪���擾
	static int	PopString(char *pSrc, char *pDest);		// ������𔲂��o��

	int							GetCntA(void);
	int							GetCntB(void);

	float						m_fDestAngle;			//�v���C���[�̊p�x
	float						m_fDiffAngle;			//����

private:

	//================================================================================
	// �����o�ϐ�
	//================================================================================

	// D3DXVECTOR��
	static D3DXVECTOR3			m_pos;							// �ʒu
	static D3DXVECTOR3			m_rot;							// ����
	D3DXVECTOR3					m_move;							// ����
	D3DXVECTOR3					m_aPos[4];						// ����
	D3DXVECTOR3					m_VecA;							// �x�N�g��A
	D3DXVECTOR3					m_VecB;							// �x�N�g��B
	D3DXVECTOR3					m_VecC;							// �x�N�g��C
	D3DXVECTOR3					m_vecAxis;						// ��]��

																// �o�b�t�@��
	LPD3DXBUFFER				m_pBuffMatModel2;				// �}�e���A�����ւ̃|�C���^

																// �}�g���b�N�X��
	D3DXMATRIX					m_mtxWorld;						// ���[���h�}�g���b�N�X
	D3DXMATRIX					*m_Mtx;
	D3DXMATRIX					m_mtxRot;						// ��]�}�g���b�N�X(�ۑ��p)

																// �t���[�g��
	float						m_fValueRot;					// ��]�p(��)

																// �u�[����
	bool						m_blr;
	bool						m_bBrake;						// �u���[�L���

																// char�^��
	static char					m_aFileNameModel[MAX_PARTS][256];

	// int�^��
	int							m_nCntA;
	int							m_nCntB;
	int							m_testCnt;

	// ���̑�
	D3DXQUATERNION				m_quat;							// �N�H�[�^�j�I��
	static CMeshOrbit			*m_mesh;
	static JOCKEYSTATE			m_State;
	static JOCKEYTYPE			m_nType;

	//================================================================================
	// ���[�V�����֐�
	//================================================================================

	D3DXVECTOR3					m_OffSetPos[MAX_PARTS];
	CScene						*m_pSceneTarget;				// �Ώۂ̃I�u�W�F�N�g(�����蔻��)
	int							m_nKey;
	int							m_nCountMotion;					// ���[�V�����J�E���^�[
	int							m_nMotionType;					// ���[�V�����̃^�C�v(int�^)
	int							m_nCountFlame;					// �t���[����

	bool						m_bMotionEnd;

	// �ÓI�����o�ϐ�
	static CModel				*m_apModel[MAX_PARTS];			// ���f���ւ̃|�C���^
	static KEY					m_aKeyOffset[MAX_PARTS];		// �p�[�c�̍ő吔
	static KEY_INFO				*m_pKeyInfo[MAX_MOTION];		// �L�[�̑���
	static MOTION_INFO			m_aMotionInfo[MAX_PARTS];		// ���[�V�������ւ̃|�C���^
	static LPD3DXMESH			m_pMeshModel[MAX_PARTS];		// ���b�V�����ւ̃|�C���^
	static DWORD				m_nNumMatModel[MAX_PARTS];		// �}�e���A�����̐�
	static LPD3DXBUFFER			m_pBuffMatModel[MAX_PARTS];		// �}�e���A�����ւ̃|�C���^
	static LPDIRECT3DTEXTURE9	m_pTexture;						// �e�N�X�`��
	static int					m_nNumParts;					// �p�[�c��
	static int					m_nNumModel;					// ���f����
	static int					m_aIndexParent[MAX_PARTS];		// �p�[�c�̍ő吔
};
#endif