//=============================================================================
//
// �Q�[���̏��� [game.h]
// Author : Jukiya Hayakawa
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"

//�O���錾
class CMeshField;
class CPlayer;
class CCommand;
class CMap;
class CScore;
class CObjBillboard;
class CItemBillboard;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CGame
{
public:	//�N������A�N�Z�X�\
	//�����o�֐�
	CGame();
	~CGame();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//�ÓI�����o�֐�
	static CGame			*Create(void);
	static CMeshField		*GetMeshField(void);
	static CPlayer			*GetPlayer(void);
	static CScore	*GetScore(void);


private:	//�����������A�N�Z�X�\
	//�ÓI�����o�ϐ�
	static CMeshField		*m_pMeshField;	//���b�V���t�B�[���h�̃|�C���^
	static CPlayer			*m_pPlayer;		//�v���C���[�̃|�C���^
	static CMap				*m_pMap;		//�}�b�v�̃|�C���^
	static CScore	*m_pScore;
	static CObjBillboard *m_p3Dporigon;
	static CItemBillboard *m_p3DItem;

};
#endif