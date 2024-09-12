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

	// �S�Ă̑g�ݍ��킹�ɂ��đ�������`�F�b�N
	itA = colliders.begin();
	for (; itA != colliders.end(); ++itA)
	{
		BaseCollider* colA = *itA;

		// �v���C���[������͈͓����ǂ������`�F�b�N
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

			// �����̃R���C�_�[���~�ł��邩�`�F�b�N
			if (colA->GetShapeType() == COLLISIONSHAPE_CIRCLE && colB->GetShapeType() == COLLISIONSHAPE_CIRCLE)
			{
				// �قȂ鑮���̃I�u�W�F�N�g���m���������蔻��
				if (colA->GetAttribute() != colB->GetAttribute())
				{
					Circle CircleA;
					Circle CircleB;

					CircleA.pos = colA->objcet2d_->GetColliderPos();
					CircleA.radius = colA->objcet2d_->GetRadius();

					CircleB.pos = colB->objcet2d_->GetColliderPos();
					CircleB.radius = colB->objcet2d_->GetRadius();

					Vec2 inter;

					// �~���m�̏Փ˔���
					if (Collision::CheckCircle2Circle(CircleA, CircleB))
					{
						colA->OnCollison(CollisionInfo(colB->GetObject2d(), colB, inter));
						colB->OnCollison(CollisionInfo(colA->GetObject2d(), colA, inter));
					}
				}
			}
		}
	}

	auto it = colliders.before_begin();  // �擪�̗v�f�̑O���w������ȃC�e���[�^�[
	auto next = colliders.begin();       // ���̗v�f���w���C�e���[�^�[

	while (next != colliders.end()) {
		BaseCollider* collider = *next;

		// �폜�����̔���
		if (collider->objcet2d_->GetIsDeleteCollider() == true) {
				// �R���W�����}�l�[�W���[����o�^����
				//RemoveCollider(collider);

				// �C�e���[�^�[�𐳂����X�V���ėv�f���폜
				next = colliders.erase_after(it);
				continue;  // erase_after ��ɃC�e���[�^�[���X�V���Ď��̃��[�v��
		}

		// ���̗v�f�Ɉړ�
		it = next;
		++next;
	}
}

void CollisionManager::FinalizeCollisions()
{
	// �폜�\��̃R���C�_�[���ꊇ�폜
	for (auto collider : collidersToRemove)
	{
		colliders.remove(collider);
	}
	collidersToRemove.clear();  // �폜���X�g���N���A
}


// 2�_�Ԃ̋����̓����v�Z
float CollisionManager::DistanceSquared(const Vec2& a, const Vec2& b)
{
	float dx = a.x - b.x;
	float dy = a.y - b.y;
	return dx * dx + dy * dy;
}