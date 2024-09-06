#pragma once
#include "IObject2D.h"
#include "CollisionInfo.h"
#include "CollisionTypes.h"

class CollisionManager;

/// <summary>
/// 基礎コライダー
/// </summary>
class BaseCollider
{
public:
	//デフォルトコンストラクタ
	BaseCollider() = default;
	//仮想デストラクタ
	virtual ~BaseCollider() = default;

	friend class CollisionManager;

	//オブジェクトをメンバ変数のオブジェクトに代入
	inline void SetObject(IObject2D* objcet)
	{
		this->objcet2d_ = objcet;
	}

	//メンバ変数のオブジェクトの値を返す
	inline IObject2D* GetObject2d()
	{
		return objcet2d_;
	}

	//属性をメンバ変数の属性に代入
	inline void SetAttribute(unsigned short attribute)
	{
		attribute_ = attribute;
	}

	//メンバ変数に属性を追加
	inline void AddAttribute(unsigned short attribute)
	{
		attribute_ |= attribute;
	}

	//メンバ変数の属性を削除
	inline void RemoveAttribute(unsigned short attribute)
	{
		attribute_ &= !attribute;
	}

	/// <summary>
	/// 更新
	/// </summary>
	virtual void Update() = 0;

	//形状タイプ取得
	inline CollisionShapeType GetShapeType() { return shapeType_; }

	//衝突時呼び出し関数
	inline void OnCollison(const CollisionInfo& info)
	{
		objcet2d_->OnCollision(info);
	}

protected:

	//オブジェクト
	IObject2D* objcet2d_ = nullptr;
	//形状タイプ
	CollisionShapeType shapeType_ = SHAPE_UNKNOWN;
	//当たり判定属性
	unsigned short attribute_ = 0b1111111111111111;
};
