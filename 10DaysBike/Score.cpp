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
	LoadDivGraph((RESOUCE_PATH + "number.png").c_str(), 10, 10, 1, 32, 32, textureHandle_);
}

void Score::Init(Vec2 pos)
{
	//���_������
	score_ = 1023459;
	isDrumRoll_ = false;

	//�ǂꂮ�炢�̓��Ԋu�ŗ�����
	const float equalDistanceX = 32.0f;
	const float equalDistanceY = 0.0f;

	for (int i = 0; i < kScoreDigitNum_; i++)
	{
		// ���W�̏�����
		pos_[i] = Vec2((i * equalDistanceX), 10.0f);
	}
}

void Score::Update()
{
	//�G�����񂾍ۂɓG�̎�ނɂ���ă|�C���g��ς���

	if (KeyboardInput::GetInstance().GetTriggerKey(KEY_INPUT_T)) {
		//�Q�[���V�[���Ɉړ�
		isDrumRoll_ = true;
	}

	if (isDrumRoll_ == true)
	{
		InputDrumRoll();
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
	if (drumTimer_ < kMaxDrumTime_) 
	{
		drumTimer_++;
	}
	else
	{
		isDrumRoll_ = false;
	}

	drumRollscore_ = EaseInOutExpo(drumTimer_, 0.0f, static_cast<float>(score_), kMaxDrumTime_);

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
