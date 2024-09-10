#include "EnemyManager.h"
#include <random>
#include <fstream>

void EnemyManager::Init()
{
	waitTimer_ = kWaitTime_;
	enemies_.clear();
	bulletManager_ = std::make_unique<BulletManager>();
	GenerateTriangleEnemy();
}

void EnemyManager::Update()
{
	//�f�X�t���O�̗������G���폜
	// �G�̍폜�i�f�X�t���O�̗��������̂��폜�j
	enemies_.erase(
		std::remove_if(enemies_.begin(), enemies_.end(),
		[](std::unique_ptr<IEnemy>& enemy) {
		return enemy->IsDead();
	}),
	enemies_.end());

	if (waitTimer_ >= 0)
	{
		waitTimer_--;
		if (waitTimer_ < 0)
		{
			if (enemies_.size() < kMaxEnemyNum)
			{
				GenerateBulletEnemy();
				waitTimer_ = kWaitTime_;
			}
		}
	}

	for (std::unique_ptr<IEnemy>& enemy : enemies_)
	{
		enemy->Update();
	}

	bulletManager_->Update();
}

void EnemyManager::Draw()
{
	for (std::unique_ptr<IEnemy>& enemy : enemies_)
	{
		enemy->Draw();
	}

	bulletManager_->Draw();
}

void EnemyManager::LoadEnemyPopDate()
{
	//�t�@�C�����J��
	std::ifstream file;
	file.open("//CSV�̃t�@�C���p�X");
	assert(file.is_open());

	//�t�@�C���̓��e�𕶎���X�g���[���ɃR�s�[
	enemyPopComands << file.rdbuf();

	//�t�@�C�������
	file.close();
}

void EnemyManager::UpdateEnemyPopComands()
{
	//1�s���̕����������ϐ�
	std::string line;

	//�R�}���h���s���[�v
	while (getline(enemyPopComands, line))
	{
		//1�s���̕�������X�g���[���ɕϊ����ĉ�͂��₷������
		std::istringstream line_stream(line);

		std::string word;
		//,��؂�ōs�̐擪��������擾
		getline(line_stream, word, ',');

		//"//"����n�܂�s�̓R�����g
		if (word.find("//") == 0)
		{
			//�R�����g�s�͔�΂�
			continue;
		}

		//POP�R�}���h
		if (word.find("POP") == 0)
		{
			//x���W

		}
		
	}
}

void EnemyManager::GenerateBulletEnemy()
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
	else if (randomValue == Left)
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

void EnemyManager::GenerateTriangleEnemy()
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
	Vec2 popPos;

	if (randomValue == Up)
	{
		popPos = { WINDOW_SIZE.x / 2 ,WINDOW_SIZE .y / 2 - 250};
	}
	else if (randomValue == Left)
	{
		popPos = { WINDOW_SIZE.x / 2 ,WINDOW_SIZE.y / 2 - 250 };
	}
	else
	{
		popPos = { WINDOW_SIZE.x / 2 ,WINDOW_SIZE.y / 2 - 250 };
	}

	//�G�𐶐����A������
	std::unique_ptr<TriangleEnemy> newEnemy = std::make_unique<TriangleEnemy>();
	newEnemy->Init(popPos);

	newEnemy->SetBullletManger(bulletManager_.get());

	//�G��o�^����
	enemies_.push_back(std::move(newEnemy));
}
