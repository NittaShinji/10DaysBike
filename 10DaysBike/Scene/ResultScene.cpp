#include "ResultScene.h"
#include "KeyboardInput.h"
#include "SceneManager.h"
#include "Inform.h"

int ResultScene::gameOverImageHandle_;
int ResultScene::clearImageHandle_;
int ResultScene::gameOverSoundHandle_;
int ResultScene::clearSoundHandle_;

void ResultScene::StaticInitialize()
{
	clearImageHandle_ = LoadGraph((RESOUCE_PATH + "GameClear.png").c_str());
	gameOverImageHandle_ = LoadGraph((RESOUCE_PATH + "GameOver.png").c_str());
	clearSoundHandle_ = LoadSoundMem((RESOUCE_PATH + "GameClearSE.wav").c_str());
	gameOverSoundHandle_ = LoadSoundMem((RESOUCE_PATH + "GameOverSE.wav").c_str());
}

void ResultScene::DeleteResource()
{
	DeleteSoundMem(gameOverImageHandle_);
	DeleteSoundMem(clearImageHandle_);
	DeleteSoundMem(gameOverSoundHandle_);
	DeleteSoundMem(clearSoundHandle_);
}

void ResultScene::Initialize()
{
	
	//�N���A���Ă���΃Q�[���N���A
	if (gameState_->GetIsClear() == true)
	{
		// ���ʂ̐ݒ�
		ChangeVolumeSoundMem(255 * 50 / 100, clearSoundHandle_);
		//BGM�Đ�
		PlaySoundMem(clearSoundHandle_, DX_PLAYTYPE_BACK);
	}
	//�N���A���Ă��Ȃ���΃Q�[���I�[�o�[
	else
	{
		// ���ʂ̐ݒ�
		ChangeVolumeSoundMem(255 * 50 / 100, gameOverSoundHandle_);
		//BGM�Đ�
		PlaySoundMem(gameOverSoundHandle_, DX_PLAYTYPE_BACK);
	}
}

void ResultScene::Update()
{
	if (KeyboardInput::GetInstance().GetTriggerKey(KEY_INPUT_RETURN)) {
		//�Q�[���V�[���Ɉړ�
		if (CheckSoundMem(gameOverSoundHandle_) == 1)
		{
			StopSoundMem(gameOverSoundHandle_);
		}
		if (CheckSoundMem(clearSoundHandle_) == 1)
		{
			StopSoundMem(clearSoundHandle_);
		}
		SceneManager::GetInstance()->ChangeScene("TITLE");
		gameState_->scoreManager_->Reset();
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

		//�Q�[���N���A�`��
		DrawGraph(0, 0, clearImageHandle_, true);
	}
	else
	{
		//�Q�[���I�[�o�[�`��
		DrawGraph(0, 0, gameOverImageHandle_, true);
	}

	gameState_->scoreManager_->Draw();
}