#include "ResultScene.h"
#include "KeyboardInput.h"
#include "SceneManager.h"
#include "Inform.h"

int ResultScene::gameOverImageHandle_;
int ResultScene::clearImageHandle_;

ResultScene::~ResultScene()
{
	DeleteGraph(clearImageHandle_);
	DeleteGraph(gameOverImageHandle_);
}

void ResultScene::StaticInitialize()
{
	clearImageHandle_ = LoadGraph((RESOUCE_PATH + "GameClear.png").c_str());
	gameOverImageHandle_ = LoadGraph((RESOUCE_PATH + "GameOver.png").c_str());
}

void ResultScene::Initialize()
{

}

void ResultScene::Update()
{
	if (KeyboardInput::GetInstance().GetTriggerKey(KEY_INPUT_RETURN)) {
		//ゲームシーンに移動
		SceneManager::GetInstance()->ChangeScene("TITLE");
		gameState_->SetIsClear(false);
	}

	gameState_->scoreManager_->Update();
}

void ResultScene::Draw()
{
	if (gameState_->GetIsClear()) 
	{
		const unsigned int stringCr = GetColor(255, 255, 255);
		DrawString(200, 100, "CLEAR  PUSH ENTER", stringCr);

		//ゲームクリア描画
		DrawGraph(0, 0, clearImageHandle_, true);
	}
	else
	{
		//ゲームオーバー描画
		DrawGraph(0, 0, gameOverImageHandle_, true);
	}

	gameState_->scoreManager_->Draw();
}