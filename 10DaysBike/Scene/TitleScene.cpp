#include "TitleScene.h"
#include "KeyboardInput.h"
#include "SceneManager.h"
#include "Inform.h"

int TitleScene::titleHandle_;
int TitleScene::bgmHandle_;

void TitleScene::StaticInitialize()
{
	//画像読み込み
	titleHandle_ = LoadGraph((RESOUCE_PATH + "Title.png").c_str());
	bgmHandle_ = LoadSoundMem((RESOUCE_PATH + "titleBGM.wav").c_str());
}

void TitleScene::Initialize()
{
	playTimer_ = kDefaultPlaytoTime_;
	
	// 音量の設定
	//ChangeVolumeSoundMem(255 * 50 / 100, bgmHandle_);
	////BGM再生
	//PlaySoundMem(bgmHandle_, DX_PLAYTYPE_LOOP);
	gameState_->scoreManager_->SetIsRegistRanking(false);
	gameState_->scoreManager_->SetIsjugeRegist(false);
	gameState_->scoreManager_->InitRanking();
	gameState_->scoreManager_->UpdateRanking();
}

void TitleScene::Update()
{
	if (KeyboardInput::GetInstance().GetTriggerKey(KEY_INPUT_Y)) 
	{
		if (isTakeRank_ == false)
		{
			isTakeRank_ = true;
			gameState_->scoreManager_->InitRanking();
		}
	}

	if (isTakeRank_ == true)
	{
		gameState_->scoreManager_->UpdateRanking();
	}


	if (isPlayBgm_ == false)
	{
		if (playTimer_ > 0)
		{
			playTimer_--;
		}
		else
		{
			isPlayBgm_ = true;
			// 音量の設定
			ChangeVolumeSoundMem(255 * 50 / 100, bgmHandle_);
			//BGM再生
			PlaySoundMem(bgmHandle_, DX_PLAYTYPE_LOOP);
		}
	}

	if (KeyboardInput::GetInstance().GetTriggerKey(KEY_INPUT_SPACE)) {
		//ゲームシーンに移動
		StopSoundMem(bgmHandle_);
		SceneManager::GetInstance()->ChangeScene("GAME");
	}

	gameState_->scoreManager_->Update();
}

void TitleScene::Draw()
{
	//タイトル描画
	DrawGraph(0, 0, titleHandle_, true);

	//gameState_->scoreManager_->DrawRanking();
	//背景描画

}

void TitleScene::DeleteResource()
{
	DeleteGraph(titleHandle_);
	DeleteSoundMem(bgmHandle_);
}
