//=============================================================================
//
// �V�[������ [scene.h]
// Author : Ozaki
//
//=============================================================================
#ifndef _SCENE_H_
#define _SCENE_H_

#include "main.h"

//===================================================================
// �}�N����`
//===================================================================
#define MAX_POLYGON		(9)		// �|���S����
#define MAX_PRIORITY1	(9)		// �`��̗D�揇��

//*****************************************************************************
// �N���X�錾
//*****************************************************************************
class CScene
{
public:

	typedef enum
	{
		OBJTYPE_NONE = 0,		// �����Ȃ�
		OBJTYPE_2D,				// 2D
		OBJTYPE_3D,				// 3D
		OBJTYPE_X,				// X
		OBJTYPE_LOGO,			// ���S
		OBJTYPE_MODEL,			// ���f��
		OBJTYPE_GIMMICK,		// �M�~�b�N
		OBJTYPE_MESHFIELD,		// ���b�V���t�B�[���h
		OBJTYPE_GAUGE,			// �Q�[�W
		OBJTYPE_WALL,
		OBJTYPE_MESHORBIT,		// ���b�V���I�[�r�b�g
		OBJTYPE_BILLBOARD,		// �r���{�[�h
		OBJTYPE_PLAYER,			// �v���C���[
		OBJTYPE_ENEMY,			// �G
		OBJTYPE_BULLET,			// �e
		OBJTYPE_PRESSENTOR,		// �v���X�G���^�[
		OBJTYPE_BGMODEL,		// �I�u�W�F�N�g���f��
		OBJTYPE_PAUSE,
		OBJTYPE_MAX				// �ő吔
	}OBJTYPE;

	CScene(int nPriority = 3,OBJTYPE objtype = OBJTYPE_NONE);
	virtual ~CScene();

	// �������z�֐�
	virtual HRESULT	Init(void) = 0;
	virtual void	Uninit(void) = 0;
	virtual void	Update(void) = 0;
	virtual void	Draw(void) = 0;

	static void ReleaseAll(void);
	static void UpdateAll(void);
	static void DrawAll(void);
		   void	UninitAll(void);
		   void SetObjtType(OBJTYPE objttpe);

		   OBJTYPE GetObjtType(void);
		   void SetObjType(OBJTYPE ObjType);			//�^�C�v��ݒ�
		   CScene::OBJTYPE GetObjType(void);			//�^�C�v���擾

		   // X
		   D3DXVECTOR3 GetPosition(void);
		   void SetPosition(D3DXVECTOR3 pos);
		   D3DXVECTOR3 GetMove(void);
		   void SetMove(D3DXVECTOR3 move);
		   void SetRot(D3DXVECTOR3 rot);
protected:

	void Release(void);

private:

	static	CScene * m_pTop[MAX_PRIORITY1];					// �擪�̃I�u�W�F�N�g�ւ̃|�C���^
	static	CScene * m_pCur[MAX_PRIORITY1];					// ����(�Ō��)�̃I�u�W�F�N�g�ւ̃|�C���^
	CScene		   * m_pPrev;								// �O�̃I�u�W�F�N�g�ւ̃|�C���^
	CScene		   * m_pNext;								// ���̃I�u�W�F�N�g�ւ̃|�C���^


	static int		m_nNumALL;								// �|���S���̑���
	int				m_nID;									// �������g�̔ԍ�
	int				m_nPriority;							// �D�揇�ʂ̔ԍ�
	static int		m_nNumPriority[MAX_PRIORITY1];
	OBJTYPE			m_objtype;								// �I�u�W�F�N�g�^�C�v
	bool			m_bDeath;								// ���S�t���O
	bool			m_pDeath;								// ���S�t���O

	// X
	D3DXVECTOR3		m_move;									// ����
	D3DXVECTOR3		m_pos;									// �ʒu

	D3DXVECTOR3		m_rot;									// ����
};
#endif