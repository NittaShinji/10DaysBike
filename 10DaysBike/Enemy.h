#pragma once
#include"IEnemy.h"
#include "CircleCollider.h"
#include"TrajectoriesManager.h"
#include "EnemyBullet.h"
#include <list>

//�O���錾
class IEnemyState;
class BulletManager;

//�G
class Enemy : public IEnemy
{
public:
	static const uint16_t PROT_ENEMY_DAMEGE_NUM = 1;
	static const uint16_t PROT_ENEMY_IMGAE_NUM = 4;

private:

	//�O�Ղ̊Ǘ��N���X
	//std::unique_ptr<TrajectoriesManager> trajManag_ = nullptr;
	//�X�e�[�g
	std::unique_ptr<IEnemyState>state_ = nullptr;
	//�G�̒e
	std::list<std::unique_ptr<EnemyBullet>> bullets_;

public:
	~Enemy();
	
private:
	void MoveUpdate();
public:
	void Init()override;
	void Init(const Vec2& pos);
	void Update()override;
	void Draw()override;
public:
	void ChangeState(std::unique_ptr<IEnemyState> state);
	void ProccesingNewTrajs();
	//�Փˎ��ɌĂяo�����֐�
	void OnCollision(const CollisionInfo& info) override;
	
private:
	//int graphHandle_[PROT_ENEMY_IMGAE_NUM];
	int graphHandle_;

	BulletManager* bulletManager_ = nullptr;

public:

	std::list<std::unique_ptr<EnemyBullet>>& GetBullets() { return bullets_; };
	void SetBullletManger(BulletManager* bulletManager) { bulletManager_ = bulletManager; }
	BulletManager* GetBullletManager() { return bulletManager_; }
};

