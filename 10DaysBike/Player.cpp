#include "Player.h"
#include "PlayerState.h"
#include "CollisionAttribute.h"
#include "EnergyGauge.h"
const float Player::AUTO_MOVING_SPEED = 3.0f;
const float Player::SIDE_MOVING_SPEED = 9.37f;
const ColorDxLib Player::PROT_PLAYER_COLOR = { 255,255,255 };


void Player::MoveUpdate()
{

}

void Player::Init()
{
	Init({ 0,0 });
}

void Player::Init(const Vec2& pos)
{
	name_ = "player";

	pos_ = pos;

	color_ = PROT_PLAYER_COLOR;

	radius_ = PROT_PLAYER_DRAWING_SIZE;

	//軌跡管理クラス
	trajManag_.reset();
	trajManag_ = std::make_unique<TrajectoriesManager>();
	trajManag_->Init(pos_);

	//コライダーの追加
	const float radius = static_cast<float>(PROT_PLAYER_DRAWING_SIZE);
	playerCollider_ = std::make_unique<CircleCollider>(pos_, radius);

	//コライダーの登録
	SetCollider(playerCollider_.get());

	//属性を指定
	playerCollider_->SetAttribute(COLLISION_ATTR_ALLIES);

	//ステート
	ChangeState(std::make_unique<PlayerStateDown>());
}

void Player::Update()
{
	Update(nullptr, nullptr, 0);
}

void Player::Update(std::function<bool(float)> shootGaugeFunc,
	std::function<bool(float trajPos, float chargeGaugeRatio)> chargeGaugeFunc,
	float rimitY)
{
	//ステート更新
	state_->Update(
		[=](float thickRate, float costRate)
		{
			trajManag_->Update({ -vec_.y * moveSpeedRate_, thickRate, costRate }, shootGaugeFunc, chargeGaugeFunc);
		}
	);

	//画面内に収める
	FitTheScreen(PROT_PLAYER_DRAWING_SIZE);
	//ゲージも含めた画面内に収める
	pos_.y = min(pos_.y, rimitY - PROT_PLAYER_DRAWING_SIZE);

	//--------------------------
	if (isHit_ == true)
	{
		isHit_ = false;
		color_ = { 255,255,255 };
	}

	coliderPos_ = pos_;
}

void Player::Draw()
{
	trajManag_->Draw();

	state_->Draw();
}


//----------------------------------------------------------------------
void Player::ChangeState(std::unique_ptr<IPlayerState> state)
{
	state_.reset();
	state_ = std::move(state);
	state_->SetPlayerPtr(this);
	state_->Init();
}

void Player::ProccesingNewTrajs()
{
	trajManag_->ProccesingNewTrajs();
}

void Player::TrajManagerPosUpdate()
{
	trajManag_->SetPos(pos_);
}

void Player::OnCollision(const CollisionInfo& info)
{
	if (isHit_ == false)
	{
		isHit_ = true;
		color_ = { 0,0,255 };
	}
}
