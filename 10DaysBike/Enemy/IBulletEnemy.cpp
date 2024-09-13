#include "IBulletEnemy.h"
#include "BulletEnemyState.h"
#include "BulletManager.h"
#include "CollisionAttribute.h"

IBulletEnemy::~IBulletEnemy()
{
	bulletManager_ = nullptr;
}

void IBulletEnemy::ChangeState(std::unique_ptr<IBulletEnemyState> state)
{
	state_.reset();
	state_ = std::move(state);
	state_->SetEnemyPtr(this);
	state_->Init();
}

void IBulletEnemy::Init(const Vec2& pos, float bulletSpeed,std::string name)
{
	bulletSpeed_ = bulletSpeed;
	IEnemy::Init(pos,name);
	IEnemy::AddCollider();
}

void IBulletEnemy::Update()
{
	state_->Update();
	IEnemy::Update();
}

void IBulletEnemy::Draw()
{

	for (std::unique_ptr<EnemyBullet>& bullet : bullets_)
	{
		bullet->Draw();
	}

	ExplosionStaging_->Draw();
}

void IBulletEnemy::OnCollision(const CollisionInfo& info)
{
	IEnemy::OnCollision(info);
}

void IBulletEnemy::Fire(float bulletSpeed)
{
	//íeÇÃë¨ìx
	const float kBulletSpeed = -bulletSpeed;
	Vec2 velocity(0, kBulletSpeed);

	//íeÇê∂ê¨ÇµÅAèâä˙âª
	std::unique_ptr<EnemyBullet> newBullet = std::make_unique<EnemyBullet>();
	newBullet->Initialize(pos_, velocity);

	//íeÇíeÉ}ÉlÅ[ÉWÉÉÅ[Ç…ìoò^Ç∑ÇÈ
	bulletManager_->GetBullets().push_back(std::move(newBullet));
}
