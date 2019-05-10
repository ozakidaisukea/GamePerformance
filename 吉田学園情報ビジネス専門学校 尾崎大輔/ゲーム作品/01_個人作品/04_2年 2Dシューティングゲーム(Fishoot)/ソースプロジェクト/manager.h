//=============================================================================
//
// �}�l�[�W���[�̏��� [manager.h]
// Author : Ozaki
//
//=============================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "main.h"
#include "input.h"

#define MAX_RANKING	(5)

//*****************************************************************************
// �N���X�錾
//*****************************************************************************
class CTitle;
class CGame;
class CResult;
class CGameover;
class CRanking;
class CTutorial;
class CSound;
class CFade;
class CScore;
class CInputjoypad;
class CSousa;

class CManager
{
public:

	typedef enum
	{
		MODE_TITLE = 0,
		MODE_SOUSA,
		MODE_TUTORIAL,
		MODE_GAME,
		MODE_RESULT,
		MODE_GAMEOVER,
		MODE_RANKING,
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

	// ���[�h�̐ݒ�
	static void SetMode(MODE mode);

	// �����_���[
	static CRenderer *GetRenderer(void);

	// �L�[�{�[�h
	static CInputKeyboard *GetInputKeyboard(void);

	// �p�b�h
	static CInputjoypad *GetInputJoypad(void);

	// �T�E���h
	static CSound *GetSound(void);

	// �t�F�[�h
	static CFade *GetFade(void);

	// �X�R�A
	static CScore *GetScore(void);

	// �Q�[��
	static CGame *GetGame(void);

	// �`���[�g���A��
	static CTutorial *GetTutorial(void);

	// ������@
	static CSousa *GetSousa(void);

	// �����L���O����ёւ�
	static void RankingScore(int m_pScore);

	static int GetRankingScore(int nIdx);

private:

	// ���[�h
	static MODE m_mode;

	// �����_���[
	static CRenderer *m_pRenderer;

	// �L�[�{�[�h
	static CInputKeyboard *m_pInputKeyboard;

	// �W���C�p�b�h
	static CInputjoypad *m_pInputJoypad;

	// �T�E���h
	static CSound *m_pSound;

	// �^�C�g��
	static CTitle *m_pTitle;

	// �`���[�g���A��
	static CTutorial *m_pTutorial;

	// �Q�[��
	static CGame *m_pGame;

	// ���U���g
	static CResult *m_pResult;

	// �Q�[���I�[�o�[
	static CGameover *m_pGameover;

	// �����L���O
	static CRanking *m_pRanking;

	// �t�F�[�h
	static CFade *m_pFade;

	// �X�R�A
	static CScore *m_pScore;

	// ������@
	static CSousa *m_pSousa;

	// �����L���O��
	static int m_Rankingscore[MAX_RANKING];
};
#endif