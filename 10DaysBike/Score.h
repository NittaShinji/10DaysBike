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
	void Pop();
	void Draw();
	int GetScore() { return score_; }

	//���l���������ɓ���
	//�X�R�A����
	void InputNumberTS();
	void InputDrumRoll();

	float EaseInOutExpo(float t, float b, float c, float d);

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
	//���U���g�ő����Ă����Ƃ��̃^�C�}�[
	float drumTimer_ = 0;
	//�h�������[�����鎞��
	float kMaxDrumTime_ = 340;

	//�h�������[�����Ă��邩�̃t���O
	bool isDrumRoll_ = false;
};

