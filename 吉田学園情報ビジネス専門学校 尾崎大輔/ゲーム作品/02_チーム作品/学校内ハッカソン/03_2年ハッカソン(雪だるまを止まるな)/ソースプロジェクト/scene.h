//=============================================================================
//
// �I�u�W�F�N�g���� [scene.h]
// Author : Jukiya Hayakawa
//
//=============================================================================
#ifndef _SCENE_H_
#define _SCENE_H_

#include "main.h"

#define MAX_SCENE (2000)		//Scene�̍ő吔
#define NUM_PRIORITY (8)		//�D�揇�ʂ̑���
#define SCORE_DIGIT (5)
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CScene
{
public:	//�N������A�N�Z�X�\
	//=========================================================================
	// �\���̂̒�`
	//=========================================================================
	typedef enum
	{
		OBJTYPE_NONE = 0,
		OBJTYPE_SCENE2D,		//�I�u�W�F�N�g2D
		OBJTYPE_SCENE3D,		//�I�u�W�F�N�g3D
		OBJTYPE_SCENEX,			//�I�u�W�F�N�gX
		OBJTYPE_FADE,			//�t�F�[�h
		OBJTYPE_MESHFIELD,		//���b�V���t�B�[���h
		OBJTYPE_BILLBOARD,		//�r���{�[�h
		OBJTYPE_GIMMIC,			//�M�~�b�N
		OBJTYPE_PLAYER,			//�v���C���[
		OBJTYPE_OBJECT,			//�I�u�W�F�N�g
		OBJTYPE_EFFECT,			//�G�t�F�N�g
		OBJTYPE_ITEM_BILLBOARD,	//�A�C�e���r���{�[�h
		OBJTYPE_MAX,
	} OBJTYPE;

	//�����o�֐�
	CScene(int nPriority, OBJTYPE objtype);
	void SetObjType(OBJTYPE objType);
	OBJTYPE GetObjType(void);
	void SetVertex(D3DXVECTOR3 vtx);
	void SetMatrix(D3DXMATRIX mtx);
	D3DXVECTOR3 GetVertex(void);
	D3DXMATRIX GetMatrix(void);
	CScene *GetNext(void);
	CScene *GetPrev(void);

	//�������z�֐�
	virtual ~CScene();
	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

	//�ÓI�����o�֐�
	static void ReleaseAll(void);
	static void UpdateAll(void);
	static void DrawAll(void);
	static CScene *GetTop(int nPriority);

private:	//�����������A�N�Z�X�\
	//�����o�֐�
	void Death(void);

	//�����o�ϐ�
	CScene			*m_pPrev;		//�O�̃I�u�W�F�N�g�ւ̃|�C���^
	CScene			*m_pNext;		//���̃I�u�W�F�N�g�ւ̃|�C���^
	bool			m_bDeath;		//���S�t���O
	int				m_nPriority;	//�D�揇�ʂ̔ԍ�
	OBJTYPE			m_objType;		//�I�u�W�F�N�g�̎��
	D3DXVECTOR3		m_vertex;
	D3DXMATRIX		m_matrix;

	//�ÓI�����o�ϐ�
	static CScene	*m_apTop[NUM_PRIORITY];			//�擪�̃I�u�W�F�N�g�ւ̃|�C���^
	static CScene	*m_apCur[NUM_PRIORITY];			//���݁i�Ō���j�̃I�u�W�F�N�g�ւ̃|�C���^
	static int		m_nNumAll;						//�I�u�W�F�N�g�̑���
	static int		m_nNumPriority[NUM_PRIORITY];	//�D�揇�ʂ̏��
protected:	//�����Ɣh���N���X�������A�N�Z�X�\
	void Release(void);								//�f�[�^�J��
};
#endif