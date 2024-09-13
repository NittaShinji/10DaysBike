#pragma once
#include "Vec2.h"
class Score
{
public:

	static const int kScoreDigitNum_ = 7;
	static const int kScoreNumberNum_ = 10;

public:
	~Score();
	static void Load();
	void Init(Vec2 pos);
	void Update();
	void Draw();
	int GetScore() { return score_; }
	int GetTargetScore() { return targetScore_; }
	bool GetIsDrum() { return isDrumRoll_; }

	void SetIsDrum(bool isDrumRoll) { isDrumRoll_ = isDrumRoll; }
	void SetDrumTimer(float drumRollTimer) { drumTimer_ = drumRollTimer; }
	void SetTargetScore(int targetScore) { targetScore_ = targetScore; }

	//�X�R�A�ǉ�
	void AddScore(int32_t addNum)
	{
		//if (isDrumRoll_)
		//{
		//	// �h�������[�����̏ꍇ�A�ǉ��̃X�R�A�̓h�������[���̖ڕW�X�R�A�ɔ��f
		//	drumRollscoreTarget_ += addNum;
		//}
		//else
		//{
		//	score_ += addNum;
		//}

		score_ += addNum;
	};

	//���l���������ɓ���
	//�X�R�A����
	void InputNumberTS();
	void InputDrumRoll();

	float EaseInOutExpo(float t, float b, float c, float d);
	float EaseOutSine(float t, float b, float c, float d);

	void StartDrumRoll(int32_t newScore); // �h�������[�����J�n����V�����֐���ǉ�

	void Reset();

private:

	//�񎟌��p�̍��W
	Vec2 pos_[kScoreDigitNum_];
	int popPos_ = 0;
	int popVec_ = 0;

	//�\������X�R�A�摜�p�̕ϐ�(�\������)
	int displayNum_[kScoreDigitNum_];
	//�����̉摜�p�n���h��
	static int textureHandle_[kScoreNumberNum_];

	//��{���_
	const int scoreNum = 100;
	//���Z����X�R�A
	int score_ = 0;

	//�h�������[������X�R�A
	int drumRollscore_ = 0;
	//�ڕW�X�R�A
	int targetScore_ = 0;
	//���U���g�ő����Ă����Ƃ��̃^�C�}�[
	float drumTimer_ = 0;
	//�h�������[�����鎞��
	const float kMaxDrumTime_ = 90;

	//�h�������[�����Ă��邩�̃t���O
	bool isDrumRoll_ = false;

	//�h�������[���̖ڕW�X�R�A
	int drumRollscoreTarget_ = 0;
};