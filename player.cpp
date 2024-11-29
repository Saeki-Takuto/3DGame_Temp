#include "player.h"
#include "input.h"
#include "shadow.h"
#include "block.h"
#include "wall.h"
//�O���[�o���ϐ�
Player g_player;

void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_player.pos = D3DXVECTOR3(100.0f, 0.0f, 0.0f);
	g_player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	int nNumVtx;//���_��
	DWORD sizeFVF;//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE* pVtxBuff;//���_�o�b�t�@�ւ̃|�C���^

	//�e��ϐ��̏�����

	//X�t�@�C���̓ǂݍ���_00
	D3DXLoadMeshFromX("data/MODEL/00_body.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_player.aModel[0].pBuffMat,
		NULL,
		&g_player.aModel[0].dwNumMat,
		&g_player.aModel[0].pMesh);

	//X�t�@�C���̓ǂݍ���_01
	D3DXLoadMeshFromX("data/MODEL/01_head.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_player.aModel[1].pBuffMat,
		NULL,
		&g_player.aModel[1].dwNumMat,
		&g_player.aModel[1].pMesh);

	//X�t�@�C���̓ǂݍ���_02
	D3DXLoadMeshFromX("data/MODEL/02_Rshoulder.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_player.aModel[2].pBuffMat,
		NULL,
		&g_player.aModel[2].dwNumMat,
		&g_player.aModel[2].pMesh);

	//X�t�@�C���̓ǂݍ���_03
	D3DXLoadMeshFromX("data/MODEL/03_Rarm.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_player.aModel[3].pBuffMat,
		NULL,
		&g_player.aModel[3].dwNumMat,
		&g_player.aModel[3].pMesh);

	//X�t�@�C���̓ǂݍ���_04
	D3DXLoadMeshFromX("data/MODEL/04_Rhand.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_player.aModel[4].pBuffMat,
		NULL,
		&g_player.aModel[4].dwNumMat,
		&g_player.aModel[4].pMesh);

	//X�t�@�C���̓ǂݍ���_05
	D3DXLoadMeshFromX("data/MODEL/05_Lshoulder.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_player.aModel[5].pBuffMat,
		NULL,
		&g_player.aModel[5].dwNumMat,
		&g_player.aModel[5].pMesh);

	//X�t�@�C���̓ǂݍ���_06
	D3DXLoadMeshFromX("data/MODEL/06_Larm.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_player.aModel[6].pBuffMat,
		NULL,
		&g_player.aModel[6].dwNumMat,
		&g_player.aModel[6].pMesh);

	//X�t�@�C���̓ǂݍ���_07
	D3DXLoadMeshFromX("data/MODEL/07_Lhand.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_player.aModel[7].pBuffMat,
		NULL,
		&g_player.aModel[7].dwNumMat,
		&g_player.aModel[7].pMesh);

	//X�t�@�C���̓ǂݍ���_08
	D3DXLoadMeshFromX("data/MODEL/08_Rleg.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_player.aModel[8].pBuffMat,
		NULL,
		&g_player.aModel[8].dwNumMat,
		&g_player.aModel[8].pMesh);

	//X�t�@�C���̓ǂݍ���_09
	D3DXLoadMeshFromX("data/MODEL/09_Rfoot.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_player.aModel[9].pBuffMat,
		NULL,
		&g_player.aModel[9].dwNumMat,
		&g_player.aModel[9].pMesh);

	//X�t�@�C���̓ǂݍ���_10
	D3DXLoadMeshFromX("data/MODEL/10_Lleg.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_player.aModel[10].pBuffMat,
		NULL,
		&g_player.aModel[10].dwNumMat,
		&g_player.aModel[10].pMesh);

	//X�t�@�C���̓ǂݍ���_11
	D3DXLoadMeshFromX("data/MODEL/11_Lfoot.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_player.aModel[11].pBuffMat,
		NULL,
		&g_player.aModel[11].dwNumMat,
		&g_player.aModel[11].pMesh);


	g_player.nNumModel = 12;

	//�e�p�[�c�̊K�w�\���ݒ�
	g_player.aModel[0].nIdxModelParent = -1;
	g_player.aModel[0].pos = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
	g_player.aModel[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	g_player.aModel[1].nIdxModelParent = 0;
	g_player.aModel[1].pos = D3DXVECTOR3(0.0f, 20.0f, 0.0f);
	g_player.aModel[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	g_player.aModel[2].nIdxModelParent = 0;
	g_player.aModel[2].pos = D3DXVECTOR3(-7.0f, 12.0f, 0.0f);
	g_player.aModel[2].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	g_player.aModel[3].nIdxModelParent = 2;
	g_player.aModel[3].pos = D3DXVECTOR3(-4.0f, 1.0f, 0.0f);
	g_player.aModel[3].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	g_player.aModel[4].nIdxModelParent = 3;
	g_player.aModel[4].pos = D3DXVECTOR3(-5.3f, 0.0f, 0.0f);
	g_player.aModel[4].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	g_player.aModel[5].nIdxModelParent = 0;
	g_player.aModel[5].pos = D3DXVECTOR3(7.0f, 12.0f, 0.0f);
	g_player.aModel[5].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	g_player.aModel[6].nIdxModelParent = 5;
	g_player.aModel[6].pos = D3DXVECTOR3(4.0f, 1.0f, 0.0f);
	g_player.aModel[6].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	g_player.aModel[7].nIdxModelParent = 6;
	g_player.aModel[7].pos = D3DXVECTOR3(5.3f, 0.0f, 0.0f);
	g_player.aModel[7].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	g_player.aModel[8].nIdxModelParent = 0;
	g_player.aModel[8].pos = D3DXVECTOR3(-3.0f, -1.0f, 0.0f);
	g_player.aModel[8].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	g_player.aModel[9].nIdxModelParent = 8;
	g_player.aModel[9].pos = D3DXVECTOR3(0.0f, -2.0f, 0.0f);
	g_player.aModel[9].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	g_player.aModel[10].nIdxModelParent = 0;
	g_player.aModel[10].pos = D3DXVECTOR3(3.0f, -1.0f, 0.0f);
	g_player.aModel[10].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	g_player.aModel[11].nIdxModelParent = 10;
	g_player.aModel[11].pos = D3DXVECTOR3(0.0f, -2.0f, 0.0f);
	g_player.aModel[11].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);


	for (int nCntModel = 0; nCntModel < g_player.nNumModel; nCntModel++)
	{
		D3DXMATERIAL* pMat;//�}�e���A���ւ̃|�C���^

		//�}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)g_player.aModel[nCntModel].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_player.aModel[nCntModel].dwNumMat; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				//�e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_player.aModel[nCntModel].pTexture[nCntMat]);
			}
		}

		//���_���̎擾
		nNumVtx = g_player.aModel[nCntModel].pMesh->GetNumVertices();
		//���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFVF = D3DXGetFVFVertexSize(g_player.aModel[nCntModel].pMesh->GetFVF());
		//���_�o�b�t�@�̃��b�N
		g_player.aModel[nCntModel].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

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
		g_player.aModel[nCntModel].pMesh->UnlockVertexBuffer();
	}

	g_player.size = g_player.vtxMaxBlock - g_player.vtxMinBlock;

	g_player.g_nIdxShadow = SetShadow(g_player.pos,g_player.rot);
}

