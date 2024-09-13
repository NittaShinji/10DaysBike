#include "ResultScene.h"
#include "KeyboardInput.h"
#include "SceneManager.h"
#include "Inform.h"

int ResultScene::gameOverImageHandle_;
int ResultScene::clearImageHandle_;
int ResultScene::gameOverSoundHandle_;
int ResultScene::clearSoundHandle_;
int ResultScene::registHandle_;

void ResultScene::StaticInitialize()
{
	clearImageHandle_ = LoadGraph((RESOUCE_PATH + "GameClear.png").c_str());
	gameOverImageHandle_ = LoadGraph((RESOUCE_PATH + "GameOver.png").c_str());
	clearSoundHandle_ = LoadSoundMem((RESOUCE_PATH + "GameClearSE.wav").c_str());
	gameOverSoundHandle_ = LoadSoundMem((RESOUCE_PATH + "GameOverSE.wav").c_str());
	registHandle_ = LoadGraph((RESOUCE_PATH + "RegistScore.png").c_str());
}

void ResultScene::DeleteResource()
{
	DeleteSoundMem(gameOverImageHandle_);
	DeleteSoundMem(clearImageHandle_);
	DeleteSoundMem(gameOverSoundHandle_);
	DeleteSoundMem(clearSoundHandle_);
	DeleteSoundMem(registHandle_);
}

void ResultScene::Initialize()
{
	gameState_->scoreManager_->ResetInit();
	gameState_->scoreManager_->GetResultScore()->SetPos(Vec2(480,805));
	gameState_->scoreManager_->GetResultScore()->SetIsDrum(true);
	gameState_->scoreManager_->SetNotRankDrumRoll();

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
	if (KeyboardInput::GetInstance().GetTriggerKey(KEY_INPUT_SPACE)) 
	{
		//if (gameState_->scoreManager_->GetIsjugeRegist() == false && gameState_->scoreManager_->GetIsRegistRanking() == true)
		//{
		//	//�Q�[���V�[���Ɉړ�
		//	if (CheckSoundMem(gameOverSoundHandle_) == 1)
		//	{
		//		StopSoundMem(gameOverSoundHandle_);
		//	}
		//	if (CheckSoundMem(clearSoundHandle_) == 1)
		//	{
		//		StopSoundMem(clearSoundHandle_);
		//	}

		//	SceneManager::GetInstance()->ChangeScene("TITLE");
		//	gameState_->scoreManager_->Reset();
		//	gameState_->SetIsClear(false);
		//}

		if (gameState_->scoreManager_->GetIsjugeRegist() == false)
		{
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
	}

	if (waitScoreTimer_ > 0 && isStartDrumScore_ == false)
	{
		waitScoreTimer_--;
		if (waitScoreTimer_ <= 0)
		{
			isStartDrumScore_ = true;
		}
	}

	if (gameState_->scoreManager_->GetResultScore()->GetIsFinishDrum() == true)
	{
		gameState_->scoreManager_->RegistRanking();
	}

	if(isStartDrumScore_ == true)
	{
		gameState_->scoreManager_->ResetUpdate();
	}
}

void ResultScene::Draw()
{
	if (gameState_->GetIsClear()) 
	{
		//�Q�[���N���A�`��
		DrawGraph(0, 0, clearImageHandle_, true);

		if (gameState_->scoreManager_->GetIsjugeRegist() == true)
		{
			DrawGraph(0, 210, registHandle_, true);
		}
	}
	else
	{
		//�Q�[���I�[�o�[�`��
		DrawGraph(0, 0, gameOverImageHandle_, true);
	}

	gameState_->scoreManager_->ResetDraw();
	gameState_->scoreManager_->DrawRanking();

}