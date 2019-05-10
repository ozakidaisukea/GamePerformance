//=============================================================================
//
// タイトル処理 [title.h]
// Author : Ozaki
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

#include "scene2D.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define Title_WIDTH		(SCREEN_WIDTH)
#define Title_HEIGHT	(SCREEN_HEIGHT)

//*****************************************************************************
// クラス宣言
//*****************************************************************************
class CFade;
class CSound;
class CGimmick;
class CCamera;
class CLight;
class CMeshFiled;
class CScene2D;
class CPlayer;
class CHorse2;
class CHorse3;
class CHorse4;
class CHorse5;
class CHorse6;
class CHorse7;
class CHorse8;
class CHorse9;
class CHorse10;
class CJockey;
class CJockey2;
class CJockey3;
class CJockey4;
class CJockey5;
class CJockey6;
class CJockey7;
class CJockey8;
class CJockey9;
class CJockey10;
class CUnion;
class CLogo;
class CPressEntor;
class CInputjoypad;

class CTitle
{
public:

	CTitle();
	~CTitle();

	void Load(void);	// 読み込み

	void Unload(void);	// 開放

	static CTitle *Create(void);

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// カメラ
	static CCamera *GetCamera(void);

	// ライト
	static CLight *GetLight(void);

	// フィールド
	static CMeshFiled *GetMeshFiled(void);

	static CUnion *GetUnion(void);

	static CLogo *GetLogo(void);

	static CPressEntor *GetEntor(void);

	// 馬
	static CPlayer *GetPlayer(void);
	// 馬
	static CHorse2 *GetHorse2(void);
	// 馬
	static CHorse3 *GetHorse3(void);
	// 馬
	static CHorse4 *GetHorse4(void);
	// 馬
	static CHorse5 *GetHorse5(void);
	// 馬
	static CHorse6 *GetHorse6(void);
	// 馬
	static CHorse7 *GetHorse7(void);
	// 馬
	static CHorse8 *GetHorse8(void);
	// 馬
	static CHorse9 *GetHorse9(void);
	// 馬
	static CHorse10 *GetHorse10(void);

	// ジョッキー
	static CJockey *GetJockey(void);
	// ジョッキー
	static CJockey2 *GetJockey2(void);
	// ジョッキー
	static CJockey3 *GetJockey3(void);
	// ジョッキー
	static CJockey4 *GetJockey4(void);
	// ジョッキー
	static CJockey5 *GetJockey5(void);
	// ジョッキー
	static CJockey6 *GetJockey6(void);
	// ジョッキー
	static CJockey7 *GetJocke7(void);
	// ジョッキー
	static CJockey8 *GetJocke8(void);
	// ジョッキー
	static CJockey9 *GetJockey9(void);
	// ジョッキー
	static CJockey10 *GetJockey10(void);
	// オーナー
	//static COwner *GetOwner(void);

private:

	// カメラ
	static CCamera *m_pCamera;

	// ライト
	static CLight *m_pLight;

	// フィールド
	static CMeshFiled *m_pMeshFiled;

	static CUnion *m_pUnion;

	static CLogo *m_pLogo;

	// 馬
	static CPlayer *m_pPlayer;
	// 馬
	static CHorse2 *m_pHorse2;
	// 馬
	static CHorse3 *m_pHorse3;
	// 馬
	static CHorse4 *m_pHorse4;
	// 馬
	static CHorse5 *m_pHorse5;
	// 馬
	static CHorse6 *m_pHorse6;
	// 馬
	static CHorse7 *m_pHorse7;
	// 馬
	static CHorse8 *m_pHorse8;
	// 馬
	static CHorse9 *m_pHorse9;
	// 馬
	static CHorse10 *m_pHorse10;

	// ジョッキー
	static CJockey *m_pJockey;
	// ジョッキー
	static CJockey2 *m_pJockey2;
	// ジョッキー
	static CJockey3 *m_pJockey3;
	// ジョッキー
	static CJockey4 *m_pJockey4;
	// ジョッキー
	static CJockey5 *m_pJockey5;
	// ジョッキー
	static CJockey6 *m_pJockey6;
	// ジョッキー
	static CJockey7 *m_pJockey7;
	// ジョッキー
	static CJockey8 *m_pJockey8;
	// ジョッキー
	static CJockey9 *m_pJockey9;
	// ジョッキー
	static CJockey10 *m_pJockey10;

	// サウンド
	static CSound						*m_pSound;

	// プレスエンター
	static CPressEntor *m_pPressEntor;

	int									m_Titletimer;
	D3DXVECTOR3							m_move;
	static LPDIRECT3DTEXTURE9			m_pTexture;
	static LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;
	int									m_nTime;
};
#endif

