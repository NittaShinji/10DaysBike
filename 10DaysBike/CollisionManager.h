#pragma once
#include "CollisionPrimitive.h"
#include "BaseCollider.h"
#include <forward_list>

class CollisionManager
{
public: //静的メンバ関数

	static CollisionManager* GetInstance();

	//デフォルトコンストラクタ
	CollisionManager() = default;
	//デフォルトデストラクタ
	~CollisionManager() = default;
	//コピーコンストラクタの無効
	CollisionManager(const CollisionManager&) = delete;
	//代入演算子の無効
	CollisionManager& operator = (const CollisionManager&) = delete;

public: //メンバ関数

	/// <summary>
	/// コライダーの追加
	/// </summary>
	/// <param name="collider">コライダー</param>
	inline void AddCollider(BaseCollider* collider)
	{
		colliders.push_front(collider);
	}

	/// <summary>
	/// コライダーの削除
	/// </summary>
	/// <param name="collider">コライダー</param>
	inline void RemoveCollider(BaseCollider* collider)
	{
		colliders.remove(collider);
	}

	/// <summary>
	/// 全ての衝突をチェック
	/// </summary>
	void CheckAllCollisions();

private:

	//コライダーのリスト
	std::forward_list<BaseCollider*> colliders;
};

