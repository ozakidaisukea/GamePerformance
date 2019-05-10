//=============================================================================
//
// ���S���̏��� [logosyake.h]
// Author : Ozaki
//
//=============================================================================
#ifndef _LOGOSYAKE_H_
#define _LOGOSYAKE_H_

#include "scene2D.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_SYAKE	(4)

//*****************************************************************************
// �N���X�錾
//*****************************************************************************
class CScene2D;

class CLogosyake : public CScene2D
{
public:

	typedef enum
	{
		SYAKE_LOGO = 0,
		SYAKE_DEATH,
		SYAKE_RESULT,
		SYAKE_GAMEOVER,
		ENEMY_MAX
	}SYAKE_TYPE;

	CLogosyake();
	~CLogosyake();

	static HRESULT Load(void);	// �ǂݍ���

	static void Unload(void);	// �J��

	HRESULT Init(D3DXVECTOR3 pos, float widtgh, float height,D3DXVECTOR3 move,SYAKE_TYPE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static	CLogosyake *Create(D3DXVECTOR3 pos, float widtgh, float height, D3DXVECTOR3 move, SYAKE_TYPE type);

private:
	D3DXVECTOR3				m_move;

	float					m_rot = 0.0f;
	float					m_position = 0.0f;
	float					m_Addposition = 1.0f;
	SYAKE_TYPE				m_Type;

	// ���L�e�N�X�`���ւ̃|�C���^
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_SYAKE];	// �ۑ�����ꏊ

	CScene2D					*m_apScene2D;

protected:

	float					m_Perjudgment;
};
#endif