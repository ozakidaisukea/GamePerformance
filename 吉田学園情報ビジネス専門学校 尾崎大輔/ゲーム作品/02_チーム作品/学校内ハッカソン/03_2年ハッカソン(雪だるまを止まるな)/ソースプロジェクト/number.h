//=============================================================================
//
// �����̏��� [number.h]
// Author : Jukiya Hayakawa
//
//=============================================================================
#ifndef _NUMBER_H_
#define _NUMBER_H_

#include "main.h"

#define TEXTURE_NAME008 "data\\TEXTURE\\number001.png"
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CNumber
{
public:
	//�����o�֐�
	CNumber();
	~CNumber();
	HRESULT Init(D3DXVECTOR3 pos, float fWight, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetNumber(int nNumber);
	void SetCol(D3DXCOLOR col);

	//�ÓI�����o�֐�
	static CNumber *Create(D3DXVECTOR3 pos, float fWight, float fHeight);
	static HRESULT Load(void);
	static void Unload(void);

private:
	static LPDIRECT3DTEXTURE9			m_pTexture;	// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9				m_pVtxBuff;	// ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3							m_pos;				// �ʒu
	D3DXCOLOR							m_col;		//�F

protected:
};
#endif