//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : Jukiya Hayakawa
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CSound
{
public:	//�N������A�N�Z�X�\
		//*************************************
		// �T�E���h�t�@�C��
		//*************************************
	typedef enum
	{
		SOUND_LABEL_BGM000 = 0,		// BGM0 (OP)
		SOUND_LABEL_BGM001,			// BGM1	(TUTORIAL)
		SOUND_LABEL_BGM002,			// BGM2	(GAME)
		SOUND_LABEL_BGM003,			// BGM3	(CLEAR)
		SOUND_LABEL_BGM004,			// BGM5	(RANKING)
		SOUND_LABEL_SE_DAMAGE,		//�_���[�W
		SOUND_LABEL_SE_IDOU,		//�ړ�
		SOUND_LABEL_SE_ITEM,		//�A�C�e��
		SOUND_LABEL_SE_JUMP,		//�W�����v
		SOUND_LABEL_SE_KAKUDAI,		//�g��
		SOUND_LABEL_SE_PAUSE,		//�|�[�Y
		SOUND_LABEL_SE_SYUKUSYOU,		//�|�[�Y
		SOUND_LABEL_MAX,
	} SOUND_LABEL;

	//*****************************************************************************
	// �p�����[�^�\���̒�`
	//*****************************************************************************
	typedef struct
	{
		char *pFilename;	// �t�@�C����
		int nCntLoop;		// ���[�v�J�E���g(-1�Ń��[�v�Đ�)
	} SOUNDPARAM;

	CSound();
	~CSound();
	HRESULT InitSound(HWND hWnd);
	void UninitSound(void);
	HRESULT PlaySound(SOUND_LABEL label);
	void StopSound(SOUND_LABEL label);
	void StopSound(void);
private:	//�����������A�N�Z�X�\
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	IXAudio2 *m_pXAudio2 = NULL;								// XAudio2�I�u�W�F�N�g�ւ̃|�C���^
	IXAudio2MasteringVoice *m_pMasteringVoice = NULL;			// �}�X�^�[�{�C�X�ւ̃|�C���^
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX] = {};	// �\�[�X�{�C�X�ւ̃|�C���^
	BYTE *m_apDataAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^�ւ̃|�C���^
	DWORD m_aSizeAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^�T�C�Y

																// �e���f�ނ̃p�����[�^
	SOUNDPARAM m_aSoundParam[SOUND_LABEL_MAX] =
	{
		{ "data/BGM/Game.wav", -1 },		// BGM0 (OP)
		{ "data/BGM/Tutorial.wav", -1 },	// BGM1	(TUTORIAL)
		{ "data/BGM/Title.wav", -1 },		// BGM2	(GAME)
		{ "data/BGM/Result.wav", 0 },		// BGM3	(RESULT)
		{ "data/BGM/Ranking.wav", -1 },		// BGM5	(RANKING)
		{ "data/SE/Damage.wav", 0 },		// �_���[�W
		{ "data/SE/Idou.wav", 0 },			// �ړ�
		{ "data/SE/Item.wav", 0 },			// �A�C�e��
		{ "data/SE/Jump.wav", 0 },			// �W�����v
		{ "data/SE/Kakudai.wav", 0 },		// �g��
		{ "data/SE/Pause.wav", 0 },			// �|�[�Y
		{ "data/SE/Syukusyou.wav", 0 },			// �|�[�Y
	};
};
#endif
