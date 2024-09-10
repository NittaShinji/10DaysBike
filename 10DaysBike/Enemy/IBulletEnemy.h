#pragma once
#include "IEnemy.h"
#include "EnemyBullet.h"

//前方宣言
class IBulletEnemyState;
class BulletManager;

class IBulletEnemy : public IEnemy
{
public:
	~IBulletEnemy();

protected:

	//ステート
	std::unique_ptr<IBulletEnemyState>state_ = nullptr;
	//弾管理クラス
	BulletManager* bulletManager_ = nullptr;
	//敵の弾
	std::list<std::unique_ptr<EnemyBullet>> bullets_;
	//弾のスピード
	float bulletSpeed_;

public:
	void ChangeState(std::unique_ptr<IBulletEnemyState> state);

public:
	virtual void Init(const Vec2& pos, float bulletSpeed,std::string name);
	void Update()override;
	void Draw()override;
public:

	//衝突時に呼び出される関数
	void OnCollision(const CollisionInfo& info) override;

public:

	//弾を発射
	void Fire(float bulletSpeed);

public:

	std::list<std::unique_ptr<EnemyBullet>>& GetBullets() { return bullets_; };
	void SetBullletManger(BulletManager* bulletManager) { bulletManager_ = bulletManager; }
	BulletManager* GetBullletManager() { return bulletManager_; }
	float GetBulletSpeed() { return bulletSpeed_; }

};

