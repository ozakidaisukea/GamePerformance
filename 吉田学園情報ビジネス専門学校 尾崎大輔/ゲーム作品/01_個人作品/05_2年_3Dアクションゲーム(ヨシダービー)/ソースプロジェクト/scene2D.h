//=============================================================================
//
// シーン2D 処理 [scene2D.h]
// Author : Ozaki
//
//=============================================================================
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

#include "main.h"
#include "scene.h"
//*****************************************************************************
// クラス宣言
//*****************************************************************************
class CScene2D : public CScene
{
public:

	CScene2D(int nPriority,OBJTYPE objtype = CScene::OBJTYPE_2D);
	~CScene2D();

	HRESULT Init(void);
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);
	void	BindTexture(LPDIRECT3DTEXTURE9 texture);
	LPDIRECT3DTEXTURE9	GetTexture(void);
	static CScene2D *Create(D3DXVECTOR3 pos, float width, float height);

	LPDIRECT3DVERTEXBUFFER9 GetVtxBG(void);
	D3DXVECTOR3 GetPos(void);
	void SetPosition(D3DXVECTOR3 pos, float frot, float position, float addposition);
	void SetWidth(float width);
	void Setheight(float height);
	void SetColor(D3DXCOLOR col);
	void SetTexture(float TexU, float TexV, int nPatternAnim, int MaxPattern);

private:

	float							m_rot = 0.0f;
	float							m_position = 0.0f;
	float							m_Addposition = 1.0f;

	LPDIRECT3DTEXTURE9		m_pTexture;
	LPDIRECT3DVERTEXBUFFER9			m_pVtxBuff;

	D3DXVECTOR3						m_pos;
	float							m_width;		// 横
	float							m_height;		// 縦
	float							m_Perjudgment;
	float							m_flength;
protected:
	D3DXCOLOR						m_col;
};
#endif