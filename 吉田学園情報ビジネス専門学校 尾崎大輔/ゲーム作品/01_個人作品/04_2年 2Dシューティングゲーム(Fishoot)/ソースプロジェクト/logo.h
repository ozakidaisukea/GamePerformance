//=============================================================================
//
// ロゴの処理 [logo.h]
// Author : Ozaki
//
//=============================================================================
#ifndef _LOGO_H_
#define _LOGO_H_

#include "scene2D.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_LOGO (14)

//*****************************************************************************
// クラス宣言
//*****************************************************************************
class CScene2D;

class CLogo : public CScene2D
{
public:
	CLogo();
	~CLogo();

	typedef enum
	{
		LOGO_TITLE = 0,
		LOGO_TUTORIAL,
		LOGO_RESULT,
		LOGO_GAMEOVER,
		LOGO_RANKING,
		LOGO_SYAKE,
		LOGO_TUTORIALHAKASE,
		LOGO_RANKINGNUMBER,
		LOGO_1,
		LOGO_2,
		LOGO_3,
		LOGO_4,
		LOGO_5,
		LOGO_SOUSA,
		ENEMY_MAX
	}LOGO_TYPE;

	static HRESULT Load(void);	// 読み込み

	static void Unload(void);	// 開放

	HRESULT Init(D3DXVECTOR3 pos, float widtgh,float height, LOGO_TYPE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static	CLogo *Create(D3DXVECTOR3 pos, float widtgh, float height, LOGO_TYPE type);

private:

	D3DXVECTOR3				m_move;							// 移動量
	float					m_rot = 0.0f;
	float					m_position = 0.0f;
	float					m_Addposition = 1.0f;
	LOGO_TYPE				m_Type;

	// 共有テクスチャへのポインタ
	static LPDIRECT3DTEXTURE9	m_pTexture[MAX_LOGO];		// 保存する場所
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff = NULL;			// 頂点バッファへのポインタ

	CScene2D					*m_apScene2D[MAX_LOGO];

protected:

	float						m_Perjudgment;
};
#endif