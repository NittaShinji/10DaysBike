#include "EnemyManager.h"
#include "Inform.h"
#include <random>
#include <fstream>

void EnemyManager::Init()
{
	waitTimer_ = kWaitTime_;
	enemies_.clear();
	bulletManager_ = std::make_unique<BulletManager>();
	isWaitEnemy_ = false;
	LoadEnemyPopDate();
	//GenerateBulletFlyEnemy();
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
				GenerateBadEnemy({ 300,60 },1);
				//GenerateWanderEnemy(playerPosPtr_,{630,30});
				waitTimer_ = kWaitTime_;
			}
		}
	}

	UpdateEnemyPopComands();

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

void EnemyManager::SetPlayerPosPtr(Vec2* pPosPtr)
{
	playerPosPtr_ = pPosPtr;
}

void EnemyManager::LoadEnemyPopDate()
{
	//�t�@�C�����J��
	std::ifstream file;
	file.open((RESOUCE_PATH + "enemyPop.csv").c_str());
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
			//�G�̍s��
			getline(line_stream, word, ',');
			int pattern = atoi(word.c_str());

			//�G�𔭐�������
			if (enemyNum == BAT)
			{
				GenerateBadEnemy(Vec2(x,y), pattern);
			}
			else if (enemyNum == BULLET_FLY)
			{
				GenerateBulletFlyEnemy(Vec2(x, y), pattern);
			}
			else if (enemyNum == WANDER)
			{
				GenerateWanderEnemy(playerPosPtr_, Vec2(x, y), pattern);
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

void EnemyManager::GenerateBadEnemy(const Vec2& GeneratePos, const int32_t pattern)
{
	// �G�̖ڕW�n�_��ݒ�
	Vec2 targetPos;
	targetPos = Vec2(GeneratePos.x + UI_SIZE.x, 1200);

	//�����n�_��UI�w�i�����炷
	Vec2 generatePos = Vec2(GeneratePos.x + UI_SIZE.x, GeneratePos.y);

	//�G�𐶐����A������
	std::unique_ptr<BadEnemy> newEnemy = std::make_unique<BadEnemy>();
	newEnemy->Init(generatePos,targetPos,pattern);

	//�G��o�^����
	enemies_.push_back(std::move(newEnemy));
}

void EnemyManager::GenerateBulletFlyEnemy(const Vec2& GeneratePos, const int32_t pattern)
{
	const float bulletSpeed = 12.5f;

	//�����n�_��UI�w�i�����炷
	Vec2 generatePos = Vec2(GeneratePos.x + UI_SIZE.x, GeneratePos.y);

	//�G�𐶐����A������
	std::unique_ptr<BulletFlyEnemy> newEnemy = std::make_unique<BulletFlyEnemy>();
	newEnemy->Init(generatePos, bulletSpeed);

	newEnemy->SetBullletManger(bulletManager_.get());

	//�G��o�^����
	enemies_.push_back(std::move(newEnemy));
}

void EnemyManager::GenerateWanderEnemy(Vec2* PlayerPos, const Vec2& GeneratePos, const int32_t pattern)
{
	//�����n�_��UI�w�i�����炷
	Vec2 generatePos = Vec2(GeneratePos.x + UI_SIZE.x, GeneratePos.y);

	//�G�𐶐����A������
	std::unique_ptr<WanderEnemy> newEnemy = std::make_unique<WanderEnemy>();
	newEnemy->Init(generatePos, PlayerPos);

	//�G��o�^����
	enemies_.push_back(std::move(newEnemy));
}
