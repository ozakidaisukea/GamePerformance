//=============================================================================
//
// レンダリング処理 [renderer.h]
// Author : Ozaki
//
//=============================================================================
#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "main.h"

//*****************************************************************************
// クラス宣言
//*****************************************************************************
class CDebugProc;
class CPause;

class CRenderer
{
public:

	CRenderer();
	~CRenderer();

	HRESULT Init(HWND hWnd, bool bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	LPDIRECT3DDEVICE9 GetDevice(void); /*{ return m_pD3DDevice; }*/
	static CDebugProc *GetDebug(void);

private:

	void DrawFPS(void);

	LPDIRECT3D9				m_pD3D = NULL;			// Direct3Dオブジェクト
	LPDIRECT3DDEVICE9		m_pD3DDevice = NULL;	// Deviceオブジェクト(描画に必要)
	LPDIRECT3DTEXTURE9		m_pTexture = NULL;		// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;		// 頂点バッファへのポインタ

	D3DXVECTOR3				m_posPolygon;			// ポリゴンの位置

	float					m_rot = 0.0f;
	float					m_position = 0.0f;
	float					m_Addposition = 1.0f;
	LPD3DXFONT				m_pFont = NULL;			// フォントへのポインタ
	int						m_nCountFPS;			// FPSカウンタ
	static	CDebugProc		*m_pDebugProc;
	bool					m_bPause;
	static  CPause			*m_pPause;
	bool					m_bUse;
};
#endif