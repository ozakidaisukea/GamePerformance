//=============================================================================
//
// �t�B�[���h�̏��� [field.cpp]
// Author : Jukiya Hayakawa
//
//=============================================================================
#include "field.h"
#include "scene3D.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "debugproc.h"
#include "player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_NAME01 "data\\TEXTURE\\grass.jpg"			//�e�N�X�`����
//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CField::m_pTexture = NULL;

//=============================================================================
// �I�u�W�F�N�g�̃e�N�X�`���ǂݍ���
//=============================================================================
HRESULT CField::Load(void)
{
	//�����_�����O�̎擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		NULL/*"data\\TEXTURE\\earth000.jpg"*/,
		&m_pTexture);

	return S_OK;
}

//=============================================================================
// �I�u�W�F�N�g�̃e�N�X�`���j��
//=============================================================================
void CField::Unload(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// �t�B�[���h�̃R���X�g���N�^
//=============================================================================
CField::CField() : CScene3D(6, OBJTYPE_SCENE3D)
{

}
//=============================================================================
// �t�B�[���h�̃f�X�g���N�^
//=============================================================================
CField::~CField()
{

}
//=============================================================================
// �t�B�[���h�̐���
//=============================================================================
CField *CField::Create(D3DXVECTOR3 pos,float sizeX,float sizeZ)
{
	CField *pField = NULL;		//�I�u�W�F�N�g�̃|�C���^

	if (pField == NULL)
	{
		pField = new CField;	//���I�m��
		if (pField != NULL)
		{
			pField->SetPos(pos);
			pField->SetSizeX(sizeX);
			pField->SetSizeZ(sizeZ);
			pField->BindTexture(m_pTexture);
			pField->Init();		//����������
		}
	}
	return pField;
}
//=============================================================================
// ����������
//=============================================================================
HRESULT CField::Init(void)
{
	//�����_�����O�̎擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();


	//����������
	CScene3D::Init();

	//��ނ̐ݒ�
	SetObjType(OBJTYPE_SCENE3D);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CField::Uninit(void)
{
	//�I�u�W�F�N�g3D�̏I������
	CScene3D::Uninit();

	//�I�u�W�F�N�g�̔j��
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CField::Update(void)
{
	D3DXVECTOR3 pos = GetPos();
	float sizeX = GetSizeX();
	float sizeZ = GetSizeZ();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CField::Draw(void)
{
	//�I�u�W�F�N�g3D�̕`�揈��
	CScene3D::Draw();
}