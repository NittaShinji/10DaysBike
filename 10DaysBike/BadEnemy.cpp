#include "BadEnemy.h"
#include "BulletManager.h"
#include "CollisionAttribute.h"

BadEnemy::~BadEnemy()
{
	DeleteGraph(graphHandle_);
}

void BadEnemy::Init(const Vec2& pos)
{
	//èâä˙âª
	IEnemy::Init(pos,"BadEnemy");
	
	//âÊëúì«Ç›çûÇ›
	graphHandle_ = LoadGraph((RESOUCE_PATH + "batEnemy.png").c_str());

	IEnemy::AddCollider();
}

void BadEnemy::Update()
{
	IEnemy::Update();
}

void BadEnemy::Draw()
{
	IEnemy::Draw();
	const int* handles = nullptr;
	DrawGraph(pos_.x - radius_, pos_.y - radius_, graphHandle_, FALSE);
}

//----------------------------------------------------------------------

void BadEnemy::OnCollision(const CollisionInfo& info)
{
	IEnemy::OnCollision(info);
}
