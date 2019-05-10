//=============================================================================
//
// �|���S������ [Wall.cpp]
// Author : Meguro Mikiya
//
//=============================================================================
#include "wall.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define WALL_TEXTURENAME		 "data\\TEXTURE\\wall002.jpg"	//�e�N�X�`���̃t�@�C����
#define TEX_POS_X_INIT			(1.0f)							//�e�N�X�`�����WU�̏����ʒu
#define TEX_POS_Y_INIT			(1.0f)							//�e�N�X�`�����WV�̏����ʒu
#define TEX_LEFT				(0.0f)							//�e�N�X�`�����WU��
#define TEX_RIGHT				(1.0f)							//�e�N�X�`�����WU�E
#define TEX_TOP					(0.0f)							//�e�N�X�`�����WV��
#define TEX_BOT					(1.0f)							//�e�N�X�`�����WV��
#define MAX_WALL				(128)							//�ǂ̍ő吔

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexWall(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWall = NULL;	//���_�o�b�t�@�ւ̃|�C���^
//D3DXVECTOR3 g_posWall;							//�ʒu
//D3DXVECTOR3 g_rotWall;							//����
//D3DXMATRIX	g_mtrxWorldWall;					//���[���h�}�g���b�N�X
LPDIRECT3DTEXTURE9	g_pTextureWall = NULL;		//�e�N�X�`���ւ̃|�C���^
WALL g_aWall[MAX_WALL];
//=============================================================================
// ����������
//=============================================================================
void InitWall(void)
{
	LPDIRECT3DDEVICE9 pDevice;	// �f�o�C�X�̎擾
	pDevice = GetDevice();	// �f�o�C�X�̎擾

	//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			WALL_TEXTURENAME,
			&g_pTextureWall);
	// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_WALL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffWall,
		NULL);

	VERTEX_3D *pVtx;
	//���_�o�b�t�@�����b�N
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		//���_���W
		//pVtx[0].pos = D3DXVECTOR3(-100.0f, 50.0f, 0.0f);
		//pVtx[1].pos = D3DXVECTOR3(100.0f, 50.0f, 0.0f);
		//pVtx[2].pos = D3DXVECTOR3(-100.0f, 0.0f, 0.0f);
		//pVtx[3].pos = D3DXVECTOR3(100.0f, 0.0f, 0.0f);

		//���_���W
		pVtx[0].pos = D3DXVECTOR3(g_aWall[nCntWall].fWidth, g_aWall[nCntWall].fHeght, 0);
		pVtx[1].pos = D3DXVECTOR3(g_aWall[nCntWall].fWidth, g_aWall[nCntWall].fHeght, 0);
		pVtx[2].pos = D3DXVECTOR3(g_aWall[nCntWall].fWidth, 0, 0);
		pVtx[3].pos = D3DXVECTOR3(g_aWall[nCntWall].fWidth, 0, 0);
		//�@���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		//���_�J���[
		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(TEX_LEFT, TEX_TOP);
		pVtx[1].tex = D3DXVECTOR2(TEX_RIGHT, TEX_TOP);
		pVtx[2].tex = D3DXVECTOR2(TEX_LEFT, TEX_BOT);
		pVtx[3].tex = D3DXVECTOR2(TEX_RIGHT, TEX_BOT);
		//���_�f�[�^�̃|�C���^��4���i�߂�
		pVtx += 4;	
	}

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		g_aWall[nCntWall].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aWall[nCntWall].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aWall[nCntWall].fRadius = 0.0f;
		g_aWall[nCntWall].fHeght = 0.0f;
		g_aWall[nCntWall].fWidth = 0.0f;
		g_aWall[nCntWall].bUse = false;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffWall->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void UninitWall(void)
{	//�e�N�X�`���̔j��
	if (g_pTextureWall != NULL)
	{
		g_pTextureWall->Release();
		g_pTextureWall = NULL;
	}
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffWall != NULL)
	{
		g_pVtxBuffWall->Release();
		g_pVtxBuffWall = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateWall(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX  mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_aWall[nCntWall].mtrxWorld);
		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aWall[nCntWall].rot.y, g_aWall[nCntWall].rot.x, g_aWall[nCntWall].rot.z);
		D3DXMatrixMultiply(&g_aWall[nCntWall].mtrxWorld, &g_aWall[nCntWall].mtrxWorld, &mtxRot);
		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_aWall[nCntWall].pos.x , g_aWall[nCntWall].pos.y, g_aWall[nCntWall].pos.z);
		D3DXMatrixMultiply(&g_aWall[nCntWall].mtrxWorld, &g_aWall[nCntWall].mtrxWorld, &mtxTrans);
		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_aWall[nCntWall].mtrxWorld);
		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffWall, 0, sizeof(VERTEX_3D));
		//���_�t�H�[�}�b�g��ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureWall);

		if (g_aWall[nCntWall].bUse == true)	//�ǂ��g�p����Ă���
		{
			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				0 + (4 * nCntWall),	//�J�n���钸�_�̃C���f�b�N�X
				2); //�`�悷��v���~�e�B�u��
		}
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexWall(LPDIRECT3DDEVICE9 pDevice)
{
	// ���_�o�b�t�@�𐶐�


	// ���_���̐ݒ�

}

//=============================================================================
// �ǂ̐ݒ菈��
//=============================================================================
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fHeght, float fWidth)
{
	int nCntWall;
	VERTEX_3D *pVtx;//���_���ւ̃|�C���^
					//���_�o�b�t�@�����b�N�����_�f�[�^�̃|�C���^���擾
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_aWall[nCntWall].bUse == false)	//�ǂ��g�p����Ă��Ȃ�
		{
			g_aWall[nCntWall].pos = pos;
			g_aWall[nCntWall].rot = rot;
			g_aWall[nCntWall].fHeght= fHeght;
			g_aWall[nCntWall].fWidth = fWidth;

			//���_���W
			pVtx[0].pos = D3DXVECTOR3(-g_aWall[nCntWall].fWidth, g_aWall[nCntWall].fHeght, 0);
			pVtx[1].pos = D3DXVECTOR3(g_aWall[nCntWall].fWidth, g_aWall[nCntWall].fHeght, 0);
			pVtx[2].pos = D3DXVECTOR3(-g_aWall[nCntWall].fWidth, 0, 0);
			pVtx[3].pos = D3DXVECTOR3(g_aWall[nCntWall].fWidth, 0, 0);

			g_aWall[nCntWall].bUse = true;
			break;
		}
		pVtx += 4;	//���_�f�[�^�̃|�C���^��4���i�߂�	
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffWall->Unlock();
}
