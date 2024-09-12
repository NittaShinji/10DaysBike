#include "TitleScene.h"
#include "KeyboardInput.h"
#include "SceneManager.h"
#include "Inform.h"

int TitleScene::titleHandle_;

TitleScene::~TitleScene()
{
	DeleteGraph(titleHandle_);
}

void TitleScene::StaticInitialize()
{
	//画像読み込み
	titleHandle_ = LoadGraph((RESOUCE_PATH + "Title.png").c_str());
}

void TitleScene::Initialize()
{
	
}

void TitleScene::Update()
{
	if (KeyboardInput::GetInstance().GetTriggerKey(KEY_INPUT_SPACE)) {
		//ゲームシーンに移動
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
