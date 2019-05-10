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
		SOUND_LABEL_BGM_BOSS,			// BGM3	�{�X
		SOUND_LABEL_BGM_RESULT,			// BGM4	���U���g
		SOUND_LABEL_BGM_GAMEOVER,		// BGM5	�Q�[���I�[�o�[
		SOUND_LABEL_BGM_RANKING,		// BGM6	�����L���O
		SOUND_LABEL_SE_SHOT,			// �e���ˉ�
		SOUND_LABEL_SE_EXPLOSION,		// ������
		SOUND_LABEL_SE_DECISON,			// ���艹
		SOUND_LABEL_SE_SUPERDRY,		// �K�E�Z��
		SOUND_LABEL_SE_DAMAGE,			// �_���[�W��
		SOUND_LABEL_SE_SOSYAKU,			// �𚐉�
		SOUND_LABEL_SE_SERECT,			// �Z���N�g��
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
		{ "data/BGM/Boss.wav", -1 },								// BGM3	�{�X
		{ "data/BGM/bgm002.wav", -1 },								// BGM4	���U���g
		{ "data/BGM/Gameover.wav", -1 },							// BGM5	�Q�[���I�[�o�[
		{ "data/BGM/Ranking.wav", -1 },								// BGM6	�����L���O
		{ "data/SE/bullet.wav",0 },									// �e���ˉ�
		{ "data/SE/bomb1.wav", 0 },									// ������
		{ "data/SE/decision.wav", 0 },								// ���艹
		{ "data/SE/shakin1.wav", 0 },								// �K�E�Z��
		{ "data/SE/hit000.wav", 0 },								// �_���[�W��
		{ "data/SE/sosyaku.wav", 0 },								// �𚐉�
		{ "data/SE/decide000.wav", 0 },								// �Z���N�g��
	};																// �e���f�ނ̃p�����[
};
#endif
