//=============================================================================
//
// 背景の処理 [bg.h]
// Author : Ozaki
//
//=============================================================================
#ifndef _BG_H_
#define _BG_H_

#include "scene.h"
#include "title.h"
#include "result.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MAX_BG		(3)		// 背景の最大数

//*****************************************************************************
// クラス宣言
//*****************************************************************************
class CScene2D;

class CBg :public CScene
{
public:

	typedef enum
	{
		MODE_TITLE = 0,		// タイトル
		MODE_GAME,			// ゲーム
		MODE_RESULT,		// リザルト
		MODE_GAMEOVER,		// ゲームオーバー
		MODE_RANKING,		// ランキング
		MODE_TUTORIAL,		// チュートリアル
		MODE_MAX
	}MODE;

	CBg();
	~CBg();

	static HRESULT Load(void);	// 読み込み

	static void Unload(void);	// 開放

	static	CBg *Create(D3DXVECTOR3 pos, float widtgh, float height);

	HRESULT Init(D3DXVECTOR3 pos, float widtgh, float height);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// モードの設定
	static void SetMode(MODE mode);

private:

	// モード
	static MODE m_mode;

	// 共有テクスチャへのポインタ
	static LPDIRECT3DTEXTURE9	m_apTexture[MAX_BG];	// 保存する場所
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;

	D3DXVECTOR3					m_move;					//移動量
	CScene2D					*m_apScene2D[MAX_BG];

	float						m_fTex;
protected:

	int							m_nCounterAnim;				//アニメーションカウンター
	int							m_nPatternAnim;				//アニメーションパターン
};
#endif