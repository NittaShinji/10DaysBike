#pragma once
#include "EnemyBullet.h"
#include <list>

class BulletManager
{
public:

	~BulletManager();
	void Init();
	void Update();
	void Draw();

	void AddBullets(std::list<std::unique_ptr<EnemyBullet>> bullets) {
		// bullets_ は BulletManager のメンバ変数
		bullets_.splice(bullets_.end(), bullets); // リストを追加
	}

private:

	//敵の弾
	std::list<std::unique_ptr<EnemyBullet>> bullets_;

public:
	std::list<std::unique_ptr<EnemyBullet>>& GetBullets() { return bullets_; };
};

