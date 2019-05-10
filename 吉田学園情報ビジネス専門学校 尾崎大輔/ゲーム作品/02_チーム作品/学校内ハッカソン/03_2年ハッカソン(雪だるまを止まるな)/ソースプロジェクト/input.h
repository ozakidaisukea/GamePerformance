//=============================================================================
//
// ���͏��� [input.h]
// Author :�@Jukiya Hayakawa
//
//=============================================================================
#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	NUM_KEY_MAX			(256)	// �L�[�̍ő吔
#define DI_JOY_I_INPUT		(1000)	// DirectInput

//*****************************************************************************
// �N���X��`(���͏���)
//*****************************************************************************
class CInput
{
public:		//�N������A�N�Z�X�\
	//�����o�֐�
	CInput();
	//���z�֐�
	virtual ~CInput();
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	virtual void Uninit(void);
	//�������z�֐�
	virtual void Update(void) = 0;

private:	//�����������A�N�Z�X�\

protected:	//�����Ɣh���N���X�������A�N�Z�X�\
	//�����o�ϐ�
	LPDIRECTINPUTDEVICE8 m_pDevice;	//�f�o�C�X�̃|�C���^
	//�ÓI�����o�ϐ�
	static LPDIRECTINPUT8 m_pInput;	//���͂̃|�C���^
};

//*****************************************************************************
// �N���X��`(�L�[�{�[�h�̓��͏���)
//*****************************************************************************
class CInputKeyboard : public CInput
{
public:		//�N������A�N�Z�X�\
	//�����o�֐�
	CInputKeyboard();
	~CInputKeyboard();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	bool GetPress(int nKey);
	bool GetTrigger(int nKey);

private:	//�����������A�N�Z�X�\
	//�����o�ϐ�
	BYTE m_aKeyState[NUM_KEY_MAX];					// �L�[�{�[�h�̓��͏��i�v���X���j
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX];			// �L�[�{�[�h�̓��͏��i�g���K�[���j

protected:	//�����Ɣh���N���X�������A�N�Z�X�\
};
//*****************************************************************************
// �N���X��`(�W���C�p�b�h�̓��͏���)
//*****************************************************************************
class CInputJoypad : public CInput
{
public:		//�N������A�N�Z�X�\
	typedef enum
	{
		DIJS_BUTTON_X = 0,			//X�{�^��
		DIJS_BUTTON_A,				//A�{�^��
		DIJS_BUTTON_B,				//B�{�^��
		DIJS_BUTTON_Y,				//Y�{�^��
		DIJS_BUTTON_LB,				//LB�{�^��
		DIJS_BUTTON_RB,				//RB�{�^��
		DIJS_BUTTON_LT,				//LT�{�^��
		DIJS_BUTTON_RT,				//RTbutton
		DIJS_BUTTON_BACK,			//BACK�{�^��
		DIJS_BUTTON_START,			//START�{�^��
		DIJS_BUTTON_LSTICK_PUSH,	//���X�e�B�b�N����
		DIJS_BUTTON_RSTICK_PUSH,	//�E�X�e�B�b�N����
		DIJS_BUTTON_13,
		DIJS_BUTTON_14,
		DIJS_BUTTON_15,
		DIJS_BUTTON_16,
		DIJS_BUTTON_17,
		DIJS_BUTTON_18,
		DIJS_BUTTON_19,
		DIJS_BUTTON_UP,				//�\���L�[��
		DIJS_BUTTON_DOWN,			//�\���L�[��
		DIJS_BUTTON_LEFT,			//�\���L�[��
		DIJS_BUTTON_RIGHT,			//�\���L�[�E
		DIJS_BUTTON_LSTICK_UP,		//���X�e�B�b�N��
		DIJS_BUTTON_LSTICK_DOWN,	//���X�e�B�b�N��
		DIJS_BUTTON_LSTICK_LEFT,	//���X�e�B�b�N��
		DIJS_BUTTON_LSTICK_RIGHT,	//���X�e�B�b�N�E
		DIJS_BUTTON_RSTICK_UP,		//�E�X�e�B�b�N��
		DIJS_BUTTON_RSTICK_DOWN,	//�E�X�e�B�b�N��
		DIJS_BUTTON_RSTICK_LEFT,	//�E�X�e�B�b�N��
		DIJS_BUTTON_RSTICK_RIGHT,	//�E�X�e�B�b�N�E
		DIJS_BUTTON_MAX,
	} DIJS_BUTTON;

	//�����o�֐�
	CInputJoypad();
	~CInputJoypad();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	bool GetPress(DIJS_BUTTON button);
	bool GetTrigger(DIJS_BUTTON button);
	float GetLeftAxiz(void);
	float GetRightAxiz(void);
	float GetRadian(void);

private:	//�����������A�N�Z�X�\
	//�����o�ϐ�
	BYTE m_aButtonState[32];					// �L�[�{�[�h�̓��͏��i�v���X���j
	BYTE m_aButtonStateTrigger[32];				// �L�[�{�[�h�̓��͏��i�g���K�[���j
	float m_LeftAxizX;							// ���X�e�B�b�N��X��
	float m_LeftAxizY;							// ���X�e�B�b�N��Y��
	float m_RightAxizX;							// �E�X�e�B�b�N��X��
	float m_RightAxizY;							// �E�X�e�B�b�N��Y��
	float m_Radian;								// ���a

protected:	//�����Ɣh���N���X�������A�N�Z�X�\
};
#endif