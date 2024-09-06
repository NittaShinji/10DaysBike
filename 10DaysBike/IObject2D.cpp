#include "IObject2D.h"
#include "CollisionManager.h"
#include "BaseCollider.h"

void IObject2D::OnCollision(const CollisionInfo& info)
{
	static_cast<void>(info);
}

void IObject2D::RemoveCollider()
{
	if (collider_)
	{
		//�R���W�����}�l�[�W���[����o�^����������
		CollisionManager::GetInstance()->RemoveCollider(collider_);
	}
}

void IObject2D::SetCollider(BaseCollider* collider)
{
	collider->SetObject(this);
	collider_ = collider;
	//�R���W�����}�l�[�W���[�ɓo�^
	CollisionManager::GetInstance()->AddCollider(collider);
	//�R���C�_�[���X�V���Ă���
	collider->Update();
}

bool IObject2D::GetIsOffingScreen()
{
	return GetIsOffingScreen(pos_);
}

bool IObject2D::GetIsOffingScreen(const Vec2& pos)
{
	bool isOffingX = (pos.x > WINDOW_SIZE.x) || (pos.x < 0);
	bool isOffingY = (pos.y > WINDOW_SIZE.y) || (pos.y < 0);

	return (isOffingX || isOffingY);
}

bool IObject2D::GetIsOffingScreen(const Vec2& pos, const Vec2& pos2)
{
	return (GetIsOffingScreen(pos) && GetIsOffingScreen(pos2));
}

bool IObject2D::GetIsOffingScreen(const Vec2& pos, const Vec2& pos2, const Vec2& pos3)
{
	return (GetIsOffingScreen(pos) && GetIsOffingScreen(pos2) && GetIsOffingScreen(pos3));
}
