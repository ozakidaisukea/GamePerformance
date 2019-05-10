//=============================================================================
//
// ロゴの処理 [logo.h]
// Author : Ozaki
//
//=============================================================================
#ifndef _LOGO_H_
#define _LOGO_H_

#include "scene2D.h"
#include "scene.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_LOGO (5)

//*****************************************************************************
// クラス宣言
//*****************************************************************************
class CLogo : public CScene2D
{
public:
	CLogo();
	~CLogo();

	typedef enum
	{
		LOGO_TITLE = 0,		// タイトル
		LOGO_RESECARD,		// 出馬表
		LOGO_TUTORIAL,		// チュートリアル
		LOGO_RESULT,		// リザルト
		LOGO_PRESSENTOR,	// プレスエンター
		ENEMY_MAX
	}LOGO_TYPE;

	typedef enum
	{
		LOGOSTATE_NONE = 0,		//初期状態
		LOGOSTATE_NORMAL,		//通常
		LOGOSTATE_MOVE,			//動く
		LOGOSTATE_MAX,			//最大数
	}LOGOSTATE;

	static HRESULT Load(void);	// 読み込み

	static void Unload(void);	// 開放

	HRESULT Init(D3DXVECTOR3 pos, float widtgh, float height, LOGO_TYPE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static	CLogo *Create(D3DXVECTOR3 pos, float widtgh, float height, LOGO_TYPE type);

private:

	D3DXVECTOR3				m_pos;							// 位置
	D3DXVECTOR3				m_move;							// 移動量
	float					m_rot = 0.0f;
	float					m_position = 0.0f;
	float					m_Addposition = 1.0f;
	LOGO_TYPE				m_Type;							// タイプ
	LOGOSTATE				m_State;
	float					m_widtgh;						// 横
	float					m_height;						// 縦
															// プレスエンター
	int						m_nCntEnter;
	float					m_fEnterTimer;


	// 共有テクスチャへのポインタ
	static LPDIRECT3DTEXTURE9	m_pTexture[MAX_LOGO];		// 保存する場所

	CScene2D					*m_apScene2D;

protected:

	float						m_Perjudgment;
};
#endif