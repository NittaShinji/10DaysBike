#include "BackGround.h"
#include "DxLib.h"
#include "Inform.h"
#include "PlayerState.h"

void BackGround::Init()
{
	
	for (int i = 0; i < backGroundGraphNum; i++)
	{
		//画像読み込み
		backGroundObj[i].graphHandle = LoadGraph((RESOUCE_PATH + "backGround.png").c_str());
		//位置の初期化
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

		// プレイヤーのスピードに応じてスクロール値を増加
		scrollValue_ += -(std::abs(playerSpeed) * kBackGroundScllolNum);

		// 画像の高さに基づいてループさせるための変数
		int backgroundHeight = kBackGroundGraphHeight;

		// 背景画像が画面外に出たら再配置する
		for (int i = 0; i < backGroundGraphNum; i++)
		{
			// スクロール値を背景のY座標に反映
			backGroundObj[i].pos.y += -(std::abs(playerSpeed) * kBackGroundScllolNum);

			// 背景が画面外（上）に出た場合、画面下に再配置
			if (backGroundObj[i].pos.y <= -backgroundHeight)
			{
				backGroundObj[i].pos.y += backgroundHeight * backGroundGraphNum;
			}
		}
	}
	else
	{
		// プレイヤーのスピードに応じてスクロール値を増加
		scrollValue_ += -(std::abs(saveScrollValue_) * kBackGroundScllolNum);

		// 画像の高さに基づいてループさせるための変数
		int backgroundHeight = kBackGroundGraphHeight;

		// 背景画像が画面外に出たら再配置する
		for (int i = 0; i < backGroundGraphNum; i++)
		{
			// スクロール値を背景のY座標に反映
			backGroundObj[i].pos.y += -(std::abs(saveScrollValue_) * kBackGroundScllolNum);

			// 背景が画面外（上）に出た場合、画面下に再配置
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
		// 背景画像を描画
		DrawGraph(backGroundObj[i].pos.x, backGroundObj[i].pos.y, backGroundObj[i].graphHandle, true);
	}
}
