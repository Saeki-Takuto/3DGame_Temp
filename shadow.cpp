//==================================================================
//
//�e����<shadow.cpp>
//Author:Saeki Takuto
//
//==================================================================

#include "main.h"
#include "shadow.h"

//�O���[�o���ϐ��錾
Shadow g_aShadow[64];

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffShadow = NULL;//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureShadow = NULL;		//�e�N�X�`���ւ̃|�C���^
//D3DXVECTOR3 g_posShadow;//�ʒu
//D3DXVECTOR3 g_rotShadow;//����
//D3DXMATRIX g_mtxWorldShadow;//���[���h�}�g���b�N�X

//==================================================================
//����������
//==================================================================
void InitShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/effect000.jpg",
		&g_pTextureShadow);


	for (int nCntShadow = 0; nCntShadow < 64; nCntShadow++)
	{
		g_aShadow[nCntShadow].bUse = false;
		g_aShadow[nCntShadow].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aShadow[nCntShadow].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	}
	//���_�o�b�t�@�̐ݒ�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * 64,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffShadow, NULL);

	VERTEX_3D* pVtx = NULL;
	//���_�o�b�t�@�����b�N
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntShadow = 0; nCntShadow < 64; nCntShadow++)
	{
		//���_���W��ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aShadow[nCntShadow].pos.x-10.0f, g_aShadow[nCntShadow].pos.y+0.1f, g_aShadow[nCntShadow].pos.z+10.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aShadow[nCntShadow].pos.x+10.0f, g_aShadow[nCntShadow].pos.y+0.1f, g_aShadow[nCntShadow].pos.z+10.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aShadow[nCntShadow].pos.x-10.0f, g_aShadow[nCntShadow].pos.y+0.1f, g_aShadow[nCntShadow].pos.z-10.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aShadow[nCntShadow].pos.x+10.0f, g_aShadow[nCntShadow].pos.y+0.1f, g_aShadow[nCntShadow].pos.z-10.0f);

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
	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffShadow->Unlock();
}

//==================================================================
//�I������
//==================================================================
void UninitShadow(void)
{
	//�e�N�X�`���̉��
	if (g_pTextureShadow != NULL)
	{
		g_pTextureShadow->Release();
		g_pTextureShadow = NULL;
	}

	//���_�o�b�t�@�̉��
	if (g_pVtxBuffShadow != NULL)
	{
		g_pVtxBuffShadow->Release();
		g_pVtxBuffShadow = NULL;
	}
}

//==================================================================
//�X�V����
//==================================================================
void UpdateShadow(void)
{
}

//==================================================================
//�`�揈��
//==================================================================
void DrawShadow(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	//���Z�����̐ݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	for (int nCntShadow = 0; nCntShadow < 64; nCntShadow++)
	{
		if (g_aShadow[nCntShadow].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aShadow[nCntShadow].mtxWorld);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aShadow[nCntShadow].rot.y, g_aShadow[nCntShadow].rot.x, g_aShadow[nCntShadow].rot.z);
			D3DXMatrixMultiply(&g_aShadow[nCntShadow].mtxWorld, &g_aShadow[nCntShadow].mtxWorld, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aShadow[nCntShadow].pos.x, g_aShadow[nCntShadow].pos.y, g_aShadow[nCntShadow].pos.z);
			D3DXMatrixMultiply(&g_aShadow[nCntShadow].mtxWorld, &g_aShadow[nCntShadow].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aShadow[nCntShadow].mtxWorld);

			//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffShadow, 0, sizeof(VERTEX_3D));

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureShadow);

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,nCntShadow * 4, 2);
		}
	}
	//�ݒ�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

int SetShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	int nCntShadow;

	for (nCntShadow = 0; nCntShadow<64;nCntShadow++)
	{
		//bUse��false�̏ꍇ�Apos,rot������bUse��true�ɂ���
		if (g_aShadow[nCntShadow].bUse == false)
		{
			g_aShadow[nCntShadow].pos = pos;
			g_aShadow[nCntShadow].rot = rot;
			g_aShadow[nCntShadow].bUse = true;
			break;
		}
	}
	return nCntShadow;//�e�̔ԍ�(index)��Ԃ�
}

void SetPositionShadow(int nIdxShadow, D3DXVECTOR3 pos)
{
	//�����Ŏw�肳�ꂽ�ԍ��̉e��pos��ݒ�
	g_aShadow[nIdxShadow].pos = pos;
}