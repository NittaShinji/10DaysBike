#pragma once
#include "CollisionPrimitive.h"
#include "BaseCollider.h"
#include <forward_list>

class CollisionManager
{
public: //�ÓI�����o�֐�

	static CollisionManager* GetInstance();

	//�f�t�H���g�R���X�g���N�^
	CollisionManager() = default;
	//�f�t�H���g�f�X�g���N�^
	~CollisionManager() = default;
	//�R�s�[�R���X�g���N�^�̖���
	CollisionManager(const CollisionManager&) = delete;
	//������Z�q�̖���
	CollisionManager& operator = (const CollisionManager&) = delete;

public: //�����o�֐�

	/// <summary>
	/// �R���C�_�[�̒ǉ�
	/// </summary>
	/// <param name="collider">�R���C�_�[</param>
	inline void AddCollider(BaseCollider* collider)
	{
		colliders.push_front(collider);
	}

	/// <summary>
	/// �R���C�_�[�̍폜
	/// </summary>
	/// <param name="collider">�R���C�_�[</param>
	inline void RemoveCollider(BaseCollider* collider)
	{
		colliders.remove(collider);
	}

	/// <summary>
	/// �S�Ă̏Փ˂��`�F�b�N
	/// </summary>
	void CheckAllCollisions();

private:

	//�R���C�_�[�̃��X�g
	std::forward_list<BaseCollider*> colliders;
};

