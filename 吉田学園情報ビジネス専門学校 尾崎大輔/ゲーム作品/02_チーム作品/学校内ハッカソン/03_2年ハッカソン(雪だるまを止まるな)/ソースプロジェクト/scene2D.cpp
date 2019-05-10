//=============================================================================
//
// �I�u�W�F�N�g2D���� [scene2D.cpp]
// Author : Jukiya Hayakawa
//
//=============================================================================
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"

#define TEXTURE_NAME "data\\TEXTURE\\enemy010.png"			//�e�N�X�`����

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================

//=============================================================================
// �I�u�W�F�N�g�̃R���X�g���N�^
//=============================================================================
CScene2D::CScene2D(int nPriority,OBJTYPE objtype) : CScene(nPriority, objtype)
{
	m_pTexture = NULL;					// �e�N�X�`���ւ̃|�C���^
	m_pVtxBuff = NULL;					// ���_�o�b�t�@�ւ̃|�C���^
	m_pos = D3DXVECTOR3(0, 0, 0);		// �ʒu
	m_rot = 0;							//����
	m_fAddLength = 1;					//���Z��
	m_fLength = 0;						//�g��
	m_fWidth = 50;						//��
	m_fHeight = 50;						//����
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//�F

}
//=============================================================================
// �I�u�W�F�N�g�̃f�X�g���N�^
//=============================================================================
CScene2D::~CScene2D()
{

}

//=============================================================================
//�I�u�W�F�N�g�̐���
//=============================================================================
CScene2D *CScene2D::Create(D3DXVECTOR3 pos, float fWight, float fHeight)
{
	CScene2D *pScene2D = NULL;	//CScene2D�̃|�C���^

	if (pScene2D == NULL)
	{//NULL�̏ꍇ
		pScene2D = new CScene2D;	//�V�[���̓��I�m��
		if (pScene2D != NULL)
		{
			pScene2D->m_pos = pos;			//�ʒu�̑��
			pScene2D->m_fWidth = fWight;	//���̑��
			pScene2D->m_fHeight = fHeight;	//�����̑��
			pScene2D->Init();				//����������
		}
	}
	return pScene2D;			//�l��Ԃ�
}

//=============================================================================
// �I�u�W�F�N�g�̏���������
//=============================================================================
HRESULT CScene2D::Init(void)
{
	//�����_�����O�̎擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	//�|�C���^�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_NAME,
		&m_pTexture);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_2D*pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)& pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_fWidth, m_pos.y - m_fHeight, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_fWidth, m_pos.y - m_fHeight, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_fWidth, m_pos.y + m_fHeight, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_fWidth, m_pos.y + m_fHeight, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	//��ނ̐ݒ�
	SetObjType(OBJTYPE_SCENE2D);

	return S_OK;
}

//=============================================================================
// �I�u�W�F�N�g�̏I������
//=============================================================================
void CScene2D::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// �e�N�X�`���̔j��
	/*if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}*/

	//�I�u�W�F�N�g�̔j��
	Release();
}

//=============================================================================
// �I�u�W�F�N�g�̍X�V����
//=============================================================================
void CScene2D::Update(void)
{
	//�L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetKeyboard();
	/*m_rot.x += 0.01f;*/

	if (pInputKeyboard->GetTrigger(DIK_1) == true)
	{
		//Uninit();
	}
}

//=============================================================================
// �I�u�W�F�N�g�̕`�揈��
//=============================================================================
void CScene2D::Draw(void)
{
	//�����_�����O�̎擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//=============================================================================
// �I�u�W�F�N�g�̎擾����
//=============================================================================
D3DXVECTOR3 CScene2D::GetPos(void)
{
	return m_pos;	//�l��Ԃ�
}

//=============================================================================
// �I�u�W�F�N�g�̐ݒu����
//=============================================================================
void CScene2D::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;	//�ʒu�̑��
}

//=============================================================================
// ���_���̐ݒu����
//=============================================================================
void CScene2D::SetVtxPos(D3DXVECTOR3 pos)
{
	m_pos = pos;	//�ʒu�̑��

	VERTEX_2D*pVtx;	//���_���ւ̃|�C���^

					//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_fWidth, m_pos.y - m_fHeight, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_fWidth, m_pos.y - m_fHeight, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_fWidth, m_pos.y + m_fHeight, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_fWidth, m_pos.y + m_fHeight, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=============================================================================
// ���_���̐ݒu����
//=============================================================================
void CScene2D::SetVtxLenghtPos(D3DXVECTOR3 pos)
{
	m_pos = pos;	//�ʒu�̑��

	VERTEX_2D*pVtx;	//���_���ւ̃|�C���^

					//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_fLength, m_pos.y - m_fLength, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_fLength, m_pos.y - m_fLength, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_fLength, m_pos.y + m_fLength, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_fLength, m_pos.y + m_fLength, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}
//=============================================================================
// �I�u�W�F�N�g�̐ݒu����
//=============================================================================
void CScene2D::SetVtxRotPos(D3DXVECTOR3 pos)
{
	m_pos = pos;	//�ʒu�̑��

	VERTEX_2D*pVtx;	//���_���ւ̃|�C���^

					//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x + sinf(-D3DX_PI * 0.75f - m_rot) * m_fLength, m_pos.y + cosf(-D3DX_PI * 0.75f - m_rot) * m_fLength, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + sinf(D3DX_PI * 0.75f - m_rot) * m_fLength, m_pos.y + cosf(D3DX_PI * 0.75f - m_rot) * m_fLength, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x + sinf(-D3DX_PI * 0.25f - m_rot) * m_fLength, m_pos.y + cosf(-D3DX_PI * 0.25f - m_rot) * m_fLength, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + sinf(D3DX_PI * 0.25f - m_rot) * m_fLength, m_pos.y + cosf(D3DX_PI * 0.25f - m_rot) * m_fLength, 0.0f);


	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}
//=============================================================================
// ���̐ݒu����
//=============================================================================
void CScene2D::SetWidth(float width)
{
	m_fWidth = width;
}
//=============================================================================
// �����̐ݒu����
//=============================================================================
void CScene2D::SetHeight(float height)
{
	m_fHeight = height;
}
//=============================================================================
// �g��̐ݒu����
//=============================================================================
void CScene2D::SetLength(float fLength)
{
	m_fLength = fLength;
}
//=============================================================================
// ���̎擾����
//=============================================================================
float CScene2D::GetWidth(void)
{
	return m_fWidth;
}
//=============================================================================
// �����̐ݒu����
//=============================================================================
float CScene2D::GetHeight(void)
{
	return m_fHeight;
}
//=============================================================================
// �g��̐ݒu����
//=============================================================================
float CScene2D::GetfLength(void)
{
	return m_fLength;
}

//=============================================================================
// �I�u�W�F�N�g�e�N�X�`���̐ݒu����
//=============================================================================
void CScene2D::SetCol(D3DXCOLOR col)
{
	m_col = col;
	VERTEX_2D*pVtx;	//���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_�J���[�̐ݒ�
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	// ���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

//=============================================================================
// �I�u�W�F�N�g�̎擾����
//=============================================================================
void CScene2D::BindTexture(LPDIRECT3DTEXTURE9 texture)
{
	m_pTexture = texture;
}

//=============================================================================
// ���_�o�b�t�@�̎擾����
//=============================================================================
LPDIRECT3DVERTEXBUFFER9 CScene2D::GetVtx(void)
{
	return m_pVtxBuff;
}

//=============================================================================
// ���_�o�b�t�@�̎擾����
//=============================================================================
D3DXCOLOR CScene2D::GetCol(void)
{
	return m_col;
}