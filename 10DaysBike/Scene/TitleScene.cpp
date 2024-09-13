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
}

void TitleScene::Update()
{
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
	const unsigned int stringCr = GetColor(255, 255, 255);
	DrawString(200, 100, "TITLE PUSH ENTER", stringCr);

	gameState_->scoreManager_->Draw();

	//タイトル描画
	DrawGraph(0, 0, titleHandle_, true);

	//背景描画

}

void TitleScene::DeleteResource()
{
	DeleteGraph(titleHandle_);
	DeleteSoundMem(bgmHandle_);
}
