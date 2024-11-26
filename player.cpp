#include "player.h"
#include "input.h"
#include "shadow.h"
#include "block.h"
#include "wall.h"
//グローバル変数
LPDIRECT3DTEXTURE9 g_apTexturePlayer[128] = {};
LPD3DXMESH g_pMeshPlayer = NULL;//メッシュ(頂点情報)へのポインタ
LPD3DXBUFFER g_pBuffMatPlayer = NULL;//マテリアルへのポインタ
DWORD g_dwNumMatPlayer = 0;//マテリアルの数
D3DXMATRIX g_mtxWorldPlayer;//ワールドマトリックス
Player g_player;

void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//各種変数の初期化

	//Xファイルの読み込み
	D3DXLoadMeshFromX("data/MODEL/vending.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatPlayer,
		NULL,
		&g_dwNumMatPlayer,
		&g_pMeshPlayer);

	int nNumVtx;//頂点数
	DWORD sizeFVF;//頂点フォーマットのサイズ
	BYTE* pVtxBuff;//頂点バッファへのポインタ
	//頂点数の取得
	nNumVtx = g_pMeshPlayer->GetNumVertices();
	//頂点フォーマットのサイズを取得
	sizeFVF = D3DXGetFVFVertexSize(g_pMeshPlayer->GetFVF());
	//頂点バッファのロック
	g_pMeshPlayer->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		//頂点座標の代入
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

		//xの最大値比較
		if (vtx.x > g_player.vtxMaxBlock.x)
		{
			g_player.vtxMaxBlock.x = vtx.x;
		}

		//yの最大値比較
		if (vtx.y > g_player.vtxMaxBlock.y)
		{
			g_player.vtxMaxBlock.y = vtx.y;
		}

		//xの最大値比較
		if (vtx.z > g_player.vtxMaxBlock.z)
		{
			g_player.vtxMaxBlock.z = vtx.z;
		}

		//xの最小値比較
		if (vtx.x < g_player.vtxMinBlock.x)
		{
			g_player.vtxMinBlock.x = vtx.x;
		}

		//yの最小値比較
		if (vtx.y < g_player.vtxMinBlock.y)
		{
			g_player.vtxMinBlock.y = vtx.y;
		}

		//xの最小値比較
		if (vtx.z < g_player.vtxMinBlock.z)
		{
			g_player.vtxMinBlock.z = vtx.z;
		}

		//頂点フォーマットのサイズ分ポインタを進める
		pVtxBuff += sizeFVF;
	}

	//頂点バッファのアンロック
	g_pMeshPlayer->UnlockVertexBuffer();

	D3DXMATERIAL* pMat;//マテリアルへのポインタ

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)g_pBuffMatPlayer->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatPlayer; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			//テクスチャの読み込み
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCntMat].pTextureFilename,
				&g_apTexturePlayer[nCntMat]);
		}
	}

	g_player.pos = D3DXVECTOR3(100.0f, 0.0f, 0.0f);
	g_player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.size = g_player.vtxMaxBlock - g_player.vtxMinBlock;

	g_player.g_nIdxShadow = SetShadow(g_player.pos,g_player.rot);
}

void UninitPlayer(void)
{
	//テクスチャの解放
	if (g_pMeshPlayer != NULL)
	{
		g_pMeshPlayer->Release();
		g_pMeshPlayer = NULL;
	}

	//頂点バッファの解放
	if (g_pBuffMatPlayer != NULL)
	{
		g_pBuffMatPlayer->Release();
		g_pBuffMatPlayer = NULL;
	}

	for (int nCnt = 0; nCnt < 1; nCnt++)
	{
		//テクスチャの破棄
		if (g_apTexturePlayer[nCnt] != NULL)
		{
			g_apTexturePlayer[nCnt]->Release();
			g_apTexturePlayer[nCnt] = NULL;
		}
	}
}

void UpdatePlayer(void)
{
	Camera* pCamera = GetCamera();

	if (KeyboardRepeat(DIK_DOWN) == true)
	{
		g_player.move.x += sinf(pCamera->rot.y);
		g_player.move.z += cosf(pCamera->rot.y);
		//g_player.rot.y = pCamera->rot.y;
		g_player.rotDest.y = pCamera->rot.y-D3DX_PI;
	}
	else if (KeyboardRepeat(DIK_UP) == true)
	{
		g_player.move.x -= sinf(pCamera->rot.y);
		g_player.move.z -= cosf(pCamera->rot.y);
		//g_player.rot.y = pCamera->rot.y;
		g_player.rotDest.y = pCamera->rot.y;

	}
	else if (KeyboardRepeat(DIK_RIGHT) == true)
	{
		g_player.move.z += sinf(pCamera->rot.y);
		g_player.move.x -= cosf(pCamera->rot.y);
		//g_player.rot.y = pCamera->rot.y;
		g_player.rotDest.y = pCamera->rot.y+D3DX_PI*0.5f;

	}
	else if (KeyboardRepeat(DIK_LEFT) == true)
	{
		g_player.move.z -= sinf(pCamera->rot.y);
		g_player.move.x += cosf(pCamera->rot.y);
		//g_player.rot.y = pCamera->rot.y;
		g_player.rotDest.y = pCamera->rot.y - D3DX_PI*0.5f;

	}
	
	if (g_player.rotDest.y - g_player.rot.y >= D3DX_PI)
	{
		g_player.rot.y += D3DX_PI*2;
	}
	else if (g_player.rotDest.y - g_player.rot.y <= -D3DX_PI)
	{
		g_player.rot.y -= D3DX_PI * 2;
	}


	g_player.rot.y += (g_player.rotDest.y - g_player.rot.y) * 0.1f;


	//前回の位置を保存
	g_player.posOld = g_player.pos;

	g_player.pos += g_player.move;

	CollisionBlock();
	CollisionWall();


	//移動量を更新(減衰させる)
	g_player.move.x += (0.0f - g_player.move.x) * 0.17f;
	g_player.move.z += (0.0f - g_player.move.z) * 0.17f;


	SetPositionShadow(g_player.g_nIdxShadow,g_player.pos);
}

void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;//計算用マトリックス
	D3DMATERIAL9 matDef;//現在のマテリアル保存用
	D3DXMATERIAL* pMat;//マテリアルデータへのポインタ

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldPlayer);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_player.rot.y, g_player.rot.x, g_player.rot.z);
	D3DXMatrixMultiply(&g_mtxWorldPlayer, &g_mtxWorldPlayer, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_player.pos.x, g_player.pos.y, g_player.pos.z);
	D3DXMatrixMultiply(&g_mtxWorldPlayer, &g_mtxWorldPlayer, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldPlayer);

	//現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)g_pBuffMatPlayer->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatPlayer; nCntMat++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//テクスチャの設定
		pDevice->SetTexture(0, g_apTexturePlayer[nCntMat]);

		//モデル(パーツ)の描画
		g_pMeshPlayer->DrawSubset(nCntMat);
	}

	//保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

Player* GetPlayer()
{
	return &g_player;
}
