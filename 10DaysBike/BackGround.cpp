#include "BackGround.h"
#include "DxLib.h"
#include "Inform.h"
#include "PlayerState.h"

void BackGround::Init()
{
	
	for (int i = 0; i < backGroundGraphNum; i++)
	{
		//�摜�ǂݍ���
		backGroundObj[i].graphHandle = LoadGraph((RESOUCE_PATH + "backGround.png").c_str());
		//�ʒu�̏�����
		backGroundObj[i].pos.x = UI_SIZE.x;
		backGroundObj[i].pos.y = i * kBackGroundGraphHeight;
		backGroundObj[i].defaultPos = backGroundObj[i].pos;
	}

	scrollValue_ = 0;
}

void BackGround::Update(int playerSpeed, IPlayerState* playerState)
{
	PlayerStateBurstUp* fireBulletStateUp = dynamic_cast<PlayerStateBurstUp*>(playerState);
	PlayerStateBurstDown* fireBulletStateDown = dynamic_cast<PlayerStateBurstDown*>(playerState);

	if (!fireBulletStateUp)
	{
		//
		if (!fireBulletStateDown)
		{
			saveScrollValue_ = playerSpeed;
		}

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
	else
	{
		// �v���C���[�̃X�s�[�h�ɉ����ăX�N���[���l�𑝉�
		scrollValue_ += -(std::abs(saveScrollValue_) * kBackGroundScllolNum);

		// �摜�̍����Ɋ�Â��ă��[�v�����邽�߂̕ϐ�
		int backgroundHeight = kBackGroundGraphHeight;

		// �w�i�摜����ʊO�ɏo����Ĕz�u����
		for (int i = 0; i < backGroundGraphNum; i++)
		{
			// �X�N���[���l��w�i��Y���W�ɔ��f
			backGroundObj[i].pos.y += -(std::abs(saveScrollValue_) * kBackGroundScllolNum);

			// �w�i����ʊO�i��j�ɏo���ꍇ�A��ʉ��ɍĔz�u
			if (backGroundObj[i].pos.y <= -backgroundHeight)
			{
				backGroundObj[i].pos.y += backgroundHeight * backGroundGraphNum;
			}
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
