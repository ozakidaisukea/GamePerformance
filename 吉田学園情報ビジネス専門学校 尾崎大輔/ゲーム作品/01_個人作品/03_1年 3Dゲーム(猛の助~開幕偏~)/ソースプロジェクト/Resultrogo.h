//=============================================================================
// 授業作成
// 背景の処理 [Resultrogo.h]
// Author : Ozaki
//
//=============================================================================
#ifndef _RESULTROGO_H_
#define _RWSULTROGO_H_

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitResultrogo(void);
void UninitResultrogo(void);
void UpdateResultrogo(void);
void DrawResultrogo(void);
D3DXVECTOR3 *GetResultrogo(void);
void SetResultrogo(D3DXVECTOR3 TitleLogo);
#endif