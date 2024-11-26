#include "player.h"
#include "input.h"
#include "shadow.h"
#include "block.h"
#include "wall.h"
//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_apTexturePlayer[128] = {};
LPD3DXMESH g_pMeshPlayer = NULL;//���b�V��(���_���)�ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatPlayer = NULL;//�}�e���A���ւ̃|�C���^
DWORD g_dwNumMatPlayer = 0;//�}�e���A���̐�
D3DXMATRIX g_mtxWorldPlayer;//���[���h�}�g���b�N�X
Player g_player;

void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�e��ϐ��̏�����

	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("data/MODEL/vending.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatPlayer,
		NULL,
		&g_dwNumMatPlayer,
		&g_pMeshPlayer);

	int nNumVtx;//���_��
	DWORD sizeFVF;//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE* pVtxBuff;//���_�o�b�t�@�ւ̃|�C���^
	//���_���̎擾
	nNumVtx = g_pMeshPlayer->GetNumVertices();
	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	sizeFVF = D3DXGetFVFVertexSize(g_pMeshPlayer->GetFVF());
	//���_�o�b�t�@�̃��b�N
	g_pMeshPlayer->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		//���_���W�̑��
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

		//x�̍ő�l��r
		if (vtx.x > g_player.vtxMaxBlock.x)
		{
			g_player.vtxMaxBlock.x = vtx.x;
		}

		//y�̍ő�l��r
		if (vtx.y > g_player.vtxMaxBlock.y)
		{
			g_player.vtxMaxBlock.y = vtx.y;
		}

		//x�̍ő�l��r
		if (vtx.z > g_player.vtxMaxBlock.z)
		{
			g_player.vtxMaxBlock.z = vtx.z;
		}

		//x�̍ŏ��l��r
		if (vtx.x < g_player.vtxMinBlock.x)
		{
			g_player.vtxMinBlock.x = vtx.x;
		}

		//y�̍ŏ��l��r
		if (vtx.y < g_player.vtxMinBlock.y)
		{
			g_player.vtxMinBlock.y = vtx.y;
		}

		//x�̍ŏ��l��r
		if (vtx.z < g_player.vtxMinBlock.z)
		{
			g_player.vtxMinBlock.z = vtx.z;
		}

		//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
		pVtxBuff += sizeFVF;
	}

	//���_�o�b�t�@�̃A�����b�N
	g_pMeshPlayer->UnlockVertexBuffer();

	D3DXMATERIAL* pMat;//�}�e���A���ւ̃|�C���^

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)g_pBuffMatPlayer->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatPlayer; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			//�e�N�X�`���̓ǂݍ���
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
	//�e�N�X�`���̉��
	if (g_pMeshPlayer != NULL)
	{
		g_pMeshPlayer->Release();
		g_pMeshPlayer = NULL;
	}

	//���_�o�b�t�@�̉��
	if (g_pBuffMatPlayer != NULL)
	{
		g_pBuffMatPlayer->Release();
		g_pBuffMatPlayer = NULL;
	}

	for (int nCnt = 0; nCnt < 1; nCnt++)
	{
		//�e�N�X�`���̔j��
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


	//�O��̈ʒu��ۑ�
	g_player.posOld = g_player.pos;

	g_player.pos += g_player.move;

	CollisionBlock();
	CollisionWall();


	//�ړ��ʂ��X�V(����������)
	g_player.move.x += (0.0f - g_player.move.x) * 0.17f;
	g_player.move.z += (0.0f - g_player.move.z) * 0.17f;


	SetPositionShadow(g_player.g_nIdxShadow,g_player.pos);
}

void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldPlayer);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_player.rot.y, g_player.rot.x, g_player.rot.z);
	D3DXMatrixMultiply(&g_mtxWorldPlayer, &g_mtxWorldPlayer, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_player.pos.x, g_player.pos.y, g_player.pos.z);
	D3DXMatrixMultiply(&g_mtxWorldPlayer, &g_mtxWorldPlayer, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldPlayer);

	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)g_pBuffMatPlayer->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatPlayer; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_apTexturePlayer[nCntMat]);

		//���f��(�p�[�c)�̕`��
		g_pMeshPlayer->DrawSubset(nCntMat);
	}

	//�ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

Player* GetPlayer()
{
	return &g_player;
}
