#include "IObject2D.h"
#include "CollisionManager.h"
#include "BaseCollider.h"
#include <algorithm>

void IObject2D::OnCollision(const CollisionInfo& info)
{
	static_cast<void>(info);
}

void IObject2D::RemoveCollider()
{
	if (collider_)
	{
		//コリジョンマネージャーから登録を解除する
		CollisionManager::GetInstance()->RemoveCollider(collider_);
	}
}

void IObject2D::Move()
{
	pos_ += vec_;
}

void IObject2D::SetCollider(BaseCollider* collider)
{
	collider->SetObject(this);
	collider_ = collider;
	//コリジョンマネージャーに登録
	CollisionManager::GetInstance()->AddCollider(collider);
	//コライダーを更新しておく
	collider->Update();
}

bool IObject2D::GetIsOffingGameScreen()
{
	return GetIsOffingGameScreen(pos_);
}

bool IObject2D::GetIsOffingGameScreen(const Vec2& pos)
{
	bool isOffingX = (pos.x > WINDOW_SIZE.x) || (UI_SIZE.x < 0);
	bool isOffingY = (pos.y > WINDOW_SIZE.y) || (pos.y < 0);

	return (isOffingX || isOffingY);
}

bool IObject2D::GetIsOffingGameScreen(const Vec2& pos, const Vec2& pos2)
{
	return (GetIsOffingGameScreen(pos) && GetIsOffingGameScreen(pos2));
}

bool IObject2D::GetIsOffingGameScreen(const Vec2& pos, const Vec2& pos2, const Vec2& pos3)
{
	return (GetIsOffingGameScreen(pos) && GetIsOffingGameScreen(pos2) && GetIsOffingGameScreen(pos3));
}

void IObject2D::FitTheScreen(float radius)
{
	pos_.x = min(max(pos_.x, UI_SIZE.x + radius), WINDOW_SIZE.x - radius);
	pos_.y = min(max(pos_.y, radius), WINDOW_SIZE.y - radius);
}
