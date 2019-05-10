//=============================================================================
//
// 弾の処理 [bullet.h]
// Author : Ozaki
//
//=============================================================================
#pragma once
#ifndef _BULLET_H_
#define _BULLET_H_

#include "scene2D.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MAX_BULLET		(256)		// 弾の最大数
#define ADD_POSITION	(50)
#define MAX_TEXBULLET	(4)
//#define MAX_PRIORITY1	(8)
//*****************************************************************************
// クラス宣言
//*****************************************************************************
class CPlayer;
class CExplosion;
class CEnemy;
class CEffect;
class CScore;

class CBullet : public CScene2D //CPlayer
{
public:

	//弾の種類
	typedef enum
	{
		BULLETTYPE_PLAYER = 0,		//プレイヤーの弾
		BULLETTYPE_AMI,				//敵の弾
		BULLETTYPE_MORI,
		BULLETTYPE_TURIZAO,
		BULLETTYPE_MAX,
	}BULLETTYPE;

	CBullet();
	~CBullet();

	static HRESULT Load(void);	// 読み込み

	static void Unload(void);	// 開放

	static	CBullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float widtgh, float height, BULLETTYPE type);

	HRESULT Init(D3DXVECTOR3 pos,D3DXVECTOR3 move, float widtgh, float height, BULLETTYPE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:

	// 爆発
	static CExplosion				*m_pExplosion;

	// スコア
	static CScore *m_pScore;

	// 共有テクスチャへのポインタ
	static LPDIRECT3DTEXTURE9		m_pTexture[MAX_TEXBULLET];				// 保存する場所
	LPDIRECT3DVERTEXBUFFER9			m_pVtxBuffBullet = NULL;			    // 頂点バッファへのポインタ
	D3DXVECTOR3						m_move;									// 移動量
	BULLETTYPE						m_type;

	float							m_rot = 0.0f;
	float							m_position = 0.0f;
	float							m_Addposition = 1.0f;
	int								m_CountState;

protected:

	float							m_fLength = 0.0f;
};
#endif