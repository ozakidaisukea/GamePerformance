//=============================================================================
//
// ���b�V���E�B�[���̏��� [wall.h]
// Author :
//
//=============================================================================
#ifndef _WALL_H_
#define _WALL_H_

#include "main.h"
#include "scene.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_NOR		(10000)
#define XSize		(10)
#define ZSize		(10)

#define mPolygonX	(50)				// ���̒��_��
#define mPolygonY	(50)				// �c�̒��_��
#define X_SIZE		(1200)				// X�̃T�C�Y
#define Y_SIZE		(3600)				// Z�̃T�C�Y
//=============================================================================
//	���b�V���t�B�[���h�N���X�i�V�[���̔h���N���X�j
//=============================================================================
class CWall : public CScene
{
public:
	CWall(int nPriarity, CScene::OBJTYPE objtype);			//	�R���X�g���N�^
	~CWall();												//	�f�X�g���N�^

	void Load(void);								// �ǂݍ���
    void Unload(void);								// �J��

	HRESULT Init(void);										//	����������
	void Uninit(void);										//	�I������
	void Update(void);										//	�X�V����
	void Draw(void);										//	�`�揈��
	void BindTexture(LPDIRECT3DTEXTURE9		pTexture);		//	���ʃe�N�X�`�������蓖�Ă�
	static CWall *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fDepth, int nCutX, int nCutY);		//	�|���S���̐���
																														//float CWall::GetHeight(D3DXVECTOR3 pos);			//	�n�ʂ̍����̎擾
	void SetHigth(D3DXVECTOR3 pos, float fValue, float fRange);
	void Save(void);

private:
	LPDIRECT3DTEXTURE9		m_pTexture;						//�@�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;						//�@���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9	m_pIdxBuff;						//  �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3				m_pos;							//�@�ʒu
	D3DXVECTOR3				m_rot;							//�@����
	D3DXMATRIX				m_mtxworld;						//	���[���h�}�g���b�N�X
	float					m_fWidth;						//	��
	float					m_fDepth;						//	���s
	int						m_nNumVtx;						//  ���_��
	int						m_nNumIdx;						//  �C���f�b�N�X��
	int						m_nNumPolygon;					//  �|���S����
	int						m_nCutX;						//  ���̃��b�V���̕�����
	int						m_nCutY;						//  ���̃��b�V���̕�����
	float					m_posY;
	float					m_aHeight;
protected:
};
#endif