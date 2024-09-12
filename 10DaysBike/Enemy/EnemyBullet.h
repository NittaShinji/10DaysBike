#pragma once

#include "IObject2D.h"
#include "CircleCollider.h"

class EnemyBullet : public IObject2D
{

public:
	EnemyBullet();
	~EnemyBullet();

	void Initialize(const Vec2& position, const Vec2& velocity);
	void Init()override;
	void Update()override;

	//ゲッター
	bool IsDead() const { return isDead_; }

	//描画
	void Draw()override;

	// 衝突を検知したら呼び出されるコールバック関数
	void OnCollision(const CollisionInfo& info) override;

	void OnCollisionStop();

	//死ぬ
	void Dead();

	//リセット
	void Reset(Vec2 position);

	void SetDead() { isDead_ = true; };

	void SetGraph(int graph) { graph_ = graph; isDrawGraph_ = true; };
	

private:

	const float kBulletRadius_ = 5.0f;

	//回転角
	float radian_;

	//速度
	Vec2 velocity_;

	float size_ = 5;

	//寿命
	static const int32_t kLifeTime = 60 * 5;

	//デスタイマー
	int32_t deathTimer_ = kLifeTime;
	//デスフラグ
	bool isDead_ = false;

	bool canMoved;

	//当たったかどうか
	bool isHit_ = false;

	bool markedForDeletion_ = false;

	int graph_ = 0;

	bool isDrawGraph_ = false;

	//敵のコライダー
	std::unique_ptr<CircleCollider> bulletCollider_ = nullptr;

};