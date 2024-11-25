//==================================================================
//
//�Ǐ���<wall.cpp>
//Author:Saeki Takuto
//
//==================================================================

#include "main.h"
#include "wall.h"

//�O���[�o���ϐ��錾
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWall = NULL;//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureWall = NULL;		//�e�N�X�`���ւ̃|�C���^
Wall g_aWall[NUM_WALL];
//D3DXVECTOR3 g_posWall;//�ʒu
//D3DXVECTOR3 g_rotWall;//����
//D3DXMATRIX g_mtxWorldWall;//���[���h�}�g���b�N�X

//==================================================================
//����������
//==================================================================
void InitWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/wall000.jpg",
		&g_pTextureWall);

	//���_�o�b�t�@�̐ݒ�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4*NUM_WALL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffWall, NULL);

	for (int nCntWall = 0; nCntWall < NUM_WALL; nCntWall++)
	{
		g_aWall[nCntWall].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aWall[nCntWall].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aWall[nCntWall].bUse = false;
	}

	VERTEX_3D* pVtx = NULL;
	//���_�o�b�t�@�����b�N
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W��ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�e���_�̖@���̐ݒ�(���x�N�g���̑傫����1�ɂ���K�v������)
	pVtx[0].nor = D3DXVECTOR3(0.0, 1.0, 0.0);
	pVtx[1].nor = D3DXVECTOR3(0.0, 1.0, 0.0);
	pVtx[2].nor = D3DXVECTOR3(0.0, 1.0, 0.0);
	pVtx[3].nor = D3DXVECTOR3(0.0, 1.0, 0.0);

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx += 4;

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffWall->Unlock();
}

//==================================================================
//�I������
//==================================================================
void UninitWall(void)
{
	//�e�N�X�`���̉��
	if (g_pTextureWall != NULL)
	{
		g_pTextureWall->Release();
		g_pTextureWall = NULL;
	}

	//���_�o�b�t�@�̉��
	if (g_pVtxBuffWall != NULL)
	{
		g_pVtxBuffWall->Release();
		g_pVtxBuffWall = NULL;
	}
}

//==================================================================
//�X�V����
//==================================================================
void UpdateWall(void)
{
}

//==================================================================
//�`�揈��
//==================================================================
void DrawWall(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	for (int nCntWall = 0; nCntWall < NUM_WALL; nCntWall++)
	{
		if (g_aWall[nCntWall].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aWall[nCntWall].mtxWorld);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aWall[nCntWall].rot.y, g_aWall[nCntWall].rot.x, g_aWall[nCntWall].rot.z);
			D3DXMatrixMultiply(&g_aWall[nCntWall].mtxWorld, &g_aWall[nCntWall].mtxWorld, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aWall[nCntWall].pos.x, g_aWall[nCntWall].pos.y, g_aWall[nCntWall].pos.z);
			D3DXMatrixMultiply(&g_aWall[nCntWall].mtxWorld, &g_aWall[nCntWall].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aWall[nCntWall].mtxWorld);

			//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffWall, 0, sizeof(VERTEX_3D));

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureWall);

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntWall*4, 2);
		}
	}
}

void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float alpha)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	VERTEX_3D* pVtx = NULL;
	//���_�o�b�t�@�����b�N
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntWall = 0; nCntWall < NUM_WALL; nCntWall++)
	{
		if (g_aWall[nCntWall].bUse == false)
		{
			g_aWall[nCntWall].pos = pos;
			g_aWall[nCntWall].rot = rot;
			g_aWall[nCntWall].bUse = true;

			//���_���W��ݒ�
			pVtx[0].pos = D3DXVECTOR3(-150.0f, +150.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(+150.0f, +150.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-150.0f, -150.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(+150.0f, -150.0f, 0.0f);

			//�e���_�̖@���̐ݒ�(���x�N�g���̑傫����1�ɂ���K�v������)
			pVtx[0].nor = D3DXVECTOR3(0.0, 1.0, 0.0);
			pVtx[1].nor = D3DXVECTOR3(0.0, 1.0, 0.0);
			pVtx[2].nor = D3DXVECTOR3(0.0, 1.0, 0.0);
			pVtx[3].nor = D3DXVECTOR3(0.0, 1.0, 0.0);

			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, alpha);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, alpha);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, alpha);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, alpha);

			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);


			break;
		}
		pVtx += 4;
	}

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffWall->Unlock();
}


