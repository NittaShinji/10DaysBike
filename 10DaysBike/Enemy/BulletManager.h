#pragma once
#include "EnemyBullet.h"
#include <list>

class BulletManager
{
public:
	BulletManager();
	~BulletManager();
	void Init();
	void Update();
	void Draw();

	void AddBullets(std::list<std::unique_ptr<EnemyBullet>> bullets) {
		// bullets_ ‚Í BulletManager ‚Ìƒƒ“ƒo•Ï”
		bullets_.splice(bullets_.end(), bullets); // ƒŠƒXƒg‚ğ’Ç‰Á
	}

	int normalBulletGraph_;
	int normalBulletAnmGraph_[3];
	int beamTopGraph_;
	int beamLineGraph_;
private:

	//“G‚Ì’e
	std::list<std::unique_ptr<EnemyBullet>> bullets_;

public:
	std::list<std::unique_ptr<EnemyBullet>>& GetBullets() { return bullets_; };
};

