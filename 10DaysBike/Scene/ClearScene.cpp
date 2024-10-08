#include "ClearScene.h"
#include "KeyboardInput.h"
#include "SceneManager.h"

void ClearScene::Initialize()
{
}

void ClearScene::Update()
{
	if (KeyboardInput::GetInstance().GetTriggerKey(KEY_INPUT_RETURN)) {
		//ゲームシーンに移動
		SceneManager::GetInstance()->ChangeScene("TITLE");
	}

	gameState_->scoreManager_->Update();
}

void ClearScene::Draw()
{
	const unsigned int stringCr = GetColor(255, 255, 255);
	DrawString(200, 100, "CLEAR  PUSH ENTER", stringCr);

	gameState_->scoreManager_->Draw();
}
