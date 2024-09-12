#include "Collision.h"
#include "CollisionManager.h"
#include "EnemyBullet.h"

CollisionManager* CollisionManager::GetInstance()
{
	static CollisionManager instance;
	return &instance;
}

void CollisionManager::CheckAllCollisions(const Vec2& playerPos, float range)
{
	std::forward_list<BaseCollider*>::iterator itA;
	std::forward_list<BaseCollider*>::iterator itB;

	// 全ての組み合わせについて総当たりチェック
	itA = colliders.begin();
	for (; itA != colliders.end(); ++itA)
	{
		BaseCollider* colA = *itA;

		// プレイヤーから一定範囲内かどうかをチェック
		if (colA->objcet2d_->GetName() == "enemyBullet")
		{
			if (DistanceSquared(playerPos, colA->objcet2d_->GetColliderPos()) > range * range)
			{
				continue;
			}
		}
		else if (colA->objcet2d_->GetName() == "enemy")
		{
			if (DistanceSquared(playerPos, colA->objcet2d_->GetColliderPos()) > range * range)
			{
				continue;
			}
		}
		else
		{

		}
		
		itB = itA;
		++itB;
		for (; itB != colliders.end(); ++itB)
		{
			BaseCollider* colB = *itB;

			// 両方のコライダーが円であるかチェック
			if (colA->GetShapeType() == COLLISIONSHAPE_CIRCLE && colB->GetShapeType() == COLLISIONSHAPE_CIRCLE)
			{
				// 異なる属性のオブジェクト同士だけ当たり判定
				if (colA->GetAttribute() != colB->GetAttribute())
				{
					Circle CircleA;
					Circle CircleB;

					CircleA.pos = colA->objcet2d_->GetColliderPos();
					CircleA.radius = colA->objcet2d_->GetRadius();

					CircleB.pos = colB->objcet2d_->GetColliderPos();
					CircleB.radius = colB->objcet2d_->GetRadius();

					Vec2 inter;

					// 円同士の衝突判定
					if (Collision::CheckCircle2Circle(CircleA, CircleB))
					{
						colA->OnCollison(CollisionInfo(colB->GetObject2d(), colB, inter));
						colB->OnCollison(CollisionInfo(colA->GetObject2d(), colA, inter));
					}
				}
			}
		}
	}

	auto it = colliders.before_begin();  // 先頭の要素の前を指す特殊なイテレーター
	auto next = colliders.begin();       // 次の要素を指すイテレーター

	while (next != colliders.end()) {
		BaseCollider* collider = *next;

		// 削除条件の判定
		if (collider->objcet2d_->GetIsDeleteCollider() == true) {
				// コリジョンマネージャーから登録解除
				//RemoveCollider(collider);

				// イテレーターを正しく更新して要素を削除
				next = colliders.erase_after(it);
				continue;  // erase_after 後にイテレーターを更新して次のループへ
		}

		// 次の要素に移動
		it = next;
		++next;
	}
}

void CollisionManager::FinalizeCollisions()
{
	// 削除予定のコライダーを一括削除
	for (auto collider : collidersToRemove)
	{
		colliders.remove(collider);
	}
	collidersToRemove.clear();  // 削除リストをクリア
}


// 2点間の距離の二乗を計算
float CollisionManager::DistanceSquared(const Vec2& a, const Vec2& b)
{
	float dx = a.x - b.x;
	float dy = a.y - b.y;
	return dx * dx + dy * dy;
}