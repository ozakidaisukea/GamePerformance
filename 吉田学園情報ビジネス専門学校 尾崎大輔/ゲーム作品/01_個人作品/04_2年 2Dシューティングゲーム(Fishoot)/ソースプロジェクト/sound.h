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
		SOUND_LABEL_BGM_BOSS,			// BGM3	ボス
		SOUND_LABEL_BGM_RESULT,			// BGM4	リザルト
		SOUND_LABEL_BGM_GAMEOVER,		// BGM5	ゲームオーバー
		SOUND_LABEL_BGM_RANKING,		// BGM6	ランキング
		SOUND_LABEL_SE_SHOT,			// 弾発射音
		SOUND_LABEL_SE_EXPLOSION,		// 爆発音
		SOUND_LABEL_SE_DECISON,			// 決定音
		SOUND_LABEL_SE_SUPERDRY,		// 必殺技音
		SOUND_LABEL_SE_DAMAGE,			// ダメージ音
		SOUND_LABEL_SE_SOSYAKU,			// 咀嚼音
		SOUND_LABEL_SE_SERECT,			// セレクト音
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
		{ "data/BGM/Boss.wav", -1 },								// BGM3	ボス
		{ "data/BGM/bgm002.wav", -1 },								// BGM4	リザルト
		{ "data/BGM/Gameover.wav", -1 },							// BGM5	ゲームオーバー
		{ "data/BGM/Ranking.wav", -1 },								// BGM6	ランキング
		{ "data/SE/bullet.wav",0 },									// 弾発射音
		{ "data/SE/bomb1.wav", 0 },									// 爆発音
		{ "data/SE/decision.wav", 0 },								// 決定音
		{ "data/SE/shakin1.wav", 0 },								// 必殺技音
		{ "data/SE/hit000.wav", 0 },								// ダメージ音
		{ "data/SE/sosyaku.wav", 0 },								// 咀嚼音
		{ "data/SE/decide000.wav", 0 },								// セレクト音
	};																// 各音素材のパラメー
};
#endif
