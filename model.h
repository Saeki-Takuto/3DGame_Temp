//==================================================================
//
//モデル処理<model.h>
//Author:Saeki Takuto
//
//==================================================================
#ifndef _MODEL_H_	//このマクロ定義がされてなかったら
#define _MODEL_H_	//2重インクルード防止のマクロ定義

#include "main.h"

//プロトタイプ宣言
void InitModel(void);//初期化処理
void UninitModel(void);//終了処理
void UpdateModel(void);//更新処理
void DrawModel(void);//描画処理

#endif