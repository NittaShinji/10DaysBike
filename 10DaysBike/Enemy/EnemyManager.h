#pragma once
#include "BadEnemy.h"
#include "BulletFlyEnemy.h"
#include "WanderEnemy.h"
#include "BulletEnemyState.h"
#include "BulletManager.h"
#include <vector>
#include <sstream>

class EnemyManager
{
public:

	// �}�`�̌`
	enum EnmeyPopInfo {
		Up = 0,		// ��
		Right,	// �E
		Left,	// ��
	};

	enum EnmeyNameNum {
		BAT = 5,
		BULLET_FLY,
		WANDER,
	};

	const Vec2 kEnemyPopUP = Vec2(WINDOW_SIZE.x / 2, -100.0f);
	const Vec2 kEnemyPopLeft = Vec2(-300, 100.0f);
	const Vec2 kEnemyPopRight = Vec2(900, 100.0f);
	const int kMaxEnemyNum = 20;

private:
	std::vector<std::unique_ptr<IEnemy>> enemies_;
	std::unique_ptr<BulletManager> bulletManager_;
public:
	~EnemyManager() { enemies_.clear(); }
private:

	//�G�����f�[�^�̓ǂݍ���
	void LoadEnemyPopDate();
	//�G�����R�}���h�̍X�V
	void UpdateEnemyPopComands();
	//�G�����֐�
	void GenerateBadEnemy();
	void GenerateBulletFlyEnemy();
	/*void GenerateBadEnemy(Vec2 pos);
	void GenerateBulletFlyEnemy(Vec2 pos);*/
	void GenerateWanderEnemy(Vec2* PlayerPos ,const Vec2& GeneratePos );


public:
	void Init();
	void Update();
	void Draw();

private:

	const float kWaitTime_ = 120.0f;
	float waitTimer_ = kWaitTime_;
	//�G�����R�}���h
	std::stringstream enemyPopComands;

	//�G�ҋ@���t���O
	bool isWaitEnemy_;

	//�G�ҋ@���^�C�}�[
	int32_t enemyWaitTimer_;
};

