#include "TitleScene.h"
#include "KeyboardInput.h"
#include "SceneManager.h"
#include "Inform.h"

int TitleScene::titleHandle_;
int TitleScene::bgmHandle_;

void TitleScene::StaticInitialize()
{
	//�摜�ǂݍ���
	titleHandle_ = LoadGraph((RESOUCE_PATH + "Title.png").c_str());
	bgmHandle_ = LoadSoundMem((RESOUCE_PATH + "titleBGM.wav").c_str());
}

void TitleScene::Initialize()
{
	playTimer_ = kDefaultPlaytoTime_;
	
	// ���ʂ̐ݒ�
	//ChangeVolumeSoundMem(255 * 50 / 100, bgmHandle_);
	////BGM�Đ�
	//PlaySoundMem(bgmHandle_, DX_PLAYTYPE_LOOP);
	gameState_->scoreManager_->SetIsRegistRanking(false);
	gameState_->scoreManager_->SetIsjugeRegist(false);
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
			// ���ʂ̐ݒ�
			ChangeVolumeSoundMem(255 * 50 / 100, bgmHandle_);
			//BGM�Đ�
			PlaySoundMem(bgmHandle_, DX_PLAYTYPE_LOOP);
		}
	}

	if (KeyboardInput::GetInstance().GetTriggerKey(KEY_INPUT_SPACE)) {
		//�Q�[���V�[���Ɉړ�
		StopSoundMem(bgmHandle_);
		SceneManager::GetInstance()->ChangeScene("GAME");
	}

	gameState_->scoreManager_->Update();
}

void TitleScene::Draw()
{
	//�^�C�g���`��
	DrawGraph(0, 0, titleHandle_, true);

	//gameState_->scoreManager_->DrawRanking();

	//�w�i�`��

}

void TitleScene::DeleteResource()
{
	DeleteGraph(titleHandle_);
	DeleteSoundMem(bgmHandle_);
}
