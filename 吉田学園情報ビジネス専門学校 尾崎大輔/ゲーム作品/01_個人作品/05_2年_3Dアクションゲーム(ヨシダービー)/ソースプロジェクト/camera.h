//=============================================================================
//
// �J�������� [camera.h]
// Author : Ozaki
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MOVE			(30.0f)
#define MAX_X			(250)
#define	CAMERA_MOVE		(2.0f)
#define	MAX_CAMERA		(2)
//*****************************************************************************
// �N���X�錾
//*****************************************************************************
class COwner;
class CCamera
{
public:

	//*****************************************************************************
	// �J�����̍\����
	//*****************************************************************************
	typedef enum
	{
		CAMERA_NORMAL = 0,
		CAMERA_PLAYER,
	}CAMERA;

	typedef enum
	{
		MODE_TITLE = 0,		// �^�C�g��
		MODE_TUTORIAL,		// �`���[�g���A��
		MODE_GAME,			// �Q�[��
		MODE_RESULT,		// ���U���g
		MODE_MAX
	}MODE;

	typedef struct
	{
		D3DXVECTOR3 posV;				// ���_
		D3DXVECTOR3 posR;				// �����_
		D3DXVECTOR3 posU;				// ������x�N�g��

		D3DXVECTOR3 posVDest;			// ���_
		D3DXVECTOR3 posRDest;			// �����_
		D3DXVECTOR3 posUDest;			// ������x�N�g��
		D3DXVECTOR3 rot;				// ����
		D3DXVECTOR3 rotDest;			// �ړI�̌���
		float		rotDiff;			// ����
		D3DXMATRIX  mtxProjection;		// �v���W�F�N�^�[�}�g���b�N�X
		D3DXMATRIX	mtxView;			// �r���[�}�g���b�N�X
		float		flength;			// ����
		float		angle;				// ����
		int			nCounterState;		// ��ԊǗ��J�E���^�[
		int			DirectionMove0;		// �E
		bool		bDisp;				// �g�p���Ă邩�ǂ���
		CAMERA		state;				// �J�����̃X�e�[�g
		int nCounterAngle;				// �J�����A���O�����ς��J�E���^�[

	}Camera;

	CCamera();
	~CCamera();

	HRESULT Init(void);
	void	Uninit(void);
	void	Update(void);
	void	SetCamera(void);
	Camera  GetCamera(void);
	MODE	GetMode(void);
	void	SetMode(MODE mode);
	D3DXVECTOR3 GetRot(void);

private:

	Camera	m_camera;						// �J�����̏��
	MODE	m_mode;
	D3DXVECTOR3	m_rot;
	float fLength;
	int nCounterAngle;			//�J�����A���O�����ς��J�E���^�[
};
#endif
