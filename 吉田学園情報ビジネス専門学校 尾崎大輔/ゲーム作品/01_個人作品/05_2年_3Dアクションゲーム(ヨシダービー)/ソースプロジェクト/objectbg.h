//=============================================================================
//
// �I�u�W�F�N�gBG���� [objectBG.h]
// Author : Ozaki
//
//=============================================================================
#ifndef _OBJECTBG_H_
#define _OBJECTBG_H_

#include "main.h"
#include "scene.h"

#include<stdio.h>
#include<string.h>

//*********************************************************************
// �}�N����`
//*********************************************************************
#define MAX_MATTEX				(20)
#define MAX_PARTS				(30)
#define NUM_OBJ_MODEL			(11)
#define MAX_OBJMOTION			(10)
//*********************************************************************
// �\����
//*********************************************************************

//*********************************************************************
//�v���C���[�N���X�̒�`
//*********************************************************************
class CModel;

class CObjectBG : public CScene //�h���N���X
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
		KEY_INFO	aKeyInfo[NUM_OBJ_MODEL];
	}MOTION_INFO;

	typedef enum
	{
		MODELTYPE_BILL000 = 0,	// �r�� 0 ��
		MODELTYPE_BILL001,		// �r�� 1 ��
		MODELTYPE_BILL002,		// �r�� 2 ��
		MODELTYPE_BILL003,		// �r�� 3 ��
		MODELTYPE_GOAL,			// �S�[��
		MODELTYPE_GAGE,			// �Q�[�W
		MODELTYPE_MAX,			// �ő吔
	}MODELTYPE;

	CObjectBG();
	~CObjectBG();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Setpos(D3DXVECTOR3 pos);
	static CObjectBG *Create(D3DXVECTOR3 pos,D3DXVECTOR3 rot, MODELTYPE type);
	static HRESULT Load(void);
	static void UnLoad(void);
	D3DXVECTOR3 GetPos(void);

	//void	FileLoad(void);							// �t�@�C���ǂݍ���
	void UpdateMotion(void);							// ���[�V�����̍X�V�֐�

	static char	*ReadLine(FILE *pFile, char *pDest);	// 1�s��(256������)�̓ǂݍ���
	static char *GetLineTop(char *pSrc);				// ������̐擪���擾
	static int	PopString(char *pSrc, char *pDest);		// ������𔲂��o��

	//bool CollisionObject(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove);
	CModel								*m_pModel;

private:

	//�����o�ϐ�
	D3DXVECTOR3							m_pos;						//�ʒu
	D3DXVECTOR3							m_posold;					//�O��̈ʒu
	D3DXVECTOR3							m_move;						//�ړ���
	D3DXVECTOR3							m_rot;						//����
	D3DXMATRIX							m_mtxWorld;					//���[���h�}�g���b�N�X
	MODELTYPE							m_Type;						//�^�C�v


	float								m_fDestAngle;				//�p�x
	float								m_fDiffAngle;				//����

	static LPD3DXMESH					m_pMesh[MODELTYPE_MAX];		//���b�V�����ւ̃|�C���^
	static LPD3DXBUFFER					m_pBuffMat[MODELTYPE_MAX];	//�}�e���A�����ւ̃|�C���^
	static LPDIRECT3DTEXTURE9			m_pObjTexture[MODELTYPE_MAX];	//�e�N�X�`���ւ̃|�C���^
	static DWORD						m_nNumMat[MODELTYPE_MAX];	//�}�e���A�����̐�

	int									m_nCollision;				// �����蔻���ONOFF

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

	// char�^��
	static char					m_aFileNameModel[MAX_PARTS][256];

	// �ÓI�����o�ϐ�
	static CModel				*m_apModel[MAX_PARTS];			// ���f���ւ̃|�C���^
	static KEY					m_aKeyOffset[MAX_PARTS];		// �p�[�c�̍ő吔
	static KEY_INFO				*m_pKeyInfo[MAX_OBJMOTION];		// �L�[�̑���
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