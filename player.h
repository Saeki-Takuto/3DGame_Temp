//==================================================================
//
//���f������<model.h>
//Author:Saeki Takuto
//
//==================================================================
#ifndef _PLAYER_H_	//���̃}�N����`������ĂȂ�������
#define _PLAYER_H_	//2�d�C���N���[�h�h�~�̃}�N����`

#include "main.h"
#include "model.h"

//�v���C���[�̍\����
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
	Model aModel[12];//���f���i�p�[�c)
	int nNumModel;	//���f��(�p�[�c)�̑���
}Player;

//�v���g�^�C�v�錾
void InitPlayer(void);//����������
void UninitPlayer(void);//�I������
void UpdatePlayer(void);//�X�V����
void DrawPlayer(void);//�`�揈��
Player* GetPlayer();

#endif