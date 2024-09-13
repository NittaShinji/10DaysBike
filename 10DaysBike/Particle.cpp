#include "Particle.h"

void Particle::Init()
{
}

void Particle::Init(const ParticleInform& info)
{
	info_.accel = info.accel;
	info_.maxSpeed = info.maxSpeed;
	radius_ = info.radius;

	info_.blendMode = info.blendMode;
	info_.blendParam = info.blendParam;

	info_.timer = info.timer;

	info_.type = info.type;
}

void Particle::Update()
{
	info_.timer--;

	vec_ += info_.accel;
	float length = vec_.GetLength();
	vec_ = min(length, info_.maxSpeed) * vec_.GetNormalize();


	pos_ += vec_;


	if (GetIsOffingGameScreen() || info_.timer < 1)
	{
		isAlive_ = false;
	}
}

void Particle::Draw()
{
	SetDrawBlendMode(info_.blendMode, info_.blendParam);

	//�`��
	if (info_.type == ShapeType::CIRCLE)
	{
		DrawCircle((int)pos_.x, (int)pos_.y, (int)radius_, GetColorUsedForDrawing());
	}
	else if (info_.type == ShapeType::SQUARE)
	{
		DrawBox((int)pos_.x - radius_, (int)pos_.y - radius_, (int)pos_.x + radius_, (int)pos_.y + radius_,
			GetColorUsedForDrawing(), true);
	}
	else if (info_.type == ShapeType::TRIANGLE)
	{
		DrawTriangle((int)pos_.x, (int)pos_.y - radius_, (int)pos_.x + radius_, (int)pos_.y + radius_,
			(int)pos_.x - radius_, (int)pos_.y + radius_,
			GetColorUsedForDrawing(), true);
	}

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
