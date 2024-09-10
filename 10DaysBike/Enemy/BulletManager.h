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
		// bullets_ �� BulletManager �̃����o�ϐ�
		bullets_.splice(bullets_.end(), bullets); // ���X�g��ǉ�
	}

private:

	//�G�̒e
	std::list<std::unique_ptr<EnemyBullet>> bullets_;

public:
	std::list<std::unique_ptr<EnemyBullet>>& GetBullets() { return bullets_; };
};

