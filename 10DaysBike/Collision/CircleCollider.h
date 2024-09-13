#pragma once
#include "BaseCollider.h"
#include "CollisionPrimitive.h"

/// <summary>
/// �~�̏Փ˔���p�N���X
/// </summary>
class CircleCollider : public BaseCollider, public Circle
{
public:

	static const float kDefaultRadius_;
	static const Vec2 kDefaultOffset_;

public:

	//�R���X�g���N�^
	CircleCollider(Vec2 offset = kDefaultOffset_, float radius = kDefaultRadius_) :

		offset_(offset),
		radius(radius)
	{
		//���`����Z�b�g
		shapeType_ = COLLISIONSHAPE_CIRCLE;
	}

	/// <summary>
	/// �X�V
	/// </summary>
	void Update() override;

private:

	//�I�u�W�F�N�g���S����̃I�t�Z�b�g
	Vec2 offset_;
	//���a
	float radius;

public:

	inline void SetRadius(float radius) { radius = radius; }
	inline void SetOffset(const Vec2& offset) { this->offset_ = offset; }
	inline const Vec2& GetOffset() { return offset_; }
	inline float GetRadius() { return radius; }

};
