#include "BackGround.h"
#include "DxLib.h"
#include "Inform.h"

void BackGround::Init()
{
	
	for (int i = 0; i < backGroundGraphNum; i++)
	{
		//�摜�ǂݍ���
		backGroundObj[i].graphHandle = LoadGraph((RESOUCE_PATH + "backGround.png").c_str());
		//�ʒu�̏�����
		backGroundObj[i].pos.x = 0;
		backGroundObj[i].pos.y = i * kBackGroundGraphHeight;
		backGroundObj[i].defaultPos = backGroundObj[i].pos;
	}

	scrollValue_ = 0;
}

void BackGround::Update(int playerSpeed)
{
	// �v���C���[�̃X�s�[�h�ɉ����ăX�N���[���l�𑝉�
	scrollValue_ += -(std::abs(playerSpeed) * kBackGroundScllolNum);

	// �摜�̍����Ɋ�Â��ă��[�v�����邽�߂̕ϐ�
	int backgroundHeight = kBackGroundGraphHeight;

	// �w�i�摜����ʊO�ɏo����Ĕz�u����
	for (int i = 0; i < backGroundGraphNum; i++)
	{
		// �X�N���[���l��w�i��Y���W�ɔ��f
		backGroundObj[i].pos.y += -(std::abs(playerSpeed) * kBackGroundScllolNum);

		// �w�i����ʊO�i��j�ɏo���ꍇ�A��ʉ��ɍĔz�u
		if (backGroundObj[i].pos.y <= -backgroundHeight)
		{
			backGroundObj[i].pos.y += backgroundHeight * backGroundGraphNum;
		}
	}
}

void BackGround::Draw()
{
	for (size_t i = 0; i < backGroundGraphNum; i++)
	{
		// �w�i�摜��`��
		DrawGraph(backGroundObj[i].pos.x, backGroundObj[i].pos.y, backGroundObj[i].graphHandle, true);
	}
}