void UninitPlayer(void)
{
	for (int nCntModel = 0; nCntModel < g_player.nNumModel; nCntModel++)
	{

		//�e�N�X�`���̉��
		if (g_player.aModel[nCntModel].pMesh != NULL)
		{
			g_player.aModel[nCntModel].pMesh->Release();
			g_player.aModel[nCntModel].pMesh = NULL;
		}

		//���_�o�b�t�@�̉��
		if (g_player.aModel[nCntModel].pBuffMat != NULL)
		{
			g_player.aModel[nCntModel].pBuffMat->Release();
			g_player.aModel[nCntModel].pBuffMat = NULL;
		}

		for (int nCnt = 0; nCnt < 1; nCnt++)
		{
			//�e�N�X�`���̔j��
			if (g_player.aModel[nCntModel].pTexture[nCnt] != NULL)
			{
				g_player.aModel[nCntModel].pTexture[nCnt]->Release();
				g_player.aModel[nCntModel].pTexture[nCnt] = NULL;
			}
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
	D3DXMatrixIdentity(&g_player.mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_player.rot.y, g_player.rot.x, g_player.rot.z);
	D3DXMatrixMultiply(&g_player.mtxWorld, &g_player.mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_player.pos.x, g_player.pos.y, g_player.pos.z);
	D3DXMatrixMultiply(&g_player.mtxWorld, &g_player.mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_player.mtxWorld);

	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	//�S���f��(�p�[�c�̕`��)
	for (int nCntModel = 0; nCntModel < g_player.nNumModel; nCntModel++)
	{
		D3DXMATRIX mtxRotModel, mtxTransModel;//�v�Z�p�}�g���b�N�X
		D3DXMATRIX mtxParent;//�e�̃}�g���b�N�X

		//�p�[�c�̃��[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_player.aModel[nCntModel].mtxWorld);

		//�p�[�c�̌����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_player.aModel[nCntModel].rot.y, g_player.aModel[nCntModel].rot.x, g_player.aModel[nCntModel].rot.z);
		D3DXMatrixMultiply(&g_player.aModel[nCntModel].mtxWorld, &g_player.aModel[nCntModel].mtxWorld, &mtxRotModel);

		//�p�[�c�̈ʒu(�I�t�Z�b�g)�𔽉f
		D3DXMatrixTranslation(&mtxTransModel, g_player.aModel[nCntModel].pos.x, g_player.aModel[nCntModel].pos.y, g_player.aModel[nCntModel].pos.z);
		D3DXMatrixMultiply(&g_player.aModel[nCntModel].mtxWorld, &g_player.aModel[nCntModel].mtxWorld, &mtxTransModel);

		//�p�[�c�́u�e�̃}�g���b�N�X�v��ݒ�
		if (g_player.aModel[nCntModel].nIdxModelParent != -1)
		{//�e���f��������ꍇ
			mtxParent = g_player.aModel[g_player.aModel[nCntModel].nIdxModelParent].mtxWorld;
		}
		else
		{//�e���f�����Ȃ��ꍇ
			mtxParent = g_player.mtxWorld;
		}

		//�Z�o�����u�p�[�c�̃��[���h�}�g���b�N�X�v�Ɓu�e�̃}�g���b�N�X�v���|�����킹��
		D3DXMatrixMultiply(&g_player.aModel[nCntModel].mtxWorld,
						   &g_player.aModel[nCntModel].mtxWorld,
						   &mtxParent);

		//�p�[�c�̃��[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD,
			&g_player.aModel[nCntModel].mtxWorld);
		
		//�}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)g_player.aModel[nCntModel].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_player.aModel[nCntModel].dwNumMat; nCntMat++)
		{
			//�}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_player.aModel[nCntModel].pTexture[nCntMat]);

			//���f��(�p�[�c)�̕`��
			g_player.aModel[nCntModel].pMesh->DrawSubset(nCntMat);
		}
	}

	//�ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

Player* GetPlayer()
{
	return &g_player;
}
