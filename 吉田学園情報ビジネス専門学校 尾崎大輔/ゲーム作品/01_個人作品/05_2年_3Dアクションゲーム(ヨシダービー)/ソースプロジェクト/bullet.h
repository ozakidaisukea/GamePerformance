//=============================================================================
//
// bullet処理 [bullet.h]
// Author : Ozaki
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"
#include "scene.h"
#include "billboard.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define		MAX_FOER		(4)
#define		MAX_BILLBOARD	(20)

//*****************************************************************************
// クラス宣言
//*****************************************************************************
class CBullet : public CBillboard
{
public:

	CBullet(int nPriority, OBJTYPE objtype = CScene::OBJTYPE_BULLET);
	~CBullet();

	HRESULT Init(void);
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);
	void	BindTexture(LPDIRECT3DTEXTURE9 texture);
	static CBullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move);

private:

	float							m_position = 0.0f;
	float							m_Addposition = 1.0f;

	static LPDIRECT3DTEXTURE9		m_pTexture;
	LPDIRECT3DVERTEXBUFFER9			m_pVtxBuff;

	int								m_nLife;		// 表示時間(寿命)
	D3DXVECTOR3						m_move;			// 移動量
	D3DXVECTOR3						m_pos;			// 位置
	D3DXVECTOR3						m_rot;			// 向き
	D3DXVECTOR3						m_movve;		// 動き
	D3DXMATRIX						m_mtxWorld;		// ワールドマトリックス
	D3DXVECTOR3						m_aPos[4];
	D3DXVECTOR3						m_VecA;
	D3DXVECTOR3						m_VecB;
	D3DXVECTOR3						m_VecC;
	bool							m_bUse;			// 使用してるかしてないか

};
#endif