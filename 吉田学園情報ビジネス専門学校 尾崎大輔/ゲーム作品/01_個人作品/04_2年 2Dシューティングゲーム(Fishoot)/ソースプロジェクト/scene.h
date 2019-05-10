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
#define MAX_POLYGON		(1000)
#define MAX_PRIORITY1	(10)			// �`��̗D�揇��

//*****************************************************************************
// �N���X�錾
//*****************************************************************************
class CScene
{
public:

	// �|���S���̎��
	typedef enum
	{
		TYPE_2D = 0,
		TYPE_3D,
		TYPE_MAX
	}TYPE;

	typedef enum
	{
		OBJTYPE_NONE = 0,
		OBJTYPE_PLAYER,
		OBJTYPE_ENEMY,
		OBJTYPE_BULLET,
		OBJTYPE_EXPLOSION,
		OBJTYPE_ITEM,
		OBJTYPE_GAUGE,
		OBJTYPE_BG,
		OBJTYPE_LOGO,
		OBJTYPE_PRESSENTOR,
		OBJTYPE_LIFE,
		OBJTYPE_EFFECT,
		OBJTYPE_PAUSE,
		OBJTYPE_MAX
	}OBJTYPE;

	CScene(int nPriority = 3);
	virtual ~CScene();

	// �������z�֐�
	virtual HRESULT Init(D3DXVECTOR3 pos, float widtgh, float height) = 0;
	virtual void	Uninit(void) = 0;
	virtual void	Update(void) = 0;
	virtual void	Draw(void) = 0;

	static void ReleaseAll(void);
	static void UpdateAll(void);
	static void DrawAll(void);

	void SetObjtType(OBJTYPE objttpe);

	OBJTYPE GetObjtType(void);

	static CScene *GetSCene(int nIdex,int nPriority);

protected:

	void Release(void);

private:

	// CScene�^�̃|�C���^ �񎟌��z��
	static CScene *m_apCscene[MAX_PRIORITY1][MAX_POLYGON];

	// �|���S���̑���
	static int	m_nNumALL;
	int			m_nID;			// �������g�̔ԍ�
	int			m_nPriority;	// �D�揇�ʂ̔ԍ�
	OBJTYPE		m_objtype;
};
#endif