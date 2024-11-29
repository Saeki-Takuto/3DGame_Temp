//==================================================================
//
//モデル処理<model.h>
//Author:Saeki Takuto
//
//==================================================================
#ifndef _PLAYER_H_	//このマクロ定義がされてなかったら
#define _PLAYER_H_	//2重インクルード防止のマクロ定義

#include "main.h"
#include "model.h"

//プレイヤーの構造体
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 posOld;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 rotDest;
	D3DXVECTOR3 move;
	D3DXVECTOR3 vtxMinBlock, vtxMaxBlock;
	D3DXVECTOR3 size;
	int g_nIdxShadow;
	D3DXMATRIX mtxWorld;
	Model aModel[12];//モデル（パーツ)
	int nNumModel;	//モデル(パーツ)の総数
}Player;

//プロトタイプ宣言
void InitPlayer(void);//初期化処理
void UninitPlayer(void);//終了処理
void UpdatePlayer(void);//更新処理
void DrawPlayer(void);//描画処理
Player* GetPlayer();

#endif