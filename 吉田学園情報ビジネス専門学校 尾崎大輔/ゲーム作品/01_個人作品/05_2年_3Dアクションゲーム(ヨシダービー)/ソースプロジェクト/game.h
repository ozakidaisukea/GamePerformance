//=============================================================================
//
// �Q�[������ [game.h]
// Author : Ozaki
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"
#include "scene2D.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define GAME_WIDTH		(SCREEN_WIDTH)
#define GAME_HEIGHT		(SCREEN_HEIGHT)
#define MAX_ENEMY		(5)
#define MAX_GAUGE		(3)
#define ENEMYLIFE_NO1	(3)
#define ENEMYLIFE_NO2	(5)
#define ENEMYLIFE_NO3	(10)
#define ENEMYLIFE_NO4	(15)
#define ENEMYLIFE_NO5	(20)

//*****************************************************************************
// �N���X�錾
//*****************************************************************************
class CBullet;
class CRenderer;
class CInputKeyboard;
class CPlayer;
class CEnemy;
class CCamera;
class CLight;
class CFade;
class CMeshFiled;
class CWall;
class CObjectBG;
class CStarter;
class CHorse;
class CHorse2;
class CHorse3;
class CHorse4;
class CHorse5;
class CHorse6;
class CHorse7;
class CHorse8;
class CHorse9;
class CHorse10;
class CGate;
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
class COwner;
class CUnion;
class CScene3D;
class CLogo;
class CInputjoypad;
class CGauge;

class CGame
{
public:

	typedef enum
	{
		STATE_NONE = 0,			//�������Ă��Ȃ����
		STATE_NORMAL,			//�ʏ���
		STATE_RESULT,			//�I�����
		STATE_GAMEOVER,
		STATE_MAX,
	}STATE;

	CGame();
	~CGame();

	HRESULT Load(void);	// �ǂݍ���

	void Unload(void);	// �J��

	static CGame *Create(void);

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �v���C���[
	static CPlayer *GetPlayer(void);

	// �G
	static CEnemy *GetEnemy(void);

	// �n
	static CHorse *GetHorse(void);
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


	// �J����
	static CCamera *GetCamera(void);

	// ���C�g
	static CLight *GetLight(void);

	// ���b�V���t�B�[���h
	static CMeshFiled *GetMeshFiled(void);

	// ��
	static CWall *GetWall(void);

	// �I�u�W�F�N�g�w�i
	static CObjectBG *GetObjectbg(void);

	// �X�^�[�^�[
	static CStarter *GetStarter(void);

	// �Q�[�g
	static CGate *GetGate(void);

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
	static COwner *GetOwner(void);

	// ����
	static CUnion *GetUnion(void);

	// �V�[��3D
	static CScene3D *GetScene3D(void);

	static CLogo *GetLogo(void);

	// �Q�[�W
	static CGauge *GetGauge(void);

	static int	GetTime(void);

private:

	// �v���C���[
	static CPlayer *m_pPlayer;

	// �G
	static CEnemy *m_pEnemy;

	// �J����
	static CCamera *m_pCamera;

	// ���C�g
	static CLight *m_pLight;

	// ���b�V���t�B�[���h
	static CMeshFiled *m_pMeshField;

	// ��
	static CWall *m_pWall;

	// �I�u�W�F�N�g�w�i
	static CObjectBG *m_pObjectbg;

	// �X�^�[�^�[
	static CStarter *m_pStarter;

	// �n
	static CHorse *m_pHorse;
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

	// �Q�[�g
	static CGate *m_pGate;

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

	// ���S
	static CLogo *m_pLogo;

	// �I�[�i�[
	static COwner *m_pOwner;

	// ����
	static CUnion *m_pUnion;

	// �V�[��3D
	static CScene3D *m_pScene3D;

	// �Q�[�W
	static CGauge *m_pGauge;

	static LPDIRECT3DTEXTURE9			m_pTexture;
	static LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;
	int									m_nCounterGameState;
	int									m_Gametimmer;
	static STATE						m_State;
	int									m_nIndex;
	static int							m_nTimer;

};
#endif

