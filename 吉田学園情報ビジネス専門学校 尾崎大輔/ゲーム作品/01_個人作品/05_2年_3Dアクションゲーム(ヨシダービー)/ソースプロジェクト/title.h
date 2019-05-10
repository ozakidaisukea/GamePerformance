//=============================================================================
//
// �^�C�g������ [title.h]
// Author : Ozaki
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

#include "scene2D.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define Title_WIDTH		(SCREEN_WIDTH)
#define Title_HEIGHT	(SCREEN_HEIGHT)

//*****************************************************************************
// �N���X�錾
//*****************************************************************************
class CFade;
class CSound;
class CGimmick;
class CCamera;
class CLight;
class CMeshFiled;
class CScene2D;
class CPlayer;
class CHorse2;
class CHorse3;
class CHorse4;
class CHorse5;
class CHorse6;
class CHorse7;
class CHorse8;
class CHorse9;
class CHorse10;
class CJockey;
class CJockey2;
class CJockey3;
class CJockey4;
class CJockey5;
class CJockey6;
class CJockey7;
class CJockey8;
class CJockey9;
class CJockey10;
class CUnion;
class CLogo;
class CPressEntor;
class CInputjoypad;

class CTitle
{
public:

	CTitle();
	~CTitle();

	void Load(void);	// �ǂݍ���

	void Unload(void);	// �J��

	static CTitle *Create(void);

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �J����
	static CCamera *GetCamera(void);

	// ���C�g
	static CLight *GetLight(void);

	// �t�B�[���h
	static CMeshFiled *GetMeshFiled(void);

	static CUnion *GetUnion(void);

	static CLogo *GetLogo(void);

	static CPressEntor *GetEntor(void);

	// �n
	static CPlayer *GetPlayer(void);
	// �n
	static CHorse2 *GetHorse2(void);
	// �n
	static CHorse3 *GetHorse3(void);
	// �n
	static CHorse4 *GetHorse4(void);
	// �n
	static CHorse5 *GetHorse5(void);
	// �n
	static CHorse6 *GetHorse6(void);
	// �n
	static CHorse7 *GetHorse7(void);
	// �n
	static CHorse8 *GetHorse8(void);
	// �n
	static CHorse9 *GetHorse9(void);
	// �n
	static CHorse10 *GetHorse10(void);

	// �W���b�L�[
	static CJockey *GetJockey(void);
	// �W���b�L�[
	static CJockey2 *GetJockey2(void);
	// �W���b�L�[
	static CJockey3 *GetJockey3(void);
	// �W���b�L�[
	static CJockey4 *GetJockey4(void);
	// �W���b�L�[
	static CJockey5 *GetJockey5(void);
	// �W���b�L�[
	static CJockey6 *GetJockey6(void);
	// �W���b�L�[
	static CJockey7 *GetJocke7(void);
	// �W���b�L�[
	static CJockey8 *GetJocke8(void);
	// �W���b�L�[
	static CJockey9 *GetJockey9(void);
	// �W���b�L�[
	static CJockey10 *GetJockey10(void);
	// �I�[�i�[
	//static COwner *GetOwner(void);

private:

	// �J����
	static CCamera *m_pCamera;

	// ���C�g
	static CLight *m_pLight;

	// �t�B�[���h
	static CMeshFiled *m_pMeshFiled;

	static CUnion *m_pUnion;

	static CLogo *m_pLogo;

	// �n
	static CPlayer *m_pPlayer;
	// �n
	static CHorse2 *m_pHorse2;
	// �n
	static CHorse3 *m_pHorse3;
	// �n
	static CHorse4 *m_pHorse4;
	// �n
	static CHorse5 *m_pHorse5;
	// �n
	static CHorse6 *m_pHorse6;
	// �n
	static CHorse7 *m_pHorse7;
	// �n
	static CHorse8 *m_pHorse8;
	// �n
	static CHorse9 *m_pHorse9;
	// �n
	static CHorse10 *m_pHorse10;

	// �W���b�L�[
	static CJockey *m_pJockey;
	// �W���b�L�[
	static CJockey2 *m_pJockey2;
	// �W���b�L�[
	static CJockey3 *m_pJockey3;
	// �W���b�L�[
	static CJockey4 *m_pJockey4;
	// �W���b�L�[
	static CJockey5 *m_pJockey5;
	// �W���b�L�[
	static CJockey6 *m_pJockey6;
	// �W���b�L�[
	static CJockey7 *m_pJockey7;
	// �W���b�L�[
	static CJockey8 *m_pJockey8;
	// �W���b�L�[
	static CJockey9 *m_pJockey9;
	// �W���b�L�[
	static CJockey10 *m_pJockey10;

	// �T�E���h
	static CSound						*m_pSound;

	// �v���X�G���^�[
	static CPressEntor *m_pPressEntor;

	int									m_Titletimer;
	D3DXVECTOR3							m_move;
	static LPDIRECT3DTEXTURE9			m_pTexture;
	static LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;
	int									m_nTime;
};
#endif

