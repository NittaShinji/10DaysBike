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
	//ファイルを開く
	std::ifstream file;
	file.open((RESOUCE_PATH + "enemyPop.csv").c_str());
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
			//敵の行動
			getline(line_stream, word, ',');
			int pattern = atoi(word.c_str());

			//敵を発生させる
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

void EnemyManager::GenerateBadEnemy(const Vec2& GeneratePos, const int32_t pattern)
{
	// 敵の目標地点を設定
	Vec2 targetPos;
	targetPos = Vec2(GeneratePos.x + UI_SIZE.x, 1200);

	//生成地点をUI背景分ずらす
	Vec2 generatePos = Vec2(GeneratePos.x + UI_SIZE.x, GeneratePos.y);

	//敵を生成し、初期化
	std::unique_ptr<BadEnemy> newEnemy = std::make_unique<BadEnemy>();
	newEnemy->Init(generatePos,targetPos,pattern);

	//敵を登録する
	enemies_.push_back(std::move(newEnemy));
}

void EnemyManager::GenerateBulletFlyEnemy(const Vec2& GeneratePos, const int32_t pattern)
{
	const float bulletSpeed = 12.5f;

	//生成地点をUI背景分ずらす
	Vec2 generatePos = Vec2(GeneratePos.x + UI_SIZE.x, GeneratePos.y);

	//敵を生成し、初期化
	std::unique_ptr<BulletFlyEnemy> newEnemy = std::make_unique<BulletFlyEnemy>();
	newEnemy->Init(generatePos, bulletSpeed);

	newEnemy->SetBullletManger(bulletManager_.get());

	//敵を登録する
	enemies_.push_back(std::move(newEnemy));
}

void EnemyManager::GenerateWanderEnemy(Vec2* PlayerPos, const Vec2& GeneratePos, const int32_t pattern)
{
	//生成地点をUI背景分ずらす
	Vec2 generatePos = Vec2(GeneratePos.x + UI_SIZE.x, GeneratePos.y);

	//敵を生成し、初期化
	std::unique_ptr<WanderEnemy> newEnemy = std::make_unique<WanderEnemy>();
	newEnemy->Init(generatePos, PlayerPos);

	//敵を登録する
	enemies_.push_back(std::move(newEnemy));
}
