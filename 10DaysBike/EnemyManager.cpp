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
	//デスフラグの立った敵を削除
	// 敵の削除（デスフラグの立ったものを削除）
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
	//ファイルを開く
	std::ifstream file;
	file.open("//CSVのファイルパス");
	assert(file.is_open());

	//ファイルの内容を文字列ストリームにコピー
	enemyPopComands << file.rdbuf();

	//ファイルを閉じる
	file.close();
}

void EnemyManager::UpdateEnemyPopComands()
{
	//1行分の文字列を入れる変数
	std::string line;

	//コマンド実行ループ
	while (getline(enemyPopComands, line))
	{
		//1行分の文字列をストリームに変換して解析しやすくする
		std::istringstream line_stream(line);

		std::string word;
		//,区切りで行の先頭文字列を取得
		getline(line_stream, word, ',');

		//"//"から始まる行はコメント
		if (word.find("//") == 0)
		{
			//コメント行は飛ばす
			continue;
		}

		//POPコマンド
		if (word.find("POP") == 0)
		{
			//x座標

		}
		
	}
}

void EnemyManager::GenerateBulletEnemy()
{
	//乱数シード生成器
	std::random_device seed_gen;
	//メルセンヌツイスターの乱数エンジン
	std::mt19937_64 engine(seed_gen());
	//乱数範囲の指定
	std::uniform_int_distribution<int> dist(0, 2);

	// ランダムな値を取得
	int randomValue = dist(engine);

	// 敵の位置をランダムで生成
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

	//敵を生成し、初期化
	std::unique_ptr<Enemy> newEnemy = std::make_unique<Enemy>();
	newEnemy->Init(enemyPopPos);

	newEnemy->SetBullletManger(bulletManager_.get());

	//敵を登録する
	enemies_.push_back(std::move(newEnemy));
}

void EnemyManager::GenerateTriangleEnemy()
{
	//乱数シード生成器
	std::random_device seed_gen;
	//メルセンヌツイスターの乱数エンジン
	std::mt19937_64 engine(seed_gen());
	//乱数範囲の指定
	std::uniform_int_distribution<int> dist(0, 2);

	// ランダムな値を取得
	int randomValue = dist(engine);

	// 敵の位置をランダムで生成
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

	//敵を生成し、初期化
	std::unique_ptr<TriangleEnemy> newEnemy = std::make_unique<TriangleEnemy>();
	newEnemy->Init(popPos);

	newEnemy->SetBullletManger(bulletManager_.get());

	//敵を登録する
	enemies_.push_back(std::move(newEnemy));
}
