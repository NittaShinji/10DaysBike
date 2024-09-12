#include "ClearScene.h"
#include "KeyboardInput.h"
#include "SceneManager.h"

void ClearScene::Initialize()
{
}

void ClearScene::Update()
{
	if (KeyboardInput::GetInstance().GetTriggerKey(KEY_INPUT_RETURN)) {
		//ƒQ[ƒ€ƒV[ƒ“‚ÉˆÚ“®
		SceneManager::GetInstance()->ChangeScene("TITLE");
	}
}

void ClearScene::Draw()
{
	const unsigned int stringCr = GetColor(255, 255, 255);
	DrawString(200, 100, "CLEAR  PUSH ENTER", stringCr);
}
