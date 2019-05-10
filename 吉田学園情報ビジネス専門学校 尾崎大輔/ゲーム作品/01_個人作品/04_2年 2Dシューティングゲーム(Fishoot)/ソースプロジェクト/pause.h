//=============================================================================
//
// 入力処理 [pause.h]
// Author :  Ozaki
//
//=============================================================================
#ifndef _PAUSESELECT_H_
#define _PAUSESELECT_H_

#include "main.h"
#include "Scene2D.h"
#include "scene.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MAX_Pausecont	(256)	// 最大数
#define	TEXTURE_CONTINUE		"data/TEXTURE/pause000.png"	// 読み込むテクスチャファイル名
#define	TEXTURE_RETRY			"data/TEXTURE/pause001.png"	// 読み込むテクスチャファイル名
#define	TEXTURE_QUIT			"data/TEXTURE/pause002.png"	// 読み込むテクスチャファイル名
#define POLYGON_POS_X			(200)						// 頂点座標Xの移動量
#define POLYGON_POS_Y			(50)						// 頂点座標Yの移動量
#define TEX_POS_X_INIT			(1.0f)						// テクスチャ座標Uの初期位置
#define TEX_POS_Y_INIT			(1.0f)						// テクスチャ座標Vの初期位置
#define TEX_LEFT				(0.0f)						// テクスチャ座標U左
#define TEX_RIGHT				(1.0f)						// テクスチャ座標U右
#define TEX_TOP					(0.0f)						// テクスチャ座標V上
#define TEX_BOT					(1.0f)						// テクスチャ座標V下
#define MAX_PAUSEMENU			(4)							// ポーズの数

//*****************************************************************************
// クラス宣言
//*****************************************************************************

class CPause : public CScene
{
public:

	typedef enum
	{
		SELECTMODE_NONE = 0,
		SELECTMODE_CONTINE,
		SELECTMODE_RETRY,
		SELECTMODE_QUIT,
		SELECTMODE_MAX,
	}PAUSETYPE;

	typedef enum
	{
		SELECTTYPE_NONE = 0,
		SELECTTYPE_SELECT,
		SELECTTYPE_BG,
		SELECTTYPE_MAX
	}SELECT;

	typedef struct
	{
		SELECT		select;		//セレクト
		D3DXVECTOR3 pos;		//位置
		D3DXCOLOR   col;		//カラー

	}PAUSESELECT;

	static HRESULT Load(void);	// 読み込み

	static void Unload(void);	// 開放

	CPause();
	~CPause();

	HRESULT Init(D3DXVECTOR3 pos, float widtgh, float height);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	PAUSETYPE GetPause(void);

	static CPause *Create(D3DXVECTOR3 pos, float widtgh, float height);

private:

	static LPDIRECT3DTEXTURE9	m_pTexture[MAX_PAUSEMENU];					// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff[MAX_PAUSEMENU];							// 頂点バッファへのポインタ
	LPDIRECT3DTEXTURE9			m_pTexturePause = NULL;						// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuffPause = NULL;						// バッファのポインタ
	PAUSESELECT					m_aPauseMenu[MAX_PAUSEMENU];				// ポーズメニュー
	D3DXVECTOR3					m_PauseMenuPos;
	static PAUSETYPE			m_SelectMode;
	int							m_nSelect = 0;
	CScene2D					*m_pScene2D[MAX_PAUSEMENU];
};
#endif

