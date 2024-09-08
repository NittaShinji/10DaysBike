#include "Trajectory.h"
#include "CollisionAttribute.h"
#include "Easing.h"
#include "Util.h"

const ColorDxLib Trajectory::PROT_TRAJ_COLOR = { 255,255,0 };
const float Trajectory::SHOOT_DECREMENT_GAUGE = 1.0f / 600.0f;
const float Trajectory::CHARGE_GAUGE_RATIO = SHOOT_DECREMENT_GAUGE * 2.4f;


Trajectory::Trajectory() {}
Trajectory::~Trajectory() { RemoveCollider(); }

void Trajectory::Init()
{
	const TwoPoses POSES = { {0,0},{0,0} };
	const Vec2 VEC = { 0,0 };

	Init(POSES, VEC);
}

void Trajectory::Init(const TwoPoses& twoPoses, const Vec2& vec, bool isHead)
{
	color_ = PROT_TRAJ_COLOR;

	//コライダーの追加
	SetRadius(32.5f);
	trajectoryCollider_ = std::make_unique<CircleCollider>(twoPoses.sPos, radius_);
	SetCollider(trajectoryCollider_.get());

	//属性を指定
	trajectoryCollider_->SetAttribute(COLLISION_ATTR_ALLIES);

	twoPoses_ = twoPoses;
	vec_ = vec;
	isHead_ = isHead;
}

void Trajectory::Update()
{
	Update(nullptr);
}

void Trajectory::Update(std::function<bool(float, float)> chargeGaugeFunc)
{
	pos_ += vec_;

	twoPoses_.sPos += vec_ + scrollVec_;
	twoPoses_.ePos += vec_ + scrollVec_;

	collider_->Update();

	lifeFrame_--;

	//ゲージをチャージするため
	if (chargeGaugeFunc(twoPoses_.sPos.y, CHARGE_GAUGE_RATIO))
	{
		isAlive_ = false;
	}

	if (GetIsOffingScreen(twoPoses_.sPos, twoPoses_.ePos)
		|| lifeFrame_ < 1)
	{
		//画面外に出たら消してもらうため
		isAlive_ = false;
	}

	coliderPos_ = twoPoses_.sPos;
}

void Trajectory::Draw()
{
	const Vec2 S_POS = twoPoses_.sPos;
	const Vec2 E_POS = twoPoses_.ePos;

	const float T = (lifeFrame_ / (float)LIFE_FRAME);

	const float TICKNESS = (float)LINE_TICKNESS * EaseIn(T);
	const float LENGTH = SHAKING_LENGTH * EaseOut(T);
	const float SHAKE_TICKNESS = GetRand(TICKNESS - LENGTH, TICKNESS + LENGTH);

	//線描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, ALPHA_MAX * EaseIn(T));
	DrawLineAA(S_POS.x, S_POS.y, E_POS.x, E_POS.y, GetColorUsedForDrawing(), (int)(SHAKE_TICKNESS));
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
