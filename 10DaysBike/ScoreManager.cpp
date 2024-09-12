#include "ScoreManager.h"
#include "Vec2.h"

void ScoreManager::Init()
{
	totalScore_ = std::make_unique<Score>();
	totalScore_->Init(Vec2(500,500));
	Score::Load();
}

void ScoreManager::Update()
{
	totalScore_->Update();
}

void ScoreManager::Draw()
{
	totalScore_->Draw();
	//ランキングの表示
}

void ScoreManager::RegistScore(std::vector<std::string>& deadEnemyNames)
{
    bool scoreAdded = false;

	for (std::string& deadEnemyName : deadEnemyNames)
	{
        for (std::string& deadEnemyName : deadEnemyNames)
        {
            if (deadEnemyName == "BadEnemy")
            {
                totalScore_->AddScore(100);
                scoreAdded = true;
            }
            else if (deadEnemyName == "BeamEnemy")
            {
                totalScore_->AddScore(500);
                scoreAdded = true;
            }
            else if (deadEnemyName == "BulletFlyEnemy")
            {
                totalScore_->AddScore(1000);
                scoreAdded = true;
            }
            else if (deadEnemyName == "WanderEnemy")
            {
                totalScore_->AddScore(200);
                scoreAdded = true;
            }
        }

        if (scoreAdded)
        {
            totalScore_->SetIsDrum(true);
        }
	}

    if (scoreAdded)
    {
        // 新しいスコアに合わせて目標スコアを設定
        totalScore_->SetTargetScore(totalScore_->GetScore());

        // ドラムロールを開始
        totalScore_->SetIsDrum(true);
        totalScore_->SetDrumTimer(0.0f);  // ドラムロールのタイマーをリセット
    }

	// deadEnemyNamesを空にする
	deadEnemyNames.clear();
}

void ScoreManager::UpdateRanking()
{

}
