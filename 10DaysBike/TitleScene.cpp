#include "TitleScene.h"
#include "KeyboardInput.h"
#include "SceneManager.h"

void TitleScene::Initialize()
{

}

void TitleScene::Update()
{
	if (KeyboardInput::GetInstance().GetTriggerKey(KEY_INPUT_RETURN)) {
		//�Q�[���V�[���Ɉړ�
		SceneManager::GetInstance()->ChangeScene("GAME");
	}
}

void TitleScene::Draw()
{
	const unsigned int stringCr = GetColor(255, 255, 255);
	DrawString(200, 100, "TITLE PUSH ENTER", stringCr);

	//�^�C�g���`��

	//�w�i�`��

}
