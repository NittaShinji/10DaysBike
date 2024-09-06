#pragma once

class vec2;
class IObject2D;
class BaseCollider;

/// <summary>
/// �Փˏ��
/// </summary>
struct CollisionInfo
{
public:
	CollisionInfo(IObject2D* object, BaseCollider* collider, const Vec2& inter)
	{
		this->object = object;
		this->collider = collider;
		this->inter = inter;
	}

	//�Փˑ���̃I�u�W�F�N�g
	IObject2D* object = nullptr;
	//�Փˑ���̃R���C�_�[
	BaseCollider* collider = nullptr;
	//�Փ˓_
	Vec2 inter;
};
