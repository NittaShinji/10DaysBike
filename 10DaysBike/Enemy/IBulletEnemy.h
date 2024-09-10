#pragma once
#include "IEnemy.h"
#include "EnemyBullet.h"

//�O���錾
class IBulletEnemyState;
class BulletManager;

class IBulletEnemy : public IEnemy
{
public:
	~IBulletEnemy();

protected:

	//�X�e�[�g
	std::unique_ptr<IBulletEnemyState>state_ = nullptr;
	//�e�Ǘ��N���X
	BulletManager* bulletManager_ = nullptr;
	//�G�̒e
	std::list<std::unique_ptr<EnemyBullet>> bullets_;
	//�e�̃X�s�[�h
	float bulletSpeed_;

public:
	void ChangeState(std::unique_ptr<IBulletEnemyState> state);

public:
	virtual void Init(const Vec2& pos, float bulletSpeed,std::string name);
	void Update()override;
	void Draw()override;
public:

	//�Փˎ��ɌĂяo�����֐�
	void OnCollision(const CollisionInfo& info) override;

public:

	//�e�𔭎�
	void Fire(float bulletSpeed);

public:

	std::list<std::unique_ptr<EnemyBullet>>& GetBullets() { return bullets_; };
	void SetBullletManger(BulletManager* bulletManager) { bulletManager_ = bulletManager; }
	BulletManager* GetBullletManager() { return bulletManager_; }
	float GetBulletSpeed() { return bulletSpeed_; }

};

