#pragma once
#include "BaseScene.h"

class ResultScene : public BaseScene
{
public:

	//�ÓI������
	static void StaticInitialize();

	//���\�[�X�폜
	static void DeleteResource();

	//������
	void Initialize() override;

	//���t���[���X�V
	void Update() override;

	//�`��
	void Draw() override;

private:

	//�N���A�摜
	static int clearImageHandle_;
	//�Q�[���I�[�o�[�摜
	static int gameOverImageHandle_;
	//�o�^���摜
	static int registHandle_;

	//�Q�[����BGM
	static int gameOverSoundHandle_;
	//�X�^�[�g��
	static int clearSoundHandle_;

	const int waitScoreTime = 60;
	int waitScoreTimer_ = waitScoreTime;

	bool isStartDrumScore_ = false;
};