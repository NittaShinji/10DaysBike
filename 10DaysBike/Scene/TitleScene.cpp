#include "TitleScene.h"
#include "KeyboardInput.h"
#include "SceneManager.h"

void TitleScene::Initialize()
{}

void TitleScene::Update()
{
	if (KeyboardInput::GetInstance().GetTriggerKey(KEY_INPUT_RETURN)) {
		//�Q�[���V�[���Ɉړ�
		SceneManager::GetInstance()->ChangeScene("GAME");
	}

	gameState_->scoreManager_->Update();
}

void TitleScene::Draw()
{
	const unsigned int stringCr = GetColor(255, 255, 255);
	DrawString(200, 100, "TITLE PUSH ENTER", stringCr);

	gameState_->scoreManager_->Draw();

	//�^�C�g���`��

	//�w�i�`��

}
