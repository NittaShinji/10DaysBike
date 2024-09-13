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
	const unsigned int stringCr = GetColor(255, 255, 255);
	DrawString(200, 100, "TITLE PUSH ENTER", stringCr);

	gameState_->scoreManager_->Draw();

	//�^�C�g���`��
	DrawGraph(0, 0, titleHandle_, true);

	//�w�i�`��

}

void TitleScene::DeleteResource()
{
	DeleteGraph(titleHandle_);
	DeleteSoundMem(bgmHandle_);
}
