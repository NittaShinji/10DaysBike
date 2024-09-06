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
	float attackTimer_ = kAttackTime_;
	//中心からの角度
	float angle = 0.0f;
	//円運動の速度
	const float circleMoveSpeed = 0.35f;


public:
	void Init()override;
	void Update()override;
	void Draw()override;

};
