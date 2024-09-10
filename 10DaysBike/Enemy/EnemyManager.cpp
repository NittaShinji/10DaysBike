#include "EnemyManager.h"
#include <random>
#include <fstream>

void EnemyManager::Init()
{
	waitTimer_ = kWaitTime_;
	enemies_.clear();
	bulletManager_ = std::make_unique<BulletManager>();
	GenerateBulletFlyEnemy();
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
				GenerateBadEnemy();
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
	//�ҋ@����
	if (isWaitEnemy_)
	{
		enemyWaitTimer_--;
		if (enemyWaitTimer_ <= 0)
		{
			//�ҋ@����
			isWaitEnemy_ = false;
		}
		return;
	}

	//1�s���̕����������ϐ�
	std::string line;

	//�R�}���h���s���[�v
	//�R�}���h���s���[�v
	while (getline(enemyPopComands, line))
	{
		//1�s���̕�������X�g���[���ɕϊ����ĉ�͂��₷������
		std::istringstream line_stream(line);

		std::string word;
		//,��؂�ōs�̐擪��������擾
		getline(line_stream, word, ',');

		// "//"����n�܂�s�̓R�����g
		if (word.find("//") == 0)
		{
			//�R�����g�s���΂�
			continue;
		}

		//POP�R�}���h
		if (word.find("POP") == 0)
		{
			//X���W
			getline(line_stream, word, ',');
			float x = (float)std::atof(word.c_str());
			//Y���W
			getline(line_stream, word, ',');
			float y = (float)std::atof(word.c_str());
			//�G�̖��O
			getline(line_stream, word, ',');
			int enemyNum = atoi(word.c_str());

			//�G�𔭐�������
			if (enemyNum == 5)
			{
				//GenerateBadEnemy(Vec2(x, y));
			}
			else if (enemyNum == 6)
			{
				//GenerateBulletFlyEnemy(Vec2(x, y));
			}
		}
		//WAIT�R�}���h
		else if (word.find("WAIT") == 0)
		{
			getline(line_stream, word, ',');

			//�҂�����
			int32_t waitTime = atoi(word.c_str());

			//�ҋ@�J�n
			isWaitEnemy_ = true;
			enemyWaitTimer_ = waitTime;

			//�R�}���h���[�v�𔲂���
			break;
		}
	}
}

void EnemyManager::GenerateBadEnemy()
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
	Vec2 targetPos;

	if (randomValue == Up)
	{
		enemyPopPos = kEnemyPopUP;
		targetPos = Vec2(kEnemyPopUP.x, 1200);
	}
	else if (randomValue == Left)
	{
		enemyPopPos = kEnemyPopLeft;
		targetPos = Vec2(1200, kEnemyPopUP.y + 300);
	}
	else
	{
		enemyPopPos = kEnemyPopRight;
		targetPos = Vec2(-300, kEnemyPopRight.y + 300);
	}

	//�G�𐶐����A������
	std::unique_ptr<BadEnemy> newEnemy = std::make_unique<BadEnemy>();
	newEnemy->Init(enemyPopPos,targetPos);

	//�G��o�^����
	enemies_.push_back(std::move(newEnemy));
}

void EnemyManager::GenerateBulletFlyEnemy()
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

	const float bulletSpeed = 12.5f;

	//�G�𐶐����A������
	std::unique_ptr<BulletFlyEnemy> newEnemy = std::make_unique<BulletFlyEnemy>();
	newEnemy->Init(popPos, bulletSpeed);

	newEnemy->SetBullletManger(bulletManager_.get());

	//�G��o�^����
	enemies_.push_back(std::move(newEnemy));
}

void EnemyManager::GenerateWanderEnemy(Vec2* PlayerPos, const Vec2& GeneratePos)
{
	//�G�𐶐����A������
	std::unique_ptr<WanderEnemy> newEnemy = std::make_unique<WanderEnemy>();
	newEnemy->Init(GeneratePos, PlayerPos);

	//�G��o�^����
	enemies_.push_back(std::move(newEnemy));
}
