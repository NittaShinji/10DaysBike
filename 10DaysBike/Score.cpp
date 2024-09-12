#include "Score.h"
#include "Easing.h"
#include "DxLib.h"
#include "Inform.h"
#include "KeyboardInput.h"
#include <cassert>

int Score::textureHandle_[kScoreNumberNum_];

Score::~Score()
{
	// �ǂݍ��񂾉摜�̃O���t�B�b�N�n���h�����폜
	for (int i = 0; i < kScoreNumberNum_; i++)
	{
		DeleteGraph(textureHandle_[i]);
	}
}

void Score::Load()
{
	//�e�N�X�`���ǂݍ���
	LoadDivGraph((RESOUCE_PATH + "bitmap_num.png").c_str(), 10, 10, 1, 32, 32, textureHandle_);
}

void Score::Init(Vec2 pos)
{
	//���_������
	score_ = 0;
	isDrumRoll_ = false;

	//�ǂꂮ�炢�̓��Ԋu�ŗ�����
	const float equalDistanceX = 32.0f;
	const float equalDistanceY = 0.0f;

	for (int i = 0; i < kScoreDigitNum_; i++)
	{
		// ���W�̏�����
		pos_[i] = Vec2((i * equalDistanceX) + 16.0f, 10.0f);
	}
}

void Score::Update()
{
	if (isDrumRoll_)
    {
        InputDrumRoll();

        // �h�������[���X�R�A���ڕW�X�R�A�ɒB������I��
        if (drumRollscore_ >= targetScore_) {
            isDrumRoll_ = false;
            drumRollscore_ = targetScore_;  // �ŏI�I�ȃX�R�A�ɍ��킹��
        }
    }
    else
    {
        InputNumberTS();  // �ʏ�̃X�R�A�\��
    }
}

void Score::Draw()
{
	//0�`9�܂ł��ꂼ��`��
	for (int i = 0; i < kScoreDigitNum_; i++)
	{
		DrawGraph(pos_[i].x + UI_SIZE.x, pos_[i].y, textureHandle_[displayNum_[i]], true);
	}
}

void Score::InputNumberTS()
{
	//--7����(10���̈ʂ�\��)
	displayNum_[0] = (score_ % 10000000) / 1000000;
	//--6����(���̈ʂ�\��)
	displayNum_[1] = (score_ % 1000000) / 100000;
	//--5����(��̈ʂ�\��)
	displayNum_[2] = (score_ % 100000) / 10000;
	//--4����(�S�̈ʂ�\��)
	displayNum_[3] = (score_ % 10000) / 1000;
	//--3����(�\�̈ʂ�\��)
	displayNum_[4] = (score_ % 1000) / 100;
	//--2����(1�̈ʂ�\��)
	displayNum_[5] = (score_ % 100) / 10;
	//--1����(1�̈ʂ�\��)
	displayNum_[6] = (score_ % 10) / 1;
}

void Score::InputDrumRoll()
{
	//t �o�ߎ���	b�ŏ��̈ʒu	c�ړ���	d�ړ�����
	if (isDrumRoll_)
	{
		if (drumTimer_ < kMaxDrumTime_)
		{
			drumTimer_++;
		}

		// �h�������[���̕\���X�R�A���X�V�i�X�R�A�̕ϓ��ɑΉ��j
		drumRollscore_ = EaseOutSine(drumTimer_, drumRollscore_, static_cast<float>(targetScore_ - drumRollscore_), kMaxDrumTime_);
	}

	//drumRollscore_ = EaseInOutExpo(drumTimer_, 0.0f, static_cast<float>(score_), kMaxDrumTime_);
	//drumRollscore_ = EaseOutSine(drumTimer_, 0.0f, static_cast<float>(score_), kMaxDrumTime_);


	//--7����(10���̈ʂ�\��)
	displayNum_[0] = (drumRollscore_ % 10000000) / 1000000;
	//--6����(���̈ʂ�\��)
	displayNum_[1] = (drumRollscore_ % 1000000) / 100000;
	//--5����(��̈ʂ�\��)
	displayNum_[2] = (drumRollscore_ % 100000) / 10000;
	//--4����(�S�̈ʂ�\��)
	displayNum_[3] = (drumRollscore_ % 10000) / 1000;
	//--3����(�\�̈ʂ�\��)
	displayNum_[4] = (drumRollscore_ % 1000) / 100;
	//--2����(1�̈ʂ�\��)
	displayNum_[5] = (drumRollscore_ % 100) / 10;
	//--1����(1�̈ʂ�\��)
	displayNum_[6] = (drumRollscore_ % 10) / 1;
}

float Score::EaseInOutExpo(float t, float b, float c, float d) {
	if (t == 0) return b;
	if (t == d) return b + c;
	if ((t /= d / 2) < 1) return c / 2 * pow(2, 10 * (t - 1)) + b;
	return c / 2 * (-pow(2, -10 * --t) + 2) + b;
}

float Score::EaseOutSine(float t, float b, float c, float d)
{
	float x = t / d;
	return c * sin((x * 3.1415) / 2) + b;
}

void Score::StartDrumRoll(int32_t newScore)
{
	if (isDrumRoll_)
	{
		// �����̃h�������[���̖ڕW�X�R�A���X�V
		targetScore_ = newScore;
	}
	else
	{
		// �h�������[�����J�n
		score_ += newScore; // �����̃X�R�A�ɒǉ�
		targetScore_ = score_; // �V�����ڕW�X�R�A�ɐݒ�
		drumTimer_ = 0.0f; // �^�C�}�[�����Z�b�g
		isDrumRoll_ = true; // �h�������[����L���ɂ���
	}
}
