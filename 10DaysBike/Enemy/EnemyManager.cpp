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
	//待機処理
	if (isWaitEnemy_)
	{
		enemyWaitTimer_--;
		if (enemyWaitTimer_ <= 0)
		{
			//待機完了
			isWaitEnemy_ = false;
		}
		return;
	}

	//1行分の文字列を入れる変数
	std::string line;

	//コマンド実行ループ
	//コマンド実行ループ
	while (getline(enemyPopComands, line))
	{
		//1行分の文字列をストリームに変換して解析しやすくする
		std::istringstream line_stream(line);

		std::string word;
		//,区切りで行の先頭文字列を取得
		getline(line_stream, word, ',');

		// "//"から始まる行はコメント
		if (word.find("//") == 0)
		{
			//コメント行を飛ばす
			continue;
		}

		//POPコマンド
		if (word.find("POP") == 0)
		{
			//X座標
			getline(line_stream, word, ',');
			float x = (float)std::atof(word.c_str());
			//Y座標
			getline(line_stream, word, ',');
			float y = (float)std::atof(word.c_str());
			//敵の名前
			getline(line_stream, word, ',');
			int enemyNum = atoi(word.c_str());

			//敵を発生させる
			if (enemyNum == 5)
			{
				//GenerateBadEnemy(Vec2(x, y));
			}
			else if (enemyNum == 6)
			{
				//GenerateBulletFlyEnemy(Vec2(x, y));
			}
		}
		//WAITコマンド
		else if (word.find("WAIT") == 0)
		{
			getline(line_stream, word, ',');

			//待ち時間
			int32_t waitTime = atoi(word.c_str());

			//待機開始
			isWaitEnemy_ = true;
			enemyWaitTimer_ = waitTime;

			//コマンドループを抜ける
			break;
		}
	}
}

void EnemyManager::GenerateBadEnemy()
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

	//敵を生成し、初期化
	std::unique_ptr<BadEnemy> newEnemy = std::make_unique<BadEnemy>();
	newEnemy->Init(enemyPopPos,targetPos);

	//敵を登録する
	enemies_.push_back(std::move(newEnemy));
}

void EnemyManager::GenerateBulletFlyEnemy()
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

	const float bulletSpeed = 12.5f;

	//敵を生成し、初期化
	std::unique_ptr<BulletFlyEnemy> newEnemy = std::make_unique<BulletFlyEnemy>();
	newEnemy->Init(popPos, bulletSpeed);

	newEnemy->SetBullletManger(bulletManager_.get());

	//敵を登録する
	enemies_.push_back(std::move(newEnemy));
}

void EnemyManager::GenerateWanderEnemy(Vec2* PlayerPos, const Vec2& GeneratePos)
{
	//敵を生成し、初期化
	std::unique_ptr<WanderEnemy> newEnemy = std::make_unique<WanderEnemy>();
	newEnemy->Init(GeneratePos, PlayerPos);

	//敵を登録する
	enemies_.push_back(std::move(newEnemy));
}
