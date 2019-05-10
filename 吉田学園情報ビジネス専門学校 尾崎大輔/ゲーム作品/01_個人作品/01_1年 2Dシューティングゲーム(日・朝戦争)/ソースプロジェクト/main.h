//=============================================================================
//
// DirectX���^���� [main.h]
// Author : Ozaki
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_
//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include <windows.h>
#include "d3dx9.h"					//�`�揈���ɕK�v
#define DIRECTINPUT_VERSION (0x0800) //�r���h���̌x���Ώ��p�}�N��
#include "dinput.h"

#include "xaudio2.h"

//*****************************************************************************
// ���C�u�����̃����N
//*****************************************************************************
#pragma comment(lib,"d3d9.lib")			// �`�揈���ɕK�v
#pragma comment(lib,"d3dx9.lib")		// [d3d9.lib]�̊g���̃��C�u����
#pragma comment(lib,"dxguid.lib")		// DirectX�R���{�[�l�b�g(���i)�g�p�ɕK�v
#pragma comment(lib,"winmm.lib")		// �V�X�e�������擾���K�v
#pragma comment(lib,"dinput8.lib")		// �V�X�e�������擾���K�v

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SCREEN_WIDTH	(1280)		// �E�C���h�E�̕�
#define SCREEN_HEIGHT	(720)		// �E�C���h�E�̍���
#define FVF_VRETEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

//*****************************************************************************
//�\���̂̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;				//���_���W
	float rhw;						//1.0f�ŌŒ�
	D3DCOLOR col;					//���_�J���[
	D3DXVECTOR2 tex;				//�e�N�X�`�����W

}VERTEX_2D;

typedef enum
{
	MODE_TITLE = 0,		//�^�C�g��
	MODE_GAME,			//�Q�[��
	MODE_RESULT,		//���U���g
	MODE_GAMEOVER,		//�Q�[���I�[�o�[
	MODE_RANKING,		//�����L���O
	MODE_TUTORIAL,
	MODE_MAX
}MODE;

//*****************************************************************************
//�v���g�^�C�v�錾
//*****************************************************************************
LPDIRECT3DDEVICE9 GetDevice(void);
void SetMode(MODE mode);
MODE GetMode(void);
#endif