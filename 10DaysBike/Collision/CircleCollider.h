#pragma once
#include "BaseCollider.h"
#include "CollisionPrimitive.h"

/// <summary>
/// 円の衝突判定用クラス
/// </summary>
class CircleCollider : public BaseCollider, public Circle
{
public:

	static const float kDefaultRadius_;
	static const Vec2 kDefaultOffset_;

public:

	//コンストラクタ
	CircleCollider(Vec2 offset = kDefaultOffset_, float radius = kDefaultRadius_) :

		offset_(offset),
		radius(radius)
	{
		//球形状をセット
		shapeType_ = COLLISIONSHAPE_CIRCLE;
	}

	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;

private:

	//オブジェクト中心からのオフセット
	Vec2 offset_;
	//半径
	float radius;

public:

	inline void SetRadius(float radius) { radius = radius; }
	inline void SetOffset(const Vec2& offset) { this->offset_ = offset; }
	inline const Vec2& GetOffset() { return offset_; }
	inline float GetRadius() { return radius; }

};
