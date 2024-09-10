#pragma once

//前方宣言
class Enemy;

//敵のステートの基底クラス
class IEnemyState
{
protected:
	Enemy* enemy_ = nullptr;

public:
	void SetEnemyPtr(Enemy* enemy) { enemy_ = enemy; }

public:
	virtual void Init() = 0;
	virtual void Update();
	virtual void Draw() = 0;
};

//待機状態
class EnemyStateWait : public IEnemyState
{

private:
	const float kWaitTime_ = 20.0f;
	float waitTimer_ = kWaitTime_;

public:
	void Init()override;
	void Update()override;
	void Draw()override;

};

//攻撃状態
class EnemyStateAttack : public IEnemyState
{

private:
	const float kAttackTime_ = 120.0f;
	const float kMoveCircleRadius_ = 175.0f;

	float attackTimer_ = kAttackTime_;
	//中心からの角度
	float angle = 0.0f;
	//円運動の速度
	const float circleMoveSpeed = 0.35f;
	//発射タイマー
	int32_t bulletCoolTimer_;
	//発射時間
	const float kBulletCoolTime_ = 60.0f;
	//出現位置を保存
	Vec2 savePopPos_;
	//中心点
	Vec2 centerPos_;
	// 円周上への移動中かどうか
	bool inTransition; 
	//移動速度
	float moveSpeed_;
	//角速度
	float radianSpeed_;

public:
	void Init()override;
	void Update()override;
	void Draw()override;

public:
	void Fire();

};
