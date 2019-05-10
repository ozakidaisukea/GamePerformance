//=============================================================================
//
// �r���{�[�h�̏��� [billboard.h]
// Author : Jukiya Hayakawa
//
//=============================================================================
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

#include "main.h"
#include "scene.h"
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CBillboard : public CScene
{
public:
	//�����o�֐�
	CBillboard(int nPriority = 4, OBJTYPE objtype = OBJTYPE_BILLBOARD);
	~CBillboard();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void BindTexture(LPDIRECT3DTEXTURE9 texture);
	void SetPos(D3DXVECTOR3 pos);
	void SetRot(D3DXVECTOR3 rot);
	void SetWidth(float fWidth);
	void SetHeight(float fHwight);
	void SetmtxParent(D3DXMATRIX* mtxParent);
	D3DXVECTOR3 GetPos(void);
	float GetHeight(void);
	float GetWidth(void);
	D3DXVECTOR3 GetRot(void);
	//�ÓI�����o�֐�
	static CBillboard *Create(void);
private:
	//�����o�ϐ�
	D3DXVECTOR3 m_pos;			//�ʒu
	float		m_fWidth;		//��
	float		m_fHeight;		//����
	D3DXVECTOR3 m_rot;			//����
	D3DXMATRIX	m_mtxWorld;		//���[���h�}�g���b�N�X
	D3DXMATRIX*	m_mtxParent;	//�e�}�g���b�N�X

								//�ÓI�����o�ϐ�
	LPDIRECT3DTEXTURE9			m_pTexture = NULL;	// �e�N�X�`���ւ̃|�C���^

};
#endif
