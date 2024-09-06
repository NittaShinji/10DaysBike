#include "Collision.h"
#include "CollisionManager.h"

CollisionManager* CollisionManager::GetInstance()
{
	static CollisionManager instance;
	return &instance;
}

void CollisionManager::CheckAllCollisions()
{
	std::forward_list<BaseCollider*>::iterator itA;
	std::forward_list<BaseCollider*>::iterator itB;

	//全ての組み合わせについて総当たりチェック
	itA = colliders.begin();
	for (; itA != colliders.end(); ++itA)
	{
		itB = itA;
		++itB;
		for (; itB != colliders.end(); ++itB)
		{
			BaseCollider* colA = *itA;
			BaseCollider* colB = *itB;

			if (colA->GetShapeType() == COLLISIONSHAPE_CIRCLE && colB->GetShapeType() == COLLISIONSHAPE_CIRCLE)
			{
				if (colA->GetAttribute() != colB->GetAttribute())
				{
					Circle CircleA;
					Circle CircleB;

					CircleA.pos = colA->objcet2d_->GetPos();
					CircleA.radius = colA->objcet2d_->GetRadius();

					CircleB.pos = colB->objcet2d_->GetPos();
					CircleB.radius = colB->objcet2d_->GetRadius();

					Vec2 inter;

					if (Collision::CheckCircle2Circle(CircleA, CircleB))
					{
						colA->OnCollison(CollisionInfo(colB->GetObject2d(), colB, inter));
						colB->OnCollison(CollisionInfo(colA->GetObject2d(), colA, inter));
					}
				}
			}
		}
	}
}