//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : Ozaki
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//=============================================================================
//	�T�E���h�N���X
//=============================================================================
class CSound
{
public:
	typedef struct
	{
		char *pFilename;	// �t�@�C����
		int nCntLoop;		// ���[�v�J�E���g(-1�Ń��[�v�Đ�)
	} SOUNDPARAM;

	typedef enum
	{// �T�E���h�t�@�C��
		SOUND_LABEL_BGM_TITLE = 0,		// BGM0 �^�C�g��
		SOUND_LABEL_BGM_TUTORIAL,		// BGM1 �`���[�g���A��
		SOUND_LABEL_BGM_GAME,			// BGM2 �Q�[��
		SOUND_LABEL_BGM_RESULT,			// BGM3	���U���g
		SOUND_LABEL_SE_DECISON1,		// SE0 ���艹1 [�^�C�g��]
		SOUND_LABEL_SE_DECISON2,		// SE1 ���艹2 [�`���[�g���A��]
	//	SOUND_LABEL_SE_DECISON,			// SE2 ���艹
		SOUND_LABEL_SE_OUEN,			// SE3 ����
		SOUND_LABEL_MAX,
	} SOUND_LABEL;

	CSound();						//	�R���X�g���N�^
	~CSound();						//	�f�X�g���N�^

	 HRESULT InitSound(HWND hWnd);
	 void UninitSound(void);
	 HRESULT PlaySound(SOUND_LABEL label);
	void StopSound(SOUND_LABEL label);
	void StopSound(void);
	 HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	 HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

private:

	 IXAudio2 *m_pXAudio2;											// XAudio2�I�u�W�F�N�g�ւ̃|�C���^
	 IXAudio2MasteringVoice *m_pMasteringVoice;						// �}�X�^�[�{�C�X�ւ̃|�C���^
	 IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX] = {};	// �\�[�X�{�C�X�ւ̃|�C���^
	 BYTE *m_apDataAudio[SOUND_LABEL_MAX] = {};						// �I�[�f�B�I�f�[�^�ւ̃|�C���^
	 DWORD m_aSizeAudio[SOUND_LABEL_MAX] = {};						// �I�[�f�B�I�f�[�^�T�C�Y

	SOUNDPARAM m_aSoundParam[CSound::SOUND_LABEL_MAX] =
	{
		{ "data/BGM/Title.wav", -1 },								// BGM0 �^�C�g��
		{ "data/BGM/Tutorial.wav", -1 },							// BGM1	�`���[�g���A��
		{ "data/BGM/Game.wav", -1 },								// BGM2	�Q�[��
		{ "data/BGM/Result.wav", -1 },								// BGM4	���U���g
		{ "data/SE/Entor.wav", 0 },									// ���艹1 [�^�C�g��]
		{ "data/SE/tutoentor.wav", 0 },								// ���艹2 [�`���[�g���A��]
		{ "data/SE/ouenn.wav", 0 },									// ����
	};																// �e���f�ނ̃p�����[
};
#endif
