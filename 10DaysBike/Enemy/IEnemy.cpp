#include "IEnemy.h"
#include "CollisionAttribute.h"
#include "Inform.h" 
#include "TrajectoriesManager.h"

const float IEnemy::AUTO_MOVING_SPEED = 3.0f;
const float IEnemy::SIDE_MOVING_SPEED = 3.0f;
const ColorDxLib IEnemy::PROT_ENEMY_COLOR = { 255,128,128 };
int IEnemy::explosionSoundHandle_;
int IEnemy::deadSoundHandle_;

IEnemy::~IEnemy()
{

}

void IEnemy::LoadSound()
{
	explosionSoundHandle_ = LoadSoundMem((RESOUCE_PATH + "enemyDamege.wav").c_str());
	deadSoundHandle_ = LoadSoundMem((RESOUCE_PATH + "enemyDead.wav").c_str());
}

void IEnemy::Init(){}

void IEnemy::Init(const Vec2& pos, std::string name)
{
	name_ = name;

	pos_ = pos;

	color_ = PROT_ENEMY_COLOR;

	radius_ = PROT_ENEMY_DRAWING_SIZE;
}

void IEnemy::Update()
{
	//攻撃を受けた判定をなくす(当たっていればOnCollision関数で再度trueになる)
	if (isHit_ == true)
	{
		isHit_ = false;
		color_ = { 255,128,128 };
	}

	//HPが0になったら死亡状態にし、コライダーを消すフラグをオンにする
	if (hp_ <= 0)
	{
		isDead_ = true;
		isDeleteCollider_ = true;
	}
	
	//現在位置をコライダー用の変数に渡す
	coliderPos_ = pos_;
	drawPos_ = pos_;
}

void IEnemy::Draw()
{	
}

void IEnemy::AddCollider()
{
	//コライダーの追加
	const float radius = static_cast<float>(PROT_ENEMY_DRAWING_SIZE);
	enemyCollider_ = std::make_unique<CircleCollider>(pos_, radius);

	//コライダーの登録
	SetCollider(enemyCollider_.get());

	//属性を指定
	enemyCollider_->SetAttribute(COLLISION_ATTR_ENEMYS);
}

void IEnemy::OnCollision(const CollisionInfo& info)
{
	if (isHit_ == false)
	{
		isHit_ = true;

		std::string objName = info.object->GetName();
		if (objName == TrajectoriesManager::UP_TRAJ_NAME)
		{
			hp_ -= 1;
		}
		else if (objName == TrajectoriesManager::BURST_DOWN_NAME)
		{
			hp_ = 0;
		}
		else if (objName == TrajectoriesManager::DOWN_TRAJ_NAME)
		{
			hp_ -= 1;
		}
		else if (objName == TrajectoriesManager::BURST_UP_NAME)
		{
			hp_ -= 2;
		}


		color_ = { 255,0,0 };

		//ダメージ時にゲージ回復させる
		chargeFunc_(DAMAGED_CHARGE_GAUGE_RATIO);
		//ダメージ演出
		damagedEffectFunc_(pos_, radius_);
	}

	if (hp_ <= 0)
	{
		//音が鳴っていなかったら再生する
		if (CheckSoundMem(deadSoundHandle_) == 0)
		{
			PlaySoundMem(deadSoundHandle_, DX_PLAYTYPE_BACK);
		}
	}
	else {
		//音が鳴っていなかったら再生する
		if (CheckSoundMem(explosionSoundHandle_) == 0)
		{
			PlaySoundMem(explosionSoundHandle_, DX_PLAYTYPE_BACK);
		}
	}
}
