//=============================================================================
//
// サウンド処理 [sound.h]
// Author : Ozaki
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//=============================================================================
//	サウンドクラス
//=============================================================================
class CSound
{
public:
	typedef struct
	{
		char *pFilename;	// ファイル名
		int nCntLoop;		// ループカウント(-1でループ再生)
	} SOUNDPARAM;

	typedef enum
	{// サウンドファイル
		SOUND_LABEL_BGM_TITLE = 0,		// BGM0 タイトル
		SOUND_LABEL_BGM_TUTORIAL,		// BGM1 チュートリアル
		SOUND_LABEL_BGM_GAME,			// BGM2 ゲーム
		SOUND_LABEL_BGM_RESULT,			// BGM3	リザルト
		SOUND_LABEL_SE_DECISON1,		// SE0 決定音1 [タイトル]
		SOUND_LABEL_SE_DECISON2,		// SE1 決定音2 [チュートリアル]
	//	SOUND_LABEL_SE_DECISON,			// SE2 決定音
		SOUND_LABEL_SE_OUEN,			// SE3 応援
		SOUND_LABEL_MAX,
	} SOUND_LABEL;

	CSound();						//	コンストラクタ
	~CSound();						//	デストラクタ

	 HRESULT InitSound(HWND hWnd);
	 void UninitSound(void);
	 HRESULT PlaySound(SOUND_LABEL label);
	void StopSound(SOUND_LABEL label);
	void StopSound(void);
	 HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	 HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

private:

	 IXAudio2 *m_pXAudio2;											// XAudio2オブジェクトへのポインタ
	 IXAudio2MasteringVoice *m_pMasteringVoice;						// マスターボイスへのポインタ
	 IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX] = {};	// ソースボイスへのポインタ
	 BYTE *m_apDataAudio[SOUND_LABEL_MAX] = {};						// オーディオデータへのポインタ
	 DWORD m_aSizeAudio[SOUND_LABEL_MAX] = {};						// オーディオデータサイズ

	SOUNDPARAM m_aSoundParam[CSound::SOUND_LABEL_MAX] =
	{
		{ "data/BGM/Title.wav", -1 },								// BGM0 タイトル
		{ "data/BGM/Tutorial.wav", -1 },							// BGM1	チュートリアル
		{ "data/BGM/Game.wav", -1 },								// BGM2	ゲーム
		{ "data/BGM/Result.wav", -1 },								// BGM4	リザルト
		{ "data/SE/Entor.wav", 0 },									// 決定音1 [タイトル]
		{ "data/SE/tutoentor.wav", 0 },								// 決定音2 [チュートリアル]
		{ "data/SE/ouenn.wav", 0 },									// 応援
	};																// 各音素材のパラメー
};
#endif
