//=============================================================================
//
// ライフシーン2D 処理 [lifescene2D.h]
// Author : Ozaki
//
//=============================================================================
#ifndef _LIFESCENE2D_H_
#define _LIFESCENE2D_H_

#include "main.h"

//*****************************************************************************
// クラス宣言
//*****************************************************************************
class CLIfeScene2D
{
public:

	CLIfeScene2D();
	~CLIfeScene2D();

	HRESULT Init(D3DXVECTOR3 pos, float widtgh, float height);
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);

	void SetPosition(D3DXVECTOR3 pos, float rot, float position, float addposition);
	D3DXVECTOR3 GetPosition(void);
	float GetLength(void);
	static CLIfeScene2D *Create(D3DXVECTOR3 pos, float widtgh, float height);
	void BindTexture(LPDIRECT3DTEXTURE9 texture);
	void SetTexture(float TexU, float TexV, int nPatternAnim, int MaxPattern);
	LPDIRECT3DVERTEXBUFFER9 GetVtxBG(void);		// 頂点バッファへのポインタ


protected:

	float					m_Perjudgment;
	float					m_flength;
	float					m_fwidtgh;
	float					m_fheight;
	int						m_nLife;
private:
	LPDIRECT3DTEXTURE9		m_pTexture;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;

	D3DXVECTOR3				m_pos;
};
#endif