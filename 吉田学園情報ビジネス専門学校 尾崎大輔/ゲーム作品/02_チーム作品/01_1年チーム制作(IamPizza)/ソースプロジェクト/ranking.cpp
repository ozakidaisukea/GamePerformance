//=============================================================================
//
// �����L���O���� [ranking.cpp]
// Author : Mikiya Meguro
//
//=============================================================================
#include "ranking.h"
#include "input.h"
#include "fade.h"
#include "rank.h"
#include "time.h"
#include "title.h"
#include "rankinglogo.h"
#include "rankingbg.h"
#include "polygon.h"
#include "inputx.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_SCORE		"data/TEXTURE/Number000.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define POLYGON_POS_X			(30)						//���_���WX�̈ړ���
#define POLYGON_POS_Y			(30)						//���_���WY�̈ړ���
#define TEX_POS_X_INIT			(1.0f)						//�e�N�X�`�����WU�̏����ʒu
#define TEX_POS_Y_INIT			(1.0f)						//�e�N�X�`�����WV�̏����ʒu
#define TEX_LEFT				(0.0f)						//�e�N�X�`�����WU��
#define TEX_RIGHT				(1.0f)						//�e�N�X�`�����WU�E
#define TEX_TOP					(0.0f)						//�e�N�X�`�����WV��
#define TEX_BOT					(1.0f)						//�e�N�X�`�����WV��
#define MAX_RANKING				(5)							//�����L���O�̐�
#define MAX_NUM					(3)
#define NUM_WHIDTH				(50)
#define NUM_HIGHT				(88)
#define POS_WHIDTH				(70)
#define NUMPOS_WHIDTH			(55)
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexRanking(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureRanking = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRanking = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
int						g_nRanking;						// �X�R�A
int						g_aScore[MAX_RANKING];
Ranking					g_aRanking[MAX_RANKING];	
D3DXVECTOR3				g_RankingPos;
int						g_nCounterTimer;
int						g_nRankNum;
int						g_nCntRankTimer;
int						g_RankChange;
int						g_nUpdateScore;
JoyState g_JoyStateRanking;
//=============================================================================
// ����������
//=============================================================================
void InitRanking(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	g_JoyStateRanking.nJoypadState = INPUT_JOYSTATE_NOTPUSH;

	g_RankingPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_nRanking = 0;
	g_nCounterTimer = 0;
	g_nCntRankTimer = 0;
	g_RankChange = 0;

	int nScoreChange, nScoreChange2;

	for (int nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
	{
		g_aRanking[nCntRanking].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aRanking[nCntRanking].col = D3DXCOLOR(0.0f, 0.0f, 0.0f,0.0f);
	}

	TIME *pScore;
	//�X�R�A�̎擾
	pScore = GetTime();
	g_nRanking = pScore->nTime;
	g_nUpdateScore = g_nRanking;

	for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
	{//�����L���O���X�V
		if (g_aScore[nCnt] <= g_nRanking)
		{
			if (g_aScore[nCnt + 1] >= g_nRanking)
			{//�����L���O�����ւ�
				//�l���Ƃ��Ă���
				nScoreChange = g_aScore[nCnt];
				//�Q�[����̃X�R�A����
				g_aScore[nCnt] = g_nRanking;
				g_nRankNum = nCnt;
				//���̃X�R�A���Ƃ��Ă���
				nScoreChange2 = g_aScore[nCnt - 1];
				//���̃X�R�A�ɓh��ւ����X�R�A����
				g_aScore[nCnt - 1] = nScoreChange;
				//���̃X�R�A��n���Ă���
				nScoreChange = nScoreChange2;
				for (nCnt = nCnt - 1; nCnt >= 0; nCnt--)
				{	//�n���ꂽ�X�R�A����
					nScoreChange2 = nScoreChange;
					//����ɉ��̃X�R�A���Ƃ��Ă���
					nScoreChange = g_aScore[nCnt - 1];
					//���̃X�R�A������ɉ��̃X�R�A�ɑ��
					g_aScore[nCnt -1] = nScoreChange2;
				}
				break;
			}
			if (nCnt == MAX_RANKING - 1)
			{
				if (g_aScore[nCnt] <= g_nRanking)
				{
					//�l���Ƃ��Ă���
					nScoreChange = g_aScore[nCnt];
					//�Q�[����̃X�R�A����
					g_aScore[nCnt] = g_nRanking;
					g_nRankNum = nCnt;
					//���̃X�R�A���Ƃ��Ă���
					nScoreChange2 = g_aScore[nCnt - 1];
					//���̃X�R�A�ɓh��ւ����X�R�A����
					g_aScore[nCnt - 1] = nScoreChange;
					//���̃X�R�A��n���Ă���
					nScoreChange = nScoreChange2;
					for (nCnt = nCnt - 1; nCnt >= 0; nCnt--)
					{	//�n���ꂽ�X�R�A����
						nScoreChange2 = nScoreChange;
						//����ɉ��̃X�R�A���Ƃ��Ă���
						nScoreChange = g_aScore[nCnt - 1];
						//���̃X�R�A������ɉ��̃X�R�A�ɑ��
						g_aScore[nCnt - 1] = nScoreChange2;
					}
					break;
				}
			}
		}	
	}

	g_nCounterTimer = 0;
	g_nCntRankTimer = 0;
	g_RankChange = 0;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,			// �f�o�C�X�ւ̃|�C���^
		TEXTURE_SCORE,							// �t�@�C���̖��O
		&g_pTextureRanking);					// �e�N�X�`���ւ̃|�C���^

	// ���_���̍쐬
	MakeVertexRanking(pDevice);
	//2D������
	InitRank();
	InitRankingLogo();
	InitRankingBG();
	//
	//3D��Ԃ̏�����
	//
	// �J�����̏���������
	//InitCamera();
	// ���C�g�̏���������
	//InitLight();
	//���b�V���t�B�[���h�̏�����
	//InitMeshField();
	InitPolygon();
}

//=============================================================================
// �I������
//=============================================================================
void UninitRanking(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureRanking != NULL)
	{
		g_pTextureRanking->Release();
		g_pTextureRanking = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffRanking != NULL)
	{
		g_pVtxBuffRanking->Release();
		g_pVtxBuffRanking = NULL;
	}

	//���ʂ̏I������
	UninitRank();
	//���S�̏I������
	UninitRankingLogo();
	UninitRankingBG();
	//�J�����̏I������
	//UninitCamera();
	//���C�g�̏I������
	//UninitLight();
	//���b�V���t�B�[���h�̏I������
	//UninitMeshField();
	UninitPolygon();

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateRanking(void)
{
	FADE fade;
	fade = GetFade();

	JoyState pJoyState = GetJoystate();
	XINPUT_STATE state;
	XInputGetState(0, &state);

	TIME *pScore;
	//�X�R�A�̎擾
	pScore = GetTime();

	// ���_���̍쐬
	VERTEX_2D *pVtx;

	//�G���^�[�L�[
	if (GetKeyboardTrigger(DIK_RETURN) == true && fade == FADE_NONE || (state.Gamepad.wButtons & XINPUT_GAMEPAD_B  && pJoyState.bConnectionJoypad == true) && fade == FADE_NONE)
	{
		pScore = 0;
		SetFade(MODE_TITLE);
	}
	g_nCounterTimer++;
	if (g_nCounterTimer >= 600)
	{
		pScore = 0;
		SetFade(MODE_TITLE);
	}
	//�F�ς�
	int nUpdateScore = NULL;
	int nAnswer = 0;
	int nKeisan = 1;

	for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
	{//�����L���O���X�V
		if (g_aScore[nCnt] == g_nUpdateScore)
		{//�X�V�����X�R�A�͉��Ԗڂ�
			nUpdateScore = nCnt;
			break;
		}
		else if (nCnt == 4)
		{//�X�V�����X�R�A�͉��Ԗڂ�
			nUpdateScore = 4;
		}
	}
	g_aRanking[nUpdateScore].pos.x = SCREEN_WIDTH / 2 + NUM_WHIDTH;
	g_aRanking[nUpdateScore].pos.y = 550.0f - (NUM_HIGHT * nUpdateScore);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += 4 * MAX_NUM * nUpdateScore;	//���_�f�[�^�̃|�C���^��i�߂�
	for (int nCntScore = 0; nCntScore < MAX_NUM; nCntScore++)
	{
		nAnswer = g_aScore[nUpdateScore] % (nKeisan * 10) / nKeisan;
		//���_���W
		pVtx[0].pos = D3DXVECTOR3(g_aRanking[nUpdateScore].pos.x - POLYGON_POS_X, g_aRanking[nUpdateScore].pos.y - POLYGON_POS_Y, g_aRanking[nUpdateScore].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_aRanking[nUpdateScore].pos.x + POLYGON_POS_X, g_aRanking[nUpdateScore].pos.y - POLYGON_POS_Y, g_aRanking[nUpdateScore].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_aRanking[nUpdateScore].pos.x - POLYGON_POS_X, g_aRanking[nUpdateScore].pos.y + POLYGON_POS_Y, g_aRanking[nUpdateScore].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_aRanking[nUpdateScore].pos.x + POLYGON_POS_X, g_aRanking[nUpdateScore].pos.y + POLYGON_POS_Y, g_aRanking[nUpdateScore].pos.z);
		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f + (nAnswer * 0.1f), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + (nAnswer * 0.1f), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (nAnswer * 0.1f), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + (nAnswer * 0.1f), 1.0f);
		//���_
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		if (nUpdateScore == 4)
		{
			if (g_RankChange == 0)
			{
				{	//���_�J���[
					pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
					pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
					pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
					pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				}
			}
			else if (g_RankChange == 1)
			{
				{	//���_�J���[
					pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				}
			}
		}
		else
		{
			if (g_RankChange == 0)
			{
				{	//���_�J���[
					pVtx[0].col = D3DXCOLOR(0.2f, 0.0f, 1.0f, 1.0f);
					pVtx[1].col = D3DXCOLOR(0.2f, 0.0f, 1.0f, 1.0f);
					pVtx[2].col = D3DXCOLOR(0.2f, 0.0f, 1.0f, 1.0f);
					pVtx[3].col = D3DXCOLOR(0.2f, 0.0f, 1.0f, 1.0f);
				}
			}
			else if (g_RankChange == 1)
			{
				{	//���_�J���[
					pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				}
			}
		}
		////���_�J���[
		//pVtx[0].col = D3DXCOLOR(0.2f, 0.0f, 1.0f, 1.0f);
		//pVtx[1].col = D3DXCOLOR(0.2f, 0.0f, 1.0f, 1.0f);
		//pVtx[2].col = D3DXCOLOR(0.2f, 0.0f, 1.0f, 1.0f);
		//pVtx[3].col = D3DXCOLOR(0.2f, 0.0f, 1.0f, 1.0f);

		//if (nUpdateScore == 4)
		//{
		//	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
		//	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
		//	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
		//	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
		//}



		pVtx += 4;	//���_�f�[�^�̃|�C���^��4���i�߂�
		nKeisan *= 10;
		g_RankingPos.x -= POS_WHIDTH;
		g_aRanking[nUpdateScore].pos.x -= NUMPOS_WHIDTH;
	}


	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffRanking->Unlock();

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);

	//�_�Ń^�C�}�[
	g_nCntRankTimer++;

	if (g_nCntRankTimer >= 10)
	{
		if (g_RankChange == 0)
		{
			g_RankChange = 1;
		}
		else if (g_RankChange == 1)
		{
			g_RankChange = 0;
		}
		g_nCntRankTimer = 0;
	}


	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffRanking->Unlock();

	//����
	UpdateRank();
	//���S
	UpdateRankingLogo();
	UpdateRankingBG();
	// �J�����̍X�V����
	//UpdateCamera();
	// ���C�g�̍X�V����
	//UpdateLight();
	//���b�V���t�B�[���h�̍X�V����
	//UpdateMeshField();

	UpdatePolygon();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawRanking(void)
{
	// �J�����̐ݒ�
	//SetCamera(0);
	DrawRankingBG();

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCntScore;

	//�A���t�@�e�X�g(�����F��`�悵�Ȃ��悤��)
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 150);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffRanking, 0, sizeof(VERTEX_2D));
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureRanking);
	// �|���S���̕`��
	for (nCntScore = 0; nCntScore < MAX_NUM * MAX_RANKING; nCntScore++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			0 + (4 * nCntScore),	//�J�n���钸�_�̃C���f�b�N�X
			2); //�`�悷��v���~�e�B�u��
	}
	//���ʕ`�揈��
	DrawRank();
	//���S�`�揈��
	//DrawRankingLogo();

	//�����_�[�X�e�[�g�̐ݒ�����ɖ߂�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	//���b�V���t�B�[���h�̕`�揈��
	//DrawMeshField();
	DrawPolygon();

}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexRanking(LPDIRECT3DDEVICE9 pDevice)
{
	// ���_���̍쐬
	VERTEX_2D *pVtx;
	int nCntScore;
	int nPosMove = 0;
	int nAnswer = 0;
	int nKeisan = 1;
	int nCntRanking;


	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_NUM * MAX_RANKING,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRanking,
		NULL);

	//���_����ݒ�
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
	{//�z�u
		g_aRanking[nCntRanking].pos.x = SCREEN_WIDTH / 2 + NUM_WHIDTH;
		g_aRanking[nCntRanking].pos.y = 558.0f - (NUM_HIGHT * nCntRanking);

		for (nCntScore = 0; nCntScore < MAX_NUM; nCntScore++)
		{
			nAnswer = g_aScore[nCntRanking] % (nKeisan * 10) / nKeisan;

			//���_���W
			pVtx[0].pos = D3DXVECTOR3(g_aRanking[nCntRanking].pos.x - POLYGON_POS_X, g_aRanking[nCntRanking].pos.y - POLYGON_POS_Y, g_aRanking[nCntRanking].pos.z);
			pVtx[1].pos = D3DXVECTOR3(g_aRanking[nCntRanking].pos.x + POLYGON_POS_X, g_aRanking[nCntRanking].pos.y - POLYGON_POS_Y, g_aRanking[nCntRanking].pos.z);
			pVtx[2].pos = D3DXVECTOR3(g_aRanking[nCntRanking].pos.x - POLYGON_POS_X, g_aRanking[nCntRanking].pos.y + POLYGON_POS_Y, g_aRanking[nCntRanking].pos.z);
			pVtx[3].pos = D3DXVECTOR3(g_aRanking[nCntRanking].pos.x + POLYGON_POS_X, g_aRanking[nCntRanking].pos.y + POLYGON_POS_Y, g_aRanking[nCntRanking].pos.z);

			//�e�N�X�`�����W
			pVtx[0].tex = D3DXVECTOR2(0.0f + (nAnswer * 0.1f), 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f + (nAnswer * 0.1f), 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f + (nAnswer * 0.1f), 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f + (nAnswer * 0.1f), 1.0f);

			//���_
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			//���_�J���[
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);

			pVtx += 4;	//���_�f�[�^�̃|�C���^��4���i�߂�
			nKeisan *= 10;
			g_RankingPos.x -= POS_WHIDTH;
			g_aRanking[nCntRanking].pos.x -= NUMPOS_WHIDTH;
		}
		nKeisan = 1;
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffRanking->Unlock();
}
//=============================================================================
// �����L���O�̎擾
//=============================================================================
void SetRanking(int nRanking)
{
	for (int nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
	{
		g_aScore[nCntRanking] = nRanking * (1 + nCntRanking);
	}
}