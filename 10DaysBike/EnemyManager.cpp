#include "EnemyManager.h"
#include <random>

void EnemyManager::Init()
{
	waitTimer_ = kWaitTime_;
	bulletManager_ = std::make_unique<BulletManager>();
}

void EnemyManager::Update()
{
	//�f�X�t���O�̗������G���폜
	// �G�̍폜�i�f�X�t���O�̗��������̂��폜�j
	enemies_.erase(
		std::remove_if(enemies_.begin(), enemies_.end(),
		[](std::unique_ptr<Enemy>& enemy) {
		return enemy->IsDead();
	}),
	enemies_.end());

	if (waitTimer_ >= 0)
	{
		waitTimer_--;
		if (waitTimer_ < 0)
		{
			GenerateEnemy();
			waitTimer_ = kWaitTime_;
		}
	}

	for (std::unique_ptr<Enemy>& enemy : enemies_)
	{
		enemy->Update();
	}

	bulletManager_->Update();
}

void EnemyManager::Draw()
{
	for (std::unique_ptr<Enemy>& enemy : enemies_)
	{
		enemy->Draw();
	}

	bulletManager_->Draw();
}

void EnemyManager::GenerateEnemy()
{
	//�����V�[�h������
	std::random_device seed_gen;
	//�����Z���k�c�C�X�^�[�̗����G���W��
	std::mt19937_64 engine(seed_gen());
	//�����͈͂̎w��
	std::uniform_int_distribution<int> dist(0, 2);

	// �����_���Ȓl���擾
	int randomValue = dist(engine);

	// �G�̈ʒu�������_���Ő���
	Vec2 enemyPopPos;
	if (randomValue == Up)
	{
		enemyPopPos = kEnemyPopUP;
	}
	else if (randomValue == Up)
	{
		enemyPopPos = kEnemyPopLeft;
	}
	else
	{
		enemyPopPos = kEnemyPopRight;
	}

	//�G�𐶐����A������
	std::unique_ptr<Enemy> newEnemy = std::make_unique<Enemy>();
	newEnemy->Init(enemyPopPos);

	newEnemy->SetBullletManger(bulletManager_.get());

	//�G��o�^����
	enemies_.push_back(std::move(newEnemy));
}
