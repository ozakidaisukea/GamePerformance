//=============================================================================
//
// ���C������ [main.h]
// Author :  Meguro Mikiya
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include <windows.h>
#include "d3dx9.h"						//�`�揈���ɕK�v
#define DIRECTINPUT_VERSION (0x0800)	// �x���Ώ��p
#include "dinput.h"						//���͏����ɕK�v
#include "xaudio2.h"					//���y�f�[�^�ɕK�v
#include "XInput.h"
//*****************************************************************************
// ���C�u�����t�@�C��
//*****************************************************************************
#pragma comment (lib, "d3d9.lib")		//�`�揈���ɕK�v
#pragma comment (lib, "d3dx9.lib")		//d3d9�̊g�����C�u����
#pragma comment (lib, "dxguid.lib")		//DirectX�R���|�[�l���g(���i)�g�p�ɕK�v
#pragma comment (lib, "winmm.lib")		//�V�X�e�����Ԏ擾�ɕK�v
#pragma comment (lib, "dinput8.lib")	//���͏����ɕK�v
#pragma comment (lib, "xinput.lib")	//���͏����ɕK�v
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SCREEN_WIDTH	(1280)	// �E�C���h�E�̕�
#define SCREEN_HEIGHT	(720)	// �E�C���h�E�̍���

// 2�c�|���S�����_�t�H�[�}�b�g( ���_���W[2D] / �@���x�N�g�� / ���_�J���[ )
#define FVF_VERTEX_2D			(D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)	

// 3�c�|���S�����_�t�H�[�}�b�g( ���_���W[3D] / �@���x�N�g�� / ���_�J���[ )
#define	FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)


//*****************************************************************************
// �\���̒�`
//*****************************************************************************
//��ʑJ�ڗp
typedef enum
{
	MODE_TITLE = 0,		//�^�C�g��
	MODE_TUTORIAL,		//�`���[�g���A��
	MODE_GAME,			//�Q�[��
	MODE_RESULT,		//���U���g
	MODE_RANKING,		//�����L���O
	MODE_GAMEOVER,		//�Q�[���I�[�o�[
	MODE_MAX
}MODE;
// 2�c�|���S�����_�t�H�[�}�b�g�ɍ��킹���\���̂��`
typedef struct
{
	D3DXVECTOR3 pos;	//���_���W
	float rhw;			//1.0f�ŌŒ�
	D3DCOLOR col;		//���_�J���[
	D3DXVECTOR2 tex;	//�e�N�X�`�����W
}VERTEX_2D;

// 3�c�|���S�����_�t�H�[�}�b�g�ɍ��킹���\���̂��`
typedef struct
{
	D3DXVECTOR3 pos;	// ���_���W
	D3DXVECTOR3 nor;	//	�@���x�N�g��
	//float rhw;			// ���W�ϊ��p�W��(1.0f�ŌŒ�)
	D3DCOLOR col;		// ���_�J���[
	D3DXVECTOR2 tex;	// �e�N�X�`�����W
} VERTEX_3D;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
LPDIRECT3DDEVICE9 GetDevice(void);
void SetMode(MODE mode);
MODE GetMode(void);

#endif