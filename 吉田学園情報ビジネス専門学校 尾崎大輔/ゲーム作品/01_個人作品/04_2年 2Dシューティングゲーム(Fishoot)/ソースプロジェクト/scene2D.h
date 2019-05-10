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

	CScene2D(int nPriority);
	~CScene2D();

	HRESULT Init(D3DXVECTOR3 pos, float widtgh, float height);
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);

	void SetPosition(D3DXVECTOR3 pos, float rot,float position,float addposition);
	D3DXVECTOR3 GetPosition(void);
	//float GetLength(void);
	float GetWidth(void);
	float GetHeigth(void);
	static CScene2D *Create(D3DXVECTOR3 pos, float widtgh, float height);
	void BindTexture(LPDIRECT3DTEXTURE9 texture);
	void SetTexture(float TexU, float TexV,int nPatternAnim,int MaxPattern);
	LPDIRECT3DVERTEXBUFFER9 GetVtxBG(void);		// 頂点バッファへのポインタ

	void SetColor(D3DXCOLOR col);


protected:

	float					m_Perjudgment;
	float					m_flength;
	float					m_widtgh;
	float					m_height;
	int						m_nLife;
	D3DXCOLOR				m_col;
private:

	LPDIRECT3DTEXTURE9		m_pTexture;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;

	D3DXVECTOR3				m_pos;
};
#endif