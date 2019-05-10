//=============================================================================
//
// �}�l�[�W���[�̏��� [manager.h]
// Author : Ozaki
//
//=============================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "main.h"

//*****************************************************************************
// �N���X�錾
//*****************************************************************************
class CRenderer;
class CInputKeyboard;
class CCamera;
class CLight;
class CPlayer;
class CScene3D;
class CMeshFiled;
class CGimmick;
class CMeshOrbit;
class CSound;
class CFade;
class CTitle;
class CTutorial;
class CGame;
class CResult;
class CRanking;
class CInputjoypad;

class CManager
{
public:

	typedef enum
	{
		MODE_TITLE = 0,
		MODE_TUTORIAL,
		MODE_GAME,
		MODE_RESULT,
		MODE_MAX
	}MODE;

	CManager();
	~CManager();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// ���[�h���擾
	static MODE GetMode(void);

	// �T�E���h
	static CSound *GetSound(void);

	// ���[�h�̐ݒ�
	static void SetMode(MODE mode);

	// �����_���[
	static CRenderer *GetRenderer(void);

	// �L�[�{�[�h
	static CInputKeyboard *GetInputKeyboard(void);

	// �^�C�g��
	static CTitle *GetTitle(void);

	// �`���[�g���A��
	static CTutorial *GetTutorial(void);

	// �Q�[��
	static CGame *GetGame(void);

	// ���U���g
	static CResult *GetResult(void);

	// �����L���O
	static CRanking *GetRamking(void);

	// ���C�g
	static CLight *GetLight(void);

	// �V�[��3D
	static CScene3D *GetScene3D(void);

	// �v���C���[
	static CPlayer *GetPlayer(void);

	// �t�F�[�h
	static CFade *GetFade(void);

	// ���b�V���t�B�[���h
	static CMeshFiled *GetMeshField(void);

	// ���b�V���I�[�r�b�g
	static CMeshOrbit *GetMeshOrbit(void);

	// �p�b�h
	static CInputjoypad *GetInputJoypad(void);

	// ���[�h
	static MODE m_mode;

private:

	// �T�E���h
	static CSound *m_pSound;

	// �����_���[
	static CRenderer *m_pRenderer;

	// �J����
	static CCamera *m_pCamera;

	// �W���C�p�b�h
	static CInputjoypad *m_pInputJoypad;

	// ���C�g
	static CLight *m_pLight;

	// �V�[��3D
	static CScene3D *m_pScene3D;

	// �L�[�{�[�h
	static CInputKeyboard *m_pInputKeyboard;

	// �^�C�g��
	static CTitle *m_pTitle;

	// �`���[�g���A��
	static CTutorial *m_pTutorial;

	// �Q�[��
	static CGame *m_pGame;

	// ���U���g
	static CResult *m_pResult;

	// �����L���O
	static CRanking *m_pRanking;

	// �v���C���[
	static CPlayer *m_pPlayer;

	// �t�F�[�h
	static CFade *m_pFade;

	// ���b�V���t�B�[���h
	static CMeshFiled *m_pMeshField;

	// ���b�V���I�[�r�b�g
	static CMeshOrbit *m_pMeshOrbit;

	static int m_playertaime;
};
#endif