#include "Player.h"
#include "PlayerState.h"
#include "CollisionAttribute.h"
#include "EnergyGauge.h"
#include "Inform.h"
const float Player::AUTO_MOVING_SPEED = 3.0f;
const float Player::SIDE_MOVING_SPEED = 9.37f;
const float  Player::DOWN_IMAGE_ANGLE = 3.1415f;
const float Player::IMAGE_EXTEND = PROT_PLAYER_DRAWING_SIZE * 2.0f / (float)IMAGE_SIZE;
const ColorDxLib Player::PROT_PLAYER_COLOR = { 255,255,255 };
const ColorDxLib Player::DAMAGED_PLAYER_COLOR = { 255,0,0 };

const std::string Player::NORMAL_IMAGE_NAME = "BikeRun.png";
const std::string Player::CURVE_IMAGE_NAME = "BikeCurve.png";
const std::string Player::UP_BURST_SOUND_NAME = "upBurst.wav";
const std::string Player::DOWN_BURST_SOUND_NAME = "downBurst.wav";

const float Player::DAMAGE_DECRE_RATIO = 0.25f;

Player::~Player()
{
	RemoveCollider();

	DeleteSoundMem(upBurstSound_);
	DeleteSoundMem(downBurstSound_);

	for (int i = 0; i < NORMAL_IMAGE_NUM;i++)
	{
		DeleteGraph(normalImageHandles_[i]);
	}
	for (int i = 0; i < CURVE_IMAGE_NUM; i++)
	{
		DeleteGraph(curveImageHandles_[i]);
	}
}

void Player::Init()
{
	Init({ 0,0 });
}

void Player::Init(const Vec2& pos)
{
	name_ = "player";

	pos_ = pos;

	//画像
	LoadDivGraph((RESOUCE_PATH + NORMAL_IMAGE_NAME).c_str(), NORMAL_IMAGE_NUM, NORMAL_IMAGE_NUM,
		1, IMAGE_SIZE, IMAGE_SIZE, normalImageHandles_);
	LoadDivGraph((RESOUCE_PATH + CURVE_IMAGE_NAME).c_str(), CURVE_IMAGE_NUM, CURVE_IMAGE_NUM,
		1, IMAGE_SIZE, IMAGE_SIZE, curveImageHandles_);

	//音
	upBurstSound_ = LoadSoundMem((RESOUCE_PATH + UP_BURST_SOUND_NAME).c_str());
	downBurstSound_ = LoadSoundMem((RESOUCE_PATH + DOWN_BURST_SOUND_NAME).c_str());

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

	coliderPos_ = pos_;

	//シェイク
	damagedShake_ = std::make_unique<Shake>();

	//ステート
	ChangeState(std::make_unique<PlayerStateDown>());
}

void Player::Update()
{
	Update(nullptr, nullptr, 0);
}

void Player::Update(std::function<bool(float decreGauge, int32_t continueNum)> shootGaugeFunc,
	std::function<bool(float trajPos, float chargeGaugeRatio)> chargeGaugeFunc,
	float rimitY)
{
	//ステート更新
	state_->Update(
		[=](float thickRate, float costRate, int32_t continueNum, const std::string& trajName)
		{
			TrajectoriesManager::TrajGenerateInform info =
			{ -vec_.y * moveSpeedRate_, thickRate, costRate, continueNum, trajName };

			return trajManag_->Update(info, shootGaugeFunc, chargeGaugeFunc);
		}
	);

	//画面内に収める
	FitTheScreen(PROT_PLAYER_DRAWING_SIZE);
	//ゲージも含めた画面内に収める
	pos_.y = min(pos_.y, rimitY - PROT_PLAYER_DRAWING_SIZE);

	//--------------------------
	//雑に
	damagedShake_->Update();

	coliderPos_ = GetDrawPos();
}

void Player::Draw()
{
	if (damagedShake_->GetIsShaking())
	{
		color_ = DAMAGED_PLAYER_COLOR;
	}

	trajManag_->Draw();

	state_->Draw();
}

void Player::DrawImage(const std::string& imageName, float angle, bool imageSideTurn)
{
	const int* handles = nullptr;
	if (imageName == NORMAL_IMAGE_NAME)
	{
		handles = normalImageHandles_;
	}
	else if (imageName == CURVE_IMAGE_NAME)
	{
		handles = curveImageHandles_;
	}

	if (handles)
	{
		DrawRotaGraph(GetDrawPos().x, GetDrawPos().y, IMAGE_EXTEND, angle, handles[imageIndex_], true, imageSideTurn);
	}
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
	trajManag_->SetPos(GetDrawPos());
}

Vec2 Player::GetDrawPos()
{
	return pos_ + Vec2{ damagedShake_->GetShake(),damagedShake_->GetShake() };
}

void Player::IncrementImageIndex(const std::string& imageName)
{
	if (imageName == NORMAL_IMAGE_NAME)
	{
		imageIndex_++;
		if (imageIndex_ >= NORMAL_IMAGE_NUM)
		{
			imageIndex_ = 0;
		}
	}
	else if (imageName == CURVE_IMAGE_NAME)
	{
		imageIndex_ = min(imageIndex_ + 1, CURVE_IMAGE_NUM - 1);
	}
}

void Player::PlayUpBurstSound()
{
	ChangeVolumeSoundMem(255 * 80 / 100, upBurstSound_);
	PlaySoundMem(upBurstSound_, DX_PLAYTYPE_BACK);
}

void Player::StopUpBurstSound()
{
	ChangeVolumeSoundMem(255 * 80 / 100, upBurstSound_);
	StopSoundMem(upBurstSound_);
}

void Player::PlayDownBurstSound()
{
	ChangeVolumeSoundMem(255 * 60 / 100, downBurstSound_);
	PlaySoundMem(downBurstSound_, DX_PLAYTYPE_BACK);
}

void Player::OnCollision(const CollisionInfo& info)
{
	if (!damagedShake_->GetIsShaking())
	{
		//ダメージでゲージ減らす(ゲージがなくなったらしぼう)
		isAlive_ = damageFunc_(DAMAGE_DECRE_RATIO);
		//雑に
		damagedShake_->BeginShake(DAMAGED_TIME, DAMAGED_SHAKE_MAX);
	}
}
