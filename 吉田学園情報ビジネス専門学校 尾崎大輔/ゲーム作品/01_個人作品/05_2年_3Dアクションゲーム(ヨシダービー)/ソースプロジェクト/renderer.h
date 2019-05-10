//=============================================================================
//
// �����_�����O���� [renderer.h]
// Author : Ozaki
//
//=============================================================================
#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "main.h"

//*****************************************************************************
// �N���X�錾
//*****************************************************************************
class CDebugProc;
class CPause;

class CRenderer
{
public:

	CRenderer();
	~CRenderer();

	HRESULT Init(HWND hWnd, bool bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	LPDIRECT3DDEVICE9 GetDevice(void); /*{ return m_pD3DDevice; }*/
	static CDebugProc *GetDebug(void);

private:

	void DrawFPS(void);

	LPDIRECT3D9				m_pD3D = NULL;			// Direct3D�I�u�W�F�N�g
	LPDIRECT3DDEVICE9		m_pD3DDevice = NULL;	// Device�I�u�W�F�N�g(�`��ɕK�v)
	LPDIRECT3DTEXTURE9		m_pTexture = NULL;		// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;		// ���_�o�b�t�@�ւ̃|�C���^

	D3DXVECTOR3				m_posPolygon;			// �|���S���̈ʒu

	float					m_rot = 0.0f;
	float					m_position = 0.0f;
	float					m_Addposition = 1.0f;
	LPD3DXFONT				m_pFont = NULL;			// �t�H���g�ւ̃|�C���^
	int						m_nCountFPS;			// FPS�J�E���^
	static	CDebugProc		*m_pDebugProc;
	bool					m_bPause;
	static  CPause			*m_pPause;
	bool					m_bUse;
};
#endif