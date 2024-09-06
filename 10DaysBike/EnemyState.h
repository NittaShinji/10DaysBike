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

public:
	void Init()override;
	void Update()override;
	void Draw()override;

};

//攻撃状態
class EnemyStateAttack : public IEnemyState
{

private:

public:
	void Init()override;
	void Update()override;
	void Draw()override;

};
