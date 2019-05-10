//=============================================================================
//
// �e���� [explosion.cpp]
// Author : ozaki
//
//=============================================================================
#include "Explosion.h"
#include "sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_EXPLOSION		(128)		// �����̍ő吔
#define MAX_MIKY			(150)
//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;				//�ʒu
	D3DXCOLOR col;					//�F
	int nCounterAnim;				//�A�j���[�V�����J�E���^�[
	int nPatternAnim;				//�A�j���[�V�����p�^�[��
	bool bUse;						//�g�p���Ă��邩
}Explosion;

//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureExplosion = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
Explosion g_aExplosion[MAX_EXPLOSION];				// �����̏��

//=============================================================================
// ����������
//=============================================================================
void InitExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D*pVtx;														//���_���ւ̃|�C���^
	int nCntExplosion;
	//�f���@�C�X���擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\explosion000.png",
		&g_pTextureExplosion);


	// �e�̏��̏�����
	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		g_aExplosion[nCntExplosion].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aExplosion[nCntExplosion].col = D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f);
		g_aExplosion[nCntExplosion].bUse = false;
	}

	// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_EXPLOSION,
		D3DUSAGE_WRITEONLY,
		FVF_VRETEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffExplosion,
		NULL);

	////���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^�̎擾
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - MAX_MIKY, g_aExplosion[nCntExplosion].pos.y - MAX_MIKY, g_aExplosion[nCntExplosion].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + MAX_MIKY, g_aExplosion[nCntExplosion].pos.y - MAX_MIKY, g_aExplosion[nCntExplosion].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - MAX_MIKY, g_aExplosion[nCntExplosion].pos.y + MAX_MIKY, g_aExplosion[nCntExplosion].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + MAX_MIKY, g_aExplosion[nCntExplosion].pos.y + MAX_MIKY, g_aExplosion[nCntExplosion].pos.z);

		//�e�N�X�`���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.125f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.125f,  1.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		pVtx += 4;					//���_�f�[�^�̃|�C���^��4���i�߂�
	}
	//���_�o�b�t�@���A�����b�N
		g_pVtxBuffExplosion->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void UninitExplosion(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureExplosion != NULL)
	{
		g_pTextureExplosion->Release();
		g_pTextureExplosion = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffExplosion != NULL)
	{
		g_pVtxBuffExplosion->Release();
		g_pVtxBuffExplosion = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateExplosion(void)
{
	int nCntExplosion;
	VERTEX_2D*pVtx;
												//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^�̎擾
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == true)
		{
			g_aExplosion[nCntExplosion].nCounterAnim++;
			if ((g_aExplosion[nCntExplosion].nCounterAnim % 5) == 0)
			{
				g_aExplosion[nCntExplosion].nPatternAnim = (g_aExplosion[nCntExplosion].nPatternAnim + 1 % 8);
				//g_aExplosion[nCntExplosion].pos.y -= 10.0f;
				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - MAX_MIKY, g_aExplosion[nCntExplosion].pos.y - MAX_MIKY, g_aExplosion[nCntExplosion].pos.z);
				pVtx[1].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + MAX_MIKY, g_aExplosion[nCntExplosion].pos.y - MAX_MIKY, g_aExplosion[nCntExplosion].pos.z);
				pVtx[2].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - MAX_MIKY, g_aExplosion[nCntExplosion].pos.y + MAX_MIKY, g_aExplosion[nCntExplosion].pos.z);
				pVtx[3].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + MAX_MIKY, g_aExplosion[nCntExplosion].pos.y + MAX_MIKY, g_aExplosion[nCntExplosion].pos.z);

				//�e�N�X�`���̐ݒ�
				pVtx[0].tex.x = (0.0f + (0.125f * (g_aExplosion[nCntExplosion].nPatternAnim % 8)));
				pVtx[0].tex.y = (0.0f + 1.0f);

				pVtx[1].tex.x = (0.125f + (0.125f * (g_aExplosion[nCntExplosion].nPatternAnim % 8)));
				pVtx[1].tex.y = (0.0f + 1.0f);

				pVtx[2].tex.x = (0.0f + (0.125f * (g_aExplosion[nCntExplosion].nPatternAnim % 8)));
				pVtx[2].tex.y = (1.0f + 1.0f);

				pVtx[3].tex.x = (0.125f + (0.125f * (g_aExplosion[nCntExplosion].nPatternAnim % 8)));
				pVtx[3].tex.y = (1.0f + 1.0f);

				if (g_aExplosion[nCntExplosion].nPatternAnim >= 8)
				{
					g_aExplosion[nCntExplosion].bUse = false;
				}
			}
		}
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffExplosion->Unlock();

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntExplosion;

	//�f���@�C�X���擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
    pDevice->SetStreamSource(0, g_pVtxBuffExplosion, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VRETEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureExplosion);

	// �|���S���̕`��
	for(nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == true)
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
									0 +(4 * nCntExplosion),
									2);
		}
	}
}

//=============================================================================
// �e�̐ݒ菈��
//=============================================================================
void SetExplosion(D3DXVECTOR3 pos, D3DXCOLOR col)
{
	int nCntExplosion;
	VERTEX_2D*pVtx;														//���_���ւ̃|�C���^

	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == false)		//�e���g�p����Ă���
		{
			g_aExplosion[nCntExplosion].pos = pos;
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - MAX_MIKY, g_aExplosion[nCntExplosion].pos.y - MAX_MIKY, g_aExplosion[nCntExplosion].pos.z);
			pVtx[1].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + MAX_MIKY, g_aExplosion[nCntExplosion].pos.y - MAX_MIKY, g_aExplosion[nCntExplosion].pos.z);
			pVtx[2].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - MAX_MIKY, g_aExplosion[nCntExplosion].pos.y + MAX_MIKY, g_aExplosion[nCntExplosion].pos.z);
			pVtx[3].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + MAX_MIKY, g_aExplosion[nCntExplosion].pos.y + MAX_MIKY, g_aExplosion[nCntExplosion].pos.z);

			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);

			g_aExplosion[nCntExplosion].nCounterAnim = 0;
			g_aExplosion[nCntExplosion].nPatternAnim = 0;
			g_aExplosion[nCntExplosion].bUse = true;
			break;
		}
		pVtx += 4;
	}
	g_pVtxBuffExplosion->Unlock();
}