//=============================================================================
//
// ���͏��� [pause.h]
// Author :  Ozaki
//
//=============================================================================
#ifndef _PAUSESELECT_H_
#define _PAUSESELECT_H_

#include "main.h"
#include "Scene2D.h"
#include "scene.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_Pausecont	(256)	// �ő吔
#define	TEXTURE_CONTINUE		"data/TEXTURE/pause000.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_RETRY			"data/TEXTURE/pause001.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_QUIT			"data/TEXTURE/pause002.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define POLYGON_POS_X			(200)						// ���_���WX�̈ړ���
#define POLYGON_POS_Y			(50)						// ���_���WY�̈ړ���
#define TEX_POS_X_INIT			(1.0f)						// �e�N�X�`�����WU�̏����ʒu
#define TEX_POS_Y_INIT			(1.0f)						// �e�N�X�`�����WV�̏����ʒu
#define TEX_LEFT				(0.0f)						// �e�N�X�`�����WU��
#define TEX_RIGHT				(1.0f)						// �e�N�X�`�����WU�E
#define TEX_TOP					(0.0f)						// �e�N�X�`�����WV��
#define TEX_BOT					(1.0f)						// �e�N�X�`�����WV��
#define MAX_PAUSEMENU			(4)							// �|�[�Y�̐�

//*****************************************************************************
// �N���X�錾
//*****************************************************************************

class CPause : public CScene
{
public:

	typedef enum
	{
		SELECTMODE_NONE = 0,
		SELECTMODE_CONTINE,
		SELECTMODE_RETRY,
		SELECTMODE_QUIT,
		SELECTMODE_MAX,
	}PAUSETYPE;

	typedef enum
	{
		SELECTTYPE_NONE = 0,
		SELECTTYPE_SELECT,
		SELECTTYPE_BG,
		SELECTTYPE_MAX
	}SELECT;

	typedef struct
	{
		SELECT		select;		//�Z���N�g
		D3DXVECTOR3 pos;		//�ʒu
		D3DXCOLOR   col;		//�J���[

	}PAUSESELECT;

	static HRESULT Load(void);	// �ǂݍ���

	static void Unload(void);	// �J��

	CPause();
	~CPause();

	HRESULT Init(D3DXVECTOR3 pos, float widtgh, float height);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	PAUSETYPE GetPause(void);

	static CPause *Create(D3DXVECTOR3 pos, float widtgh, float height);

private:

	static LPDIRECT3DTEXTURE9	m_pTexture[MAX_PAUSEMENU];					// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff[MAX_PAUSEMENU];							// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DTEXTURE9			m_pTexturePause = NULL;						// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuffPause = NULL;						// �o�b�t�@�̃|�C���^
	PAUSESELECT					m_aPauseMenu[MAX_PAUSEMENU];				// �|�[�Y���j���[
	D3DXVECTOR3					m_PauseMenuPos;
	static PAUSETYPE			m_SelectMode;
	int							m_nSelect = 0;
	CScene2D					*m_pScene2D[MAX_PAUSEMENU];
};
#endif

