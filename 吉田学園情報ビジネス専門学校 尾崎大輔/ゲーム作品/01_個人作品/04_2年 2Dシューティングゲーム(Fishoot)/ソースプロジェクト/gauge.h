//=============================================================================
//
//	�Q�[�W�̏��� [gauge.h]
// Author : Ozaki
//
//=============================================================================
#ifndef _GAUGE_H_
#define _GAUGE_H_


#include "scene2D.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_GAUGE				(3)					// �Q�[�W�̍ő吔
#define REDUCE_GAUGE			(0.08f)				// �Q�[�W�̌����(���t���[��)
#define GAUGE_VALUE				(250.0f)			// �Q�[�W�̍ő�l
//*****************************************************************************
// �N���X�錾
//*****************************************************************************
class CRenderer;
class CItem;
class CPlayer;
class CScene2D;

class CGauge : public CScene2D
{
public:
	CGauge();
	~CGauge();

	static HRESULT Load(void);	// �ǂݍ���

	static void Unload(void);	// �J��

	static CGauge *Create(D3DXVECTOR3 pos, float widtgh, float height);

	HRESULT Init(D3DXVECTOR3 pos, float widtgh, float height);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static void AddGauge(float f_itemgauge);

	static float					m_fGauge;							// �Q�[�W�̒l

private:

	static LPDIRECT3DTEXTURE9		m_pTexture[MAX_GAUGE];				// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9			m_pVtxBuff= NULL;					// ���_�o�b�t�@�ւ̃|�C���^
	CScene2D						*m_Scene2D[MAX_GAUGE];
	float							m_fGaugeColR = 1.0f;				// �Q�[�W�̐F(��)
	float							m_fGaugeColG = 0.0f;				// �Q�[�W�̐F(��)
	float							m_fGaugeColB = 0.0f;				// �Q�[�W�̐F(��)
	D3DXVECTOR3						m_move;

};
#endif