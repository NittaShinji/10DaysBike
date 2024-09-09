#include "Player.h"
#include "PlayerState.h"
#include "CollisionAttribute.h"
#include "EnergyGauge.h"
const float Player::AUTO_MOVING_SPEED = 3.0f;
const float Player::SIDE_MOVING_SPEED = 7.37f;
const ColorDxLib Player::PROT_PLAYER_COLOR = { 255,255,255 };


void Player::MoveUpdate()
{

}

Player::~Player()
{
	RemoveCollider();
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

	//�O�ՊǗ��N���X
	trajManag_.reset();
	trajManag_ = std::make_unique<TrajectoriesManager>();
	trajManag_->Init(pos_);

	//�R���C�_�[�̒ǉ�
	const float radius = static_cast<float>(PROT_PLAYER_DRAWING_SIZE);
	playerCollider_ = std::make_unique<CircleCollider>(pos_, radius);

	//�R���C�_�[�̓o�^
	SetCollider(playerCollider_.get());

	//�������w��
	playerCollider_->SetAttribute(COLLISION_ATTR_ALLIES);

	//�X�e�[�g
	ChangeState(std::make_unique<PlayerStateDown>());
}

void Player::Update()
{
	Update(nullptr, nullptr, 0);
}

void Player::Update(std::function<bool(float)> shootGaugeFunc,
	std::function<bool(float, float)> chargeGaugeFunc,
	float rimitY)
{
	state_->Update();

	trajManag_->SetPos(pos_);
	trajManag_->Update(-vec_.y, shootGaugeFunc, chargeGaugeFunc);

	//��ʓ��Ɏ��߂�
	FitTheScreen(PROT_PLAYER_DRAWING_SIZE);
	//�Q�[�W���܂߂���ʓ��Ɏ��߂�
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

void Player::ProccesingTurning()
{
	trajManag_->ProccesingTurning();
}

void Player::OnCollision(const CollisionInfo& info)
{
	if (isHit_ == false)
	{
		isHit_ = true;
		color_ = { 0,0,255 };
	}
}
